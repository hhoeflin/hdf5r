/**************************************************************************
 * 
 * Copyright 2016 Novartis Institutes for BioMedical Research Inc.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *************************************************************************/


#include "global.h"
#include <stdlib.h>
#include <time.h>


struct client_data_struct {
  ssize_t pos;
  char *err_msg;
};

#define MSG_SIZE       64
#define ERROR_MSG_SIZE 256

herr_t custom_print_cb(unsigned n, const H5E_error2_t *err_desc, void* client_data) {
    char                maj[MSG_SIZE];
    char                min[MSG_SIZE];
    char                cls[MSG_SIZE];
    const int		indent = 4;

    /* Get descriptions for the major and minor error numbers */
    if(H5Eget_class_name(err_desc->cls_id, cls, MSG_SIZE)<0)
      error("Error getting cls_id in custom_print_cb");

    if(H5Eget_msg(err_desc->maj_num, NULL, maj, MSG_SIZE)<0)
      error("Error getting maj_num in custom_print_cb");

    if(H5Eget_msg(err_desc->min_num, NULL, min, MSG_SIZE)<0)
      error("Error getting min_num in custom_print_cb");

    struct client_data_struct * cd = client_data;

    int have_desc = 1;
    if(err_desc->desc == NULL || strlen(err_desc->desc) == 0)
      have_desc=0;
    
    snprintf(cd->err_msg + cd->pos, ERROR_MSG_SIZE , "%*serror #%03u: %s in %s(): line %u%s%s\n",
	     indent, "", n, err_desc->file_name,
	     err_desc->func_name, err_desc->line, (have_desc ? ": " : ""),
             (have_desc ? err_desc->desc : "")); 
    cd->pos += strlen(cd->err_msg + cd->pos);
    snprintf(cd->err_msg + cd->pos, ERROR_MSG_SIZE, "%*sclass: %s\n", indent*2, "", cls);
    cd->pos += strlen(cd->err_msg + cd->pos);
    snprintf(cd->err_msg + cd->pos, ERROR_MSG_SIZE, "%*smajor: %s\n", indent*2, "", maj);
    cd->pos += strlen(cd->err_msg + cd->pos);
    snprintf(cd->err_msg + cd->pos, ERROR_MSG_SIZE, "%*sminor: %s\n\n", indent*2, "", min);
    cd->pos += strlen(cd->err_msg + cd->pos);

    return 0;
}


herr_t _errorCollector( hid_t estack_id, void * stream) {
  int was_default = 0;
  if(estack_id == H5E_DEFAULT) {
    // need to get a copy of the stack
    was_default = 1;
    estack_id = H5Eget_current_stack();
  }

  struct client_data_struct client_data;
  client_data.pos = 0;

  ssize_t s = H5Eget_num(estack_id);
  if ( s > 0) {
    
    // allocate sufficient space for the string
    client_data.err_msg = R_alloc(s+1, 4 * ERROR_MSG_SIZE);

    // Give the message a header pointing to it being from HDF5
    client_data.err_msg = strncpy(client_data.err_msg, "HDF5-API Errors:\n", ERROR_MSG_SIZE);
    client_data.pos = strlen(client_data.err_msg);
    ssize_t initial_pos = client_data.pos;

    herr_t eee = H5Ewalk2(estack_id, H5E_WALK_DOWNWARD, &custom_print_cb, &client_data);
    if(eee < 0) {
      client_data.err_msg = "Error walking the error stack!";
      client_data.pos = strlen(client_data.err_msg);
    }


    // check if any error was written at all (has to, just as s>0; just to make sure
    if(client_data.pos == initial_pos) {
      strncpy(client_data.err_msg + client_data.pos, "There were errors, but could not retrieve any error messages\n", ERROR_MSG_SIZE);
    }
    else { // superfluous newline at the end - remove
      client_data.err_msg[client_data.pos - 1] = '\0';
    }
  } 
  else {
    client_data.err_msg = "HDF5-API Errors:\nNo error messages\n";
  }
  
  // close the stack we openend
  if(was_default) {
    H5Eclose_stack(estack_id);
  }
  error(client_data.err_msg);

  return 0;
}



SEXP R_H5error(void) {
  H5E_auto2_t err_func;
  void *err_func_data;
  herr_t err;
  err = H5Eget_auto2 (H5E_DEFAULT, &err_func, &err_func_data);
  if(err < 0) {
    error("Error retrieving current error handler");
  }
  H5E_auto2_t myfct = &_errorCollector;
  err = H5Eset_auto2 (H5E_DEFAULT, myfct, err_func_data);
  if(err < 0) {
    error("Error setting custom error handler");
  }

  return R_NilValue;
}

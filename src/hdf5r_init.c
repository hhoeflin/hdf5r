
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

#include "export_auto.h"
#include "export_manual.h"

R_CallMethodDef libraryRCalls[] = {
  {"R_H5ls", (DL_FUNC) &R_H5ls, 7},
  {"R_H5error", (DL_FUNC) &R_H5error, 0},
  {"R_RToH5", (DL_FUNC) &R_RToH5, 3},
  {"R_H5ToR_Pre", (DL_FUNC) &R_H5ToR_Pre, 2},
  {"R_H5ToR_Post", (DL_FUNC) &R_H5ToR_Post, 5},
  {"R_guess_nelem", (DL_FUNC) &R_guess_nelem, 2},
  {"set_dim_attribute", (DL_FUNC) &set_dim_attribute, 2},
  {"copy_rvec", (DL_FUNC) &copy_rvec, 3},
  {"R_transpose_general", (DL_FUNC) &R_transpose_general, 3},
  {"R_reorder", (DL_FUNC) &R_reorder, 5},
  {"R_read_raw_subset_generic", (DL_FUNC) &R_read_raw_subset_generic, 3},
  {"R_write_raw_subset_generic", (DL_FUNC) &R_write_raw_subset_generic, 4},
  {"string_to_UTF8", (DL_FUNC) &string_to_UTF8, 1},
  {"R_as_hex", (DL_FUNC) &R_as_hex, 1},
  {"init_dtypes", (DL_FUNC) &init_dtypes, 0},
  {"show_all_types_data_frame", (DL_FUNC) &show_all_types_data_frame, 0},
  {"show_all_const_data_frame", (DL_FUNC) &show_all_const_data_frame, 0},
  {NULL, NULL, 0}
};


int R_CallMethodDef_length(R_CallMethodDef * method_ptr) {
  int i = 0;
  while(method_ptr->name != NULL || method_ptr-> fun != NULL || method_ptr->numArgs !=0) {
    method_ptr++;
    i++;
  }
  return(i);
}


void R_init_hdf5r (DllInfo * winDll) {
  R_CallMethodDef* libraryList[] = {libraryRCalls,
				    library_WRAPPER_AUTO_H5T, library_WRAPPER_MANUAL_H5T,
				    library_WRAPPER_AUTO_H5A,
				    library_WRAPPER_AUTO_H5D,
				    library_WRAPPER_AUTO_H5E,
				    library_WRAPPER_AUTO_H5F,
				    library_WRAPPER_AUTO_H5G,
				    library_WRAPPER_AUTO_H5I,
				    library_WRAPPER_AUTO_H5L,
				    library_WRAPPER_AUTO_H5O,
				    library_WRAPPER_AUTO_H5P,
				    library_WRAPPER_AUTO_H5,
				    library_WRAPPER_AUTO_H5R,
				    library_WRAPPER_AUTO_H5S,
				    library_WRAPPER_AUTO_H5Z,
				    library_WRAPPER_AUTO_H5DS,
				    library_WRAPPER_AUTO_H5IM,
				    library_WRAPPER_AUTO_H5LT,
				    library_WRAPPER_AUTO_H5TB,
				    library_WRAPPER_AUTO_H5FDCORE,
				    library_WRAPPER_AUTO_H5FDFAMILY,
				    library_WRAPPER_AUTO_H5FDLOG,
				    library_WRAPPER_AUTO_H5FDSEC2,
				    library_WRAPPER_AUTO_H5FDSTDIO,
				    NULL};

  int total_num_methods = 0;
  R_CallMethodDef** library_ptr = libraryList;
  while(*library_ptr != NULL) {
    total_num_methods += R_CallMethodDef_length(*library_ptr);
    library_ptr++;
  }

  R_CallMethodDef library_all_methods[total_num_methods + 1];
  R_CallMethodDef* library_all_ptr = library_all_methods;
  library_ptr = libraryList;
  // now copy everything over
  while(*library_ptr != NULL) {
    int num_this_library = R_CallMethodDef_length(*library_ptr);
    memcpy(library_all_ptr, *library_ptr, num_this_library * sizeof(R_CallMethodDef));
    library_ptr++;
    library_all_ptr += num_this_library;
  }
  // add the null at the end
  R_CallMethodDef null_ptr = {NULL, NULL, 0};
  library_all_methods[total_num_methods] = null_ptr;

  R_registerRoutines(winDll, NULL, library_all_methods, NULL, NULL);
  R_useDynamicSymbols(winDll, FALSE);
}



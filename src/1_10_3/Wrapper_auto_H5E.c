
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

#include "Wrapper_auto_H5E.h"
/* H5_DLL herr_t H5Eauto_is_v2(hid_t err_stack, unsigned *is_stack); */
SEXP R_H5Eauto_is_v2(SEXP R_err_stack, SEXP R_is_stack){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_is_stack = PROTECT(duplicate(R_is_stack));
  vars_protected++;
  hid_t err_stack = SEXP_to_longlong(R_err_stack, 0);
  unsigned* is_stack;
  if(XLENGTH(R_is_stack) == 0) {
    is_stack = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_is_stack, h5_datatype[DT_unsigned], XLENGTH(R_is_stack)));
    is_stack= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Eauto_is_v2(err_stack, is_stack);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_is_stack, h5_datatype[DT_unsigned]);
  R_is_stack = PROTECT(H5ToR_single_step(is_stack, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_is_stack);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("is_stack"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Eclear2(hid_t err_stack); */
SEXP R_H5Eclear2(SEXP R_err_stack){
  int vars_protected=0;
  hid_t err_stack = SEXP_to_longlong(R_err_stack, 0);
  herr_t return_val = H5Eclear2(err_stack);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Eclose_msg(hid_t err_id); */
SEXP R_H5Eclose_msg(SEXP R_err_id){
  int vars_protected=0;
  hid_t err_id = SEXP_to_longlong(R_err_id, 0);
  herr_t return_val = H5Eclose_msg(err_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Eclose_stack(hid_t stack_id); */
SEXP R_H5Eclose_stack(SEXP R_stack_id){
  int vars_protected=0;
  hid_t stack_id = SEXP_to_longlong(R_stack_id, 0);
  herr_t return_val = H5Eclose_stack(stack_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Ecreate_msg(hid_t cls, H5E_type_t msg_type, const char *msg); */
SEXP R_H5Ecreate_msg(SEXP R_cls, SEXP R_msg_type, SEXP R_msg){
  int vars_protected=0;
  hid_t cls = SEXP_to_longlong(R_cls, 0);
  H5E_type_t msg_type = SEXP_to_longlong(R_msg_type, 0);
  const char* msg = CHAR(STRING_ELT(R_msg, 0));
  hid_t return_val = H5Ecreate_msg(cls, msg_type, msg);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Ecreate_stack(void); */
SEXP R_H5Ecreate_stack(void){
  int vars_protected=0;
  hid_t return_val = H5Ecreate_stack();
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL ssize_t H5Eget_class_name(hid_t class_id, char *name, size_t size); */
SEXP R_H5Eget_class_name(SEXP R_class_id, SEXP R_name, SEXP R_size){
  int vars_protected=0;
  R_name = PROTECT(duplicate(R_name));
  vars_protected++;
  hid_t class_id = SEXP_to_longlong(R_class_id, 0);
  char* name;
  if(XLENGTH(R_name) == 0) {
    name = NULL;
  }
  else {
    name = R_alloc(strlen(CHAR(STRING_ELT(R_name, 0))) + 1, 1);
    strcpy(name, CHAR(STRING_ELT(R_name, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  ssize_t return_val = H5Eget_class_name(class_id, name, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(name==NULL) {
    R_name = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_name = PROTECT(mkString(name));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_name);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("name"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Eget_current_stack(void); */
SEXP R_H5Eget_current_stack(void){
  int vars_protected=0;
  hid_t return_val = H5Eget_current_stack();
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL char *H5Eget_major(H5E_major_t maj); */
SEXP R_H5Eget_major(SEXP R_maj){
  int vars_protected=0;
  H5E_major_t maj = SEXP_to_longlong(R_maj, 0);
  char* return_val = H5Eget_major(maj);
  SEXP R_return_val= R_NilValue;
  if(return_val==NULL) {
    R_return_val = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_return_val = PROTECT(mkString(return_val));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  H5free_memory(return_val);
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL char *H5Eget_minor(H5E_minor_t min); */
SEXP R_H5Eget_minor(SEXP R_min){
  int vars_protected=0;
  H5E_minor_t min = SEXP_to_longlong(R_min, 0);
  char* return_val = H5Eget_minor(min);
  SEXP R_return_val= R_NilValue;
  if(return_val==NULL) {
    R_return_val = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_return_val = PROTECT(mkString(return_val));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  H5free_memory(return_val);
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL ssize_t H5Eget_msg(hid_t msg_id, H5E_type_t *type, char *msg, size_t size); */
SEXP R_H5Eget_msg(SEXP R_msg_id, SEXP R_type, SEXP R_msg, SEXP R_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_type = PROTECT(duplicate(R_type));
  vars_protected++;
  R_msg = PROTECT(duplicate(R_msg));
  vars_protected++;
  hid_t msg_id = SEXP_to_longlong(R_msg_id, 0);
  H5E_type_t* type;
  if(XLENGTH(R_type) == 0) {
    type = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_type, h5_datatype[DT_H5E_type_t], XLENGTH(R_type)));
    type= (H5E_type_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  char* msg;
  if(XLENGTH(R_msg) == 0) {
    msg = NULL;
  }
  else {
    msg = R_alloc(strlen(CHAR(STRING_ELT(R_msg, 0))) + 1, 1);
    strcpy(msg, CHAR(STRING_ELT(R_msg, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  ssize_t return_val = H5Eget_msg(msg_id, type, msg, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_type, h5_datatype[DT_H5E_type_t]);
  R_type = PROTECT(H5ToR_single_step(type, h5_datatype[DT_H5E_type_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  if(msg==NULL) {
    R_msg = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_msg = PROTECT(mkString(msg));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_type);
  SET_VECTOR_ELT(__ret_list, 2, R_msg);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("type"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("msg"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL ssize_t H5Eget_num(hid_t error_stack_id); */
SEXP R_H5Eget_num(SEXP R_error_stack_id){
  int vars_protected=0;
  hid_t error_stack_id = SEXP_to_longlong(R_error_stack_id, 0);
  ssize_t return_val = H5Eget_num(error_stack_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Epop(hid_t err_stack, size_t count); */
SEXP R_H5Epop(SEXP R_err_stack, SEXP R_count){
  int vars_protected=0;
  hid_t err_stack = SEXP_to_longlong(R_err_stack, 0);
  size_t count = SEXP_to_longlong(R_count, 0);
  herr_t return_val = H5Epop(err_stack, count);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Epush2(hid_t err_stack, const char *file, const char *func, unsigned line, hid_t cls_id, hid_t maj_id, hid_t min_id, const char *msg, ...); */
SEXP R_H5Epush2(SEXP R_err_stack, SEXP R_file, SEXP R_func, SEXP R_line, SEXP R_cls_id, SEXP R_maj_id, SEXP R_min_id, SEXP R_msg){
  int vars_protected=0;
  hid_t err_stack = SEXP_to_longlong(R_err_stack, 0);
  const char* file = CHAR(STRING_ELT(R_file, 0));
  const char* func = CHAR(STRING_ELT(R_func, 0));
  unsigned line = SEXP_to_longlong(R_line, 0);
  hid_t cls_id = SEXP_to_longlong(R_cls_id, 0);
  hid_t maj_id = SEXP_to_longlong(R_maj_id, 0);
  hid_t min_id = SEXP_to_longlong(R_min_id, 0);
  const char* msg = CHAR(STRING_ELT(R_msg, 0));
  herr_t return_val = H5Epush2(err_stack, file, func, line, cls_id, maj_id, min_id, msg);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Eregister_class(const char *cls_name, const char *lib_name, const char *version); */
SEXP R_H5Eregister_class(SEXP R_cls_name, SEXP R_lib_name, SEXP R_version){
  int vars_protected=0;
  const char* cls_name = CHAR(STRING_ELT(R_cls_name, 0));
  const char* lib_name = CHAR(STRING_ELT(R_lib_name, 0));
  const char* version = CHAR(STRING_ELT(R_version, 0));
  hid_t return_val = H5Eregister_class(cls_name, lib_name, version);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Eset_current_stack(hid_t err_stack_id); */
SEXP R_H5Eset_current_stack(SEXP R_err_stack_id){
  int vars_protected=0;
  hid_t err_stack_id = SEXP_to_longlong(R_err_stack_id, 0);
  herr_t return_val = H5Eset_current_stack(err_stack_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Eunregister_class(hid_t class_id); */
SEXP R_H5Eunregister_class(SEXP R_class_id){
  int vars_protected=0;
  hid_t class_id = SEXP_to_longlong(R_class_id, 0);
  herr_t return_val = H5Eunregister_class(class_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}


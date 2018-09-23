
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

#include "Wrapper_auto_H5LT.h"
/* H5_HLDLL herr_t H5LTdtype_to_text(hid_t dtype, char *str, H5LT_lang_t lang_type, size_t *len); */
SEXP R_H5LTdtype_to_text(SEXP R_dtype, SEXP R_str, SEXP R_lang_type, SEXP R_len){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_str = PROTECT(duplicate(R_str));
  vars_protected++;
  R_len = PROTECT(duplicate(R_len));
  vars_protected++;
  hid_t dtype = SEXP_to_longlong(R_dtype, 0);
  char* str;
  if(XLENGTH(R_str) == 0) {
    str = NULL;
  }
  else {
    str = R_alloc(strlen(CHAR(STRING_ELT(R_str, 0))) + 1, 1);
    strcpy(str, CHAR(STRING_ELT(R_str, 0)));
  }
  H5LT_lang_t lang_type = SEXP_to_longlong(R_lang_type, 0);
  size_t* len;
  if(XLENGTH(R_len) == 0) {
    len = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_len, h5_datatype[DT_size_t], XLENGTH(R_len)));
    len= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTdtype_to_text(dtype, str, lang_type, len);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(str==NULL) {
    R_str = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_str = PROTECT(mkString(str));
    vars_protected++;
  }
  size_helper = guess_nelem(R_len, h5_datatype[DT_size_t]);
  R_len = PROTECT(H5ToR_single_step(len, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_str);
  SET_VECTOR_ELT(__ret_list, 2, R_len);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("str"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("len"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTfind_attribute( hid_t loc_id, const char *name ); */
SEXP R_H5LTfind_attribute(SEXP R_loc_id, SEXP R_name){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  herr_t return_val = H5LTfind_attribute(loc_id, name);
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

/* H5_HLDLL herr_t H5LTfind_dataset( hid_t loc_id, const char *name ); */
SEXP R_H5LTfind_dataset(SEXP R_loc_id, SEXP R_name){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  herr_t return_val = H5LTfind_dataset(loc_id, name);
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

/* H5_HLDLL herr_t H5LTget_attribute( hid_t loc_id, const char *obj_name, const char *attr_name, hid_t mem_type_id, void *data ); */
SEXP R_H5LTget_attribute(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_mem_type_id, SEXP R_data, SEXP _dupl_data){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_data)) {
    R_data = PROTECT(duplicate(R_data));
    vars_protected++;
  }
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  hid_t mem_type_id = SEXP_to_longlong(R_mem_type_id, 0);
  void* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    data = (void *) VOIDPTR(R_data);
  }
  herr_t return_val = H5LTget_attribute(loc_id, obj_name, attr_name, mem_type_id, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_char( hid_t loc_id, const char *obj_name, const char *attr_name, char *data ); */
SEXP R_H5LTget_attribute_char(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  char* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    data = R_alloc(strlen(CHAR(STRING_ELT(R_data, 0))) + 1, 1);
    strcpy(data, CHAR(STRING_ELT(R_data, 0)));
  }
  herr_t return_val = H5LTget_attribute_char(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(data==NULL) {
    R_data = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_data = PROTECT(mkString(data));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_double( hid_t loc_id, const char *obj_name, const char *attr_name, double *data ); */
SEXP R_H5LTget_attribute_double(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  double* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_data, h5_datatype[DT_double], XLENGTH(R_data)));
    data= (double*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_double(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_data, h5_datatype[DT_double]);
  R_data = PROTECT(H5ToR_single_step(data, h5_datatype[DT_double], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_float( hid_t loc_id, const char *obj_name, const char *attr_name, float *data ); */
SEXP R_H5LTget_attribute_float(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  float* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_data, h5_datatype[DT_float], XLENGTH(R_data)));
    data= (float*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_float(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_data, h5_datatype[DT_float]);
  R_data = PROTECT(H5ToR_single_step(data, h5_datatype[DT_float], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_info( hid_t loc_id, const char *obj_name, const char *attr_name, hsize_t *dims, H5T_class_t *type_class, size_t *type_size ); */
SEXP R_H5LTget_attribute_info(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_dims, SEXP R_type_class, SEXP R_type_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_dims = PROTECT(duplicate(R_dims));
  vars_protected++;
  R_type_class = PROTECT(duplicate(R_type_class));
  vars_protected++;
  R_type_size = PROTECT(duplicate(R_type_size));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  hsize_t* dims;
  if(XLENGTH(R_dims) == 0) {
    dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dims, h5_datatype[DT_hsize_t], XLENGTH(R_dims)));
    dims= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  H5T_class_t* type_class;
  if(XLENGTH(R_type_class) == 0) {
    type_class = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_type_class, h5_datatype[DT_H5T_class_t], XLENGTH(R_type_class)));
    type_class= (H5T_class_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* type_size;
  if(XLENGTH(R_type_size) == 0) {
    type_size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_type_size, h5_datatype[DT_size_t], XLENGTH(R_type_size)));
    type_size= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_info(loc_id, obj_name, attr_name, dims, type_class, type_size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_dims, h5_datatype[DT_hsize_t]);
  R_dims = PROTECT(H5ToR_single_step(dims, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_type_class, h5_datatype[DT_H5T_class_t]);
  R_type_class = PROTECT(H5ToR_single_step(type_class, h5_datatype[DT_H5T_class_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_type_size, h5_datatype[DT_size_t]);
  R_type_size = PROTECT(H5ToR_single_step(type_size, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 4));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_dims);
  SET_VECTOR_ELT(__ret_list, 2, R_type_class);
  SET_VECTOR_ELT(__ret_list, 3, R_type_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 4));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("dims"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("type_class"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("type_size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_int( hid_t loc_id, const char *obj_name, const char *attr_name, int *data ); */
SEXP R_H5LTget_attribute_int(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  int* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_data, h5_datatype[DT_int], XLENGTH(R_data)));
    data= (int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_int(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_data, h5_datatype[DT_int]);
  R_data = PROTECT(H5ToR_single_step(data, h5_datatype[DT_int], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_long( hid_t loc_id, const char *obj_name, const char *attr_name, long *data ); */
SEXP R_H5LTget_attribute_long(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  long* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_data, h5_datatype[DT_long], XLENGTH(R_data)));
    data= (long*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_long(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_data, h5_datatype[DT_long]);
  R_data = PROTECT(H5ToR_single_step(data, h5_datatype[DT_long], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_long_long( hid_t loc_id, const char *obj_name, const char *attr_name, long long *data ); */
SEXP R_H5LTget_attribute_long_long(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  long long* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_data, h5_datatype[DT_long_long], XLENGTH(R_data)));
    data= (long long*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_long_long(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_data, h5_datatype[DT_long_long]);
  R_data = PROTECT(H5ToR_single_step(data, h5_datatype[DT_long_long], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_ndims( hid_t loc_id, const char *obj_name, const char *attr_name, int *rank ); */
SEXP R_H5LTget_attribute_ndims(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_rank){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_rank = PROTECT(duplicate(R_rank));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  int* rank;
  if(XLENGTH(R_rank) == 0) {
    rank = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_rank, h5_datatype[DT_int], XLENGTH(R_rank)));
    rank= (int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_ndims(loc_id, obj_name, attr_name, rank);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_rank, h5_datatype[DT_int]);
  R_rank = PROTECT(H5ToR_single_step(rank, h5_datatype[DT_int], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_rank);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("rank"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_short( hid_t loc_id, const char *obj_name, const char *attr_name, short *data ); */
SEXP R_H5LTget_attribute_short(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  short* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_data, h5_datatype[DT_short], XLENGTH(R_data)));
    data= (short*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_short(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_data, h5_datatype[DT_short]);
  R_data = PROTECT(H5ToR_single_step(data, h5_datatype[DT_short], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_string( hid_t loc_id, const char *obj_name, const char *attr_name, char *data ); */
SEXP R_H5LTget_attribute_string(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  char* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    data = R_alloc(strlen(CHAR(STRING_ELT(R_data, 0))) + 1, 1);
    strcpy(data, CHAR(STRING_ELT(R_data, 0)));
  }
  herr_t return_val = H5LTget_attribute_string(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(data==NULL) {
    R_data = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_data = PROTECT(mkString(data));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_uchar( hid_t loc_id, const char *obj_name, const char *attr_name, unsigned char *data ); */
SEXP R_H5LTget_attribute_uchar(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  unsigned char* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_data, h5_datatype[DT_unsigned_char], XLENGTH(R_data)));
    data= (unsigned char*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_uchar(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_data, h5_datatype[DT_unsigned_char]);
  R_data = PROTECT(H5ToR_single_step(data, h5_datatype[DT_unsigned_char], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_uint( hid_t loc_id, const char *obj_name, const char *attr_name, unsigned int *data ); */
SEXP R_H5LTget_attribute_uint(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  unsigned int* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_data, h5_datatype[DT_unsigned_int], XLENGTH(R_data)));
    data= (unsigned int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_uint(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_data, h5_datatype[DT_unsigned_int]);
  R_data = PROTECT(H5ToR_single_step(data, h5_datatype[DT_unsigned_int], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_ulong( hid_t loc_id, const char *obj_name, const char *attr_name, unsigned long *data ); */
SEXP R_H5LTget_attribute_ulong(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  unsigned long* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_data, h5_datatype[DT_unsigned_long], XLENGTH(R_data)));
    data= (unsigned long*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_ulong(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_data, h5_datatype[DT_unsigned_long]);
  R_data = PROTECT(H5ToR_single_step(data, h5_datatype[DT_unsigned_long], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_attribute_ushort( hid_t loc_id, const char *obj_name, const char *attr_name, unsigned short *data ); */
SEXP R_H5LTget_attribute_ushort(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_data = PROTECT(duplicate(R_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  unsigned short* data;
  if(XLENGTH(R_data) == 0) {
    data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_data, h5_datatype[DT_unsigned_short], XLENGTH(R_data)));
    data= (unsigned short*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_attribute_ushort(loc_id, obj_name, attr_name, data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_data, h5_datatype[DT_unsigned_short]);
  R_data = PROTECT(H5ToR_single_step(data, h5_datatype[DT_unsigned_short], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_dataset_info( hid_t loc_id, const char *dset_name, hsize_t *dims, H5T_class_t *type_class, size_t *type_size ); */
SEXP R_H5LTget_dataset_info(SEXP R_loc_id, SEXP R_dset_name, SEXP R_dims, SEXP R_type_class, SEXP R_type_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_dims = PROTECT(duplicate(R_dims));
  vars_protected++;
  R_type_class = PROTECT(duplicate(R_type_class));
  vars_protected++;
  R_type_size = PROTECT(duplicate(R_type_size));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t* dims;
  if(XLENGTH(R_dims) == 0) {
    dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dims, h5_datatype[DT_hsize_t], XLENGTH(R_dims)));
    dims= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  H5T_class_t* type_class;
  if(XLENGTH(R_type_class) == 0) {
    type_class = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_type_class, h5_datatype[DT_H5T_class_t], XLENGTH(R_type_class)));
    type_class= (H5T_class_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* type_size;
  if(XLENGTH(R_type_size) == 0) {
    type_size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_type_size, h5_datatype[DT_size_t], XLENGTH(R_type_size)));
    type_size= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_dataset_info(loc_id, dset_name, dims, type_class, type_size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_dims, h5_datatype[DT_hsize_t]);
  R_dims = PROTECT(H5ToR_single_step(dims, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_type_class, h5_datatype[DT_H5T_class_t]);
  R_type_class = PROTECT(H5ToR_single_step(type_class, h5_datatype[DT_H5T_class_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_type_size, h5_datatype[DT_size_t]);
  R_type_size = PROTECT(H5ToR_single_step(type_size, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 4));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_dims);
  SET_VECTOR_ELT(__ret_list, 2, R_type_class);
  SET_VECTOR_ELT(__ret_list, 3, R_type_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 4));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("dims"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("type_class"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("type_size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTget_dataset_ndims( hid_t loc_id, const char *dset_name, int *rank ); */
SEXP R_H5LTget_dataset_ndims(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_rank = PROTECT(duplicate(R_rank));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  int* rank;
  if(XLENGTH(R_rank) == 0) {
    rank = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_rank, h5_datatype[DT_int], XLENGTH(R_rank)));
    rank= (int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTget_dataset_ndims(loc_id, dset_name, rank);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_rank, h5_datatype[DT_int]);
  R_rank = PROTECT(H5ToR_single_step(rank, h5_datatype[DT_int], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_rank);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("rank"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTmake_dataset( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, hid_t type_id, const void *buffer ); */
SEXP R_H5LTmake_dataset(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_type_id, SEXP R_buffer){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  int rank = SEXP_to_longlong(R_rank, 0);
  const hsize_t* dims;
  if(XLENGTH(R_dims) == 0) {
    dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dims, h5_datatype[DT_hsize_t], XLENGTH(R_dims)));
    dims= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  const void* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    buffer = (void *) VOIDPTR(R_buffer);
  }
  herr_t return_val = H5LTmake_dataset(loc_id, dset_name, rank, dims, type_id, buffer);
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

/* H5_HLDLL herr_t H5LTmake_dataset_char( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const char *buffer ); */
SEXP R_H5LTmake_dataset_char(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  int rank = SEXP_to_longlong(R_rank, 0);
  const hsize_t* dims;
  if(XLENGTH(R_dims) == 0) {
    dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dims, h5_datatype[DT_hsize_t], XLENGTH(R_dims)));
    dims= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const char* buffer = CHAR(STRING_ELT(R_buffer, 0));
  herr_t return_val = H5LTmake_dataset_char(loc_id, dset_name, rank, dims, buffer);
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

/* H5_HLDLL herr_t H5LTmake_dataset_double( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const double *buffer ); */
SEXP R_H5LTmake_dataset_double(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  int rank = SEXP_to_longlong(R_rank, 0);
  const hsize_t* dims;
  if(XLENGTH(R_dims) == 0) {
    dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dims, h5_datatype[DT_hsize_t], XLENGTH(R_dims)));
    dims= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const double* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_double], XLENGTH(R_buffer)));
    buffer= (const double*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTmake_dataset_double(loc_id, dset_name, rank, dims, buffer);
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

/* H5_HLDLL herr_t H5LTmake_dataset_float( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const float *buffer ); */
SEXP R_H5LTmake_dataset_float(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  int rank = SEXP_to_longlong(R_rank, 0);
  const hsize_t* dims;
  if(XLENGTH(R_dims) == 0) {
    dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dims, h5_datatype[DT_hsize_t], XLENGTH(R_dims)));
    dims= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const float* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_float], XLENGTH(R_buffer)));
    buffer= (const float*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTmake_dataset_float(loc_id, dset_name, rank, dims, buffer);
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

/* H5_HLDLL herr_t H5LTmake_dataset_int( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const int *buffer ); */
SEXP R_H5LTmake_dataset_int(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  int rank = SEXP_to_longlong(R_rank, 0);
  const hsize_t* dims;
  if(XLENGTH(R_dims) == 0) {
    dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dims, h5_datatype[DT_hsize_t], XLENGTH(R_dims)));
    dims= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const int* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_int], XLENGTH(R_buffer)));
    buffer= (const int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTmake_dataset_int(loc_id, dset_name, rank, dims, buffer);
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

/* H5_HLDLL herr_t H5LTmake_dataset_long( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const long *buffer ); */
SEXP R_H5LTmake_dataset_long(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  int rank = SEXP_to_longlong(R_rank, 0);
  const hsize_t* dims;
  if(XLENGTH(R_dims) == 0) {
    dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dims, h5_datatype[DT_hsize_t], XLENGTH(R_dims)));
    dims= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const long* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_long], XLENGTH(R_buffer)));
    buffer= (const long*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTmake_dataset_long(loc_id, dset_name, rank, dims, buffer);
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

/* H5_HLDLL herr_t H5LTmake_dataset_short( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const short *buffer ); */
SEXP R_H5LTmake_dataset_short(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  int rank = SEXP_to_longlong(R_rank, 0);
  const hsize_t* dims;
  if(XLENGTH(R_dims) == 0) {
    dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dims, h5_datatype[DT_hsize_t], XLENGTH(R_dims)));
    dims= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const short* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_short], XLENGTH(R_buffer)));
    buffer= (const short*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTmake_dataset_short(loc_id, dset_name, rank, dims, buffer);
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

/* H5_HLDLL herr_t H5LTmake_dataset_string( hid_t loc_id, const char *dset_name, const char *buf ); */
SEXP R_H5LTmake_dataset_string(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buf){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  const char* buf = CHAR(STRING_ELT(R_buf, 0));
  herr_t return_val = H5LTmake_dataset_string(loc_id, dset_name, buf);
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

/* H5_HLDLL hid_t H5LTopen_file_image(void *buf_ptr, size_t buf_size, unsigned flags); */
SEXP R_H5LTopen_file_image(SEXP R_buf_ptr, SEXP R_buf_size, SEXP R_flags, SEXP _dupl_buf_ptr){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf_ptr)) {
    R_buf_ptr = PROTECT(duplicate(R_buf_ptr));
    vars_protected++;
  }
  void* buf_ptr;
  if(XLENGTH(R_buf_ptr) == 0) {
    buf_ptr = NULL;
  }
  else {
    buf_ptr = (void *) VOIDPTR(R_buf_ptr);
  }
  size_t buf_size = SEXP_to_longlong(R_buf_size, 0);
  unsigned flags = SEXP_to_longlong(R_flags, 0);
  hid_t return_val = H5LTopen_file_image(buf_ptr, buf_size, flags);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buf_ptr);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buf_ptr"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL htri_t H5LTpath_valid(hid_t loc_id, const char *path, hbool_t check_object_valid); */
SEXP R_H5LTpath_valid(SEXP R_loc_id, SEXP R_path, SEXP R_check_object_valid){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* path = CHAR(STRING_ELT(R_path, 0));
  hbool_t check_object_valid = SEXP_to_longlong(R_check_object_valid, 0);
  htri_t return_val = H5LTpath_valid(loc_id, path, check_object_valid);
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

/* H5_HLDLL herr_t H5LTread_dataset( hid_t loc_id, const char *dset_name, hid_t type_id, void *buffer ); */
SEXP R_H5LTread_dataset(SEXP R_loc_id, SEXP R_dset_name, SEXP R_type_id, SEXP R_buffer, SEXP _dupl_buffer){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buffer)) {
    R_buffer = PROTECT(duplicate(R_buffer));
    vars_protected++;
  }
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  void* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    buffer = (void *) VOIDPTR(R_buffer);
  }
  herr_t return_val = H5LTread_dataset(loc_id, dset_name, type_id, buffer);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buffer);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buffer"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTread_dataset_char( hid_t loc_id, const char *dset_name, char *buffer ); */
SEXP R_H5LTread_dataset_char(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer){
  int vars_protected=0;
  R_buffer = PROTECT(duplicate(R_buffer));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  char* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    buffer = R_alloc(strlen(CHAR(STRING_ELT(R_buffer, 0))) + 1, 1);
    strcpy(buffer, CHAR(STRING_ELT(R_buffer, 0)));
  }
  herr_t return_val = H5LTread_dataset_char(loc_id, dset_name, buffer);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(buffer==NULL) {
    R_buffer = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_buffer = PROTECT(mkString(buffer));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buffer);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buffer"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTread_dataset_double( hid_t loc_id, const char *dset_name, double *buffer ); */
SEXP R_H5LTread_dataset_double(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_buffer = PROTECT(duplicate(R_buffer));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  double* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_double], XLENGTH(R_buffer)));
    buffer= (double*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTread_dataset_double(loc_id, dset_name, buffer);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_buffer, h5_datatype[DT_double]);
  R_buffer = PROTECT(H5ToR_single_step(buffer, h5_datatype[DT_double], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buffer);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buffer"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTread_dataset_float( hid_t loc_id, const char *dset_name, float *buffer ); */
SEXP R_H5LTread_dataset_float(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_buffer = PROTECT(duplicate(R_buffer));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  float* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_float], XLENGTH(R_buffer)));
    buffer= (float*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTread_dataset_float(loc_id, dset_name, buffer);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_buffer, h5_datatype[DT_float]);
  R_buffer = PROTECT(H5ToR_single_step(buffer, h5_datatype[DT_float], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buffer);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buffer"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTread_dataset_int( hid_t loc_id, const char *dset_name, int *buffer ); */
SEXP R_H5LTread_dataset_int(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_buffer = PROTECT(duplicate(R_buffer));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  int* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_int], XLENGTH(R_buffer)));
    buffer= (int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTread_dataset_int(loc_id, dset_name, buffer);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_buffer, h5_datatype[DT_int]);
  R_buffer = PROTECT(H5ToR_single_step(buffer, h5_datatype[DT_int], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buffer);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buffer"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTread_dataset_long( hid_t loc_id, const char *dset_name, long *buffer ); */
SEXP R_H5LTread_dataset_long(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_buffer = PROTECT(duplicate(R_buffer));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  long* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_long], XLENGTH(R_buffer)));
    buffer= (long*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTread_dataset_long(loc_id, dset_name, buffer);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_buffer, h5_datatype[DT_long]);
  R_buffer = PROTECT(H5ToR_single_step(buffer, h5_datatype[DT_long], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buffer);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buffer"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTread_dataset_short( hid_t loc_id, const char *dset_name, short *buffer ); */
SEXP R_H5LTread_dataset_short(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_buffer = PROTECT(duplicate(R_buffer));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  short* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_short], XLENGTH(R_buffer)));
    buffer= (short*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5LTread_dataset_short(loc_id, dset_name, buffer);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_buffer, h5_datatype[DT_short]);
  R_buffer = PROTECT(H5ToR_single_step(buffer, h5_datatype[DT_short], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buffer);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buffer"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTread_dataset_string( hid_t loc_id, const char *dset_name, char *buf ); */
SEXP R_H5LTread_dataset_string(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buf){
  int vars_protected=0;
  R_buf = PROTECT(duplicate(R_buf));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  char* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = R_alloc(strlen(CHAR(STRING_ELT(R_buf, 0))) + 1, 1);
    strcpy(buf, CHAR(STRING_ELT(R_buf, 0)));
  }
  herr_t return_val = H5LTread_dataset_string(loc_id, dset_name, buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(buf==NULL) {
    R_buf = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_buf = PROTECT(mkString(buf));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buf);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buf"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5LTset_attribute_char( hid_t loc_id, const char *obj_name, const char *attr_name, const char *buffer, size_t size ); */
SEXP R_H5LTset_attribute_char(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const char* buffer = CHAR(STRING_ELT(R_buffer, 0));
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5LTset_attribute_char(loc_id, obj_name, attr_name, buffer, size);
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

/* H5_HLDLL herr_t H5LTset_attribute_double( hid_t loc_id, const char *obj_name, const char *attr_name, const double *buffer, size_t size ); */
SEXP R_H5LTset_attribute_double(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const double* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_double], XLENGTH(R_buffer)));
    buffer= (const double*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5LTset_attribute_double(loc_id, obj_name, attr_name, buffer, size);
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

/* H5_HLDLL herr_t H5LTset_attribute_float( hid_t loc_id, const char *obj_name, const char *attr_name, const float *buffer, size_t size ); */
SEXP R_H5LTset_attribute_float(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const float* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_float], XLENGTH(R_buffer)));
    buffer= (const float*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5LTset_attribute_float(loc_id, obj_name, attr_name, buffer, size);
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

/* H5_HLDLL herr_t H5LTset_attribute_int( hid_t loc_id, const char *obj_name, const char *attr_name, const int *buffer, size_t size ); */
SEXP R_H5LTset_attribute_int(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const int* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_int], XLENGTH(R_buffer)));
    buffer= (const int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5LTset_attribute_int(loc_id, obj_name, attr_name, buffer, size);
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

/* H5_HLDLL herr_t H5LTset_attribute_long( hid_t loc_id, const char *obj_name, const char *attr_name, const long *buffer, size_t size ); */
SEXP R_H5LTset_attribute_long(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const long* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_long], XLENGTH(R_buffer)));
    buffer= (const long*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5LTset_attribute_long(loc_id, obj_name, attr_name, buffer, size);
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

/* H5_HLDLL herr_t H5LTset_attribute_long_long( hid_t loc_id, const char *obj_name, const char *attr_name, const long long *buffer, size_t size ); */
SEXP R_H5LTset_attribute_long_long(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const long long* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_long_long], XLENGTH(R_buffer)));
    buffer= (const long long*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5LTset_attribute_long_long(loc_id, obj_name, attr_name, buffer, size);
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

/* H5_HLDLL herr_t H5LTset_attribute_short( hid_t loc_id, const char *obj_name, const char *attr_name, const short *buffer, size_t size ); */
SEXP R_H5LTset_attribute_short(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const short* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_short], XLENGTH(R_buffer)));
    buffer= (const short*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5LTset_attribute_short(loc_id, obj_name, attr_name, buffer, size);
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

/* H5_HLDLL herr_t H5LTset_attribute_string( hid_t loc_id, const char *obj_name, const char *attr_name, const char *attr_data ); */
SEXP R_H5LTset_attribute_string(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_attr_data){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const char* attr_data = CHAR(STRING_ELT(R_attr_data, 0));
  herr_t return_val = H5LTset_attribute_string(loc_id, obj_name, attr_name, attr_data);
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

/* H5_HLDLL herr_t H5LTset_attribute_uchar( hid_t loc_id, const char *obj_name, const char *attr_name, const unsigned char *buffer, size_t size ); */
SEXP R_H5LTset_attribute_uchar(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const unsigned char* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_unsigned_char], XLENGTH(R_buffer)));
    buffer= (const unsigned char*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5LTset_attribute_uchar(loc_id, obj_name, attr_name, buffer, size);
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

/* H5_HLDLL herr_t H5LTset_attribute_uint( hid_t loc_id, const char *obj_name, const char *attr_name, const unsigned int *buffer, size_t size ); */
SEXP R_H5LTset_attribute_uint(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const unsigned int* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_unsigned_int], XLENGTH(R_buffer)));
    buffer= (const unsigned int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5LTset_attribute_uint(loc_id, obj_name, attr_name, buffer, size);
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

/* H5_HLDLL herr_t H5LTset_attribute_ulong( hid_t loc_id, const char *obj_name, const char *attr_name, const unsigned long *buffer, size_t size ); */
SEXP R_H5LTset_attribute_ulong(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const unsigned long* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_unsigned_long], XLENGTH(R_buffer)));
    buffer= (const unsigned long*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5LTset_attribute_ulong(loc_id, obj_name, attr_name, buffer, size);
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

/* H5_HLDLL herr_t H5LTset_attribute_ushort( hid_t loc_id, const char *obj_name, const char *attr_name, const unsigned short *buffer, size_t size ); */
SEXP R_H5LTset_attribute_ushort(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  const unsigned short* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_unsigned_short], XLENGTH(R_buffer)));
    buffer= (const unsigned short*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5LTset_attribute_ushort(loc_id, obj_name, attr_name, buffer, size);
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

/* H5_HLDLL hid_t H5LTtext_to_dtype(const char *text, H5LT_lang_t lang_type); */
SEXP R_H5LTtext_to_dtype(SEXP R_text, SEXP R_lang_type){
  int vars_protected=0;
  const char* text = CHAR(STRING_ELT(R_text, 0));
  H5LT_lang_t lang_type = SEXP_to_longlong(R_lang_type, 0);
  hid_t return_val = H5LTtext_to_dtype(text, lang_type);
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



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

#include "Wrapper_auto_H5T.h"
/* H5_DLL hid_t H5Tarray_create2(hid_t base_id, unsigned ndims, const hsize_t dim[]); */
SEXP R_H5Tarray_create2(SEXP R_base_id, SEXP R_ndims, SEXP R_dim){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t base_id = SEXP_to_longlong(R_base_id, 0);
  unsigned ndims = SEXP_to_longlong(R_ndims, 0);
  const hsize_t* dim;
  if(XLENGTH(R_dim) == 0) {
    dim = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dim, h5_datatype[DT_hsize_t], XLENGTH(R_dim)));
    dim= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hid_t return_val = H5Tarray_create2(base_id, ndims, dim);
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

/* H5_DLL herr_t H5Tclose(hid_t type_id); */
SEXP R_H5Tclose(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  herr_t return_val = H5Tclose(type_id);
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

/* H5_DLL herr_t H5Tcommit_anon(hid_t loc_id, hid_t type_id, hid_t tcpl_id, hid_t tapl_id); */
SEXP R_H5Tcommit_anon(SEXP R_loc_id, SEXP R_type_id, SEXP R_tcpl_id, SEXP R_tapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  hid_t tcpl_id = SEXP_to_longlong(R_tcpl_id, 0);
  hid_t tapl_id = SEXP_to_longlong(R_tapl_id, 0);
  herr_t return_val = H5Tcommit_anon(loc_id, type_id, tcpl_id, tapl_id);
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

/* H5_DLL herr_t H5Tcommit2(hid_t loc_id, const char *name, hid_t type_id, hid_t lcpl_id, hid_t tcpl_id, hid_t tapl_id); */
SEXP R_H5Tcommit2(SEXP R_loc_id, SEXP R_name, SEXP R_type_id, SEXP R_lcpl_id, SEXP R_tcpl_id, SEXP R_tapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  hid_t lcpl_id = SEXP_to_longlong(R_lcpl_id, 0);
  hid_t tcpl_id = SEXP_to_longlong(R_tcpl_id, 0);
  hid_t tapl_id = SEXP_to_longlong(R_tapl_id, 0);
  herr_t return_val = H5Tcommit2(loc_id, name, type_id, lcpl_id, tcpl_id, tapl_id);
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

/* H5_DLL htri_t H5Tcommitted(hid_t type_id); */
SEXP R_H5Tcommitted(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  htri_t return_val = H5Tcommitted(type_id);
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

/* H5_DLL htri_t H5Tcompiler_conv(hid_t src_id, hid_t dst_id); */
SEXP R_H5Tcompiler_conv(SEXP R_src_id, SEXP R_dst_id){
  int vars_protected=0;
  hid_t src_id = SEXP_to_longlong(R_src_id, 0);
  hid_t dst_id = SEXP_to_longlong(R_dst_id, 0);
  htri_t return_val = H5Tcompiler_conv(src_id, dst_id);
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

/* H5_DLL herr_t H5Tconvert(hid_t src_id, hid_t dst_id, size_t nelmts, void *buf, void *background, hid_t plist_id); */
SEXP R_H5Tconvert(SEXP R_src_id, SEXP R_dst_id, SEXP R_nelmts, SEXP R_buf, SEXP R_background, SEXP R_plist_id, SEXP _dupl_buf, SEXP _dupl_background){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  if(SEXP_to_logical(_dupl_background)) {
    R_background = PROTECT(duplicate(R_background));
    vars_protected++;
  }
  hid_t src_id = SEXP_to_longlong(R_src_id, 0);
  hid_t dst_id = SEXP_to_longlong(R_dst_id, 0);
  size_t nelmts = SEXP_to_longlong(R_nelmts, 0);
  void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  void* background;
  if(XLENGTH(R_background) == 0) {
    background = NULL;
  }
  else {
    background = (void *) VOIDPTR(R_background);
  }
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  herr_t return_val = H5Tconvert(src_id, dst_id, nelmts, buf, background, plist_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buf);
  SET_VECTOR_ELT(__ret_list, 2, R_background);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buf"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("background"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Tcopy(hid_t type_id); */
SEXP R_H5Tcopy(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  hid_t return_val = H5Tcopy(type_id);
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

/* H5_DLL hid_t H5Tcreate(H5T_class_t type, size_t size); */
SEXP R_H5Tcreate(SEXP R_type, SEXP R_size){
  int vars_protected=0;
  H5T_class_t type = SEXP_to_longlong(R_type, 0);
  size_t size = SEXP_to_longlong(R_size, 0);
  hid_t return_val = H5Tcreate(type, size);
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

/* H5_DLL hid_t H5Tdecode(const void *buf); */
SEXP R_H5Tdecode(SEXP R_buf){
  int vars_protected=0;
  const void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  hid_t return_val = H5Tdecode(buf);
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

/* H5_DLL htri_t H5Tdetect_class(hid_t type_id, H5T_class_t cls); */
SEXP R_H5Tdetect_class(SEXP R_type_id, SEXP R_cls){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_class_t cls = SEXP_to_longlong(R_cls, 0);
  htri_t return_val = H5Tdetect_class(type_id, cls);
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

/* H5_DLL herr_t H5Tencode(hid_t obj_id, void *buf, size_t *nalloc); */
SEXP R_H5Tencode(SEXP R_obj_id, SEXP R_buf, SEXP R_nalloc, SEXP _dupl_buf){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  R_nalloc = PROTECT(duplicate(R_nalloc));
  vars_protected++;
  hid_t obj_id = SEXP_to_longlong(R_obj_id, 0);
  void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  size_t* nalloc;
  if(XLENGTH(R_nalloc) == 0) {
    nalloc = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_nalloc, h5_datatype[DT_size_t], XLENGTH(R_nalloc)));
    nalloc= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Tencode(obj_id, buf, nalloc);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_nalloc, h5_datatype[DT_size_t]);
  R_nalloc = PROTECT(H5ToR_single_step(nalloc, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buf);
  SET_VECTOR_ELT(__ret_list, 2, R_nalloc);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buf"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("nalloc"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Tenum_create(hid_t base_id); */
SEXP R_H5Tenum_create(SEXP R_base_id){
  int vars_protected=0;
  hid_t base_id = SEXP_to_longlong(R_base_id, 0);
  hid_t return_val = H5Tenum_create(base_id);
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

/* H5_DLL herr_t H5Tenum_insert(hid_t type, const char *name, const void *value); */
SEXP R_H5Tenum_insert(SEXP R_type, SEXP R_name, SEXP R_value){
  int vars_protected=0;
  hid_t type = SEXP_to_longlong(R_type, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  const void* value;
  if(XLENGTH(R_value) == 0) {
    value = NULL;
  }
  else {
    value = (void *) VOIDPTR(R_value);
  }
  herr_t return_val = H5Tenum_insert(type, name, value);
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

/* H5_DLL herr_t H5Tenum_nameof(hid_t type, const void *value, char *name, size_t size); */
SEXP R_H5Tenum_nameof(SEXP R_type, SEXP R_value, SEXP R_name, SEXP R_size){
  int vars_protected=0;
  R_name = PROTECT(duplicate(R_name));
  vars_protected++;
  hid_t type = SEXP_to_longlong(R_type, 0);
  const void* value;
  if(XLENGTH(R_value) == 0) {
    value = NULL;
  }
  else {
    value = (void *) VOIDPTR(R_value);
  }
  char* name;
  if(XLENGTH(R_name) == 0) {
    name = NULL;
  }
  else {
    name = R_alloc(strlen(CHAR(STRING_ELT(R_name, 0))) + 1, 1);
    strcpy(name, CHAR(STRING_ELT(R_name, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5Tenum_nameof(type, value, name, size);
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

/* H5_DLL herr_t H5Tenum_valueof(hid_t type, const char *name, void *value); */
SEXP R_H5Tenum_valueof(SEXP R_type, SEXP R_name, SEXP R_value, SEXP _dupl_value){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_value)) {
    R_value = PROTECT(duplicate(R_value));
    vars_protected++;
  }
  hid_t type = SEXP_to_longlong(R_type, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  void* value;
  if(XLENGTH(R_value) == 0) {
    value = NULL;
  }
  else {
    value = (void *) VOIDPTR(R_value);
  }
  herr_t return_val = H5Tenum_valueof(type, name, value);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_value);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("value"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL htri_t H5Tequal(hid_t type1_id, hid_t type2_id); */
SEXP R_H5Tequal(SEXP R_type1_id, SEXP R_type2_id){
  int vars_protected=0;
  hid_t type1_id = SEXP_to_longlong(R_type1_id, 0);
  hid_t type2_id = SEXP_to_longlong(R_type2_id, 0);
  htri_t return_val = H5Tequal(type1_id, type2_id);
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

/* H5_DLL herr_t H5Tflush(hid_t type_id); */
SEXP R_H5Tflush(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  herr_t return_val = H5Tflush(type_id);
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

/* H5_DLL int H5Tget_array_dims2(hid_t type_id, hsize_t dims[]); */
SEXP R_H5Tget_array_dims2(SEXP R_type_id, SEXP R_dims){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_dims = PROTECT(duplicate(R_dims));
  vars_protected++;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  hsize_t* dims;
  if(XLENGTH(R_dims) == 0) {
    dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dims, h5_datatype[DT_hsize_t], XLENGTH(R_dims)));
    dims= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  int return_val = H5Tget_array_dims2(type_id, dims);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_dims, h5_datatype[DT_hsize_t]);
  R_dims = PROTECT(H5ToR_single_step(dims, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_dims);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("dims"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL int H5Tget_array_ndims(hid_t type_id); */
SEXP R_H5Tget_array_ndims(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  int return_val = H5Tget_array_ndims(type_id);
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

/* H5_DLL H5T_class_t H5Tget_class(hid_t type_id); */
SEXP R_H5Tget_class(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_class_t return_val = H5Tget_class(type_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5T_class_t]));
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

/* H5_DLL hid_t H5Tget_create_plist(hid_t type_id); */
SEXP R_H5Tget_create_plist(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  hid_t return_val = H5Tget_create_plist(type_id);
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

/* H5_DLL H5T_cset_t H5Tget_cset(hid_t type_id); */
SEXP R_H5Tget_cset(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_cset_t return_val = H5Tget_cset(type_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5T_cset_t]));
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

/* H5_DLL size_t H5Tget_ebias(hid_t type_id); */
SEXP R_H5Tget_ebias(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  size_t return_val = H5Tget_ebias(type_id);
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

/* H5_DLL herr_t H5Tget_fields(hid_t type_id, size_t *spos, size_t *epos, size_t *esize, size_t *mpos, size_t *msize); */
SEXP R_H5Tget_fields(SEXP R_type_id, SEXP R_spos, SEXP R_epos, SEXP R_esize, SEXP R_mpos, SEXP R_msize){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_spos = PROTECT(duplicate(R_spos));
  vars_protected++;
  R_epos = PROTECT(duplicate(R_epos));
  vars_protected++;
  R_esize = PROTECT(duplicate(R_esize));
  vars_protected++;
  R_mpos = PROTECT(duplicate(R_mpos));
  vars_protected++;
  R_msize = PROTECT(duplicate(R_msize));
  vars_protected++;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  size_t* spos;
  if(XLENGTH(R_spos) == 0) {
    spos = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_spos, h5_datatype[DT_size_t], XLENGTH(R_spos)));
    spos= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* epos;
  if(XLENGTH(R_epos) == 0) {
    epos = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_epos, h5_datatype[DT_size_t], XLENGTH(R_epos)));
    epos= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* esize;
  if(XLENGTH(R_esize) == 0) {
    esize = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_esize, h5_datatype[DT_size_t], XLENGTH(R_esize)));
    esize= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* mpos;
  if(XLENGTH(R_mpos) == 0) {
    mpos = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_mpos, h5_datatype[DT_size_t], XLENGTH(R_mpos)));
    mpos= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* msize;
  if(XLENGTH(R_msize) == 0) {
    msize = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_msize, h5_datatype[DT_size_t], XLENGTH(R_msize)));
    msize= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Tget_fields(type_id, spos, epos, esize, mpos, msize);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_spos, h5_datatype[DT_size_t]);
  R_spos = PROTECT(H5ToR_single_step(spos, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_epos, h5_datatype[DT_size_t]);
  R_epos = PROTECT(H5ToR_single_step(epos, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_esize, h5_datatype[DT_size_t]);
  R_esize = PROTECT(H5ToR_single_step(esize, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_mpos, h5_datatype[DT_size_t]);
  R_mpos = PROTECT(H5ToR_single_step(mpos, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_msize, h5_datatype[DT_size_t]);
  R_msize = PROTECT(H5ToR_single_step(msize, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 6));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_spos);
  SET_VECTOR_ELT(__ret_list, 2, R_epos);
  SET_VECTOR_ELT(__ret_list, 3, R_esize);
  SET_VECTOR_ELT(__ret_list, 4, R_mpos);
  SET_VECTOR_ELT(__ret_list, 5, R_msize);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 6));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("spos"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("epos"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("esize"));
  SET_STRING_ELT(__ret_list_names, 4, mkChar("mpos"));
  SET_STRING_ELT(__ret_list_names, 5, mkChar("msize"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL H5T_pad_t H5Tget_inpad(hid_t type_id); */
SEXP R_H5Tget_inpad(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_pad_t return_val = H5Tget_inpad(type_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5T_pad_t]));
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

/* H5_DLL H5T_class_t H5Tget_member_class(hid_t type_id, unsigned membno); */
SEXP R_H5Tget_member_class(SEXP R_type_id, SEXP R_membno){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  unsigned membno = SEXP_to_longlong(R_membno, 0);
  H5T_class_t return_val = H5Tget_member_class(type_id, membno);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5T_class_t]));
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

/* H5_DLL int H5Tget_member_index(hid_t type_id, const char *name); */
SEXP R_H5Tget_member_index(SEXP R_type_id, SEXP R_name){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  int return_val = H5Tget_member_index(type_id, name);
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

/* H5_DLL char *H5Tget_member_name(hid_t type_id, unsigned membno); */
SEXP R_H5Tget_member_name(SEXP R_type_id, SEXP R_membno){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  unsigned membno = SEXP_to_longlong(R_membno, 0);
  char* return_val = H5Tget_member_name(type_id, membno);
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

/* H5_DLL size_t H5Tget_member_offset(hid_t type_id, unsigned membno); */
SEXP R_H5Tget_member_offset(SEXP R_type_id, SEXP R_membno){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  unsigned membno = SEXP_to_longlong(R_membno, 0);
  size_t return_val = H5Tget_member_offset(type_id, membno);
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

/* H5_DLL hid_t H5Tget_member_type(hid_t type_id, unsigned membno); */
SEXP R_H5Tget_member_type(SEXP R_type_id, SEXP R_membno){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  unsigned membno = SEXP_to_longlong(R_membno, 0);
  hid_t return_val = H5Tget_member_type(type_id, membno);
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

/* H5_DLL herr_t H5Tget_member_value(hid_t type_id, unsigned membno, void *value); */
SEXP R_H5Tget_member_value(SEXP R_type_id, SEXP R_membno, SEXP R_value, SEXP _dupl_value){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_value)) {
    R_value = PROTECT(duplicate(R_value));
    vars_protected++;
  }
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  unsigned membno = SEXP_to_longlong(R_membno, 0);
  void* value;
  if(XLENGTH(R_value) == 0) {
    value = NULL;
  }
  else {
    value = (void *) VOIDPTR(R_value);
  }
  herr_t return_val = H5Tget_member_value(type_id, membno, value);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_value);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("value"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Tget_native_type(hid_t type_id, H5T_direction_t direction); */
SEXP R_H5Tget_native_type(SEXP R_type_id, SEXP R_direction){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_direction_t direction = SEXP_to_longlong(R_direction, 0);
  hid_t return_val = H5Tget_native_type(type_id, direction);
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

/* H5_DLL int H5Tget_nmembers(hid_t type_id); */
SEXP R_H5Tget_nmembers(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  int return_val = H5Tget_nmembers(type_id);
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

/* H5_DLL H5T_norm_t H5Tget_norm(hid_t type_id); */
SEXP R_H5Tget_norm(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_norm_t return_val = H5Tget_norm(type_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5T_norm_t]));
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

/* H5_DLL int H5Tget_offset(hid_t type_id); */
SEXP R_H5Tget_offset(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  int return_val = H5Tget_offset(type_id);
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

/* H5_DLL H5T_order_t H5Tget_order(hid_t type_id); */
SEXP R_H5Tget_order(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_order_t return_val = H5Tget_order(type_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5T_order_t]));
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

/* H5_DLL herr_t H5Tget_pad(hid_t type_id, H5T_pad_t *lsb, H5T_pad_t *msb); */
SEXP R_H5Tget_pad(SEXP R_type_id, SEXP R_lsb, SEXP R_msb){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_lsb = PROTECT(duplicate(R_lsb));
  vars_protected++;
  R_msb = PROTECT(duplicate(R_msb));
  vars_protected++;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_pad_t* lsb;
  if(XLENGTH(R_lsb) == 0) {
    lsb = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_lsb, h5_datatype[DT_H5T_pad_t], XLENGTH(R_lsb)));
    lsb= (H5T_pad_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  H5T_pad_t* msb;
  if(XLENGTH(R_msb) == 0) {
    msb = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_msb, h5_datatype[DT_H5T_pad_t], XLENGTH(R_msb)));
    msb= (H5T_pad_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Tget_pad(type_id, lsb, msb);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_lsb, h5_datatype[DT_H5T_pad_t]);
  R_lsb = PROTECT(H5ToR_single_step(lsb, h5_datatype[DT_H5T_pad_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_msb, h5_datatype[DT_H5T_pad_t]);
  R_msb = PROTECT(H5ToR_single_step(msb, h5_datatype[DT_H5T_pad_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_lsb);
  SET_VECTOR_ELT(__ret_list, 2, R_msb);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("lsb"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("msb"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL size_t H5Tget_precision(hid_t type_id); */
SEXP R_H5Tget_precision(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  size_t return_val = H5Tget_precision(type_id);
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

/* H5_DLL H5T_sign_t H5Tget_sign(hid_t type_id); */
SEXP R_H5Tget_sign(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_sign_t return_val = H5Tget_sign(type_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5T_sign_t]));
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

/* H5_DLL size_t H5Tget_size(hid_t type_id); */
SEXP R_H5Tget_size(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  size_t return_val = H5Tget_size(type_id);
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

/* H5_DLL H5T_str_t H5Tget_strpad(hid_t type_id); */
SEXP R_H5Tget_strpad(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_str_t return_val = H5Tget_strpad(type_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5T_str_t]));
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

/* H5_DLL hid_t H5Tget_super(hid_t type); */
SEXP R_H5Tget_super(SEXP R_type){
  int vars_protected=0;
  hid_t type = SEXP_to_longlong(R_type, 0);
  hid_t return_val = H5Tget_super(type);
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

/* H5_DLL char *H5Tget_tag(hid_t type); */
SEXP R_H5Tget_tag(SEXP R_type){
  int vars_protected=0;
  hid_t type = SEXP_to_longlong(R_type, 0);
  char* return_val = H5Tget_tag(type);
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

/* H5_DLL herr_t H5Tinsert(hid_t parent_id, const char *name, size_t offset, hid_t member_id); */
SEXP R_H5Tinsert(SEXP R_parent_id, SEXP R_name, SEXP R_offset, SEXP R_member_id){
  int vars_protected=0;
  hid_t parent_id = SEXP_to_longlong(R_parent_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  size_t offset = SEXP_to_longlong(R_offset, 0);
  hid_t member_id = SEXP_to_longlong(R_member_id, 0);
  herr_t return_val = H5Tinsert(parent_id, name, offset, member_id);
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

/* H5_DLL htri_t H5Tis_variable_str(hid_t type_id); */
SEXP R_H5Tis_variable_str(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  htri_t return_val = H5Tis_variable_str(type_id);
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

/* H5_DLL herr_t H5Tlock(hid_t type_id); */
SEXP R_H5Tlock(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  herr_t return_val = H5Tlock(type_id);
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

/* H5_DLL hid_t H5Topen2(hid_t loc_id, const char *name, hid_t tapl_id); */
SEXP R_H5Topen2(SEXP R_loc_id, SEXP R_name, SEXP R_tapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  hid_t tapl_id = SEXP_to_longlong(R_tapl_id, 0);
  hid_t return_val = H5Topen2(loc_id, name, tapl_id);
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

/* H5_DLL herr_t H5Tpack(hid_t type_id); */
SEXP R_H5Tpack(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  herr_t return_val = H5Tpack(type_id);
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

/* H5_DLL herr_t H5Trefresh(hid_t type_id); */
SEXP R_H5Trefresh(SEXP R_type_id){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  herr_t return_val = H5Trefresh(type_id);
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

/* H5_DLL herr_t H5Tset_cset(hid_t type_id, H5T_cset_t cset); */
SEXP R_H5Tset_cset(SEXP R_type_id, SEXP R_cset){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_cset_t cset = SEXP_to_longlong(R_cset, 0);
  herr_t return_val = H5Tset_cset(type_id, cset);
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

/* H5_DLL herr_t H5Tset_ebias(hid_t type_id, size_t ebias); */
SEXP R_H5Tset_ebias(SEXP R_type_id, SEXP R_ebias){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  size_t ebias = SEXP_to_longlong(R_ebias, 0);
  herr_t return_val = H5Tset_ebias(type_id, ebias);
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

/* H5_DLL herr_t H5Tset_fields(hid_t type_id, size_t spos, size_t epos, size_t esize, size_t mpos, size_t msize); */
SEXP R_H5Tset_fields(SEXP R_type_id, SEXP R_spos, SEXP R_epos, SEXP R_esize, SEXP R_mpos, SEXP R_msize){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  size_t spos = SEXP_to_longlong(R_spos, 0);
  size_t epos = SEXP_to_longlong(R_epos, 0);
  size_t esize = SEXP_to_longlong(R_esize, 0);
  size_t mpos = SEXP_to_longlong(R_mpos, 0);
  size_t msize = SEXP_to_longlong(R_msize, 0);
  herr_t return_val = H5Tset_fields(type_id, spos, epos, esize, mpos, msize);
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

/* H5_DLL herr_t H5Tset_inpad(hid_t type_id, H5T_pad_t pad); */
SEXP R_H5Tset_inpad(SEXP R_type_id, SEXP R_pad){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_pad_t pad = SEXP_to_longlong(R_pad, 0);
  herr_t return_val = H5Tset_inpad(type_id, pad);
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

/* H5_DLL herr_t H5Tset_norm(hid_t type_id, H5T_norm_t norm); */
SEXP R_H5Tset_norm(SEXP R_type_id, SEXP R_norm){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_norm_t norm = SEXP_to_longlong(R_norm, 0);
  herr_t return_val = H5Tset_norm(type_id, norm);
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

/* H5_DLL herr_t H5Tset_offset(hid_t type_id, size_t offset); */
SEXP R_H5Tset_offset(SEXP R_type_id, SEXP R_offset){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  size_t offset = SEXP_to_longlong(R_offset, 0);
  herr_t return_val = H5Tset_offset(type_id, offset);
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

/* H5_DLL herr_t H5Tset_order(hid_t type_id, H5T_order_t order); */
SEXP R_H5Tset_order(SEXP R_type_id, SEXP R_order){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_order_t order = SEXP_to_longlong(R_order, 0);
  herr_t return_val = H5Tset_order(type_id, order);
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

/* H5_DLL herr_t H5Tset_pad(hid_t type_id, H5T_pad_t lsb, H5T_pad_t msb); */
SEXP R_H5Tset_pad(SEXP R_type_id, SEXP R_lsb, SEXP R_msb){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_pad_t lsb = SEXP_to_longlong(R_lsb, 0);
  H5T_pad_t msb = SEXP_to_longlong(R_msb, 0);
  herr_t return_val = H5Tset_pad(type_id, lsb, msb);
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

/* H5_DLL herr_t H5Tset_precision(hid_t type_id, size_t prec); */
SEXP R_H5Tset_precision(SEXP R_type_id, SEXP R_prec){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  size_t prec = SEXP_to_longlong(R_prec, 0);
  herr_t return_val = H5Tset_precision(type_id, prec);
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

/* H5_DLL herr_t H5Tset_sign(hid_t type_id, H5T_sign_t sign); */
SEXP R_H5Tset_sign(SEXP R_type_id, SEXP R_sign){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_sign_t sign = SEXP_to_longlong(R_sign, 0);
  herr_t return_val = H5Tset_sign(type_id, sign);
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

/* H5_DLL herr_t H5Tset_size(hid_t type_id, size_t size); */
SEXP R_H5Tset_size(SEXP R_type_id, SEXP R_size){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  size_t size = SEXP_to_longlong(R_size, 0);
  // INJECTION CODE START
  if(isReal(R_size ) && REAL(R_size)[0] == R_PosInf) {
    size = H5T_VARIABLE;
  }
  // INJECTION CODE END
  herr_t return_val = H5Tset_size(type_id, size);
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

/* H5_DLL herr_t H5Tset_strpad(hid_t type_id, H5T_str_t strpad); */
SEXP R_H5Tset_strpad(SEXP R_type_id, SEXP R_strpad){
  int vars_protected=0;
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  H5T_str_t strpad = SEXP_to_longlong(R_strpad, 0);
  herr_t return_val = H5Tset_strpad(type_id, strpad);
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

/* H5_DLL herr_t H5Tset_tag(hid_t type, const char *tag); */
SEXP R_H5Tset_tag(SEXP R_type, SEXP R_tag){
  int vars_protected=0;
  hid_t type = SEXP_to_longlong(R_type, 0);
  const char* tag = CHAR(STRING_ELT(R_tag, 0));
  herr_t return_val = H5Tset_tag(type, tag);
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

/* H5_DLL hid_t H5Tvlen_create(hid_t base_id); */
SEXP R_H5Tvlen_create(SEXP R_base_id){
  int vars_protected=0;
  hid_t base_id = SEXP_to_longlong(R_base_id, 0);
  hid_t return_val = H5Tvlen_create(base_id);
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


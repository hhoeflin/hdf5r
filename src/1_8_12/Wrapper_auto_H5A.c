
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

#include "Wrapper_auto_H5A.h"
/* H5_DLL herr_t H5Aclose(hid_t attr_id); */
SEXP R_H5Aclose(SEXP R_attr_id){
  int vars_protected=0;
  hid_t attr_id = SEXP_to_longlong(R_attr_id, 0);
  herr_t return_val = H5Aclose(attr_id);
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

/* H5_DLL hid_t H5Acreate_by_name(hid_t loc_id, const char *obj_name, const char *attr_name, hid_t type_id, hid_t space_id, hid_t acpl_id, hid_t aapl_id, hid_t lapl_id); */
SEXP R_H5Acreate_by_name(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_type_id, SEXP R_space_id, SEXP R_acpl_id, SEXP R_aapl_id, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  hid_t acpl_id = SEXP_to_longlong(R_acpl_id, 0);
  hid_t aapl_id = SEXP_to_longlong(R_aapl_id, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  hid_t return_val = H5Acreate_by_name(loc_id, obj_name, attr_name, type_id, space_id, acpl_id, aapl_id, lapl_id);
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

/* H5_DLL hid_t H5Acreate2(hid_t loc_id, const char *attr_name, hid_t type_id, hid_t space_id, hid_t acpl_id, hid_t aapl_id); */
SEXP R_H5Acreate2(SEXP R_loc_id, SEXP R_attr_name, SEXP R_type_id, SEXP R_space_id, SEXP R_acpl_id, SEXP R_aapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  hid_t acpl_id = SEXP_to_longlong(R_acpl_id, 0);
  hid_t aapl_id = SEXP_to_longlong(R_aapl_id, 0);
  hid_t return_val = H5Acreate2(loc_id, attr_name, type_id, space_id, acpl_id, aapl_id);
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

/* H5_DLL herr_t H5Adelete(hid_t loc_id, const char *name); */
SEXP R_H5Adelete(SEXP R_loc_id, SEXP R_name){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  herr_t return_val = H5Adelete(loc_id, name);
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

/* H5_DLL herr_t H5Adelete_by_idx(hid_t loc_id, const char *obj_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, hid_t lapl_id); */
SEXP R_H5Adelete_by_idx(SEXP R_loc_id, SEXP R_obj_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Adelete_by_idx(loc_id, obj_name, idx_type, order, n, lapl_id);
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

/* H5_DLL herr_t H5Adelete_by_name(hid_t loc_id, const char *obj_name, const char *attr_name, hid_t lapl_id); */
SEXP R_H5Adelete_by_name(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Adelete_by_name(loc_id, obj_name, attr_name, lapl_id);
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

/* H5_DLL htri_t H5Aexists(hid_t obj_id, const char *attr_name); */
SEXP R_H5Aexists(SEXP R_obj_id, SEXP R_attr_name){
  int vars_protected=0;
  hid_t obj_id = SEXP_to_longlong(R_obj_id, 0);
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  htri_t return_val = H5Aexists(obj_id, attr_name);
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

/* H5_DLL htri_t H5Aexists_by_name(hid_t obj_id, const char *obj_name, const char *attr_name, hid_t lapl_id); */
SEXP R_H5Aexists_by_name(SEXP R_obj_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t obj_id = SEXP_to_longlong(R_obj_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  htri_t return_val = H5Aexists_by_name(obj_id, obj_name, attr_name, lapl_id);
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

/* H5_DLL hid_t H5Aget_create_plist(hid_t attr_id); */
SEXP R_H5Aget_create_plist(SEXP R_attr_id){
  int vars_protected=0;
  hid_t attr_id = SEXP_to_longlong(R_attr_id, 0);
  hid_t return_val = H5Aget_create_plist(attr_id);
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

/* H5_DLL herr_t H5Aget_info(hid_t attr_id, H5A_info_t *ainfo ); */
SEXP R_H5Aget_info(SEXP R_attr_id, SEXP R_ainfo){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_ainfo = PROTECT(duplicate(R_ainfo));
  vars_protected++;
  hid_t attr_id = SEXP_to_longlong(R_attr_id, 0);
  R_helper = PROTECT(RToH5(R_ainfo, h5_datatype[DT_H5A_info_t], guess_nelem(R_ainfo, h5_datatype[DT_H5A_info_t])));
  H5A_info_t* ainfo= (H5A_info_t*) VOIDPTR(R_helper);
  vars_protected++;
  herr_t return_val = H5Aget_info(attr_id, ainfo);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_ainfo, h5_datatype[DT_H5A_info_t]);
  R_ainfo = PROTECT(H5ToR_single_step(ainfo, h5_datatype[DT_H5A_info_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_ainfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("ainfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Aget_info_by_idx(hid_t loc_id, const char *obj_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, H5A_info_t *ainfo , hid_t lapl_id); */
SEXP R_H5Aget_info_by_idx(SEXP R_loc_id, SEXP R_obj_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_ainfo, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_ainfo = PROTECT(duplicate(R_ainfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  R_helper = PROTECT(RToH5(R_ainfo, h5_datatype[DT_H5A_info_t], guess_nelem(R_ainfo, h5_datatype[DT_H5A_info_t])));
  H5A_info_t* ainfo= (H5A_info_t*) VOIDPTR(R_helper);
  vars_protected++;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Aget_info_by_idx(loc_id, obj_name, idx_type, order, n, ainfo, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_ainfo, h5_datatype[DT_H5A_info_t]);
  R_ainfo = PROTECT(H5ToR_single_step(ainfo, h5_datatype[DT_H5A_info_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_ainfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("ainfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Aget_info_by_name(hid_t loc_id, const char *obj_name, const char *attr_name, H5A_info_t *ainfo , hid_t lapl_id); */
SEXP R_H5Aget_info_by_name(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_ainfo, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_ainfo = PROTECT(duplicate(R_ainfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  R_helper = PROTECT(RToH5(R_ainfo, h5_datatype[DT_H5A_info_t], guess_nelem(R_ainfo, h5_datatype[DT_H5A_info_t])));
  H5A_info_t* ainfo= (H5A_info_t*) VOIDPTR(R_helper);
  vars_protected++;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Aget_info_by_name(loc_id, obj_name, attr_name, ainfo, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_ainfo, h5_datatype[DT_H5A_info_t]);
  R_ainfo = PROTECT(H5ToR_single_step(ainfo, h5_datatype[DT_H5A_info_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_ainfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("ainfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL ssize_t H5Aget_name(hid_t attr_id, size_t buf_size, char *buf); */
SEXP R_H5Aget_name(SEXP R_attr_id, SEXP R_buf_size, SEXP R_buf){
  int vars_protected=0;
  R_buf = PROTECT(duplicate(R_buf));
  vars_protected++;
  hid_t attr_id = SEXP_to_longlong(R_attr_id, 0);
  size_t buf_size = SEXP_to_longlong(R_buf_size, 0);
  char* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = R_alloc(strlen(CHAR(STRING_ELT(R_buf, 0))) + 1, 1);
    strcpy(buf, CHAR(STRING_ELT(R_buf, 0)));
  }
  ssize_t return_val = H5Aget_name(attr_id, buf_size, buf);
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

/* H5_DLL ssize_t H5Aget_name_by_idx(hid_t loc_id, const char *obj_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, char *name , size_t size, hid_t lapl_id); */
SEXP R_H5Aget_name_by_idx(SEXP R_loc_id, SEXP R_obj_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_name, SEXP R_size, SEXP R_lapl_id){
  int vars_protected=0;
  R_name = PROTECT(duplicate(R_name));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  char* name;
  if(XLENGTH(R_name) == 0) {
    name = NULL;
  }
  else {
    name = R_alloc(strlen(CHAR(STRING_ELT(R_name, 0))) + 1, 1);
    strcpy(name, CHAR(STRING_ELT(R_name, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  ssize_t return_val = H5Aget_name_by_idx(loc_id, obj_name, idx_type, order, n, name, size, lapl_id);
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

/* H5_DLL int H5Aget_num_attrs(hid_t loc_id); */
SEXP R_H5Aget_num_attrs(SEXP R_loc_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  int return_val = H5Aget_num_attrs(loc_id);
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

/* H5_DLL hid_t H5Aget_space(hid_t attr_id); */
SEXP R_H5Aget_space(SEXP R_attr_id){
  int vars_protected=0;
  hid_t attr_id = SEXP_to_longlong(R_attr_id, 0);
  hid_t return_val = H5Aget_space(attr_id);
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

/* H5_DLL hsize_t H5Aget_storage_size(hid_t attr_id); */
SEXP R_H5Aget_storage_size(SEXP R_attr_id){
  int vars_protected=0;
  hid_t attr_id = SEXP_to_longlong(R_attr_id, 0);
  hsize_t return_val = H5Aget_storage_size(attr_id);
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

/* H5_DLL hid_t H5Aget_type(hid_t attr_id); */
SEXP R_H5Aget_type(SEXP R_attr_id){
  int vars_protected=0;
  hid_t attr_id = SEXP_to_longlong(R_attr_id, 0);
  hid_t return_val = H5Aget_type(attr_id);
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

/* H5_DLL hid_t H5Aopen(hid_t obj_id, const char *attr_name, hid_t aapl_id); */
SEXP R_H5Aopen(SEXP R_obj_id, SEXP R_attr_name, SEXP R_aapl_id){
  int vars_protected=0;
  hid_t obj_id = SEXP_to_longlong(R_obj_id, 0);
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  hid_t aapl_id = SEXP_to_longlong(R_aapl_id, 0);
  hid_t return_val = H5Aopen(obj_id, attr_name, aapl_id);
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

/* H5_DLL hid_t H5Aopen_by_idx(hid_t loc_id, const char *obj_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, hid_t aapl_id, hid_t lapl_id); */
SEXP R_H5Aopen_by_idx(SEXP R_loc_id, SEXP R_obj_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_aapl_id, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  hid_t aapl_id = SEXP_to_longlong(R_aapl_id, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  hid_t return_val = H5Aopen_by_idx(loc_id, obj_name, idx_type, order, n, aapl_id, lapl_id);
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

/* H5_DLL hid_t H5Aopen_by_name(hid_t loc_id, const char *obj_name, const char *attr_name, hid_t aapl_id, hid_t lapl_id); */
SEXP R_H5Aopen_by_name(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_aapl_id, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* attr_name = CHAR(STRING_ELT(R_attr_name, 0));
  hid_t aapl_id = SEXP_to_longlong(R_aapl_id, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  hid_t return_val = H5Aopen_by_name(loc_id, obj_name, attr_name, aapl_id, lapl_id);
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

/* H5_DLL hid_t H5Aopen_idx(hid_t loc_id, unsigned idx); */
SEXP R_H5Aopen_idx(SEXP R_loc_id, SEXP R_idx){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  unsigned idx = SEXP_to_longlong(R_idx, 0);
  hid_t return_val = H5Aopen_idx(loc_id, idx);
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

/* H5_DLL hid_t H5Aopen_name(hid_t loc_id, const char *name); */
SEXP R_H5Aopen_name(SEXP R_loc_id, SEXP R_name){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  hid_t return_val = H5Aopen_name(loc_id, name);
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

/* H5_DLL herr_t H5Aread(hid_t attr_id, hid_t type_id, void *buf); */
SEXP R_H5Aread(SEXP R_attr_id, SEXP R_type_id, SEXP R_buf, SEXP _dupl_buf){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  hid_t attr_id = SEXP_to_longlong(R_attr_id, 0);
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  void* buf;
  if(TYPEOF(R_buf) == NILSXP) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5Aread(attr_id, type_id, buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
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

/* H5_DLL herr_t H5Arename(hid_t loc_id, const char *old_name, const char *new_name); */
SEXP R_H5Arename(SEXP R_loc_id, SEXP R_old_name, SEXP R_new_name){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* old_name = CHAR(STRING_ELT(R_old_name, 0));
  const char* new_name = CHAR(STRING_ELT(R_new_name, 0));
  herr_t return_val = H5Arename(loc_id, old_name, new_name);
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

/* H5_DLL herr_t H5Arename_by_name(hid_t loc_id, const char *obj_name, const char *old_attr_name, const char *new_attr_name, hid_t lapl_id); */
SEXP R_H5Arename_by_name(SEXP R_loc_id, SEXP R_obj_name, SEXP R_old_attr_name, SEXP R_new_attr_name, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  const char* old_attr_name = CHAR(STRING_ELT(R_old_attr_name, 0));
  const char* new_attr_name = CHAR(STRING_ELT(R_new_attr_name, 0));
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Arename_by_name(loc_id, obj_name, old_attr_name, new_attr_name, lapl_id);
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

/* H5_DLL herr_t H5Awrite(hid_t attr_id, hid_t type_id, const void *buf); */
SEXP R_H5Awrite(SEXP R_attr_id, SEXP R_type_id, SEXP R_buf){
  int vars_protected=0;
  hid_t attr_id = SEXP_to_longlong(R_attr_id, 0);
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  const void* buf;
  if(TYPEOF(R_buf) == NILSXP) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5Awrite(attr_id, type_id, buf);
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


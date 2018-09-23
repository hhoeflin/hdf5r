
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

#include "Wrapper_auto_H5L.h"
/* H5_DLL herr_t H5Lcopy(hid_t src_loc, const char *src_name, hid_t dst_loc, const char *dst_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lcopy(SEXP R_src_loc, SEXP R_src_name, SEXP R_dst_loc, SEXP R_dst_name, SEXP R_lcpl_id, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t src_loc = SEXP_to_longlong(R_src_loc, 0);
  const char* src_name = CHAR(STRING_ELT(R_src_name, 0));
  hid_t dst_loc = SEXP_to_longlong(R_dst_loc, 0);
  const char* dst_name = CHAR(STRING_ELT(R_dst_name, 0));
  hid_t lcpl_id = SEXP_to_longlong(R_lcpl_id, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Lcopy(src_loc, src_name, dst_loc, dst_name, lcpl_id, lapl_id);
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

/* H5_DLL herr_t H5Lcreate_external(const char *file_name, const char *obj_name, hid_t link_loc_id, const char *link_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lcreate_external(SEXP R_file_name, SEXP R_obj_name, SEXP R_link_loc_id, SEXP R_link_name, SEXP R_lcpl_id, SEXP R_lapl_id){
  int vars_protected=0;
  const char* file_name = CHAR(STRING_ELT(R_file_name, 0));
  const char* obj_name = CHAR(STRING_ELT(R_obj_name, 0));
  hid_t link_loc_id = SEXP_to_longlong(R_link_loc_id, 0);
  const char* link_name = CHAR(STRING_ELT(R_link_name, 0));
  hid_t lcpl_id = SEXP_to_longlong(R_lcpl_id, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Lcreate_external(file_name, obj_name, link_loc_id, link_name, lcpl_id, lapl_id);
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

/* H5_DLL herr_t H5Lcreate_hard(hid_t cur_loc, const char *cur_name, hid_t dst_loc, const char *dst_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lcreate_hard(SEXP R_cur_loc, SEXP R_cur_name, SEXP R_dst_loc, SEXP R_dst_name, SEXP R_lcpl_id, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t cur_loc = SEXP_to_longlong(R_cur_loc, 0);
  const char* cur_name = CHAR(STRING_ELT(R_cur_name, 0));
  hid_t dst_loc = SEXP_to_longlong(R_dst_loc, 0);
  const char* dst_name = CHAR(STRING_ELT(R_dst_name, 0));
  hid_t lcpl_id = SEXP_to_longlong(R_lcpl_id, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Lcreate_hard(cur_loc, cur_name, dst_loc, dst_name, lcpl_id, lapl_id);
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

/* H5_DLL herr_t H5Lcreate_soft(const char *link_target, hid_t link_loc_id, const char *link_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lcreate_soft(SEXP R_link_target, SEXP R_link_loc_id, SEXP R_link_name, SEXP R_lcpl_id, SEXP R_lapl_id){
  int vars_protected=0;
  const char* link_target = CHAR(STRING_ELT(R_link_target, 0));
  hid_t link_loc_id = SEXP_to_longlong(R_link_loc_id, 0);
  const char* link_name = CHAR(STRING_ELT(R_link_name, 0));
  hid_t lcpl_id = SEXP_to_longlong(R_lcpl_id, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Lcreate_soft(link_target, link_loc_id, link_name, lcpl_id, lapl_id);
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

/* H5_DLL herr_t H5Lcreate_ud(hid_t link_loc_id, const char *link_name, H5L_type_t link_type, const void *udata, size_t udata_size, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lcreate_ud(SEXP R_link_loc_id, SEXP R_link_name, SEXP R_link_type, SEXP R_udata, SEXP R_udata_size, SEXP R_lcpl_id, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t link_loc_id = SEXP_to_longlong(R_link_loc_id, 0);
  const char* link_name = CHAR(STRING_ELT(R_link_name, 0));
  H5L_type_t link_type = SEXP_to_longlong(R_link_type, 0);
  const void* udata;
  if(XLENGTH(R_udata) == 0) {
    udata = NULL;
  }
  else {
    udata = (void *) VOIDPTR(R_udata);
  }
  size_t udata_size = SEXP_to_longlong(R_udata_size, 0);
  hid_t lcpl_id = SEXP_to_longlong(R_lcpl_id, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Lcreate_ud(link_loc_id, link_name, link_type, udata, udata_size, lcpl_id, lapl_id);
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

/* H5_DLL herr_t H5Ldelete(hid_t loc_id, const char *name, hid_t lapl_id); */
SEXP R_H5Ldelete(SEXP R_loc_id, SEXP R_name, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Ldelete(loc_id, name, lapl_id);
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

/* H5_DLL herr_t H5Ldelete_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, hid_t lapl_id); */
SEXP R_H5Ldelete_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* group_name = CHAR(STRING_ELT(R_group_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Ldelete_by_idx(loc_id, group_name, idx_type, order, n, lapl_id);
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

/* H5_DLL htri_t H5Lexists(hid_t loc_id, const char *name, hid_t lapl_id); */
SEXP R_H5Lexists(SEXP R_loc_id, SEXP R_name, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  htri_t return_val = H5Lexists(loc_id, name, lapl_id);
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

/* H5_DLL herr_t H5Lget_info(hid_t loc_id, const char *name, H5L_info_t *linfo , hid_t lapl_id); */
SEXP R_H5Lget_info(SEXP R_loc_id, SEXP R_name, SEXP R_linfo, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_linfo = PROTECT(duplicate(R_linfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  R_helper = PROTECT(RToH5(R_linfo, h5_datatype[DT_H5L_info_t], guess_nelem(R_linfo, h5_datatype[DT_H5L_info_t])));
  H5L_info_t* linfo= (H5L_info_t*) VOIDPTR(R_helper);
  vars_protected++;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Lget_info(loc_id, name, linfo, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_linfo, h5_datatype[DT_H5L_info_t]);
  R_linfo = PROTECT(H5ToR_single_step(linfo, h5_datatype[DT_H5L_info_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_linfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("linfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Lget_info_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, H5L_info_t *linfo , hid_t lapl_id); */
SEXP R_H5Lget_info_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_linfo, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_linfo = PROTECT(duplicate(R_linfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* group_name = CHAR(STRING_ELT(R_group_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  R_helper = PROTECT(RToH5(R_linfo, h5_datatype[DT_H5L_info_t], guess_nelem(R_linfo, h5_datatype[DT_H5L_info_t])));
  H5L_info_t* linfo= (H5L_info_t*) VOIDPTR(R_helper);
  vars_protected++;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Lget_info_by_idx(loc_id, group_name, idx_type, order, n, linfo, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_linfo, h5_datatype[DT_H5L_info_t]);
  R_linfo = PROTECT(H5ToR_single_step(linfo, h5_datatype[DT_H5L_info_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_linfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("linfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL ssize_t H5Lget_name_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, char *name , size_t size, hid_t lapl_id); */
SEXP R_H5Lget_name_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_name, SEXP R_size, SEXP R_lapl_id){
  int vars_protected=0;
  R_name = PROTECT(duplicate(R_name));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* group_name = CHAR(STRING_ELT(R_group_name, 0));
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
  ssize_t return_val = H5Lget_name_by_idx(loc_id, group_name, idx_type, order, n, name, size, lapl_id);
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

/* H5_DLL herr_t H5Lget_val(hid_t loc_id, const char *name, void *buf, size_t size, hid_t lapl_id); */
SEXP R_H5Lget_val(SEXP R_loc_id, SEXP R_name, SEXP R_buf, SEXP R_size, SEXP R_lapl_id, SEXP _dupl_buf){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Lget_val(loc_id, name, buf, size, lapl_id);
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

/* H5_DLL herr_t H5Lget_val_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, void *buf, size_t size, hid_t lapl_id); */
SEXP R_H5Lget_val_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_buf, SEXP R_size, SEXP R_lapl_id, SEXP _dupl_buf){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* group_name = CHAR(STRING_ELT(R_group_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Lget_val_by_idx(loc_id, group_name, idx_type, order, n, buf, size, lapl_id);
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

/* H5_DLL htri_t H5Lis_registered(H5L_type_t id); */
SEXP R_H5Lis_registered(SEXP R_id){
  int vars_protected=0;
  H5L_type_t id = SEXP_to_longlong(R_id, 0);
  htri_t return_val = H5Lis_registered(id);
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

/* H5_DLL herr_t H5Lmove(hid_t src_loc, const char *src_name, hid_t dst_loc, const char *dst_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lmove(SEXP R_src_loc, SEXP R_src_name, SEXP R_dst_loc, SEXP R_dst_name, SEXP R_lcpl_id, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t src_loc = SEXP_to_longlong(R_src_loc, 0);
  const char* src_name = CHAR(STRING_ELT(R_src_name, 0));
  hid_t dst_loc = SEXP_to_longlong(R_dst_loc, 0);
  const char* dst_name = CHAR(STRING_ELT(R_dst_name, 0));
  hid_t lcpl_id = SEXP_to_longlong(R_lcpl_id, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Lmove(src_loc, src_name, dst_loc, dst_name, lcpl_id, lapl_id);
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

/* H5_DLL herr_t H5Lunpack_elink_val(const void *ext_linkval, size_t link_size, unsigned *flags, const char **filename, const char **obj_path ); */
SEXP R_H5Lunpack_elink_val(SEXP R_ext_linkval, SEXP R_link_size, SEXP R_flags, SEXP R_filename, SEXP R_obj_path){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_flags = PROTECT(duplicate(R_flags));
  vars_protected++;
  R_filename = PROTECT(duplicate(R_filename));
  vars_protected++;
  R_obj_path = PROTECT(duplicate(R_obj_path));
  vars_protected++;
  const void* ext_linkval;
  if(XLENGTH(R_ext_linkval) == 0) {
    ext_linkval = NULL;
  }
  else {
    ext_linkval = (void *) VOIDPTR(R_ext_linkval);
  }
  size_t link_size = SEXP_to_longlong(R_link_size, 0);
  unsigned* flags;
  if(XLENGTH(R_flags) == 0) {
    flags = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_flags, h5_datatype[DT_unsigned], XLENGTH(R_flags)));
    flags= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const char** filename;
  if(XLENGTH(R_filename) == 0) {
    filename = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_filename, h5_datatype[DT_char], XLENGTH(R_filename)));
    filename= (const char**) VOIDPTR(R_helper);
    vars_protected++;
  }
  const char** obj_path;
  if(XLENGTH(R_obj_path) == 0) {
    obj_path = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_obj_path, h5_datatype[DT_char], XLENGTH(R_obj_path)));
    obj_path= (const char**) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Lunpack_elink_val(ext_linkval, link_size, flags, filename, obj_path);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_flags, h5_datatype[DT_unsigned]);
  R_flags = PROTECT(H5ToR_single_step(flags, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_filename, h5_datatype[DT_char]);
  R_filename = PROTECT(H5ToR_single_step(filename, h5_datatype[DT_char], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_obj_path, h5_datatype[DT_char]);
  R_obj_path = PROTECT(H5ToR_single_step(obj_path, h5_datatype[DT_char], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 4));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_flags);
  SET_VECTOR_ELT(__ret_list, 2, R_filename);
  SET_VECTOR_ELT(__ret_list, 3, R_obj_path);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 4));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("flags"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("filename"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("obj_path"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Lunregister(H5L_type_t id); */
SEXP R_H5Lunregister(SEXP R_id){
  int vars_protected=0;
  H5L_type_t id = SEXP_to_longlong(R_id, 0);
  herr_t return_val = H5Lunregister(id);
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


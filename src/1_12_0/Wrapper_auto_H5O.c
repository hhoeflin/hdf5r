
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

#include "Wrapper_auto_H5O.h"
/* H5_DLL herr_t H5Oare_mdc_flushes_disabled(hid_t object_id, hbool_t *are_disabled); */
SEXP R_H5Oare_mdc_flushes_disabled(SEXP R_object_id, SEXP R_are_disabled){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_are_disabled = PROTECT(duplicate(R_are_disabled));
  vars_protected++;
  hid_t object_id = SEXP_to_longlong(R_object_id, 0);
  hbool_t* are_disabled;
  if(XLENGTH(R_are_disabled) == 0) {
    are_disabled = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_are_disabled, h5_datatype[DT_hbool_t], XLENGTH(R_are_disabled)));
    are_disabled= (hbool_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Oare_mdc_flushes_disabled(object_id, are_disabled);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_are_disabled, h5_datatype[DT_hbool_t]);
  R_are_disabled = PROTECT(H5ToR_single_step(are_disabled, h5_datatype[DT_hbool_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_are_disabled);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("are_disabled"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Oclose(hid_t object_id); */
SEXP R_H5Oclose(SEXP R_object_id){
  int vars_protected=0;
  hid_t object_id = SEXP_to_longlong(R_object_id, 0);
  herr_t return_val = H5Oclose(object_id);
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

/* H5_DLL herr_t H5Ocopy(hid_t src_loc_id, const char *src_name, hid_t dst_loc_id, const char *dst_name, hid_t ocpypl_id, hid_t lcpl_id); */
SEXP R_H5Ocopy(SEXP R_src_loc_id, SEXP R_src_name, SEXP R_dst_loc_id, SEXP R_dst_name, SEXP R_ocpypl_id, SEXP R_lcpl_id){
  int vars_protected=0;
  hid_t src_loc_id = SEXP_to_longlong(R_src_loc_id, 0);
  const char* src_name = CHAR(STRING_ELT(R_src_name, 0));
  hid_t dst_loc_id = SEXP_to_longlong(R_dst_loc_id, 0);
  const char* dst_name = CHAR(STRING_ELT(R_dst_name, 0));
  hid_t ocpypl_id = SEXP_to_longlong(R_ocpypl_id, 0);
  hid_t lcpl_id = SEXP_to_longlong(R_lcpl_id, 0);
  herr_t return_val = H5Ocopy(src_loc_id, src_name, dst_loc_id, dst_name, ocpypl_id, lcpl_id);
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

/* H5_DLL herr_t H5Odecr_refcount(hid_t object_id); */
SEXP R_H5Odecr_refcount(SEXP R_object_id){
  int vars_protected=0;
  hid_t object_id = SEXP_to_longlong(R_object_id, 0);
  herr_t return_val = H5Odecr_refcount(object_id);
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

/* H5_DLL herr_t H5Odisable_mdc_flushes(hid_t object_id); */
SEXP R_H5Odisable_mdc_flushes(SEXP R_object_id){
  int vars_protected=0;
  hid_t object_id = SEXP_to_longlong(R_object_id, 0);
  herr_t return_val = H5Odisable_mdc_flushes(object_id);
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

/* H5_DLL herr_t H5Oenable_mdc_flushes(hid_t object_id); */
SEXP R_H5Oenable_mdc_flushes(SEXP R_object_id){
  int vars_protected=0;
  hid_t object_id = SEXP_to_longlong(R_object_id, 0);
  herr_t return_val = H5Oenable_mdc_flushes(object_id);
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

/* H5_DLL htri_t H5Oexists_by_name(hid_t loc_id, const char *name, hid_t lapl_id); */
SEXP R_H5Oexists_by_name(SEXP R_loc_id, SEXP R_name, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  htri_t return_val = H5Oexists_by_name(loc_id, name, lapl_id);
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

/* H5_DLL herr_t H5Oflush(hid_t obj_id); */
SEXP R_H5Oflush(SEXP R_obj_id){
  int vars_protected=0;
  hid_t obj_id = SEXP_to_longlong(R_obj_id, 0);
  herr_t return_val = H5Oflush(obj_id);
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

/* H5_DLL ssize_t H5Oget_comment(hid_t obj_id, char *comment, size_t bufsize); */
SEXP R_H5Oget_comment(SEXP R_obj_id, SEXP R_comment, SEXP R_bufsize){
  int vars_protected=0;
  R_comment = PROTECT(duplicate(R_comment));
  vars_protected++;
  hid_t obj_id = SEXP_to_longlong(R_obj_id, 0);
  char* comment;
  if(XLENGTH(R_comment) == 0) {
    comment = NULL;
  }
  else {
    comment = R_alloc(strlen(CHAR(STRING_ELT(R_comment, 0))) + 1, 1);
    strcpy(comment, CHAR(STRING_ELT(R_comment, 0)));
  }
  size_t bufsize = SEXP_to_longlong(R_bufsize, 0);
  ssize_t return_val = H5Oget_comment(obj_id, comment, bufsize);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(comment==NULL) {
    R_comment = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_comment = PROTECT(mkString(comment));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_comment);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("comment"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL ssize_t H5Oget_comment_by_name(hid_t loc_id, const char *name, char *comment, size_t bufsize, hid_t lapl_id); */
SEXP R_H5Oget_comment_by_name(SEXP R_loc_id, SEXP R_name, SEXP R_comment, SEXP R_bufsize, SEXP R_lapl_id){
  int vars_protected=0;
  R_comment = PROTECT(duplicate(R_comment));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  char* comment;
  if(XLENGTH(R_comment) == 0) {
    comment = NULL;
  }
  else {
    comment = R_alloc(strlen(CHAR(STRING_ELT(R_comment, 0))) + 1, 1);
    strcpy(comment, CHAR(STRING_ELT(R_comment, 0)));
  }
  size_t bufsize = SEXP_to_longlong(R_bufsize, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  ssize_t return_val = H5Oget_comment_by_name(loc_id, name, comment, bufsize, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(comment==NULL) {
    R_comment = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_comment = PROTECT(mkString(comment));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_comment);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("comment"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Oget_info1(hid_t loc_id, H5O_info1_t *oinfo); */
SEXP R_H5Oget_info(SEXP R_loc_id, SEXP R_oinfo){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_oinfo = PROTECT(duplicate(R_oinfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  R_helper = PROTECT(RToH5(R_oinfo, h5_datatype[DT_H5O_info1_t], guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t])));
  H5O_info1_t* oinfo= (H5O_info1_t*) VOIDPTR(R_helper);
  vars_protected++;
  herr_t return_val = H5Oget_info(loc_id, oinfo);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t]);
  R_oinfo = PROTECT(H5ToR_single_step(oinfo, h5_datatype[DT_H5O_info1_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_oinfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("oinfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Oget_info_by_idx1(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, H5O_info1_t *oinfo, hid_t lapl_id); */
SEXP R_H5Oget_info_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_oinfo, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_oinfo = PROTECT(duplicate(R_oinfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* group_name = CHAR(STRING_ELT(R_group_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  R_helper = PROTECT(RToH5(R_oinfo, h5_datatype[DT_H5O_info1_t], guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t])));
  H5O_info1_t* oinfo= (H5O_info1_t*) VOIDPTR(R_helper);
  vars_protected++;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Oget_info_by_idx(loc_id, group_name, idx_type, order, n, oinfo, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t]);
  R_oinfo = PROTECT(H5ToR_single_step(oinfo, h5_datatype[DT_H5O_info1_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_oinfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("oinfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Oget_info_by_idx2(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, H5O_info1_t *oinfo, unsigned fields, hid_t lapl_id); */
SEXP R_H5Oget_info_by_idx2(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_oinfo, SEXP R_fields, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_oinfo = PROTECT(duplicate(R_oinfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* group_name = CHAR(STRING_ELT(R_group_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  R_helper = PROTECT(RToH5(R_oinfo, h5_datatype[DT_H5O_info1_t], guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t])));
  H5O_info1_t* oinfo= (H5O_info1_t*) VOIDPTR(R_helper);
  vars_protected++;
  unsigned fields = SEXP_to_longlong(R_fields, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Oget_info_by_idx2(loc_id, group_name, idx_type, order, n, oinfo, fields, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t]);
  R_oinfo = PROTECT(H5ToR_single_step(oinfo, h5_datatype[DT_H5O_info1_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_oinfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("oinfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Oget_info_by_name1(hid_t loc_id, const char *name, H5O_info1_t *oinfo, hid_t lapl_id); */
SEXP R_H5Oget_info_by_name(SEXP R_loc_id, SEXP R_name, SEXP R_oinfo, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_oinfo = PROTECT(duplicate(R_oinfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  R_helper = PROTECT(RToH5(R_oinfo, h5_datatype[DT_H5O_info1_t], guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t])));
  H5O_info1_t* oinfo= (H5O_info1_t*) VOIDPTR(R_helper);
  vars_protected++;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Oget_info_by_name(loc_id, name, oinfo, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t]);
  R_oinfo = PROTECT(H5ToR_single_step(oinfo, h5_datatype[DT_H5O_info1_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_oinfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("oinfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Oget_info_by_name2(hid_t loc_id, const char *name, H5O_info1_t *oinfo, unsigned fields, hid_t lapl_id); */
SEXP R_H5Oget_info_by_name2(SEXP R_loc_id, SEXP R_name, SEXP R_oinfo, SEXP R_fields, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_oinfo = PROTECT(duplicate(R_oinfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  R_helper = PROTECT(RToH5(R_oinfo, h5_datatype[DT_H5O_info1_t], guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t])));
  H5O_info1_t* oinfo= (H5O_info1_t*) VOIDPTR(R_helper);
  vars_protected++;
  unsigned fields = SEXP_to_longlong(R_fields, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Oget_info_by_name2(loc_id, name, oinfo, fields, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t]);
  R_oinfo = PROTECT(H5ToR_single_step(oinfo, h5_datatype[DT_H5O_info1_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_oinfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("oinfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Oget_info2(hid_t loc_id, H5O_info1_t *oinfo, unsigned fields); */
SEXP R_H5Oget_info2(SEXP R_loc_id, SEXP R_oinfo, SEXP R_fields){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_oinfo = PROTECT(duplicate(R_oinfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  R_helper = PROTECT(RToH5(R_oinfo, h5_datatype[DT_H5O_info1_t], guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t])));
  H5O_info1_t* oinfo= (H5O_info1_t*) VOIDPTR(R_helper);
  vars_protected++;
  unsigned fields = SEXP_to_longlong(R_fields, 0);
  herr_t return_val = H5Oget_info2(loc_id, oinfo, fields);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_oinfo, h5_datatype[DT_H5O_info1_t]);
  R_oinfo = PROTECT(H5ToR_single_step(oinfo, h5_datatype[DT_H5O_info1_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_oinfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("oinfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Oget_native_info(hid_t loc_id, H5O_native_info_t *oinfo, unsigned fields); */
SEXP R_H5Oget_native_info(SEXP R_loc_id, SEXP R_oinfo, SEXP R_fields){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_oinfo = PROTECT(duplicate(R_oinfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  R_helper = PROTECT(RToH5(R_oinfo, h5_datatype[DT_H5O_native_info_t], guess_nelem(R_oinfo, h5_datatype[DT_H5O_native_info_t])));
  H5O_native_info_t* oinfo= (H5O_native_info_t*) VOIDPTR(R_helper);
  vars_protected++;
  unsigned fields = SEXP_to_longlong(R_fields, 0);
  herr_t return_val = H5Oget_native_info(loc_id, oinfo, fields);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_oinfo, h5_datatype[DT_H5O_native_info_t]);
  R_oinfo = PROTECT(H5ToR_single_step(oinfo, h5_datatype[DT_H5O_native_info_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_oinfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("oinfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Oget_native_info_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, H5O_native_info_t *oinfo, unsigned fields, hid_t lapl_id); */
SEXP R_H5Oget_native_info_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_oinfo, SEXP R_fields, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_oinfo = PROTECT(duplicate(R_oinfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* group_name = CHAR(STRING_ELT(R_group_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  R_helper = PROTECT(RToH5(R_oinfo, h5_datatype[DT_H5O_native_info_t], guess_nelem(R_oinfo, h5_datatype[DT_H5O_native_info_t])));
  H5O_native_info_t* oinfo= (H5O_native_info_t*) VOIDPTR(R_helper);
  vars_protected++;
  unsigned fields = SEXP_to_longlong(R_fields, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Oget_native_info_by_idx(loc_id, group_name, idx_type, order, n, oinfo, fields, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_oinfo, h5_datatype[DT_H5O_native_info_t]);
  R_oinfo = PROTECT(H5ToR_single_step(oinfo, h5_datatype[DT_H5O_native_info_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_oinfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("oinfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Oget_native_info_by_name(hid_t loc_id, const char *name, H5O_native_info_t *oinfo, unsigned fields, hid_t lapl_id); */
SEXP R_H5Oget_native_info_by_name(SEXP R_loc_id, SEXP R_name, SEXP R_oinfo, SEXP R_fields, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_oinfo = PROTECT(duplicate(R_oinfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  R_helper = PROTECT(RToH5(R_oinfo, h5_datatype[DT_H5O_native_info_t], guess_nelem(R_oinfo, h5_datatype[DT_H5O_native_info_t])));
  H5O_native_info_t* oinfo= (H5O_native_info_t*) VOIDPTR(R_helper);
  vars_protected++;
  unsigned fields = SEXP_to_longlong(R_fields, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Oget_native_info_by_name(loc_id, name, oinfo, fields, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_oinfo, h5_datatype[DT_H5O_native_info_t]);
  R_oinfo = PROTECT(H5ToR_single_step(oinfo, h5_datatype[DT_H5O_native_info_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_oinfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("oinfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Oincr_refcount(hid_t object_id); */
SEXP R_H5Oincr_refcount(SEXP R_object_id){
  int vars_protected=0;
  hid_t object_id = SEXP_to_longlong(R_object_id, 0);
  herr_t return_val = H5Oincr_refcount(object_id);
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

/* H5_DLL herr_t H5Olink(hid_t obj_id, hid_t new_loc_id, const char *new_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Olink(SEXP R_obj_id, SEXP R_new_loc_id, SEXP R_new_name, SEXP R_lcpl_id, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t obj_id = SEXP_to_longlong(R_obj_id, 0);
  hid_t new_loc_id = SEXP_to_longlong(R_new_loc_id, 0);
  const char* new_name = CHAR(STRING_ELT(R_new_name, 0));
  hid_t lcpl_id = SEXP_to_longlong(R_lcpl_id, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Olink(obj_id, new_loc_id, new_name, lcpl_id, lapl_id);
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

/* H5_DLL hid_t H5Oopen(hid_t loc_id, const char *name, hid_t lapl_id); */
SEXP R_H5Oopen(SEXP R_loc_id, SEXP R_name, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  hid_t return_val = H5Oopen(loc_id, name, lapl_id);
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

/* H5_DLL hid_t H5Oopen_by_addr(hid_t loc_id, haddr_t addr); */
SEXP R_H5Oopen_by_addr(SEXP R_loc_id, SEXP R_addr){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  haddr_t addr = SEXP_to_longlong(R_addr, 0);
  hid_t return_val = H5Oopen_by_addr(loc_id, addr);
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

/* H5_DLL hid_t H5Oopen_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, hid_t lapl_id); */
SEXP R_H5Oopen_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* group_name = CHAR(STRING_ELT(R_group_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  hid_t return_val = H5Oopen_by_idx(loc_id, group_name, idx_type, order, n, lapl_id);
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

/* H5_DLL hid_t H5Oopen_by_token(hid_t loc_id, H5O_token_t token); */
SEXP R_H5Oopen_by_token(SEXP R_loc_id, SEXP R_token){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  R_helper = PROTECT(RToH5(R_token, h5_datatype[DT_H5O_token_t], 1));
  H5O_token_t token = * ((H5O_token_t*) VOIDPTR(R_helper));
  vars_protected++;
  hid_t return_val = H5Oopen_by_token(loc_id, token);
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

/* H5_DLL herr_t H5Orefresh(hid_t oid); */
SEXP R_H5Orefresh(SEXP R_oid){
  int vars_protected=0;
  hid_t oid = SEXP_to_longlong(R_oid, 0);
  herr_t return_val = H5Orefresh(oid);
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

/* H5_DLL herr_t H5Oset_comment(hid_t obj_id, const char *comment); */
SEXP R_H5Oset_comment(SEXP R_obj_id, SEXP R_comment){
  int vars_protected=0;
  hid_t obj_id = SEXP_to_longlong(R_obj_id, 0);
  const char* comment = CHAR(STRING_ELT(R_comment, 0));
  herr_t return_val = H5Oset_comment(obj_id, comment);
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

/* H5_DLL herr_t H5Oset_comment_by_name(hid_t loc_id, const char *name, const char *comment, hid_t lapl_id); */
SEXP R_H5Oset_comment_by_name(SEXP R_loc_id, SEXP R_name, SEXP R_comment, SEXP R_lapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  const char* comment = CHAR(STRING_ELT(R_comment, 0));
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Oset_comment_by_name(loc_id, name, comment, lapl_id);
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

/* H5_DLL herr_t H5Otoken_cmp(hid_t loc_id, const H5O_token_t *token1, const H5O_token_t *token2, int *cmp_value); */
SEXP R_H5Otoken_cmp(SEXP R_loc_id, SEXP R_token1, SEXP R_token2, SEXP R_cmp_value){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_cmp_value = PROTECT(duplicate(R_cmp_value));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  R_helper = PROTECT(RToH5(R_token1, h5_datatype[DT_H5O_token_t], guess_nelem(R_token1, h5_datatype[DT_H5O_token_t])));
  const H5O_token_t* token1= (const H5O_token_t*) VOIDPTR(R_helper);
  vars_protected++;
  R_helper = PROTECT(RToH5(R_token2, h5_datatype[DT_H5O_token_t], guess_nelem(R_token2, h5_datatype[DT_H5O_token_t])));
  const H5O_token_t* token2= (const H5O_token_t*) VOIDPTR(R_helper);
  vars_protected++;
  int* cmp_value;
  if(XLENGTH(R_cmp_value) == 0) {
    cmp_value = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_cmp_value, h5_datatype[DT_int], XLENGTH(R_cmp_value)));
    cmp_value= (int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Otoken_cmp(loc_id, token1, token2, cmp_value);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_cmp_value, h5_datatype[DT_int]);
  R_cmp_value = PROTECT(H5ToR_single_step(cmp_value, h5_datatype[DT_int], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_cmp_value);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("cmp_value"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Otoken_from_str(hid_t loc_id, const char *token_str, H5O_token_t *token); */
SEXP R_H5Otoken_from_str(SEXP R_loc_id, SEXP R_token_str, SEXP R_token){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_token = PROTECT(duplicate(R_token));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* token_str = CHAR(STRING_ELT(R_token_str, 0));
  R_helper = PROTECT(RToH5(R_token, h5_datatype[DT_H5O_token_t], guess_nelem(R_token, h5_datatype[DT_H5O_token_t])));
  H5O_token_t* token= (H5O_token_t*) VOIDPTR(R_helper);
  vars_protected++;
  herr_t return_val = H5Otoken_from_str(loc_id, token_str, token);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_token, h5_datatype[DT_H5O_token_t]);
  R_token = PROTECT(H5ToR_single_step(token, h5_datatype[DT_H5O_token_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_token);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("token"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Otoken_to_str(hid_t loc_id, const H5O_token_t *token, char **token_str); */
SEXP R_H5Otoken_to_str(SEXP R_loc_id, SEXP R_token, SEXP R_token_str){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_token_str = PROTECT(duplicate(R_token_str));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  R_helper = PROTECT(RToH5(R_token, h5_datatype[DT_H5O_token_t], guess_nelem(R_token, h5_datatype[DT_H5O_token_t])));
  const H5O_token_t* token= (const H5O_token_t*) VOIDPTR(R_helper);
  vars_protected++;
  char** token_str;
  if(XLENGTH(R_token_str) == 0) {
    token_str = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_token_str, h5_datatype[DT_char], XLENGTH(R_token_str)));
    token_str= (char**) VOIDPTR(R_helper);
    vars_protected++;
    if(!inherits(R_token_str, "_RToH5_empty")) {
      for(int i = 0; i < XLENGTH(R_token_str); ++i) {
        if(XLENGTH(STRING_ELT(R_token_str, i)) == 0) {
          token_str[i] = NULL;
        }
        else {
          token_str[i] = (char*) R_alloc(XLENGTH(STRING_ELT(R_token_str, i)), 1);
          strcpy(token_str[i], CHAR(STRING_ELT(R_token_str, i)));
        }
      }
    }
  }
  herr_t return_val = H5Otoken_to_str(loc_id, token, token_str);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_token_str, h5_datatype[DT_char]);
  R_token_str = PROTECT(H5ToR_single_step(token_str, h5_datatype[DT_char], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_token_str);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("token_str"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}


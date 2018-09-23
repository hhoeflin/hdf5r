
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

#include "Wrapper_auto_H5G.h"
/* H5_DLL herr_t H5Gclose(hid_t group_id); */
SEXP R_H5Gclose(SEXP R_group_id){
  int vars_protected=0;
  hid_t group_id = SEXP_to_longlong(R_group_id, 0);
  herr_t return_val = H5Gclose(group_id);
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

/* H5_DLL hid_t H5Gcreate_anon(hid_t loc_id, hid_t gcpl_id, hid_t gapl_id); */
SEXP R_H5Gcreate_anon(SEXP R_loc_id, SEXP R_gcpl_id, SEXP R_gapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  hid_t gcpl_id = SEXP_to_longlong(R_gcpl_id, 0);
  hid_t gapl_id = SEXP_to_longlong(R_gapl_id, 0);
  hid_t return_val = H5Gcreate_anon(loc_id, gcpl_id, gapl_id);
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

/* H5_DLL hid_t H5Gcreate2(hid_t loc_id, const char *name, hid_t lcpl_id, hid_t gcpl_id, hid_t gapl_id); */
SEXP R_H5Gcreate2(SEXP R_loc_id, SEXP R_name, SEXP R_lcpl_id, SEXP R_gcpl_id, SEXP R_gapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  hid_t lcpl_id = SEXP_to_longlong(R_lcpl_id, 0);
  hid_t gcpl_id = SEXP_to_longlong(R_gcpl_id, 0);
  hid_t gapl_id = SEXP_to_longlong(R_gapl_id, 0);
  hid_t return_val = H5Gcreate2(loc_id, name, lcpl_id, gcpl_id, gapl_id);
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

/* H5_DLL herr_t H5Gflush(hid_t group_id); */
SEXP R_H5Gflush(SEXP R_group_id){
  int vars_protected=0;
  hid_t group_id = SEXP_to_longlong(R_group_id, 0);
  herr_t return_val = H5Gflush(group_id);
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

/* H5_DLL hid_t H5Gget_create_plist(hid_t group_id); */
SEXP R_H5Gget_create_plist(SEXP R_group_id){
  int vars_protected=0;
  hid_t group_id = SEXP_to_longlong(R_group_id, 0);
  hid_t return_val = H5Gget_create_plist(group_id);
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

/* H5_DLL herr_t H5Gget_info(hid_t loc_id, H5G_info_t *ginfo); */
SEXP R_H5Gget_info(SEXP R_loc_id, SEXP R_ginfo){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_ginfo = PROTECT(duplicate(R_ginfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  R_helper = PROTECT(RToH5(R_ginfo, h5_datatype[DT_H5G_info_t], guess_nelem(R_ginfo, h5_datatype[DT_H5G_info_t])));
  H5G_info_t* ginfo= (H5G_info_t*) VOIDPTR(R_helper);
  vars_protected++;
  herr_t return_val = H5Gget_info(loc_id, ginfo);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_ginfo, h5_datatype[DT_H5G_info_t]);
  R_ginfo = PROTECT(H5ToR_single_step(ginfo, h5_datatype[DT_H5G_info_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_ginfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("ginfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Gget_info_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, H5G_info_t *ginfo, hid_t lapl_id); */
SEXP R_H5Gget_info_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_ginfo, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_ginfo = PROTECT(duplicate(R_ginfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* group_name = CHAR(STRING_ELT(R_group_name, 0));
  H5_index_t idx_type = SEXP_to_longlong(R_idx_type, 0);
  H5_iter_order_t order = SEXP_to_longlong(R_order, 0);
  hsize_t n = SEXP_to_longlong(R_n, 0);
  R_helper = PROTECT(RToH5(R_ginfo, h5_datatype[DT_H5G_info_t], guess_nelem(R_ginfo, h5_datatype[DT_H5G_info_t])));
  H5G_info_t* ginfo= (H5G_info_t*) VOIDPTR(R_helper);
  vars_protected++;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Gget_info_by_idx(loc_id, group_name, idx_type, order, n, ginfo, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_ginfo, h5_datatype[DT_H5G_info_t]);
  R_ginfo = PROTECT(H5ToR_single_step(ginfo, h5_datatype[DT_H5G_info_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_ginfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("ginfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Gget_info_by_name(hid_t loc_id, const char *name, H5G_info_t *ginfo, hid_t lapl_id); */
SEXP R_H5Gget_info_by_name(SEXP R_loc_id, SEXP R_name, SEXP R_ginfo, SEXP R_lapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_ginfo = PROTECT(duplicate(R_ginfo));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  R_helper = PROTECT(RToH5(R_ginfo, h5_datatype[DT_H5G_info_t], guess_nelem(R_ginfo, h5_datatype[DT_H5G_info_t])));
  H5G_info_t* ginfo= (H5G_info_t*) VOIDPTR(R_helper);
  vars_protected++;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  herr_t return_val = H5Gget_info_by_name(loc_id, name, ginfo, lapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_ginfo, h5_datatype[DT_H5G_info_t]);
  R_ginfo = PROTECT(H5ToR_single_step(ginfo, h5_datatype[DT_H5G_info_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_ginfo);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("ginfo"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Gopen2(hid_t loc_id, const char *name, hid_t gapl_id); */
SEXP R_H5Gopen2(SEXP R_loc_id, SEXP R_name, SEXP R_gapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  hid_t gapl_id = SEXP_to_longlong(R_gapl_id, 0);
  hid_t return_val = H5Gopen2(loc_id, name, gapl_id);
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

/* H5_DLL herr_t H5Grefresh(hid_t group_id); */
SEXP R_H5Grefresh(SEXP R_group_id){
  int vars_protected=0;
  hid_t group_id = SEXP_to_longlong(R_group_id, 0);
  herr_t return_val = H5Grefresh(group_id);
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

/* H5_DLL herr_t H5Gset_comment(hid_t loc_id, const char *name, const char *comment); */
SEXP R_H5Gset_comment(SEXP R_loc_id, SEXP R_name, SEXP R_comment){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  const char* comment = CHAR(STRING_ELT(R_comment, 0));
  herr_t return_val = H5Gset_comment(loc_id, name, comment);
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


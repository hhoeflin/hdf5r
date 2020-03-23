
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

#include "Wrapper_auto_H5P.h"
/* H5_DLL herr_t H5Padd_merge_committed_dtype_path(hid_t plist_id, const char *path); */
SEXP R_H5Padd_merge_committed_dtype_path(SEXP R_plist_id, SEXP R_path){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  const char* path = CHAR(STRING_ELT(R_path, 0));
  herr_t return_val = H5Padd_merge_committed_dtype_path(plist_id, path);
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

/* H5_DLL htri_t H5Pall_filters_avail(hid_t plist_id); */
SEXP R_H5Pall_filters_avail(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  htri_t return_val = H5Pall_filters_avail(plist_id);
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

/* H5_DLL herr_t H5Pclose(hid_t plist_id); */
SEXP R_H5Pclose(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  herr_t return_val = H5Pclose(plist_id);
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

/* H5_DLL herr_t H5Pclose_class(hid_t plist_id); */
SEXP R_H5Pclose_class(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  herr_t return_val = H5Pclose_class(plist_id);
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

/* H5_DLL hid_t H5Pcopy(hid_t plist_id); */
SEXP R_H5Pcopy(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hid_t return_val = H5Pcopy(plist_id);
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

/* H5_DLL herr_t H5Pcopy_prop(hid_t dst_id, hid_t src_id, const char *name); */
SEXP R_H5Pcopy_prop(SEXP R_dst_id, SEXP R_src_id, SEXP R_name){
  int vars_protected=0;
  hid_t dst_id = SEXP_to_longlong(R_dst_id, 0);
  hid_t src_id = SEXP_to_longlong(R_src_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  herr_t return_val = H5Pcopy_prop(dst_id, src_id, name);
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

/* H5_DLL hid_t H5Pcreate(hid_t cls_id); */
SEXP R_H5Pcreate(SEXP R_cls_id){
  int vars_protected=0;
  hid_t cls_id = SEXP_to_longlong(R_cls_id, 0);
  hid_t return_val = H5Pcreate(cls_id);
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

/* H5_DLL hid_t H5Pdecode(const void *buf); */
SEXP R_H5Pdecode(SEXP R_buf){
  int vars_protected=0;
  const void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  hid_t return_val = H5Pdecode(buf);
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

/* H5_DLL herr_t H5Pencode1(hid_t plist_id, void *buf, size_t *nalloc); */
SEXP R_H5Pencode(SEXP R_plist_id, SEXP R_buf, SEXP R_nalloc, SEXP _dupl_buf){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  R_nalloc = PROTECT(duplicate(R_nalloc));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
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
  herr_t return_val = H5Pencode(plist_id, buf, nalloc);
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

/* H5_DLL htri_t H5Pequal(hid_t id1, hid_t id2); */
SEXP R_H5Pequal(SEXP R_id1, SEXP R_id2){
  int vars_protected=0;
  hid_t id1 = SEXP_to_longlong(R_id1, 0);
  hid_t id2 = SEXP_to_longlong(R_id2, 0);
  htri_t return_val = H5Pequal(id1, id2);
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

/* H5_DLL htri_t H5Pexist(hid_t plist_id, const char *name); */
SEXP R_H5Pexist(SEXP R_plist_id, SEXP R_name){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  htri_t return_val = H5Pexist(plist_id, name);
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

/* H5_DLL herr_t H5Pfill_value_defined(hid_t plist, H5D_fill_value_t *status); */
SEXP R_H5Pfill_value_defined(SEXP R_plist, SEXP R_status){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_status = PROTECT(duplicate(R_status));
  vars_protected++;
  hid_t plist = SEXP_to_longlong(R_plist, 0);
  H5D_fill_value_t* status;
  if(XLENGTH(R_status) == 0) {
    status = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_status, h5_datatype[DT_H5D_fill_value_t], XLENGTH(R_status)));
    status= (H5D_fill_value_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pfill_value_defined(plist, status);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_status, h5_datatype[DT_H5D_fill_value_t]);
  R_status = PROTECT(H5ToR_single_step(status, h5_datatype[DT_H5D_fill_value_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_status);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("status"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pfree_merge_committed_dtype_paths(hid_t plist_id); */
SEXP R_H5Pfree_merge_committed_dtype_paths(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  herr_t return_val = H5Pfree_merge_committed_dtype_paths(plist_id);
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

/* H5_DLL herr_t H5Pget(hid_t plist_id, const char *name, void * value); */
SEXP R_H5Pget(SEXP R_plist_id, SEXP R_name, SEXP R_value, SEXP _dupl_value){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_value)) {
    R_value = PROTECT(duplicate(R_value));
    vars_protected++;
  }
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  void* value;
  if(XLENGTH(R_value) == 0) {
    value = NULL;
  }
  else {
    value = (void *) VOIDPTR(R_value);
  }
  herr_t return_val = H5Pget(plist_id, name, value);
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

/* H5_DLL herr_t H5Pget_alignment(hid_t fapl_id, hsize_t *threshold, hsize_t *alignment); */
SEXP R_H5Pget_alignment(SEXP R_fapl_id, SEXP R_threshold, SEXP R_alignment){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_threshold = PROTECT(duplicate(R_threshold));
  vars_protected++;
  R_alignment = PROTECT(duplicate(R_alignment));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hsize_t* threshold;
  if(XLENGTH(R_threshold) == 0) {
    threshold = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_threshold, h5_datatype[DT_hsize_t], XLENGTH(R_threshold)));
    threshold= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* alignment;
  if(XLENGTH(R_alignment) == 0) {
    alignment = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_alignment, h5_datatype[DT_hsize_t], XLENGTH(R_alignment)));
    alignment= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_alignment(fapl_id, threshold, alignment);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_threshold, h5_datatype[DT_hsize_t]);
  R_threshold = PROTECT(H5ToR_single_step(threshold, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_alignment, h5_datatype[DT_hsize_t]);
  R_alignment = PROTECT(H5ToR_single_step(alignment, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_threshold);
  SET_VECTOR_ELT(__ret_list, 2, R_alignment);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("threshold"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("alignment"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_alloc_time(hid_t plist_id, H5D_alloc_time_t *alloc_time); */
SEXP R_H5Pget_alloc_time(SEXP R_plist_id, SEXP R_alloc_time){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_alloc_time = PROTECT(duplicate(R_alloc_time));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5D_alloc_time_t* alloc_time;
  if(XLENGTH(R_alloc_time) == 0) {
    alloc_time = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_alloc_time, h5_datatype[DT_H5D_alloc_time_t], XLENGTH(R_alloc_time)));
    alloc_time= (H5D_alloc_time_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_alloc_time(plist_id, alloc_time);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_alloc_time, h5_datatype[DT_H5D_alloc_time_t]);
  R_alloc_time = PROTECT(H5ToR_single_step(alloc_time, h5_datatype[DT_H5D_alloc_time_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_alloc_time);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("alloc_time"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_attr_creation_order(hid_t plist_id, unsigned *crt_order_flags); */
SEXP R_H5Pget_attr_creation_order(SEXP R_plist_id, SEXP R_crt_order_flags){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_crt_order_flags = PROTECT(duplicate(R_crt_order_flags));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* crt_order_flags;
  if(XLENGTH(R_crt_order_flags) == 0) {
    crt_order_flags = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_crt_order_flags, h5_datatype[DT_unsigned], XLENGTH(R_crt_order_flags)));
    crt_order_flags= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_attr_creation_order(plist_id, crt_order_flags);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_crt_order_flags, h5_datatype[DT_unsigned]);
  R_crt_order_flags = PROTECT(H5ToR_single_step(crt_order_flags, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_crt_order_flags);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("crt_order_flags"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_attr_phase_change(hid_t plist_id, unsigned *max_compact, unsigned *min_dense); */
SEXP R_H5Pget_attr_phase_change(SEXP R_plist_id, SEXP R_max_compact, SEXP R_min_dense){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_max_compact = PROTECT(duplicate(R_max_compact));
  vars_protected++;
  R_min_dense = PROTECT(duplicate(R_min_dense));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* max_compact;
  if(XLENGTH(R_max_compact) == 0) {
    max_compact = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_max_compact, h5_datatype[DT_unsigned], XLENGTH(R_max_compact)));
    max_compact= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* min_dense;
  if(XLENGTH(R_min_dense) == 0) {
    min_dense = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_min_dense, h5_datatype[DT_unsigned], XLENGTH(R_min_dense)));
    min_dense= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_attr_phase_change(plist_id, max_compact, min_dense);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_max_compact, h5_datatype[DT_unsigned]);
  R_max_compact = PROTECT(H5ToR_single_step(max_compact, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_min_dense, h5_datatype[DT_unsigned]);
  R_min_dense = PROTECT(H5ToR_single_step(min_dense, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_max_compact);
  SET_VECTOR_ELT(__ret_list, 2, R_min_dense);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("max_compact"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("min_dense"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_btree_ratios(hid_t plist_id, double *left, double *middle, double *right); */
SEXP R_H5Pget_btree_ratios(SEXP R_plist_id, SEXP R_left, SEXP R_middle, SEXP R_right){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_left = PROTECT(duplicate(R_left));
  vars_protected++;
  R_middle = PROTECT(duplicate(R_middle));
  vars_protected++;
  R_right = PROTECT(duplicate(R_right));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  double* left;
  if(XLENGTH(R_left) == 0) {
    left = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_left, h5_datatype[DT_double], XLENGTH(R_left)));
    left= (double*) VOIDPTR(R_helper);
    vars_protected++;
  }
  double* middle;
  if(XLENGTH(R_middle) == 0) {
    middle = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_middle, h5_datatype[DT_double], XLENGTH(R_middle)));
    middle= (double*) VOIDPTR(R_helper);
    vars_protected++;
  }
  double* right;
  if(XLENGTH(R_right) == 0) {
    right = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_right, h5_datatype[DT_double], XLENGTH(R_right)));
    right= (double*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_btree_ratios(plist_id, left, middle, right);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_left, h5_datatype[DT_double]);
  R_left = PROTECT(H5ToR_single_step(left, h5_datatype[DT_double], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_middle, h5_datatype[DT_double]);
  R_middle = PROTECT(H5ToR_single_step(middle, h5_datatype[DT_double], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_right, h5_datatype[DT_double]);
  R_right = PROTECT(H5ToR_single_step(right, h5_datatype[DT_double], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 4));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_left);
  SET_VECTOR_ELT(__ret_list, 2, R_middle);
  SET_VECTOR_ELT(__ret_list, 3, R_right);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 4));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("left"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("middle"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("right"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_cache(hid_t plist_id, int *mdc_nelmts, size_t *rdcc_nslots, size_t *rdcc_nbytes, double *rdcc_w0); */
SEXP R_H5Pget_cache(SEXP R_plist_id, SEXP R_mdc_nelmts, SEXP R_rdcc_nslots, SEXP R_rdcc_nbytes, SEXP R_rdcc_w0){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_mdc_nelmts = PROTECT(duplicate(R_mdc_nelmts));
  vars_protected++;
  R_rdcc_nslots = PROTECT(duplicate(R_rdcc_nslots));
  vars_protected++;
  R_rdcc_nbytes = PROTECT(duplicate(R_rdcc_nbytes));
  vars_protected++;
  R_rdcc_w0 = PROTECT(duplicate(R_rdcc_w0));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  int* mdc_nelmts;
  if(XLENGTH(R_mdc_nelmts) == 0) {
    mdc_nelmts = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_mdc_nelmts, h5_datatype[DT_int], XLENGTH(R_mdc_nelmts)));
    mdc_nelmts= (int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* rdcc_nslots;
  if(XLENGTH(R_rdcc_nslots) == 0) {
    rdcc_nslots = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_rdcc_nslots, h5_datatype[DT_size_t], XLENGTH(R_rdcc_nslots)));
    rdcc_nslots= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* rdcc_nbytes;
  if(XLENGTH(R_rdcc_nbytes) == 0) {
    rdcc_nbytes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_rdcc_nbytes, h5_datatype[DT_size_t], XLENGTH(R_rdcc_nbytes)));
    rdcc_nbytes= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  double* rdcc_w0;
  if(XLENGTH(R_rdcc_w0) == 0) {
    rdcc_w0 = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_rdcc_w0, h5_datatype[DT_double], XLENGTH(R_rdcc_w0)));
    rdcc_w0= (double*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_cache(plist_id, mdc_nelmts, rdcc_nslots, rdcc_nbytes, rdcc_w0);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_mdc_nelmts, h5_datatype[DT_int]);
  R_mdc_nelmts = PROTECT(H5ToR_single_step(mdc_nelmts, h5_datatype[DT_int], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_rdcc_nslots, h5_datatype[DT_size_t]);
  R_rdcc_nslots = PROTECT(H5ToR_single_step(rdcc_nslots, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_rdcc_nbytes, h5_datatype[DT_size_t]);
  R_rdcc_nbytes = PROTECT(H5ToR_single_step(rdcc_nbytes, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_rdcc_w0, h5_datatype[DT_double]);
  R_rdcc_w0 = PROTECT(H5ToR_single_step(rdcc_w0, h5_datatype[DT_double], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 5));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_mdc_nelmts);
  SET_VECTOR_ELT(__ret_list, 2, R_rdcc_nslots);
  SET_VECTOR_ELT(__ret_list, 3, R_rdcc_nbytes);
  SET_VECTOR_ELT(__ret_list, 4, R_rdcc_w0);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 5));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("mdc_nelmts"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("rdcc_nslots"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("rdcc_nbytes"));
  SET_STRING_ELT(__ret_list_names, 4, mkChar("rdcc_w0"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_char_encoding(hid_t plist_id, H5T_cset_t *encoding ); */
SEXP R_H5Pget_char_encoding(SEXP R_plist_id, SEXP R_encoding){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_encoding = PROTECT(duplicate(R_encoding));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5T_cset_t* encoding;
  if(XLENGTH(R_encoding) == 0) {
    encoding = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_encoding, h5_datatype[DT_H5T_cset_t], XLENGTH(R_encoding)));
    encoding= (H5T_cset_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_char_encoding(plist_id, encoding);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_encoding, h5_datatype[DT_H5T_cset_t]);
  R_encoding = PROTECT(H5ToR_single_step(encoding, h5_datatype[DT_H5T_cset_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_encoding);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("encoding"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL int H5Pget_chunk(hid_t plist_id, int max_ndims, hsize_t dim[]); */
SEXP R_H5Pget_chunk(SEXP R_plist_id, SEXP R_max_ndims, SEXP R_dim){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_dim = PROTECT(duplicate(R_dim));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  int max_ndims = SEXP_to_longlong(R_max_ndims, 0);
  hsize_t* dim;
  if(XLENGTH(R_dim) == 0) {
    dim = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dim, h5_datatype[DT_hsize_t], XLENGTH(R_dim)));
    dim= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  int return_val = H5Pget_chunk(plist_id, max_ndims, dim);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_dim, h5_datatype[DT_hsize_t]);
  R_dim = PROTECT(H5ToR_single_step(dim, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_dim);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("dim"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_chunk_cache(hid_t dapl_id, size_t *rdcc_nslots, size_t *rdcc_nbytes, double *rdcc_w0); */
SEXP R_H5Pget_chunk_cache(SEXP R_dapl_id, SEXP R_rdcc_nslots, SEXP R_rdcc_nbytes, SEXP R_rdcc_w0){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_rdcc_nslots = PROTECT(duplicate(R_rdcc_nslots));
  vars_protected++;
  R_rdcc_nbytes = PROTECT(duplicate(R_rdcc_nbytes));
  vars_protected++;
  R_rdcc_w0 = PROTECT(duplicate(R_rdcc_w0));
  vars_protected++;
  hid_t dapl_id = SEXP_to_longlong(R_dapl_id, 0);
  size_t* rdcc_nslots;
  if(XLENGTH(R_rdcc_nslots) == 0) {
    rdcc_nslots = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_rdcc_nslots, h5_datatype[DT_size_t], XLENGTH(R_rdcc_nslots)));
    rdcc_nslots= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* rdcc_nbytes;
  if(XLENGTH(R_rdcc_nbytes) == 0) {
    rdcc_nbytes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_rdcc_nbytes, h5_datatype[DT_size_t], XLENGTH(R_rdcc_nbytes)));
    rdcc_nbytes= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  double* rdcc_w0;
  if(XLENGTH(R_rdcc_w0) == 0) {
    rdcc_w0 = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_rdcc_w0, h5_datatype[DT_double], XLENGTH(R_rdcc_w0)));
    rdcc_w0= (double*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_chunk_cache(dapl_id, rdcc_nslots, rdcc_nbytes, rdcc_w0);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_rdcc_nslots, h5_datatype[DT_size_t]);
  R_rdcc_nslots = PROTECT(H5ToR_single_step(rdcc_nslots, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_rdcc_nbytes, h5_datatype[DT_size_t]);
  R_rdcc_nbytes = PROTECT(H5ToR_single_step(rdcc_nbytes, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_rdcc_w0, h5_datatype[DT_double]);
  R_rdcc_w0 = PROTECT(H5ToR_single_step(rdcc_w0, h5_datatype[DT_double], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 4));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_rdcc_nslots);
  SET_VECTOR_ELT(__ret_list, 2, R_rdcc_nbytes);
  SET_VECTOR_ELT(__ret_list, 3, R_rdcc_w0);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 4));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("rdcc_nslots"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("rdcc_nbytes"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("rdcc_w0"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_chunk_opts(hid_t plist_id, unsigned *opts); */
SEXP R_H5Pget_chunk_opts(SEXP R_plist_id, SEXP R_opts){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_opts = PROTECT(duplicate(R_opts));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* opts;
  if(XLENGTH(R_opts) == 0) {
    opts = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_opts, h5_datatype[DT_unsigned], XLENGTH(R_opts)));
    opts= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_chunk_opts(plist_id, opts);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_opts, h5_datatype[DT_unsigned]);
  R_opts = PROTECT(H5ToR_single_step(opts, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_opts);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("opts"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Pget_class(hid_t plist_id); */
SEXP R_H5Pget_class(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hid_t return_val = H5Pget_class(plist_id);
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

/* H5_DLL char *H5Pget_class_name(hid_t pclass_id); */
SEXP R_H5Pget_class_name(SEXP R_pclass_id){
  int vars_protected=0;
  hid_t pclass_id = SEXP_to_longlong(R_pclass_id, 0);
  char* return_val = H5Pget_class_name(pclass_id);
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

/* H5_DLL hid_t H5Pget_class_parent(hid_t pclass_id); */
SEXP R_H5Pget_class_parent(SEXP R_pclass_id){
  int vars_protected=0;
  hid_t pclass_id = SEXP_to_longlong(R_pclass_id, 0);
  hid_t return_val = H5Pget_class_parent(pclass_id);
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

/* H5_DLL herr_t H5Pget_copy_object(hid_t plist_id, unsigned *crt_intmd ); */
SEXP R_H5Pget_copy_object(SEXP R_plist_id, SEXP R_crt_intmd){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_crt_intmd = PROTECT(duplicate(R_crt_intmd));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* crt_intmd;
  if(XLENGTH(R_crt_intmd) == 0) {
    crt_intmd = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_crt_intmd, h5_datatype[DT_unsigned], XLENGTH(R_crt_intmd)));
    crt_intmd= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_copy_object(plist_id, crt_intmd);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_crt_intmd, h5_datatype[DT_unsigned]);
  R_crt_intmd = PROTECT(H5ToR_single_step(crt_intmd, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_crt_intmd);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("crt_intmd"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_core_write_tracking(hid_t fapl_id, hbool_t *is_enabled, size_t *page_size); */
SEXP R_H5Pget_core_write_tracking(SEXP R_fapl_id, SEXP R_is_enabled, SEXP R_page_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_is_enabled = PROTECT(duplicate(R_is_enabled));
  vars_protected++;
  R_page_size = PROTECT(duplicate(R_page_size));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hbool_t* is_enabled;
  if(XLENGTH(R_is_enabled) == 0) {
    is_enabled = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_is_enabled, h5_datatype[DT_hbool_t], XLENGTH(R_is_enabled)));
    is_enabled= (hbool_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* page_size;
  if(XLENGTH(R_page_size) == 0) {
    page_size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_page_size, h5_datatype[DT_size_t], XLENGTH(R_page_size)));
    page_size= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_core_write_tracking(fapl_id, is_enabled, page_size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_is_enabled, h5_datatype[DT_hbool_t]);
  R_is_enabled = PROTECT(H5ToR_single_step(is_enabled, h5_datatype[DT_hbool_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_page_size, h5_datatype[DT_size_t]);
  R_page_size = PROTECT(H5ToR_single_step(page_size, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_is_enabled);
  SET_VECTOR_ELT(__ret_list, 2, R_page_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("is_enabled"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("page_size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_create_intermediate_group(hid_t plist_id, unsigned *crt_intmd ); */
SEXP R_H5Pget_create_intermediate_group(SEXP R_plist_id, SEXP R_crt_intmd){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_crt_intmd = PROTECT(duplicate(R_crt_intmd));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* crt_intmd;
  if(XLENGTH(R_crt_intmd) == 0) {
    crt_intmd = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_crt_intmd, h5_datatype[DT_unsigned], XLENGTH(R_crt_intmd)));
    crt_intmd= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_create_intermediate_group(plist_id, crt_intmd);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_crt_intmd, h5_datatype[DT_unsigned]);
  R_crt_intmd = PROTECT(H5ToR_single_step(crt_intmd, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_crt_intmd);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("crt_intmd"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL ssize_t H5Pget_data_transform(hid_t plist_id, char* expression , size_t size); */
SEXP R_H5Pget_data_transform(SEXP R_plist_id, SEXP R_expression, SEXP R_size){
  int vars_protected=0;
  R_expression = PROTECT(duplicate(R_expression));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  char* expression;
  if(XLENGTH(R_expression) == 0) {
    expression = NULL;
  }
  else {
    expression = R_alloc(strlen(CHAR(STRING_ELT(R_expression, 0))) + 1, 1);
    strcpy(expression, CHAR(STRING_ELT(R_expression, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  ssize_t return_val = H5Pget_data_transform(plist_id, expression, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(expression==NULL) {
    R_expression = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_expression = PROTECT(mkString(expression));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_expression);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("expression"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Pget_driver(hid_t plist_id); */
SEXP R_H5Pget_driver(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hid_t return_val = H5Pget_driver(plist_id);
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

/* H5_DLL herr_t H5Pget_dset_no_attrs_hint(hid_t dcpl_id, hbool_t *minimize); */
SEXP R_H5Pget_dset_no_attrs_hint(SEXP R_dcpl_id, SEXP R_minimize){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_minimize = PROTECT(duplicate(R_minimize));
  vars_protected++;
  hid_t dcpl_id = SEXP_to_longlong(R_dcpl_id, 0);
  hbool_t* minimize;
  if(XLENGTH(R_minimize) == 0) {
    minimize = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_minimize, h5_datatype[DT_hbool_t], XLENGTH(R_minimize)));
    minimize= (hbool_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_dset_no_attrs_hint(dcpl_id, minimize);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_minimize, h5_datatype[DT_hbool_t]);
  R_minimize = PROTECT(H5ToR_single_step(minimize, h5_datatype[DT_hbool_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_minimize);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("minimize"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL H5Z_EDC_t H5Pget_edc_check(hid_t plist_id); */
SEXP R_H5Pget_edc_check(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5Z_EDC_t return_val = H5Pget_edc_check(plist_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5Z_EDC_t]));
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

/* H5_DLL ssize_t H5Pget_efile_prefix(hid_t dapl_id, char* prefix , size_t size); */
SEXP R_H5Pget_efile_prefix(SEXP R_dapl_id, SEXP R_prefix, SEXP R_size){
  int vars_protected=0;
  R_prefix = PROTECT(duplicate(R_prefix));
  vars_protected++;
  hid_t dapl_id = SEXP_to_longlong(R_dapl_id, 0);
  char* prefix;
  if(XLENGTH(R_prefix) == 0) {
    prefix = NULL;
  }
  else {
    prefix = R_alloc(strlen(CHAR(STRING_ELT(R_prefix, 0))) + 1, 1);
    strcpy(prefix, CHAR(STRING_ELT(R_prefix, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  ssize_t return_val = H5Pget_efile_prefix(dapl_id, prefix, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(prefix==NULL) {
    R_prefix = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_prefix = PROTECT(mkString(prefix));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_prefix);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("prefix"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_elink_acc_flags(hid_t lapl_id, unsigned *flags); */
SEXP R_H5Pget_elink_acc_flags(SEXP R_lapl_id, SEXP R_flags){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_flags = PROTECT(duplicate(R_flags));
  vars_protected++;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  unsigned* flags;
  if(XLENGTH(R_flags) == 0) {
    flags = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_flags, h5_datatype[DT_unsigned], XLENGTH(R_flags)));
    flags= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_elink_acc_flags(lapl_id, flags);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_flags, h5_datatype[DT_unsigned]);
  R_flags = PROTECT(H5ToR_single_step(flags, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_flags);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("flags"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Pget_elink_fapl(hid_t lapl_id); */
SEXP R_H5Pget_elink_fapl(SEXP R_lapl_id){
  int vars_protected=0;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  hid_t return_val = H5Pget_elink_fapl(lapl_id);
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

/* H5_DLL herr_t H5Pget_elink_file_cache_size(hid_t plist_id, unsigned *efc_size); */
SEXP R_H5Pget_elink_file_cache_size(SEXP R_plist_id, SEXP R_efc_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_efc_size = PROTECT(duplicate(R_efc_size));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* efc_size;
  if(XLENGTH(R_efc_size) == 0) {
    efc_size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_efc_size, h5_datatype[DT_unsigned], XLENGTH(R_efc_size)));
    efc_size= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_elink_file_cache_size(plist_id, efc_size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_efc_size, h5_datatype[DT_unsigned]);
  R_efc_size = PROTECT(H5ToR_single_step(efc_size, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_efc_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("efc_size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL ssize_t H5Pget_elink_prefix(hid_t plist_id, char *prefix, size_t size); */
SEXP R_H5Pget_elink_prefix(SEXP R_plist_id, SEXP R_prefix, SEXP R_size){
  int vars_protected=0;
  R_prefix = PROTECT(duplicate(R_prefix));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  char* prefix;
  if(XLENGTH(R_prefix) == 0) {
    prefix = NULL;
  }
  else {
    prefix = R_alloc(strlen(CHAR(STRING_ELT(R_prefix, 0))) + 1, 1);
    strcpy(prefix, CHAR(STRING_ELT(R_prefix, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  ssize_t return_val = H5Pget_elink_prefix(plist_id, prefix, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(prefix==NULL) {
    R_prefix = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_prefix = PROTECT(mkString(prefix));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_prefix);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("prefix"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_est_link_info(hid_t plist_id, unsigned *est_num_entries , unsigned *est_name_len ); */
SEXP R_H5Pget_est_link_info(SEXP R_plist_id, SEXP R_est_num_entries, SEXP R_est_name_len){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_est_num_entries = PROTECT(duplicate(R_est_num_entries));
  vars_protected++;
  R_est_name_len = PROTECT(duplicate(R_est_name_len));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* est_num_entries;
  if(XLENGTH(R_est_num_entries) == 0) {
    est_num_entries = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_est_num_entries, h5_datatype[DT_unsigned], XLENGTH(R_est_num_entries)));
    est_num_entries= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* est_name_len;
  if(XLENGTH(R_est_name_len) == 0) {
    est_name_len = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_est_name_len, h5_datatype[DT_unsigned], XLENGTH(R_est_name_len)));
    est_name_len= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_est_link_info(plist_id, est_num_entries, est_name_len);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_est_num_entries, h5_datatype[DT_unsigned]);
  R_est_num_entries = PROTECT(H5ToR_single_step(est_num_entries, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_est_name_len, h5_datatype[DT_unsigned]);
  R_est_name_len = PROTECT(H5ToR_single_step(est_name_len, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_est_num_entries);
  SET_VECTOR_ELT(__ret_list, 2, R_est_name_len);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("est_num_entries"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("est_name_len"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_evict_on_close(hid_t fapl_id, hbool_t *evict_on_close); */
SEXP R_H5Pget_evict_on_close(SEXP R_fapl_id, SEXP R_evict_on_close){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_evict_on_close = PROTECT(duplicate(R_evict_on_close));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hbool_t* evict_on_close;
  if(XLENGTH(R_evict_on_close) == 0) {
    evict_on_close = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_evict_on_close, h5_datatype[DT_hbool_t], XLENGTH(R_evict_on_close)));
    evict_on_close= (hbool_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_evict_on_close(fapl_id, evict_on_close);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_evict_on_close, h5_datatype[DT_hbool_t]);
  R_evict_on_close = PROTECT(H5ToR_single_step(evict_on_close, h5_datatype[DT_hbool_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_evict_on_close);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("evict_on_close"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_external(hid_t plist_id, unsigned idx, size_t name_size, char *name, off_t *offset, hsize_t *size); */
SEXP R_H5Pget_external(SEXP R_plist_id, SEXP R_idx, SEXP R_name_size, SEXP R_name, SEXP R_offset, SEXP R_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_name = PROTECT(duplicate(R_name));
  vars_protected++;
  R_offset = PROTECT(duplicate(R_offset));
  vars_protected++;
  R_size = PROTECT(duplicate(R_size));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned idx = SEXP_to_longlong(R_idx, 0);
  size_t name_size = SEXP_to_longlong(R_name_size, 0);
  char* name;
  if(XLENGTH(R_name) == 0) {
    name = NULL;
  }
  else {
    name = R_alloc(strlen(CHAR(STRING_ELT(R_name, 0))) + 1, 1);
    strcpy(name, CHAR(STRING_ELT(R_name, 0)));
  }
  off_t* offset;
  if(XLENGTH(R_offset) == 0) {
    offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_offset, h5_datatype[DT_off_t], XLENGTH(R_offset)));
    offset= (off_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* size;
  if(XLENGTH(R_size) == 0) {
    size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_size, h5_datatype[DT_hsize_t], XLENGTH(R_size)));
    size= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_external(plist_id, idx, name_size, name, offset, size);
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
  size_helper = guess_nelem(R_offset, h5_datatype[DT_off_t]);
  R_offset = PROTECT(H5ToR_single_step(offset, h5_datatype[DT_off_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_size, h5_datatype[DT_hsize_t]);
  R_size = PROTECT(H5ToR_single_step(size, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 4));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_name);
  SET_VECTOR_ELT(__ret_list, 2, R_offset);
  SET_VECTOR_ELT(__ret_list, 3, R_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 4));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("name"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("offset"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL int H5Pget_external_count(hid_t plist_id); */
SEXP R_H5Pget_external_count(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  int return_val = H5Pget_external_count(plist_id);
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

/* H5_DLL herr_t H5Pget_family_offset(hid_t fapl_id, hsize_t *offset); */
SEXP R_H5Pget_family_offset(SEXP R_fapl_id, SEXP R_offset){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_offset = PROTECT(duplicate(R_offset));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hsize_t* offset;
  if(XLENGTH(R_offset) == 0) {
    offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_offset, h5_datatype[DT_hsize_t], XLENGTH(R_offset)));
    offset= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_family_offset(fapl_id, offset);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_offset, h5_datatype[DT_hsize_t]);
  R_offset = PROTECT(H5ToR_single_step(offset, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_offset);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("offset"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_fclose_degree(hid_t fapl_id, H5F_close_degree_t *degree); */
SEXP R_H5Pget_fclose_degree(SEXP R_fapl_id, SEXP R_degree){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_degree = PROTECT(duplicate(R_degree));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  H5F_close_degree_t* degree;
  if(XLENGTH(R_degree) == 0) {
    degree = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_degree, h5_datatype[DT_H5F_close_degree_t], XLENGTH(R_degree)));
    degree= (H5F_close_degree_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_fclose_degree(fapl_id, degree);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_degree, h5_datatype[DT_H5F_close_degree_t]);
  R_degree = PROTECT(H5ToR_single_step(degree, h5_datatype[DT_H5F_close_degree_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_degree);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("degree"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_file_space(hid_t plist_id, H5F_file_space_type_t *strategy, hsize_t *threshold); */
SEXP R_H5Pget_file_space(SEXP R_plist_id, SEXP R_strategy, SEXP R_threshold){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_strategy = PROTECT(duplicate(R_strategy));
  vars_protected++;
  R_threshold = PROTECT(duplicate(R_threshold));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5F_file_space_type_t* strategy;
  if(XLENGTH(R_strategy) == 0) {
    strategy = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_strategy, h5_datatype[DT_H5F_file_space_type_t], XLENGTH(R_strategy)));
    strategy= (H5F_file_space_type_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* threshold;
  if(XLENGTH(R_threshold) == 0) {
    threshold = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_threshold, h5_datatype[DT_hsize_t], XLENGTH(R_threshold)));
    threshold= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_file_space(plist_id, strategy, threshold);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_strategy, h5_datatype[DT_H5F_file_space_type_t]);
  R_strategy = PROTECT(H5ToR_single_step(strategy, h5_datatype[DT_H5F_file_space_type_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_threshold, h5_datatype[DT_hsize_t]);
  R_threshold = PROTECT(H5ToR_single_step(threshold, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_strategy);
  SET_VECTOR_ELT(__ret_list, 2, R_threshold);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("strategy"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("threshold"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_file_space_page_size(hid_t plist_id, hsize_t *fsp_size); */
SEXP R_H5Pget_file_space_page_size(SEXP R_plist_id, SEXP R_fsp_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_fsp_size = PROTECT(duplicate(R_fsp_size));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hsize_t* fsp_size;
  if(XLENGTH(R_fsp_size) == 0) {
    fsp_size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_fsp_size, h5_datatype[DT_hsize_t], XLENGTH(R_fsp_size)));
    fsp_size= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_file_space_page_size(plist_id, fsp_size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_fsp_size, h5_datatype[DT_hsize_t]);
  R_fsp_size = PROTECT(H5ToR_single_step(fsp_size, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_fsp_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("fsp_size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_file_space_strategy(hid_t plist_id, H5F_fspace_strategy_t *strategy, hbool_t *persist, hsize_t *threshold); */
SEXP R_H5Pget_file_space_strategy(SEXP R_plist_id, SEXP R_strategy, SEXP R_persist, SEXP R_threshold){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_strategy = PROTECT(duplicate(R_strategy));
  vars_protected++;
  R_persist = PROTECT(duplicate(R_persist));
  vars_protected++;
  R_threshold = PROTECT(duplicate(R_threshold));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5F_fspace_strategy_t* strategy;
  if(XLENGTH(R_strategy) == 0) {
    strategy = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_strategy, h5_datatype[DT_H5F_fspace_strategy_t], XLENGTH(R_strategy)));
    strategy= (H5F_fspace_strategy_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hbool_t* persist;
  if(XLENGTH(R_persist) == 0) {
    persist = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_persist, h5_datatype[DT_hbool_t], XLENGTH(R_persist)));
    persist= (hbool_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* threshold;
  if(XLENGTH(R_threshold) == 0) {
    threshold = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_threshold, h5_datatype[DT_hsize_t], XLENGTH(R_threshold)));
    threshold= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_file_space_strategy(plist_id, strategy, persist, threshold);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_strategy, h5_datatype[DT_H5F_fspace_strategy_t]);
  R_strategy = PROTECT(H5ToR_single_step(strategy, h5_datatype[DT_H5F_fspace_strategy_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_persist, h5_datatype[DT_hbool_t]);
  R_persist = PROTECT(H5ToR_single_step(persist, h5_datatype[DT_hbool_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_threshold, h5_datatype[DT_hsize_t]);
  R_threshold = PROTECT(H5ToR_single_step(threshold, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 4));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_strategy);
  SET_VECTOR_ELT(__ret_list, 2, R_persist);
  SET_VECTOR_ELT(__ret_list, 3, R_threshold);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 4));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("strategy"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("persist"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("threshold"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_fill_time(hid_t plist_id, H5D_fill_time_t *fill_time); */
SEXP R_H5Pget_fill_time(SEXP R_plist_id, SEXP R_fill_time){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_fill_time = PROTECT(duplicate(R_fill_time));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5D_fill_time_t* fill_time;
  if(XLENGTH(R_fill_time) == 0) {
    fill_time = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_fill_time, h5_datatype[DT_H5D_fill_time_t], XLENGTH(R_fill_time)));
    fill_time= (H5D_fill_time_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_fill_time(plist_id, fill_time);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_fill_time, h5_datatype[DT_H5D_fill_time_t]);
  R_fill_time = PROTECT(H5ToR_single_step(fill_time, h5_datatype[DT_H5D_fill_time_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_fill_time);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("fill_time"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_fill_value(hid_t plist_id, hid_t type_id, void *value); */
SEXP R_H5Pget_fill_value(SEXP R_plist_id, SEXP R_type_id, SEXP R_value, SEXP _dupl_value){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_value)) {
    R_value = PROTECT(duplicate(R_value));
    vars_protected++;
  }
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  void* value;
  if(XLENGTH(R_value) == 0) {
    value = NULL;
  }
  else {
    value = (void *) VOIDPTR(R_value);
  }
  herr_t return_val = H5Pget_fill_value(plist_id, type_id, value);
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

/* H5_DLL herr_t H5Pget_filter_by_id2(hid_t plist_id, H5Z_filter_t id, unsigned int *flags, size_t *cd_nelmts, unsigned cd_values[], size_t namelen, char name[], unsigned *filter_config); */
SEXP R_H5Pget_filter_by_id2(SEXP R_plist_id, SEXP R_id, SEXP R_flags, SEXP R_cd_nelmts, SEXP R_cd_values, SEXP R_namelen, SEXP R_name, SEXP R_filter_config){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_flags = PROTECT(duplicate(R_flags));
  vars_protected++;
  R_cd_nelmts = PROTECT(duplicate(R_cd_nelmts));
  vars_protected++;
  R_cd_values = PROTECT(duplicate(R_cd_values));
  vars_protected++;
  R_name = PROTECT(duplicate(R_name));
  vars_protected++;
  R_filter_config = PROTECT(duplicate(R_filter_config));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5Z_filter_t id = SEXP_to_longlong(R_id, 0);
  unsigned int* flags;
  if(XLENGTH(R_flags) == 0) {
    flags = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_flags, h5_datatype[DT_unsigned_int], XLENGTH(R_flags)));
    flags= (unsigned int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* cd_nelmts;
  if(XLENGTH(R_cd_nelmts) == 0) {
    cd_nelmts = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_cd_nelmts, h5_datatype[DT_size_t], XLENGTH(R_cd_nelmts)));
    cd_nelmts= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* cd_values;
  if(XLENGTH(R_cd_values) == 0) {
    cd_values = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_cd_values, h5_datatype[DT_unsigned], XLENGTH(R_cd_values)));
    cd_values= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t namelen = SEXP_to_longlong(R_namelen, 0);
  char* name;
  if(XLENGTH(R_name) == 0) {
    name = NULL;
  }
  else {
    name = R_alloc(strlen(CHAR(STRING_ELT(R_name, 0))) + 1, 1);
    strcpy(name, CHAR(STRING_ELT(R_name, 0)));
  }
  unsigned* filter_config;
  if(XLENGTH(R_filter_config) == 0) {
    filter_config = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_filter_config, h5_datatype[DT_unsigned], XLENGTH(R_filter_config)));
    filter_config= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_filter_by_id2(plist_id, id, flags, cd_nelmts, cd_values, namelen, name, filter_config);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_flags, h5_datatype[DT_unsigned_int]);
  R_flags = PROTECT(H5ToR_single_step(flags, h5_datatype[DT_unsigned_int], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_cd_nelmts, h5_datatype[DT_size_t]);
  R_cd_nelmts = PROTECT(H5ToR_single_step(cd_nelmts, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_cd_values, h5_datatype[DT_unsigned]);
  R_cd_values = PROTECT(H5ToR_single_step(cd_values, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  if(name==NULL) {
    R_name = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_name = PROTECT(mkString(name));
    vars_protected++;
  }
  size_helper = guess_nelem(R_filter_config, h5_datatype[DT_unsigned]);
  R_filter_config = PROTECT(H5ToR_single_step(filter_config, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 6));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_flags);
  SET_VECTOR_ELT(__ret_list, 2, R_cd_nelmts);
  SET_VECTOR_ELT(__ret_list, 3, R_cd_values);
  SET_VECTOR_ELT(__ret_list, 4, R_name);
  SET_VECTOR_ELT(__ret_list, 5, R_filter_config);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 6));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("flags"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("cd_nelmts"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("cd_values"));
  SET_STRING_ELT(__ret_list_names, 4, mkChar("name"));
  SET_STRING_ELT(__ret_list_names, 5, mkChar("filter_config"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL H5Z_filter_t H5Pget_filter2(hid_t plist_id, unsigned filter, unsigned int *flags, size_t *cd_nelmts, unsigned cd_values[], size_t namelen, char name[], unsigned *filter_config ); */
SEXP R_H5Pget_filter2(SEXP R_plist_id, SEXP R_filter, SEXP R_flags, SEXP R_cd_nelmts, SEXP R_cd_values, SEXP R_namelen, SEXP R_name, SEXP R_filter_config){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_flags = PROTECT(duplicate(R_flags));
  vars_protected++;
  R_cd_nelmts = PROTECT(duplicate(R_cd_nelmts));
  vars_protected++;
  R_cd_values = PROTECT(duplicate(R_cd_values));
  vars_protected++;
  R_name = PROTECT(duplicate(R_name));
  vars_protected++;
  R_filter_config = PROTECT(duplicate(R_filter_config));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned filter = SEXP_to_longlong(R_filter, 0);
  unsigned int* flags;
  if(XLENGTH(R_flags) == 0) {
    flags = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_flags, h5_datatype[DT_unsigned_int], XLENGTH(R_flags)));
    flags= (unsigned int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* cd_nelmts;
  if(XLENGTH(R_cd_nelmts) == 0) {
    cd_nelmts = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_cd_nelmts, h5_datatype[DT_size_t], XLENGTH(R_cd_nelmts)));
    cd_nelmts= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* cd_values;
  if(XLENGTH(R_cd_values) == 0) {
    cd_values = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_cd_values, h5_datatype[DT_unsigned], XLENGTH(R_cd_values)));
    cd_values= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t namelen = SEXP_to_longlong(R_namelen, 0);
  char* name;
  if(XLENGTH(R_name) == 0) {
    name = NULL;
  }
  else {
    name = R_alloc(strlen(CHAR(STRING_ELT(R_name, 0))) + 1, 1);
    strcpy(name, CHAR(STRING_ELT(R_name, 0)));
  }
  unsigned* filter_config;
  if(XLENGTH(R_filter_config) == 0) {
    filter_config = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_filter_config, h5_datatype[DT_unsigned], XLENGTH(R_filter_config)));
    filter_config= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  H5Z_filter_t return_val = H5Pget_filter2(plist_id, filter, flags, cd_nelmts, cd_values, namelen, name, filter_config);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_flags, h5_datatype[DT_unsigned_int]);
  R_flags = PROTECT(H5ToR_single_step(flags, h5_datatype[DT_unsigned_int], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_cd_nelmts, h5_datatype[DT_size_t]);
  R_cd_nelmts = PROTECT(H5ToR_single_step(cd_nelmts, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_cd_values, h5_datatype[DT_unsigned]);
  R_cd_values = PROTECT(H5ToR_single_step(cd_values, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  if(name==NULL) {
    R_name = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_name = PROTECT(mkString(name));
    vars_protected++;
  }
  size_helper = guess_nelem(R_filter_config, h5_datatype[DT_unsigned]);
  R_filter_config = PROTECT(H5ToR_single_step(filter_config, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 6));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_flags);
  SET_VECTOR_ELT(__ret_list, 2, R_cd_nelmts);
  SET_VECTOR_ELT(__ret_list, 3, R_cd_values);
  SET_VECTOR_ELT(__ret_list, 4, R_name);
  SET_VECTOR_ELT(__ret_list, 5, R_filter_config);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 6));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("flags"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("cd_nelmts"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("cd_values"));
  SET_STRING_ELT(__ret_list_names, 4, mkChar("name"));
  SET_STRING_ELT(__ret_list_names, 5, mkChar("filter_config"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_gc_references(hid_t fapl_id, unsigned *gc_ref); */
SEXP R_H5Pget_gc_references(SEXP R_fapl_id, SEXP R_gc_ref){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_gc_ref = PROTECT(duplicate(R_gc_ref));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  unsigned* gc_ref;
  if(XLENGTH(R_gc_ref) == 0) {
    gc_ref = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_gc_ref, h5_datatype[DT_unsigned], XLENGTH(R_gc_ref)));
    gc_ref= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_gc_references(fapl_id, gc_ref);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_gc_ref, h5_datatype[DT_unsigned]);
  R_gc_ref = PROTECT(H5ToR_single_step(gc_ref, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_gc_ref);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("gc_ref"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_hyper_vector_size(hid_t fapl_id, size_t *size); */
SEXP R_H5Pget_hyper_vector_size(SEXP R_fapl_id, SEXP R_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_size = PROTECT(duplicate(R_size));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  size_t* size;
  if(XLENGTH(R_size) == 0) {
    size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_size, h5_datatype[DT_size_t], XLENGTH(R_size)));
    size= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_hyper_vector_size(fapl_id, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_size, h5_datatype[DT_size_t]);
  R_size = PROTECT(H5ToR_single_step(size, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_istore_k(hid_t plist_id, unsigned *ik); */
SEXP R_H5Pget_istore_k(SEXP R_plist_id, SEXP R_ik){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_ik = PROTECT(duplicate(R_ik));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* ik;
  if(XLENGTH(R_ik) == 0) {
    ik = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_ik, h5_datatype[DT_unsigned], XLENGTH(R_ik)));
    ik= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_istore_k(plist_id, ik);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_ik, h5_datatype[DT_unsigned]);
  R_ik = PROTECT(H5ToR_single_step(ik, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_ik);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("ik"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL H5D_layout_t H5Pget_layout(hid_t plist_id); */
SEXP R_H5Pget_layout(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5D_layout_t return_val = H5Pget_layout(plist_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5D_layout_t]));
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

/* H5_DLL herr_t H5Pget_libver_bounds(hid_t plist_id, H5F_libver_t *low, H5F_libver_t *high); */
SEXP R_H5Pget_libver_bounds(SEXP R_plist_id, SEXP R_low, SEXP R_high){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_low = PROTECT(duplicate(R_low));
  vars_protected++;
  R_high = PROTECT(duplicate(R_high));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5F_libver_t* low;
  if(XLENGTH(R_low) == 0) {
    low = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_low, h5_datatype[DT_H5F_libver_t], XLENGTH(R_low)));
    low= (H5F_libver_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  H5F_libver_t* high;
  if(XLENGTH(R_high) == 0) {
    high = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_high, h5_datatype[DT_H5F_libver_t], XLENGTH(R_high)));
    high= (H5F_libver_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_libver_bounds(plist_id, low, high);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_low, h5_datatype[DT_H5F_libver_t]);
  R_low = PROTECT(H5ToR_single_step(low, h5_datatype[DT_H5F_libver_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_high, h5_datatype[DT_H5F_libver_t]);
  R_high = PROTECT(H5ToR_single_step(high, h5_datatype[DT_H5F_libver_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_low);
  SET_VECTOR_ELT(__ret_list, 2, R_high);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("low"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("high"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_link_creation_order(hid_t plist_id, unsigned *crt_order_flags ); */
SEXP R_H5Pget_link_creation_order(SEXP R_plist_id, SEXP R_crt_order_flags){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_crt_order_flags = PROTECT(duplicate(R_crt_order_flags));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* crt_order_flags;
  if(XLENGTH(R_crt_order_flags) == 0) {
    crt_order_flags = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_crt_order_flags, h5_datatype[DT_unsigned], XLENGTH(R_crt_order_flags)));
    crt_order_flags= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_link_creation_order(plist_id, crt_order_flags);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_crt_order_flags, h5_datatype[DT_unsigned]);
  R_crt_order_flags = PROTECT(H5ToR_single_step(crt_order_flags, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_crt_order_flags);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("crt_order_flags"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_link_phase_change(hid_t plist_id, unsigned *max_compact , unsigned *min_dense ); */
SEXP R_H5Pget_link_phase_change(SEXP R_plist_id, SEXP R_max_compact, SEXP R_min_dense){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_max_compact = PROTECT(duplicate(R_max_compact));
  vars_protected++;
  R_min_dense = PROTECT(duplicate(R_min_dense));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* max_compact;
  if(XLENGTH(R_max_compact) == 0) {
    max_compact = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_max_compact, h5_datatype[DT_unsigned], XLENGTH(R_max_compact)));
    max_compact= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* min_dense;
  if(XLENGTH(R_min_dense) == 0) {
    min_dense = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_min_dense, h5_datatype[DT_unsigned], XLENGTH(R_min_dense)));
    min_dense= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_link_phase_change(plist_id, max_compact, min_dense);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_max_compact, h5_datatype[DT_unsigned]);
  R_max_compact = PROTECT(H5ToR_single_step(max_compact, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_min_dense, h5_datatype[DT_unsigned]);
  R_min_dense = PROTECT(H5ToR_single_step(min_dense, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_max_compact);
  SET_VECTOR_ELT(__ret_list, 2, R_min_dense);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("max_compact"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("min_dense"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_local_heap_size_hint(hid_t plist_id, size_t *size_hint ); */
SEXP R_H5Pget_local_heap_size_hint(SEXP R_plist_id, SEXP R_size_hint){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_size_hint = PROTECT(duplicate(R_size_hint));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  size_t* size_hint;
  if(XLENGTH(R_size_hint) == 0) {
    size_hint = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_size_hint, h5_datatype[DT_size_t], XLENGTH(R_size_hint)));
    size_hint= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_local_heap_size_hint(plist_id, size_hint);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_size_hint, h5_datatype[DT_size_t]);
  R_size_hint = PROTECT(H5ToR_single_step(size_hint, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_size_hint);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("size_hint"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_mdc_config(hid_t plist_id, H5AC_cache_config_t * config_ptr);  */
SEXP R_H5Pget_mdc_config (SEXP R_plist_id, SEXP R_config_ptr){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_config_ptr = PROTECT(duplicate(R_config_ptr));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  R_helper = PROTECT(RToH5(R_config_ptr, h5_datatype[DT_H5AC_cache_config_t], guess_nelem(R_config_ptr, h5_datatype[DT_H5AC_cache_config_t])));
  H5AC_cache_config_t* config_ptr= (H5AC_cache_config_t*) VOIDPTR(R_helper);
  vars_protected++;
  herr_t return_val = H5Pget_mdc_config (plist_id, config_ptr);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_config_ptr, h5_datatype[DT_H5AC_cache_config_t]);
  R_config_ptr = PROTECT(H5ToR_single_step(config_ptr, h5_datatype[DT_H5AC_cache_config_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_config_ptr);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("config_ptr"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_mdc_image_config(hid_t plist_id, H5AC_cache_image_config_t *config_ptr ); */
SEXP R_H5Pget_mdc_image_config(SEXP R_plist_id, SEXP R_config_ptr){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_config_ptr = PROTECT(duplicate(R_config_ptr));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  R_helper = PROTECT(RToH5(R_config_ptr, h5_datatype[DT_H5AC_cache_image_config_t], guess_nelem(R_config_ptr, h5_datatype[DT_H5AC_cache_image_config_t])));
  H5AC_cache_image_config_t* config_ptr= (H5AC_cache_image_config_t*) VOIDPTR(R_helper);
  vars_protected++;
  herr_t return_val = H5Pget_mdc_image_config(plist_id, config_ptr);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_config_ptr, h5_datatype[DT_H5AC_cache_image_config_t]);
  R_config_ptr = PROTECT(H5ToR_single_step(config_ptr, h5_datatype[DT_H5AC_cache_image_config_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_config_ptr);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("config_ptr"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_mdc_log_options(hid_t plist_id, hbool_t *is_enabled, char *location, size_t *location_size, hbool_t *start_on_access); */
SEXP R_H5Pget_mdc_log_options(SEXP R_plist_id, SEXP R_is_enabled, SEXP R_location, SEXP R_location_size, SEXP R_start_on_access){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_is_enabled = PROTECT(duplicate(R_is_enabled));
  vars_protected++;
  R_location = PROTECT(duplicate(R_location));
  vars_protected++;
  R_location_size = PROTECT(duplicate(R_location_size));
  vars_protected++;
  R_start_on_access = PROTECT(duplicate(R_start_on_access));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hbool_t* is_enabled;
  if(XLENGTH(R_is_enabled) == 0) {
    is_enabled = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_is_enabled, h5_datatype[DT_hbool_t], XLENGTH(R_is_enabled)));
    is_enabled= (hbool_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  char* location;
  if(XLENGTH(R_location) == 0) {
    location = NULL;
  }
  else {
    location = R_alloc(strlen(CHAR(STRING_ELT(R_location, 0))) + 1, 1);
    strcpy(location, CHAR(STRING_ELT(R_location, 0)));
  }
  size_t* location_size;
  if(XLENGTH(R_location_size) == 0) {
    location_size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_location_size, h5_datatype[DT_size_t], XLENGTH(R_location_size)));
    location_size= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hbool_t* start_on_access;
  if(XLENGTH(R_start_on_access) == 0) {
    start_on_access = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_start_on_access, h5_datatype[DT_hbool_t], XLENGTH(R_start_on_access)));
    start_on_access= (hbool_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_mdc_log_options(plist_id, is_enabled, location, location_size, start_on_access);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_is_enabled, h5_datatype[DT_hbool_t]);
  R_is_enabled = PROTECT(H5ToR_single_step(is_enabled, h5_datatype[DT_hbool_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  if(location==NULL) {
    R_location = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_location = PROTECT(mkString(location));
    vars_protected++;
  }
  size_helper = guess_nelem(R_location_size, h5_datatype[DT_size_t]);
  R_location_size = PROTECT(H5ToR_single_step(location_size, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_start_on_access, h5_datatype[DT_hbool_t]);
  R_start_on_access = PROTECT(H5ToR_single_step(start_on_access, h5_datatype[DT_hbool_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 5));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_is_enabled);
  SET_VECTOR_ELT(__ret_list, 2, R_location);
  SET_VECTOR_ELT(__ret_list, 3, R_location_size);
  SET_VECTOR_ELT(__ret_list, 4, R_start_on_access);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 5));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("is_enabled"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("location"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("location_size"));
  SET_STRING_ELT(__ret_list_names, 4, mkChar("start_on_access"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_meta_block_size(hid_t fapl_id, hsize_t *size); */
SEXP R_H5Pget_meta_block_size(SEXP R_fapl_id, SEXP R_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_size = PROTECT(duplicate(R_size));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hsize_t* size;
  if(XLENGTH(R_size) == 0) {
    size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_size, h5_datatype[DT_hsize_t], XLENGTH(R_size)));
    size= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_meta_block_size(fapl_id, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_size, h5_datatype[DT_hsize_t]);
  R_size = PROTECT(H5ToR_single_step(size, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_metadata_read_attempts(hid_t plist_id, unsigned *attempts); */
SEXP R_H5Pget_metadata_read_attempts(SEXP R_plist_id, SEXP R_attempts){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_attempts = PROTECT(duplicate(R_attempts));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* attempts;
  if(XLENGTH(R_attempts) == 0) {
    attempts = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_attempts, h5_datatype[DT_unsigned], XLENGTH(R_attempts)));
    attempts= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_metadata_read_attempts(plist_id, attempts);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_attempts, h5_datatype[DT_unsigned]);
  R_attempts = PROTECT(H5ToR_single_step(attempts, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_attempts);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("attempts"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_multi_type(hid_t fapl_id, H5FD_mem_t *type); */
SEXP R_H5Pget_multi_type(SEXP R_fapl_id, SEXP R_type){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_type = PROTECT(duplicate(R_type));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  H5FD_mem_t* type;
  if(XLENGTH(R_type) == 0) {
    type = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_type, h5_datatype[DT_H5FD_mem_t], XLENGTH(R_type)));
    type= (H5FD_mem_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_multi_type(fapl_id, type);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_type, h5_datatype[DT_H5FD_mem_t]);
  R_type = PROTECT(H5ToR_single_step(type, h5_datatype[DT_H5FD_mem_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_type);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("type"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL int H5Pget_nfilters(hid_t plist_id); */
SEXP R_H5Pget_nfilters(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  int return_val = H5Pget_nfilters(plist_id);
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

/* H5_DLL herr_t H5Pget_nlinks(hid_t plist_id, size_t *nlinks); */
SEXP R_H5Pget_nlinks(SEXP R_plist_id, SEXP R_nlinks){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_nlinks = PROTECT(duplicate(R_nlinks));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  size_t* nlinks;
  if(XLENGTH(R_nlinks) == 0) {
    nlinks = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_nlinks, h5_datatype[DT_size_t], XLENGTH(R_nlinks)));
    nlinks= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_nlinks(plist_id, nlinks);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_nlinks, h5_datatype[DT_size_t]);
  R_nlinks = PROTECT(H5ToR_single_step(nlinks, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_nlinks);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("nlinks"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_nprops(hid_t id, size_t *nprops); */
SEXP R_H5Pget_nprops(SEXP R_id, SEXP R_nprops){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_nprops = PROTECT(duplicate(R_nprops));
  vars_protected++;
  hid_t id = SEXP_to_longlong(R_id, 0);
  size_t* nprops;
  if(XLENGTH(R_nprops) == 0) {
    nprops = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_nprops, h5_datatype[DT_size_t], XLENGTH(R_nprops)));
    nprops= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_nprops(id, nprops);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_nprops, h5_datatype[DT_size_t]);
  R_nprops = PROTECT(H5ToR_single_step(nprops, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_nprops);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("nprops"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_obj_track_times(hid_t plist_id, hbool_t *track_times); */
SEXP R_H5Pget_obj_track_times(SEXP R_plist_id, SEXP R_track_times){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_track_times = PROTECT(duplicate(R_track_times));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hbool_t* track_times;
  if(XLENGTH(R_track_times) == 0) {
    track_times = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_track_times, h5_datatype[DT_hbool_t], XLENGTH(R_track_times)));
    track_times= (hbool_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_obj_track_times(plist_id, track_times);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_track_times, h5_datatype[DT_hbool_t]);
  R_track_times = PROTECT(H5ToR_single_step(track_times, h5_datatype[DT_hbool_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_track_times);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("track_times"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_page_buffer_size(hid_t plist_id, size_t *buf_size, unsigned *min_meta_per, unsigned *min_raw_per); */
SEXP R_H5Pget_page_buffer_size(SEXP R_plist_id, SEXP R_buf_size, SEXP R_min_meta_per, SEXP R_min_raw_per){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_buf_size = PROTECT(duplicate(R_buf_size));
  vars_protected++;
  R_min_meta_per = PROTECT(duplicate(R_min_meta_per));
  vars_protected++;
  R_min_raw_per = PROTECT(duplicate(R_min_raw_per));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  size_t* buf_size;
  if(XLENGTH(R_buf_size) == 0) {
    buf_size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buf_size, h5_datatype[DT_size_t], XLENGTH(R_buf_size)));
    buf_size= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* min_meta_per;
  if(XLENGTH(R_min_meta_per) == 0) {
    min_meta_per = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_min_meta_per, h5_datatype[DT_unsigned], XLENGTH(R_min_meta_per)));
    min_meta_per= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* min_raw_per;
  if(XLENGTH(R_min_raw_per) == 0) {
    min_raw_per = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_min_raw_per, h5_datatype[DT_unsigned], XLENGTH(R_min_raw_per)));
    min_raw_per= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_page_buffer_size(plist_id, buf_size, min_meta_per, min_raw_per);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_buf_size, h5_datatype[DT_size_t]);
  R_buf_size = PROTECT(H5ToR_single_step(buf_size, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_min_meta_per, h5_datatype[DT_unsigned]);
  R_min_meta_per = PROTECT(H5ToR_single_step(min_meta_per, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_min_raw_per, h5_datatype[DT_unsigned]);
  R_min_raw_per = PROTECT(H5ToR_single_step(min_raw_per, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 4));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buf_size);
  SET_VECTOR_ELT(__ret_list, 2, R_min_meta_per);
  SET_VECTOR_ELT(__ret_list, 3, R_min_raw_per);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 4));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buf_size"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("min_meta_per"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("min_raw_per"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL int H5Pget_preserve(hid_t plist_id); */
SEXP R_H5Pget_preserve(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  int return_val = H5Pget_preserve(plist_id);
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

/* H5_DLL herr_t H5Pget_shared_mesg_index(hid_t plist_id, unsigned index_num, unsigned *mesg_type_flags, unsigned *min_mesg_size); */
SEXP R_H5Pget_shared_mesg_index(SEXP R_plist_id, SEXP R_index_num, SEXP R_mesg_type_flags, SEXP R_min_mesg_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_mesg_type_flags = PROTECT(duplicate(R_mesg_type_flags));
  vars_protected++;
  R_min_mesg_size = PROTECT(duplicate(R_min_mesg_size));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned index_num = SEXP_to_longlong(R_index_num, 0);
  unsigned* mesg_type_flags;
  if(XLENGTH(R_mesg_type_flags) == 0) {
    mesg_type_flags = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_mesg_type_flags, h5_datatype[DT_unsigned], XLENGTH(R_mesg_type_flags)));
    mesg_type_flags= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* min_mesg_size;
  if(XLENGTH(R_min_mesg_size) == 0) {
    min_mesg_size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_min_mesg_size, h5_datatype[DT_unsigned], XLENGTH(R_min_mesg_size)));
    min_mesg_size= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_shared_mesg_index(plist_id, index_num, mesg_type_flags, min_mesg_size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_mesg_type_flags, h5_datatype[DT_unsigned]);
  R_mesg_type_flags = PROTECT(H5ToR_single_step(mesg_type_flags, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_min_mesg_size, h5_datatype[DT_unsigned]);
  R_min_mesg_size = PROTECT(H5ToR_single_step(min_mesg_size, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_mesg_type_flags);
  SET_VECTOR_ELT(__ret_list, 2, R_min_mesg_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("mesg_type_flags"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("min_mesg_size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_shared_mesg_nindexes(hid_t plist_id, unsigned *nindexes); */
SEXP R_H5Pget_shared_mesg_nindexes(SEXP R_plist_id, SEXP R_nindexes){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_nindexes = PROTECT(duplicate(R_nindexes));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* nindexes;
  if(XLENGTH(R_nindexes) == 0) {
    nindexes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_nindexes, h5_datatype[DT_unsigned], XLENGTH(R_nindexes)));
    nindexes= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_shared_mesg_nindexes(plist_id, nindexes);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_nindexes, h5_datatype[DT_unsigned]);
  R_nindexes = PROTECT(H5ToR_single_step(nindexes, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_nindexes);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("nindexes"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_shared_mesg_phase_change(hid_t plist_id, unsigned *max_list, unsigned *min_btree); */
SEXP R_H5Pget_shared_mesg_phase_change(SEXP R_plist_id, SEXP R_max_list, SEXP R_min_btree){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_max_list = PROTECT(duplicate(R_max_list));
  vars_protected++;
  R_min_btree = PROTECT(duplicate(R_min_btree));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* max_list;
  if(XLENGTH(R_max_list) == 0) {
    max_list = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_max_list, h5_datatype[DT_unsigned], XLENGTH(R_max_list)));
    max_list= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* min_btree;
  if(XLENGTH(R_min_btree) == 0) {
    min_btree = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_min_btree, h5_datatype[DT_unsigned], XLENGTH(R_min_btree)));
    min_btree= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_shared_mesg_phase_change(plist_id, max_list, min_btree);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_max_list, h5_datatype[DT_unsigned]);
  R_max_list = PROTECT(H5ToR_single_step(max_list, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_min_btree, h5_datatype[DT_unsigned]);
  R_min_btree = PROTECT(H5ToR_single_step(min_btree, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_max_list);
  SET_VECTOR_ELT(__ret_list, 2, R_min_btree);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("max_list"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("min_btree"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_sieve_buf_size(hid_t fapl_id, size_t *size); */
SEXP R_H5Pget_sieve_buf_size(SEXP R_fapl_id, SEXP R_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_size = PROTECT(duplicate(R_size));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  size_t* size;
  if(XLENGTH(R_size) == 0) {
    size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_size, h5_datatype[DT_size_t], XLENGTH(R_size)));
    size= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_sieve_buf_size(fapl_id, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_size, h5_datatype[DT_size_t]);
  R_size = PROTECT(H5ToR_single_step(size, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_size(hid_t id, const char *name, size_t *size); */
SEXP R_H5Pget_size(SEXP R_id, SEXP R_name, SEXP R_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_size = PROTECT(duplicate(R_size));
  vars_protected++;
  hid_t id = SEXP_to_longlong(R_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  size_t* size;
  if(XLENGTH(R_size) == 0) {
    size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_size, h5_datatype[DT_size_t], XLENGTH(R_size)));
    size= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_size(id, name, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_size, h5_datatype[DT_size_t]);
  R_size = PROTECT(H5ToR_single_step(size, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_sizes(hid_t plist_id, size_t *sizeof_addr, size_t *sizeof_size); */
SEXP R_H5Pget_sizes(SEXP R_plist_id, SEXP R_sizeof_addr, SEXP R_sizeof_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_sizeof_addr = PROTECT(duplicate(R_sizeof_addr));
  vars_protected++;
  R_sizeof_size = PROTECT(duplicate(R_sizeof_size));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  size_t* sizeof_addr;
  if(XLENGTH(R_sizeof_addr) == 0) {
    sizeof_addr = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_sizeof_addr, h5_datatype[DT_size_t], XLENGTH(R_sizeof_addr)));
    sizeof_addr= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* sizeof_size;
  if(XLENGTH(R_sizeof_size) == 0) {
    sizeof_size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_sizeof_size, h5_datatype[DT_size_t], XLENGTH(R_sizeof_size)));
    sizeof_size= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_sizes(plist_id, sizeof_addr, sizeof_size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_sizeof_addr, h5_datatype[DT_size_t]);
  R_sizeof_addr = PROTECT(H5ToR_single_step(sizeof_addr, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_sizeof_size, h5_datatype[DT_size_t]);
  R_sizeof_size = PROTECT(H5ToR_single_step(sizeof_size, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_sizeof_addr);
  SET_VECTOR_ELT(__ret_list, 2, R_sizeof_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("sizeof_addr"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("sizeof_size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_small_data_block_size(hid_t fapl_id, hsize_t *size); */
SEXP R_H5Pget_small_data_block_size(SEXP R_fapl_id, SEXP R_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_size = PROTECT(duplicate(R_size));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hsize_t* size;
  if(XLENGTH(R_size) == 0) {
    size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_size, h5_datatype[DT_hsize_t], XLENGTH(R_size)));
    size= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_small_data_block_size(fapl_id, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_size, h5_datatype[DT_hsize_t]);
  R_size = PROTECT(H5ToR_single_step(size, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_sym_k(hid_t plist_id, unsigned *ik, unsigned *lk); */
SEXP R_H5Pget_sym_k(SEXP R_plist_id, SEXP R_ik, SEXP R_lk){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_ik = PROTECT(duplicate(R_ik));
  vars_protected++;
  R_lk = PROTECT(duplicate(R_lk));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* ik;
  if(XLENGTH(R_ik) == 0) {
    ik = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_ik, h5_datatype[DT_unsigned], XLENGTH(R_ik)));
    ik= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* lk;
  if(XLENGTH(R_lk) == 0) {
    lk = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_lk, h5_datatype[DT_unsigned], XLENGTH(R_lk)));
    lk= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_sym_k(plist_id, ik, lk);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_ik, h5_datatype[DT_unsigned]);
  R_ik = PROTECT(H5ToR_single_step(ik, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_lk, h5_datatype[DT_unsigned]);
  R_lk = PROTECT(H5ToR_single_step(lk, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_ik);
  SET_VECTOR_ELT(__ret_list, 2, R_lk);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("ik"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("lk"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_userblock(hid_t plist_id, hsize_t *size); */
SEXP R_H5Pget_userblock(SEXP R_plist_id, SEXP R_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_size = PROTECT(duplicate(R_size));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hsize_t* size;
  if(XLENGTH(R_size) == 0) {
    size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_size, h5_datatype[DT_hsize_t], XLENGTH(R_size)));
    size= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_userblock(plist_id, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_size, h5_datatype[DT_hsize_t]);
  R_size = PROTECT(H5ToR_single_step(size, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_version(hid_t plist_id, unsigned *boot, unsigned *freelist, unsigned *stab, unsigned *shhdr); */
SEXP R_H5Pget_version(SEXP R_plist_id, SEXP R_boot, SEXP R_freelist, SEXP R_stab, SEXP R_shhdr){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_boot = PROTECT(duplicate(R_boot));
  vars_protected++;
  R_freelist = PROTECT(duplicate(R_freelist));
  vars_protected++;
  R_stab = PROTECT(duplicate(R_stab));
  vars_protected++;
  R_shhdr = PROTECT(duplicate(R_shhdr));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned* boot;
  if(XLENGTH(R_boot) == 0) {
    boot = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_boot, h5_datatype[DT_unsigned], XLENGTH(R_boot)));
    boot= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* freelist;
  if(XLENGTH(R_freelist) == 0) {
    freelist = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_freelist, h5_datatype[DT_unsigned], XLENGTH(R_freelist)));
    freelist= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* stab;
  if(XLENGTH(R_stab) == 0) {
    stab = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_stab, h5_datatype[DT_unsigned], XLENGTH(R_stab)));
    stab= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* shhdr;
  if(XLENGTH(R_shhdr) == 0) {
    shhdr = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_shhdr, h5_datatype[DT_unsigned], XLENGTH(R_shhdr)));
    shhdr= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_version(plist_id, boot, freelist, stab, shhdr);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_boot, h5_datatype[DT_unsigned]);
  R_boot = PROTECT(H5ToR_single_step(boot, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_freelist, h5_datatype[DT_unsigned]);
  R_freelist = PROTECT(H5ToR_single_step(freelist, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_stab, h5_datatype[DT_unsigned]);
  R_stab = PROTECT(H5ToR_single_step(stab, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_shhdr, h5_datatype[DT_unsigned]);
  R_shhdr = PROTECT(H5ToR_single_step(shhdr, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 5));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_boot);
  SET_VECTOR_ELT(__ret_list, 2, R_freelist);
  SET_VECTOR_ELT(__ret_list, 3, R_stab);
  SET_VECTOR_ELT(__ret_list, 4, R_shhdr);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 5));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("boot"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("freelist"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("stab"));
  SET_STRING_ELT(__ret_list_names, 4, mkChar("shhdr"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_virtual_count(hid_t dcpl_id, size_t *count); */
SEXP R_H5Pget_virtual_count(SEXP R_dcpl_id, SEXP R_count){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_count = PROTECT(duplicate(R_count));
  vars_protected++;
  hid_t dcpl_id = SEXP_to_longlong(R_dcpl_id, 0);
  size_t* count;
  if(XLENGTH(R_count) == 0) {
    count = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_count, h5_datatype[DT_size_t], XLENGTH(R_count)));
    count= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_virtual_count(dcpl_id, count);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_count, h5_datatype[DT_size_t]);
  R_count = PROTECT(H5ToR_single_step(count, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_count);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("count"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL ssize_t H5Pget_virtual_dsetname(hid_t dcpl_id, size_t index, char *name, size_t size); */
SEXP R_H5Pget_virtual_dsetname(SEXP R_dcpl_id, SEXP R_index, SEXP R_name, SEXP R_size){
  int vars_protected=0;
  R_name = PROTECT(duplicate(R_name));
  vars_protected++;
  hid_t dcpl_id = SEXP_to_longlong(R_dcpl_id, 0);
  size_t index = SEXP_to_longlong(R_index, 0);
  char* name;
  if(XLENGTH(R_name) == 0) {
    name = NULL;
  }
  else {
    name = R_alloc(strlen(CHAR(STRING_ELT(R_name, 0))) + 1, 1);
    strcpy(name, CHAR(STRING_ELT(R_name, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  ssize_t return_val = H5Pget_virtual_dsetname(dcpl_id, index, name, size);
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

/* H5_DLL ssize_t H5Pget_virtual_filename(hid_t dcpl_id, size_t index, char *name, size_t size); */
SEXP R_H5Pget_virtual_filename(SEXP R_dcpl_id, SEXP R_index, SEXP R_name, SEXP R_size){
  int vars_protected=0;
  R_name = PROTECT(duplicate(R_name));
  vars_protected++;
  hid_t dcpl_id = SEXP_to_longlong(R_dcpl_id, 0);
  size_t index = SEXP_to_longlong(R_index, 0);
  char* name;
  if(XLENGTH(R_name) == 0) {
    name = NULL;
  }
  else {
    name = R_alloc(strlen(CHAR(STRING_ELT(R_name, 0))) + 1, 1);
    strcpy(name, CHAR(STRING_ELT(R_name, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  ssize_t return_val = H5Pget_virtual_filename(dcpl_id, index, name, size);
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

/* H5_DLL ssize_t H5Pget_virtual_prefix(hid_t dapl_id, char* prefix , size_t size); */
SEXP R_H5Pget_virtual_prefix(SEXP R_dapl_id, SEXP R_prefix, SEXP R_size){
  int vars_protected=0;
  R_prefix = PROTECT(duplicate(R_prefix));
  vars_protected++;
  hid_t dapl_id = SEXP_to_longlong(R_dapl_id, 0);
  char* prefix;
  if(XLENGTH(R_prefix) == 0) {
    prefix = NULL;
  }
  else {
    prefix = R_alloc(strlen(CHAR(STRING_ELT(R_prefix, 0))) + 1, 1);
    strcpy(prefix, CHAR(STRING_ELT(R_prefix, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  ssize_t return_val = H5Pget_virtual_prefix(dapl_id, prefix, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(prefix==NULL) {
    R_prefix = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_prefix = PROTECT(mkString(prefix));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_prefix);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("prefix"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pget_virtual_printf_gap(hid_t plist_id, hsize_t *gap_size); */
SEXP R_H5Pget_virtual_printf_gap(SEXP R_plist_id, SEXP R_gap_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_gap_size = PROTECT(duplicate(R_gap_size));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hsize_t* gap_size;
  if(XLENGTH(R_gap_size) == 0) {
    gap_size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_gap_size, h5_datatype[DT_hsize_t], XLENGTH(R_gap_size)));
    gap_size= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_virtual_printf_gap(plist_id, gap_size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_gap_size, h5_datatype[DT_hsize_t]);
  R_gap_size = PROTECT(H5ToR_single_step(gap_size, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_gap_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("gap_size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Pget_virtual_srcspace(hid_t dcpl_id, size_t index); */
SEXP R_H5Pget_virtual_srcspace(SEXP R_dcpl_id, SEXP R_index){
  int vars_protected=0;
  hid_t dcpl_id = SEXP_to_longlong(R_dcpl_id, 0);
  size_t index = SEXP_to_longlong(R_index, 0);
  hid_t return_val = H5Pget_virtual_srcspace(dcpl_id, index);
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

/* H5_DLL herr_t H5Pget_virtual_view(hid_t plist_id, H5D_vds_view_t *view); */
SEXP R_H5Pget_virtual_view(SEXP R_plist_id, SEXP R_view){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_view = PROTECT(duplicate(R_view));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5D_vds_view_t* view;
  if(XLENGTH(R_view) == 0) {
    view = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_view, h5_datatype[DT_H5D_vds_view_t], XLENGTH(R_view)));
    view= (H5D_vds_view_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_virtual_view(plist_id, view);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_view, h5_datatype[DT_H5D_vds_view_t]);
  R_view = PROTECT(H5ToR_single_step(view, h5_datatype[DT_H5D_vds_view_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_view);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("view"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Pget_virtual_vspace(hid_t dcpl_id, size_t index); */
SEXP R_H5Pget_virtual_vspace(SEXP R_dcpl_id, SEXP R_index){
  int vars_protected=0;
  hid_t dcpl_id = SEXP_to_longlong(R_dcpl_id, 0);
  size_t index = SEXP_to_longlong(R_index, 0);
  hid_t return_val = H5Pget_virtual_vspace(dcpl_id, index);
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

/* H5_DLL herr_t H5Pget_vol_id(hid_t plist_id, hid_t *vol_id); */
SEXP R_H5Pget_vol_id(SEXP R_plist_id, SEXP R_vol_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_vol_id = PROTECT(duplicate(R_vol_id));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hid_t* vol_id;
  if(XLENGTH(R_vol_id) == 0) {
    vol_id = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_vol_id, h5_datatype[DT_hid_t], XLENGTH(R_vol_id)));
    vol_id= (hid_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_vol_id(plist_id, vol_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_vol_id, h5_datatype[DT_hid_t]);
  R_vol_id = PROTECT(H5ToR_single_step(vol_id, h5_datatype[DT_hid_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_vol_id);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("vol_id"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL htri_t H5Pisa_class(hid_t plist_id, hid_t pclass_id); */
SEXP R_H5Pisa_class(SEXP R_plist_id, SEXP R_pclass_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hid_t pclass_id = SEXP_to_longlong(R_pclass_id, 0);
  htri_t return_val = H5Pisa_class(plist_id, pclass_id);
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

/* H5_DLL herr_t H5Pmodify_filter(hid_t plist_id, H5Z_filter_t filter, unsigned int flags, size_t cd_nelmts, const unsigned int cd_values[]); */
SEXP R_H5Pmodify_filter(SEXP R_plist_id, SEXP R_filter, SEXP R_flags, SEXP R_cd_nelmts, SEXP R_cd_values){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5Z_filter_t filter = SEXP_to_longlong(R_filter, 0);
  unsigned int flags = SEXP_to_longlong(R_flags, 0);
  size_t cd_nelmts = SEXP_to_longlong(R_cd_nelmts, 0);
  const unsigned int* cd_values;
  if(XLENGTH(R_cd_values) == 0) {
    cd_values = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_cd_values, h5_datatype[DT_unsigned_int], XLENGTH(R_cd_values)));
    cd_values= (const unsigned int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pmodify_filter(plist_id, filter, flags, cd_nelmts, cd_values);
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

/* H5_DLL herr_t H5Premove(hid_t plist_id, const char *name); */
SEXP R_H5Premove(SEXP R_plist_id, SEXP R_name){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  herr_t return_val = H5Premove(plist_id, name);
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

/* H5_DLL herr_t H5Premove_filter(hid_t plist_id, H5Z_filter_t filter); */
SEXP R_H5Premove_filter(SEXP R_plist_id, SEXP R_filter){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5Z_filter_t filter = SEXP_to_longlong(R_filter, 0);
  herr_t return_val = H5Premove_filter(plist_id, filter);
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

/* H5_DLL herr_t H5Pset(hid_t plist_id, const char *name, const void *value); */
SEXP R_H5Pset(SEXP R_plist_id, SEXP R_name, SEXP R_value){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  const void* value;
  if(XLENGTH(R_value) == 0) {
    value = NULL;
  }
  else {
    value = (void *) VOIDPTR(R_value);
  }
  herr_t return_val = H5Pset(plist_id, name, value);
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

/* H5_DLL herr_t H5Pset_alignment(hid_t fapl_id, hsize_t threshold, hsize_t alignment); */
SEXP R_H5Pset_alignment(SEXP R_fapl_id, SEXP R_threshold, SEXP R_alignment){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hsize_t threshold = SEXP_to_longlong(R_threshold, 0);
  hsize_t alignment = SEXP_to_longlong(R_alignment, 0);
  herr_t return_val = H5Pset_alignment(fapl_id, threshold, alignment);
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

/* H5_DLL herr_t H5Pset_alloc_time(hid_t plist_id, H5D_alloc_time_t alloc_time); */
SEXP R_H5Pset_alloc_time(SEXP R_plist_id, SEXP R_alloc_time){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5D_alloc_time_t alloc_time = SEXP_to_longlong(R_alloc_time, 0);
  herr_t return_val = H5Pset_alloc_time(plist_id, alloc_time);
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

/* H5_DLL herr_t H5Pset_attr_creation_order(hid_t plist_id, unsigned crt_order_flags); */
SEXP R_H5Pset_attr_creation_order(SEXP R_plist_id, SEXP R_crt_order_flags){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned crt_order_flags = SEXP_to_longlong(R_crt_order_flags, 0);
  herr_t return_val = H5Pset_attr_creation_order(plist_id, crt_order_flags);
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

/* H5_DLL herr_t H5Pset_attr_phase_change(hid_t plist_id, unsigned max_compact, unsigned min_dense); */
SEXP R_H5Pset_attr_phase_change(SEXP R_plist_id, SEXP R_max_compact, SEXP R_min_dense){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned max_compact = SEXP_to_longlong(R_max_compact, 0);
  unsigned min_dense = SEXP_to_longlong(R_min_dense, 0);
  herr_t return_val = H5Pset_attr_phase_change(plist_id, max_compact, min_dense);
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

/* H5_DLL herr_t H5Pset_btree_ratios(hid_t plist_id, double left, double middle, double right); */
SEXP R_H5Pset_btree_ratios(SEXP R_plist_id, SEXP R_left, SEXP R_middle, SEXP R_right){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  double left = SEXP_to_double(R_left);
  double middle = SEXP_to_double(R_middle);
  double right = SEXP_to_double(R_right);
  herr_t return_val = H5Pset_btree_ratios(plist_id, left, middle, right);
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

/* H5_DLL herr_t H5Pset_buffer(hid_t plist_id, size_t size, void *tconv, void *bkg); */
SEXP R_H5Pset_buffer(SEXP R_plist_id, SEXP R_size, SEXP R_tconv, SEXP R_bkg, SEXP _dupl_tconv, SEXP _dupl_bkg){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_tconv)) {
    R_tconv = PROTECT(duplicate(R_tconv));
    vars_protected++;
  }
  if(SEXP_to_logical(_dupl_bkg)) {
    R_bkg = PROTECT(duplicate(R_bkg));
    vars_protected++;
  }
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  size_t size = SEXP_to_longlong(R_size, 0);
  void* tconv;
  if(XLENGTH(R_tconv) == 0) {
    tconv = NULL;
  }
  else {
    tconv = (void *) VOIDPTR(R_tconv);
  }
  void* bkg;
  if(XLENGTH(R_bkg) == 0) {
    bkg = NULL;
  }
  else {
    bkg = (void *) VOIDPTR(R_bkg);
  }
  herr_t return_val = H5Pset_buffer(plist_id, size, tconv, bkg);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_tconv);
  SET_VECTOR_ELT(__ret_list, 2, R_bkg);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("tconv"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("bkg"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pset_cache(hid_t plist_id, int mdc_nelmts, size_t rdcc_nslots, size_t rdcc_nbytes, double rdcc_w0); */
SEXP R_H5Pset_cache(SEXP R_plist_id, SEXP R_mdc_nelmts, SEXP R_rdcc_nslots, SEXP R_rdcc_nbytes, SEXP R_rdcc_w0){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  int mdc_nelmts = SEXP_to_longlong(R_mdc_nelmts, 0);
  size_t rdcc_nslots = SEXP_to_longlong(R_rdcc_nslots, 0);
  size_t rdcc_nbytes = SEXP_to_longlong(R_rdcc_nbytes, 0);
  double rdcc_w0 = SEXP_to_double(R_rdcc_w0);
  herr_t return_val = H5Pset_cache(plist_id, mdc_nelmts, rdcc_nslots, rdcc_nbytes, rdcc_w0);
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

/* H5_DLL herr_t H5Pset_char_encoding(hid_t plist_id, H5T_cset_t encoding); */
SEXP R_H5Pset_char_encoding(SEXP R_plist_id, SEXP R_encoding){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5T_cset_t encoding = SEXP_to_longlong(R_encoding, 0);
  herr_t return_val = H5Pset_char_encoding(plist_id, encoding);
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

/* H5_DLL herr_t H5Pset_chunk(hid_t plist_id, int ndims, const hsize_t dim[]); */
SEXP R_H5Pset_chunk(SEXP R_plist_id, SEXP R_ndims, SEXP R_dim){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  int ndims = SEXP_to_longlong(R_ndims, 0);
  const hsize_t* dim;
  if(XLENGTH(R_dim) == 0) {
    dim = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dim, h5_datatype[DT_hsize_t], XLENGTH(R_dim)));
    dim= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pset_chunk(plist_id, ndims, dim);
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

/* H5_DLL herr_t H5Pset_chunk_cache(hid_t dapl_id, size_t rdcc_nslots, size_t rdcc_nbytes, double rdcc_w0); */
SEXP R_H5Pset_chunk_cache(SEXP R_dapl_id, SEXP R_rdcc_nslots, SEXP R_rdcc_nbytes, SEXP R_rdcc_w0){
  int vars_protected=0;
  hid_t dapl_id = SEXP_to_longlong(R_dapl_id, 0);
  size_t rdcc_nslots = SEXP_to_longlong(R_rdcc_nslots, 0);
  size_t rdcc_nbytes = SEXP_to_longlong(R_rdcc_nbytes, 0);
  double rdcc_w0 = SEXP_to_double(R_rdcc_w0);
  // INJECTION CODE START
  if(SEXP_to_longlong(R_rdcc_nslots, 0)==-1) {
    rdcc_nslots = H5D_CHUNK_CACHE_NSLOTS_DEFAULT;
  }
  if(SEXP_to_longlong(R_rdcc_nbytes, 0)==-1) {
    rdcc_nbytes = H5D_CHUNK_CACHE_NBYTES_DEFAULT;
  }
  if(SEXP_to_longlong(R_rdcc_w0, 0)==-1) {
    rdcc_w0 = H5D_CHUNK_CACHE_W0_DEFAULT;
  }
  // INJECTION CODE END
  herr_t return_val = H5Pset_chunk_cache(dapl_id, rdcc_nslots, rdcc_nbytes, rdcc_w0);
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

/* H5_DLL herr_t H5Pset_chunk_opts(hid_t plist_id, unsigned opts); */
SEXP R_H5Pset_chunk_opts(SEXP R_plist_id, SEXP R_opts){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned opts = SEXP_to_longlong(R_opts, 0);
  herr_t return_val = H5Pset_chunk_opts(plist_id, opts);
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

/* H5_DLL herr_t H5Pset_copy_object(hid_t plist_id, unsigned crt_intmd); */
SEXP R_H5Pset_copy_object(SEXP R_plist_id, SEXP R_crt_intmd){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned crt_intmd = SEXP_to_longlong(R_crt_intmd, 0);
  herr_t return_val = H5Pset_copy_object(plist_id, crt_intmd);
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

/* H5_DLL herr_t H5Pset_core_write_tracking(hid_t fapl_id, hbool_t is_enabled, size_t page_size); */
SEXP R_H5Pset_core_write_tracking(SEXP R_fapl_id, SEXP R_is_enabled, SEXP R_page_size){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hbool_t is_enabled = SEXP_to_longlong(R_is_enabled, 0);
  size_t page_size = SEXP_to_longlong(R_page_size, 0);
  herr_t return_val = H5Pset_core_write_tracking(fapl_id, is_enabled, page_size);
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

/* H5_DLL herr_t H5Pset_create_intermediate_group(hid_t plist_id, unsigned crt_intmd); */
SEXP R_H5Pset_create_intermediate_group(SEXP R_plist_id, SEXP R_crt_intmd){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned crt_intmd = SEXP_to_longlong(R_crt_intmd, 0);
  herr_t return_val = H5Pset_create_intermediate_group(plist_id, crt_intmd);
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

/* H5_DLL herr_t H5Pset_data_transform(hid_t plist_id, const char* expression); */
SEXP R_H5Pset_data_transform(SEXP R_plist_id, SEXP R_expression){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  const char* expression = CHAR(STRING_ELT(R_expression, 0));
  herr_t return_val = H5Pset_data_transform(plist_id, expression);
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

/* H5_DLL herr_t H5Pset_deflate(hid_t plist_id, unsigned aggression); */
SEXP R_H5Pset_deflate(SEXP R_plist_id, SEXP R_aggression){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned aggression = SEXP_to_longlong(R_aggression, 0);
  herr_t return_val = H5Pset_deflate(plist_id, aggression);
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

/* H5_DLL herr_t H5Pset_driver(hid_t plist_id, hid_t driver_id, const void *driver_info); */
SEXP R_H5Pset_driver(SEXP R_plist_id, SEXP R_driver_id, SEXP R_driver_info){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hid_t driver_id = SEXP_to_longlong(R_driver_id, 0);
  const void* driver_info;
  if(XLENGTH(R_driver_info) == 0) {
    driver_info = NULL;
  }
  else {
    driver_info = (void *) VOIDPTR(R_driver_info);
  }
  herr_t return_val = H5Pset_driver(plist_id, driver_id, driver_info);
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

/* H5_DLL herr_t H5Pset_dset_no_attrs_hint(hid_t dcpl_id, hbool_t minimize); */
SEXP R_H5Pset_dset_no_attrs_hint(SEXP R_dcpl_id, SEXP R_minimize){
  int vars_protected=0;
  hid_t dcpl_id = SEXP_to_longlong(R_dcpl_id, 0);
  hbool_t minimize = SEXP_to_longlong(R_minimize, 0);
  herr_t return_val = H5Pset_dset_no_attrs_hint(dcpl_id, minimize);
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

/* H5_DLL herr_t H5Pset_edc_check(hid_t plist_id, H5Z_EDC_t check); */
SEXP R_H5Pset_edc_check(SEXP R_plist_id, SEXP R_check){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5Z_EDC_t check = SEXP_to_longlong(R_check, 0);
  herr_t return_val = H5Pset_edc_check(plist_id, check);
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

/* H5_DLL herr_t H5Pset_efile_prefix(hid_t dapl_id, const char* prefix); */
SEXP R_H5Pset_efile_prefix(SEXP R_dapl_id, SEXP R_prefix){
  int vars_protected=0;
  hid_t dapl_id = SEXP_to_longlong(R_dapl_id, 0);
  const char* prefix = CHAR(STRING_ELT(R_prefix, 0));
  herr_t return_val = H5Pset_efile_prefix(dapl_id, prefix);
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

/* H5_DLL herr_t H5Pset_elink_acc_flags(hid_t lapl_id, unsigned flags); */
SEXP R_H5Pset_elink_acc_flags(SEXP R_lapl_id, SEXP R_flags){
  int vars_protected=0;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  unsigned flags = SEXP_to_longlong(R_flags, 0);
  herr_t return_val = H5Pset_elink_acc_flags(lapl_id, flags);
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

/* H5_DLL herr_t H5Pset_elink_fapl(hid_t lapl_id, hid_t fapl_id); */
SEXP R_H5Pset_elink_fapl(SEXP R_lapl_id, SEXP R_fapl_id){
  int vars_protected=0;
  hid_t lapl_id = SEXP_to_longlong(R_lapl_id, 0);
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  herr_t return_val = H5Pset_elink_fapl(lapl_id, fapl_id);
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

/* H5_DLL herr_t H5Pset_elink_file_cache_size(hid_t plist_id, unsigned efc_size); */
SEXP R_H5Pset_elink_file_cache_size(SEXP R_plist_id, SEXP R_efc_size){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned efc_size = SEXP_to_longlong(R_efc_size, 0);
  herr_t return_val = H5Pset_elink_file_cache_size(plist_id, efc_size);
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

/* H5_DLL herr_t H5Pset_elink_prefix(hid_t plist_id, const char *prefix); */
SEXP R_H5Pset_elink_prefix(SEXP R_plist_id, SEXP R_prefix){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  const char* prefix = CHAR(STRING_ELT(R_prefix, 0));
  herr_t return_val = H5Pset_elink_prefix(plist_id, prefix);
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

/* H5_DLL herr_t H5Pset_est_link_info(hid_t plist_id, unsigned est_num_entries, unsigned est_name_len); */
SEXP R_H5Pset_est_link_info(SEXP R_plist_id, SEXP R_est_num_entries, SEXP R_est_name_len){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned est_num_entries = SEXP_to_longlong(R_est_num_entries, 0);
  unsigned est_name_len = SEXP_to_longlong(R_est_name_len, 0);
  herr_t return_val = H5Pset_est_link_info(plist_id, est_num_entries, est_name_len);
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

/* H5_DLL herr_t H5Pset_evict_on_close(hid_t fapl_id, hbool_t evict_on_close); */
SEXP R_H5Pset_evict_on_close(SEXP R_fapl_id, SEXP R_evict_on_close){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hbool_t evict_on_close = SEXP_to_longlong(R_evict_on_close, 0);
  herr_t return_val = H5Pset_evict_on_close(fapl_id, evict_on_close);
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

/* H5_DLL herr_t H5Pset_external(hid_t plist_id, const char *name, off_t offset, hsize_t size); */
SEXP R_H5Pset_external(SEXP R_plist_id, SEXP R_name, SEXP R_offset, SEXP R_size){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  off_t offset = SEXP_to_longlong(R_offset, 0);
  hsize_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5Pset_external(plist_id, name, offset, size);
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

/* H5_DLL herr_t H5Pset_family_offset(hid_t fapl_id, hsize_t offset); */
SEXP R_H5Pset_family_offset(SEXP R_fapl_id, SEXP R_offset){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hsize_t offset = SEXP_to_longlong(R_offset, 0);
  herr_t return_val = H5Pset_family_offset(fapl_id, offset);
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

/* H5_DLL herr_t H5Pset_fclose_degree(hid_t fapl_id, H5F_close_degree_t degree); */
SEXP R_H5Pset_fclose_degree(SEXP R_fapl_id, SEXP R_degree){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  H5F_close_degree_t degree = SEXP_to_longlong(R_degree, 0);
  herr_t return_val = H5Pset_fclose_degree(fapl_id, degree);
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

/* H5_DLL herr_t H5Pset_file_image(hid_t fapl_id, void *buf_ptr, size_t buf_len); */
SEXP R_H5Pset_file_image(SEXP R_fapl_id, SEXP R_buf_ptr, SEXP R_buf_len, SEXP _dupl_buf_ptr){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf_ptr)) {
    R_buf_ptr = PROTECT(duplicate(R_buf_ptr));
    vars_protected++;
  }
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  void* buf_ptr;
  if(XLENGTH(R_buf_ptr) == 0) {
    buf_ptr = NULL;
  }
  else {
    buf_ptr = (void *) VOIDPTR(R_buf_ptr);
  }
  size_t buf_len = SEXP_to_longlong(R_buf_len, 0);
  herr_t return_val = H5Pset_file_image(fapl_id, buf_ptr, buf_len);
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

/* H5_DLL herr_t H5Pset_file_space(hid_t plist_id, H5F_file_space_type_t strategy, hsize_t threshold); */
SEXP R_H5Pset_file_space(SEXP R_plist_id, SEXP R_strategy, SEXP R_threshold){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5F_file_space_type_t strategy = SEXP_to_longlong(R_strategy, 0);
  hsize_t threshold = SEXP_to_longlong(R_threshold, 0);
  herr_t return_val = H5Pset_file_space(plist_id, strategy, threshold);
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

/* H5_DLL herr_t H5Pset_file_space_page_size(hid_t plist_id, hsize_t fsp_size); */
SEXP R_H5Pset_file_space_page_size(SEXP R_plist_id, SEXP R_fsp_size){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hsize_t fsp_size = SEXP_to_longlong(R_fsp_size, 0);
  herr_t return_val = H5Pset_file_space_page_size(plist_id, fsp_size);
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

/* H5_DLL herr_t H5Pset_file_space_strategy(hid_t plist_id, H5F_fspace_strategy_t strategy, hbool_t persist, hsize_t threshold); */
SEXP R_H5Pset_file_space_strategy(SEXP R_plist_id, SEXP R_strategy, SEXP R_persist, SEXP R_threshold){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5F_fspace_strategy_t strategy = SEXP_to_longlong(R_strategy, 0);
  hbool_t persist = SEXP_to_longlong(R_persist, 0);
  hsize_t threshold = SEXP_to_longlong(R_threshold, 0);
  herr_t return_val = H5Pset_file_space_strategy(plist_id, strategy, persist, threshold);
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

/* H5_DLL herr_t H5Pset_fill_time(hid_t plist_id, H5D_fill_time_t fill_time); */
SEXP R_H5Pset_fill_time(SEXP R_plist_id, SEXP R_fill_time){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5D_fill_time_t fill_time = SEXP_to_longlong(R_fill_time, 0);
  herr_t return_val = H5Pset_fill_time(plist_id, fill_time);
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

/* H5_DLL herr_t H5Pset_fill_value(hid_t plist_id, hid_t type_id, const void *value); */
SEXP R_H5Pset_fill_value(SEXP R_plist_id, SEXP R_type_id, SEXP R_value){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  const void* value;
  if(XLENGTH(R_value) == 0) {
    value = NULL;
  }
  else {
    value = (void *) VOIDPTR(R_value);
  }
  herr_t return_val = H5Pset_fill_value(plist_id, type_id, value);
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

/* H5_DLL herr_t H5Pset_filter(hid_t plist_id, H5Z_filter_t filter, unsigned int flags, size_t cd_nelmts, const unsigned int c_values[]); */
SEXP R_H5Pset_filter(SEXP R_plist_id, SEXP R_filter, SEXP R_flags, SEXP R_cd_nelmts, SEXP R_c_values){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5Z_filter_t filter = SEXP_to_longlong(R_filter, 0);
  unsigned int flags = SEXP_to_longlong(R_flags, 0);
  size_t cd_nelmts = SEXP_to_longlong(R_cd_nelmts, 0);
  const unsigned int* c_values;
  if(XLENGTH(R_c_values) == 0) {
    c_values = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_c_values, h5_datatype[DT_unsigned_int], XLENGTH(R_c_values)));
    c_values= (const unsigned int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pset_filter(plist_id, filter, flags, cd_nelmts, c_values);
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

/* H5_DLL herr_t H5Pset_fletcher32(hid_t plist_id); */
SEXP R_H5Pset_fletcher32(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  herr_t return_val = H5Pset_fletcher32(plist_id);
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

/* H5_DLL herr_t H5Pset_gc_references(hid_t fapl_id, unsigned gc_ref); */
SEXP R_H5Pset_gc_references(SEXP R_fapl_id, SEXP R_gc_ref){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  unsigned gc_ref = SEXP_to_longlong(R_gc_ref, 0);
  herr_t return_val = H5Pset_gc_references(fapl_id, gc_ref);
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

/* H5_DLL herr_t H5Pset_hyper_vector_size(hid_t fapl_id, size_t size); */
SEXP R_H5Pset_hyper_vector_size(SEXP R_fapl_id, SEXP R_size){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5Pset_hyper_vector_size(fapl_id, size);
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

/* H5_DLL herr_t H5Pset_istore_k(hid_t plist_id, unsigned ik); */
SEXP R_H5Pset_istore_k(SEXP R_plist_id, SEXP R_ik){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned ik = SEXP_to_longlong(R_ik, 0);
  herr_t return_val = H5Pset_istore_k(plist_id, ik);
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

/* H5_DLL herr_t H5Pset_layout(hid_t plist_id, H5D_layout_t layout); */
SEXP R_H5Pset_layout(SEXP R_plist_id, SEXP R_layout){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5D_layout_t layout = SEXP_to_longlong(R_layout, 0);
  herr_t return_val = H5Pset_layout(plist_id, layout);
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

/* H5_DLL herr_t H5Pset_libver_bounds(hid_t plist_id, H5F_libver_t low, H5F_libver_t high); */
SEXP R_H5Pset_libver_bounds(SEXP R_plist_id, SEXP R_low, SEXP R_high){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5F_libver_t low = SEXP_to_longlong(R_low, 0);
  H5F_libver_t high = SEXP_to_longlong(R_high, 0);
  herr_t return_val = H5Pset_libver_bounds(plist_id, low, high);
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

/* H5_DLL herr_t H5Pset_link_creation_order(hid_t plist_id, unsigned crt_order_flags); */
SEXP R_H5Pset_link_creation_order(SEXP R_plist_id, SEXP R_crt_order_flags){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned crt_order_flags = SEXP_to_longlong(R_crt_order_flags, 0);
  herr_t return_val = H5Pset_link_creation_order(plist_id, crt_order_flags);
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

/* H5_DLL herr_t H5Pset_link_phase_change(hid_t plist_id, unsigned max_compact, unsigned min_dense); */
SEXP R_H5Pset_link_phase_change(SEXP R_plist_id, SEXP R_max_compact, SEXP R_min_dense){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned max_compact = SEXP_to_longlong(R_max_compact, 0);
  unsigned min_dense = SEXP_to_longlong(R_min_dense, 0);
  herr_t return_val = H5Pset_link_phase_change(plist_id, max_compact, min_dense);
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

/* H5_DLL herr_t H5Pset_local_heap_size_hint(hid_t plist_id, size_t size_hint); */
SEXP R_H5Pset_local_heap_size_hint(SEXP R_plist_id, SEXP R_size_hint){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  size_t size_hint = SEXP_to_longlong(R_size_hint, 0);
  herr_t return_val = H5Pset_local_heap_size_hint(plist_id, size_hint);
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

/* H5_DLL herr_t H5Pset_mdc_config(hid_t plist_id, H5AC_cache_config_t * config_ptr); */
SEXP R_H5Pset_mdc_config(SEXP R_plist_id, SEXP R_config_ptr){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_config_ptr = PROTECT(duplicate(R_config_ptr));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  R_helper = PROTECT(RToH5(R_config_ptr, h5_datatype[DT_H5AC_cache_config_t], guess_nelem(R_config_ptr, h5_datatype[DT_H5AC_cache_config_t])));
  H5AC_cache_config_t* config_ptr= (H5AC_cache_config_t*) VOIDPTR(R_helper);
  vars_protected++;
  herr_t return_val = H5Pset_mdc_config(plist_id, config_ptr);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_config_ptr, h5_datatype[DT_H5AC_cache_config_t]);
  R_config_ptr = PROTECT(H5ToR_single_step(config_ptr, h5_datatype[DT_H5AC_cache_config_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_config_ptr);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("config_ptr"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pset_mdc_image_config(hid_t plist_id, H5AC_cache_image_config_t *config_ptr); */
SEXP R_H5Pset_mdc_image_config(SEXP R_plist_id, SEXP R_config_ptr){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_config_ptr = PROTECT(duplicate(R_config_ptr));
  vars_protected++;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  R_helper = PROTECT(RToH5(R_config_ptr, h5_datatype[DT_H5AC_cache_image_config_t], guess_nelem(R_config_ptr, h5_datatype[DT_H5AC_cache_image_config_t])));
  H5AC_cache_image_config_t* config_ptr= (H5AC_cache_image_config_t*) VOIDPTR(R_helper);
  vars_protected++;
  herr_t return_val = H5Pset_mdc_image_config(plist_id, config_ptr);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_config_ptr, h5_datatype[DT_H5AC_cache_image_config_t]);
  R_config_ptr = PROTECT(H5ToR_single_step(config_ptr, h5_datatype[DT_H5AC_cache_image_config_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_config_ptr);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("config_ptr"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pset_mdc_log_options(hid_t plist_id, hbool_t is_enabled, const char *location, hbool_t start_on_access); */
SEXP R_H5Pset_mdc_log_options(SEXP R_plist_id, SEXP R_is_enabled, SEXP R_location, SEXP R_start_on_access){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hbool_t is_enabled = SEXP_to_longlong(R_is_enabled, 0);
  const char* location = CHAR(STRING_ELT(R_location, 0));
  hbool_t start_on_access = SEXP_to_longlong(R_start_on_access, 0);
  herr_t return_val = H5Pset_mdc_log_options(plist_id, is_enabled, location, start_on_access);
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

/* H5_DLL herr_t H5Pset_meta_block_size(hid_t fapl_id, hsize_t size); */
SEXP R_H5Pset_meta_block_size(SEXP R_fapl_id, SEXP R_size){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hsize_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5Pset_meta_block_size(fapl_id, size);
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

/* H5_DLL herr_t H5Pset_metadata_read_attempts(hid_t plist_id, unsigned attempts); */
SEXP R_H5Pset_metadata_read_attempts(SEXP R_plist_id, SEXP R_attempts){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned attempts = SEXP_to_longlong(R_attempts, 0);
  herr_t return_val = H5Pset_metadata_read_attempts(plist_id, attempts);
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

/* H5_DLL herr_t H5Pset_multi_type(hid_t fapl_id, H5FD_mem_t type); */
SEXP R_H5Pset_multi_type(SEXP R_fapl_id, SEXP R_type){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  H5FD_mem_t type = SEXP_to_longlong(R_type, 0);
  herr_t return_val = H5Pset_multi_type(fapl_id, type);
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

/* H5_DLL herr_t H5Pset_nbit(hid_t plist_id); */
SEXP R_H5Pset_nbit(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  herr_t return_val = H5Pset_nbit(plist_id);
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

/* H5_DLL herr_t H5Pset_nlinks(hid_t plist_id, size_t nlinks); */
SEXP R_H5Pset_nlinks(SEXP R_plist_id, SEXP R_nlinks){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  size_t nlinks = SEXP_to_longlong(R_nlinks, 0);
  herr_t return_val = H5Pset_nlinks(plist_id, nlinks);
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

/* H5_DLL herr_t H5Pset_obj_track_times(hid_t plist_id, hbool_t track_times); */
SEXP R_H5Pset_obj_track_times(SEXP R_plist_id, SEXP R_track_times){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hbool_t track_times = SEXP_to_longlong(R_track_times, 0);
  herr_t return_val = H5Pset_obj_track_times(plist_id, track_times);
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

/* H5_DLL herr_t H5Pset_page_buffer_size(hid_t plist_id, size_t buf_size, unsigned min_meta_per, unsigned min_raw_per); */
SEXP R_H5Pset_page_buffer_size(SEXP R_plist_id, SEXP R_buf_size, SEXP R_min_meta_per, SEXP R_min_raw_per){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  size_t buf_size = SEXP_to_longlong(R_buf_size, 0);
  unsigned min_meta_per = SEXP_to_longlong(R_min_meta_per, 0);
  unsigned min_raw_per = SEXP_to_longlong(R_min_raw_per, 0);
  herr_t return_val = H5Pset_page_buffer_size(plist_id, buf_size, min_meta_per, min_raw_per);
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

/* H5_DLL herr_t H5Pset_preserve(hid_t plist_id, hbool_t status); */
SEXP R_H5Pset_preserve(SEXP R_plist_id, SEXP R_status){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hbool_t status = SEXP_to_longlong(R_status, 0);
  herr_t return_val = H5Pset_preserve(plist_id, status);
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

/* H5_DLL herr_t H5Pset_scaleoffset(hid_t plist_id, H5Z_SO_scale_type_t scale_type, int scale_factor); */
SEXP R_H5Pset_scaleoffset(SEXP R_plist_id, SEXP R_scale_type, SEXP R_scale_factor){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5Z_SO_scale_type_t scale_type = SEXP_to_longlong(R_scale_type, 0);
  int scale_factor = SEXP_to_longlong(R_scale_factor, 0);
  herr_t return_val = H5Pset_scaleoffset(plist_id, scale_type, scale_factor);
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

/* H5_DLL herr_t H5Pset_shared_mesg_index(hid_t plist_id, unsigned index_num, unsigned mesg_type_flags, unsigned min_mesg_size); */
SEXP R_H5Pset_shared_mesg_index(SEXP R_plist_id, SEXP R_index_num, SEXP R_mesg_type_flags, SEXP R_min_mesg_size){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned index_num = SEXP_to_longlong(R_index_num, 0);
  unsigned mesg_type_flags = SEXP_to_longlong(R_mesg_type_flags, 0);
  unsigned min_mesg_size = SEXP_to_longlong(R_min_mesg_size, 0);
  herr_t return_val = H5Pset_shared_mesg_index(plist_id, index_num, mesg_type_flags, min_mesg_size);
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

/* H5_DLL herr_t H5Pset_shared_mesg_nindexes(hid_t plist_id, unsigned nindexes); */
SEXP R_H5Pset_shared_mesg_nindexes(SEXP R_plist_id, SEXP R_nindexes){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned nindexes = SEXP_to_longlong(R_nindexes, 0);
  herr_t return_val = H5Pset_shared_mesg_nindexes(plist_id, nindexes);
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

/* H5_DLL herr_t H5Pset_shared_mesg_phase_change(hid_t plist_id, unsigned max_list, unsigned min_btree); */
SEXP R_H5Pset_shared_mesg_phase_change(SEXP R_plist_id, SEXP R_max_list, SEXP R_min_btree){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned max_list = SEXP_to_longlong(R_max_list, 0);
  unsigned min_btree = SEXP_to_longlong(R_min_btree, 0);
  herr_t return_val = H5Pset_shared_mesg_phase_change(plist_id, max_list, min_btree);
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

/* H5_DLL herr_t H5Pset_shuffle(hid_t plist_id); */
SEXP R_H5Pset_shuffle(SEXP R_plist_id){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  herr_t return_val = H5Pset_shuffle(plist_id);
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

/* H5_DLL herr_t H5Pset_sieve_buf_size(hid_t fapl_id, size_t size); */
SEXP R_H5Pset_sieve_buf_size(SEXP R_fapl_id, SEXP R_size){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  size_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5Pset_sieve_buf_size(fapl_id, size);
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

/* H5_DLL herr_t H5Pset_sizes(hid_t plist_id, size_t sizeof_addr, size_t sizeof_size); */
SEXP R_H5Pset_sizes(SEXP R_plist_id, SEXP R_sizeof_addr, SEXP R_sizeof_size){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  size_t sizeof_addr = SEXP_to_longlong(R_sizeof_addr, 0);
  size_t sizeof_size = SEXP_to_longlong(R_sizeof_size, 0);
  herr_t return_val = H5Pset_sizes(plist_id, sizeof_addr, sizeof_size);
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

/* H5_DLL herr_t H5Pset_small_data_block_size(hid_t fapl_id, hsize_t size); */
SEXP R_H5Pset_small_data_block_size(SEXP R_fapl_id, SEXP R_size){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hsize_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5Pset_small_data_block_size(fapl_id, size);
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

/* H5_DLL herr_t H5Pset_sym_k(hid_t plist_id, unsigned ik, unsigned lk); */
SEXP R_H5Pset_sym_k(SEXP R_plist_id, SEXP R_ik, SEXP R_lk){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned ik = SEXP_to_longlong(R_ik, 0);
  unsigned lk = SEXP_to_longlong(R_lk, 0);
  herr_t return_val = H5Pset_sym_k(plist_id, ik, lk);
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

/* H5_DLL herr_t H5Pset_szip(hid_t plist_id, unsigned options_mask, unsigned pixels_per_block); */
SEXP R_H5Pset_szip(SEXP R_plist_id, SEXP R_options_mask, SEXP R_pixels_per_block){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  unsigned options_mask = SEXP_to_longlong(R_options_mask, 0);
  unsigned pixels_per_block = SEXP_to_longlong(R_pixels_per_block, 0);
  herr_t return_val = H5Pset_szip(plist_id, options_mask, pixels_per_block);
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

/* H5_DLL herr_t H5Pset_userblock(hid_t plist_id, hsize_t size); */
SEXP R_H5Pset_userblock(SEXP R_plist_id, SEXP R_size){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hsize_t size = SEXP_to_longlong(R_size, 0);
  herr_t return_val = H5Pset_userblock(plist_id, size);
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

/* H5_DLL herr_t H5Pset_virtual(hid_t dcpl_id, hid_t vspace_id, const char *src_file_name, const char *src_dset_name, hid_t src_space_id); */
SEXP R_H5Pset_virtual(SEXP R_dcpl_id, SEXP R_vspace_id, SEXP R_src_file_name, SEXP R_src_dset_name, SEXP R_src_space_id){
  int vars_protected=0;
  hid_t dcpl_id = SEXP_to_longlong(R_dcpl_id, 0);
  hid_t vspace_id = SEXP_to_longlong(R_vspace_id, 0);
  const char* src_file_name = CHAR(STRING_ELT(R_src_file_name, 0));
  const char* src_dset_name = CHAR(STRING_ELT(R_src_dset_name, 0));
  hid_t src_space_id = SEXP_to_longlong(R_src_space_id, 0);
  herr_t return_val = H5Pset_virtual(dcpl_id, vspace_id, src_file_name, src_dset_name, src_space_id);
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

/* H5_DLL herr_t H5Pset_virtual_prefix(hid_t dapl_id, const char* prefix); */
SEXP R_H5Pset_virtual_prefix(SEXP R_dapl_id, SEXP R_prefix){
  int vars_protected=0;
  hid_t dapl_id = SEXP_to_longlong(R_dapl_id, 0);
  const char* prefix = CHAR(STRING_ELT(R_prefix, 0));
  herr_t return_val = H5Pset_virtual_prefix(dapl_id, prefix);
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

/* H5_DLL herr_t H5Pset_virtual_printf_gap(hid_t plist_id, hsize_t gap_size); */
SEXP R_H5Pset_virtual_printf_gap(SEXP R_plist_id, SEXP R_gap_size){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hsize_t gap_size = SEXP_to_longlong(R_gap_size, 0);
  herr_t return_val = H5Pset_virtual_printf_gap(plist_id, gap_size);
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

/* H5_DLL herr_t H5Pset_virtual_view(hid_t plist_id, H5D_vds_view_t view); */
SEXP R_H5Pset_virtual_view(SEXP R_plist_id, SEXP R_view){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  H5D_vds_view_t view = SEXP_to_longlong(R_view, 0);
  herr_t return_val = H5Pset_virtual_view(plist_id, view);
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

/* H5_DLL herr_t H5Pset_vol(hid_t plist_id, hid_t new_vol_id, const void *new_vol_info); */
SEXP R_H5Pset_vol(SEXP R_plist_id, SEXP R_new_vol_id, SEXP R_new_vol_info){
  int vars_protected=0;
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hid_t new_vol_id = SEXP_to_longlong(R_new_vol_id, 0);
  const void* new_vol_info;
  if(XLENGTH(R_new_vol_info) == 0) {
    new_vol_info = NULL;
  }
  else {
    new_vol_info = (void *) VOIDPTR(R_new_vol_info);
  }
  herr_t return_val = H5Pset_vol(plist_id, new_vol_id, new_vol_info);
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

/* H5_DLL herr_t H5Punregister(hid_t pclass_id, const char *name); */
SEXP R_H5Punregister(SEXP R_pclass_id, SEXP R_name){
  int vars_protected=0;
  hid_t pclass_id = SEXP_to_longlong(R_pclass_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  herr_t return_val = H5Punregister(pclass_id, name);
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


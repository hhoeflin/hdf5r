
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

#include "Wrapper_auto_H5S.h"
/* H5_DLL herr_t H5Sclose(hid_t space_id); */
SEXP R_H5Sclose(SEXP R_space_id){
  int vars_protected=0;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  herr_t return_val = H5Sclose(space_id);
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

/* H5_DLL hid_t H5Scopy(hid_t space_id); */
SEXP R_H5Scopy(SEXP R_space_id){
  int vars_protected=0;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  hid_t return_val = H5Scopy(space_id);
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

/* H5_DLL hid_t H5Screate(H5S_class_t type); */
SEXP R_H5Screate(SEXP R_type){
  int vars_protected=0;
  H5S_class_t type = SEXP_to_longlong(R_type, 0);
  hid_t return_val = H5Screate(type);
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

/* H5_DLL hid_t H5Screate_simple(int rank, const hsize_t dims[], const hsize_t maxdims[]); */
SEXP R_H5Screate_simple(SEXP R_rank, SEXP R_dims, SEXP R_maxdims){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
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
  const hsize_t* maxdims;
  if(XLENGTH(R_maxdims) == 0) {
    maxdims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_maxdims, h5_datatype[DT_hsize_t], XLENGTH(R_maxdims)));
    maxdims= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  // INJECTION CODE START
  // the pointer is to const; need to cast it when I detect an Inf value
  if(isReal(R_maxdims)) {
    hsize_t* maxdims_helper = (hsize_t *) VOIDPTR(R_helper);
    for(int i=0; i < rank; ++i) {
      if(REAL(R_maxdims)[i] == R_PosInf) {
        maxdims_helper[i] = H5S_UNLIMITED;
      }
    }
  }
  // INJECTION CODE END
  hid_t return_val = H5Screate_simple(rank, dims, maxdims);
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

/* H5_DLL hid_t H5Sdecode(const void *buf); */
SEXP R_H5Sdecode(SEXP R_buf){
  int vars_protected=0;
  const void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  hid_t return_val = H5Sdecode(buf);
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

/* H5_DLL herr_t H5Sencode(hid_t obj_id, void *buf, size_t *nalloc); */
SEXP R_H5Sencode(SEXP R_obj_id, SEXP R_buf, SEXP R_nalloc, SEXP _dupl_buf){
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
  herr_t return_val = H5Sencode(obj_id, buf, nalloc);
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

/* H5_DLL herr_t H5Sextent_copy(hid_t dst_id,hid_t src_id); */
SEXP R_H5Sextent_copy(SEXP R_dst_id, SEXP R_src_id){
  int vars_protected=0;
  hid_t dst_id = SEXP_to_longlong(R_dst_id, 0);
  hid_t src_id = SEXP_to_longlong(R_src_id, 0);
  herr_t return_val = H5Sextent_copy(dst_id, src_id);
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

/* H5_DLL htri_t H5Sextent_equal(hid_t sid1, hid_t sid2); */
SEXP R_H5Sextent_equal(SEXP R_sid1, SEXP R_sid2){
  int vars_protected=0;
  hid_t sid1 = SEXP_to_longlong(R_sid1, 0);
  hid_t sid2 = SEXP_to_longlong(R_sid2, 0);
  htri_t return_val = H5Sextent_equal(sid1, sid2);
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

/* H5_DLL htri_t H5Sget_regular_hyperslab(hid_t spaceid, hsize_t start[], hsize_t stride[], hsize_t count[], hsize_t block[]); */
SEXP R_H5Sget_regular_hyperslab(SEXP R_spaceid, SEXP R_start, SEXP R_stride, SEXP R_count, SEXP R_block){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_start = PROTECT(duplicate(R_start));
  vars_protected++;
  R_stride = PROTECT(duplicate(R_stride));
  vars_protected++;
  R_count = PROTECT(duplicate(R_count));
  vars_protected++;
  R_block = PROTECT(duplicate(R_block));
  vars_protected++;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  hsize_t* start;
  if(XLENGTH(R_start) == 0) {
    start = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_start, h5_datatype[DT_hsize_t], XLENGTH(R_start)));
    start= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* stride;
  if(XLENGTH(R_stride) == 0) {
    stride = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_stride, h5_datatype[DT_hsize_t], XLENGTH(R_stride)));
    stride= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* count;
  if(XLENGTH(R_count) == 0) {
    count = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_count, h5_datatype[DT_hsize_t], XLENGTH(R_count)));
    count= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* block;
  if(XLENGTH(R_block) == 0) {
    block = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_block, h5_datatype[DT_hsize_t], XLENGTH(R_block)));
    block= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  htri_t return_val = H5Sget_regular_hyperslab(spaceid, start, stride, count, block);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_start, h5_datatype[DT_hsize_t]);
  R_start = PROTECT(H5ToR_single_step(start, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_stride, h5_datatype[DT_hsize_t]);
  R_stride = PROTECT(H5ToR_single_step(stride, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_count, h5_datatype[DT_hsize_t]);
  R_count = PROTECT(H5ToR_single_step(count, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_block, h5_datatype[DT_hsize_t]);
  R_block = PROTECT(H5ToR_single_step(block, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 5));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_start);
  SET_VECTOR_ELT(__ret_list, 2, R_stride);
  SET_VECTOR_ELT(__ret_list, 3, R_count);
  SET_VECTOR_ELT(__ret_list, 4, R_block);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 5));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("start"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("stride"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("count"));
  SET_STRING_ELT(__ret_list_names, 4, mkChar("block"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Sget_select_bounds(hid_t spaceid, hsize_t start[], hsize_t end[]); */
SEXP R_H5Sget_select_bounds(SEXP R_spaceid, SEXP R_start, SEXP R_end){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_start = PROTECT(duplicate(R_start));
  vars_protected++;
  R_end = PROTECT(duplicate(R_end));
  vars_protected++;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  hsize_t* start;
  if(XLENGTH(R_start) == 0) {
    start = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_start, h5_datatype[DT_hsize_t], XLENGTH(R_start)));
    start= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* end;
  if(XLENGTH(R_end) == 0) {
    end = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_end, h5_datatype[DT_hsize_t], XLENGTH(R_end)));
    end= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Sget_select_bounds(spaceid, start, end);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_start, h5_datatype[DT_hsize_t]);
  R_start = PROTECT(H5ToR_single_step(start, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_end, h5_datatype[DT_hsize_t]);
  R_end = PROTECT(H5ToR_single_step(end, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_start);
  SET_VECTOR_ELT(__ret_list, 2, R_end);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("start"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("end"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hssize_t H5Sget_select_elem_npoints(hid_t spaceid); */
SEXP R_H5Sget_select_elem_npoints(SEXP R_spaceid){
  int vars_protected=0;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  hssize_t return_val = H5Sget_select_elem_npoints(spaceid);
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

/* H5_DLL herr_t H5Sget_select_elem_pointlist(hid_t spaceid, hsize_t startpoint, hsize_t numpoints, hsize_t buf[]); */
SEXP R_H5Sget_select_elem_pointlist(SEXP R_spaceid, SEXP R_startpoint, SEXP R_numpoints, SEXP R_buf){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_buf = PROTECT(duplicate(R_buf));
  vars_protected++;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  hsize_t startpoint = SEXP_to_longlong(R_startpoint, 0);
  hsize_t numpoints = SEXP_to_longlong(R_numpoints, 0);
  hsize_t* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buf, h5_datatype[DT_hsize_t], XLENGTH(R_buf)));
    buf= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Sget_select_elem_pointlist(spaceid, startpoint, numpoints, buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_buf, h5_datatype[DT_hsize_t]);
  R_buf = PROTECT(H5ToR_single_step(buf, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
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

/* H5_DLL herr_t H5Sget_select_hyper_blocklist(hid_t spaceid, hsize_t startblock, hsize_t numblocks, hsize_t buf[]); */
SEXP R_H5Sget_select_hyper_blocklist(SEXP R_spaceid, SEXP R_startblock, SEXP R_numblocks, SEXP R_buf){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_buf = PROTECT(duplicate(R_buf));
  vars_protected++;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  hsize_t startblock = SEXP_to_longlong(R_startblock, 0);
  hsize_t numblocks = SEXP_to_longlong(R_numblocks, 0);
  hsize_t* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buf, h5_datatype[DT_hsize_t], XLENGTH(R_buf)));
    buf= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Sget_select_hyper_blocklist(spaceid, startblock, numblocks, buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_buf, h5_datatype[DT_hsize_t]);
  R_buf = PROTECT(H5ToR_single_step(buf, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
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

/* H5_DLL hssize_t H5Sget_select_hyper_nblocks(hid_t spaceid); */
SEXP R_H5Sget_select_hyper_nblocks(SEXP R_spaceid){
  int vars_protected=0;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  hssize_t return_val = H5Sget_select_hyper_nblocks(spaceid);
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

/* H5_DLL hssize_t H5Sget_select_npoints(hid_t spaceid); */
SEXP R_H5Sget_select_npoints(SEXP R_spaceid){
  int vars_protected=0;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  hssize_t return_val = H5Sget_select_npoints(spaceid);
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

/* H5_DLL H5S_sel_type H5Sget_select_type(hid_t spaceid); */
SEXP R_H5Sget_select_type(SEXP R_spaceid){
  int vars_protected=0;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  H5S_sel_type return_val = H5Sget_select_type(spaceid);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5S_sel_type]));
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

/* H5_DLL int H5Sget_simple_extent_dims(hid_t space_id, hsize_t dims[], hsize_t maxdims[]); */
SEXP R_H5Sget_simple_extent_dims(SEXP R_space_id, SEXP R_dims, SEXP R_maxdims){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_dims = PROTECT(duplicate(R_dims));
  vars_protected++;
  R_maxdims = PROTECT(duplicate(R_maxdims));
  vars_protected++;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  hsize_t* dims;
  if(XLENGTH(R_dims) == 0) {
    dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dims, h5_datatype[DT_hsize_t], XLENGTH(R_dims)));
    dims= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* maxdims;
  if(XLENGTH(R_maxdims) == 0) {
    maxdims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_maxdims, h5_datatype[DT_hsize_t], XLENGTH(R_maxdims)));
    maxdims= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  int return_val = H5Sget_simple_extent_dims(space_id, dims, maxdims);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_dims, h5_datatype[DT_hsize_t]);
  R_dims = PROTECT(H5ToR_single_step(dims, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_maxdims, h5_datatype[DT_hsize_t]);
  R_maxdims = PROTECT(H5ToR_single_step(maxdims, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  // INJECTION CODE START
  // check if it is an int64 vector, and if yes which is H5S_UNLIMITED
  // in that case, the return needs to be a real vector, so that Inf can be set
  if(is_rint64(R_maxdims)) {
    R_maxdims = PROTECT(convert_int64_using_flags(R_maxdims, H5TOR_CONV_INT64_FLOAT_FORCE));
    vars_protected++;
    double  dbl_unlimited = (double) LLONG_MAX;
    R_xlen_t len = XLENGTH(R_maxdims);
    for(R_xlen_t i = 0; i < len; ++i) {
      if(REAL(R_maxdims)[i] == dbl_unlimited) {
        REAL(R_maxdims)[i] = R_PosInf;
      }
    }
  }
  // INJECTION CODE END
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_dims);
  SET_VECTOR_ELT(__ret_list, 2, R_maxdims);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("dims"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("maxdims"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL int H5Sget_simple_extent_ndims(hid_t space_id); */
SEXP R_H5Sget_simple_extent_ndims(SEXP R_space_id){
  int vars_protected=0;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  int return_val = H5Sget_simple_extent_ndims(space_id);
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

/* H5_DLL hssize_t H5Sget_simple_extent_npoints(hid_t space_id); */
SEXP R_H5Sget_simple_extent_npoints(SEXP R_space_id){
  int vars_protected=0;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  hssize_t return_val = H5Sget_simple_extent_npoints(space_id);
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

/* H5_DLL H5S_class_t H5Sget_simple_extent_type(hid_t space_id); */
SEXP R_H5Sget_simple_extent_type(SEXP R_space_id){
  int vars_protected=0;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  H5S_class_t return_val = H5Sget_simple_extent_type(space_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5S_class_t]));
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

/* H5_DLL htri_t H5Sis_regular_hyperslab(hid_t spaceid); */
SEXP R_H5Sis_regular_hyperslab(SEXP R_spaceid){
  int vars_protected=0;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  htri_t return_val = H5Sis_regular_hyperslab(spaceid);
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

/* H5_DLL htri_t H5Sis_simple(hid_t space_id); */
SEXP R_H5Sis_simple(SEXP R_space_id){
  int vars_protected=0;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  htri_t return_val = H5Sis_simple(space_id);
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

/* H5_DLL herr_t H5Soffset_simple(hid_t space_id, const hssize_t *offset); */
SEXP R_H5Soffset_simple(SEXP R_space_id, SEXP R_offset){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  const hssize_t* offset;
  if(XLENGTH(R_offset) == 0) {
    offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_offset, h5_datatype[DT_hssize_t], XLENGTH(R_offset)));
    offset= (const hssize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Soffset_simple(space_id, offset);
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

/* H5_DLL herr_t H5Sselect_all(hid_t spaceid); */
SEXP R_H5Sselect_all(SEXP R_spaceid){
  int vars_protected=0;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  herr_t return_val = H5Sselect_all(spaceid);
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

/* H5_DLL herr_t H5Sselect_elements(hid_t space_id, H5S_seloper_t op, size_t num_elem, const hsize_t *coord); */
SEXP R_H5Sselect_elements(SEXP R_space_id, SEXP R_op, SEXP R_num_elem, SEXP R_coord){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  H5S_seloper_t op = SEXP_to_longlong(R_op, 0);
  size_t num_elem = SEXP_to_longlong(R_num_elem, 0);
  const hsize_t* coord;
  if(XLENGTH(R_coord) == 0) {
    coord = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_coord, h5_datatype[DT_hsize_t], XLENGTH(R_coord)));
    coord= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Sselect_elements(space_id, op, num_elem, coord);
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

/* H5_DLL herr_t H5Sselect_hyperslab(hid_t space_id, H5S_seloper_t op, const hsize_t start[], const hsize_t _stride[], const hsize_t count[], const hsize_t _block[]); */
SEXP R_H5Sselect_hyperslab(SEXP R_space_id, SEXP R_op, SEXP R_start, SEXP R__stride, SEXP R_count, SEXP R__block){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  H5S_seloper_t op = SEXP_to_longlong(R_op, 0);
  const hsize_t* start;
  if(XLENGTH(R_start) == 0) {
    start = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_start, h5_datatype[DT_hsize_t], XLENGTH(R_start)));
    start= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const hsize_t* _stride;
  if(XLENGTH(R__stride) == 0) {
    _stride = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R__stride, h5_datatype[DT_hsize_t], XLENGTH(R__stride)));
    _stride= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const hsize_t* count;
  if(XLENGTH(R_count) == 0) {
    count = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_count, h5_datatype[DT_hsize_t], XLENGTH(R_count)));
    count= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const hsize_t* _block;
  if(XLENGTH(R__block) == 0) {
    _block = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R__block, h5_datatype[DT_hsize_t], XLENGTH(R__block)));
    _block= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Sselect_hyperslab(space_id, op, start, _stride, count, _block);
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

/* H5_DLL herr_t H5Sselect_none(hid_t spaceid); */
SEXP R_H5Sselect_none(SEXP R_spaceid){
  int vars_protected=0;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  herr_t return_val = H5Sselect_none(spaceid);
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

/* H5_DLL htri_t H5Sselect_valid(hid_t spaceid); */
SEXP R_H5Sselect_valid(SEXP R_spaceid){
  int vars_protected=0;
  hid_t spaceid = SEXP_to_longlong(R_spaceid, 0);
  htri_t return_val = H5Sselect_valid(spaceid);
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

/* H5_DLL herr_t H5Sset_extent_none(hid_t space_id); */
SEXP R_H5Sset_extent_none(SEXP R_space_id){
  int vars_protected=0;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  herr_t return_val = H5Sset_extent_none(space_id);
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

/* H5_DLL herr_t H5Sset_extent_simple(hid_t space_id, int rank, const hsize_t dims[], const hsize_t max[]); */
SEXP R_H5Sset_extent_simple(SEXP R_space_id, SEXP R_rank, SEXP R_dims, SEXP R_max){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
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
  const hsize_t* max;
  if(XLENGTH(R_max) == 0) {
    max = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_max, h5_datatype[DT_hsize_t], XLENGTH(R_max)));
    max= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  // INJECTION CODE START
  // the pointer is to const; need to cast it when I detect an Inf value
  if(isReal(R_max)) {
    hsize_t* max_helper = (hsize_t *) VOIDPTR(R_helper);
    for(int i=0; i < rank; ++i) {
      if(REAL(R_max)[i] == R_PosInf) {
        max_helper[i] = H5S_UNLIMITED;
      }
    }
  }
  // INJECTION CODE END
  herr_t return_val = H5Sset_extent_simple(space_id, rank, dims, max);
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


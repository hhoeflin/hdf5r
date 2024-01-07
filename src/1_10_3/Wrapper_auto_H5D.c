
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

#include "Wrapper_auto_H5D.h"
/* H5_DLL herr_t H5Dclose(hid_t dset_id); */
SEXP R_H5Dclose(SEXP R_dset_id){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  herr_t return_val = H5Dclose(dset_id);
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

/* H5_DLL hid_t H5Dcreate_anon(hid_t file_id, hid_t type_id, hid_t space_id, hid_t plist_id, hid_t dapl_id); */
SEXP R_H5Dcreate_anon(SEXP R_file_id, SEXP R_type_id, SEXP R_space_id, SEXP R_plist_id, SEXP R_dapl_id){
  int vars_protected=0;
  hid_t file_id = SEXP_to_longlong(R_file_id, 0);
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  hid_t dapl_id = SEXP_to_longlong(R_dapl_id, 0);
  hid_t return_val = H5Dcreate_anon(file_id, type_id, space_id, plist_id, dapl_id);
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

/* H5_DLL hid_t H5Dcreate2(hid_t loc_id, const char *name, hid_t type_id, hid_t space_id, hid_t lcpl_id, hid_t dcpl_id, hid_t dapl_id); */
SEXP R_H5Dcreate2(SEXP R_loc_id, SEXP R_name, SEXP R_type_id, SEXP R_space_id, SEXP R_lcpl_id, SEXP R_dcpl_id, SEXP R_dapl_id){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  hid_t lcpl_id = SEXP_to_longlong(R_lcpl_id, 0);
  hid_t dcpl_id = SEXP_to_longlong(R_dcpl_id, 0);
  hid_t dapl_id = SEXP_to_longlong(R_dapl_id, 0);
  hid_t return_val = H5Dcreate2(loc_id, name, type_id, space_id, lcpl_id, dcpl_id, dapl_id);
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

/* H5_DLL herr_t H5Ddebug(hid_t dset_id); */
SEXP R_H5Ddebug(SEXP R_dset_id){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  herr_t return_val = H5Ddebug(dset_id);
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

/* H5_DLL herr_t H5Dfill(const void *fill, hid_t fill_type, void *buf, hid_t buf_type, hid_t space); */
SEXP R_H5Dfill(SEXP R_fill, SEXP R_fill_type, SEXP R_buf, SEXP R_buf_type, SEXP R_space, SEXP _dupl_buf){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  const void* fill;
  if(XLENGTH(R_fill) == 0) {
    fill = NULL;
  }
  else {
    fill = (void *) VOIDPTR(R_fill);
  }
  hid_t fill_type = SEXP_to_longlong(R_fill_type, 0);
  void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  hid_t buf_type = SEXP_to_longlong(R_buf_type, 0);
  hid_t space = SEXP_to_longlong(R_space, 0);
  herr_t return_val = H5Dfill(fill, fill_type, buf, buf_type, space);
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

/* H5_DLL herr_t H5Dflush(hid_t dset_id); */
SEXP R_H5Dflush(SEXP R_dset_id){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  herr_t return_val = H5Dflush(dset_id);
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

/* H5_DLL herr_t H5Dformat_convert(hid_t dset_id); */
SEXP R_H5Dformat_convert(SEXP R_dset_id){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  herr_t return_val = H5Dformat_convert(dset_id);
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

/* H5_DLL hid_t H5Dget_access_plist(hid_t dset_id); */
SEXP R_H5Dget_access_plist(SEXP R_dset_id){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  hid_t return_val = H5Dget_access_plist(dset_id);
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

/* H5_DLL herr_t H5Dget_chunk_index_type(hid_t did, H5D_chunk_index_t *idx_type); */
SEXP R_H5Dget_chunk_index_type(SEXP R_did, SEXP R_idx_type){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_idx_type = PROTECT(duplicate(R_idx_type));
  vars_protected++;
  hid_t did = SEXP_to_longlong(R_did, 0);
  H5D_chunk_index_t* idx_type;
  if(XLENGTH(R_idx_type) == 0) {
    idx_type = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_idx_type, h5_datatype[DT_H5D_chunk_index_t], XLENGTH(R_idx_type)));
    idx_type= (H5D_chunk_index_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Dget_chunk_index_type(did, idx_type);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_idx_type, h5_datatype[DT_H5D_chunk_index_t]);
  R_idx_type = PROTECT(H5ToR_single_step(idx_type, h5_datatype[DT_H5D_chunk_index_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_idx_type);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("idx_type"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Dget_chunk_storage_size(hid_t dset_id, const hsize_t *offset, hsize_t *chunk_bytes); */
SEXP R_H5Dget_chunk_storage_size(SEXP R_dset_id, SEXP R_offset, SEXP R_chunk_bytes){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_chunk_bytes = PROTECT(duplicate(R_chunk_bytes));
  vars_protected++;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  const hsize_t* offset;
  if(XLENGTH(R_offset) == 0) {
    offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_offset, h5_datatype[DT_hsize_t], XLENGTH(R_offset)));
    offset= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* chunk_bytes;
  if(XLENGTH(R_chunk_bytes) == 0) {
    chunk_bytes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_chunk_bytes, h5_datatype[DT_hsize_t], XLENGTH(R_chunk_bytes)));
    chunk_bytes= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Dget_chunk_storage_size(dset_id, offset, chunk_bytes);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_chunk_bytes, h5_datatype[DT_hsize_t]);
  R_chunk_bytes = PROTECT(H5ToR_single_step(chunk_bytes, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_chunk_bytes);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("chunk_bytes"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Dget_create_plist(hid_t dset_id); */
SEXP R_H5Dget_create_plist(SEXP R_dset_id){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  hid_t return_val = H5Dget_create_plist(dset_id);
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

/* H5_DLL haddr_t H5Dget_offset(hid_t dset_id); */
SEXP R_H5Dget_offset(SEXP R_dset_id){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  haddr_t return_val = H5Dget_offset(dset_id);
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

/* H5_DLL hid_t H5Dget_space(hid_t dset_id); */
SEXP R_H5Dget_space(SEXP R_dset_id){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  hid_t return_val = H5Dget_space(dset_id);
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

/* H5_DLL herr_t H5Dget_space_status(hid_t dset_id, H5D_space_status_t *allocation); */
SEXP R_H5Dget_space_status(SEXP R_dset_id, SEXP R_allocation){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_allocation = PROTECT(duplicate(R_allocation));
  vars_protected++;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  H5D_space_status_t* allocation;
  if(XLENGTH(R_allocation) == 0) {
    allocation = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_allocation, h5_datatype[DT_H5D_space_status_t], XLENGTH(R_allocation)));
    allocation= (H5D_space_status_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Dget_space_status(dset_id, allocation);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_allocation, h5_datatype[DT_H5D_space_status_t]);
  R_allocation = PROTECT(H5ToR_single_step(allocation, h5_datatype[DT_H5D_space_status_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_allocation);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("allocation"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hsize_t H5Dget_storage_size(hid_t dset_id); */
SEXP R_H5Dget_storage_size(SEXP R_dset_id){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  hsize_t return_val = H5Dget_storage_size(dset_id);
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

/* H5_DLL hid_t H5Dget_type(hid_t dset_id); */
SEXP R_H5Dget_type(SEXP R_dset_id){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  hid_t return_val = H5Dget_type(dset_id);
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

/* H5_DLL hid_t H5Dopen2(hid_t file_id, const char *name, hid_t dapl_id); */
SEXP R_H5Dopen2(SEXP R_file_id, SEXP R_name, SEXP R_dapl_id){
  int vars_protected=0;
  hid_t file_id = SEXP_to_longlong(R_file_id, 0);
  const char* name = CHAR(STRING_ELT(R_name, 0));
  hid_t dapl_id = SEXP_to_longlong(R_dapl_id, 0);
  hid_t return_val = H5Dopen2(file_id, name, dapl_id);
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

/* H5_DLL herr_t H5Dread(hid_t dset_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t plist_id, void *buf); */
SEXP R_H5Dread(SEXP R_dset_id, SEXP R_mem_type_id, SEXP R_mem_space_id, SEXP R_file_space_id, SEXP R_plist_id, SEXP R_buf, SEXP _dupl_buf){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  hid_t mem_type_id = SEXP_to_longlong(R_mem_type_id, 0);
  hid_t mem_space_id = SEXP_to_longlong(R_mem_space_id, 0);
  hid_t file_space_id = SEXP_to_longlong(R_file_space_id, 0);
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5Dread(dset_id, mem_type_id, mem_space_id, file_space_id, plist_id, buf);
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

/* H5_DLL herr_t H5Dread_chunk(hid_t dset_id, hid_t dxpl_id, const hsize_t *offset, uint32_t *filters, void *buf); */
SEXP R_H5Dread_chunk(SEXP R_dset_id, SEXP R_dxpl_id, SEXP R_offset, SEXP R_filters, SEXP R_buf, SEXP _dupl_buf){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_filters = PROTECT(duplicate(R_filters));
  vars_protected++;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  hid_t dxpl_id = SEXP_to_longlong(R_dxpl_id, 0);
  const hsize_t* offset;
  if(XLENGTH(R_offset) == 0) {
    offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_offset, h5_datatype[DT_hsize_t], XLENGTH(R_offset)));
    offset= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  uint32_t* filters;
  if(XLENGTH(R_filters) == 0) {
    filters = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_filters, h5_datatype[DT_uint32_t], XLENGTH(R_filters)));
    filters= (uint32_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5Dread_chunk(dset_id, dxpl_id, offset, filters, buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_filters, h5_datatype[DT_uint32_t]);
  R_filters = PROTECT(H5ToR_single_step(filters, h5_datatype[DT_uint32_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_filters);
  SET_VECTOR_ELT(__ret_list, 2, R_buf);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("filters"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("buf"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Drefresh(hid_t dset_id); */
SEXP R_H5Drefresh(SEXP R_dset_id){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  herr_t return_val = H5Drefresh(dset_id);
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

/* H5_DLL herr_t H5Dset_extent(hid_t dset_id, const hsize_t size[]); */
SEXP R_H5Dset_extent(SEXP R_dset_id, SEXP R_size){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  const hsize_t* size;
  if(XLENGTH(R_size) == 0) {
    size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_size, h5_datatype[DT_hsize_t], XLENGTH(R_size)));
    size= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Dset_extent(dset_id, size);
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

/* H5_DLL herr_t H5Dvlen_get_buf_size(hid_t dataset_id, hid_t type_id, hid_t space_id, hsize_t *size); */
SEXP R_H5Dvlen_get_buf_size(SEXP R_dataset_id, SEXP R_type_id, SEXP R_space_id, SEXP R_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_size = PROTECT(duplicate(R_size));
  vars_protected++;
  hid_t dataset_id = SEXP_to_longlong(R_dataset_id, 0);
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  hsize_t* size;
  if(XLENGTH(R_size) == 0) {
    size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_size, h5_datatype[DT_hsize_t], XLENGTH(R_size)));
    size= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Dvlen_get_buf_size(dataset_id, type_id, space_id, size);
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

/* H5_DLL herr_t H5Dvlen_reclaim(hid_t type_id, hid_t space_id, hid_t plist_id, void *buf); */
SEXP R_H5Dvlen_reclaim(SEXP R_type_id, SEXP R_space_id, SEXP R_plist_id, SEXP R_buf, SEXP _dupl_buf){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  hid_t type_id = SEXP_to_longlong(R_type_id, 0);
  hid_t space_id = SEXP_to_longlong(R_space_id, 0);
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  void* buf;
  if(TYPEOF(R_buf) == NILSXP) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5Dvlen_reclaim(type_id, space_id, plist_id, buf);
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

/* H5_DLL herr_t H5Dwrite(hid_t dset_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t plist_id, const void *buf); */
SEXP R_H5Dwrite(SEXP R_dset_id, SEXP R_mem_type_id, SEXP R_mem_space_id, SEXP R_file_space_id, SEXP R_plist_id, SEXP R_buf){
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  hid_t mem_type_id = SEXP_to_longlong(R_mem_type_id, 0);
  hid_t mem_space_id = SEXP_to_longlong(R_mem_space_id, 0);
  hid_t file_space_id = SEXP_to_longlong(R_file_space_id, 0);
  hid_t plist_id = SEXP_to_longlong(R_plist_id, 0);
  const void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5Dwrite(dset_id, mem_type_id, mem_space_id, file_space_id, plist_id, buf);
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

/* H5_DLL herr_t H5Dwrite_chunk(hid_t dset_id, hid_t dxpl_id, uint32_t filters, const hsize_t *offset, size_t data_size, const void *buf); */
SEXP R_H5Dwrite_chunk(SEXP R_dset_id, SEXP R_dxpl_id, SEXP R_filters, SEXP R_offset, SEXP R_data_size, SEXP R_buf){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  hid_t dxpl_id = SEXP_to_longlong(R_dxpl_id, 0);
  uint32_t filters = SEXP_to_longlong(R_filters, 0);
  const hsize_t* offset;
  if(XLENGTH(R_offset) == 0) {
    offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_offset, h5_datatype[DT_hsize_t], XLENGTH(R_offset)));
    offset= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t data_size = SEXP_to_longlong(R_data_size, 0);
  const void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5Dwrite_chunk(dset_id, dxpl_id, filters, offset, data_size, buf);
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


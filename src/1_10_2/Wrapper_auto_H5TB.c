
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

#include "Wrapper_auto_H5TB.h"
/* H5_HLDLL herr_t H5TBadd_records_from( hid_t loc_id, const char *dset_name1, hsize_t start1, hsize_t nrecords, const char *dset_name2, hsize_t start2 ); */
SEXP R_H5TBadd_records_from(SEXP R_loc_id, SEXP R_dset_name1, SEXP R_start1, SEXP R_nrecords, SEXP R_dset_name2, SEXP R_start2){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name1 = CHAR(STRING_ELT(R_dset_name1, 0));
  hsize_t start1 = SEXP_to_longlong(R_start1, 0);
  hsize_t nrecords = SEXP_to_longlong(R_nrecords, 0);
  const char* dset_name2 = CHAR(STRING_ELT(R_dset_name2, 0));
  hsize_t start2 = SEXP_to_longlong(R_start2, 0);
  herr_t return_val = H5TBadd_records_from(loc_id, dset_name1, start1, nrecords, dset_name2, start2);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL htri_t H5TBAget_fill(hid_t loc_id, const char *dset_name, hid_t dset_id, unsigned char *dst_buf); */
SEXP R_H5TBAget_fill(SEXP R_loc_id, SEXP R_dset_name, SEXP R_dset_id, SEXP R_dst_buf){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_dst_buf = PROTECT(duplicate(R_dst_buf));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hid_t dset_id = SEXP_to_longlong(R_dset_id, 0);
  unsigned char* dst_buf;
  if(XLENGTH(R_dst_buf) == 0) {
    dst_buf = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_buf, h5_datatype[DT_unsigned_char], XLENGTH(R_dst_buf)));
    dst_buf= (unsigned char*) VOIDPTR(R_helper);
    vars_protected++;
  }
  htri_t return_val = H5TBAget_fill(loc_id, dset_name, dset_id, dst_buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_dst_buf, h5_datatype[DT_unsigned_char]);
  R_dst_buf = PROTECT(H5ToR_single_step(dst_buf, h5_datatype[DT_unsigned_char], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_dst_buf);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("dst_buf"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBAget_title( hid_t loc_id, char *table_title ); */
SEXP R_H5TBAget_title(SEXP R_loc_id, SEXP R_table_title){
  int vars_protected=0;
  R_table_title = PROTECT(duplicate(R_table_title));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  char* table_title;
  if(XLENGTH(R_table_title) == 0) {
    table_title = NULL;
  }
  else {
    table_title = R_alloc(strlen(CHAR(STRING_ELT(R_table_title, 0))) + 1, 1);
    strcpy(table_title, CHAR(STRING_ELT(R_table_title, 0)));
  }
  herr_t return_val = H5TBAget_title(loc_id, table_title);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(table_title==NULL) {
    R_table_title = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_table_title = PROTECT(mkString(table_title));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_table_title);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("table_title"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBappend_records( hid_t loc_id, const char *dset_name, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, const void *buf ); */
SEXP R_H5TBappend_records(SEXP R_loc_id, SEXP R_dset_name, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t nrecords = SEXP_to_longlong(R_nrecords, 0);
  size_t type_size = SEXP_to_longlong(R_type_size, 0);
  const size_t* field_offset;
  if(XLENGTH(R_field_offset) == 0) {
    field_offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_offset, h5_datatype[DT_size_t], XLENGTH(R_field_offset)));
    field_offset= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const size_t* dst_sizes;
  if(XLENGTH(R_dst_sizes) == 0) {
    dst_sizes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_sizes, h5_datatype[DT_size_t], XLENGTH(R_dst_sizes)));
    dst_sizes= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5TBappend_records(loc_id, dset_name, nrecords, type_size, field_offset, dst_sizes, buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBcombine_tables( hid_t loc_id1, const char *dset_name1, hid_t loc_id2, const char *dset_name2, const char *dset_name3 ); */
SEXP R_H5TBcombine_tables(SEXP R_loc_id1, SEXP R_dset_name1, SEXP R_loc_id2, SEXP R_dset_name2, SEXP R_dset_name3){
  int vars_protected=0;
  hid_t loc_id1 = SEXP_to_longlong(R_loc_id1, 0);
  const char* dset_name1 = CHAR(STRING_ELT(R_dset_name1, 0));
  hid_t loc_id2 = SEXP_to_longlong(R_loc_id2, 0);
  const char* dset_name2 = CHAR(STRING_ELT(R_dset_name2, 0));
  const char* dset_name3 = CHAR(STRING_ELT(R_dset_name3, 0));
  herr_t return_val = H5TBcombine_tables(loc_id1, dset_name1, loc_id2, dset_name2, dset_name3);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBdelete_field( hid_t loc_id, const char *dset_name, const char *field_name ); */
SEXP R_H5TBdelete_field(SEXP R_loc_id, SEXP R_dset_name, SEXP R_field_name){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  const char* field_name = CHAR(STRING_ELT(R_field_name, 0));
  herr_t return_val = H5TBdelete_field(loc_id, dset_name, field_name);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBdelete_record( hid_t loc_id, const char *dset_name, hsize_t start, hsize_t nrecords ); */
SEXP R_H5TBdelete_record(SEXP R_loc_id, SEXP R_dset_name, SEXP R_start, SEXP R_nrecords){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t start = SEXP_to_longlong(R_start, 0);
  hsize_t nrecords = SEXP_to_longlong(R_nrecords, 0);
  herr_t return_val = H5TBdelete_record(loc_id, dset_name, start, nrecords);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBget_field_info( hid_t loc_id, const char *dset_name, char *field_names[], size_t *field_sizes, size_t *field_offsets, size_t *type_size ); */
SEXP R_H5TBget_field_info(SEXP R_loc_id, SEXP R_dset_name, SEXP R_field_names, SEXP R_field_sizes, SEXP R_field_offsets, SEXP R_type_size){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_field_names = PROTECT(duplicate(R_field_names));
  vars_protected++;
  R_field_sizes = PROTECT(duplicate(R_field_sizes));
  vars_protected++;
  R_field_offsets = PROTECT(duplicate(R_field_offsets));
  vars_protected++;
  R_type_size = PROTECT(duplicate(R_type_size));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  char** field_names;
  if(XLENGTH(R_field_names) == 0) {
    field_names = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_names, h5_datatype[DT_char], XLENGTH(R_field_names)));
    field_names= (char**) VOIDPTR(R_helper);
    vars_protected++;
    if(!inherits(R_field_names, "_RToH5_empty")) {
      for(int i = 0; i < XLENGTH(R_field_names); ++i) {
        if(XLENGTH(STRING_ELT(R_field_names, i)) == 0) {
          field_names[i] = NULL;
        }
        else {
          field_names[i] = (char*) R_alloc(XLENGTH(STRING_ELT(R_field_names, i)), 1);
          strcpy(field_names[i], CHAR(STRING_ELT(R_field_names, i)));
        }
      }
    }
  }
  size_t* field_sizes;
  if(XLENGTH(R_field_sizes) == 0) {
    field_sizes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_sizes, h5_datatype[DT_size_t], XLENGTH(R_field_sizes)));
    field_sizes= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  size_t* field_offsets;
  if(XLENGTH(R_field_offsets) == 0) {
    field_offsets = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_offsets, h5_datatype[DT_size_t], XLENGTH(R_field_offsets)));
    field_offsets= (size_t*) VOIDPTR(R_helper);
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
  herr_t return_val = H5TBget_field_info(loc_id, dset_name, field_names, field_sizes, field_offsets, type_size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_field_names, h5_datatype[DT_char]);
  R_field_names = PROTECT(H5ToR_single_step(field_names, h5_datatype[DT_char], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_field_sizes, h5_datatype[DT_size_t]);
  R_field_sizes = PROTECT(H5ToR_single_step(field_sizes, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_field_offsets, h5_datatype[DT_size_t]);
  R_field_offsets = PROTECT(H5ToR_single_step(field_offsets, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_type_size, h5_datatype[DT_size_t]);
  R_type_size = PROTECT(H5ToR_single_step(type_size, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 5));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_field_names);
  SET_VECTOR_ELT(__ret_list, 2, R_field_sizes);
  SET_VECTOR_ELT(__ret_list, 3, R_field_offsets);
  SET_VECTOR_ELT(__ret_list, 4, R_type_size);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 5));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("field_names"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("field_sizes"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("field_offsets"));
  SET_STRING_ELT(__ret_list_names, 4, mkChar("type_size"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBget_table_info ( hid_t loc_id, const char *dset_name, hsize_t *nfields, hsize_t *nrecords ); */
SEXP R_H5TBget_table_info(SEXP R_loc_id, SEXP R_dset_name, SEXP R_nfields, SEXP R_nrecords){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_nfields = PROTECT(duplicate(R_nfields));
  vars_protected++;
  R_nrecords = PROTECT(duplicate(R_nrecords));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t* nfields;
  if(XLENGTH(R_nfields) == 0) {
    nfields = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_nfields, h5_datatype[DT_hsize_t], XLENGTH(R_nfields)));
    nfields= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* nrecords;
  if(XLENGTH(R_nrecords) == 0) {
    nrecords = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_nrecords, h5_datatype[DT_hsize_t], XLENGTH(R_nrecords)));
    nrecords= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5TBget_table_info(loc_id, dset_name, nfields, nrecords);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_nfields, h5_datatype[DT_hsize_t]);
  R_nfields = PROTECT(H5ToR_single_step(nfields, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_nrecords, h5_datatype[DT_hsize_t]);
  R_nrecords = PROTECT(H5ToR_single_step(nrecords, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_nfields);
  SET_VECTOR_ELT(__ret_list, 2, R_nrecords);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("nfields"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("nrecords"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBinsert_field( hid_t loc_id, const char *dset_name, const char *field_name, hid_t field_type, hsize_t position, const void *fill_data, const void *buf ); */
SEXP R_H5TBinsert_field(SEXP R_loc_id, SEXP R_dset_name, SEXP R_field_name, SEXP R_field_type, SEXP R_position, SEXP R_fill_data, SEXP R_buf){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  const char* field_name = CHAR(STRING_ELT(R_field_name, 0));
  hid_t field_type = SEXP_to_longlong(R_field_type, 0);
  hsize_t position = SEXP_to_longlong(R_position, 0);
  const void* fill_data;
  if(XLENGTH(R_fill_data) == 0) {
    fill_data = NULL;
  }
  else {
    fill_data = (void *) VOIDPTR(R_fill_data);
  }
  const void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5TBinsert_field(loc_id, dset_name, field_name, field_type, position, fill_data, buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBinsert_record( hid_t loc_id, const char *dset_name, hsize_t start, hsize_t nrecords, size_t dst_size, const size_t *dst_offset, const size_t *dst_sizes, void *buf ); */
SEXP R_H5TBinsert_record(SEXP R_loc_id, SEXP R_dset_name, SEXP R_start, SEXP R_nrecords, SEXP R_dst_size, SEXP R_dst_offset, SEXP R_dst_sizes, SEXP R_buf, SEXP _dupl_buf){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t start = SEXP_to_longlong(R_start, 0);
  hsize_t nrecords = SEXP_to_longlong(R_nrecords, 0);
  size_t dst_size = SEXP_to_longlong(R_dst_size, 0);
  const size_t* dst_offset;
  if(XLENGTH(R_dst_offset) == 0) {
    dst_offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_offset, h5_datatype[DT_size_t], XLENGTH(R_dst_offset)));
    dst_offset= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const size_t* dst_sizes;
  if(XLENGTH(R_dst_sizes) == 0) {
    dst_sizes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_sizes, h5_datatype[DT_size_t], XLENGTH(R_dst_sizes)));
    dst_sizes= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5TBinsert_record(loc_id, dset_name, start, nrecords, dst_size, dst_offset, dst_sizes, buf);
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

/* H5_HLDLL herr_t H5TBmake_table( const char *table_title, hid_t loc_id, const char *dset_name, hsize_t nfields, hsize_t nrecords, size_t type_size, const char *field_names[], const size_t *field_offset, const hid_t *field_types, hsize_t chunk_size, void *fill_data, int compress, const void *buf ); */
SEXP R_H5TBmake_table(SEXP R_table_title, SEXP R_loc_id, SEXP R_dset_name, SEXP R_nfields, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_names, SEXP R_field_offset, SEXP R_field_types, SEXP R_chunk_size, SEXP R_fill_data, SEXP R_compress, SEXP R_buf, SEXP _dupl_fill_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_field_names = PROTECT(duplicate(R_field_names));
  vars_protected++;
  if(SEXP_to_logical(_dupl_fill_data)) {
    R_fill_data = PROTECT(duplicate(R_fill_data));
    vars_protected++;
  }
  const char* table_title = CHAR(STRING_ELT(R_table_title, 0));
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t nfields = SEXP_to_longlong(R_nfields, 0);
  hsize_t nrecords = SEXP_to_longlong(R_nrecords, 0);
  size_t type_size = SEXP_to_longlong(R_type_size, 0);
  const char** field_names;
  if(XLENGTH(R_field_names) == 0) {
    field_names = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_names, h5_datatype[DT_char], XLENGTH(R_field_names)));
    field_names= (const char**) VOIDPTR(R_helper);
    vars_protected++;
  }
  const size_t* field_offset;
  if(XLENGTH(R_field_offset) == 0) {
    field_offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_offset, h5_datatype[DT_size_t], XLENGTH(R_field_offset)));
    field_offset= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const hid_t* field_types;
  if(XLENGTH(R_field_types) == 0) {
    field_types = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_types, h5_datatype[DT_hid_t], XLENGTH(R_field_types)));
    field_types= (const hid_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t chunk_size = SEXP_to_longlong(R_chunk_size, 0);
  void* fill_data;
  if(XLENGTH(R_fill_data) == 0) {
    fill_data = NULL;
  }
  else {
    fill_data = (void *) VOIDPTR(R_fill_data);
  }
  int compress = SEXP_to_longlong(R_compress, 0);
  const void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5TBmake_table(table_title, loc_id, dset_name, nfields, nrecords, type_size, field_names, field_offset, field_types, chunk_size, fill_data, compress, buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_field_names, h5_datatype[DT_char]);
  R_field_names = PROTECT(H5ToR_single_step(field_names, h5_datatype[DT_char], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_field_names);
  SET_VECTOR_ELT(__ret_list, 2, R_fill_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("field_names"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("fill_data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBread_fields_index( hid_t loc_id, const char *dset_name, hsize_t nfields, const int *field_index, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, void *buf ); */
SEXP R_H5TBread_fields_index(SEXP R_loc_id, SEXP R_dset_name, SEXP R_nfields, SEXP R_field_index, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf, SEXP _dupl_buf){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t nfields = SEXP_to_longlong(R_nfields, 0);
  const int* field_index;
  if(XLENGTH(R_field_index) == 0) {
    field_index = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_index, h5_datatype[DT_int], XLENGTH(R_field_index)));
    field_index= (const int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t start = SEXP_to_longlong(R_start, 0);
  hsize_t nrecords = SEXP_to_longlong(R_nrecords, 0);
  size_t type_size = SEXP_to_longlong(R_type_size, 0);
  const size_t* field_offset;
  if(XLENGTH(R_field_offset) == 0) {
    field_offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_offset, h5_datatype[DT_size_t], XLENGTH(R_field_offset)));
    field_offset= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const size_t* dst_sizes;
  if(XLENGTH(R_dst_sizes) == 0) {
    dst_sizes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_sizes, h5_datatype[DT_size_t], XLENGTH(R_dst_sizes)));
    dst_sizes= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5TBread_fields_index(loc_id, dset_name, nfields, field_index, start, nrecords, type_size, field_offset, dst_sizes, buf);
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

/* H5_HLDLL herr_t H5TBread_fields_name( hid_t loc_id, const char *dset_name, const char *field_names, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, void *buf ); */
SEXP R_H5TBread_fields_name(SEXP R_loc_id, SEXP R_dset_name, SEXP R_field_names, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf, SEXP _dupl_buf){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  const char* field_names = CHAR(STRING_ELT(R_field_names, 0));
  hsize_t start = SEXP_to_longlong(R_start, 0);
  hsize_t nrecords = SEXP_to_longlong(R_nrecords, 0);
  size_t type_size = SEXP_to_longlong(R_type_size, 0);
  const size_t* field_offset;
  if(XLENGTH(R_field_offset) == 0) {
    field_offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_offset, h5_datatype[DT_size_t], XLENGTH(R_field_offset)));
    field_offset= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const size_t* dst_sizes;
  if(XLENGTH(R_dst_sizes) == 0) {
    dst_sizes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_sizes, h5_datatype[DT_size_t], XLENGTH(R_dst_sizes)));
    dst_sizes= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5TBread_fields_name(loc_id, dset_name, field_names, start, nrecords, type_size, field_offset, dst_sizes, buf);
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

/* H5_HLDLL herr_t H5TBread_records( hid_t loc_id, const char *dset_name, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *dst_offset, const size_t *dst_sizes, void *buf ); */
SEXP R_H5TBread_records(SEXP R_loc_id, SEXP R_dset_name, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_dst_offset, SEXP R_dst_sizes, SEXP R_buf, SEXP _dupl_buf){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_buf)) {
    R_buf = PROTECT(duplicate(R_buf));
    vars_protected++;
  }
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t start = SEXP_to_longlong(R_start, 0);
  hsize_t nrecords = SEXP_to_longlong(R_nrecords, 0);
  size_t type_size = SEXP_to_longlong(R_type_size, 0);
  const size_t* dst_offset;
  if(XLENGTH(R_dst_offset) == 0) {
    dst_offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_offset, h5_datatype[DT_size_t], XLENGTH(R_dst_offset)));
    dst_offset= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const size_t* dst_sizes;
  if(XLENGTH(R_dst_sizes) == 0) {
    dst_sizes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_sizes, h5_datatype[DT_size_t], XLENGTH(R_dst_sizes)));
    dst_sizes= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5TBread_records(loc_id, dset_name, start, nrecords, type_size, dst_offset, dst_sizes, buf);
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

/* H5_HLDLL herr_t H5TBread_table( hid_t loc_id, const char *dset_name, size_t dst_size, const size_t *dst_offset, const size_t *dst_sizes, void *dst_buf ); */
SEXP R_H5TBread_table(SEXP R_loc_id, SEXP R_dset_name, SEXP R_dst_size, SEXP R_dst_offset, SEXP R_dst_sizes, SEXP R_dst_buf, SEXP _dupl_dst_buf){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_dst_buf)) {
    R_dst_buf = PROTECT(duplicate(R_dst_buf));
    vars_protected++;
  }
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  size_t dst_size = SEXP_to_longlong(R_dst_size, 0);
  const size_t* dst_offset;
  if(XLENGTH(R_dst_offset) == 0) {
    dst_offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_offset, h5_datatype[DT_size_t], XLENGTH(R_dst_offset)));
    dst_offset= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const size_t* dst_sizes;
  if(XLENGTH(R_dst_sizes) == 0) {
    dst_sizes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_sizes, h5_datatype[DT_size_t], XLENGTH(R_dst_sizes)));
    dst_sizes= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  void* dst_buf;
  if(XLENGTH(R_dst_buf) == 0) {
    dst_buf = NULL;
  }
  else {
    dst_buf = (void *) VOIDPTR(R_dst_buf);
  }
  herr_t return_val = H5TBread_table(loc_id, dset_name, dst_size, dst_offset, dst_sizes, dst_buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_dst_buf);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("dst_buf"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBwrite_fields_index( hid_t loc_id, const char *dset_name, hsize_t nfields, const int *field_index, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, const void *buf ); */
SEXP R_H5TBwrite_fields_index(SEXP R_loc_id, SEXP R_dset_name, SEXP R_nfields, SEXP R_field_index, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t nfields = SEXP_to_longlong(R_nfields, 0);
  const int* field_index;
  if(XLENGTH(R_field_index) == 0) {
    field_index = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_index, h5_datatype[DT_int], XLENGTH(R_field_index)));
    field_index= (const int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t start = SEXP_to_longlong(R_start, 0);
  hsize_t nrecords = SEXP_to_longlong(R_nrecords, 0);
  size_t type_size = SEXP_to_longlong(R_type_size, 0);
  const size_t* field_offset;
  if(XLENGTH(R_field_offset) == 0) {
    field_offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_offset, h5_datatype[DT_size_t], XLENGTH(R_field_offset)));
    field_offset= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const size_t* dst_sizes;
  if(XLENGTH(R_dst_sizes) == 0) {
    dst_sizes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_sizes, h5_datatype[DT_size_t], XLENGTH(R_dst_sizes)));
    dst_sizes= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5TBwrite_fields_index(loc_id, dset_name, nfields, field_index, start, nrecords, type_size, field_offset, dst_sizes, buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBwrite_fields_name( hid_t loc_id, const char *dset_name, const char *field_names, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, const void *buf ); */
SEXP R_H5TBwrite_fields_name(SEXP R_loc_id, SEXP R_dset_name, SEXP R_field_names, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  const char* field_names = CHAR(STRING_ELT(R_field_names, 0));
  hsize_t start = SEXP_to_longlong(R_start, 0);
  hsize_t nrecords = SEXP_to_longlong(R_nrecords, 0);
  size_t type_size = SEXP_to_longlong(R_type_size, 0);
  const size_t* field_offset;
  if(XLENGTH(R_field_offset) == 0) {
    field_offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_offset, h5_datatype[DT_size_t], XLENGTH(R_field_offset)));
    field_offset= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const size_t* dst_sizes;
  if(XLENGTH(R_dst_sizes) == 0) {
    dst_sizes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_sizes, h5_datatype[DT_size_t], XLENGTH(R_dst_sizes)));
    dst_sizes= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5TBwrite_fields_name(loc_id, dset_name, field_names, start, nrecords, type_size, field_offset, dst_sizes, buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5TBwrite_records( hid_t loc_id, const char *dset_name, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, const void *buf ); */
SEXP R_H5TBwrite_records(SEXP R_loc_id, SEXP R_dset_name, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t start = SEXP_to_longlong(R_start, 0);
  hsize_t nrecords = SEXP_to_longlong(R_nrecords, 0);
  size_t type_size = SEXP_to_longlong(R_type_size, 0);
  const size_t* field_offset;
  if(XLENGTH(R_field_offset) == 0) {
    field_offset = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_field_offset, h5_datatype[DT_size_t], XLENGTH(R_field_offset)));
    field_offset= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const size_t* dst_sizes;
  if(XLENGTH(R_dst_sizes) == 0) {
    dst_sizes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_dst_sizes, h5_datatype[DT_size_t], XLENGTH(R_dst_sizes)));
    dst_sizes= (const size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const void* buf;
  if(XLENGTH(R_buf) == 0) {
    buf = NULL;
  }
  else {
    buf = (void *) VOIDPTR(R_buf);
  }
  herr_t return_val = H5TBwrite_records(loc_id, dset_name, start, nrecords, type_size, field_offset, dst_sizes, buf);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}


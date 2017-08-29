
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


#ifndef _CONVERT_H
#define _CONVERT_H

#define __USE_MINGW_ANSI_STDIO 1
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "global.h"

#define MAX_INT_DOUBLE_PREC (1LL << 53)
#define MIN_INT_DOUBLE_PREC (-1LL << 53)
#define NA_INTEGER64 LLONG_MIN

#define STRING2(x) #x
#define STRING(x) STRING2(x)

// the following is needed for HDF5 version 1.8.12 to work with the code; H5free_memory did not exist; 
// it is therefore here simply defined as being the free function
#if _HDF5_USE_1_8_12_ == 1
void H5free_memory(void *ptr);
#endif // _HDF5_USE_1_8_12_


SEXP R_RToH5(SEXP _Robj, SEXP _dtype_id, SEXP _nelem);
SEXP RToH5(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);
SEXP RToH5_RComplex(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);
SEXP RToH5_COMPOUND(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);
SEXP RToH5_ARRAY(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);
SEXP RToH5_ENUM(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);
SEXP RToH5_INTEGER(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);
SEXP RToH5_FLOAT(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);
SEXP RToH5_STRING(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);
SEXP RToH5_OPAQUE(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);
SEXP RToH5_REFERENCE(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);
SEXP RToH5_VLEN(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);

SEXP H5ToR_single_step(void* _h5obj, hid_t dtype_id, R_xlen_t nelem, int flags); // not intended for references
SEXP R_H5ToR_Pre(SEXP _dtype_id, SEXP _nelem);
SEXP H5ToR_Pre(hid_t dtype_id, R_xlen_t nelem);
SEXP H5ToR_Pre_RComplex(hid_t dtype_id, R_xlen_t nelem);
SEXP H5ToR_Pre_COMPOUND(hid_t dtype_id, R_xlen_t nelem);
SEXP H5ToR_Pre_ARRAY(hid_t dtype_id, R_xlen_t nelem);
SEXP H5ToR_Pre_ENUM(hid_t dtype_id, R_xlen_t nelem);
SEXP H5ToR_Pre_INTEGER(hid_t dtype_id, R_xlen_t nelem);
SEXP H5ToR_Pre_FLOAT(hid_t dtype_id, R_xlen_t nelem);
SEXP H5ToR_Pre_STRING(hid_t dtype_id, R_xlen_t nelem);
SEXP H5ToR_Pre_OPAQUE(hid_t dtype_id, R_xlen_t nelem);
SEXP H5ToR_Pre_REFERENCE(hid_t dtype_id, R_xlen_t nelem);
SEXP H5ToR_Pre_VLEN(hid_t dtype_id, R_xlen_t nelem);


SEXP R_H5ToR_Post(SEXP _Robj, SEXP _dtype_id, SEXP _nelem, SEXP _flags, SEXP _obj_id);
SEXP H5ToR_Post(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags, hid_t obj_id);
SEXP H5ToR_Post_RComplex(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags);
SEXP H5ToR_Post_COMPOUND(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags, hid_t obj_id);
SEXP H5ToR_Post_ARRAY(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags, hid_t obj_id);
SEXP H5ToR_Post_ENUM(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags);
SEXP H5ToR_Post_INTEGER(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags);
SEXP H5ToR_Post_FLOAT(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags);
SEXP H5ToR_Post_STRING(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags);
SEXP H5ToR_Post_OPAQUE(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags);
SEXP H5ToR_Post_REFERENCE(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags, hid_t obj_id);
SEXP H5ToR_Post_VLEN(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags, hid_t obj_id);

/***************************************
 * copy functions and matrix re-rodering
 *************************************/
void* memcpy_to_record(void* dst, const void* src, hsize_t num_items, hsize_t record_size, hsize_t offset, hsize_t item_size);
void* memcpy_from_record(void* dst, const void* src, hsize_t num_items, hsize_t record_size, hsize_t offset, hsize_t item_size);
void* memcpy_between_record(void* dst, const void* src, hsize_t num_items, hsize_t record_size, hsize_t offset_dst, hsize_t offset_src, hsize_t item_size);
void* transpose_general(void* dst, const void* src, hsize_t num_rows, hsize_t num_cols, hsize_t item_size, bool cpy_by_col);
SEXP R_transpose_general(SEXP R_src, SEXP R_dim, SEXP R_item_size);
void* reorder(void* dst, const void* src, hsize_t num_rows, hsize_t num_cols, hsize_t item_size, const hsize_t * new_order);
SEXP R_reorder(SEXP R_src, SEXP R_num_rows, SEXP R_num_cols, SEXP R_item_size, SEXP R_new_order);
SEXP copy_rvec(SEXP _dst, SEXP _src, SEXP _nbytes);
SEXP R_read_raw_subset_generic(SEXP R_dst, SEXP R_idx, SEXP R_item_size);
void* read_raw_subset_generic(void* dst, void* src, R_xlen_t idx_len, long long *idx, R_xlen_t item_size);
SEXP R_write_raw_subset_generic(SEXP R_dst, SEXP R_src, SEXP R_idx, SEXP R_item_size);
void* write_raw_subset_generic(void* dst, void* src, R_xlen_t idx_len, long long *idx, R_xlen_t item_size);

/*****************************************
 * helper functions for class checking and simple transformations
 ****************************************/

int is_rint64(SEXP _Robj);
SEXP _is_rint64(SEXP _Robj);
R_xlen_t SEXP_to_xlen(SEXP _len);
long long SEXP_to_longlong(SEXP value, R_xlen_t pos);
bool SEXP_to_logical(SEXP value);
double SEXP_to_double(SEXP value);
SEXP ScalarInteger64(long long value);
SEXP ScalarInteger64_or_int(long long value);
SEXP ScalarFactor(int value, hid_t dtype_id);
bool is_sequence(SEXP val);

// can potentially add clearer error reporting here by passing in an STRSXP of length one, where the first 
// element is then used to report what when wrong
bool is_h5_complex(hid_t dtype_id);
bool is_RToH5_empty(SEXP _Robj, R_xlen_t nelem);
bool is_enum_factor(hid_t dtype);
bool is_enum_logical(hid_t dtype);
char* str_to_lower(char * str);
bool is_robj_enum(SEXP _Robj, hid_t dtype_id);
bool is_robj_compound(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem);
SEXP get_array_dim(hid_t dtype_id);
bool is_robj_array(SEXP _Robj, hid_t dtype_id);
SEXP string_to_UTF8(SEXP _str);

// guess the number of elements in an Robj; low-level for C usage as well as
// an interface to be used with .Call from R
SEXP R_guess_nelem(SEXP _Robj, SEXP _dtype);
R_xlen_t guess_nelem(SEXP _Robj, hid_t dtype_id);
void* VOIDPTR(SEXP x);
size_t R_get_item_size(SEXP x);

// converts int64 to int if none of the values are too large
SEXP convert_int64_using_flags(SEXP val, int flags);
SEXP convert_uint64_using_flags(SEXP val, int flags);

// cheaply set the dim attribute
SEXP set_dim_attribute(SEXP x, SEXP dim);

// convert to a hex character string
SEXP R_as_hex(SEXP x);

// conversion between double, int64 and int
SEXP convert_double_to_int64(SEXP dbl_vec);
SEXP convert_int64_to_double(SEXP int64_vec);
SEXP convert_int_to_int64(SEXP int_vec);
SEXP convert_int64_to_int(SEXP int64_vec);


// creating new r6 classes
SEXP new_H5R_R6_class(char * class_name, SEXP num, SEXP id);


// callback functions for using H5Tconvert
typedef struct H5T_conv_op_data {
  bool H5T_CONV_EXCEPT_RANGE_HI;
  bool H5T_CONV_EXCEPT_RANGE_LOW;
  bool H5T_CONV_EXCEPT_TRUNCATE;
  bool H5T_CONV_EXCEPT_PRECISION;
  bool H5T_CONV_EXCEPT_PINF;
  bool H5T_CONV_EXCEPT_NINF;
  bool H5T_CONV_EXCEPT_NAN;
} H5T_conv_op_data;


void H5T_conv_log_issue(H5T_conv_except_t except_type, H5T_conv_op_data *conv_op_data);
int get_issue_string(H5T_conv_op_data conv_op_data, char* issue_string, size_t string_len);
// this callback function will do nothing (return that it is unhandled), and let hdf5 library handle it (which is usually truncation)
herr_t conv_cb_log(H5T_conv_except_t except_type, hid_t src_id, hid_t dst_id, void* src_buf, void* dst_buf, void* op_data);

// run the conversion; also collects issues and writes a warning; no background support; plist will be set inside the function
herr_t H5Tconvert_with_warning(hid_t src_type_id, hid_t dest_type_id, size_t nelmts, void* buf);

#endif


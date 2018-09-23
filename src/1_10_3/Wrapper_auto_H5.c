
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

#include "Wrapper_auto_H5.h"
/* H5_DLL herr_t H5check_version(unsigned majnum, unsigned minnum, unsigned relnum); */
SEXP R_H5check_version(SEXP R_majnum, SEXP R_minnum, SEXP R_relnum){
  int vars_protected=0;
  unsigned majnum = SEXP_to_longlong(R_majnum, 0);
  unsigned minnum = SEXP_to_longlong(R_minnum, 0);
  unsigned relnum = SEXP_to_longlong(R_relnum, 0);
  herr_t return_val = H5check_version(majnum, minnum, relnum);
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

/* H5_DLL herr_t H5close(void); */
SEXP R_H5close(void){
  int vars_protected=0;
  herr_t return_val = H5close();
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

/* H5_DLL herr_t H5dont_atexit(void); */
SEXP R_H5dont_atexit(void){
  int vars_protected=0;
  herr_t return_val = H5dont_atexit();
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

/* H5_DLL herr_t H5free_memory(void *mem); */
SEXP R_H5free_memory(SEXP R_mem, SEXP _dupl_mem){
  int vars_protected=0;
  if(SEXP_to_logical(_dupl_mem)) {
    R_mem = PROTECT(duplicate(R_mem));
    vars_protected++;
  }
  void* mem;
  if(XLENGTH(R_mem) == 0) {
    mem = NULL;
  }
  else {
    mem = (void *) VOIDPTR(R_mem);
  }
  herr_t return_val = H5free_memory(mem);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_mem);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("mem"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5garbage_collect(void); */
SEXP R_H5garbage_collect(void){
  int vars_protected=0;
  herr_t return_val = H5garbage_collect();
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

/* H5_DLL herr_t H5get_libversion(unsigned *majnum, unsigned *minnum, unsigned *relnum); */
SEXP R_H5get_libversion(SEXP R_majnum, SEXP R_minnum, SEXP R_relnum){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_majnum = PROTECT(duplicate(R_majnum));
  vars_protected++;
  R_minnum = PROTECT(duplicate(R_minnum));
  vars_protected++;
  R_relnum = PROTECT(duplicate(R_relnum));
  vars_protected++;
  unsigned* majnum;
  if(XLENGTH(R_majnum) == 0) {
    majnum = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_majnum, h5_datatype[DT_unsigned], XLENGTH(R_majnum)));
    majnum= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* minnum;
  if(XLENGTH(R_minnum) == 0) {
    minnum = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_minnum, h5_datatype[DT_unsigned], XLENGTH(R_minnum)));
    minnum= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  unsigned* relnum;
  if(XLENGTH(R_relnum) == 0) {
    relnum = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_relnum, h5_datatype[DT_unsigned], XLENGTH(R_relnum)));
    relnum= (unsigned*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5get_libversion(majnum, minnum, relnum);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_majnum, h5_datatype[DT_unsigned]);
  R_majnum = PROTECT(H5ToR_single_step(majnum, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_minnum, h5_datatype[DT_unsigned]);
  R_minnum = PROTECT(H5ToR_single_step(minnum, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_relnum, h5_datatype[DT_unsigned]);
  R_relnum = PROTECT(H5ToR_single_step(relnum, h5_datatype[DT_unsigned], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 4));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_majnum);
  SET_VECTOR_ELT(__ret_list, 2, R_minnum);
  SET_VECTOR_ELT(__ret_list, 3, R_relnum);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 4));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("majnum"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("minnum"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("relnum"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5is_library_threadsafe(hbool_t *is_ts); */
SEXP R_H5is_library_threadsafe(SEXP R_is_ts){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_is_ts = PROTECT(duplicate(R_is_ts));
  vars_protected++;
  hbool_t* is_ts;
  if(XLENGTH(R_is_ts) == 0) {
    is_ts = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_is_ts, h5_datatype[DT_hbool_t], XLENGTH(R_is_ts)));
    is_ts= (hbool_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5is_library_threadsafe(is_ts);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_is_ts, h5_datatype[DT_hbool_t]);
  R_is_ts = PROTECT(H5ToR_single_step(is_ts, h5_datatype[DT_hbool_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_is_ts);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("is_ts"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5open(void); */
SEXP R_H5open(void){
  int vars_protected=0;
  herr_t return_val = H5open();
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

/* H5_DLL herr_t H5set_free_list_limits (int reg_global_lim, int reg_list_lim, int arr_global_lim, int arr_list_lim, int blk_global_lim, int blk_list_lim); */
SEXP R_H5set_free_list_limits(SEXP R_reg_global_lim, SEXP R_reg_list_lim, SEXP R_arr_global_lim, SEXP R_arr_list_lim, SEXP R_blk_global_lim, SEXP R_blk_list_lim){
  int vars_protected=0;
  int reg_global_lim = SEXP_to_longlong(R_reg_global_lim, 0);
  int reg_list_lim = SEXP_to_longlong(R_reg_list_lim, 0);
  int arr_global_lim = SEXP_to_longlong(R_arr_global_lim, 0);
  int arr_list_lim = SEXP_to_longlong(R_arr_list_lim, 0);
  int blk_global_lim = SEXP_to_longlong(R_blk_global_lim, 0);
  int blk_list_lim = SEXP_to_longlong(R_blk_list_lim, 0);
  herr_t return_val = H5set_free_list_limits(reg_global_lim, reg_list_lim, arr_global_lim, arr_list_lim, blk_global_lim, blk_list_lim);
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


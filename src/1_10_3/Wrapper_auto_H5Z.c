
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

#include "Wrapper_auto_H5Z.h"
/* H5_DLL htri_t H5Zfilter_avail(H5Z_filter_t id); */
SEXP R_H5Zfilter_avail(SEXP R_id){
  int vars_protected=0;
  H5Z_filter_t id = SEXP_to_longlong(R_id, 0);
  htri_t return_val = H5Zfilter_avail(id);
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

/* H5_DLL herr_t H5Zget_filter_info(H5Z_filter_t filter, unsigned int *filter_config_flags); */
SEXP R_H5Zget_filter_info(SEXP R_filter, SEXP R_filter_config_flags){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_filter_config_flags = PROTECT(duplicate(R_filter_config_flags));
  vars_protected++;
  H5Z_filter_t filter = SEXP_to_longlong(R_filter, 0);
  unsigned int* filter_config_flags;
  if(XLENGTH(R_filter_config_flags) == 0) {
    filter_config_flags = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_filter_config_flags, h5_datatype[DT_unsigned_int], XLENGTH(R_filter_config_flags)));
    filter_config_flags= (unsigned int*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Zget_filter_info(filter, filter_config_flags);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_filter_config_flags, h5_datatype[DT_unsigned_int]);
  R_filter_config_flags = PROTECT(H5ToR_single_step(filter_config_flags, h5_datatype[DT_unsigned_int], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_filter_config_flags);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("filter_config_flags"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Zregister(const void *cls); */
SEXP R_H5Zregister(SEXP R_cls){
  int vars_protected=0;
  const void* cls;
  if(XLENGTH(R_cls) == 0) {
    cls = NULL;
  }
  else {
    cls = (void *) VOIDPTR(R_cls);
  }
  herr_t return_val = H5Zregister(cls);
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

/* H5_DLL herr_t H5Zunregister(H5Z_filter_t id); */
SEXP R_H5Zunregister(SEXP R_id){
  int vars_protected=0;
  H5Z_filter_t id = SEXP_to_longlong(R_id, 0);
  herr_t return_val = H5Zunregister(id);
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


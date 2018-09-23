
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

#include "Wrapper_auto_H5FDcore.h"
/* H5_DLL herr_t H5Pget_fapl_core(hid_t fapl_id, size_t *increment, hbool_t *backing_store); */
SEXP R_H5Pget_fapl_core(SEXP R_fapl_id, SEXP R_increment, SEXP R_backing_store){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_increment = PROTECT(duplicate(R_increment));
  vars_protected++;
  R_backing_store = PROTECT(duplicate(R_backing_store));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  size_t* increment;
  if(XLENGTH(R_increment) == 0) {
    increment = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_increment, h5_datatype[DT_size_t], XLENGTH(R_increment)));
    increment= (size_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hbool_t* backing_store;
  if(XLENGTH(R_backing_store) == 0) {
    backing_store = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_backing_store, h5_datatype[DT_hbool_t], XLENGTH(R_backing_store)));
    backing_store= (hbool_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_fapl_core(fapl_id, increment, backing_store);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_increment, h5_datatype[DT_size_t]);
  R_increment = PROTECT(H5ToR_single_step(increment, h5_datatype[DT_size_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_backing_store, h5_datatype[DT_hbool_t]);
  R_backing_store = PROTECT(H5ToR_single_step(backing_store, h5_datatype[DT_hbool_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_increment);
  SET_VECTOR_ELT(__ret_list, 2, R_backing_store);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("increment"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("backing_store"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pset_fapl_core(hid_t fapl_id, size_t increment, hbool_t backing_store); */
SEXP R_H5Pset_fapl_core(SEXP R_fapl_id, SEXP R_increment, SEXP R_backing_store){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  size_t increment = SEXP_to_longlong(R_increment, 0);
  hbool_t backing_store = SEXP_to_longlong(R_backing_store, 0);
  herr_t return_val = H5Pset_fapl_core(fapl_id, increment, backing_store);
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


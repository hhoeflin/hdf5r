
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

#include "Wrapper_auto_H5FDfamily.h"
/* H5_DLL hid_t H5FD_family_init(void); */
SEXP R_H5FD_family_init(void){
  int vars_protected=0;
  hid_t return_val = H5FD_family_init();
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

/* H5_DLL herr_t H5Pget_fapl_family(hid_t fapl_id, hsize_t *memb_size, hid_t *memb_fapl_id); */
SEXP R_H5Pget_fapl_family(SEXP R_fapl_id, SEXP R_memb_size, SEXP R_memb_fapl_id){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_memb_size = PROTECT(duplicate(R_memb_size));
  vars_protected++;
  R_memb_fapl_id = PROTECT(duplicate(R_memb_fapl_id));
  vars_protected++;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hsize_t* memb_size;
  if(XLENGTH(R_memb_size) == 0) {
    memb_size = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_memb_size, h5_datatype[DT_hsize_t], XLENGTH(R_memb_size)));
    memb_size= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hid_t* memb_fapl_id;
  if(XLENGTH(R_memb_fapl_id) == 0) {
    memb_fapl_id = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_memb_fapl_id, h5_datatype[DT_hid_t], XLENGTH(R_memb_fapl_id)));
    memb_fapl_id= (hid_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Pget_fapl_family(fapl_id, memb_size, memb_fapl_id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_memb_size, h5_datatype[DT_hsize_t]);
  R_memb_size = PROTECT(H5ToR_single_step(memb_size, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_memb_fapl_id, h5_datatype[DT_hid_t]);
  R_memb_fapl_id = PROTECT(H5ToR_single_step(memb_fapl_id, h5_datatype[DT_hid_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_memb_size);
  SET_VECTOR_ELT(__ret_list, 2, R_memb_fapl_id);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 3));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("memb_size"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("memb_fapl_id"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL herr_t H5Pset_fapl_family(hid_t fapl_id, hsize_t memb_size, hid_t memb_fapl_id); */
SEXP R_H5Pset_fapl_family(SEXP R_fapl_id, SEXP R_memb_size, SEXP R_memb_fapl_id){
  int vars_protected=0;
  hid_t fapl_id = SEXP_to_longlong(R_fapl_id, 0);
  hsize_t memb_size = SEXP_to_longlong(R_memb_size, 0);
  hid_t memb_fapl_id = SEXP_to_longlong(R_memb_fapl_id, 0);
  herr_t return_val = H5Pset_fapl_family(fapl_id, memb_size, memb_fapl_id);
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


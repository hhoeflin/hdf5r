
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

#include "Wrapper_auto_H5DS.h"
/* H5_HLDLL herr_t H5DSattach_scale( hid_t did, hid_t dsid, unsigned int idx); */
SEXP R_H5DSattach_scale(SEXP R_did, SEXP R_dsid, SEXP R_idx){
  int vars_protected=0;
  hid_t did = SEXP_to_longlong(R_did, 0);
  hid_t dsid = SEXP_to_longlong(R_dsid, 0);
  unsigned int idx = SEXP_to_longlong(R_idx, 0);
  herr_t return_val = H5DSattach_scale(did, dsid, idx);
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

/* H5_HLDLL herr_t H5DSdetach_scale( hid_t did, hid_t dsid, unsigned int idx); */
SEXP R_H5DSdetach_scale(SEXP R_did, SEXP R_dsid, SEXP R_idx){
  int vars_protected=0;
  hid_t did = SEXP_to_longlong(R_did, 0);
  hid_t dsid = SEXP_to_longlong(R_dsid, 0);
  unsigned int idx = SEXP_to_longlong(R_idx, 0);
  herr_t return_val = H5DSdetach_scale(did, dsid, idx);
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

/* H5_HLDLL ssize_t H5DSget_label( hid_t did, unsigned int idx, char *label, size_t size); */
SEXP R_H5DSget_label(SEXP R_did, SEXP R_idx, SEXP R_label, SEXP R_size){
  int vars_protected=0;
  R_label = PROTECT(duplicate(R_label));
  vars_protected++;
  hid_t did = SEXP_to_longlong(R_did, 0);
  unsigned int idx = SEXP_to_longlong(R_idx, 0);
  char* label;
  if(XLENGTH(R_label) == 0) {
    label = NULL;
  }
  else {
    label = R_alloc(strlen(CHAR(STRING_ELT(R_label, 0))) + 1, 1);
    strcpy(label, CHAR(STRING_ELT(R_label, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  ssize_t return_val = H5DSget_label(did, idx, label, size);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  if(label==NULL) {
    R_label = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_label = PROTECT(mkString(label));
    vars_protected++;
  }
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_label);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("label"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL int H5DSget_num_scales( hid_t did, unsigned int dim); */
SEXP R_H5DSget_num_scales(SEXP R_did, SEXP R_dim){
  int vars_protected=0;
  hid_t did = SEXP_to_longlong(R_did, 0);
  unsigned int dim = SEXP_to_longlong(R_dim, 0);
  int return_val = H5DSget_num_scales(did, dim);
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

/* H5_HLDLL ssize_t H5DSget_scale_name( hid_t did, char *name, size_t size); */
SEXP R_H5DSget_scale_name(SEXP R_did, SEXP R_name, SEXP R_size){
  int vars_protected=0;
  R_name = PROTECT(duplicate(R_name));
  vars_protected++;
  hid_t did = SEXP_to_longlong(R_did, 0);
  char* name;
  if(XLENGTH(R_name) == 0) {
    name = NULL;
  }
  else {
    name = R_alloc(strlen(CHAR(STRING_ELT(R_name, 0))) + 1, 1);
    strcpy(name, CHAR(STRING_ELT(R_name, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  ssize_t return_val = H5DSget_scale_name(did, name, size);
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

/* H5_HLDLL htri_t H5DSis_attached( hid_t did, hid_t dsid, unsigned int idx); */
SEXP R_H5DSis_attached(SEXP R_did, SEXP R_dsid, SEXP R_idx){
  int vars_protected=0;
  hid_t did = SEXP_to_longlong(R_did, 0);
  hid_t dsid = SEXP_to_longlong(R_dsid, 0);
  unsigned int idx = SEXP_to_longlong(R_idx, 0);
  htri_t return_val = H5DSis_attached(did, dsid, idx);
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

/* H5_HLDLL htri_t H5DSis_scale( hid_t did); */
SEXP R_H5DSis_scale(SEXP R_did){
  int vars_protected=0;
  hid_t did = SEXP_to_longlong(R_did, 0);
  htri_t return_val = H5DSis_scale(did);
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

/* H5_HLDLL herr_t H5DSset_label( hid_t did, unsigned int idx, const char *label); */
SEXP R_H5DSset_label(SEXP R_did, SEXP R_idx, SEXP R_label){
  int vars_protected=0;
  hid_t did = SEXP_to_longlong(R_did, 0);
  unsigned int idx = SEXP_to_longlong(R_idx, 0);
  const char* label = CHAR(STRING_ELT(R_label, 0));
  herr_t return_val = H5DSset_label(did, idx, label);
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

/* H5_HLDLL herr_t H5DSset_scale( hid_t dsid, const char *dimname); */
SEXP R_H5DSset_scale(SEXP R_dsid, SEXP R_dimname){
  int vars_protected=0;
  hid_t dsid = SEXP_to_longlong(R_dsid, 0);
  const char* dimname = CHAR(STRING_ELT(R_dimname, 0));
  herr_t return_val = H5DSset_scale(dsid, dimname);
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



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

#include "Wrapper_auto_H5I.h"
/* H5_DLL herr_t H5Iclear_type(H5I_type_t type, hbool_t force); */
SEXP R_H5Iclear_type(SEXP R_type, SEXP R_force){
  int vars_protected=0;
  H5I_type_t type = SEXP_to_longlong(R_type, 0);
  hbool_t force = SEXP_to_longlong(R_force, 0);
  herr_t return_val = H5Iclear_type(type, force);
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

/* H5_DLL int H5Idec_ref(hid_t id); */
SEXP R_H5Idec_ref(SEXP R_id){
  int vars_protected=0;
  hid_t id = SEXP_to_longlong(R_id, 0);
  int return_val = H5Idec_ref(id);
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

/* H5_DLL int H5Idec_type_ref(H5I_type_t type); */
SEXP R_H5Idec_type_ref(SEXP R_type){
  int vars_protected=0;
  H5I_type_t type = SEXP_to_longlong(R_type, 0);
  int return_val = H5Idec_type_ref(type);
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

/* H5_DLL herr_t H5Idestroy_type(H5I_type_t type); */
SEXP R_H5Idestroy_type(SEXP R_type){
  int vars_protected=0;
  H5I_type_t type = SEXP_to_longlong(R_type, 0);
  herr_t return_val = H5Idestroy_type(type);
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

/* H5_DLL hid_t H5Iget_file_id(hid_t id); */
SEXP R_H5Iget_file_id(SEXP R_id){
  int vars_protected=0;
  hid_t id = SEXP_to_longlong(R_id, 0);
  hid_t return_val = H5Iget_file_id(id);
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

/* H5_DLL ssize_t H5Iget_name(hid_t id, char *name, size_t size); */
SEXP R_H5Iget_name(SEXP R_id, SEXP R_name, SEXP R_size){
  int vars_protected=0;
  R_name = PROTECT(duplicate(R_name));
  vars_protected++;
  hid_t id = SEXP_to_longlong(R_id, 0);
  char* name;
  if(XLENGTH(R_name) == 0) {
    name = NULL;
  }
  else {
    name = R_alloc(strlen(CHAR(STRING_ELT(R_name, 0))) + 1, 1);
    strcpy(name, CHAR(STRING_ELT(R_name, 0)));
  }
  size_t size = SEXP_to_longlong(R_size, 0);
  ssize_t return_val = H5Iget_name(id, name, size);
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

/* H5_DLL int H5Iget_ref(hid_t id); */
SEXP R_H5Iget_ref(SEXP R_id){
  int vars_protected=0;
  hid_t id = SEXP_to_longlong(R_id, 0);
  int return_val = H5Iget_ref(id);
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

/* H5_DLL H5I_type_t H5Iget_type(hid_t id); */
SEXP R_H5Iget_type(SEXP R_id){
  int vars_protected=0;
  hid_t id = SEXP_to_longlong(R_id, 0);
  H5I_type_t return_val = H5Iget_type(id);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarFactor(return_val, h5_datatype[DT_H5I_type_t]));
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

/* H5_DLL int H5Iget_type_ref(H5I_type_t type); */
SEXP R_H5Iget_type_ref(SEXP R_type){
  int vars_protected=0;
  H5I_type_t type = SEXP_to_longlong(R_type, 0);
  int return_val = H5Iget_type_ref(type);
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

/* H5_DLL int H5Iinc_ref(hid_t id); */
SEXP R_H5Iinc_ref(SEXP R_id){
  int vars_protected=0;
  hid_t id = SEXP_to_longlong(R_id, 0);
  int return_val = H5Iinc_ref(id);
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

/* H5_DLL int H5Iinc_type_ref(H5I_type_t type); */
SEXP R_H5Iinc_type_ref(SEXP R_type){
  int vars_protected=0;
  H5I_type_t type = SEXP_to_longlong(R_type, 0);
  int return_val = H5Iinc_type_ref(type);
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

/* H5_DLL htri_t H5Iis_valid(hid_t id); */
SEXP R_H5Iis_valid(SEXP R_id){
  int vars_protected=0;
  hid_t id = SEXP_to_longlong(R_id, 0);
  htri_t return_val = H5Iis_valid(id);
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

/* H5_DLL herr_t H5Inmembers(H5I_type_t type, hsize_t *num_members); */
SEXP R_H5Inmembers(SEXP R_type, SEXP R_num_members){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_num_members = PROTECT(duplicate(R_num_members));
  vars_protected++;
  H5I_type_t type = SEXP_to_longlong(R_type, 0);
  hsize_t* num_members;
  if(XLENGTH(R_num_members) == 0) {
    num_members = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_num_members, h5_datatype[DT_hsize_t], XLENGTH(R_num_members)));
    num_members= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5Inmembers(type, num_members);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_num_members, h5_datatype[DT_hsize_t]);
  R_num_members = PROTECT(H5ToR_single_step(num_members, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_num_members);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("num_members"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_DLL hid_t H5Iregister(H5I_type_t type, const void *object); */
SEXP R_H5Iregister(SEXP R_type, SEXP R_object){
  int vars_protected=0;
  H5I_type_t type = SEXP_to_longlong(R_type, 0);
  const void* object;
  if(XLENGTH(R_object) == 0) {
    object = NULL;
  }
  else {
    object = (void *) VOIDPTR(R_object);
  }
  hid_t return_val = H5Iregister(type, object);
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

/* H5_DLL htri_t H5Itype_exists(H5I_type_t type); */
SEXP R_H5Itype_exists(SEXP R_type){
  int vars_protected=0;
  H5I_type_t type = SEXP_to_longlong(R_type, 0);
  htri_t return_val = H5Itype_exists(type);
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


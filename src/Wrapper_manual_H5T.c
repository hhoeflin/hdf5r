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


#include "Wrapper_manual_H5T.h"


SEXP h5create_compound_type(SEXP _names, SEXP _dtype_ids, SEXP _size, SEXP _offset) {
  size_t total_size, offset[LENGTH(_names)];
  herr_t status;

  // check if offset and size are given, if not, ignore both
  if(XLENGTH(_size) == 0 || XLENGTH(_offset) == 0) {
    total_size = 0;
    for(int i=0; i < LENGTH(_names); i++) {
      offset[i] = total_size;
      total_size += H5Tget_size(SEXP_to_longlong(_dtype_ids, i));
    }

  }
  else {
    total_size = SEXP_to_longlong(_size, 0);
    for(int i=0; i < XLENGTH(_offset); ++i) {
      offset[i] = INTEGER(_offset)[i];
    }
  }

  hid_t cpd_dtype_id = H5Tcreate(H5T_COMPOUND, total_size);

  for(int i=0; i< LENGTH(_names); i++) {
    status = H5Tinsert(cpd_dtype_id, CHAR(STRING_ELT(_names, i)), offset[i], SEXP_to_longlong(_dtype_ids, i));
    if(status < 0) {
      error("Cannot insert type %lld\n", SEXP_to_longlong(_dtype_ids, i));
    }
  }

  SEXP _return_val = PROTECT(ScalarInteger64(cpd_dtype_id));
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, _return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  UNPROTECT(3);
  return(__ret_list);
}

SEXP h5create_enum_type(SEXP _labels, SEXP _values, SEXP _dtype_id) {
  herr_t status;
  hid_t dtype_id = SEXP_to_longlong(_dtype_id, 0);
  hid_t datatype = H5Tenum_create(dtype_id);
  long long buf;
  if(datatype < 0) {
    error("Cannot create new enum_type\n");
  }
  for(int i=0; i < LENGTH(_labels); i++) {
    buf = SEXP_to_longlong(_values, i);
    H5Tconvert(H5T_NATIVE_LLONG, dtype_id, 1, &buf, NULL, H5P_DEFAULT);
    status = H5Tenum_insert(datatype, CHAR(STRING_ELT(_labels, i)), &buf);
    if(status < 0) {
      error("Could not insert value into enum %s value %lld with status %d\n", CHAR(STRING_ELT(_labels, i)), buf, status);
    }
  }

  SEXP _return_val = PROTECT(ScalarInteger64(datatype));
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, _return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  UNPROTECT(3);
  return(__ret_list);
}




SEXP h5get_enum_labels(SEXP _dtype_id) {
  hid_t enum_type = SEXP_to_longlong(_dtype_id, 0);

  size_t numValues = H5Tget_nmembers(enum_type);

  SEXP _return_val = PROTECT(allocVector(STRSXP, numValues));

  char* member_name;
  for(unsigned int i=0; i<numValues; i++) {
    member_name = H5Tget_member_name(enum_type, i);
    SET_STRING_ELT(_return_val, i, mkChar(member_name));
    H5free_memory(member_name);
  }

  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, _return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  UNPROTECT(3);
  return(__ret_list);
}

SEXP h5get_enum_values(SEXP _dtype_id) {
  hid_t enum_type = SEXP_to_longlong(_dtype_id, 0);
  hid_t enum_base_type = H5Tget_super(enum_type);
  hsize_t enum_base_size = H5Tget_size(enum_base_type);
  int enum_base_signed = H5Tget_sign(enum_base_type) == H5T_SGN_2;

  size_t numValues = H5Tget_nmembers(enum_type);

  int needs_llong = (enum_base_size > 4 || (enum_base_size==4 && !enum_base_signed));

  if(enum_base_size > sizeof(long long)) {
    error("Cannot read an enum with a size > long long");
  }

  SEXP _return_val;
  if(needs_llong) {
    _return_val = PROTECT(allocVector(REALSXP, numValues));
    SET_CLASS(_return_val, ScalarString(mkChar("integer64")));
  }
  else {
    _return_val = PROTECT(allocVector(INTSXP, numValues));
  }

  long long enum_val;
  for(unsigned int i=0; i<numValues; i++) {
    H5Tget_member_value(enum_type, i, &enum_val);
    H5Tconvert(enum_base_type, H5T_NATIVE_LLONG, 1, &enum_val, NULL, H5P_DEFAULT);
    if(needs_llong) {
      ((long long *)REAL(_return_val))[i] = enum_val;
    }
    else {
      INTEGER(_return_val)[i] = enum_val;
    }
  }
  H5Tclose(enum_base_type);
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, _return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  UNPROTECT(3);
  return(__ret_list);
}



SEXP h5get_compound_types(SEXP _dtype_id) {
  hid_t cpd_type = SEXP_to_longlong(_dtype_id, 0);
  size_t numValues = H5Tget_nmembers(cpd_type);

  SEXP _return_val = PROTECT(allocVector(REALSXP, numValues));
  SET_CLASS(_return_val, ScalarString(mkChar("integer64")));

  for(unsigned int i=0; i<numValues; i++) {
    ((long long*)REAL(_return_val))[i]= H5Tget_member_type(cpd_type, i);
  }

  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, _return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  UNPROTECT(3);
  return(__ret_list);
}

SEXP h5get_compound_names(SEXP _dtype_id) {
  hid_t cpd_type = SEXP_to_longlong(_dtype_id, 0);
  size_t numValues = H5Tget_nmembers(cpd_type);

  SEXP _return_val = PROTECT(allocVector(STRSXP, numValues));
  char *member_name;
  for(unsigned int i=0; i<numValues; i++) {
    member_name = H5Tget_member_name(cpd_type, i);
    SET_STRING_ELT(_return_val, i, mkChar(member_name));
    H5free_memory(member_name);
  }

  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, _return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  UNPROTECT(3);
  return(__ret_list);
}


SEXP h5get_compound_classes(SEXP _dtype_id) {
  hid_t cpd_type = SEXP_to_longlong(_dtype_id, 0);
  size_t numValues = H5Tget_nmembers(cpd_type);

  H5T_class_t member_classes[numValues];

  for(unsigned int i=0; i<numValues; i++) {
    member_classes[i]= H5Tget_member_class(cpd_type, i);
  }

  SEXP _return_val = PROTECT(H5ToR_single_step(member_classes, h5_datatype[DT_H5T_class_t], numValues, H5TOR_CONV_INT64_NOLOSS));
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, _return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  UNPROTECT(3);
  return(__ret_list);
}


SEXP h5get_compound_offsets(SEXP _dtype_id) {
  hid_t cpd_type = SEXP_to_longlong(_dtype_id, 0);
  size_t numValues = H5Tget_nmembers(cpd_type);

  SEXP _return_val = PROTECT(allocVector(INTSXP, numValues));

  for(unsigned int i=0; i<numValues; i++) {
    INTEGER(_return_val)[i]= H5Tget_member_offset(cpd_type, i);
  }

  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, _return_val);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  UNPROTECT(3);
  return(__ret_list);
}



SEXP R_H5Tdetect_vlen(SEXP _dtype_id) {
  hid_t dtype_id = SEXP_to_longlong(_dtype_id, 0);

  // call the detect_class function is VLEN
  // but this does not check if it is a variable length string
  htri_t is_vlen = H5Tdetect_class(dtype_id, H5T_VLEN);
  // if it is not already vlen, check if it is a variabe lenght string
  if(is_vlen <= 0) {
    htri_t is_string = H5Tdetect_class(dtype_id, H5T_STRING);
    if(is_string) {
      is_vlen = H5Tis_variable_str(dtype_id);
    }
  }

  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 1));
  SET_VECTOR_ELT(__ret_list, 0, ScalarInteger(is_vlen));
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 1));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_NAMES(__ret_list, __ret_list_names);
  UNPROTECT(2);
  return(__ret_list);
}




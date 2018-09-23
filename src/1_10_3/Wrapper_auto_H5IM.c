
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

#include "Wrapper_auto_H5IM.h"
/* H5_HLDLL herr_t H5IMget_image_info( hid_t loc_id, const char *dset_name, hsize_t *width, hsize_t *height, hsize_t *planes, char *interlace, hssize_t *npals ); */
SEXP R_H5IMget_image_info(SEXP R_loc_id, SEXP R_dset_name, SEXP R_width, SEXP R_height, SEXP R_planes, SEXP R_interlace, SEXP R_npals){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_width = PROTECT(duplicate(R_width));
  vars_protected++;
  R_height = PROTECT(duplicate(R_height));
  vars_protected++;
  R_planes = PROTECT(duplicate(R_planes));
  vars_protected++;
  R_interlace = PROTECT(duplicate(R_interlace));
  vars_protected++;
  R_npals = PROTECT(duplicate(R_npals));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t* width;
  if(XLENGTH(R_width) == 0) {
    width = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_width, h5_datatype[DT_hsize_t], XLENGTH(R_width)));
    width= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* height;
  if(XLENGTH(R_height) == 0) {
    height = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_height, h5_datatype[DT_hsize_t], XLENGTH(R_height)));
    height= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  hsize_t* planes;
  if(XLENGTH(R_planes) == 0) {
    planes = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_planes, h5_datatype[DT_hsize_t], XLENGTH(R_planes)));
    planes= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  char* interlace;
  if(XLENGTH(R_interlace) == 0) {
    interlace = NULL;
  }
  else {
    interlace = R_alloc(strlen(CHAR(STRING_ELT(R_interlace, 0))) + 1, 1);
    strcpy(interlace, CHAR(STRING_ELT(R_interlace, 0)));
  }
  hssize_t* npals;
  if(XLENGTH(R_npals) == 0) {
    npals = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_npals, h5_datatype[DT_hssize_t], XLENGTH(R_npals)));
    npals= (hssize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5IMget_image_info(loc_id, dset_name, width, height, planes, interlace, npals);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_width, h5_datatype[DT_hsize_t]);
  R_width = PROTECT(H5ToR_single_step(width, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_height, h5_datatype[DT_hsize_t]);
  R_height = PROTECT(H5ToR_single_step(height, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  size_helper = guess_nelem(R_planes, h5_datatype[DT_hsize_t]);
  R_planes = PROTECT(H5ToR_single_step(planes, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  if(interlace==NULL) {
    R_interlace = PROTECT(NEW_CHARACTER(0));
    vars_protected++;
  }
  else {
    R_interlace = PROTECT(mkString(interlace));
    vars_protected++;
  }
  size_helper = guess_nelem(R_npals, h5_datatype[DT_hssize_t]);
  R_npals = PROTECT(H5ToR_single_step(npals, h5_datatype[DT_hssize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 6));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_width);
  SET_VECTOR_ELT(__ret_list, 2, R_height);
  SET_VECTOR_ELT(__ret_list, 3, R_planes);
  SET_VECTOR_ELT(__ret_list, 4, R_interlace);
  SET_VECTOR_ELT(__ret_list, 5, R_npals);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 6));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("width"));
  SET_STRING_ELT(__ret_list_names, 2, mkChar("height"));
  SET_STRING_ELT(__ret_list_names, 3, mkChar("planes"));
  SET_STRING_ELT(__ret_list_names, 4, mkChar("interlace"));
  SET_STRING_ELT(__ret_list_names, 5, mkChar("npals"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5IMget_npalettes( hid_t loc_id, const char *image_name, hssize_t *npals ); */
SEXP R_H5IMget_npalettes(SEXP R_loc_id, SEXP R_image_name, SEXP R_npals){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_npals = PROTECT(duplicate(R_npals));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* image_name = CHAR(STRING_ELT(R_image_name, 0));
  hssize_t* npals;
  if(XLENGTH(R_npals) == 0) {
    npals = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_npals, h5_datatype[DT_hssize_t], XLENGTH(R_npals)));
    npals= (hssize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5IMget_npalettes(loc_id, image_name, npals);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_npals, h5_datatype[DT_hssize_t]);
  R_npals = PROTECT(H5ToR_single_step(npals, h5_datatype[DT_hssize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_npals);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("npals"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5IMget_palette( hid_t loc_id, const char *image_name, int pal_number, unsigned char *pal_data ); */
SEXP R_H5IMget_palette(SEXP R_loc_id, SEXP R_image_name, SEXP R_pal_number, SEXP R_pal_data){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_pal_data = PROTECT(duplicate(R_pal_data));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* image_name = CHAR(STRING_ELT(R_image_name, 0));
  int pal_number = SEXP_to_longlong(R_pal_number, 0);
  unsigned char* pal_data;
  if(XLENGTH(R_pal_data) == 0) {
    pal_data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_pal_data, h5_datatype[DT_unsigned_char], XLENGTH(R_pal_data)));
    pal_data= (unsigned char*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5IMget_palette(loc_id, image_name, pal_number, pal_data);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_pal_data, h5_datatype[DT_unsigned_char]);
  R_pal_data = PROTECT(H5ToR_single_step(pal_data, h5_datatype[DT_unsigned_char], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_pal_data);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("pal_data"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5IMget_palette_info( hid_t loc_id, const char *image_name, int pal_number, hsize_t *pal_dims ); */
SEXP R_H5IMget_palette_info(SEXP R_loc_id, SEXP R_image_name, SEXP R_pal_number, SEXP R_pal_dims){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_pal_dims = PROTECT(duplicate(R_pal_dims));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* image_name = CHAR(STRING_ELT(R_image_name, 0));
  int pal_number = SEXP_to_longlong(R_pal_number, 0);
  hsize_t* pal_dims;
  if(XLENGTH(R_pal_dims) == 0) {
    pal_dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_pal_dims, h5_datatype[DT_hsize_t], XLENGTH(R_pal_dims)));
    pal_dims= (hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5IMget_palette_info(loc_id, image_name, pal_number, pal_dims);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_pal_dims, h5_datatype[DT_hsize_t]);
  R_pal_dims = PROTECT(H5ToR_single_step(pal_dims, h5_datatype[DT_hsize_t], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_pal_dims);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("pal_dims"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5IMis_image( hid_t loc_id, const char *dset_name ); */
SEXP R_H5IMis_image(SEXP R_loc_id, SEXP R_dset_name){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  herr_t return_val = H5IMis_image(loc_id, dset_name);
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

/* H5_HLDLL herr_t H5IMis_palette( hid_t loc_id, const char *dset_name ); */
SEXP R_H5IMis_palette(SEXP R_loc_id, SEXP R_dset_name){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  herr_t return_val = H5IMis_palette(loc_id, dset_name);
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

/* H5_HLDLL herr_t H5IMlink_palette( hid_t loc_id, const char *image_name, const char *pal_name ); */
SEXP R_H5IMlink_palette(SEXP R_loc_id, SEXP R_image_name, SEXP R_pal_name){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* image_name = CHAR(STRING_ELT(R_image_name, 0));
  const char* pal_name = CHAR(STRING_ELT(R_pal_name, 0));
  herr_t return_val = H5IMlink_palette(loc_id, image_name, pal_name);
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

/* H5_HLDLL herr_t H5IMmake_image_24bit( hid_t loc_id, const char *dset_name, hsize_t width, hsize_t height, const char *interlace, const unsigned char *buffer ); */
SEXP R_H5IMmake_image_24bit(SEXP R_loc_id, SEXP R_dset_name, SEXP R_width, SEXP R_height, SEXP R_interlace, SEXP R_buffer){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t width = SEXP_to_longlong(R_width, 0);
  hsize_t height = SEXP_to_longlong(R_height, 0);
  const char* interlace = CHAR(STRING_ELT(R_interlace, 0));
  const unsigned char* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_unsigned_char], XLENGTH(R_buffer)));
    buffer= (const unsigned char*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5IMmake_image_24bit(loc_id, dset_name, width, height, interlace, buffer);
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

/* H5_HLDLL herr_t H5IMmake_image_8bit( hid_t loc_id, const char *dset_name, hsize_t width, hsize_t height, const unsigned char *buffer ); */
SEXP R_H5IMmake_image_8bit(SEXP R_loc_id, SEXP R_dset_name, SEXP R_width, SEXP R_height, SEXP R_buffer){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  hsize_t width = SEXP_to_longlong(R_width, 0);
  hsize_t height = SEXP_to_longlong(R_height, 0);
  const unsigned char* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_unsigned_char], XLENGTH(R_buffer)));
    buffer= (const unsigned char*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5IMmake_image_8bit(loc_id, dset_name, width, height, buffer);
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

/* H5_HLDLL herr_t H5IMmake_palette( hid_t loc_id, const char *pal_name, const hsize_t *pal_dims, const unsigned char *pal_data ); */
SEXP R_H5IMmake_palette(SEXP R_loc_id, SEXP R_pal_name, SEXP R_pal_dims, SEXP R_pal_data){
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* pal_name = CHAR(STRING_ELT(R_pal_name, 0));
  const hsize_t* pal_dims;
  if(XLENGTH(R_pal_dims) == 0) {
    pal_dims = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_pal_dims, h5_datatype[DT_hsize_t], XLENGTH(R_pal_dims)));
    pal_dims= (const hsize_t*) VOIDPTR(R_helper);
    vars_protected++;
  }
  const unsigned char* pal_data;
  if(XLENGTH(R_pal_data) == 0) {
    pal_data = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_pal_data, h5_datatype[DT_unsigned_char], XLENGTH(R_pal_data)));
    pal_data= (const unsigned char*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5IMmake_palette(loc_id, pal_name, pal_dims, pal_data);
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

/* H5_HLDLL herr_t H5IMread_image( hid_t loc_id, const char *dset_name, unsigned char *buffer ); */
SEXP R_H5IMread_image(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer){
  hsize_t size_helper;
  SEXP R_helper = R_NilValue;
  int vars_protected=0;
  R_buffer = PROTECT(duplicate(R_buffer));
  vars_protected++;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* dset_name = CHAR(STRING_ELT(R_dset_name, 0));
  unsigned char* buffer;
  if(XLENGTH(R_buffer) == 0) {
    buffer = NULL;
  }
  else {
    R_helper = PROTECT(RToH5(R_buffer, h5_datatype[DT_unsigned_char], XLENGTH(R_buffer)));
    buffer= (unsigned char*) VOIDPTR(R_helper);
    vars_protected++;
  }
  herr_t return_val = H5IMread_image(loc_id, dset_name, buffer);
  SEXP R_return_val= R_NilValue;
  R_return_val = PROTECT(ScalarInteger64_or_int(return_val));
  vars_protected++;
  size_helper = guess_nelem(R_buffer, h5_datatype[DT_unsigned_char]);
  R_buffer = PROTECT(H5ToR_single_step(buffer, h5_datatype[DT_unsigned_char], size_helper, H5TOR_CONV_INT64_NOLOSS));
  vars_protected++;
  SEXP __ret_list;
  PROTECT(__ret_list = allocVector(VECSXP, 2));
  SET_VECTOR_ELT(__ret_list, 0, R_return_val);
  SET_VECTOR_ELT(__ret_list, 1, R_buffer);
  SEXP __ret_list_names;
  PROTECT(__ret_list_names = allocVector(STRSXP, 2));
  SET_STRING_ELT(__ret_list_names, 0, mkChar("return_val"));
  SET_STRING_ELT(__ret_list_names, 1, mkChar("buffer"));
  SET_NAMES(__ret_list, __ret_list_names);
  vars_protected += 2;
  UNPROTECT(vars_protected);
  return(__ret_list);
}

/* H5_HLDLL herr_t H5IMunlink_palette( hid_t loc_id, const char *image_name, const char *pal_name ); */
SEXP R_H5IMunlink_palette(SEXP R_loc_id, SEXP R_image_name, SEXP R_pal_name){
  int vars_protected=0;
  hid_t loc_id = SEXP_to_longlong(R_loc_id, 0);
  const char* image_name = CHAR(STRING_ELT(R_image_name, 0));
  const char* pal_name = CHAR(STRING_ELT(R_pal_name, 0));
  herr_t return_val = H5IMunlink_palette(loc_id, image_name, pal_name);
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


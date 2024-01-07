
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


#include "convert.h"

/*********************************************************************************
 * Functions for converting an R object to HDF5
 *********************************************************************************/
SEXP R_RToH5(SEXP _Robj, SEXP _dtype_id, SEXP _nelem) {
  // simply unwrap the _dtype_id and _nelem and pass it to RToH5
  hid_t dtype_id = SEXP_to_longlong(_dtype_id, 0);
  R_xlen_t nelem = SEXP_to_xlen(_nelem);
  return(RToH5(_Robj, dtype_id, nelem));
}

SEXP RToH5(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
  // dispatch based on the class_name
  H5T_class_t dtype_class = H5Tget_class(dtype_id);
  
  // adds a switch so that one can pass an "empty" r object
  // will just be a raw vector with class _RToH5_empty
  // and length equal to nelem
  // in this case, an empty raw vector of appropriate size will be returned
  SEXP Rval;
  if(is_RToH5_empty(_Robj, nelem)) {
    R_xlen_t vec_size = nelem * H5Tget_size(dtype_id);
    Rval = PROTECT(NEW_RAW(vec_size));
    // initialize array to 0
    memset(VOIDPTR(Rval), 0, vec_size);
  }
  else {
    switch(dtype_class) {
    case H5T_COMPOUND:
      if(TYPEOF(_Robj)==CPLXSXP) {
	PROTECT(Rval = RToH5_RComplex(_Robj, dtype_id, nelem));
      }
      else {
	PROTECT(Rval = RToH5_COMPOUND(_Robj, dtype_id, nelem));
      }
      break;
    case H5T_ARRAY:
      PROTECT(Rval = RToH5_ARRAY(_Robj, dtype_id, nelem));
      break;
    case H5T_ENUM:
      PROTECT(Rval = RToH5_ENUM(_Robj, dtype_id, nelem));
      break;
    case H5T_BITFIELD:
    case H5T_INTEGER:
      PROTECT(Rval = RToH5_INTEGER(_Robj, dtype_id, nelem));
      break;
    case H5T_FLOAT:
      PROTECT(Rval = RToH5_FLOAT(_Robj, dtype_id, nelem));
      break;
    case H5T_STRING:
      PROTECT(Rval = RToH5_STRING(_Robj, dtype_id, nelem));
      break;
    case H5T_OPAQUE:
      PROTECT(Rval = RToH5_OPAQUE(_Robj, dtype_id, nelem));
      break;
    case H5T_REFERENCE:
      PROTECT(Rval = RToH5_REFERENCE(_Robj, dtype_id, nelem));
      break;
    case H5T_VLEN:
      PROTECT(Rval = RToH5_VLEN(_Robj, dtype_id, nelem));
      break;
    default:
      error("Error when retrieving class");
    }
  }
  UNPROTECT(1);
  return(Rval);
}


SEXP RToH5_RComplex(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
  // check that _Robj is actually complex
  if(TYPEOF(_Robj) != CPLXSXP) {
    error("R object passed with Compound looking like a complex variable, is not a complex variable");
  }

  // check that the compound is looking like an h5_complex compound
  if(!is_h5_complex(dtype_id)) {
    error("Complex R variable passed, but compound does not look like an h5_complex compound. Needs to be a compound with 2 equal sized float variables with a name of the first variable starting with 'Re' and the second variable starting with 'Im'\n");
  }
  
  // check that the size is correct
  if(XLENGTH(_Robj) != nelem) {
    error("Length of R object not correct");
  }
  
  // pass it to the REAL variable analyzer
  hid_t dtype_member = H5Tget_member_type(dtype_id, 0);
  SEXP res;
  PROTECT(res = RToH5_FLOAT(_Robj, dtype_member, nelem * 2));
  H5Tclose(dtype_member);
  UNPROTECT(1);

  return(res);
}

SEXP RToH5_COMPOUND(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
 
  if(!is_robj_compound(_Robj, dtype_id, nelem)) {
    error("The Robj does not match the data structure of the compound datatype\n");
  }

  if(nelem != XLENGTH(VECTOR_ELT(_Robj, 0))) {
    error("Number of rows in Compound not as expected\n");
  };
  
  // allocate the raw vector that will hold the data
  hsize_t total_size = H5Tget_size(dtype_id);
  SEXP Rval, Rval_attributes;
  PROTECT(Rval = allocVector(RAWSXP, nelem * total_size));
  // for variable length arrays, we need to attach the corresponding data somehow; 
  // do this by attaching a list to the attributes that collects the corresponding 
  // attributes returned by RToH5 functions inside the loop
  PROTECT(Rval_attributes = allocVector(VECSXP, XLENGTH(_Robj)));

  // now we need to copy the data over for every list element, depending on the type
  hsize_t offset = 0;
  for(int i=0; i < LENGTH(_Robj); i++) {
    // get the type and its size
    hid_t cpd_item_id = H5Tget_member_type(dtype_id, i);
    offset = H5Tget_member_offset(dtype_id, i);
    if(cpd_item_id < 0) {
      error("An error occured when fetching the a compound item\n");
    }
    hsize_t item_size = H5Tget_size(cpd_item_id);

    // wrap the cpd_item_id in an R object
    SEXP R_item = PROTECT(RToH5(VECTOR_ELT(_Robj, i), cpd_item_id, nelem));
    // copy the h5_store attribute; if it doesn't exist, will be null
    SET_VECTOR_ELT(Rval_attributes, i, GET_ATTR(R_item, install("h5_store")));
    memcpy_to_record(VOIDPTR(Rval), VOIDPTR(R_item), nelem, total_size, offset, item_size);
    H5Tclose(cpd_item_id);
    UNPROTECT(1);
  }

  // install it in the attributes 
  SET_ATTR(Rval, install("h5_store"), Rval_attributes);
  
  UNPROTECT(2);
  return Rval;

}

SEXP RToH5_ARRAY(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
  // First we check that the dtype and the Robj have matching dimensions
  if(!is_robj_array(_Robj, dtype_id)) {
    error("The Robj does not match the data type");
  }

  // then put it back into the RToH5 Function with its own base type, so that they base type
  // is properly handled
  hsize_t num_rows = nelem;
  hid_t dtype_base = H5Tget_super(dtype_id);
  hsize_t dtype_base_size = H5Tget_size(dtype_base);
  hsize_t num_cols = H5Tget_size(dtype_id) / dtype_base_size;
    

  // now call itself on the copied object 
  SEXP res;
  PROTECT(res = RToH5(_Robj, dtype_base, num_rows * num_cols));
  H5Tclose(dtype_base);


  // now, need to transpose the input so that the data inside the array is in consecutive order 
  // but only if there is more than one element
  // (i.e. on the first dimensions)
  if(nelem != 1) {
    SEXP res_copy = PROTECT(duplicate(res)); // use this as the target to write the transposed data in
    transpose_general(VOIDPTR(res_copy), VOIDPTR(res), num_rows, num_cols, dtype_base_size, true);
    UNPROTECT(2);
    return(res_copy);
  }
  else {
    UNPROTECT(1);
    return(res);
  }
}

SEXP RToH5_ENUM(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
  // this can just be done by calling the Integer conversion on the enum base type
  // but before should check if the R object and the enum are compatible
  // R object doesn't have to be a "factor", but it should have a levels attribute 
  // that matches the levels in enum; if it is not a factor, should also have a values attribute
  if(is_enum_logical(dtype_id)) {
    // need to coerce to logical; capture if NAs are in there 
    // throw error if the logical type doesn't support NAs
    // convert to value 2 if it does
    SEXP obj_logical;
    if(!isLogical(_Robj)) {
      obj_logical = PROTECT(AS_LOGICAL(_Robj));
    }
    else {
      obj_logical = PROTECT(duplicate(_Robj));
    }
    int enum_size = H5Tget_nmembers(dtype_id);
    if(enum_size == 2) {
      // throw an error if object contains an NA
      for(R_xlen_t i =0; i < nelem; ++i) {
	if(LOGICAL(obj_logical)[i] == NA_LOGICAL) {
	  error("Trying to save an R-Logical vector with NA into an HDF5-Logical Enum without NA");
	}
      }
    }
    else if(enum_size == 3) {
      // convert value to 2 if object contains an NA
      for(R_xlen_t i =0; i < nelem; ++i) {
	if(LOGICAL(obj_logical)[i] == NA_LOGICAL) {
	  LOGICAL(obj_logical)[i] = 2;
	}
      }
    }
    else {
      error("Logical enum cannot have size other than 2 or 3");
    }
    hid_t dtype_base = H5Tget_super(dtype_id);
    SEXP Rval;
    PROTECT(Rval = RToH5_INTEGER(obj_logical, dtype_base, nelem));
    H5Tclose(dtype_base);
    UNPROTECT(2);
    return(Rval);

  }
  else {
    if(!is_robj_enum(_Robj, dtype_id)) {
      error("Robj to convert does not match enum datatype");
    }
    
    hid_t dtype_base = H5Tget_super(dtype_id);
    SEXP Rval;
    PROTECT(Rval = RToH5_INTEGER(_Robj, dtype_base, nelem));
    H5Tclose(dtype_base);
    UNPROTECT(1);
    return(Rval);
  }
}

SEXP RToH5_INTEGER(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
  SEXP Rval;

  if(nelem != XLENGTH(_Robj)) {
    error("Length of integer vector not as expected: Actual: %ld; Expected %ld\n", XLENGTH(_Robj), nelem);
  }

  switch(TYPEOF(_Robj)) {
  case REALSXP: {
    // check if it is a 64bit integer, then need to coerce it to double
    if(!is_rint64(_Robj)) {
      // it is float, 
      // two cases; if the result is UINT64, then will treat it special; 
      // otherwise convert to integer64 and rerun
      htri_t isUINT64 = H5Tequal(dtype_id, H5T_NATIVE_UINT64);
      if(isUINT64 < 0) {
	error("Error when comparing type to UINT64\n");
      }
      if(isUINT64) {
	// convert to UINT64 and return
	PROTECT(Rval = NEW_NUMERIC(nelem));
	uint64_t* uint64_ptr = (uint64_t *) REAL(Rval);
	double* dbl_ptr = REAL(_Robj);
	double dbl_max_unit64 = pow(2, 64);
	for(R_xlen_t i = 0; i < nelem; ++i) {
	  if(dbl_ptr[i] < 0) {
	    uint64_ptr[i] = 0;
	  }
	  else if(dbl_ptr[i] >= dbl_max_unit64) {
	    uint64_ptr[i] = ULLONG_MAX;
	  }
	  else if(isnan(dbl_ptr[i])) {

	  } 
	  else {
	    uint64_ptr[i] = dbl_ptr[i];
	  }
	}
	UNPROTECT(1);
	return(Rval);
      }
      else {
        PROTECT(Rval = convert_double_to_int64(_Robj));
        PROTECT(Rval = RToH5_INTEGER(Rval, dtype_id, nelem));
        UNPROTECT(2);
        return(Rval);
      }
    } 
    else {
      int isNativeLLong = H5Tequal(dtype_id, H5T_NATIVE_LLONG);
      if(isNativeLLong < 0) {
	error("Error when comparing if is native long long\n");
      }
      if(isNativeLLong) { // size of a regular llong, no conversion necessary
	return(_Robj);
      }
      
      // check if it is NATIVE_INT -> then will use R's NA-aware conversion
      int isNativeInt = H5Tequal(dtype_id, H5T_NATIVE_INT);
      if(isNativeInt < 0) {
	error("Error when comparing if is native int\n");
      }
      if(isNativeInt) { // size of a regular llong, no conversion necessary
	return(convert_int64_to_int(_Robj));
      }

      // needs to convert to smaller integer; do it and return
      PROTECT(Rval = NEW_NUMERIC(nelem)); // assumes long long is same size as double (but entire bit64 package assumes that 
      memcpy(VOIDPTR(Rval), VOIDPTR(_Robj), nelem * sizeof(long long));
      H5Tconvert_with_warning(H5T_NATIVE_LLONG, dtype_id, nelem, VOIDPTR(Rval)); 
      UNPROTECT(1);
      return(Rval);
    }
  }
  case LGLSXP: // treat logical same as integer
  case INTSXP: {
    int isNativeInt = H5Tequal(dtype_id, H5T_NATIVE_INT);
    if(isNativeInt < 0) {
      error("Error when comparing if is native integer\n");
    }
    if(isNativeInt) { // size of a regular int, no conversion necessary
      return(_Robj);
    }

    int dtype_size = H5Tget_size(dtype_id);
    H5T_sign_t dtype_sign = H5Tget_sign(dtype_id);

    // need to check; if size is > 4, then need to convert to INT64 for correct NA handling;
    // which is unimportant for unsigned integers
    // so convert to int64 if signed and size > 4
    // and then run everything again
    if(dtype_sign == H5T_SGN_2 && dtype_size > 4) {
      PROTECT(Rval = convert_int_to_int64(_Robj));
      PROTECT(Rval = RToH5_INTEGER(Rval, dtype_id, nelem));
      UNPROTECT(2);
      return(Rval);
    }
    else {
      // needs to convert to other integer; make sure to allocate enough space (if the output is larger than int)
      // this can be the case for unsigned integers
      PROTECT(Rval = NEW_RAW(nelem * (sizeof(int) > dtype_size ?  sizeof(int) : dtype_size ))); // assumes long long is same size as double (but entire bit64 package assumes that 
      memcpy(VOIDPTR(Rval), VOIDPTR(_Robj), nelem * sizeof(int));
      H5Tconvert_with_warning(H5T_NATIVE_INT, dtype_id, nelem, VOIDPTR(Rval)); 
      UNPROTECT(1);
      return(Rval);
    }
  }
  default:
    error("In RToH5_INTEGER can't convert type of object passed\n");
  }
}

SEXP RToH5_FLOAT(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
  SEXP Rval;

  // check the length of the vector
  switch(TYPEOF(_Robj)) {
  case CPLXSXP: {
      if(nelem != 2 * XLENGTH(_Robj)) {
	error("Length of float vector not as expected\n");
      }
      break;
  }
  case REALSXP:
  case INTSXP: {
    if(nelem != XLENGTH(_Robj)) {
      error("Length of float vector not as expected\n");
    }
    break;
  }
  default: 
    error("In RToH5_FLOAT can't convert type of object passed\n");
  }

  switch(TYPEOF(_Robj)) {
  case CPLXSXP:  // this case is also treated as REAL (but number of elements has to be twice _Robj size when passed in
  case REALSXP: {
    // check if it is a 64bit integer, then need to coerce it to double
    if(is_rint64(_Robj)) {
      PROTECT(Rval = convert_int64_to_double(_Robj));
      PROTECT(Rval = RToH5_FLOAT(Rval, dtype_id, nelem));
      UNPROTECT(2);
      return(Rval);
    }
    else {
      // if it is float, convert to the right size
      int dtype_size = H5Tget_size(dtype_id);
      int isNativeDouble = H5Tequal(dtype_id, H5T_NATIVE_DOUBLE);
      if(isNativeDouble < 0) {
	error("Error when comparing if is native double\n");
      }
      if(isNativeDouble) { // size of a regular double, no conversion necessary
	return(_Robj);
      }
      // in case of long double, might need 16 bytes
      int alloc_size = (dtype_size > sizeof(double) ? dtype_size : sizeof(double));
      PROTECT(Rval = NEW_RAW(nelem * alloc_size));
      memcpy(VOIDPTR(Rval), VOIDPTR(_Robj), nelem * sizeof(double));
      H5Tconvert_with_warning(H5T_NATIVE_DOUBLE, dtype_id, nelem, VOIDPTR(Rval)); 
      SETLENGTH(Rval, XLENGTH(_Robj) * dtype_size);
      UNPROTECT(1);
      return(Rval);	    
    }
  }
  case INTSXP: {
    // if it is integer, coerce to float, and then call the same function again;
    SEXP _Robj_coerced;
    PROTECT(_Robj_coerced = AS_NUMERIC(_Robj));
    PROTECT(Rval = RToH5_FLOAT(_Robj_coerced, dtype_id, nelem));
    UNPROTECT(2);
    return(Rval);
  }
  default:
    error("In RToH5_FLOAT can't convert type of object passed\n");
  }
    
}

SEXP RToH5_STRING(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
  int unprotect_counter=0;
  // check that R is actually a string
  if(!isString(_Robj)) {
    error("For STRING enum type, an R object of type character has to be passed\n");
  }

  if(nelem != XLENGTH(_Robj)) {
    error("Length of string vector not as expected\n");
  }
  hsize_t dtype_size = H5Tget_size(dtype_id);
  SEXP Rval;

  // get an array of sufficient size and store it in there; but first check if the strings are of variable size
  htri_t isVariable = H5Tis_variable_str(dtype_id);
  if(isVariable < 0) {
    error("Error retrieving is string has variable length");
  }
  
  // check out the character encoding 
  H5T_cset_t char_enc = H5Tget_cset(dtype_id);
  if(char_enc == H5T_CSET_ERROR) {
    error("Could not retrieve character encoding of datatype\n");
  }
  
  // now if the character encoding is UTF8, force the input to be changed to UTF8
  if(char_enc == H5T_CSET_UTF8) {
    PROTECT(_Robj = string_to_UTF8(_Robj));
    unprotect_counter++;
  }

  if(isVariable>0) {
    // variable length string
    // in this case just need an array of pointers to the strings we need
    PROTECT(Rval = NEW_RAW(nelem * dtype_size));
    unprotect_counter++;
    const char ** dataptr = (const char **) RAW(Rval);
    for(R_xlen_t i = 0; i < nelem; ++i) {
      dataptr[i] = CHAR(STRING_ELT(_Robj, i)); // copy the pointers to the data strings (are pointers to const char *)
    }
    // need to ensure the CHARSXP this is pointing to are not garbage collected;
    // put them into an attribute
    SET_ATTR(Rval, install("h5_store"), _Robj);
  }
  else {
    // fixed length string
    // in this case will copy the content of the strings itself
    PROTECT(Rval = NEW_RAW(nelem * dtype_size));
    unprotect_counter++;
    char * dataptr = (char *) RAW(Rval);
    for(R_xlen_t i = 0; i < nelem; ++i) {
      strncpy(dataptr, CHAR(STRING_ELT(_Robj, i)), dtype_size);
      dataptr += dtype_size;
    }
  }

  UNPROTECT(unprotect_counter);
  return(Rval);
}

SEXP RToH5_OPAQUE(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
  // check that the size is correct
  if(XLENGTH(_Robj) != nelem) {
    error("Length of R object not correct");
  }

  return(_Robj);
}

SEXP RToH5_REFERENCE(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
  // simply return the ref_obj contained in the object
  SEXP hdf5r_ns = PROTECT(eval(PROTECT(lang2(PROTECT(install("getNamespace")), PROTECT(mkString("hdf5r")))), R_GlobalEnv));
  SEXP result = PROTECT(eval(PROTECT(lang3(PROTECT(install("$")), _Robj, PROTECT(install("ref")))), hdf5r_ns));
  UNPROTECT(8);
  return(result);
}

SEXP RToH5_VLEN(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
  // for this, we expect to get a list in; each list item 
  // determines the variable length; this can be tricky, as it is not always the length
  // for data frames, it is the number of rows
  // for array items, it is only the remaining length after the array is taken into account
  // nelem here refers to the number of variable length items
  // We save pointers, so the actual data will be saved in a list and attached in the attributes to save it
  // from garbage collection
  // we need a rawsxp and a list (VECSXP) of the same length

  // first check that _Robj is a list of the right length
  if(TYPEOF(_Robj) != VECSXP) {
    error("For a variable length array, the R object has to be a list");
  }
  if(XLENGTH(_Robj) != nelem) {
    error("List does not have the expected length");
  }

  SEXP Rval = PROTECT(NEW_RAW(nelem * H5Tget_size(dtype_id)));
  SEXP Rh5_store = PROTECT(NEW_LIST(nelem));
  hvl_t* vlen_ptr = (hvl_t *) RAW(Rval);
  hid_t dtype_base = H5Tget_super(dtype_id);
  for(R_xlen_t i = 0; i < nelem; ++i) {
    vlen_ptr->len = guess_nelem(VECTOR_ELT(_Robj, i), dtype_base);
    SET_VECTOR_ELT(Rh5_store, i, RToH5(VECTOR_ELT(_Robj, i), dtype_base, vlen_ptr->len));
    vlen_ptr->p = VOIDPTR(VECTOR_ELT(Rh5_store, i));
    vlen_ptr++;
  }
  H5Tclose(dtype_base);
  // set the attributes
  SET_ATTR(Rval, install("h5_store"), Rh5_store);
  UNPROTECT(2);
  return(Rval);
}





/*********************************************************************************
 * Creating needed R object for a certain data type for translation HDF5 To R
 *********************************************************************************/
SEXP H5ToR_single_step(void* _h5obj, hid_t dtype_id, R_xlen_t nelem, int flags) {
  hsize_t dtype_size = H5Tget_size(dtype_id);

  SEXP Rval = PROTECT(H5ToR_Pre(dtype_id, nelem));
  if(nelem > 0) {
      memcpy(VOIDPTR(Rval), _h5obj, dtype_size * nelem);
  }
  Rval = PROTECT(H5ToR_Post(Rval, dtype_id, nelem, flags, -1));
  UNPROTECT(2);
  return(Rval);
}



SEXP R_H5ToR_Pre(SEXP _dtype_id, SEXP _nelem) {
  hid_t dtype_id = SEXP_to_xlen(_dtype_id);
  R_xlen_t nelem = SEXP_to_xlen(_nelem);
  return(H5ToR_Pre(dtype_id, nelem));
}
SEXP H5ToR_Pre(hid_t dtype_id, R_xlen_t nelem) {

    // dispatch based on the class_name
    H5T_class_t dtype_class = H5Tget_class(dtype_id);
    
    SEXP Rval;
    switch(dtype_class) {
    case H5T_COMPOUND: {
      bool isComplex=is_h5_complex(dtype_id);
      if(isComplex) {
	PROTECT(Rval = H5ToR_Pre_RComplex(dtype_id, nelem));
      }
      else {
	PROTECT(Rval = H5ToR_Pre_COMPOUND(dtype_id, nelem));
      }
      break;
    }
    case H5T_ARRAY:
      PROTECT(Rval = H5ToR_Pre_ARRAY(dtype_id, nelem));
      break;
    case H5T_ENUM:
      PROTECT(Rval = H5ToR_Pre_ENUM(dtype_id, nelem));
      break;
    case H5T_BITFIELD:
    case H5T_INTEGER:
      PROTECT(Rval = H5ToR_Pre_INTEGER(dtype_id, nelem));
      break;
    case H5T_FLOAT:
      PROTECT(Rval = H5ToR_Pre_FLOAT(dtype_id, nelem));
      break;
    case H5T_STRING:
      PROTECT(Rval = H5ToR_Pre_STRING(dtype_id, nelem));
      break;
    case H5T_OPAQUE:
      PROTECT(Rval = H5ToR_Pre_OPAQUE(dtype_id, nelem));
      break;
    case H5T_REFERENCE:
      PROTECT(Rval = H5ToR_Pre_REFERENCE(dtype_id, nelem));
      break;
    case H5T_VLEN:
      PROTECT(Rval = H5ToR_Pre_VLEN(dtype_id, nelem));
      break;
    default:
      error("Error when retrieving class");
    }

    UNPROTECT(1);
    return(Rval);
}

SEXP H5ToR_Pre_RComplex(hid_t dtype_id, R_xlen_t nelem) {
  hsize_t dtype_size = H5Tget_size(dtype_id);
  // maybe this is stored as 2 16byte floats instead of something smaller
  int alloc_size = (dtype_size > 2 * sizeof(double) ? dtype_size : 2 * sizeof(double));
  

  size_t num_elem_to_alloc = ceil(nelem * alloc_size / (2 * sizeof(double)));
  return(NEW_COMPLEX(num_elem_to_alloc));
}

SEXP H5ToR_Pre_COMPOUND(hid_t dtype_id, R_xlen_t nelem) {
  hsize_t dtype_size = H5Tget_size(dtype_id);

  // allocate a raw vector of appropriate size and return
  return(NEW_RAW(dtype_size * nelem));
}

SEXP H5ToR_Pre_ARRAY(hid_t dtype_id, R_xlen_t nelem) {
  hid_t dtype_base = H5Tget_super(dtype_id);
  hsize_t num_elem_array = H5Tget_size(dtype_id) / H5Tget_size(dtype_base);

  // for the allocation, will do what the base datatype does, but with higher number of elements
  SEXP res;
  res = PROTECT(H5ToR_Pre(dtype_base, nelem * num_elem_array));

  H5Tclose(dtype_base);
  UNPROTECT(1);
  return(res);
}

SEXP H5ToR_Pre_ENUM(hid_t dtype_id, R_xlen_t nelem) {
  hid_t dtype_base = H5Tget_super(dtype_id);
  SEXP Rval;
  // if it is logical, we need to treat it as a logical, otherwise as an integer
  if(is_enum_logical(dtype_id)) {
    if(H5Tget_size(dtype_base) > 4) { // we could make this more flexible, at the expense of an additional copy operation
      error("Stored a an enum corresponding to logical in a type larger than 32 bit: cannot process it\n");
    }
    PROTECT(Rval = NEW_LOGICAL(nelem));
  }
  else {
    PROTECT(Rval = H5ToR_Pre_INTEGER(dtype_base, nelem));
  }
  H5Tclose(dtype_base);
  UNPROTECT(1);
  return(Rval);
}

SEXP H5ToR_Pre_INTEGER(hid_t dtype_id, R_xlen_t nelem) {
  // need to implement heuristic for the output depending on the size of the input integer
  // if it is int or smaller, return as int; if it is uint or larger, return as int64
  int dtype_size = H5Tget_size(dtype_id);
  int dtype_signed = H5Tget_sign(dtype_id) == H5T_SGN_2;

  if(dtype_size < 4 || (dtype_size == 4 && dtype_signed)) {
    // allocate regular int
    return(NEW_INTEGER(nelem));
  }
  else {
    // allocate 64 bit integer
    SEXP Rval;
    PROTECT(Rval = NEW_NUMERIC(nelem));
    SET_CLASS(Rval, ScalarString(mkChar("integer64")));
    UNPROTECT(1);
    return(Rval);
  }
}

SEXP H5ToR_Pre_FLOAT(hid_t dtype_id, R_xlen_t nelem) {
  hsize_t dtype_size = H5Tget_size(dtype_id);
  int alloc_size = (dtype_size > sizeof(double) ? dtype_size : sizeof(double));
  
  size_t num_elem_to_alloc = ceil(nelem * alloc_size / sizeof(double));
  return(NEW_NUMERIC(num_elem_to_alloc));
}

SEXP H5ToR_Pre_STRING(hid_t dtype_id, R_xlen_t nelem) {
  hsize_t dtype_size = H5Tget_size(dtype_id);
  // here, it does not matter if it is variable size or not; we just need a buffer of the right size
  // later in post-processing, a new object has to be created in either case;
  // the reason is that the original buffer needs to be kept in tact in order to be able to free the memory

  return(NEW_RAW(nelem * dtype_size));
}

SEXP H5ToR_Pre_OPAQUE(hid_t dtype_id, R_xlen_t nelem) {
  // just create a raw vecotr of the approriate length
  return(NEW_RAW(nelem));
}

SEXP H5ToR_Pre_REFERENCE(hid_t dtype_id, R_xlen_t nelem) {
  return(NEW_RAW(nelem * H5Tget_size(dtype_id)));
}

SEXP H5ToR_Pre_VLEN(hid_t dtype_id, R_xlen_t nelem) {
  return(NEW_RAW(nelem * H5Tget_size(dtype_id)));
}



/*********************************************************************************
 * Post-processing R object after it has been filled with the data for HDF5 to R
 *********************************************************************************/

SEXP R_H5ToR_Post(SEXP _Robj, SEXP _dtype_id, SEXP _nelem, SEXP _flags, SEXP _obj_id) {
  hid_t dtype_id = SEXP_to_xlen(_dtype_id);
  hid_t obj_id = SEXP_to_longlong(_obj_id, 0);
  R_xlen_t nelem = SEXP_to_xlen(_nelem);
  int flags = SEXP_to_longlong(_flags, 0);
  return(H5ToR_Post(_Robj, dtype_id, nelem, flags, obj_id));
}
SEXP H5ToR_Post(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags, hid_t obj_id) {

    // dispatch based on the class_name
    H5T_class_t dtype_class = H5Tget_class(dtype_id);

    SEXP Rval;
    switch(dtype_class) {
    case H5T_COMPOUND: {
      bool isComplex=is_h5_complex(dtype_id);
      if(isComplex) {
	PROTECT(Rval = H5ToR_Post_RComplex(_Robj, dtype_id, nelem, flags));
      }
      else {
	PROTECT(Rval = H5ToR_Post_COMPOUND(_Robj, dtype_id, nelem, flags, obj_id));
      }
      break;
    }
    case H5T_ARRAY:
      PROTECT(Rval = H5ToR_Post_ARRAY(_Robj, dtype_id, nelem, flags, obj_id));
      break;
    case H5T_ENUM:
      PROTECT(Rval = H5ToR_Post_ENUM(_Robj, dtype_id, nelem, flags));
      break;
    case H5T_BITFIELD:
    case H5T_INTEGER:
      PROTECT(Rval = H5ToR_Post_INTEGER(_Robj, dtype_id, nelem, flags));
      break;
    case H5T_FLOAT:
      PROTECT(Rval = H5ToR_Post_FLOAT(_Robj, dtype_id, nelem, flags));
      break;
    case H5T_STRING:
      PROTECT(Rval = H5ToR_Post_STRING(_Robj, dtype_id, nelem, flags));
      break;
    case H5T_OPAQUE:
      PROTECT(Rval = H5ToR_Post_OPAQUE(_Robj, dtype_id, nelem, flags));
      break;
    case H5T_REFERENCE:
      PROTECT(Rval = H5ToR_Post_REFERENCE(_Robj, dtype_id, nelem, flags, obj_id));
      break;
    case H5T_VLEN:
      PROTECT(Rval = H5ToR_Post_VLEN(_Robj, dtype_id, nelem, flags, obj_id));
      break;
    default:
      error("Error when retrieving class");
    }

    UNPROTECT(1);
    return(Rval);
  
}

SEXP H5ToR_Post_RComplex(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags) {
  hsize_t dtype_size = H5Tget_size(dtype_id);
  
  // pass it to the REAL variable analyzer
  hid_t dtype_member = H5Tget_member_type(dtype_id, 0);
  SEXP res;
  PROTECT(res = H5ToR_Post_FLOAT(_Robj, dtype_member, nelem * 2, flags));
  H5Tclose(dtype_member);
  UNPROTECT(1);

  // if its size is larger than double, need to set the length
  if(dtype_size > sizeof(double)) {
    SETLENGTH(_Robj, nelem);
  }
  return(res);

}

SEXP H5ToR_Post_COMPOUND(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags, hid_t obj_id) {
  
  char * member_name;
  hsize_t dtype_num_members = H5Tget_nmembers(dtype_id);
  
  // allocate the raw vector that will hold the data
  // this will be list
  SEXP Rval, R_item_pre, R_item_post, Rval_names, Rval_rownames;
  PROTECT(Rval = allocVector(VECSXP, dtype_num_members));
  PROTECT(Rval_names = allocVector(STRSXP, dtype_num_members));
  
  hsize_t total_size = H5Tget_size(dtype_id);
  
  // for every record element, pre-allocate an r object, copy the data into it, then post-process it
  hsize_t offset = 0;
  for(int i=0; i < dtype_num_members; i++) {
    // get the member name and add it to names_vector for the data frame
    member_name = H5Tget_member_name(dtype_id, i);
    // Rprintf("Processing member %s\n", member_name);
    SET_STRING_ELT(Rval_names, i, mkChar(member_name));
    H5free_memory(member_name);
    offset = H5Tget_member_offset(dtype_id, i);

    // get the type and its size
    hid_t cpd_item_id = H5Tget_member_type(dtype_id, i);
    if(cpd_item_id < 0) {
      error("An error occured when fetching the a compound item\n");
    }

    // pre-allocate the r-object
    PROTECT(R_item_pre = H5ToR_Pre(cpd_item_id, nelem));

    // copy the record data into it
    hsize_t item_size = H5Tget_size(cpd_item_id);
    memcpy_from_record(VOIDPTR(R_item_pre), VOIDPTR(_Robj), nelem, total_size, offset, item_size);
    
    // post-process the object
    PROTECT(R_item_post = H5ToR_Post(R_item_pre, cpd_item_id, nelem, flags, obj_id));

    // put it into the right place in the global object
    SET_VECTOR_ELT(Rval, i, R_item_post);

    // close the H5T handle and unprotect to clean up at the end of the loop
    H5Tclose(cpd_item_id);
    // Rprintf("End Processing member\n");
    UNPROTECT(2);
  }

  // need an object with rowname
  PROTECT(Rval_rownames = allocVector(INTSXP, nelem));
  for(R_xlen_t i = 0; i < nelem; ++i) {
    INTEGER(Rval_rownames)[i] = i + 1;
  }

  // make the object into a data frame
  SET_CLASS(Rval, mkString("data.frame"));
  SET_NAMES(Rval, Rval_names);
  SET_ATTR(Rval, install("row.names"), Rval_rownames);
  UNPROTECT(3);
  return Rval;

}

SEXP H5ToR_Post_ARRAY(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags, hid_t obj_id) {
  // need to transpose back and then attach the dimensions, which will be (nelem, array_dim)
  // it is up to the R-function that requested the data to replace nelem by the right dimensions, if there exist several
  hid_t dtype_base = H5Tget_super(dtype_id);
  hsize_t dtype_base_size = H5Tget_size(dtype_base);
  hsize_t num_rows = H5Tget_size(dtype_id) / dtype_base_size;
  hsize_t num_cols = nelem;

  SEXP res;
  PROTECT(res = H5ToR_Post(_Robj, dtype_base, num_rows * num_cols, flags, obj_id));
  H5Tclose(dtype_base);
  
  // now, need to transpose the input so that the data inside the array is in consecutive order 
  // but only if there is more than one element
  // (i.e. on the first dimensions)
  if(nelem != 1) {
    SEXP res_copy = PROTECT(duplicate(res)); // use this as the target to write the transposed data in
    transpose_general(VOIDPTR(res_copy), VOIDPTR(res), num_rows, num_cols, R_get_item_size(res), false);
    UNPROTECT(2);
    return(res_copy);
  }
  else {
    UNPROTECT(1);
    return(res);
  }
}

SEXP H5ToR_Post_ENUM(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags) {
  hid_t dtype_base = H5Tget_super(dtype_id);
  SEXP Rval;
  int vars_protected = 0;
  
  PROTECT(Rval = H5ToR_Post_INTEGER(_Robj, dtype_base, nelem, flags));
  vars_protected++;
  H5Tclose(dtype_base);

  if(!is_enum_logical(dtype_id)) {
      // set the levels in the attributes
    SEXP levels;
    PROTECT(levels = VECTOR_ELT(h5get_enum_labels(PROTECT(ScalarInteger64(dtype_id))), 0));
    vars_protected+=2;
    SEXP values;
    PROTECT(values = VECTOR_ELT(h5get_enum_values(PROTECT(ScalarInteger64(dtype_id))), 0));
    vars_protected+=2;

    // check if the enum is based on int64 types; if yes don't order them
    // as we don't currently have an easy method to do the ordering; no other reason than this
    if(is_rint64(values)) {
      if(!is_rint64(Rval)) {
	// need to convert to integer64 to make it match
	Rval = PROTECT(convert_int_to_int64(Rval));
	vars_protected++;
      }
      // class needs to be factor_ext and integer64
      SEXP class_names = PROTECT(NEW_CHARACTER(2));
      vars_protected++;
      SET_STRING_ELT(class_names, 0, mkChar("factor_ext"));
      SET_STRING_ELT(class_names, 1, mkChar("integer64"));
      SET_CLASS(Rval, class_names);
      SET_ATTR(Rval, install("values"), values);
      SET_ATTR(Rval, install("levels"), levels);
    }
    else {
      // the values may not be sorted; will sort them here
      R_xlen_t num_vals = XLENGTH(values);
      SEXP index_vec = PROTECT(NEW_INTEGER(num_vals));
      vars_protected++;
      SEXP order_arglist = PROTECT(Rf_lang1(values));
      vars_protected++;
      R_orderVector(INTEGER(index_vec), num_vals, order_arglist, true, false);
      SEXP levels_ordered = PROTECT(NEW_CHARACTER(num_vals));
      vars_protected++;
      SEXP values_ordered = PROTECT(NEW_INTEGER(num_vals));
      vars_protected++;
      for(R_xlen_t i =0; i < num_vals; ++i) {
        SET_STRING_ELT(levels_ordered, i, STRING_ELT(levels, INTEGER(index_vec)[i]));
        INTEGER(values_ordered)[i] = INTEGER(values)[INTEGER(index_vec)[i]];
      }
      
      // check if values are a consecutive sequence
      SET_LEVELS(Rval, levels_ordered);
      if(is_sequence(values_ordered)) { // it is a factor
	SET_CLASS(Rval, mkString("factor"));
      }
      else {
	SET_CLASS(Rval, mkString("factor_ext"));
	SET_ATTR(Rval, install("values"), values_ordered);
      }
    }
  }
  else {
    // need to convert value 2 to a NA
    for(R_xlen_t i = 0; i < nelem; ++i) {
      if(LOGICAL(Rval)[i] >= 2) {
	LOGICAL(Rval)[i] = NA_LOGICAL;
      }
    }
  }
  UNPROTECT(vars_protected);
  return(Rval);

}

SEXP H5ToR_Post_INTEGER(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags) {
  // need to implement heuristic for the output depending on the size of the input integer
  // if it is int or smaller, return as int; if it is uint or larger, return as int64
  int dtype_size = H5Tget_size(dtype_id);
  int dtype_signed = H5Tget_sign(dtype_id) == H5T_SGN_2;
  int unprotect_counter=0;

  if(dtype_size < 4 || (dtype_size == 4 && dtype_signed)) {
    htri_t isNativeInt = H5Tequal(dtype_id, H5T_NATIVE_INT);
    if(isNativeInt < 0) {
      error("Error when comparing if is native integer\n");
    }
    if(isNativeInt) { // size of a regular double, no conversion necessary
      return(_Robj);
    }
    // received non-regular integer, need to convert
    
    H5Tconvert_with_warning(dtype_id, H5T_NATIVE_INT, nelem, VOIDPTR(_Robj)); // do it in place; from the way it is used, we know it is safe
    return(_Robj);
  }
  else {
    // have received 64 bit integer or an unsigned 32 bit integer
    // Otherwise e.g. 6 byte integer would be possible (albeit not plausible)
    htri_t isNativeLLONG = H5Tequal(dtype_id, H5T_NATIVE_LLONG);
    htri_t isNativeUINT64 = H5Tequal(dtype_id, H5T_NATIVE_UINT64);
    if(isNativeLLONG < 0 || isNativeUINT64 < 0) {
      error("Error when comparing if is native LLONG or UINT64\n");
    }
    if(!isNativeLLONG && !isNativeUINT64) {
      // need to convert to a long-long first (assumption is that BE/LE has been dealt with from the R side, 
      // so that only native datatypes arrive here; in this case, it can't be a type that needs UINT64
      H5Tconvert_with_warning(dtype_id, H5T_NATIVE_LLONG, nelem, VOIDPTR(_Robj)); // do it in place; from the way it is used, we know it is safe
      isNativeLLONG = true;
    }

    if(isNativeLLONG) {
      SEXP res = PROTECT(convert_int64_using_flags(_Robj, flags));
      unprotect_counter++;
      UNPROTECT(unprotect_counter);
      return(res);
    }
    else if(isNativeUINT64) {
      SEXP res = PROTECT(convert_uint64_using_flags(_Robj, flags));
      unprotect_counter++;
      UNPROTECT(unprotect_counter);
      return(res);
    }
    else {
      error("In H5ToR_Post_INTEGER: assumed to have INT64 of UINT64 but didn't");
    }
  }
}

SEXP H5ToR_Post_FLOAT(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags) {
  hsize_t dtype_size = H5Tget_size(dtype_id);
  
  int isNativeDouble = H5Tequal(dtype_id, H5T_NATIVE_DOUBLE);
  if(isNativeDouble < 0) {
    error("Error when comparing if is native double\n");
  }
  if(isNativeDouble) { // size of a regular double, no conversion necessary
    return(_Robj);
  }
  else {
    // need to convert
    H5Tconvert_with_warning(dtype_id, H5T_NATIVE_DOUBLE, nelem, VOIDPTR(_Robj)); // do it in place; from the way it is used, we know it is safe
    // if its size is larger than double, need to set the length
    if(dtype_size > sizeof(double)) {
      SETLENGTH(_Robj, nelem);
    }
    return(_Robj);
  }

}

SEXP H5ToR_Post_STRING(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags) {
  hsize_t dtype_size = H5Tget_size(dtype_id);
  SEXP Rval;
  // get an array of sufficient size and store it in there; but first check if the strings are of variable size
  htri_t isVariable = H5Tis_variable_str(dtype_id);
  if(isVariable < 0) {
    error("Error retrieving is string has variable length");
  }

  // check out the character encoding 
  H5T_cset_t char_enc = H5Tget_cset(dtype_id);
  cetype_t out_ce_type;
  if(char_enc == H5T_CSET_ERROR) {
    error("Could not retrieve character encoding of datatype\n");
  }
  
  // now if the character encoding is UTF8, force the input to be changed to UTF8
  if(char_enc==H5T_CSET_UTF8) {
    out_ce_type = CE_UTF8;
  }
  else {
    out_ce_type = CE_ANY;
  }

  PROTECT(Rval = allocVector(STRSXP, nelem));
  if(isVariable>0) {
    // variable length string
    // we have an array of pointers to strings; need to convert them to R strings; 
    // don't change the buffer itself; it is still needed intact so that the memory can be freed later H5Dvlen_reclaim
    char ** dataptr = (char **) RAW(_Robj);
    for(R_xlen_t i = 0; i < nelem; i++) {
      if(dataptr[i] == NULL) {
	SET_STRING_ELT(Rval, i, mkCharCE("", out_ce_type));
      }
      else {
	// Rprintf("String to transfer %s\n", dataptr[i]);
	SET_STRING_ELT(Rval, i, mkCharCE(dataptr[i], out_ce_type));
      }
    }
  }
  else {
    // fixed length string
    // need to copy the content to R strings (don't forget to add a NUL at the end, for safety in case it was truncated)
    char buf[dtype_size + 1];
    char* dataptr = (char *) RAW(_Robj);
    // set the last one to NUL to be safe
    buf[dtype_size] = '\0';
    for(R_xlen_t i = 0; i < nelem; i++) {
      strncpy(buf, dataptr, dtype_size);
      if(out_ce_type == CE_UTF8) {
	SET_STRING_ELT(Rval, i, mkCharCE(buf, out_ce_type));
      }
      else {
	SET_STRING_ELT(Rval, i, mkChar(buf));
      }
      dataptr += dtype_size;
    }
  }
  
  UNPROTECT(1);
  return(Rval);
}

SEXP H5ToR_Post_OPAQUE(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags) {
  // nothing to be done; just return
  return(_Robj);
}

// the object-id is stored in the reference object; the dataset or the attribute are expected objects
// internally they will be turned into an appropriate file-id
SEXP H5ToR_Post_REFERENCE(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags, hid_t obj_id) {
  // need to create an r6 class object and assign the reference into it
  // the id to be passed in has to be the file_id
  if(obj_id < 0) {
    error("Object_id for Reference has to be non-negative\n");
  }

  // get the file id
  hid_t file_id = H5Iget_file_id(obj_id);
  
  SEXP result;
  // create the arguments for calling the R6-class constructor
  if(H5Tequal(dtype_id, H5T_STD_REF_OBJ)) {
    result = PROTECT(new_H5R_R6_class("H5R_OBJECT", PROTECT(ScalarInteger(0)), PROTECT(ScalarInteger64(file_id))));
  }
  else if(H5Tequal(dtype_id, H5T_STD_REF_DSETREG)) {
    result = PROTECT(new_H5R_R6_class("H5R_DATASET_REGION", PROTECT(ScalarInteger(0)), PROTECT(ScalarInteger64(file_id))));
  }
  else {
    H5Fclose(file_id);
    error("Could not identify reference type\n");
  }
  
  // now assign the reference data into it
  SEXP hdf5r_ns = PROTECT(eval(PROTECT(lang2(PROTECT(install("getNamespace")), PROTECT(mkString("hdf5r")))), R_GlobalEnv));
  eval(PROTECT(lang3(install("set_ref.H5R"), result, _Robj)), hdf5r_ns);
  UNPROTECT(8);
  
  return(result);

}

SEXP H5ToR_Post_VLEN(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem, int flags, hid_t obj_id) {
  // create a list, and put the data into it
  SEXP Rval = PROTECT(NEW_LIST(nelem));
  SEXP R_item;
  hid_t dtype_base = H5Tget_super(dtype_id);
  hsize_t dtype_base_size = H5Tget_size(dtype_base);
  hvl_t * vlen_ptr = (hvl_t *) VOIDPTR(_Robj);
  for(R_xlen_t i = 0; i < nelem; ++i) {
    PROTECT(R_item = H5ToR_Pre(dtype_base, vlen_ptr->len));
    // copy the data it is pointing to back and set it into the vector after transforming it to R
    memcpy(VOIDPTR(R_item), vlen_ptr->p, dtype_base_size * vlen_ptr->len);
    SET_VECTOR_ELT(Rval, i, H5ToR_Post(R_item, dtype_base, vlen_ptr->len, flags, obj_id));
    vlen_ptr++;
    UNPROTECT(1);
  }
  H5Tclose(dtype_base);
  UNPROTECT(1);
  return(Rval);
}


/***********************************************************************************
 * Helper function for memory copying
 ***********************************************************************************/

/* the following function does the copying into a record from a vector
 * src: pointer to the input data
 * dst: pointer to where it should be copied
 * num_items: number of items to copy
 * recordSize: size in bytes of each record on the output size
 * offset: offset for the item in the output record
 * item_size: number of bytes for the item
 * Code adapted from memcpy
 */ 
void *memcpy_to_record(void* dst, const void* src, hsize_t num_items, hsize_t record_size, hsize_t offset, hsize_t item_size) {
  // check if all the copying can be done in int sizes
  if ((uintptr_t)dst % sizeof(uint64_t) == 0 &&
      (uintptr_t)src % sizeof(uint64_t) == 0 &&
      record_size % sizeof(uint64_t) == 0 && 
      offset % sizeof(uint64_t) == 0 &&
      item_size % sizeof(uint64_t) == 0) {

    uint64_t* d=dst;
    const uint64_t * s=src ;
    for(hsize_t i=0; i < num_items; ++i) {
      d += offset / sizeof(uint64_t);
      for(int j=0; j < item_size / sizeof(uint64_t); ++j) {
	d[j] = s[j];
      }
      d += record_size / sizeof(uint64_t) - offset / sizeof(uint64_t);
      s += item_size / sizeof(uint64_t);
    }
  }
  else if ((uintptr_t)dst % sizeof(uint32_t) == 0 &&
      (uintptr_t)src % sizeof(uint32_t) == 0 &&
      record_size % sizeof(uint32_t) == 0 && 
      offset % sizeof(uint32_t) == 0 &&
      item_size % sizeof(uint32_t) == 0) {

    int* d=dst;
    const int * s=src ;
    for(hsize_t i=0; i < num_items; ++i) {
      d += offset / sizeof(uint32_t);
      for(int j=0; j < item_size / sizeof(uint32_t); ++j) {
	d[j] = s[j];
      }
      d += record_size / sizeof(uint32_t) - offset / sizeof(uint32_t);
      s += item_size / sizeof(uint32_t);
    }
  }
  else {
    char* d=dst;
    const char * s=src ;
    for(hsize_t i=0; i < num_items; ++i) {
      d += offset;
      for(int j=0; j < item_size; ++j) {
	d[j] = s[j];
      }
      d += record_size - offset;
      s += item_size;
    }
  }
  return(dst);
}


/* the following function does the copying into a record from a vector
 * src: pointer to the input data
 * dst: pointer to where it should be copied
 * num_items: number of items to copy
 * recordSize: size in bytes of each record on the output size
 * offset: offset for the item in the input record
 * item_size: number of bytes for the item
 * Code adapted from memcpy
 */ 
void *memcpy_from_record(void* dst, const void* src, hsize_t num_items, hsize_t record_size, hsize_t offset, hsize_t item_size) {
  // check if all the copying can be done in int sizes
  if ((uintptr_t)dst % sizeof(uint64_t) == 0 &&
      (uintptr_t)src % sizeof(uint64_t) == 0 &&
      record_size % sizeof(uint64_t) == 0 && 
      offset % sizeof(uint64_t) == 0 &&
      item_size % sizeof(uint64_t) == 0) {


    uint64_t* d=dst;
    const uint64_t * s=src ;
    for(hsize_t i=0; i < num_items; ++i) {
      s += offset / sizeof(uint64_t);
      for(hsize_t j=0; j < item_size / sizeof(uint64_t); ++j) {
	d[j] = s[j];
      }
      s += record_size / sizeof(uint64_t) - offset / sizeof(uint64_t);
      d += item_size / sizeof(uint64_t);
    }
  }
  else if ((uintptr_t)dst % sizeof(uint32_t) == 0 &&
      (uintptr_t)src % sizeof(uint32_t) == 0 &&
      record_size % sizeof(uint32_t) == 0 && 
      offset % sizeof(uint32_t) == 0 &&
      item_size % sizeof(uint32_t) == 0) {

    uint32_t* d=dst;
    const uint32_t * s=src ;
    for(hsize_t i=0; i < num_items; ++i) {
      s += offset / sizeof(uint32_t);
      for(hsize_t j=0; j < item_size / sizeof(uint32_t); ++j) {
	d[j] = s[j];
      }
      s += record_size / sizeof(uint32_t) - offset / sizeof(uint32_t);
      d += item_size / sizeof(uint32_t);
    }
  }
  else {
    char* d=dst;
    const char * s=src ;
    for(hsize_t i=0; i < num_items; ++i) {
      s += offset;
      for(int j=0; j < item_size; ++j) {
	d[j] = s[j];
      }
      s += record_size - offset;
      d += item_size;
    }
  }
  return(dst);
}


/* the following function does the copying from a record into a record
 * src: pointer to the input data
 * dst: pointer to where it should be copied
 * num_items: number of items to copy
 * recordSize: size in bytes of each record on the output size
 * offset_dst: offset for the item in the input record
 * offset_src: offset for the item in the output record
 * item_size: number of bytes for the item
 * Code adapted from memcpy
 */ 
void *memcpy_between_record(void* dst, const void* src, hsize_t num_items, hsize_t record_size, hsize_t offset_dst, hsize_t offset_src, 
			    hsize_t item_size) {
  // check if all the copying can be done in 8 byte sizes
  if ((uintptr_t)dst % sizeof(uint64_t) == 0 &&
      (uintptr_t)src % sizeof(uint64_t) == 0 &&
      record_size % sizeof(uint64_t) == 0 && 
      offset_dst % sizeof(uint64_t) == 0 &&
      offset_src % sizeof(uint64_t) == 0 &&
      item_size % sizeof(uint64_t) == 0) {


    uint64_t* d=dst;
    const uint64_t * s=src ;
    for(hsize_t i=0; i < num_items; ++i) {
      s += offset_src / sizeof(uint64_t);
      d += offset_dst / sizeof(uint64_t);
      for(hsize_t j=0; j < item_size / sizeof(uint64_t); ++j) {
	d[j] = s[j];
      }
      s += record_size / sizeof(uint64_t) - offset_src / sizeof(uint64_t);
      d += record_size / sizeof(uint64_t) - offset_dst / sizeof(uint64_t);
    }
  }
  else if ((uintptr_t)dst % sizeof(uint32_t) == 0 &&
      (uintptr_t)src % sizeof(uint32_t) == 0 &&
      record_size % sizeof(uint32_t) == 0 && 
      offset_dst % sizeof(uint32_t) == 0 &&
      offset_src % sizeof(uint32_t) == 0 &&
      item_size % sizeof(uint32_t) == 0) {

    uint32_t* d=dst;
    const uint32_t * s=src ;
    for(hsize_t i=0; i < num_items; ++i) {
      s += offset_src / sizeof(uint32_t);
      d += offset_dst / sizeof(uint32_t);
      for(hsize_t j=0; j < item_size / sizeof(uint32_t); ++j) {
	d[j] = s[j];
      }
      s += record_size / sizeof(uint32_t) - offset_src / sizeof(uint32_t);
      d += record_size / sizeof(uint32_t) - offset_dst / sizeof(uint32_t);
    }
  }
  else {
    char* d=dst;
    const char * s=src ;
    for(hsize_t i=0; i < num_items; ++i) {
      s += offset_src;
      s += offset_dst;
      for(int j=0; j < item_size; ++j) {
	d[j] = s[j];
      }
      s += record_size - offset_src;
      s += record_size - offset_dst;
    }
  }
  return(dst);
}

/* read a subset defined by idx from src and writes it consecutively into dst */
void* read_raw_subset_generic(void* dst, void* src, R_xlen_t idx_len, long long *idx, R_xlen_t item_size) {
  if ((uintptr_t)dst % sizeof(uint64_t) == 0 &&
      (uintptr_t)src % sizeof(uint64_t) == 0 &&
      item_size % sizeof(uint64_t) == 0) {

    uint64_t* d=dst;
    const uint64_t * s;
    for(R_xlen_t i = 0; i < idx_len; ++i) {
      s = ((uint64_t*) src) + idx[i] * (item_size / sizeof(uint64_t));

      for(R_xlen_t j=0; j < item_size / sizeof(uint64_t); ++j) {
	d[j] = s[j];
      }
      d += item_size / sizeof(uint64_t);
    }
  }
  else if ((uintptr_t)dst % sizeof(uint32_t) == 0 &&
	    (uintptr_t)src % sizeof(uint32_t) == 0 &&
	    item_size % sizeof(uint32_t) == 0) {
    uint32_t* d=dst;
    const uint32_t * s;
    for(R_xlen_t i = 0; i < idx_len; ++i) {
      s = ((uint32_t*) src) + idx[i] * (item_size / sizeof(uint32_t));
      for(R_xlen_t j=0; j < item_size / sizeof(uint32_t); ++j) {
	d[j] = s[j];
      }
      d += item_size / sizeof(uint32_t);
    }
    
  }
  else {
    char* d=dst;
    const char* s;
    for(R_xlen_t i = 0; i < idx_len; ++i) {
      s = ((char*) src) + idx[i] * item_size;
      for(R_xlen_t j=0; j < item_size; ++j) {
	d[j] = s[j];
      }
      d += item_size;
    }

  }
  return(dst);
}

/* Subset a raw vector; the index is 0-based; 
 * subsetting is done for an arbitrary item_size (i.e. any size of a datatype
 */ 
SEXP R_read_raw_subset_generic(SEXP R_src, SEXP R_idx, SEXP R_item_size) {
  R_xlen_t idx_len = XLENGTH(R_idx);
  R_xlen_t item_size = SEXP_to_xlen(R_item_size);

  SEXP R_helper = PROTECT(RToH5(R_idx, H5T_NATIVE_LLONG, idx_len));
  long long* idx = (long long *) VOIDPTR(R_helper);
  
  SEXP R_dst = PROTECT(NEW_RAW(idx_len * item_size));
  read_raw_subset_generic(VOIDPTR(R_dst), VOIDPTR(R_src), idx_len, idx, item_size);
  
  UNPROTECT(2);
  return(R_dst);	  
}



/* write a vector into a subset defined by idx from src (consecutively) and writes it into dst (consecutively) */
void* write_raw_subset_generic(void* dst, void* src, R_xlen_t idx_len, long long *idx, R_xlen_t item_size) {
  if ((uintptr_t)dst % sizeof(uint64_t) == 0 &&
      (uintptr_t)src % sizeof(uint64_t) == 0 &&
      item_size % sizeof(uint64_t) == 0) {

    uint64_t * d;
    const uint64_t* s=src;
    for(R_xlen_t i = 0; i < idx_len; ++i) {
      d = ((uint64_t*) dst) + idx[i] * (item_size / sizeof(uint64_t));
      for(R_xlen_t j=0; j < item_size / sizeof(uint64_t); ++j) {
	d[j] = s[j];
      }
      s += item_size / sizeof(uint64_t);
    }
  }
  else if ((uintptr_t)dst % sizeof(uint32_t) == 0 &&
	    (uintptr_t)src % sizeof(uint32_t) == 0 &&
	    item_size % sizeof(uint32_t) == 0) {
    uint32_t* d;
    const uint32_t * s=src;
    for(R_xlen_t i = 0; i < idx_len; ++i) {
      d = ((uint32_t*) dst) + idx[i] * (item_size / sizeof(uint32_t));
      for(R_xlen_t j=0; j < item_size / sizeof(uint32_t); ++j) {
	d[j] = s[j];
      }
      s += item_size / sizeof(uint32_t);
    }
    
  }
  else {
    char* d;
    const char* s=src;
    for(R_xlen_t i = 0; i < idx_len; ++i) {
      d = ((char *) dst) + idx[i] * item_size;
      for(R_xlen_t j=0; j < item_size; ++j) {
	d[j] = s[j];
      }
      s += item_size;
    }

  }
  return(dst);
}

/* Subset a raw vector; the index is 0-based; 
 * subsetting is done for an arbitrary item_size (i.e. any size of a datatype
 */ 
SEXP R_write_raw_subset_generic(SEXP R_dst, SEXP R_src, SEXP R_idx, SEXP R_item_size) {
  R_xlen_t idx_len = XLENGTH(R_idx);
  R_xlen_t item_size = SEXP_to_xlen(R_item_size);

  // check that the size is correct
  if(item_size * idx_len != R_get_item_size(R_src) * XLENGTH(R_src)) {
    error("Item to write into subset of vector doesn't have the right size");
  }

  SEXP R_helper = PROTECT(RToH5(R_idx, H5T_NATIVE_LLONG, idx_len));
  long long* idx = (long long *) VOIDPTR(R_helper);
  
  R_dst = PROTECT(duplicate(R_dst));
  write_raw_subset_generic(VOIDPTR(R_dst), VOIDPTR(R_src), idx_len, idx, item_size);
  
  UNPROTECT(2);
  return(R_dst);	  
}



SEXP copy_rvec(SEXP _dst, SEXP _src, SEXP _nbytes) {
  memcpy(VOIDPTR(_dst), VOIDPTR(_src), INTEGER(_nbytes)[0]);
  return(_dst);
}

/****************************************
 * Transpose a matrix where an item can have an arbitrary size. Assumption is 
 * that items vary fastest in the rows (as is the case in R)
 * dst: pointer of the destination
 * src: pointer to the source
 * num_rows: number of rows of matrix
 * num_cols: number of cols of matrix
 * item_size: size in bytes of each item
 ****************************************/

void* transpose_general(void* dst, const void* src, hsize_t num_rows, hsize_t num_cols, hsize_t item_size, bool cpy_by_col) { 
  if(cpy_by_col) {
    // we will use the memcopy_to_record function; here, a "record" corresponds to one column of the transposed matrix
    hsize_t record_size = num_cols * item_size;
    hsize_t offset = 0;
    const char * src_col =  src;
    
    for(hsize_t i = 0; i < num_cols; i++) {
      memcpy_to_record(dst, src_col, num_rows, record_size, offset, item_size);
      offset += item_size;
      src_col += item_size * num_rows;
    }
  }
  else {
    hsize_t record_size = num_rows * item_size;
    hsize_t offset = 0;
    char * dst_col =  dst;
    
    for(hsize_t i = 0; i < num_rows; i++) {
      memcpy_from_record(dst_col, src, num_cols, record_size, offset, item_size);
      offset += item_size;
      dst_col += item_size * num_cols;
    }
  }
  return(dst);
}

// r wrapper for transpose_general
SEXP R_transpose_general(SEXP R_src, SEXP R_dim, SEXP R_item_size) {
  SEXP R_dst = PROTECT(duplicate(R_src));

  hsize_t num_rows = SEXP_to_longlong(R_dim, 0);
  hsize_t num_cols = SEXP_to_longlong(R_dim, 1);
  hsize_t item_size = SEXP_to_longlong(R_item_size, 0);

  bool cpy_by_col = (num_cols < num_rows);
  transpose_general(VOIDPTR(R_dst), VOIDPTR(R_src), num_rows, num_cols, item_size, cpy_by_col);

  UNPROTECT(1);
  return(R_dst);
}

/****************************************
 * Reorder the rows of a matrix where an item can have an arbitrary size (and therefore we can always assume it is the rows to reorder). 
 * Assumption is 
 * that items vary fastest in the rows (as is the case in R)
 * dst: pointer of the destination
 * src: pointer to the source
 * num_rows: number of rows of matrix
 * new_order: Vector with num_row elements, where the i-th element (0-based) is giving the src-row that should be in the i-th dst row
 * num_cols: number of cols of matrix
 * item_size: size in bytes of each item
 ****************************************/

void* reorder(void* dst, const void* src, hsize_t num_rows, hsize_t num_cols, hsize_t item_size, const hsize_t * new_order) {
  if(dst == src) {
    error("dst and src should be different");
  }
  hsize_t num_items = num_cols;
  hsize_t record_size = num_rows * item_size;
  for(hsize_t i = 0; i < num_rows; ++i) {
    // use the memcpy_between_record function
    // offset is simply item_size * row_number
    memcpy_between_record(dst, src, num_items, record_size, item_size * i, item_size * new_order[i], item_size);
  }
  return(dst);
}

SEXP R_reorder(SEXP R_src, SEXP R_num_rows, SEXP R_num_cols, SEXP R_item_size, SEXP R_new_order) {
  hsize_t num_rows = SEXP_to_longlong(R_num_rows, 0);
  hsize_t num_cols = SEXP_to_longlong(R_num_cols, 0);
  hsize_t item_size = SEXP_to_longlong(R_item_size, 0);

  SEXP R_helper = PROTECT(RToH5(R_new_order, H5T_NATIVE_ULLONG, num_rows));
  hsize_t* new_order = (unsigned long long *) VOIDPTR(R_helper);
  
  SEXP R_dst = PROTECT(duplicate(R_src));
  reorder(VOIDPTR(R_dst), VOIDPTR(R_src), num_rows, num_cols, item_size, new_order);
  
  UNPROTECT(2);
  return(R_dst);	  
}


/***********************************************************************************
 * Other Helper functions
 ***********************************************************************************/
int is_rint64(SEXP _Robj) {
  if(TYPEOF(_Robj) != REALSXP) {
    return(false);
  }
  return(inherits(_Robj, "integer64"));
}

SEXP _is_rint64(SEXP _Robj) {
  SEXP Rval;
  PROTECT(Rval = NEW_LOGICAL(1));
  LOGICAL(Rval)[0] = is_rint64(_Robj);
  UNPROTECT(1);
  return(Rval);
}


#define sgn(x)  ((x > 0) - (x < 0))

// get the value of the length given in _len
// this function is needed as sometimes it is double, not integer
// and therefore needs rounding instead of type casting
R_xlen_t SEXP_to_xlen(SEXP _len) {
  R_xlen_t len;
  R_xlen_t* len_ptr;
  switch(TYPEOF(_len)) {
  case REALSXP: 
    // need to take the double value and coerce it; the 32-bit integer issue in R; also check if this is not maybe an 
    // an integer 64
    if(is_rint64(_len)) {
      len_ptr = (R_xlen_t*) (REAL(_len));
      len = len_ptr[0];
      return(len);
    }
    else {
      len = (R_xlen_t) (REAL(_len)[0] + sgn(REAL(_len)[0]) * 0.5);
      return(len);
    }
  case INTSXP: 
    len = (R_xlen_t) (INTEGER(_len)[0]);
    break;
  default:
    error("Cannot convert to a length\n");
  }
  return(len);
}


// get the value of the given in  _value as a long long
// this function is needed as sometimes it is double, not integer
// and therefore needs rounding instead of type casting
long long SEXP_to_longlong(SEXP _value, R_xlen_t pos) {
  long long value;
  long long * value_ptr;
  if(pos >= XLENGTH(_value)) {
    error("pos >= XLENGTH(_value)");
  }
  switch(TYPEOF(_value)) {
  case REALSXP: 
    // need to take the double value and coerce it; the 32-bit integer issue in R; also check if this is not maybe an 
    // an integer 64
    if(is_rint64(_value)) {
      value_ptr = (long long*) (REAL(_value));
      value = value_ptr[pos];
      return(value);
    }
    else {
      // need to check if the value of REAL is Inf, if yes, set to maximum 
      // longlong value
      if(REAL(_value)[pos] == R_PosInf) {
        value = LLONG_MAX;
      }
      else {
        value = (long long) (REAL(_value)[pos] + sgn(REAL(_value)[pos]) * 0.5);
      }
      return(value);
    }
  case LGLSXP:
    value = (long long) (LOGICAL(_value)[pos]);
  case INTSXP: 
    value = (long long) (INTEGER(_value)[pos]);
    break;
  default:
    if(XLENGTH(_value) == 0) {
      error("Input is of length 0, cannot convert to a long long\n");
    }
    if(_value == R_NilValue) {
      error("Input is NULL; expected a value; cannot convert to long long\n");
    }
    error("Cannot convert to a long long\n");
  }
  return(value);
}



// get the value of the given in  _value as a boolean
// this function is needed as sometimes it is integer, not logical
bool SEXP_to_logical(SEXP _value) {
  bool value;
  switch(TYPEOF(_value)) {
  case LGLSXP: 
    value = (LOGICAL(_value)[0]) != 0;
  case INTSXP: 
    value = (INTEGER(_value)[0]) != 0;
    break;
  default:
    error("Cannot convert to a logical\n");
  }
  return(value);
}

// get the value of the given in  _value as a double
// this function is needed as sometimes it is integer, not double
double SEXP_to_double(SEXP _value) {
  double value;
  long long *ll_ptr;
  switch(TYPEOF(_value)) {
  case REALSXP: 
    // need to take the double value and coerce it; the 32-bit integer issue in R; also check if this is not maybe an 
    // an integer 64
    if(is_rint64(_value)) {
      ll_ptr = (long long *) REAL(_value);
      value = ll_ptr[0];
    }
    else {
      value = REAL(_value)[0];
      break;
    }
  case INTSXP: 
    value = INTEGER(_value)[0];
    break;
  default:
    error("Cannot convert to a long long\n");
  }
  return(value);
}




SEXP ScalarInteger64(long long value) {
  SEXP Rval = PROTECT(ScalarReal(0.0));
  ((long long*) REAL(Rval))[0] = value;
  SET_CLASS(Rval, ScalarString(mkChar("integer64")));
  UNPROTECT(1);
  return(Rval);
}

// contrary to ScalarInteger64, this only returns a 64bit integer if 
// the size of the value makes it necessary;
// could be a bit messy when it comes to some returns, but makes life
// on the R side a lot easier without forcing integer on everything
SEXP ScalarInteger64_or_int(long long value) {
  if(value >= INT_MAX || value <= INT_MIN) {
    SEXP Rval = PROTECT(ScalarReal(0.0));
    ((long long*) REAL(Rval))[0] = value;
    SET_CLASS(Rval, ScalarString(mkChar("integer64")));
    UNPROTECT(1);
    return(Rval);
  }
  else {
    return(ScalarInteger(value));
  }
}


// create a scalar factor variable
SEXP ScalarFactor(int value, hid_t dtype_id) {
  SEXP Rval = PROTECT(ScalarInteger(value));
  SET_CLASS(Rval, mkString("factor"));

  // get the levels and the values
  SEXP levels;
  PROTECT(levels = VECTOR_ELT(h5get_enum_labels(PROTECT(ScalarInteger64(dtype_id))), 0));
  SET_LEVELS(Rval, levels);

  SEXP values;
  PROTECT(values = VECTOR_ELT(h5get_enum_values(PROTECT(ScalarInteger64(dtype_id))), 0));
  // check if values are a consecutive sequence
  if(is_sequence(values)) { // it is a factor
    SET_CLASS(Rval, mkString("factor"));
  }
  else {
    SET_CLASS(Rval, mkString("factor_ext"));
    SET_ATTR(Rval, install("values"), values);
  }
  
  UNPROTECT(5);
  return(Rval);
}

bool is_sequence(SEXP val) {
  size_t len = XLENGTH(val);
  
  if(len == 0) return(false);
  if(TYPEOF(val) != INTSXP) return(false);

  for(size_t i=0; i < len; ++i) {
    if(INTEGER(val)[i] != i+1) return(false);
  }
  return(true);
  
}


/* Checks if the compound can be interpreted as a complex variable 
 * Also require for simplicity that the two parts of the compound have the same
 * float type
 */
bool is_h5_complex(hid_t dtype_id) {
  // check if the compound is a complex variable
  if(H5Tget_nmembers(dtype_id)!=2) { 
    // warning("Number of members not 2\n");
    return(false);
  }
  else if(H5Tget_member_class(dtype_id, 0)!=H5T_FLOAT || H5Tget_member_class(dtype_id, 0)!=H5T_FLOAT) { 
    // warning("Members don't have class float\n");
    return(false);
  }
  else {
    char * name_item_0, *name_item_1;
    hid_t member_dtype_0, member_dtype_1;
    htri_t is_equal;
    bool returnFalse = false;
    // check that the types are the same
    member_dtype_0 = H5Tget_member_type(dtype_id, 0);
    member_dtype_1 = H5Tget_member_type(dtype_id, 1);
    is_equal = H5Tequal(member_dtype_0, member_dtype_1);
    if(is_equal <= 0) { // on error also return false; don't raise the error (convenience)
      // warning("types are not equal\n");
      returnFalse = true;
    }    

    // need to close them again to avoid resource leaks
    H5Tclose(member_dtype_0);
    H5Tclose(member_dtype_1);
    if(returnFalse) { 
      return(false);
    }

    name_item_0 = H5Tget_member_name(dtype_id, 0);
    name_item_1 = H5Tget_member_name(dtype_id, 1);
    if((name_item_0[0]!='r' && name_item_0[0]!='R') || (name_item_0[1]!='e' && name_item_0[1]!='E')) {
      // warning("First letter not equal to r or second letter not equal to e\n");
      returnFalse = true;
    }
    if((name_item_1[0]!='i' && name_item_1[0]!='I') || (name_item_1[1]!='m' && name_item_1[1]!='M')) {
      // warning("First letter not equal to i or second letter not equal to m\n");
      returnFalse = true;
    }
    // need to free them again to avoid memory leaks
    H5free_memory(name_item_0);
    H5free_memory(name_item_1);
    if(returnFalse) { 
      return(false);
    }
  }
  
  return(true);
}

// checks if it is a special R object that signals 
// that an empty buffer should be created corresponding to an h5 object of 
// all 0s
bool is_RToH5_empty(SEXP _Robj, R_xlen_t nelem) {
  if(!inherits(_Robj, "R_RToH5_empty")) {
    return(false);
  }
  if(nelem != XLENGTH(_Robj)) {
    error("Incorrect length of object passed for _RToH5_empty object");
  }
  return(true);
}



/* Check if the enum can be interpreted as a factor variable
 * This is the case if all values are ordered from 1 to n  */
bool is_enum_factor(hid_t dtype_id) {
  int enum_size = H5Tget_nmembers(dtype_id);
  hid_t enum_base_type = H5Tget_super(dtype_id);
  hsize_t enum_base_size = H5Tget_size(enum_base_type);

  if(enum_base_size > sizeof(long long)) {
    error("Cannot read an enum with a size > long long");
  }

  long long val;
  for(int i=0; i < enum_size; ++i) {
    H5Tget_member_value(dtype_id, i, &val);
    H5Tconvert(enum_base_type, H5T_NATIVE_LLONG, 1, &val, NULL, H5P_DEFAULT);
    if(val != i + 1) {
      H5Tclose(enum_base_type);
      return(false);
    }
  }
  H5Tclose(enum_base_type);
  return(true);
}

bool is_enum_logical(hid_t dtype_id) {
  int enum_size = H5Tget_nmembers(dtype_id);
  hid_t enum_base_type = H5Tget_super(dtype_id);
  hsize_t enum_base_size = H5Tget_size(enum_base_type);

  if(enum_size != 2 && enum_size != 3) {
      H5Tclose(enum_base_type);
      return(false);
  }

  if(enum_base_size > sizeof(long long)) {
    error("Cannot read an enum with a size > long long");
  }

  // check that the enum has the right names
  // first, false or f needs to be included with value 0
  int idx;
  long long val;
  if(((idx = H5Tget_member_index(dtype_id, "FALSE")) >= 0) || ((idx = H5Tget_member_index(dtype_id, "false")) >= 0) || 
     ((idx = H5Tget_member_index(dtype_id, "F")) >= 0) || ((idx = H5Tget_member_index(dtype_id, "f")) >= 0)) {
    H5Tget_member_value(dtype_id, idx, &val);
    H5Tconvert(enum_base_type, H5T_NATIVE_LLONG, 1, &val, NULL, H5P_DEFAULT);
    if(val != 0) {
      H5Tclose(enum_base_type);
      return(false);
    }
  }
  else {
    H5Tclose(enum_base_type);
      return(false);
  }

  if(((idx = H5Tget_member_index(dtype_id, "TRUE")) >= 0) || ((idx = H5Tget_member_index(dtype_id, "true")) >= 0) || 
     ((idx = H5Tget_member_index(dtype_id, "T")) >= 0) || ((idx = H5Tget_member_index(dtype_id, "t")) >= 0)) {
    H5Tget_member_value(dtype_id, idx, &val);
    H5Tconvert(enum_base_type, H5T_NATIVE_LLONG, 1, &val, NULL, H5P_DEFAULT);
    if(val != 1) {
      H5Tclose(enum_base_type);
      return(false);
    }
  }
  else {

      H5Tclose(enum_base_type);
      return(false);
  }

  if(enum_size == 3) {
    if(((idx = H5Tget_member_index(dtype_id, "NA")) >= 0) || ((idx = H5Tget_member_index(dtype_id, "na") >= 0))) {
      H5Tget_member_value(dtype_id, idx, &val);
      H5Tconvert(enum_base_type, H5T_NATIVE_LLONG, 1, &val, NULL, H5P_DEFAULT);

      if(val != 2) {
	H5Tclose(enum_base_type);
	return(false);
      }
    }
    else {
      H5Tclose(enum_base_type);
      return(false);
    }
  }
  return(true);
}

char* str_to_lower(char * str) {
  char * src = str;
  for ( ; *str; ++str) *str = tolower(*str);
  return(src);
}


// when this function is called, it is already ensured that the 
// dtype doesn't represent a logical
bool is_robj_enum(SEXP _Robj, hid_t dtype_id) {

  // check if the Robject and enum conform to the same standards
  if(H5Tget_nmembers(dtype_id) == 0) {
    error("Enum has no members\n");
  }
  
  
  // now it has to be a factor (or levels and values set separately)
  
  // get the levels of the Robj
  SEXP levels, values;
  PROTECT(levels = GET_LEVELS(_Robj));
  if(isNull(levels) || !isString(levels)) {
    UNPROTECT(1);
    return(false);
  }
  
  
  // check the class of the Robj. If it is factor, the values are given implicitly
  if(isFactor(_Robj)) {
    PROTECT(values = NEW_INTEGER(LENGTH(levels)));
    for(int i = 0; i < LENGTH(levels); ++i) {
      INTEGER(values)[i] = i + 1;
    }
  } 
  else {
    PROTECT(values = GET_ATTR(_Robj, install("values")));
    if(isNull(values) || LENGTH(values) != LENGTH(levels) || !isInteger(values)) {
      UNPROTECT(2);
      return(false);
    }
  }
  
  // now check if the levels and the values match the enum
  SEXP enum_values, enum_labels;
  PROTECT(enum_values = VECTOR_ELT(h5get_enum_values(PROTECT(ScalarInteger64(dtype_id))), 0));
  PROTECT(enum_labels = VECTOR_ELT(h5get_enum_labels(PROTECT(ScalarInteger64(dtype_id))), 0));
		  
  // check that the length of both matches 
  if(LENGTH(enum_values) != LENGTH(values) || LENGTH(enum_labels) != LENGTH(levels)) {
    UNPROTECT(6);
    return(false);
    
  }

  // check that they are the same
  for(int i=0; i < LENGTH(levels); ++i) {
    if(INTEGER(enum_values)[i] != INTEGER(values)[i] || strcmp(CHAR(STRING_ELT(enum_labels, i)), CHAR(STRING_ELT(levels, i)))!=0) {
      UNPROTECT(6);
      return(false);

    }
  }

  // everything matches
  UNPROTECT(6);
  return(true);

}


bool is_robj_compound(SEXP _Robj, hid_t dtype_id, R_xlen_t nelem) {
  char* member_name;

  /* Check that the R object is of the expected type */
  // first check that it is actually a list
  if(TYPEOF(_Robj) != VECSXP) {
    warning("Input to RToH5_COMPOUND expects a list\n");
    return(false);
  }
  // check that it is actually a data.frame 
  if(!inherits(_Robj, "data.frame")) {
    return(false);
  }
  
  if(LENGTH(_Robj)==0) {
    warning("List has length 0\n");
    return(false);
  }
  // check that the list is same length as dtype
  size_t dtype_num_members = H5Tget_nmembers(dtype_id);
  if(LENGTH(_Robj) != dtype_num_members) {
    warning("Length of Robj and number of objects in dtype have to be the same\n");
    return(false);
  }
  // check that the list is named and has the same names in the same order as dtype
  SEXP list_names;
  PROTECT(list_names = GET_NAMES(_Robj));
  if(LENGTH(list_names) != dtype_num_members) {
    warning("Not a named list\n");
    UNPROTECT(1);
    return(false);
  }
  for(int i=0; i< dtype_num_members; ++i) {
    member_name = H5Tget_member_name(dtype_id, i);
    if(strcmp(CHAR(STRING_ELT(list_names, i)), member_name)) { // does not match
      H5free_memory(member_name);
      warning("Names of list elements are not the same as compound\n");
      UNPROTECT(1);
      return(false);
    }
    else {
      H5free_memory(member_name);
    }
  }
  UNPROTECT(1);
    
  // check that all list elements have the same length
  SEXP Robj_item;
  SEXP dim;
  int unprotect_counter=0;
  bool ret_val = true;
  for(int i=0; i< dtype_num_members; ++i) {
    PROTECT(Robj_item = VECTOR_ELT(_Robj, i));
    unprotect_counter++;
    PROTECT(dim = GET_ATTR(Robj_item, R_DimSymbol));
    unprotect_counter++;
    // have to treat a data frame differently, as its length is the number of columns
    if(inherits(Robj_item, "data.frame")) {
      SEXP attr;
      PROTECT(attr = GET_ATTR(Robj_item, PROTECT(install("row.names"))));
      unprotect_counter+=2;
      if(XLENGTH(attr) != nelem) {
        warning("Number of row names not equal to number of nelem\n");
        ret_val = false;
      }
    }
    else if(!isNull(dim)) { // has a dimension, so is an array or matrix
      // if it is an array, the length does not correspond to the number of rows
      if(INTEGER(dim)[0]!=nelem) {
        warning("Has a dimension, but not the number of rows as expected\n");
        ret_val = false;
      }
    }
    else {
      if(XLENGTH(Robj_item) != nelem) {
        warning("Not all elements of the list have the same length\n");
        ret_val = false;
      }
    }
    // loop done - unprotect items
    UNPROTECT(unprotect_counter);
    unprotect_counter = 0;
    if(!ret_val) { // was set to false soemwhere in if statements; return now
        return(false);
    }
  }
  // nothing to UNPROTECT here; has been taken care of in the loop
  return(true);
}

// ascertain the dimensionality of an array datatype
// does this recursively if this is a nested array datatype
// the dimensionality is returned in R-fashion, i.e. reversed
SEXP get_array_dim(hid_t dtype_id) {
  hid_t dtype_base = H5Tget_super(dtype_id);
  SEXP dim;
  int array_rank = H5Tget_array_ndims(dtype_id);
  if(array_rank < 0) {
    error("An error occured when tyring to get the array dimensions\n");
  }
  if(array_rank == 0) {
    error("The array data type has to have at least a single dimension\n");
  }

  if(H5Tget_class(dtype_base)==H5T_ARRAY) {
    SEXP super_dim;
    PROTECT(super_dim=get_array_dim(dtype_base));
    // copy it and allocate space for array_rank more 
    PROTECT(dim = allocVector(INTSXP, array_rank + XLENGTH(super_dim)));
    memcpy(INTEGER(dim), INTEGER(super_dim), sizeof(int) * XLENGTH(super_dim));
    UNPROTECT(2); /* super_dim, dim */
    PROTECT(dim);
  }
  else {
    PROTECT(dim = allocVector(INTSXP, array_rank));
  }  
  H5Tclose(dtype_base);

  int total_num_dims = XLENGTH(dim);
  hsize_t cur_array_dim[array_rank];
  H5Tget_array_dims2(dtype_id, cur_array_dim);

  for(int i=0; i < array_rank; ++i) {
    INTEGER(dim)[total_num_dims - 1 - i] = cur_array_dim[i];
  }

  UNPROTECT(1);
  return(dim);
}


bool is_robj_array(SEXP _Robj, hid_t dtype_id) {
  // now check the base class; we are currently not supporting 
  // compound data types in array data types (unless it is of type complex)
  // may have to change this later to support tables inside arguments
  // this is not an issue that it isn't posibble, but rather that there is no good
  // equivalent object in R itself
  hid_t dtype_base = H5Tget_super(dtype_id);
  H5T_class_t base_class = H5Tget_class(dtype_base);
  if(base_class == H5T_COMPOUND && !is_h5_complex(dtype_base)) {
    H5Tclose(dtype_base);
    return(false);
  }
  H5Tclose(dtype_base);

  // get the dimensions of the dtype_id; check that it is of array type first
  if(H5Tget_class(dtype_id) != H5T_ARRAY) {
    return(false);
  }
  
  return(true);
}



// converts an R character vector to UTF8
// should internally be replaced by the function
// const char *reEnc(const char *x, cetype_t ce_in, cetype_t ce_out, int subst);
SEXP string_to_UTF8(SEXP _str) {
  SEXP res, s, t;
  
  t = s = PROTECT(allocList(2));
  SET_TYPEOF(s, LANGSXP);
  SETCAR(t, install("enc2utf8")); t = CDR(t);
  SETCAR(t,  _str); t = CDR(t);
  PROTECT(res = eval(s, R_GlobalEnv));
  UNPROTECT(2);
  return(res);
}


SEXP R_guess_nelem(SEXP _Robj, SEXP _dtype) {
  hid_t dtype_id = SEXP_to_longlong(_dtype, 0);
  return(ScalarInteger64_or_int(guess_nelem(_Robj, dtype_id)));
}

R_xlen_t guess_nelem(SEXP _Robj, hid_t dtype_id) {
  // using this one can estimate the number of elements in the _Robj
  // this is necessary for variable length arrays
  // as for this it is too complicated to pass in the length directly in the 
  // Robj itself
  // first check if it is a request for an empty object
  if(inherits(_Robj, "R_RToH5_empty")) {
    return(XLENGTH(_Robj));
  }

  H5T_class_t dtype_class = H5Tget_class(dtype_id);
  
  R_xlen_t nelem;
  switch(dtype_class) {
  case H5T_COMPOUND:
    if(TYPEOF(_Robj)==CPLXSXP) {
      nelem = XLENGTH(_Robj);
    }
    else {
      // check that it is a data frame
      // estimate it based on the LENGTH of the row.names
      if(!inherits(_Robj, "data.frame")) {
	error("dtype is of class compound, but R object is not a data.frame or complex");
      }
      nelem = XLENGTH(GET_ATTR(_Robj, install("row.names")));
      return(nelem);
      break;
    }
  case H5T_ARRAY: {
    // don't need to check if the robj is matching; will be done later
    hid_t dtype_base = H5Tget_super(dtype_id);
    hsize_t dtype_base_size = H5Tget_size(dtype_base);
    hsize_t num_rows = H5Tget_size(dtype_id) / dtype_base_size;
    H5Tclose(dtype_base);
    return(XLENGTH(_Robj) / num_rows);
    break;
  }
  case H5T_ENUM:
  case H5T_BITFIELD:
  case H5T_INTEGER:
  case H5T_FLOAT:
  case H5T_STRING:
  case H5T_OPAQUE:
  case H5T_VLEN:
    return(XLENGTH(_Robj));
    break;
  case H5T_REFERENCE: {
    SEXP hdf5r_ns = PROTECT(eval(PROTECT(lang2(PROTECT(install("getNamespace")), PROTECT(mkString("hdf5r")))), R_GlobalEnv));
    SEXP robj_len = PROTECT(eval(PROTECT(lang3(install("$"), _Robj, install("length"))), hdf5r_ns));
    UNPROTECT(6);
    return(SEXP_to_xlen(robj_len));
  }	      
  default:
    error("Error when retrieving class");
  }
}


void* VOIDPTR(SEXP x) {

  switch(TYPEOF(x)) {
  case REALSXP:
    return((void *) REAL(x));
  case INTSXP:
    return((void *) INTEGER(x));
  case LGLSXP:
    return((void *) LOGICAL(x));
  case CPLXSXP:
    return((void *) COMPLEX(x));
  case RAWSXP:
    return((void *) RAW(x));
  case STRSXP:
    return((void *) STRING_PTR(x));
  case VECSXP:
    return((void *) VECTOR_PTR(x));
  default:
    error("Type cannot be converted to voidptr\n");
  }
}

size_t R_get_item_size(SEXP x) {

  switch(TYPEOF(x)) {
  case REALSXP:
    return(sizeof(double));
  case INTSXP:
    return(sizeof(int));
  case LGLSXP:
    return(sizeof(int));
  case CPLXSXP:
    return(2 * sizeof(double));
  case RAWSXP:
    return(1);
  case STRSXP:
    return(sizeof(char*));
  case VECSXP:
    return(sizeof(void *));
  default:
    error("Type cannot be converted to voidptr\n");
  }
}


/******************************************
 * Converts an int64 to other types depending on the
 * flags that are set;
 ******************************************/
SEXP convert_int64_using_flags(SEXP val, int flags) {
  int64_t* ll_ptr = (int64_t*) REAL(val);
  R_xlen_t len = XLENGTH(val);
  
  int change_to_int;
  int change_to_double;
  int change_to_double_force;
  
  change_to_int = flags & H5TOR_CONV_INT64_INT_NOLOSS;
  change_to_double = flags & H5TOR_CONV_INT64_FLOAT_NOLOSS;
  change_to_double_force = flags & H5TOR_CONV_INT64_FLOAT_FORCE;
    
  if(!change_to_int && !change_to_double && !change_to_double_force) {
    return(val);
  }
  if(change_to_double_force) {
    change_to_double = true; // the NAs are here already set
    if(change_to_int) {
      for(R_xlen_t i = 0; i < len; ++i) {
	if(change_to_int && (ll_ptr[i] > INT_MAX || ll_ptr[i] < INT_MIN) && ll_ptr[i] != NA_INTEGER64) { // note - NA's don't count
	  change_to_int = false;
	  break;
	}
      }
    }
  }
  else {
    for(R_xlen_t i = 0; i < len; ++i) {
      if((ll_ptr[i] > MAX_INT_DOUBLE_PREC || ll_ptr[i] < MIN_INT_DOUBLE_PREC) && ll_ptr[i] != NA_INTEGER64 ) {
	return(val); // nothing will be changed as cannot even be represented by double
      }
      else if(change_to_int && (ll_ptr[i] > INT_MAX || ll_ptr[i] < INT_MIN) && ll_ptr[i] != NA_INTEGER64) {
	change_to_int = false;
	if(!change_to_double) {
	  return(val); // nothing to do anymore
	}
      }
    }
  }

  // create an integer vector of the same lenth and return it
  // or a double vector of the same length
  if(change_to_int) {
    change_to_double = false;
    SEXP val_int = PROTECT(NEW_INTEGER(len));
    for(R_xlen_t i = 0; i < len; ++i) {
      if(ll_ptr[i] == NA_INTEGER64) {
	INTEGER(val_int)[i] = NA_INTEGER;
      }
      else {
	INTEGER(val_int)[i] = ll_ptr[i]; // handles NA correctly automatically
      }
    }
    UNPROTECT(1);
    return(val_int);
  }
  else if(change_to_double) {
    SEXP val_double = PROTECT(convert_int64_to_double(val)); // NA-handling done there
    UNPROTECT(1);
    return(val_double);
  }
  else {
    // usually we can only arrive here if change_to_int and change_to_double were already false 
    // when starting the function
    error("no conversion to an int64 to be done; should have returned earlier");
  }
}

/******************************************
 * Converts an uint64 to either double of int64 depending on the
 * flags that are set;
 ******************************************/
SEXP convert_uint64_using_flags(SEXP val, int flags) {
  bool na_warning = false;
  if(flags & H5TOR_CONV_INT64_FLOAT_FORCE) {
    SEXP res = PROTECT(NEW_NUMERIC(XLENGTH(val)));
    uint64_t* ull_ptr = (uint64_t*) REAL(val);
    double* dbl_ptr = (double*) REAL(res);
    for(R_xlen_t i =0; i < XLENGTH(res); ++i) {
      dbl_ptr[i] = ull_ptr[i];
    }
    UNPROTECT(1);
    return(res);
  }
  else {
    SEXP res = PROTECT(duplicate(val));
    if(flags & H5TOR_CONV_UINT64_NA) {
      // set values that are too large to NA
      uint64_t* ull_ptr = (uint64_t*) REAL(res);
      int64_t* ll_ptr = (int64_t*) REAL(res);
      for(R_xlen_t i =0; i < XLENGTH(res); ++i) {
	if(ull_ptr[i] > LLONG_MAX) {
	  ll_ptr[i] = NA_INTEGER64;
	  na_warning = true;
	}
	else {
	  ll_ptr[i] = ull_ptr[i];
	}
      }
    }
    else {
      // do truncation
      uint64_t* ull_ptr = (uint64_t*) REAL(res);
      int64_t* ll_ptr = (int64_t*) REAL(res);
      for(R_xlen_t i =0; i < XLENGTH(res); ++i) {
	if(ull_ptr[i] > LLONG_MAX) {
	  ll_ptr[i] = LLONG_MAX;
	}
	else {
	  ll_ptr[i] = ull_ptr[i];
	}
      }
    }
    if(na_warning) {
      warning("NA created during coercion from uint64 value");
    }
    res = PROTECT(convert_int64_using_flags(res, flags));
    UNPROTECT(2);
    return(res);
  }


}



SEXP set_dim_attribute(SEXP x, SEXP dim) {
  // need to distinguish if it is an H5R object
  SEXP hdf5r_ns = PROTECT(eval(PROTECT(lang2(PROTECT(install("getNamespace")), PROTECT(mkString("hdf5r")))), R_GlobalEnv));
  
  if(inherits(x, "H5R")) {
    eval(PROTECT(lang3(install("dim<-"), x, dim)), hdf5r_ns);
    UNPROTECT(1);
  }
  else {
    setAttrib(x, R_DimSymbol, dim);
  }
    
  UNPROTECT(4);  
  return(x);
}
    

SEXP R_as_hex(SEXP x) {
  SEXP as_hex_r = PROTECT(NEW_CHARACTER(XLENGTH(x)));
  char as_hex[17];
  
  if(TYPEOF(x) == REALSXP) {
    for(R_xlen_t i = 0; i < XLENGTH(x); ++i) {
      snprintf(as_hex, 17, "%016llX", ((long long*)REAL(x))[i]);
      SET_STRING_ELT(as_hex_r, i, mkChar(as_hex));
    }
  }
  else if(TYPEOF(x) == INTSXP) {
    for(R_xlen_t i = 0; i < XLENGTH(x); ++i) {
      snprintf(as_hex, 17, "%08X", INTEGER(x)[i]);
      SET_STRING_ELT(as_hex_r, i, mkChar(as_hex));
    }
  }
  else {
    error("Only works for INTSXP and REALSXP\n");
  }
  UNPROTECT(1);
  return(as_hex_r);
}





// Create code that calls the conversion from R to int64 through the R layer
SEXP convert_double_to_int64(SEXP dbl_vec) {
  SEXP result;

  // int errorOccured; don't need that here; but otherwise, R_tryEval is the equivalent of try in R
  // first get the namespace of the bit64 package
  SEXP bit64_ns = PROTECT(eval(PROTECT(lang2(PROTECT(install("getNamespace")), PROTECT(mkString("bit64")))), R_GlobalEnv));
  // now use the namespace to call the as.integer64.double function
  PROTECT(result = eval(PROTECT(lang2(install("as.integer64.double"), dbl_vec)), bit64_ns));
  UNPROTECT(6);
  return(result);    
}


SEXP convert_int64_to_double(SEXP int64_vec) {
  SEXP result;
  SEXP bit64_ns = PROTECT(eval(PROTECT(lang2(PROTECT(install("getNamespace")), PROTECT(mkString("bit64")))), R_GlobalEnv));
  // now use the namespace to call the as.integer64.double function
  PROTECT(result = eval(PROTECT(lang2(install("as.double.integer64"), int64_vec)), bit64_ns));
  UNPROTECT(6);

  return(result);    
  
}


SEXP convert_int_to_int64(SEXP int_vec) {
  SEXP result;

  // int errorOccured; don't need that here; but otherwise, R_tryEval is the equivalent of try in R

  // first get the namespace of the bit64 package
  SEXP bit64_ns = PROTECT(eval(PROTECT(lang2(PROTECT(install("getNamespace")), PROTECT(mkString("bit64")))), R_GlobalEnv));
  // now use the namespace to call the as.integer64.double function
  PROTECT(result = eval(PROTECT(lang2(install("as.integer64.integer"), int_vec)), bit64_ns));
  UNPROTECT(6);

  return(result);    
}

SEXP convert_int64_to_int(SEXP int64_vec) {
  SEXP result;

  // int errorOccured; don't need that here; but otherwise, R_tryEval is the equivalent of try in R

  // first get the namespace of the bit64 package
  SEXP bit64_ns = PROTECT(eval(PROTECT(lang2(PROTECT(install("getNamespace")), PROTECT(mkString("bit64")))), R_GlobalEnv));
  // now use the namespace to call the as.integer64.double function
  PROTECT(result = eval(PROTECT(lang2(install("as.integer.integer64"), int64_vec)), bit64_ns));
  UNPROTECT(6);

  return(result);    
}


// create a new R6 class; do it with a do.call statement
SEXP new_H5R_R6_class(char * class_name, SEXP num, SEXP id) {
  SEXP result;

  // int errorOccured; don't need that here; but otherwise, R_tryEval is the equivalent of try in R

  // first get the namespace of the hdf5r package
  SEXP hdf5r_ns = PROTECT(eval(PROTECT(lang2(PROTECT(install("getNamespace")), PROTECT(mkString("hdf5r")))), R_GlobalEnv));
  // now use the namespace to call the as.integer64.double function
  SEXP r6_class_new = PROTECT(eval(PROTECT(lang3(install("$"), install(class_name), install("new"))), hdf5r_ns));
  result = PROTECT(eval(PROTECT(lang3(r6_class_new, num, id)), hdf5r_ns));
  UNPROTECT(8);

  return(result);    

}


/*****************************************************
 * collecting warnings issued by HDF5 during type conversions
 ****************************************************/


void H5T_conv_log_issue(H5T_conv_except_t except_type, H5T_conv_op_data *conv_op_data) {
  switch(except_type) {
    case H5T_CONV_EXCEPT_RANGE_HI:
      conv_op_data->H5T_CONV_EXCEPT_RANGE_HI = true;
      break;
    case H5T_CONV_EXCEPT_RANGE_LOW:
      conv_op_data->H5T_CONV_EXCEPT_RANGE_LOW = true;
      break;
    case H5T_CONV_EXCEPT_TRUNCATE:
      conv_op_data->H5T_CONV_EXCEPT_TRUNCATE = true;
      break;
    case H5T_CONV_EXCEPT_PRECISION:
      conv_op_data->H5T_CONV_EXCEPT_PRECISION = true;
      break;
    case H5T_CONV_EXCEPT_PINF:
      conv_op_data->H5T_CONV_EXCEPT_PINF = true;
      break;
    case H5T_CONV_EXCEPT_NINF:
      conv_op_data->H5T_CONV_EXCEPT_NINF = true;
      break;
    case H5T_CONV_EXCEPT_NAN:
      conv_op_data->H5T_CONV_EXCEPT_NAN = true;
      break;
  }
  return;
}
 
void H5T_conv_init(H5T_conv_op_data *conv_op_data) {
  conv_op_data->H5T_CONV_EXCEPT_RANGE_HI = false;
  conv_op_data->H5T_CONV_EXCEPT_RANGE_LOW = false;
  conv_op_data->H5T_CONV_EXCEPT_TRUNCATE = false;
  conv_op_data->H5T_CONV_EXCEPT_PRECISION = false;
  conv_op_data->H5T_CONV_EXCEPT_PINF = false;
  conv_op_data->H5T_CONV_EXCEPT_NINF = false;
  conv_op_data->H5T_CONV_EXCEPT_NAN = false;
  return;
}

int get_issue_string(H5T_conv_op_data conv_op_data, char* issue_string, size_t string_len) {

  int first_issue = true;
  issue_string[0] = '\0';
  if(string_len < 300) {
    error("The buffer for the issue string should at least have a size of 300");
  }
  strcat(issue_string, "During conversion, the following issues occured: ");
  if(conv_op_data.H5T_CONV_EXCEPT_RANGE_HI) {
    if(!first_issue) {
      strcat(issue_string, ", ");
    }
    strcat(issue_string, "H5T_CONV_EXCEPT_RANGE_HI");
    first_issue = false;
  }
  if(conv_op_data.H5T_CONV_EXCEPT_RANGE_LOW) {
    if(!first_issue) {
      strcat(issue_string, ", ");
    }
    strcat(issue_string, "H5T_CONV_EXCEPT_RANGE_LOW");
    first_issue = false;
  }
  if(conv_op_data.H5T_CONV_EXCEPT_TRUNCATE) {
    if(!first_issue) {
      strcat(issue_string, ", ");
    }
    strcat(issue_string, "H5T_CONV_EXCEPT_TRUNCATE");
    first_issue = false;
  }
  if(conv_op_data.H5T_CONV_EXCEPT_PRECISION) {
    if(!first_issue) {
      strcat(issue_string, ", ");
    }
    strcat(issue_string, "H5T_CONV_EXCEPT_PRECISION");
    first_issue = false;
  }
  if(conv_op_data.H5T_CONV_EXCEPT_PINF) {
    if(!first_issue) {
      strcat(issue_string, ", ");
    }
    strcat(issue_string, "H5T_CONV_EXCEPT_PINF");
    first_issue = false;
  }
  if(conv_op_data.H5T_CONV_EXCEPT_NINF) {
    if(!first_issue) {
      strcat(issue_string, ", ");
    }
    strcat(issue_string, "H5T_CONV_EXCEPT_NINF");
    first_issue = false;
  }
  if(conv_op_data.H5T_CONV_EXCEPT_NAN) {
    if(!first_issue) {
      strcat(issue_string, ", ");
    }
    strcat(issue_string, "H5T_CONV_EXCEPT_NAN");
    first_issue = false;
  }

  int has_issue = !first_issue;

  if(has_issue) {
    return(true);
  }
  else {
    return(false);
  }
}

// this callback function will do nothing (return that it is unhandled), and let hdf5 library handle it (which is usually truncation)
herr_t conv_cb_log(H5T_conv_except_t except_type, hid_t src_id, hid_t dst_id, void* src_buf, void* dst_buf, void* op_data) {
  H5T_conv_op_data* conv_op_data = op_data;
  H5T_conv_log_issue(except_type, conv_op_data);
  return(H5T_CONV_UNHANDLED);
}

herr_t H5Tconvert_with_warning(hid_t src_type_id, hid_t dest_type_id, size_t nelmts, void* buf) {
  herr_t herr;

  H5T_conv_op_data conv_op_data;
  H5T_conv_init(&conv_op_data);

  hid_t plist_id = H5Pcreate(H5P_DATASET_XFER);
  herr = H5Pset_type_conv_cb(plist_id, conv_cb_log, &conv_op_data);
  if(herr < 0) {
    error("Issue creating plist in H5Tconvert_with_warning");
  }
  herr = H5Tconvert(src_type_id, dest_type_id, nelmts, buf, NULL, plist_id);
  if(herr < 0) {
    H5Pclose(plist_id);
    return(herr);
  }
  H5Pclose(plist_id);

  // see if a warning needs to be issued
  char* issue_string = R_alloc(1, 300);
  int issue_res = get_issue_string(conv_op_data, issue_string, 300);
  if(issue_res) {
    warning(issue_string);
  }
  return(herr);
}



#############################################################################
##
## Copyright 2016 Novartis Institutes for BioMedical Research Inc.
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
## http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
##
#############################################################################



add_injection <- list(start=list(), pre_call=list(), post_call=list(), pre_list=list(), end=list())

## write injection code for H5Tset_size, that takes care of Infinity in the input
add_injection$pre_call$H5Tset_size <- c(
    "  // INJECTION CODE START",
    "  if(isReal(R_size ) && REAL(R_size)[0] == R_PosInf) {",
    "    size = H5T_VARIABLE;",
    "  }",
    "  // INJECTION CODE END"
    )


add_injection$pre_call$H5Sset_extent_simple <- c(
    "  // INJECTION CODE START",
    "  // the pointer is to const; need to cast it when I detect an Inf value",
    "  if(isReal(R_max)) {",
    "    hsize_t* max_helper = (hsize_t *) VOIDPTR(R_helper);",
    "    for(int i=0; i < rank; ++i) {",
    "      if(REAL(R_max)[i] == R_PosInf) {",
    "        max_helper[i] = H5S_UNLIMITED;",
    "      }",
    "    }",
    "  }",
    "  // INJECTION CODE END"
    )
    
add_injection$pre_call$H5Screate_simple <-  c(
    "  // INJECTION CODE START",
    "  // the pointer is to const; need to cast it when I detect an Inf value",
    "  if(isReal(R_maxdims)) {",
    "    hsize_t* maxdims_helper = (hsize_t *) VOIDPTR(R_helper);",
    "    for(int i=0; i < rank; ++i) {",
    "      if(REAL(R_maxdims)[i] == R_PosInf) {",
    "        maxdims_helper[i] = H5S_UNLIMITED;",
    "      }",
    "    }",
    "  }",
    "  // INJECTION CODE END"
    )


add_injection$pre_list$H5Sget_simple_extent_dims <- c(
    "  // INJECTION CODE START",
    "  // check if it is an int64 vector, and if yes which is H5S_UNLIMITED",
    "  // in that case, the return needs to be a real vector, so that Inf can be set",
    "  if(is_rint64(R_maxdims)) {",
    "    R_maxdims = PROTECT(convert_int64_using_flags(R_maxdims, H5TOR_CONV_INT64_FLOAT_FORCE));",
    "    vars_protected++;",
    "    double  dbl_unlimited = (double) LLONG_MAX;",
    "    R_xlen_t len = XLENGTH(R_maxdims);",
    "    for(R_xlen_t i = 0; i < len; ++i) {",
    "      if(REAL(R_maxdims)[i] == dbl_unlimited) {",
    "        REAL(R_maxdims)[i] = R_PosInf;",
    "      }",
    "    }",
    "  }",
    "  // INJECTION CODE END"
    )

add_injection$pre_call$H5Pset_chunk_cache <- c(
    "  // INJECTION CODE START",
    "  if(SEXP_to_longlong(R_rdcc_nslots, 0)==-1) {",
    "    rdcc_nslots = H5D_CHUNK_CACHE_NSLOTS_DEFAULT;",
    "  }",
    "  if(SEXP_to_longlong(R_rdcc_nbytes, 0)==-1) {",
    "    rdcc_nbytes = H5D_CHUNK_CACHE_NBYTES_DEFAULT;",
    "  }",
    "  if(SEXP_to_longlong(R_rdcc_w0, 0)==-1) {",
    "    rdcc_w0 = H5D_CHUNK_CACHE_W0_DEFAULT;",
    "  }",
    "  // INJECTION CODE END"
    )

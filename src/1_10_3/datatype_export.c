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



#include "datatype_export.h"

hid_t h5_datatype[DT_LAST_ITEM];

hid_t get_h5_equiv(int size, bool sign) {
  switch(size) {
  case 1: {
    if(sign) {
      return(H5T_NATIVE_INT8);
    }
    else {
      return(H5T_NATIVE_UINT8);
    }
  }
  case 2: {
    if(sign) {
      return(H5T_NATIVE_INT16);
    }
    else {
      return(H5T_NATIVE_UINT16);
    }
  }
  case 4: {
    if(sign) {
      return(H5T_NATIVE_INT32);
    }
    else {
      return(H5T_NATIVE_UINT32);
    }
  }
  case 8: {
    if(sign) {
      return(H5T_NATIVE_INT64);
    }
    else {
      return(H5T_NATIVE_UINT64);
    }
  }
  default:
    error("Unknown size\n");
  }
}


SEXP print_dtypes_array(void) {
  Rprintf("New -------------------------------------\n");
  for(int i=0; i < DT_LAST_ITEM; ++i) {
    Rprintf("%d: %ld\n", i, h5_datatype[i]);
  }
  return(R_NilValue);
}

SEXP init_dtypes(void) {
  // The predefined hdf5 datatypes
  h5_datatype[DT_H5T_IEEE_F32BE] = H5T_IEEE_F32BE;
  h5_datatype[DT_H5T_IEEE_F32LE] = H5T_IEEE_F32LE;
  h5_datatype[DT_H5T_IEEE_F64BE] = H5T_IEEE_F64BE;
  h5_datatype[DT_H5T_IEEE_F64LE] = H5T_IEEE_F64LE;
  h5_datatype[DT_H5T_STD_I8BE] = H5T_STD_I8BE;
  h5_datatype[DT_H5T_STD_I8LE] = H5T_STD_I8LE;
  h5_datatype[DT_H5T_STD_I16BE] = H5T_STD_I16BE;
  h5_datatype[DT_H5T_STD_I16LE] = H5T_STD_I16LE;
  h5_datatype[DT_H5T_STD_I32BE] = H5T_STD_I32BE;
  h5_datatype[DT_H5T_STD_I32LE] = H5T_STD_I32LE;
  h5_datatype[DT_H5T_STD_I64BE] = H5T_STD_I64BE;
  h5_datatype[DT_H5T_STD_I64LE] = H5T_STD_I64LE;
  h5_datatype[DT_H5T_STD_U8BE] = H5T_STD_U8BE;
  h5_datatype[DT_H5T_STD_U8LE] = H5T_STD_U8LE;
  h5_datatype[DT_H5T_STD_U16BE] = H5T_STD_U16BE;
  h5_datatype[DT_H5T_STD_U16LE] = H5T_STD_U16LE;
  h5_datatype[DT_H5T_STD_U32BE] = H5T_STD_U32BE;
  h5_datatype[DT_H5T_STD_U32LE] = H5T_STD_U32LE;
  h5_datatype[DT_H5T_STD_U64BE] = H5T_STD_U64BE;
  h5_datatype[DT_H5T_STD_U64LE] = H5T_STD_U64LE;
  h5_datatype[DT_H5T_STD_B8BE] = H5T_STD_B8BE;
  h5_datatype[DT_H5T_STD_B8LE] = H5T_STD_B8LE;
  h5_datatype[DT_H5T_STD_B16BE] = H5T_STD_B16BE;
  h5_datatype[DT_H5T_STD_B16LE] = H5T_STD_B16LE;
  h5_datatype[DT_H5T_STD_B32BE] = H5T_STD_B32BE;
  h5_datatype[DT_H5T_STD_B32LE] = H5T_STD_B32LE;
  h5_datatype[DT_H5T_STD_B64BE] = H5T_STD_B64BE;
  h5_datatype[DT_H5T_STD_B64LE] = H5T_STD_B64LE;
  h5_datatype[DT_H5T_STD_REF_OBJ] = H5T_STD_REF_OBJ;
  h5_datatype[DT_H5T_STD_REF_DSETREG] = H5T_STD_REF_DSETREG;
  h5_datatype[DT_H5T_UNIX_D32BE] = H5T_UNIX_D32BE;
  h5_datatype[DT_H5T_UNIX_D32LE] = H5T_UNIX_D32LE;
  h5_datatype[DT_H5T_UNIX_D64BE] = H5T_UNIX_D64BE;
  h5_datatype[DT_H5T_UNIX_D64LE] = H5T_UNIX_D64LE;
  h5_datatype[DT_H5T_C_S1] = H5T_C_S1;
  h5_datatype[DT_H5T_FORTRAN_S1] = H5T_FORTRAN_S1;
  h5_datatype[DT_H5T_INTEL_I8] = H5T_INTEL_I8;
  h5_datatype[DT_H5T_INTEL_I16] = H5T_INTEL_I16;
  h5_datatype[DT_H5T_INTEL_I32] = H5T_INTEL_I32;
  h5_datatype[DT_H5T_INTEL_I64] = H5T_INTEL_I64;
  h5_datatype[DT_H5T_INTEL_U8] = H5T_INTEL_U8;
  h5_datatype[DT_H5T_INTEL_U16] = H5T_INTEL_U16;
  h5_datatype[DT_H5T_INTEL_U32] = H5T_INTEL_U32;
  h5_datatype[DT_H5T_INTEL_U64] = H5T_INTEL_U64;
  h5_datatype[DT_H5T_INTEL_B8] = H5T_INTEL_B8;
  h5_datatype[DT_H5T_INTEL_B16] = H5T_INTEL_B16;
  h5_datatype[DT_H5T_INTEL_B32] = H5T_INTEL_B32;
  h5_datatype[DT_H5T_INTEL_B64] = H5T_INTEL_B64;
  h5_datatype[DT_H5T_INTEL_F32] = H5T_INTEL_F32;
  h5_datatype[DT_H5T_INTEL_F64] = H5T_INTEL_F64;
  h5_datatype[DT_H5T_ALPHA_I8] = H5T_ALPHA_I8;
  h5_datatype[DT_H5T_ALPHA_I16] = H5T_ALPHA_I16;
  h5_datatype[DT_H5T_ALPHA_I32] = H5T_ALPHA_I32;
  h5_datatype[DT_H5T_ALPHA_I64] = H5T_ALPHA_I64;
  h5_datatype[DT_H5T_ALPHA_U8] = H5T_ALPHA_U8;
  h5_datatype[DT_H5T_ALPHA_U16] = H5T_ALPHA_U16;
  h5_datatype[DT_H5T_ALPHA_U32] = H5T_ALPHA_U32;
  h5_datatype[DT_H5T_ALPHA_U64] = H5T_ALPHA_U64;
  h5_datatype[DT_H5T_ALPHA_B8] = H5T_ALPHA_B8;
  h5_datatype[DT_H5T_ALPHA_B16] = H5T_ALPHA_B16;
  h5_datatype[DT_H5T_ALPHA_B32] = H5T_ALPHA_B32;
  h5_datatype[DT_H5T_ALPHA_B64] = H5T_ALPHA_B64;
  h5_datatype[DT_H5T_ALPHA_F32] = H5T_ALPHA_F32;
  h5_datatype[DT_H5T_ALPHA_F64] = H5T_ALPHA_F64;
  h5_datatype[DT_H5T_MIPS_I8] = H5T_MIPS_I8;
  h5_datatype[DT_H5T_MIPS_I16] = H5T_MIPS_I16;
  h5_datatype[DT_H5T_MIPS_I32] = H5T_MIPS_I32;
  h5_datatype[DT_H5T_MIPS_I64] = H5T_MIPS_I64;
  h5_datatype[DT_H5T_MIPS_U8] = H5T_MIPS_U8;
  h5_datatype[DT_H5T_MIPS_U16] = H5T_MIPS_U16;
  h5_datatype[DT_H5T_MIPS_U32] = H5T_MIPS_U32;
  h5_datatype[DT_H5T_MIPS_U64] = H5T_MIPS_U64;
  h5_datatype[DT_H5T_MIPS_B8] = H5T_MIPS_B8;
  h5_datatype[DT_H5T_MIPS_B16] = H5T_MIPS_B16;
  h5_datatype[DT_H5T_MIPS_B32] = H5T_MIPS_B32;
  h5_datatype[DT_H5T_MIPS_B64] = H5T_MIPS_B64;
  h5_datatype[DT_H5T_MIPS_F32] = H5T_MIPS_F32;
  h5_datatype[DT_H5T_MIPS_F64] = H5T_MIPS_F64;
  h5_datatype[DT_H5T_VAX_F32] = H5T_VAX_F32;
  h5_datatype[DT_H5T_VAX_F64] = H5T_VAX_F64;
  h5_datatype[DT_H5T_NATIVE_CHAR] = H5T_NATIVE_CHAR;
  h5_datatype[DT_H5T_NATIVE_SCHAR] = H5T_NATIVE_SCHAR;
  h5_datatype[DT_H5T_NATIVE_UCHAR] = H5T_NATIVE_UCHAR;
  h5_datatype[DT_H5T_NATIVE_SHORT] = H5T_NATIVE_SHORT;
  h5_datatype[DT_H5T_NATIVE_USHORT] = H5T_NATIVE_USHORT;
  h5_datatype[DT_H5T_NATIVE_INT] = H5T_NATIVE_INT;
  h5_datatype[DT_H5T_NATIVE_UINT] = H5T_NATIVE_UINT;
  h5_datatype[DT_H5T_NATIVE_LONG] = H5T_NATIVE_LONG;
  h5_datatype[DT_H5T_NATIVE_ULONG] = H5T_NATIVE_ULONG;
  h5_datatype[DT_H5T_NATIVE_LLONG] = H5T_NATIVE_LLONG;
  h5_datatype[DT_H5T_NATIVE_ULLONG] = H5T_NATIVE_ULLONG;
  h5_datatype[DT_H5T_NATIVE_FLOAT] = H5T_NATIVE_FLOAT;
  h5_datatype[DT_H5T_NATIVE_DOUBLE] = H5T_NATIVE_DOUBLE;
  h5_datatype[DT_H5T_NATIVE_B8] = H5T_NATIVE_B8;
  h5_datatype[DT_H5T_NATIVE_B16] = H5T_NATIVE_B16;
  h5_datatype[DT_H5T_NATIVE_B32] = H5T_NATIVE_B32;
  h5_datatype[DT_H5T_NATIVE_B64] = H5T_NATIVE_B64;
  h5_datatype[DT_H5T_NATIVE_OPAQUE] = H5T_NATIVE_OPAQUE;
  h5_datatype[DT_H5T_NATIVE_HADDR] = H5T_NATIVE_HADDR;
  h5_datatype[DT_H5T_NATIVE_HSIZE] = H5T_NATIVE_HSIZE;
  h5_datatype[DT_H5T_NATIVE_HSSIZE] = H5T_NATIVE_HSSIZE;
  h5_datatype[DT_H5T_NATIVE_HERR] = H5T_NATIVE_HERR;
  h5_datatype[DT_H5T_NATIVE_HBOOL] = H5T_NATIVE_HBOOL;
  h5_datatype[DT_H5T_NATIVE_INT8] = H5T_NATIVE_INT8;
  h5_datatype[DT_H5T_NATIVE_UINT8] = H5T_NATIVE_UINT8;
  h5_datatype[DT_H5T_NATIVE_INT_LEAST8] = H5T_NATIVE_INT_LEAST8;
  h5_datatype[DT_H5T_NATIVE_UINT_LEAST8] = H5T_NATIVE_UINT_LEAST8;
  h5_datatype[DT_H5T_NATIVE_INT_FAST8] = H5T_NATIVE_INT_FAST8;
  h5_datatype[DT_H5T_NATIVE_UINT_FAST8] = H5T_NATIVE_UINT_FAST8;
  h5_datatype[DT_H5T_NATIVE_INT16] = H5T_NATIVE_INT16;
  h5_datatype[DT_H5T_NATIVE_UINT16] = H5T_NATIVE_UINT16;
  h5_datatype[DT_H5T_NATIVE_INT_LEAST16] = H5T_NATIVE_INT_LEAST16;
  h5_datatype[DT_H5T_NATIVE_UINT_LEAST16] = H5T_NATIVE_UINT_LEAST16;
  h5_datatype[DT_H5T_NATIVE_INT_FAST16] = H5T_NATIVE_INT_FAST16;
  h5_datatype[DT_H5T_NATIVE_UINT_FAST16] = H5T_NATIVE_UINT_FAST16;
  h5_datatype[DT_H5T_NATIVE_INT32] = H5T_NATIVE_INT32;
  h5_datatype[DT_H5T_NATIVE_UINT32] = H5T_NATIVE_UINT32;
  h5_datatype[DT_H5T_NATIVE_INT_LEAST32] = H5T_NATIVE_INT_LEAST32;
  h5_datatype[DT_H5T_NATIVE_UINT_LEAST32] = H5T_NATIVE_UINT_LEAST32;
  h5_datatype[DT_H5T_NATIVE_INT_FAST32] = H5T_NATIVE_INT_FAST32;
  h5_datatype[DT_H5T_NATIVE_UINT_FAST32] = H5T_NATIVE_UINT_FAST32;
  h5_datatype[DT_H5T_NATIVE_INT64] = H5T_NATIVE_INT64;
  h5_datatype[DT_H5T_NATIVE_UINT64] = H5T_NATIVE_UINT64;
  h5_datatype[DT_H5T_NATIVE_INT_LEAST64] = H5T_NATIVE_INT_LEAST64;
  h5_datatype[DT_H5T_NATIVE_UINT_LEAST64] = H5T_NATIVE_UINT_LEAST64;
  h5_datatype[DT_H5T_NATIVE_INT_FAST64] = H5T_NATIVE_INT_FAST64;
  h5_datatype[DT_H5T_NATIVE_UINT_FAST64] = H5T_NATIVE_UINT_FAST64;
#if H5_SIZEOF_LONG_DOUBLE !=0
  h5_datatype[DT_H5T_NATIVE_LDOUBLE] = H5T_NATIVE_LDOUBLE;
#endif
  // the C_API_types
  h5_datatype[DT_ssize_t] = get_h5_equiv(sizeof(ssize_t), issigned(ssize_t));
  h5_datatype[DT_hsize_t] = get_h5_equiv(sizeof(hsize_t), issigned(hsize_t));
  h5_datatype[DT_size_t] = get_h5_equiv(sizeof(size_t), issigned(size_t));
  h5_datatype[DT_haddr_t] = get_h5_equiv(sizeof(haddr_t), issigned(haddr_t));
  h5_datatype[DT_hssize_t] = get_h5_equiv(sizeof(hssize_t), issigned(hssize_t));
  h5_datatype[DT_unsigned_long] = get_h5_equiv(sizeof(unsigned long), issigned(unsigned long));
  h5_datatype[DT_off_t] = get_h5_equiv(sizeof(off_t), issigned(off_t));
  h5_datatype[DT_uint64_t] = get_h5_equiv(sizeof(uint64_t), issigned(uint64_t));
  h5_datatype[DT_long_int] = get_h5_equiv(sizeof(long int), issigned(long int));
  h5_datatype[DT_int64_t] = get_h5_equiv(sizeof(int64_t), issigned(int64_t));
  h5_datatype[DT_time_t] = get_h5_equiv(sizeof(time_t), issigned(time_t));
  h5_datatype[DT_hid_t] = get_h5_equiv(sizeof(hid_t), issigned(hid_t));
  h5_datatype[DT_herr_t] = get_h5_equiv(sizeof(herr_t), issigned(herr_t));
  h5_datatype[DT_htri_t] = get_h5_equiv(sizeof(htri_t), issigned(htri_t));
  h5_datatype[DT_int] = get_h5_equiv(sizeof(int), issigned(int));
  h5_datatype[DT_unsigned] = get_h5_equiv(sizeof(unsigned), issigned(unsigned));
  h5_datatype[DT_hbool_t] = get_h5_equiv(sizeof(hbool_t), issigned(hbool_t));
  h5_datatype[DT_unsigned_int] = get_h5_equiv(sizeof(unsigned int), issigned(unsigned int));
  h5_datatype[DT_H5E_major_t] = get_h5_equiv(sizeof(H5E_major_t), issigned(H5E_major_t));
  h5_datatype[DT_H5E_minor_t] = get_h5_equiv(sizeof(H5E_minor_t), issigned(H5E_minor_t));
  h5_datatype[DT_H5G_link_t] = get_h5_equiv(sizeof(H5G_link_t), issigned(H5G_link_t));
  h5_datatype[DT_H5Z_filter_t] = get_h5_equiv(sizeof(H5Z_filter_t), issigned(H5Z_filter_t));
  h5_datatype[DT_H5FD_mem_t] = get_h5_equiv(sizeof(H5FD_mem_t), issigned(H5FD_mem_t));
  h5_datatype[DT_H5O_msg_crt_idx_t] = get_h5_equiv(sizeof(H5O_msg_crt_idx_t), issigned(H5O_msg_crt_idx_t));
  h5_datatype[DT_unsigned_char] = get_h5_equiv(sizeof(unsigned char), issigned(unsigned char));
  h5_datatype[DT_long] = get_h5_equiv(sizeof(long), issigned(long));
  h5_datatype[DT_long_long] = get_h5_equiv(sizeof(long long), issigned(long long));
  h5_datatype[DT_short] = get_h5_equiv(sizeof(short), issigned(short));
  h5_datatype[DT_unsigned_short] = get_h5_equiv(sizeof(unsigned short), issigned(unsigned short));
  h5_datatype[DT_uint32_t] = get_h5_equiv(sizeof(uint32_t), issigned(uint32_t));
  h5_datatype[DT_unsigned_long_long] = get_h5_equiv(sizeof(unsigned long long), issigned(unsigned long long));
  // the string and double datatypes
  h5_datatype[DT_char] = H5Tcopy(H5T_C_S1);
  H5Tset_size(h5_datatype[DT_char], H5T_VARIABLE);
  h5_datatype[DT_double] = H5T_NATIVE_DOUBLE;
  h5_datatype[DT_float] = H5T_NATIVE_FLOAT;
  // the enums
  h5_datatype[DT_H5C_cache_decr_mode] = create_DT_H5C_cache_decr_mode();
  h5_datatype[DT_H5C_cache_flash_incr_mode] = create_DT_H5C_cache_flash_incr_mode();
  h5_datatype[DT_H5C_cache_incr_mode] = create_DT_H5C_cache_incr_mode();
  h5_datatype[DT_H5D_alloc_time_t] = create_DT_H5D_alloc_time_t();
  h5_datatype[DT_H5D_chunk_index_t] = create_DT_H5D_chunk_index_t();
  h5_datatype[DT_H5D_fill_time_t] = create_DT_H5D_fill_time_t();
  h5_datatype[DT_H5D_fill_value_t] = create_DT_H5D_fill_value_t();
  h5_datatype[DT_H5D_layout_t] = create_DT_H5D_layout_t();
  h5_datatype[DT_H5D_space_status_t] = create_DT_H5D_space_status_t();
  h5_datatype[DT_H5D_vds_view_t] = create_DT_H5D_vds_view_t();
  h5_datatype[DT_H5E_direction_t] = create_DT_H5E_direction_t();
  h5_datatype[DT_H5E_type_t] = create_DT_H5E_type_t();
  h5_datatype[DT_H5FD_file_image_op_t] = create_DT_H5FD_file_image_op_t();
  h5_datatype[DT_H5F_close_degree_t] = create_DT_H5F_close_degree_t();
  h5_datatype[DT_H5F_file_space_type_t] = create_DT_H5F_file_space_type_t();
  h5_datatype[DT_H5F_fspace_strategy_t] = create_DT_H5F_fspace_strategy_t();
  h5_datatype[DT_H5F_libver_t] = create_DT_H5F_libver_t();
  h5_datatype[DT_H5F_mem_t] = create_DT_H5F_mem_t();
  h5_datatype[DT_H5F_scope_t] = create_DT_H5F_scope_t();
  h5_datatype[DT_H5G_obj_t] = create_DT_H5G_obj_t();
  h5_datatype[DT_H5G_storage_type_t] = create_DT_H5G_storage_type_t();
  h5_datatype[DT_H5I_type_t] = create_DT_H5I_type_t();
  h5_datatype[DT_H5L_type_t] = create_DT_H5L_type_t();
  h5_datatype[DT_H5LT_lang_t] = create_DT_H5LT_lang_t();
  h5_datatype[DT_H5O_mcdt_search_ret_t] = create_DT_H5O_mcdt_search_ret_t();
  h5_datatype[DT_H5O_type_t] = create_DT_H5O_type_t();
  h5_datatype[DT_H5PL_type_t] = create_DT_H5PL_type_t();
  h5_datatype[DT_H5D_mpio_actual_chunk_opt_mode_t] = create_DT_H5D_mpio_actual_chunk_opt_mode_t();
  h5_datatype[DT_H5D_mpio_actual_io_mode_t] = create_DT_H5D_mpio_actual_io_mode_t();
  h5_datatype[DT_H5D_mpio_no_collective_cause_t] = create_DT_H5D_mpio_no_collective_cause_t();
  h5_datatype[DT_H5_iter_order_t] = create_DT_H5_iter_order_t();
  h5_datatype[DT_H5_index_t] = create_DT_H5_index_t();
  h5_datatype[DT_H5R_type_t] = create_DT_H5R_type_t();
  h5_datatype[DT_H5S_sel_type] = create_DT_H5S_sel_type();
  h5_datatype[DT_H5S_class_t] = create_DT_H5S_class_t();
  h5_datatype[DT_H5S_seloper_t] = create_DT_H5S_seloper_t();
  h5_datatype[DT_H5T_bkg_t] = create_DT_H5T_bkg_t();
  h5_datatype[DT_H5T_class_t] = create_DT_H5T_class_t();
  h5_datatype[DT_H5T_cmd_t] = create_DT_H5T_cmd_t();
  h5_datatype[DT_H5T_conv_except_t] = create_DT_H5T_conv_except_t();
  h5_datatype[DT_H5T_conv_ret_t] = create_DT_H5T_conv_ret_t();
  h5_datatype[DT_H5T_cset_t] = create_DT_H5T_cset_t();
  h5_datatype[DT_H5T_direction_t] = create_DT_H5T_direction_t();
  h5_datatype[DT_H5T_norm_t] = create_DT_H5T_norm_t();
  h5_datatype[DT_H5T_order_t] = create_DT_H5T_order_t();
  h5_datatype[DT_H5T_pad_t] = create_DT_H5T_pad_t();
  h5_datatype[DT_H5T_pers_t] = create_DT_H5T_pers_t();
  h5_datatype[DT_H5T_sign_t] = create_DT_H5T_sign_t();
  h5_datatype[DT_H5T_str_t] = create_DT_H5T_str_t();
  h5_datatype[DT_H5Z_cb_return_t] = create_DT_H5Z_cb_return_t();
  h5_datatype[DT_H5Z_EDC_t] = create_DT_H5Z_EDC_t();
  h5_datatype[DT_H5Z_SO_scale_type_t] = create_DT_H5Z_SO_scale_type_t();
  // the structs; the following are out of order, as more basic structs need to be created first
  // for DT_H5L_info_helper_t careful; not a struct but a union; only address specified, not size
  // will only work properly in both cases if haddr_t and size_t are the same type
  h5_datatype[DT_H5_ih_info_t] = create_DT_H5_ih_info_t();
  h5_datatype[DT_H5AC_cache_config_t] = create_DT_H5AC_cache_config_t();
  h5_datatype[DT_H5A_info_t] = create_DT_H5A_info_t();
  h5_datatype[DT_H5E_error1_t] = create_DT_H5E_error1_t();
  h5_datatype[DT_H5E_error2_t] = create_DT_H5E_error2_t();
  h5_datatype[DT_H5F_info1_helper_t] = create_DT_H5F_info1_helper_t();
  h5_datatype[DT_H5F_info1_t] = create_DT_H5F_info1_t();
  h5_datatype[DT_H5F_info2_super_t] = create_DT_H5F_info2_super_t();
  h5_datatype[DT_H5F_info2_free_t] = create_DT_H5F_info2_free_t();
  h5_datatype[DT_H5F_info2_sohm_t] = create_DT_H5F_info2_sohm_t();
  h5_datatype[DT_H5F_info2_t] = create_DT_H5F_info2_t();
  h5_datatype[DT_H5G_info_t] = create_DT_H5G_info_t();
  h5_datatype[DT_H5L_info_helper_t] = create_DT_H5L_info_helper_t();
  h5_datatype[DT_H5L_info_t] = create_DT_H5L_info_t();
  h5_datatype[DT_H5O_hdr_info_helper_msg_t] = create_DT_H5O_hdr_info_helper_msg_t();
  h5_datatype[DT_H5O_hdr_info_helper_space_t] = create_DT_H5O_hdr_info_helper_space_t();
  h5_datatype[DT_H5O_hdr_info_t] = create_DT_H5O_hdr_info_t();
  h5_datatype[DT_H5O_info_helper_t] = create_DT_H5O_info_helper_t();
  h5_datatype[DT_H5O_info_t] = create_DT_H5O_info_t();
  h5_datatype[DT_H5O_stat_t] = create_DT_H5O_stat_t();
  h5_datatype[DT_H5AC_cache_image_config_t] = create_DT_H5AC_cache_image_config_t();
  h5_datatype[DT_H5F_retry_info_t] = create_DT_H5F_retry_info_t();
  h5_datatype[DT_H5F_sect_info_t] = create_DT_H5F_sect_info_t();
  h5_datatype[DT_H5D_info_t] = create_DT_H5D_info_t();
  h5_datatype[DT_H5ls_info_t] = create_DT_H5ls_info_t();
  return(R_NilValue);
}





/*************************************************************************
 *
 * Create the dataframe with all the type information
 *
 *************************************************************************/

SEXP show_all_types_data_frame(void) {
  SEXP df = PROTECT(allocVector(VECSXP, 3));
  SET_VECTOR_ELT(df, 0, NEW_CHARACTER(DT_LAST_ITEM));
  SET_VECTOR_ELT(df, 1, NEW_CHARACTER(DT_LAST_ITEM));
  SEXP R_type = PROTECT(NEW_NUMERIC(DT_LAST_ITEM));
  SET_CLASS(R_type, ScalarString(mkChar("integer64")));
  SET_VECTOR_ELT(df, 2, R_type);
  SEXP df_rownames = PROTECT(NEW_INTEGER(DT_LAST_ITEM));
  for(R_xlen_t i = 0; i < DT_LAST_ITEM; ++i) {
    INTEGER(df_rownames)[i] = i + 1;
  }
  SET_CLASS(df, mkString("data.frame"));
  SET_ATTR(df, install("row.names"), df_rownames);
  SEXP df_names = PROTECT(NEW_CHARACTER(3));
  SET_STRING_ELT(df_names, 0, mkChar("Category"));
  SET_STRING_ELT(df_names, 1, mkChar("Name"));
  SET_STRING_ELT(df_names, 2, mkChar("Type_id"));
  SET_NAMES(df, df_names);
  SEXP R_categ = VECTOR_ELT(df, 0);
  SEXP R_name = VECTOR_ELT(df, 1);
  R_type = VECTOR_ELT(df, 2);

  SET_STRING_ELT(R_categ, DT_H5T_IEEE_F32BE, mkChar("IEEE"));
  SET_STRING_ELT(R_name, DT_H5T_IEEE_F32BE, mkChar("H5T_IEEE_F32BE"));
  ((long long *) REAL(R_type))[DT_H5T_IEEE_F32BE] = h5_datatype[DT_H5T_IEEE_F32BE];

  SET_STRING_ELT(R_categ, DT_H5T_IEEE_F32LE, mkChar("IEEE"));
  SET_STRING_ELT(R_name, DT_H5T_IEEE_F32LE, mkChar("H5T_IEEE_F32LE"));
  ((long long *) REAL(R_type))[DT_H5T_IEEE_F32LE] = h5_datatype[DT_H5T_IEEE_F32LE];

  SET_STRING_ELT(R_categ, DT_H5T_IEEE_F64BE, mkChar("IEEE"));
  SET_STRING_ELT(R_name, DT_H5T_IEEE_F64BE, mkChar("H5T_IEEE_F64BE"));
  ((long long *) REAL(R_type))[DT_H5T_IEEE_F64BE] = h5_datatype[DT_H5T_IEEE_F64BE];

  SET_STRING_ELT(R_categ, DT_H5T_IEEE_F64LE, mkChar("IEEE"));
  SET_STRING_ELT(R_name, DT_H5T_IEEE_F64LE, mkChar("H5T_IEEE_F64LE"));
  ((long long *) REAL(R_type))[DT_H5T_IEEE_F64LE] = h5_datatype[DT_H5T_IEEE_F64LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_I8BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_I8BE, mkChar("H5T_STD_I8BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_I8BE] = h5_datatype[DT_H5T_STD_I8BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_I8LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_I8LE, mkChar("H5T_STD_I8LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_I8LE] = h5_datatype[DT_H5T_STD_I8LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_I16BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_I16BE, mkChar("H5T_STD_I16BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_I16BE] = h5_datatype[DT_H5T_STD_I16BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_I16LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_I16LE, mkChar("H5T_STD_I16LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_I16LE] = h5_datatype[DT_H5T_STD_I16LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_I32BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_I32BE, mkChar("H5T_STD_I32BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_I32BE] = h5_datatype[DT_H5T_STD_I32BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_I32LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_I32LE, mkChar("H5T_STD_I32LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_I32LE] = h5_datatype[DT_H5T_STD_I32LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_I64BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_I64BE, mkChar("H5T_STD_I64BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_I64BE] = h5_datatype[DT_H5T_STD_I64BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_I64LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_I64LE, mkChar("H5T_STD_I64LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_I64LE] = h5_datatype[DT_H5T_STD_I64LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_U8BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_U8BE, mkChar("H5T_STD_U8BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_U8BE] = h5_datatype[DT_H5T_STD_U8BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_U8LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_U8LE, mkChar("H5T_STD_U8LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_U8LE] = h5_datatype[DT_H5T_STD_U8LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_U16BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_U16BE, mkChar("H5T_STD_U16BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_U16BE] = h5_datatype[DT_H5T_STD_U16BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_U16LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_U16LE, mkChar("H5T_STD_U16LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_U16LE] = h5_datatype[DT_H5T_STD_U16LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_U32BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_U32BE, mkChar("H5T_STD_U32BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_U32BE] = h5_datatype[DT_H5T_STD_U32BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_U32LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_U32LE, mkChar("H5T_STD_U32LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_U32LE] = h5_datatype[DT_H5T_STD_U32LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_U64BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_U64BE, mkChar("H5T_STD_U64BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_U64BE] = h5_datatype[DT_H5T_STD_U64BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_U64LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_U64LE, mkChar("H5T_STD_U64LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_U64LE] = h5_datatype[DT_H5T_STD_U64LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_B8BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_B8BE, mkChar("H5T_STD_B8BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_B8BE] = h5_datatype[DT_H5T_STD_B8BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_B8LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_B8LE, mkChar("H5T_STD_B8LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_B8LE] = h5_datatype[DT_H5T_STD_B8LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_B16BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_B16BE, mkChar("H5T_STD_B16BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_B16BE] = h5_datatype[DT_H5T_STD_B16BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_B16LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_B16LE, mkChar("H5T_STD_B16LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_B16LE] = h5_datatype[DT_H5T_STD_B16LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_B32BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_B32BE, mkChar("H5T_STD_B32BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_B32BE] = h5_datatype[DT_H5T_STD_B32BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_B32LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_B32LE, mkChar("H5T_STD_B32LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_B32LE] = h5_datatype[DT_H5T_STD_B32LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_B64BE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_B64BE, mkChar("H5T_STD_B64BE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_B64BE] = h5_datatype[DT_H5T_STD_B64BE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_B64LE, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_B64LE, mkChar("H5T_STD_B64LE"));
  ((long long *) REAL(R_type))[DT_H5T_STD_B64LE] = h5_datatype[DT_H5T_STD_B64LE];

  SET_STRING_ELT(R_categ, DT_H5T_STD_REF_OBJ, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_REF_OBJ, mkChar("H5T_STD_REF_OBJ"));
  ((long long *) REAL(R_type))[DT_H5T_STD_REF_OBJ] = h5_datatype[DT_H5T_STD_REF_OBJ];

  SET_STRING_ELT(R_categ, DT_H5T_STD_REF_DSETREG, mkChar("STD"));
  SET_STRING_ELT(R_name, DT_H5T_STD_REF_DSETREG, mkChar("H5T_STD_REF_DSETREG"));
  ((long long *) REAL(R_type))[DT_H5T_STD_REF_DSETREG] = h5_datatype[DT_H5T_STD_REF_DSETREG];

  SET_STRING_ELT(R_categ, DT_H5T_UNIX_D32BE, mkChar("UNIX"));
  SET_STRING_ELT(R_name, DT_H5T_UNIX_D32BE, mkChar("H5T_UNIX_D32BE"));
  ((long long *) REAL(R_type))[DT_H5T_UNIX_D32BE] = h5_datatype[DT_H5T_UNIX_D32BE];

  SET_STRING_ELT(R_categ, DT_H5T_UNIX_D32LE, mkChar("UNIX"));
  SET_STRING_ELT(R_name, DT_H5T_UNIX_D32LE, mkChar("H5T_UNIX_D32LE"));
  ((long long *) REAL(R_type))[DT_H5T_UNIX_D32LE] = h5_datatype[DT_H5T_UNIX_D32LE];

  SET_STRING_ELT(R_categ, DT_H5T_UNIX_D64BE, mkChar("UNIX"));
  SET_STRING_ELT(R_name, DT_H5T_UNIX_D64BE, mkChar("H5T_UNIX_D64BE"));
  ((long long *) REAL(R_type))[DT_H5T_UNIX_D64BE] = h5_datatype[DT_H5T_UNIX_D64BE];

  SET_STRING_ELT(R_categ, DT_H5T_UNIX_D64LE, mkChar("UNIX"));
  SET_STRING_ELT(R_name, DT_H5T_UNIX_D64LE, mkChar("H5T_UNIX_D64LE"));
  ((long long *) REAL(R_type))[DT_H5T_UNIX_D64LE] = h5_datatype[DT_H5T_UNIX_D64LE];

  SET_STRING_ELT(R_categ, DT_H5T_C_S1, mkChar("STRING"));
  SET_STRING_ELT(R_name, DT_H5T_C_S1, mkChar("H5T_C_S1"));
  ((long long *) REAL(R_type))[DT_H5T_C_S1] = h5_datatype[DT_H5T_C_S1];

  SET_STRING_ELT(R_categ, DT_H5T_FORTRAN_S1, mkChar("STRING"));
  SET_STRING_ELT(R_name, DT_H5T_FORTRAN_S1, mkChar("H5T_FORTRAN_S1"));
  ((long long *) REAL(R_type))[DT_H5T_FORTRAN_S1] = h5_datatype[DT_H5T_FORTRAN_S1];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_I8, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_I8, mkChar("H5T_INTEL_I8"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_I8] = h5_datatype[DT_H5T_INTEL_I8];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_I16, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_I16, mkChar("H5T_INTEL_I16"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_I16] = h5_datatype[DT_H5T_INTEL_I16];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_I32, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_I32, mkChar("H5T_INTEL_I32"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_I32] = h5_datatype[DT_H5T_INTEL_I32];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_I64, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_I64, mkChar("H5T_INTEL_I64"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_I64] = h5_datatype[DT_H5T_INTEL_I64];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_U8, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_U8, mkChar("H5T_INTEL_U8"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_U8] = h5_datatype[DT_H5T_INTEL_U8];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_U16, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_U16, mkChar("H5T_INTEL_U16"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_U16] = h5_datatype[DT_H5T_INTEL_U16];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_U32, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_U32, mkChar("H5T_INTEL_U32"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_U32] = h5_datatype[DT_H5T_INTEL_U32];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_U64, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_U64, mkChar("H5T_INTEL_U64"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_U64] = h5_datatype[DT_H5T_INTEL_U64];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_B8, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_B8, mkChar("H5T_INTEL_B8"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_B8] = h5_datatype[DT_H5T_INTEL_B8];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_B16, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_B16, mkChar("H5T_INTEL_B16"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_B16] = h5_datatype[DT_H5T_INTEL_B16];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_B32, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_B32, mkChar("H5T_INTEL_B32"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_B32] = h5_datatype[DT_H5T_INTEL_B32];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_B64, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_B64, mkChar("H5T_INTEL_B64"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_B64] = h5_datatype[DT_H5T_INTEL_B64];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_F32, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_F32, mkChar("H5T_INTEL_F32"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_F32] = h5_datatype[DT_H5T_INTEL_F32];

  SET_STRING_ELT(R_categ, DT_H5T_INTEL_F64, mkChar("INTEL"));
  SET_STRING_ELT(R_name, DT_H5T_INTEL_F64, mkChar("H5T_INTEL_F64"));
  ((long long *) REAL(R_type))[DT_H5T_INTEL_F64] = h5_datatype[DT_H5T_INTEL_F64];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_I8, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_I8, mkChar("H5T_ALPHA_I8"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_I8] = h5_datatype[DT_H5T_ALPHA_I8];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_I16, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_I16, mkChar("H5T_ALPHA_I16"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_I16] = h5_datatype[DT_H5T_ALPHA_I16];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_I32, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_I32, mkChar("H5T_ALPHA_I32"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_I32] = h5_datatype[DT_H5T_ALPHA_I32];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_I64, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_I64, mkChar("H5T_ALPHA_I64"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_I64] = h5_datatype[DT_H5T_ALPHA_I64];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_U8, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_U8, mkChar("H5T_ALPHA_U8"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_U8] = h5_datatype[DT_H5T_ALPHA_U8];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_U16, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_U16, mkChar("H5T_ALPHA_U16"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_U16] = h5_datatype[DT_H5T_ALPHA_U16];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_U32, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_U32, mkChar("H5T_ALPHA_U32"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_U32] = h5_datatype[DT_H5T_ALPHA_U32];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_U64, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_U64, mkChar("H5T_ALPHA_U64"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_U64] = h5_datatype[DT_H5T_ALPHA_U64];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_B8, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_B8, mkChar("H5T_ALPHA_B8"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_B8] = h5_datatype[DT_H5T_ALPHA_B8];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_B16, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_B16, mkChar("H5T_ALPHA_B16"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_B16] = h5_datatype[DT_H5T_ALPHA_B16];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_B32, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_B32, mkChar("H5T_ALPHA_B32"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_B32] = h5_datatype[DT_H5T_ALPHA_B32];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_B64, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_B64, mkChar("H5T_ALPHA_B64"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_B64] = h5_datatype[DT_H5T_ALPHA_B64];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_F32, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_F32, mkChar("H5T_ALPHA_F32"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_F32] = h5_datatype[DT_H5T_ALPHA_F32];

  SET_STRING_ELT(R_categ, DT_H5T_ALPHA_F64, mkChar("ALPHA"));
  SET_STRING_ELT(R_name, DT_H5T_ALPHA_F64, mkChar("H5T_ALPHA_F64"));
  ((long long *) REAL(R_type))[DT_H5T_ALPHA_F64] = h5_datatype[DT_H5T_ALPHA_F64];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_I8, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_I8, mkChar("H5T_MIPS_I8"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_I8] = h5_datatype[DT_H5T_MIPS_I8];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_I16, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_I16, mkChar("H5T_MIPS_I16"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_I16] = h5_datatype[DT_H5T_MIPS_I16];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_I32, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_I32, mkChar("H5T_MIPS_I32"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_I32] = h5_datatype[DT_H5T_MIPS_I32];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_I64, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_I64, mkChar("H5T_MIPS_I64"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_I64] = h5_datatype[DT_H5T_MIPS_I64];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_U8, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_U8, mkChar("H5T_MIPS_U8"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_U8] = h5_datatype[DT_H5T_MIPS_U8];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_U16, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_U16, mkChar("H5T_MIPS_U16"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_U16] = h5_datatype[DT_H5T_MIPS_U16];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_U32, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_U32, mkChar("H5T_MIPS_U32"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_U32] = h5_datatype[DT_H5T_MIPS_U32];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_U64, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_U64, mkChar("H5T_MIPS_U64"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_U64] = h5_datatype[DT_H5T_MIPS_U64];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_B8, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_B8, mkChar("H5T_MIPS_B8"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_B8] = h5_datatype[DT_H5T_MIPS_B8];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_B16, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_B16, mkChar("H5T_MIPS_B16"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_B16] = h5_datatype[DT_H5T_MIPS_B16];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_B32, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_B32, mkChar("H5T_MIPS_B32"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_B32] = h5_datatype[DT_H5T_MIPS_B32];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_B64, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_B64, mkChar("H5T_MIPS_B64"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_B64] = h5_datatype[DT_H5T_MIPS_B64];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_F32, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_F32, mkChar("H5T_MIPS_F32"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_F32] = h5_datatype[DT_H5T_MIPS_F32];

  SET_STRING_ELT(R_categ, DT_H5T_MIPS_F64, mkChar("MIPS"));
  SET_STRING_ELT(R_name, DT_H5T_MIPS_F64, mkChar("H5T_MIPS_F64"));
  ((long long *) REAL(R_type))[DT_H5T_MIPS_F64] = h5_datatype[DT_H5T_MIPS_F64];

  SET_STRING_ELT(R_categ, DT_H5T_VAX_F32, mkChar("VAX"));
  SET_STRING_ELT(R_name, DT_H5T_VAX_F32, mkChar("H5T_VAX_F32"));
  ((long long *) REAL(R_type))[DT_H5T_VAX_F32] = h5_datatype[DT_H5T_VAX_F32];

  SET_STRING_ELT(R_categ, DT_H5T_VAX_F64, mkChar("VAX"));
  SET_STRING_ELT(R_name, DT_H5T_VAX_F64, mkChar("H5T_VAX_F64"));
  ((long long *) REAL(R_type))[DT_H5T_VAX_F64] = h5_datatype[DT_H5T_VAX_F64];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_CHAR, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_CHAR, mkChar("H5T_NATIVE_CHAR"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_CHAR] = h5_datatype[DT_H5T_NATIVE_CHAR];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_SCHAR, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_SCHAR, mkChar("H5T_NATIVE_SCHAR"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_SCHAR] = h5_datatype[DT_H5T_NATIVE_SCHAR];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UCHAR, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UCHAR, mkChar("H5T_NATIVE_UCHAR"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UCHAR] = h5_datatype[DT_H5T_NATIVE_UCHAR];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_SHORT, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_SHORT, mkChar("H5T_NATIVE_SHORT"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_SHORT] = h5_datatype[DT_H5T_NATIVE_SHORT];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_USHORT, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_USHORT, mkChar("H5T_NATIVE_USHORT"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_USHORT] = h5_datatype[DT_H5T_NATIVE_USHORT];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT, mkChar("H5T_NATIVE_INT"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT] = h5_datatype[DT_H5T_NATIVE_INT];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT, mkChar("H5T_NATIVE_UINT"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT] = h5_datatype[DT_H5T_NATIVE_UINT];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_LONG, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_LONG, mkChar("H5T_NATIVE_LONG"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_LONG] = h5_datatype[DT_H5T_NATIVE_LONG];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_ULONG, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_ULONG, mkChar("H5T_NATIVE_ULONG"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_ULONG] = h5_datatype[DT_H5T_NATIVE_ULONG];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_LLONG, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_LLONG, mkChar("H5T_NATIVE_LLONG"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_LLONG] = h5_datatype[DT_H5T_NATIVE_LLONG];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_ULLONG, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_ULLONG, mkChar("H5T_NATIVE_ULLONG"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_ULLONG] = h5_datatype[DT_H5T_NATIVE_ULLONG];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_FLOAT, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_FLOAT, mkChar("H5T_NATIVE_FLOAT"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_FLOAT] = h5_datatype[DT_H5T_NATIVE_FLOAT];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_DOUBLE, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_DOUBLE, mkChar("H5T_NATIVE_DOUBLE"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_DOUBLE] = h5_datatype[DT_H5T_NATIVE_DOUBLE];

#if H5_SIZEOF_LONG_DOUBLE !=0
  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_LDOUBLE, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_LDOUBLE, mkChar("H5T_NATIVE_LDOUBLE"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_LDOUBLE] = h5_datatype[DT_H5T_NATIVE_LDOUBLE];
#endif

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_B8, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_B8, mkChar("H5T_NATIVE_B8"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_B8] = h5_datatype[DT_H5T_NATIVE_B8];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_B16, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_B16, mkChar("H5T_NATIVE_B16"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_B16] = h5_datatype[DT_H5T_NATIVE_B16];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_B32, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_B32, mkChar("H5T_NATIVE_B32"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_B32] = h5_datatype[DT_H5T_NATIVE_B32];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_B64, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_B64, mkChar("H5T_NATIVE_B64"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_B64] = h5_datatype[DT_H5T_NATIVE_B64];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_OPAQUE, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_OPAQUE, mkChar("H5T_NATIVE_OPAQUE"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_OPAQUE] = h5_datatype[DT_H5T_NATIVE_OPAQUE];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_HADDR, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_HADDR, mkChar("H5T_NATIVE_HADDR"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_HADDR] = h5_datatype[DT_H5T_NATIVE_HADDR];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_HSIZE, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_HSIZE, mkChar("H5T_NATIVE_HSIZE"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_HSIZE] = h5_datatype[DT_H5T_NATIVE_HSIZE];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_HSSIZE, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_HSSIZE, mkChar("H5T_NATIVE_HSSIZE"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_HSSIZE] = h5_datatype[DT_H5T_NATIVE_HSSIZE];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_HERR, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_HERR, mkChar("H5T_NATIVE_HERR"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_HERR] = h5_datatype[DT_H5T_NATIVE_HERR];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_HBOOL, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_HBOOL, mkChar("H5T_NATIVE_HBOOL"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_HBOOL] = h5_datatype[DT_H5T_NATIVE_HBOOL];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT8, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT8, mkChar("H5T_NATIVE_INT8"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT8] = h5_datatype[DT_H5T_NATIVE_INT8];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT8, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT8, mkChar("H5T_NATIVE_UINT8"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT8] = h5_datatype[DT_H5T_NATIVE_UINT8];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT_LEAST8, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT_LEAST8, mkChar("H5T_NATIVE_INT_LEAST8"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT_LEAST8] = h5_datatype[DT_H5T_NATIVE_INT_LEAST8];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT_LEAST8, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT_LEAST8, mkChar("H5T_NATIVE_UINT_LEAST8"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT_LEAST8] = h5_datatype[DT_H5T_NATIVE_UINT_LEAST8];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT_FAST8, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT_FAST8, mkChar("H5T_NATIVE_INT_FAST8"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT_FAST8] = h5_datatype[DT_H5T_NATIVE_INT_FAST8];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT_FAST8, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT_FAST8, mkChar("H5T_NATIVE_UINT_FAST8"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT_FAST8] = h5_datatype[DT_H5T_NATIVE_UINT_FAST8];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT16, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT16, mkChar("H5T_NATIVE_INT16"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT16] = h5_datatype[DT_H5T_NATIVE_INT16];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT16, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT16, mkChar("H5T_NATIVE_UINT16"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT16] = h5_datatype[DT_H5T_NATIVE_UINT16];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT_LEAST16, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT_LEAST16, mkChar("H5T_NATIVE_INT_LEAST16"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT_LEAST16] = h5_datatype[DT_H5T_NATIVE_INT_LEAST16];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT_LEAST16, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT_LEAST16, mkChar("H5T_NATIVE_UINT_LEAST16"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT_LEAST16] = h5_datatype[DT_H5T_NATIVE_UINT_LEAST16];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT_FAST16, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT_FAST16, mkChar("H5T_NATIVE_INT_FAST16"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT_FAST16] = h5_datatype[DT_H5T_NATIVE_INT_FAST16];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT_FAST16, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT_FAST16, mkChar("H5T_NATIVE_UINT_FAST16"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT_FAST16] = h5_datatype[DT_H5T_NATIVE_UINT_FAST16];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT32, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT32, mkChar("H5T_NATIVE_INT32"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT32] = h5_datatype[DT_H5T_NATIVE_INT32];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT32, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT32, mkChar("H5T_NATIVE_UINT32"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT32] = h5_datatype[DT_H5T_NATIVE_UINT32];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT_LEAST32, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT_LEAST32, mkChar("H5T_NATIVE_INT_LEAST32"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT_LEAST32] = h5_datatype[DT_H5T_NATIVE_INT_LEAST32];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT_LEAST32, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT_LEAST32, mkChar("H5T_NATIVE_UINT_LEAST32"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT_LEAST32] = h5_datatype[DT_H5T_NATIVE_UINT_LEAST32];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT_FAST32, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT_FAST32, mkChar("H5T_NATIVE_INT_FAST32"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT_FAST32] = h5_datatype[DT_H5T_NATIVE_INT_FAST32];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT_FAST32, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT_FAST32, mkChar("H5T_NATIVE_UINT_FAST32"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT_FAST32] = h5_datatype[DT_H5T_NATIVE_UINT_FAST32];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT64, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT64, mkChar("H5T_NATIVE_INT64"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT64] = h5_datatype[DT_H5T_NATIVE_INT64];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT64, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT64, mkChar("H5T_NATIVE_UINT64"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT64] = h5_datatype[DT_H5T_NATIVE_UINT64];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT_LEAST64, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT_LEAST64, mkChar("H5T_NATIVE_INT_LEAST64"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT_LEAST64] = h5_datatype[DT_H5T_NATIVE_INT_LEAST64];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT_LEAST64, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT_LEAST64, mkChar("H5T_NATIVE_UINT_LEAST64"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT_LEAST64] = h5_datatype[DT_H5T_NATIVE_UINT_LEAST64];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_INT_FAST64, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_INT_FAST64, mkChar("H5T_NATIVE_INT_FAST64"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_INT_FAST64] = h5_datatype[DT_H5T_NATIVE_INT_FAST64];

  SET_STRING_ELT(R_categ, DT_H5T_NATIVE_UINT_FAST64, mkChar("NATIVE"));
  SET_STRING_ELT(R_name, DT_H5T_NATIVE_UINT_FAST64, mkChar("H5T_NATIVE_UINT_FAST64"));
  ((long long *) REAL(R_type))[DT_H5T_NATIVE_UINT_FAST64] = h5_datatype[DT_H5T_NATIVE_UINT_FAST64];

  SET_STRING_ELT(R_categ, DT_H5E_major_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_H5E_major_t, mkChar("H5E_major_t"));
  ((long long *) REAL(R_type))[DT_H5E_major_t] = h5_datatype[DT_H5E_major_t];

  SET_STRING_ELT(R_categ, DT_H5E_minor_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_H5E_minor_t, mkChar("H5E_minor_t"));
  ((long long *) REAL(R_type))[DT_H5E_minor_t] = h5_datatype[DT_H5E_minor_t];

  SET_STRING_ELT(R_categ, DT_H5FD_mem_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_H5FD_mem_t, mkChar("H5FD_mem_t"));
  ((long long *) REAL(R_type))[DT_H5FD_mem_t] = h5_datatype[DT_H5FD_mem_t];

  SET_STRING_ELT(R_categ, DT_H5G_link_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_H5G_link_t, mkChar("H5G_link_t"));
  ((long long *) REAL(R_type))[DT_H5G_link_t] = h5_datatype[DT_H5G_link_t];

  SET_STRING_ELT(R_categ, DT_H5O_msg_crt_idx_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_H5O_msg_crt_idx_t, mkChar("H5O_msg_crt_idx_t"));
  ((long long *) REAL(R_type))[DT_H5O_msg_crt_idx_t] = h5_datatype[DT_H5O_msg_crt_idx_t];

  SET_STRING_ELT(R_categ, DT_H5Z_filter_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_H5Z_filter_t, mkChar("H5Z_filter_t"));
  ((long long *) REAL(R_type))[DT_H5Z_filter_t] = h5_datatype[DT_H5Z_filter_t];

  SET_STRING_ELT(R_categ, DT_haddr_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_haddr_t, mkChar("haddr_t"));
  ((long long *) REAL(R_type))[DT_haddr_t] = h5_datatype[DT_haddr_t];

  SET_STRING_ELT(R_categ, DT_hbool_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_hbool_t, mkChar("hbool_t"));
  ((long long *) REAL(R_type))[DT_hbool_t] = h5_datatype[DT_hbool_t];

  SET_STRING_ELT(R_categ, DT_herr_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_herr_t, mkChar("herr_t"));
  ((long long *) REAL(R_type))[DT_herr_t] = h5_datatype[DT_herr_t];

  SET_STRING_ELT(R_categ, DT_hid_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_hid_t, mkChar("hid_t"));
  ((long long *) REAL(R_type))[DT_hid_t] = h5_datatype[DT_hid_t];

  SET_STRING_ELT(R_categ, DT_hsize_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_hsize_t, mkChar("hsize_t"));
  ((long long *) REAL(R_type))[DT_hsize_t] = h5_datatype[DT_hsize_t];

  SET_STRING_ELT(R_categ, DT_hssize_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_hssize_t, mkChar("hssize_t"));
  ((long long *) REAL(R_type))[DT_hssize_t] = h5_datatype[DT_hssize_t];

  SET_STRING_ELT(R_categ, DT_htri_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_htri_t, mkChar("htri_t"));
  ((long long *) REAL(R_type))[DT_htri_t] = h5_datatype[DT_htri_t];

  SET_STRING_ELT(R_categ, DT_int, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_int, mkChar("int"));
  ((long long *) REAL(R_type))[DT_int] = h5_datatype[DT_int];

  SET_STRING_ELT(R_categ, DT_int64_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_int64_t, mkChar("int64_t"));
  ((long long *) REAL(R_type))[DT_int64_t] = h5_datatype[DT_int64_t];

  SET_STRING_ELT(R_categ, DT_long, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_long, mkChar("long"));
  ((long long *) REAL(R_type))[DT_long] = h5_datatype[DT_long];

  SET_STRING_ELT(R_categ, DT_long_int, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_long_int, mkChar("long_int"));
  ((long long *) REAL(R_type))[DT_long_int] = h5_datatype[DT_long_int];

  SET_STRING_ELT(R_categ, DT_long_long, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_long_long, mkChar("long_long"));
  ((long long *) REAL(R_type))[DT_long_long] = h5_datatype[DT_long_long];

  SET_STRING_ELT(R_categ, DT_off_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_off_t, mkChar("off_t"));
  ((long long *) REAL(R_type))[DT_off_t] = h5_datatype[DT_off_t];

  SET_STRING_ELT(R_categ, DT_short, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_short, mkChar("short"));
  ((long long *) REAL(R_type))[DT_short] = h5_datatype[DT_short];

  SET_STRING_ELT(R_categ, DT_size_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_size_t, mkChar("size_t"));
  ((long long *) REAL(R_type))[DT_size_t] = h5_datatype[DT_size_t];

  SET_STRING_ELT(R_categ, DT_ssize_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_ssize_t, mkChar("ssize_t"));
  ((long long *) REAL(R_type))[DT_ssize_t] = h5_datatype[DT_ssize_t];

  SET_STRING_ELT(R_categ, DT_time_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_time_t, mkChar("time_t"));
  ((long long *) REAL(R_type))[DT_time_t] = h5_datatype[DT_time_t];

  SET_STRING_ELT(R_categ, DT_uint32_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_uint32_t, mkChar("uint32_t"));
  ((long long *) REAL(R_type))[DT_uint32_t] = h5_datatype[DT_uint32_t];

  SET_STRING_ELT(R_categ, DT_uint64_t, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_uint64_t, mkChar("uint64_t"));
  ((long long *) REAL(R_type))[DT_uint64_t] = h5_datatype[DT_uint64_t];

  SET_STRING_ELT(R_categ, DT_unsigned, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_unsigned, mkChar("unsigned"));
  ((long long *) REAL(R_type))[DT_unsigned] = h5_datatype[DT_unsigned];

  SET_STRING_ELT(R_categ, DT_unsigned_char, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_unsigned_char, mkChar("unsigned_char"));
  ((long long *) REAL(R_type))[DT_unsigned_char] = h5_datatype[DT_unsigned_char];

  SET_STRING_ELT(R_categ, DT_unsigned_int, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_unsigned_int, mkChar("unsigned_int"));
  ((long long *) REAL(R_type))[DT_unsigned_int] = h5_datatype[DT_unsigned_int];

  SET_STRING_ELT(R_categ, DT_unsigned_long, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_unsigned_long, mkChar("unsigned_long"));
  ((long long *) REAL(R_type))[DT_unsigned_long] = h5_datatype[DT_unsigned_long];

  SET_STRING_ELT(R_categ, DT_unsigned_long_long, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_unsigned_long_long, mkChar("unsigned_long_long"));
  ((long long *) REAL(R_type))[DT_unsigned_long_long] = h5_datatype[DT_unsigned_long_long];

  SET_STRING_ELT(R_categ, DT_unsigned_short, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_unsigned_short, mkChar("unsigned_short"));
  ((long long *) REAL(R_type))[DT_unsigned_short] = h5_datatype[DT_unsigned_short];

  SET_STRING_ELT(R_categ, DT_char, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_char, mkChar("char"));
  ((long long *) REAL(R_type))[DT_char] = h5_datatype[DT_char];

  SET_STRING_ELT(R_categ, DT_double, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_double, mkChar("double"));
  ((long long *) REAL(R_type))[DT_double] = h5_datatype[DT_double];

  SET_STRING_ELT(R_categ, DT_float, mkChar("C_API_types"));
  SET_STRING_ELT(R_name, DT_float, mkChar("float"));
  ((long long *) REAL(R_type))[DT_float] = h5_datatype[DT_float];

  SET_STRING_ELT(R_categ, DT_H5_index_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5_index_t, mkChar("H5_index_t"));
  ((long long *) REAL(R_type))[DT_H5_index_t] = h5_datatype[DT_H5_index_t];

  SET_STRING_ELT(R_categ, DT_H5_iter_order_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5_iter_order_t, mkChar("H5_iter_order_t"));
  ((long long *) REAL(R_type))[DT_H5_iter_order_t] = h5_datatype[DT_H5_iter_order_t];

  SET_STRING_ELT(R_categ, DT_H5C_cache_decr_mode, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5C_cache_decr_mode, mkChar("H5C_cache_decr_mode"));
  ((long long *) REAL(R_type))[DT_H5C_cache_decr_mode] = h5_datatype[DT_H5C_cache_decr_mode];

  SET_STRING_ELT(R_categ, DT_H5C_cache_flash_incr_mode, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5C_cache_flash_incr_mode, mkChar("H5C_cache_flash_incr_mode"));
  ((long long *) REAL(R_type))[DT_H5C_cache_flash_incr_mode] = h5_datatype[DT_H5C_cache_flash_incr_mode];

  SET_STRING_ELT(R_categ, DT_H5C_cache_incr_mode, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5C_cache_incr_mode, mkChar("H5C_cache_incr_mode"));
  ((long long *) REAL(R_type))[DT_H5C_cache_incr_mode] = h5_datatype[DT_H5C_cache_incr_mode];

  SET_STRING_ELT(R_categ, DT_H5D_alloc_time_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5D_alloc_time_t, mkChar("H5D_alloc_time_t"));
  ((long long *) REAL(R_type))[DT_H5D_alloc_time_t] = h5_datatype[DT_H5D_alloc_time_t];

  SET_STRING_ELT(R_categ, DT_H5D_chunk_index_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5D_chunk_index_t, mkChar("H5D_chunk_index_t"));
  ((long long *) REAL(R_type))[DT_H5D_chunk_index_t] = h5_datatype[DT_H5D_chunk_index_t];

  SET_STRING_ELT(R_categ, DT_H5D_fill_time_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5D_fill_time_t, mkChar("H5D_fill_time_t"));
  ((long long *) REAL(R_type))[DT_H5D_fill_time_t] = h5_datatype[DT_H5D_fill_time_t];

  SET_STRING_ELT(R_categ, DT_H5D_fill_value_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5D_fill_value_t, mkChar("H5D_fill_value_t"));
  ((long long *) REAL(R_type))[DT_H5D_fill_value_t] = h5_datatype[DT_H5D_fill_value_t];

  SET_STRING_ELT(R_categ, DT_H5D_layout_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5D_layout_t, mkChar("H5D_layout_t"));
  ((long long *) REAL(R_type))[DT_H5D_layout_t] = h5_datatype[DT_H5D_layout_t];

  SET_STRING_ELT(R_categ, DT_H5D_mpio_actual_chunk_opt_mode_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5D_mpio_actual_chunk_opt_mode_t, mkChar("H5D_mpio_actual_chunk_opt_mode_t"));
  ((long long *) REAL(R_type))[DT_H5D_mpio_actual_chunk_opt_mode_t] = h5_datatype[DT_H5D_mpio_actual_chunk_opt_mode_t];

  SET_STRING_ELT(R_categ, DT_H5D_mpio_actual_io_mode_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5D_mpio_actual_io_mode_t, mkChar("H5D_mpio_actual_io_mode_t"));
  ((long long *) REAL(R_type))[DT_H5D_mpio_actual_io_mode_t] = h5_datatype[DT_H5D_mpio_actual_io_mode_t];

  SET_STRING_ELT(R_categ, DT_H5D_mpio_no_collective_cause_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5D_mpio_no_collective_cause_t, mkChar("H5D_mpio_no_collective_cause_t"));
  ((long long *) REAL(R_type))[DT_H5D_mpio_no_collective_cause_t] = h5_datatype[DT_H5D_mpio_no_collective_cause_t];

  SET_STRING_ELT(R_categ, DT_H5D_space_status_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5D_space_status_t, mkChar("H5D_space_status_t"));
  ((long long *) REAL(R_type))[DT_H5D_space_status_t] = h5_datatype[DT_H5D_space_status_t];

  SET_STRING_ELT(R_categ, DT_H5D_vds_view_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5D_vds_view_t, mkChar("H5D_vds_view_t"));
  ((long long *) REAL(R_type))[DT_H5D_vds_view_t] = h5_datatype[DT_H5D_vds_view_t];

  SET_STRING_ELT(R_categ, DT_H5E_direction_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5E_direction_t, mkChar("H5E_direction_t"));
  ((long long *) REAL(R_type))[DT_H5E_direction_t] = h5_datatype[DT_H5E_direction_t];

  SET_STRING_ELT(R_categ, DT_H5E_type_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5E_type_t, mkChar("H5E_type_t"));
  ((long long *) REAL(R_type))[DT_H5E_type_t] = h5_datatype[DT_H5E_type_t];

  SET_STRING_ELT(R_categ, DT_H5F_close_degree_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5F_close_degree_t, mkChar("H5F_close_degree_t"));
  ((long long *) REAL(R_type))[DT_H5F_close_degree_t] = h5_datatype[DT_H5F_close_degree_t];

  SET_STRING_ELT(R_categ, DT_H5F_file_space_type_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5F_file_space_type_t, mkChar("H5F_file_space_type_t"));
  ((long long *) REAL(R_type))[DT_H5F_file_space_type_t] = h5_datatype[DT_H5F_file_space_type_t];

  SET_STRING_ELT(R_categ, DT_H5F_fspace_strategy_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5F_fspace_strategy_t, mkChar("H5F_fspace_strategy_t"));
  ((long long *) REAL(R_type))[DT_H5F_fspace_strategy_t] = h5_datatype[DT_H5F_fspace_strategy_t];

  SET_STRING_ELT(R_categ, DT_H5F_libver_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5F_libver_t, mkChar("H5F_libver_t"));
  ((long long *) REAL(R_type))[DT_H5F_libver_t] = h5_datatype[DT_H5F_libver_t];

  SET_STRING_ELT(R_categ, DT_H5F_mem_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5F_mem_t, mkChar("H5F_mem_t"));
  ((long long *) REAL(R_type))[DT_H5F_mem_t] = h5_datatype[DT_H5F_mem_t];

  SET_STRING_ELT(R_categ, DT_H5F_scope_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5F_scope_t, mkChar("H5F_scope_t"));
  ((long long *) REAL(R_type))[DT_H5F_scope_t] = h5_datatype[DT_H5F_scope_t];

  SET_STRING_ELT(R_categ, DT_H5FD_file_image_op_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5FD_file_image_op_t, mkChar("H5FD_file_image_op_t"));
  ((long long *) REAL(R_type))[DT_H5FD_file_image_op_t] = h5_datatype[DT_H5FD_file_image_op_t];

  SET_STRING_ELT(R_categ, DT_H5G_obj_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5G_obj_t, mkChar("H5G_obj_t"));
  ((long long *) REAL(R_type))[DT_H5G_obj_t] = h5_datatype[DT_H5G_obj_t];

  SET_STRING_ELT(R_categ, DT_H5G_storage_type_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5G_storage_type_t, mkChar("H5G_storage_type_t"));
  ((long long *) REAL(R_type))[DT_H5G_storage_type_t] = h5_datatype[DT_H5G_storage_type_t];

  SET_STRING_ELT(R_categ, DT_H5I_type_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5I_type_t, mkChar("H5I_type_t"));
  ((long long *) REAL(R_type))[DT_H5I_type_t] = h5_datatype[DT_H5I_type_t];

  SET_STRING_ELT(R_categ, DT_H5L_type_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5L_type_t, mkChar("H5L_type_t"));
  ((long long *) REAL(R_type))[DT_H5L_type_t] = h5_datatype[DT_H5L_type_t];

  SET_STRING_ELT(R_categ, DT_H5LT_lang_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5LT_lang_t, mkChar("H5LT_lang_t"));
  ((long long *) REAL(R_type))[DT_H5LT_lang_t] = h5_datatype[DT_H5LT_lang_t];

  SET_STRING_ELT(R_categ, DT_H5O_mcdt_search_ret_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5O_mcdt_search_ret_t, mkChar("H5O_mcdt_search_ret_t"));
  ((long long *) REAL(R_type))[DT_H5O_mcdt_search_ret_t] = h5_datatype[DT_H5O_mcdt_search_ret_t];

  SET_STRING_ELT(R_categ, DT_H5O_type_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5O_type_t, mkChar("H5O_type_t"));
  ((long long *) REAL(R_type))[DT_H5O_type_t] = h5_datatype[DT_H5O_type_t];

  SET_STRING_ELT(R_categ, DT_H5PL_type_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5PL_type_t, mkChar("H5PL_type_t"));
  ((long long *) REAL(R_type))[DT_H5PL_type_t] = h5_datatype[DT_H5PL_type_t];

  SET_STRING_ELT(R_categ, DT_H5R_type_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5R_type_t, mkChar("H5R_type_t"));
  ((long long *) REAL(R_type))[DT_H5R_type_t] = h5_datatype[DT_H5R_type_t];

  SET_STRING_ELT(R_categ, DT_H5S_class_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5S_class_t, mkChar("H5S_class_t"));
  ((long long *) REAL(R_type))[DT_H5S_class_t] = h5_datatype[DT_H5S_class_t];

  SET_STRING_ELT(R_categ, DT_H5S_sel_type, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5S_sel_type, mkChar("H5S_sel_type"));
  ((long long *) REAL(R_type))[DT_H5S_sel_type] = h5_datatype[DT_H5S_sel_type];

  SET_STRING_ELT(R_categ, DT_H5S_seloper_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5S_seloper_t, mkChar("H5S_seloper_t"));
  ((long long *) REAL(R_type))[DT_H5S_seloper_t] = h5_datatype[DT_H5S_seloper_t];

  SET_STRING_ELT(R_categ, DT_H5T_bkg_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_bkg_t, mkChar("H5T_bkg_t"));
  ((long long *) REAL(R_type))[DT_H5T_bkg_t] = h5_datatype[DT_H5T_bkg_t];

  SET_STRING_ELT(R_categ, DT_H5T_class_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_class_t, mkChar("H5T_class_t"));
  ((long long *) REAL(R_type))[DT_H5T_class_t] = h5_datatype[DT_H5T_class_t];

  SET_STRING_ELT(R_categ, DT_H5T_cmd_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_cmd_t, mkChar("H5T_cmd_t"));
  ((long long *) REAL(R_type))[DT_H5T_cmd_t] = h5_datatype[DT_H5T_cmd_t];

  SET_STRING_ELT(R_categ, DT_H5T_conv_except_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_conv_except_t, mkChar("H5T_conv_except_t"));
  ((long long *) REAL(R_type))[DT_H5T_conv_except_t] = h5_datatype[DT_H5T_conv_except_t];

  SET_STRING_ELT(R_categ, DT_H5T_conv_ret_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_conv_ret_t, mkChar("H5T_conv_ret_t"));
  ((long long *) REAL(R_type))[DT_H5T_conv_ret_t] = h5_datatype[DT_H5T_conv_ret_t];

  SET_STRING_ELT(R_categ, DT_H5T_cset_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_cset_t, mkChar("H5T_cset_t"));
  ((long long *) REAL(R_type))[DT_H5T_cset_t] = h5_datatype[DT_H5T_cset_t];

  SET_STRING_ELT(R_categ, DT_H5T_direction_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_direction_t, mkChar("H5T_direction_t"));
  ((long long *) REAL(R_type))[DT_H5T_direction_t] = h5_datatype[DT_H5T_direction_t];

  SET_STRING_ELT(R_categ, DT_H5T_norm_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_norm_t, mkChar("H5T_norm_t"));
  ((long long *) REAL(R_type))[DT_H5T_norm_t] = h5_datatype[DT_H5T_norm_t];

  SET_STRING_ELT(R_categ, DT_H5T_order_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_order_t, mkChar("H5T_order_t"));
  ((long long *) REAL(R_type))[DT_H5T_order_t] = h5_datatype[DT_H5T_order_t];

  SET_STRING_ELT(R_categ, DT_H5T_pad_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_pad_t, mkChar("H5T_pad_t"));
  ((long long *) REAL(R_type))[DT_H5T_pad_t] = h5_datatype[DT_H5T_pad_t];

  SET_STRING_ELT(R_categ, DT_H5T_pers_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_pers_t, mkChar("H5T_pers_t"));
  ((long long *) REAL(R_type))[DT_H5T_pers_t] = h5_datatype[DT_H5T_pers_t];

  SET_STRING_ELT(R_categ, DT_H5T_sign_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_sign_t, mkChar("H5T_sign_t"));
  ((long long *) REAL(R_type))[DT_H5T_sign_t] = h5_datatype[DT_H5T_sign_t];

  SET_STRING_ELT(R_categ, DT_H5T_str_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5T_str_t, mkChar("H5T_str_t"));
  ((long long *) REAL(R_type))[DT_H5T_str_t] = h5_datatype[DT_H5T_str_t];

  SET_STRING_ELT(R_categ, DT_H5Z_cb_return_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5Z_cb_return_t, mkChar("H5Z_cb_return_t"));
  ((long long *) REAL(R_type))[DT_H5Z_cb_return_t] = h5_datatype[DT_H5Z_cb_return_t];

  SET_STRING_ELT(R_categ, DT_H5Z_EDC_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5Z_EDC_t, mkChar("H5Z_EDC_t"));
  ((long long *) REAL(R_type))[DT_H5Z_EDC_t] = h5_datatype[DT_H5Z_EDC_t];

  SET_STRING_ELT(R_categ, DT_H5Z_SO_scale_type_t, mkChar("enum"));
  SET_STRING_ELT(R_name, DT_H5Z_SO_scale_type_t, mkChar("H5Z_SO_scale_type_t"));
  ((long long *) REAL(R_type))[DT_H5Z_SO_scale_type_t] = h5_datatype[DT_H5Z_SO_scale_type_t];

  SET_STRING_ELT(R_categ, DT_H5L_info_helper_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5L_info_helper_t, mkChar("H5L_info_helper_t"));
  ((long long *) REAL(R_type))[DT_H5L_info_helper_t] = h5_datatype[DT_H5L_info_helper_t];

  SET_STRING_ELT(R_categ, DT_H5_ih_info_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5_ih_info_t, mkChar("H5_ih_info_t"));
  ((long long *) REAL(R_type))[DT_H5_ih_info_t] = h5_datatype[DT_H5_ih_info_t];

  SET_STRING_ELT(R_categ, DT_H5A_info_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5A_info_t, mkChar("H5A_info_t"));
  ((long long *) REAL(R_type))[DT_H5A_info_t] = h5_datatype[DT_H5A_info_t];

  SET_STRING_ELT(R_categ, DT_H5AC_cache_config_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5AC_cache_config_t, mkChar("H5AC_cache_config_t"));
  ((long long *) REAL(R_type))[DT_H5AC_cache_config_t] = h5_datatype[DT_H5AC_cache_config_t];

  SET_STRING_ELT(R_categ, DT_H5AC_cache_image_config_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5AC_cache_image_config_t, mkChar("H5AC_cache_image_config_t"));
  ((long long *) REAL(R_type))[DT_H5AC_cache_image_config_t] = h5_datatype[DT_H5AC_cache_image_config_t];

  SET_STRING_ELT(R_categ, DT_H5D_info_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5D_info_t, mkChar("H5D_info_t"));
  ((long long *) REAL(R_type))[DT_H5D_info_t] = h5_datatype[DT_H5D_info_t];

  SET_STRING_ELT(R_categ, DT_H5E_error1_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5E_error1_t, mkChar("H5E_error1_t"));
  ((long long *) REAL(R_type))[DT_H5E_error1_t] = h5_datatype[DT_H5E_error1_t];

  SET_STRING_ELT(R_categ, DT_H5E_error2_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5E_error2_t, mkChar("H5E_error2_t"));
  ((long long *) REAL(R_type))[DT_H5E_error2_t] = h5_datatype[DT_H5E_error2_t];

  SET_STRING_ELT(R_categ, DT_H5F_info1_helper_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5F_info1_helper_t, mkChar("H5F_info1_helper_t"));
  ((long long *) REAL(R_type))[DT_H5F_info1_helper_t] = h5_datatype[DT_H5F_info1_helper_t];

  SET_STRING_ELT(R_categ, DT_H5F_info1_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5F_info1_t, mkChar("H5F_info1_t"));
  ((long long *) REAL(R_type))[DT_H5F_info1_t] = h5_datatype[DT_H5F_info1_t];

  SET_STRING_ELT(R_categ, DT_H5F_info2_free_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5F_info2_free_t, mkChar("H5F_info2_free_t"));
  ((long long *) REAL(R_type))[DT_H5F_info2_free_t] = h5_datatype[DT_H5F_info2_free_t];

  SET_STRING_ELT(R_categ, DT_H5F_info2_sohm_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5F_info2_sohm_t, mkChar("H5F_info2_sohm_t"));
  ((long long *) REAL(R_type))[DT_H5F_info2_sohm_t] = h5_datatype[DT_H5F_info2_sohm_t];

  SET_STRING_ELT(R_categ, DT_H5F_info2_super_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5F_info2_super_t, mkChar("H5F_info2_super_t"));
  ((long long *) REAL(R_type))[DT_H5F_info2_super_t] = h5_datatype[DT_H5F_info2_super_t];

  SET_STRING_ELT(R_categ, DT_H5F_info2_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5F_info2_t, mkChar("H5F_info2_t"));
  ((long long *) REAL(R_type))[DT_H5F_info2_t] = h5_datatype[DT_H5F_info2_t];

  SET_STRING_ELT(R_categ, DT_H5F_retry_info_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5F_retry_info_t, mkChar("H5F_retry_info_t"));
  ((long long *) REAL(R_type))[DT_H5F_retry_info_t] = h5_datatype[DT_H5F_retry_info_t];

  SET_STRING_ELT(R_categ, DT_H5F_sect_info_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5F_sect_info_t, mkChar("H5F_sect_info_t"));
  ((long long *) REAL(R_type))[DT_H5F_sect_info_t] = h5_datatype[DT_H5F_sect_info_t];

  SET_STRING_ELT(R_categ, DT_H5G_info_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5G_info_t, mkChar("H5G_info_t"));
  ((long long *) REAL(R_type))[DT_H5G_info_t] = h5_datatype[DT_H5G_info_t];

  SET_STRING_ELT(R_categ, DT_H5L_info_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5L_info_t, mkChar("H5L_info_t"));
  ((long long *) REAL(R_type))[DT_H5L_info_t] = h5_datatype[DT_H5L_info_t];

  SET_STRING_ELT(R_categ, DT_H5ls_info_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5ls_info_t, mkChar("H5ls_info_t"));
  ((long long *) REAL(R_type))[DT_H5ls_info_t] = h5_datatype[DT_H5ls_info_t];

  SET_STRING_ELT(R_categ, DT_H5O_hdr_info_helper_msg_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5O_hdr_info_helper_msg_t, mkChar("H5O_hdr_info_helper_msg_t"));
  ((long long *) REAL(R_type))[DT_H5O_hdr_info_helper_msg_t] = h5_datatype[DT_H5O_hdr_info_helper_msg_t];

  SET_STRING_ELT(R_categ, DT_H5O_hdr_info_helper_space_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5O_hdr_info_helper_space_t, mkChar("H5O_hdr_info_helper_space_t"));
  ((long long *) REAL(R_type))[DT_H5O_hdr_info_helper_space_t] = h5_datatype[DT_H5O_hdr_info_helper_space_t];

  SET_STRING_ELT(R_categ, DT_H5O_hdr_info_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5O_hdr_info_t, mkChar("H5O_hdr_info_t"));
  ((long long *) REAL(R_type))[DT_H5O_hdr_info_t] = h5_datatype[DT_H5O_hdr_info_t];

  SET_STRING_ELT(R_categ, DT_H5O_info_helper_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5O_info_helper_t, mkChar("H5O_info_helper_t"));
  ((long long *) REAL(R_type))[DT_H5O_info_helper_t] = h5_datatype[DT_H5O_info_helper_t];

  SET_STRING_ELT(R_categ, DT_H5O_info_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5O_info_t, mkChar("H5O_info_t"));
  ((long long *) REAL(R_type))[DT_H5O_info_t] = h5_datatype[DT_H5O_info_t];

  SET_STRING_ELT(R_categ, DT_H5O_stat_t, mkChar("struct"));
  SET_STRING_ELT(R_name, DT_H5O_stat_t, mkChar("H5O_stat_t"));
  ((long long *) REAL(R_type))[DT_H5O_stat_t] = h5_datatype[DT_H5O_stat_t];
  UNPROTECT(4);
  return(df);
}


/*************************************************************************
 *
 * Enums
 *
 *************************************************************************/

/* typedef enum H5_index_t { H5_INDEX_UNKNOWN = -1, H5_INDEX_NAME, H5_INDEX_CRT_ORDER, H5_INDEX_N } H5_index_t; */
hid_t create_DT_H5_index_t(void) {
  enum H5_index_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5_index_t), issigned(enum H5_index_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5_INDEX_UNKNOWN;
  H5Tenum_insert(dtype_id, "H5_INDEX_UNKNOWN", &myenum);
  myenum = H5_INDEX_NAME;
  H5Tenum_insert(dtype_id, "H5_INDEX_NAME", &myenum);
  myenum = H5_INDEX_CRT_ORDER;
  H5Tenum_insert(dtype_id, "H5_INDEX_CRT_ORDER", &myenum);
  myenum = H5_INDEX_N;
  H5Tenum_insert(dtype_id, "H5_INDEX_N", &myenum);
  return(dtype_id);
}

/* typedef enum { H5_ITER_UNKNOWN = -1, H5_ITER_INC, H5_ITER_DEC, H5_ITER_NATIVE, H5_ITER_N } H5_iter_order_t; */
hid_t create_DT_H5_iter_order_t(void) {
  H5_iter_order_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(H5_iter_order_t), issigned(H5_iter_order_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5_ITER_UNKNOWN;
  H5Tenum_insert(dtype_id, "H5_ITER_UNKNOWN", &myenum);
  myenum = H5_ITER_INC;
  H5Tenum_insert(dtype_id, "H5_ITER_INC", &myenum);
  myenum = H5_ITER_DEC;
  H5Tenum_insert(dtype_id, "H5_ITER_DEC", &myenum);
  myenum = H5_ITER_NATIVE;
  H5Tenum_insert(dtype_id, "H5_ITER_NATIVE", &myenum);
  myenum = H5_ITER_N;
  H5Tenum_insert(dtype_id, "H5_ITER_N", &myenum);
  return(dtype_id);
}

/* typedef enum H5C_cache_decr_mode{ H5C_decr__off, H5C_decr__threshold, H5C_decr__age_out, H5C_decr__age_out_with_threshold} H5C_cache_decr_mode; */
hid_t create_DT_H5C_cache_decr_mode(void) {
  enum H5C_cache_decr_mode myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5C_cache_decr_mode), issigned(enum H5C_cache_decr_mode));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5C_decr__off;
  H5Tenum_insert(dtype_id, "H5C_decr__off", &myenum);
  myenum = H5C_decr__threshold;
  H5Tenum_insert(dtype_id, "H5C_decr__threshold", &myenum);
  myenum = H5C_decr__age_out;
  H5Tenum_insert(dtype_id, "H5C_decr__age_out", &myenum);
  myenum = H5C_decr__age_out_with_threshold;
  H5Tenum_insert(dtype_id, "H5C_decr__age_out_with_threshold", &myenum);
  return(dtype_id);
}

/* typedef enum H5C_cache_flash_incr_mode{ H5C_flash_incr__off, H5C_flash_incr__add_space} H5C_cache_flash_incr_mode; */
hid_t create_DT_H5C_cache_flash_incr_mode(void) {
  enum H5C_cache_flash_incr_mode myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5C_cache_flash_incr_mode), issigned(enum H5C_cache_flash_incr_mode));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5C_flash_incr__off;
  H5Tenum_insert(dtype_id, "H5C_flash_incr__off", &myenum);
  myenum = H5C_flash_incr__add_space;
  H5Tenum_insert(dtype_id, "H5C_flash_incr__add_space", &myenum);
  return(dtype_id);
}

/* typedef enum H5C_cache_incr_mode{ H5C_incr__off, H5C_incr__threshold} H5C_cache_incr_mode; */
hid_t create_DT_H5C_cache_incr_mode(void) {
  enum H5C_cache_incr_mode myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5C_cache_incr_mode), issigned(enum H5C_cache_incr_mode));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5C_incr__off;
  H5Tenum_insert(dtype_id, "H5C_incr__off", &myenum);
  myenum = H5C_incr__threshold;
  H5Tenum_insert(dtype_id, "H5C_incr__threshold", &myenum);
  return(dtype_id);
}

/* typedef enum H5D_alloc_time_t { H5D_ALLOC_TIME_ERROR = -1, H5D_ALLOC_TIME_DEFAULT = 0, H5D_ALLOC_TIME_EARLY = 1, H5D_ALLOC_TIME_LATE = 2, H5D_ALLOC_TIME_INCR = 3} H5D_alloc_time_t; */
hid_t create_DT_H5D_alloc_time_t(void) {
  enum H5D_alloc_time_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5D_alloc_time_t), issigned(enum H5D_alloc_time_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5D_ALLOC_TIME_ERROR;
  H5Tenum_insert(dtype_id, "H5D_ALLOC_TIME_ERROR", &myenum);
  myenum = H5D_ALLOC_TIME_DEFAULT;
  H5Tenum_insert(dtype_id, "H5D_ALLOC_TIME_DEFAULT", &myenum);
  myenum = H5D_ALLOC_TIME_EARLY;
  H5Tenum_insert(dtype_id, "H5D_ALLOC_TIME_EARLY", &myenum);
  myenum = H5D_ALLOC_TIME_LATE;
  H5Tenum_insert(dtype_id, "H5D_ALLOC_TIME_LATE", &myenum);
  myenum = H5D_ALLOC_TIME_INCR;
  H5Tenum_insert(dtype_id, "H5D_ALLOC_TIME_INCR", &myenum);
  return(dtype_id);
}

/* typedef enum H5D_chunk_index_t { H5D_CHUNK_IDX_BTREE = 0, H5D_CHUNK_IDX_SINGLE = 1, H5D_CHUNK_IDX_NONE = 2, H5D_CHUNK_IDX_FARRAY = 3, H5D_CHUNK_IDX_EARRAY = 4, H5D_CHUNK_IDX_BT2 = 5, H5D_CHUNK_IDX_NTYPES } H5D_chunk_index_t; */
hid_t create_DT_H5D_chunk_index_t(void) {
  enum H5D_chunk_index_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5D_chunk_index_t), issigned(enum H5D_chunk_index_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5D_CHUNK_IDX_BTREE;
  H5Tenum_insert(dtype_id, "H5D_CHUNK_IDX_BTREE", &myenum);
  myenum = H5D_CHUNK_IDX_SINGLE;
  H5Tenum_insert(dtype_id, "H5D_CHUNK_IDX_SINGLE", &myenum);
  myenum = H5D_CHUNK_IDX_NONE;
  H5Tenum_insert(dtype_id, "H5D_CHUNK_IDX_NONE", &myenum);
  myenum = H5D_CHUNK_IDX_FARRAY;
  H5Tenum_insert(dtype_id, "H5D_CHUNK_IDX_FARRAY", &myenum);
  myenum = H5D_CHUNK_IDX_EARRAY;
  H5Tenum_insert(dtype_id, "H5D_CHUNK_IDX_EARRAY", &myenum);
  myenum = H5D_CHUNK_IDX_BT2;
  H5Tenum_insert(dtype_id, "H5D_CHUNK_IDX_BT2", &myenum);
  myenum = H5D_CHUNK_IDX_NTYPES;
  H5Tenum_insert(dtype_id, "H5D_CHUNK_IDX_NTYPES", &myenum);
  return(dtype_id);
}

/* typedef enum H5D_fill_time_t { H5D_FILL_TIME_ERROR = -1, H5D_FILL_TIME_ALLOC = 0, H5D_FILL_TIME_NEVER = 1, H5D_FILL_TIME_IFSET = 2} H5D_fill_time_t; */
hid_t create_DT_H5D_fill_time_t(void) {
  enum H5D_fill_time_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5D_fill_time_t), issigned(enum H5D_fill_time_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5D_FILL_TIME_ERROR;
  H5Tenum_insert(dtype_id, "H5D_FILL_TIME_ERROR", &myenum);
  myenum = H5D_FILL_TIME_ALLOC;
  H5Tenum_insert(dtype_id, "H5D_FILL_TIME_ALLOC", &myenum);
  myenum = H5D_FILL_TIME_NEVER;
  H5Tenum_insert(dtype_id, "H5D_FILL_TIME_NEVER", &myenum);
  myenum = H5D_FILL_TIME_IFSET;
  H5Tenum_insert(dtype_id, "H5D_FILL_TIME_IFSET", &myenum);
  return(dtype_id);
}

/* typedef enum H5D_fill_value_t { H5D_FILL_VALUE_ERROR =-1, H5D_FILL_VALUE_UNDEFINED =0, H5D_FILL_VALUE_DEFAULT =1, H5D_FILL_VALUE_USER_DEFINED =2} H5D_fill_value_t; */
hid_t create_DT_H5D_fill_value_t(void) {
  enum H5D_fill_value_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5D_fill_value_t), issigned(enum H5D_fill_value_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5D_FILL_VALUE_ERROR;
  H5Tenum_insert(dtype_id, "H5D_FILL_VALUE_ERROR", &myenum);
  myenum = H5D_FILL_VALUE_UNDEFINED;
  H5Tenum_insert(dtype_id, "H5D_FILL_VALUE_UNDEFINED", &myenum);
  myenum = H5D_FILL_VALUE_DEFAULT;
  H5Tenum_insert(dtype_id, "H5D_FILL_VALUE_DEFAULT", &myenum);
  myenum = H5D_FILL_VALUE_USER_DEFINED;
  H5Tenum_insert(dtype_id, "H5D_FILL_VALUE_USER_DEFINED", &myenum);
  return(dtype_id);
}

/* typedef enum H5D_layout_t { H5D_LAYOUT_ERROR = -1, H5D_COMPACT = 0, H5D_CONTIGUOUS = 1, H5D_CHUNKED = 2, H5D_VIRTUAL = 3, H5D_NLAYOUTS = 4 } H5D_layout_t; */
hid_t create_DT_H5D_layout_t(void) {
  enum H5D_layout_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5D_layout_t), issigned(enum H5D_layout_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5D_LAYOUT_ERROR;
  H5Tenum_insert(dtype_id, "H5D_LAYOUT_ERROR", &myenum);
  myenum = H5D_COMPACT;
  H5Tenum_insert(dtype_id, "H5D_COMPACT", &myenum);
  myenum = H5D_CONTIGUOUS;
  H5Tenum_insert(dtype_id, "H5D_CONTIGUOUS", &myenum);
  myenum = H5D_CHUNKED;
  H5Tenum_insert(dtype_id, "H5D_CHUNKED", &myenum);
  myenum = H5D_VIRTUAL;
  H5Tenum_insert(dtype_id, "H5D_VIRTUAL", &myenum);
  myenum = H5D_NLAYOUTS;
  H5Tenum_insert(dtype_id, "H5D_NLAYOUTS", &myenum);
  return(dtype_id);
}

/* typedef enum H5D_mpio_actual_chunk_opt_mode_t { H5D_MPIO_NO_CHUNK_OPTIMIZATION = 0, H5D_MPIO_LINK_CHUNK, H5D_MPIO_MULTI_CHUNK} H5D_mpio_actual_chunk_opt_mode_t; */
hid_t create_DT_H5D_mpio_actual_chunk_opt_mode_t(void) {
  enum H5D_mpio_actual_chunk_opt_mode_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5D_mpio_actual_chunk_opt_mode_t), issigned(enum H5D_mpio_actual_chunk_opt_mode_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5D_MPIO_NO_CHUNK_OPTIMIZATION;
  H5Tenum_insert(dtype_id, "H5D_MPIO_NO_CHUNK_OPTIMIZATION", &myenum);
  myenum = H5D_MPIO_LINK_CHUNK;
  H5Tenum_insert(dtype_id, "H5D_MPIO_LINK_CHUNK", &myenum);
  myenum = H5D_MPIO_MULTI_CHUNK;
  H5Tenum_insert(dtype_id, "H5D_MPIO_MULTI_CHUNK", &myenum);
  return(dtype_id);
}

/* typedef enum H5D_mpio_actual_io_mode_t { H5D_MPIO_NO_COLLECTIVE = 0x0, H5D_MPIO_CHUNK_INDEPENDENT = 0x1, H5D_MPIO_CHUNK_COLLECTIVE = 0x2, H5D_MPIO_CHUNK_MIXED = 0x1 | 0x2, H5D_MPIO_CONTIGUOUS_COLLECTIVE = 0x4} H5D_mpio_actual_io_mode_t; */
hid_t create_DT_H5D_mpio_actual_io_mode_t(void) {
  enum H5D_mpio_actual_io_mode_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5D_mpio_actual_io_mode_t), issigned(enum H5D_mpio_actual_io_mode_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5D_MPIO_NO_COLLECTIVE;
  H5Tenum_insert(dtype_id, "H5D_MPIO_NO_COLLECTIVE", &myenum);
  myenum = H5D_MPIO_CHUNK_INDEPENDENT;
  H5Tenum_insert(dtype_id, "H5D_MPIO_CHUNK_INDEPENDENT", &myenum);
  myenum = H5D_MPIO_CHUNK_COLLECTIVE;
  H5Tenum_insert(dtype_id, "H5D_MPIO_CHUNK_COLLECTIVE", &myenum);
  myenum = H5D_MPIO_CHUNK_MIXED;
  H5Tenum_insert(dtype_id, "H5D_MPIO_CHUNK_MIXED", &myenum);
  myenum = H5D_MPIO_CONTIGUOUS_COLLECTIVE;
  H5Tenum_insert(dtype_id, "H5D_MPIO_CONTIGUOUS_COLLECTIVE", &myenum);
  return(dtype_id);
}

/* typedef enum H5D_mpio_no_collective_cause_t { H5D_MPIO_COLLECTIVE = 0x00, H5D_MPIO_SET_INDEPENDENT = 0x01, H5D_MPIO_DATATYPE_CONVERSION = 0x02, H5D_MPIO_DATA_TRANSFORMS = 0x04, H5D_MPIO_MPI_OPT_TYPES_ENV_VAR_DISABLED = 0x08, H5D_MPIO_NOT_SIMPLE_OR_SCALAR_DATASPACES = 0x10, H5D_MPIO_NOT_CONTIGUOUS_OR_CHUNKED_DATASET = 0x20, H5D_MPIO_PARALLEL_FILTERED_WRITES_DISABLED = 0x40, H5D_MPIO_NO_COLLECTIVE_MAX_CAUSE = 0x80} H5D_mpio_no_collective_cause_t; */
hid_t create_DT_H5D_mpio_no_collective_cause_t(void) {
  enum H5D_mpio_no_collective_cause_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5D_mpio_no_collective_cause_t), issigned(enum H5D_mpio_no_collective_cause_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5D_MPIO_COLLECTIVE;
  H5Tenum_insert(dtype_id, "H5D_MPIO_COLLECTIVE", &myenum);
  myenum = H5D_MPIO_SET_INDEPENDENT;
  H5Tenum_insert(dtype_id, "H5D_MPIO_SET_INDEPENDENT", &myenum);
  myenum = H5D_MPIO_DATATYPE_CONVERSION;
  H5Tenum_insert(dtype_id, "H5D_MPIO_DATATYPE_CONVERSION", &myenum);
  myenum = H5D_MPIO_DATA_TRANSFORMS;
  H5Tenum_insert(dtype_id, "H5D_MPIO_DATA_TRANSFORMS", &myenum);
  myenum = H5D_MPIO_MPI_OPT_TYPES_ENV_VAR_DISABLED;
  H5Tenum_insert(dtype_id, "H5D_MPIO_MPI_OPT_TYPES_ENV_VAR_DISABLED", &myenum);
  myenum = H5D_MPIO_NOT_SIMPLE_OR_SCALAR_DATASPACES;
  H5Tenum_insert(dtype_id, "H5D_MPIO_NOT_SIMPLE_OR_SCALAR_DATASPACES", &myenum);
  myenum = H5D_MPIO_NOT_CONTIGUOUS_OR_CHUNKED_DATASET;
  H5Tenum_insert(dtype_id, "H5D_MPIO_NOT_CONTIGUOUS_OR_CHUNKED_DATASET", &myenum);
  myenum = H5D_MPIO_PARALLEL_FILTERED_WRITES_DISABLED;
  H5Tenum_insert(dtype_id, "H5D_MPIO_PARALLEL_FILTERED_WRITES_DISABLED", &myenum);
  myenum = H5D_MPIO_NO_COLLECTIVE_MAX_CAUSE;
  H5Tenum_insert(dtype_id, "H5D_MPIO_NO_COLLECTIVE_MAX_CAUSE", &myenum);
  return(dtype_id);
}

/* typedef enum H5D_space_status_t { H5D_SPACE_STATUS_ERROR = -1, H5D_SPACE_STATUS_NOT_ALLOCATED = 0, H5D_SPACE_STATUS_PART_ALLOCATED = 1, H5D_SPACE_STATUS_ALLOCATED = 2} H5D_space_status_t; */
hid_t create_DT_H5D_space_status_t(void) {
  enum H5D_space_status_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5D_space_status_t), issigned(enum H5D_space_status_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5D_SPACE_STATUS_ERROR;
  H5Tenum_insert(dtype_id, "H5D_SPACE_STATUS_ERROR", &myenum);
  myenum = H5D_SPACE_STATUS_NOT_ALLOCATED;
  H5Tenum_insert(dtype_id, "H5D_SPACE_STATUS_NOT_ALLOCATED", &myenum);
  myenum = H5D_SPACE_STATUS_PART_ALLOCATED;
  H5Tenum_insert(dtype_id, "H5D_SPACE_STATUS_PART_ALLOCATED", &myenum);
  myenum = H5D_SPACE_STATUS_ALLOCATED;
  H5Tenum_insert(dtype_id, "H5D_SPACE_STATUS_ALLOCATED", &myenum);
  return(dtype_id);
}

/* typedef enum H5D_vds_view_t { H5D_VDS_ERROR = -1, H5D_VDS_FIRST_MISSING = 0, H5D_VDS_LAST_AVAILABLE = 1} H5D_vds_view_t; */
hid_t create_DT_H5D_vds_view_t(void) {
  enum H5D_vds_view_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5D_vds_view_t), issigned(enum H5D_vds_view_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5D_VDS_ERROR;
  H5Tenum_insert(dtype_id, "H5D_VDS_ERROR", &myenum);
  myenum = H5D_VDS_FIRST_MISSING;
  H5Tenum_insert(dtype_id, "H5D_VDS_FIRST_MISSING", &myenum);
  myenum = H5D_VDS_LAST_AVAILABLE;
  H5Tenum_insert(dtype_id, "H5D_VDS_LAST_AVAILABLE", &myenum);
  return(dtype_id);
}

/* typedef enum H5E_direction_t { H5E_WALK_UPWARD = 0, H5E_WALK_DOWNWARD = 1 } H5E_direction_t; */
hid_t create_DT_H5E_direction_t(void) {
  enum H5E_direction_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5E_direction_t), issigned(enum H5E_direction_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5E_WALK_UPWARD;
  H5Tenum_insert(dtype_id, "H5E_WALK_UPWARD", &myenum);
  myenum = H5E_WALK_DOWNWARD;
  H5Tenum_insert(dtype_id, "H5E_WALK_DOWNWARD", &myenum);
  return(dtype_id);
}

/* typedef enum H5E_type_t { H5E_MAJOR, H5E_MINOR} H5E_type_t; */
hid_t create_DT_H5E_type_t(void) {
  enum H5E_type_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5E_type_t), issigned(enum H5E_type_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5E_MAJOR;
  H5Tenum_insert(dtype_id, "H5E_MAJOR", &myenum);
  myenum = H5E_MINOR;
  H5Tenum_insert(dtype_id, "H5E_MINOR", &myenum);
  return(dtype_id);
}

/* typedef enum H5F_close_degree_t { H5F_CLOSE_DEFAULT = 0, H5F_CLOSE_WEAK = 1, H5F_CLOSE_SEMI = 2, H5F_CLOSE_STRONG = 3} H5F_close_degree_t; */
hid_t create_DT_H5F_close_degree_t(void) {
  enum H5F_close_degree_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5F_close_degree_t), issigned(enum H5F_close_degree_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5F_CLOSE_DEFAULT;
  H5Tenum_insert(dtype_id, "H5F_CLOSE_DEFAULT", &myenum);
  myenum = H5F_CLOSE_WEAK;
  H5Tenum_insert(dtype_id, "H5F_CLOSE_WEAK", &myenum);
  myenum = H5F_CLOSE_SEMI;
  H5Tenum_insert(dtype_id, "H5F_CLOSE_SEMI", &myenum);
  myenum = H5F_CLOSE_STRONG;
  H5Tenum_insert(dtype_id, "H5F_CLOSE_STRONG", &myenum);
  return(dtype_id);
}

/* typedef enum H5F_file_space_type_t { H5F_FILE_SPACE_DEFAULT = 0, H5F_FILE_SPACE_ALL_PERSIST = 1, H5F_FILE_SPACE_ALL = 2, H5F_FILE_SPACE_AGGR_VFD = 3, H5F_FILE_SPACE_VFD = 4, H5F_FILE_SPACE_NTYPES } H5F_file_space_type_t; */
hid_t create_DT_H5F_file_space_type_t(void) {
  enum H5F_file_space_type_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5F_file_space_type_t), issigned(enum H5F_file_space_type_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5F_FILE_SPACE_DEFAULT;
  H5Tenum_insert(dtype_id, "H5F_FILE_SPACE_DEFAULT", &myenum);
  myenum = H5F_FILE_SPACE_ALL_PERSIST;
  H5Tenum_insert(dtype_id, "H5F_FILE_SPACE_ALL_PERSIST", &myenum);
  myenum = H5F_FILE_SPACE_ALL;
  H5Tenum_insert(dtype_id, "H5F_FILE_SPACE_ALL", &myenum);
  myenum = H5F_FILE_SPACE_AGGR_VFD;
  H5Tenum_insert(dtype_id, "H5F_FILE_SPACE_AGGR_VFD", &myenum);
  myenum = H5F_FILE_SPACE_VFD;
  H5Tenum_insert(dtype_id, "H5F_FILE_SPACE_VFD", &myenum);
  myenum = H5F_FILE_SPACE_NTYPES;
  H5Tenum_insert(dtype_id, "H5F_FILE_SPACE_NTYPES", &myenum);
  return(dtype_id);
}

/* typedef enum H5F_fspace_strategy_t { H5F_FSPACE_STRATEGY_FSM_AGGR = 0, H5F_FSPACE_STRATEGY_PAGE = 1, H5F_FSPACE_STRATEGY_AGGR = 2, H5F_FSPACE_STRATEGY_NONE = 3, H5F_FSPACE_STRATEGY_NTYPES } H5F_fspace_strategy_t; */
hid_t create_DT_H5F_fspace_strategy_t(void) {
  enum H5F_fspace_strategy_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5F_fspace_strategy_t), issigned(enum H5F_fspace_strategy_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5F_FSPACE_STRATEGY_FSM_AGGR;
  H5Tenum_insert(dtype_id, "H5F_FSPACE_STRATEGY_FSM_AGGR", &myenum);
  myenum = H5F_FSPACE_STRATEGY_PAGE;
  H5Tenum_insert(dtype_id, "H5F_FSPACE_STRATEGY_PAGE", &myenum);
  myenum = H5F_FSPACE_STRATEGY_AGGR;
  H5Tenum_insert(dtype_id, "H5F_FSPACE_STRATEGY_AGGR", &myenum);
  myenum = H5F_FSPACE_STRATEGY_NONE;
  H5Tenum_insert(dtype_id, "H5F_FSPACE_STRATEGY_NONE", &myenum);
  myenum = H5F_FSPACE_STRATEGY_NTYPES;
  H5Tenum_insert(dtype_id, "H5F_FSPACE_STRATEGY_NTYPES", &myenum);
  return(dtype_id);
}

/* typedef enum H5F_libver_t { H5F_LIBVER_ERROR = -1, H5F_LIBVER_EARLIEST = 0, H5F_LIBVER_V18 = 1, H5F_LIBVER_V110 = 2, H5F_LIBVER_NBOUNDS} H5F_libver_t; */
hid_t create_DT_H5F_libver_t(void) {
  enum H5F_libver_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5F_libver_t), issigned(enum H5F_libver_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5F_LIBVER_ERROR;
  H5Tenum_insert(dtype_id, "H5F_LIBVER_ERROR", &myenum);
  myenum = H5F_LIBVER_EARLIEST;
  H5Tenum_insert(dtype_id, "H5F_LIBVER_EARLIEST", &myenum);
  myenum = H5F_LIBVER_V18;
  H5Tenum_insert(dtype_id, "H5F_LIBVER_V18", &myenum);
  myenum = H5F_LIBVER_V110;
  H5Tenum_insert(dtype_id, "H5F_LIBVER_V110", &myenum);
  myenum = H5F_LIBVER_NBOUNDS;
  H5Tenum_insert(dtype_id, "H5F_LIBVER_NBOUNDS", &myenum);
  return(dtype_id);
}

/* typedef enum H5F_mem_t { H5FD_MEM_NOLIST = -1, H5FD_MEM_DEFAULT = 0, H5FD_MEM_SUPER = 1, H5FD_MEM_BTREE = 2, H5FD_MEM_DRAW = 3, H5FD_MEM_GHEAP = 4, H5FD_MEM_LHEAP = 5, H5FD_MEM_OHDR = 6, H5FD_MEM_NTYPES } H5F_mem_t; */
hid_t create_DT_H5F_mem_t(void) {
  enum H5F_mem_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5F_mem_t), issigned(enum H5F_mem_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5FD_MEM_NOLIST;
  H5Tenum_insert(dtype_id, "H5FD_MEM_NOLIST", &myenum);
  myenum = H5FD_MEM_DEFAULT;
  H5Tenum_insert(dtype_id, "H5FD_MEM_DEFAULT", &myenum);
  myenum = H5FD_MEM_SUPER;
  H5Tenum_insert(dtype_id, "H5FD_MEM_SUPER", &myenum);
  myenum = H5FD_MEM_BTREE;
  H5Tenum_insert(dtype_id, "H5FD_MEM_BTREE", &myenum);
  myenum = H5FD_MEM_DRAW;
  H5Tenum_insert(dtype_id, "H5FD_MEM_DRAW", &myenum);
  myenum = H5FD_MEM_GHEAP;
  H5Tenum_insert(dtype_id, "H5FD_MEM_GHEAP", &myenum);
  myenum = H5FD_MEM_LHEAP;
  H5Tenum_insert(dtype_id, "H5FD_MEM_LHEAP", &myenum);
  myenum = H5FD_MEM_OHDR;
  H5Tenum_insert(dtype_id, "H5FD_MEM_OHDR", &myenum);
  myenum = H5FD_MEM_NTYPES;
  H5Tenum_insert(dtype_id, "H5FD_MEM_NTYPES", &myenum);
  return(dtype_id);
}

/* typedef enum H5F_scope_t { H5F_SCOPE_LOCAL = 0, H5F_SCOPE_GLOBAL = 1 } H5F_scope_t; */
hid_t create_DT_H5F_scope_t(void) {
  enum H5F_scope_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5F_scope_t), issigned(enum H5F_scope_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5F_SCOPE_LOCAL;
  H5Tenum_insert(dtype_id, "H5F_SCOPE_LOCAL", &myenum);
  myenum = H5F_SCOPE_GLOBAL;
  H5Tenum_insert(dtype_id, "H5F_SCOPE_GLOBAL", &myenum);
  return(dtype_id);
}

/* typedef enum { H5FD_FILE_IMAGE_OP_NO_OP, H5FD_FILE_IMAGE_OP_PROPERTY_LIST_SET, H5FD_FILE_IMAGE_OP_PROPERTY_LIST_COPY, H5FD_FILE_IMAGE_OP_PROPERTY_LIST_GET, H5FD_FILE_IMAGE_OP_PROPERTY_LIST_CLOSE, H5FD_FILE_IMAGE_OP_FILE_OPEN, H5FD_FILE_IMAGE_OP_FILE_RESIZE, H5FD_FILE_IMAGE_OP_FILE_CLOSE} H5FD_file_image_op_t; */
hid_t create_DT_H5FD_file_image_op_t(void) {
  H5FD_file_image_op_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(H5FD_file_image_op_t), issigned(H5FD_file_image_op_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5FD_FILE_IMAGE_OP_NO_OP;
  H5Tenum_insert(dtype_id, "H5FD_FILE_IMAGE_OP_NO_OP", &myenum);
  myenum = H5FD_FILE_IMAGE_OP_PROPERTY_LIST_SET;
  H5Tenum_insert(dtype_id, "H5FD_FILE_IMAGE_OP_PROPERTY_LIST_SET", &myenum);
  myenum = H5FD_FILE_IMAGE_OP_PROPERTY_LIST_COPY;
  H5Tenum_insert(dtype_id, "H5FD_FILE_IMAGE_OP_PROPERTY_LIST_COPY", &myenum);
  myenum = H5FD_FILE_IMAGE_OP_PROPERTY_LIST_GET;
  H5Tenum_insert(dtype_id, "H5FD_FILE_IMAGE_OP_PROPERTY_LIST_GET", &myenum);
  myenum = H5FD_FILE_IMAGE_OP_PROPERTY_LIST_CLOSE;
  H5Tenum_insert(dtype_id, "H5FD_FILE_IMAGE_OP_PROPERTY_LIST_CLOSE", &myenum);
  myenum = H5FD_FILE_IMAGE_OP_FILE_OPEN;
  H5Tenum_insert(dtype_id, "H5FD_FILE_IMAGE_OP_FILE_OPEN", &myenum);
  myenum = H5FD_FILE_IMAGE_OP_FILE_RESIZE;
  H5Tenum_insert(dtype_id, "H5FD_FILE_IMAGE_OP_FILE_RESIZE", &myenum);
  myenum = H5FD_FILE_IMAGE_OP_FILE_CLOSE;
  H5Tenum_insert(dtype_id, "H5FD_FILE_IMAGE_OP_FILE_CLOSE", &myenum);
  return(dtype_id);
}

/* typedef enum H5G_obj_t { H5G_UNKNOWN = -1, H5G_GROUP, H5G_DATASET, H5G_TYPE, H5G_LINK, H5G_UDLINK, H5G_RESERVED_5, H5G_RESERVED_6, H5G_RESERVED_7 } H5G_obj_t; */
hid_t create_DT_H5G_obj_t(void) {
  enum H5G_obj_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5G_obj_t), issigned(enum H5G_obj_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5G_UNKNOWN;
  H5Tenum_insert(dtype_id, "H5G_UNKNOWN", &myenum);
  myenum = H5G_GROUP;
  H5Tenum_insert(dtype_id, "H5G_GROUP", &myenum);
  myenum = H5G_DATASET;
  H5Tenum_insert(dtype_id, "H5G_DATASET", &myenum);
  myenum = H5G_TYPE;
  H5Tenum_insert(dtype_id, "H5G_TYPE", &myenum);
  myenum = H5G_LINK;
  H5Tenum_insert(dtype_id, "H5G_LINK", &myenum);
  myenum = H5G_UDLINK;
  H5Tenum_insert(dtype_id, "H5G_UDLINK", &myenum);
  myenum = H5G_RESERVED_5;
  H5Tenum_insert(dtype_id, "H5G_RESERVED_5", &myenum);
  myenum = H5G_RESERVED_6;
  H5Tenum_insert(dtype_id, "H5G_RESERVED_6", &myenum);
  myenum = H5G_RESERVED_7;
  H5Tenum_insert(dtype_id, "H5G_RESERVED_7", &myenum);
  return(dtype_id);
}

/* typedef enum H5G_storage_type_t { H5G_STORAGE_TYPE_UNKNOWN = -1, H5G_STORAGE_TYPE_SYMBOL_TABLE, H5G_STORAGE_TYPE_COMPACT, H5G_STORAGE_TYPE_DENSE } H5G_storage_type_t; */
hid_t create_DT_H5G_storage_type_t(void) {
  enum H5G_storage_type_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5G_storage_type_t), issigned(enum H5G_storage_type_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5G_STORAGE_TYPE_UNKNOWN;
  H5Tenum_insert(dtype_id, "H5G_STORAGE_TYPE_UNKNOWN", &myenum);
  myenum = H5G_STORAGE_TYPE_SYMBOL_TABLE;
  H5Tenum_insert(dtype_id, "H5G_STORAGE_TYPE_SYMBOL_TABLE", &myenum);
  myenum = H5G_STORAGE_TYPE_COMPACT;
  H5Tenum_insert(dtype_id, "H5G_STORAGE_TYPE_COMPACT", &myenum);
  myenum = H5G_STORAGE_TYPE_DENSE;
  H5Tenum_insert(dtype_id, "H5G_STORAGE_TYPE_DENSE", &myenum);
  return(dtype_id);
}

/* typedef enum H5I_type_t { H5I_UNINIT = (-2), H5I_BADID = (-1), H5I_FILE = 1, H5I_GROUP, H5I_DATATYPE, H5I_DATASPACE, H5I_DATASET, H5I_ATTR, H5I_REFERENCE, H5I_VFL, H5I_GENPROP_CLS, H5I_GENPROP_LST, H5I_ERROR_CLASS, H5I_ERROR_MSG, H5I_ERROR_STACK, H5I_NTYPES } H5I_type_t; */
hid_t create_DT_H5I_type_t(void) {
  enum H5I_type_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5I_type_t), issigned(enum H5I_type_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5I_UNINIT;
  H5Tenum_insert(dtype_id, "H5I_UNINIT", &myenum);
  myenum = H5I_BADID;
  H5Tenum_insert(dtype_id, "H5I_BADID", &myenum);
  myenum = H5I_FILE;
  H5Tenum_insert(dtype_id, "H5I_FILE", &myenum);
  myenum = H5I_GROUP;
  H5Tenum_insert(dtype_id, "H5I_GROUP", &myenum);
  myenum = H5I_DATATYPE;
  H5Tenum_insert(dtype_id, "H5I_DATATYPE", &myenum);
  myenum = H5I_DATASPACE;
  H5Tenum_insert(dtype_id, "H5I_DATASPACE", &myenum);
  myenum = H5I_DATASET;
  H5Tenum_insert(dtype_id, "H5I_DATASET", &myenum);
  myenum = H5I_ATTR;
  H5Tenum_insert(dtype_id, "H5I_ATTR", &myenum);
  myenum = H5I_REFERENCE;
  H5Tenum_insert(dtype_id, "H5I_REFERENCE", &myenum);
  myenum = H5I_VFL;
  H5Tenum_insert(dtype_id, "H5I_VFL", &myenum);
  myenum = H5I_GENPROP_CLS;
  H5Tenum_insert(dtype_id, "H5I_GENPROP_CLS", &myenum);
  myenum = H5I_GENPROP_LST;
  H5Tenum_insert(dtype_id, "H5I_GENPROP_LST", &myenum);
  myenum = H5I_ERROR_CLASS;
  H5Tenum_insert(dtype_id, "H5I_ERROR_CLASS", &myenum);
  myenum = H5I_ERROR_MSG;
  H5Tenum_insert(dtype_id, "H5I_ERROR_MSG", &myenum);
  myenum = H5I_ERROR_STACK;
  H5Tenum_insert(dtype_id, "H5I_ERROR_STACK", &myenum);
  myenum = H5I_NTYPES;
  H5Tenum_insert(dtype_id, "H5I_NTYPES", &myenum);
  return(dtype_id);
}

/* typedef enum { H5L_TYPE_ERROR = (-1), H5L_TYPE_HARD = 0, H5L_TYPE_SOFT = 1, H5L_TYPE_EXTERNAL = 64, H5L_TYPE_MAX = 255 } H5L_type_t; */
hid_t create_DT_H5L_type_t(void) {
  H5L_type_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(H5L_type_t), issigned(H5L_type_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5L_TYPE_ERROR;
  H5Tenum_insert(dtype_id, "H5L_TYPE_ERROR", &myenum);
  myenum = H5L_TYPE_HARD;
  H5Tenum_insert(dtype_id, "H5L_TYPE_HARD", &myenum);
  myenum = H5L_TYPE_SOFT;
  H5Tenum_insert(dtype_id, "H5L_TYPE_SOFT", &myenum);
  myenum = H5L_TYPE_EXTERNAL;
  H5Tenum_insert(dtype_id, "H5L_TYPE_EXTERNAL", &myenum);
  myenum = H5L_TYPE_MAX;
  H5Tenum_insert(dtype_id, "H5L_TYPE_MAX", &myenum);
  return(dtype_id);
}

/* typedef enum H5LT_lang_t { H5LT_LANG_ERR = -1, H5LT_DDL = 0, H5LT_C = 1, H5LT_FORTRAN = 2, H5LT_NO_LANG = 3 } H5LT_lang_t; */
hid_t create_DT_H5LT_lang_t(void) {
  enum H5LT_lang_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5LT_lang_t), issigned(enum H5LT_lang_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5LT_LANG_ERR;
  H5Tenum_insert(dtype_id, "H5LT_LANG_ERR", &myenum);
  myenum = H5LT_DDL;
  H5Tenum_insert(dtype_id, "H5LT_DDL", &myenum);
  myenum = H5LT_C;
  H5Tenum_insert(dtype_id, "H5LT_C", &myenum);
  myenum = H5LT_FORTRAN;
  H5Tenum_insert(dtype_id, "H5LT_FORTRAN", &myenum);
  myenum = H5LT_NO_LANG;
  H5Tenum_insert(dtype_id, "H5LT_NO_LANG", &myenum);
  return(dtype_id);
}

/* typedef enum H5O_mcdt_search_ret_t { H5O_MCDT_SEARCH_ERROR = -1, H5O_MCDT_SEARCH_CONT, H5O_MCDT_SEARCH_STOP } H5O_mcdt_search_ret_t; */
hid_t create_DT_H5O_mcdt_search_ret_t(void) {
  enum H5O_mcdt_search_ret_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5O_mcdt_search_ret_t), issigned(enum H5O_mcdt_search_ret_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5O_MCDT_SEARCH_ERROR;
  H5Tenum_insert(dtype_id, "H5O_MCDT_SEARCH_ERROR", &myenum);
  myenum = H5O_MCDT_SEARCH_CONT;
  H5Tenum_insert(dtype_id, "H5O_MCDT_SEARCH_CONT", &myenum);
  myenum = H5O_MCDT_SEARCH_STOP;
  H5Tenum_insert(dtype_id, "H5O_MCDT_SEARCH_STOP", &myenum);
  return(dtype_id);
}

/* typedef enum H5O_type_t { H5O_TYPE_UNKNOWN = -1, H5O_TYPE_GROUP, H5O_TYPE_DATASET, H5O_TYPE_NAMED_DATATYPE, H5O_TYPE_NTYPES } H5O_type_t; */
hid_t create_DT_H5O_type_t(void) {
  enum H5O_type_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5O_type_t), issigned(enum H5O_type_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5O_TYPE_UNKNOWN;
  H5Tenum_insert(dtype_id, "H5O_TYPE_UNKNOWN", &myenum);
  myenum = H5O_TYPE_GROUP;
  H5Tenum_insert(dtype_id, "H5O_TYPE_GROUP", &myenum);
  myenum = H5O_TYPE_DATASET;
  H5Tenum_insert(dtype_id, "H5O_TYPE_DATASET", &myenum);
  myenum = H5O_TYPE_NAMED_DATATYPE;
  H5Tenum_insert(dtype_id, "H5O_TYPE_NAMED_DATATYPE", &myenum);
  myenum = H5O_TYPE_NTYPES;
  H5Tenum_insert(dtype_id, "H5O_TYPE_NTYPES", &myenum);
  return(dtype_id);
}

/* typedef enum H5PL_type_t { H5PL_TYPE_ERROR = -1, H5PL_TYPE_FILTER = 0, H5PL_TYPE_NONE = 1 } H5PL_type_t; */
hid_t create_DT_H5PL_type_t(void) {
  enum H5PL_type_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5PL_type_t), issigned(enum H5PL_type_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5PL_TYPE_ERROR;
  H5Tenum_insert(dtype_id, "H5PL_TYPE_ERROR", &myenum);
  myenum = H5PL_TYPE_FILTER;
  H5Tenum_insert(dtype_id, "H5PL_TYPE_FILTER", &myenum);
  myenum = H5PL_TYPE_NONE;
  H5Tenum_insert(dtype_id, "H5PL_TYPE_NONE", &myenum);
  return(dtype_id);
}

/* typedef enum H5R_type_t { H5R_BADTYPE = (-1), H5R_OBJECT, H5R_DATASET_REGION, H5R_MAXTYPE } H5R_type_t; */
hid_t create_DT_H5R_type_t(void) {
  enum H5R_type_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5R_type_t), issigned(enum H5R_type_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5R_BADTYPE;
  H5Tenum_insert(dtype_id, "H5R_BADTYPE", &myenum);
  myenum = H5R_OBJECT;
  H5Tenum_insert(dtype_id, "H5R_OBJECT", &myenum);
  myenum = H5R_DATASET_REGION;
  H5Tenum_insert(dtype_id, "H5R_DATASET_REGION", &myenum);
  myenum = H5R_MAXTYPE;
  H5Tenum_insert(dtype_id, "H5R_MAXTYPE", &myenum);
  return(dtype_id);
}

/* typedef enum H5S_class_t { H5S_NO_CLASS = -1, H5S_SCALAR = 0, H5S_SIMPLE = 1, H5S_NULL = 2 } H5S_class_t; */
hid_t create_DT_H5S_class_t(void) {
  enum H5S_class_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5S_class_t), issigned(enum H5S_class_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5S_NO_CLASS;
  H5Tenum_insert(dtype_id, "H5S_NO_CLASS", &myenum);
  myenum = H5S_SCALAR;
  H5Tenum_insert(dtype_id, "H5S_SCALAR", &myenum);
  myenum = H5S_SIMPLE;
  H5Tenum_insert(dtype_id, "H5S_SIMPLE", &myenum);
  myenum = H5S_NULL;
  H5Tenum_insert(dtype_id, "H5S_NULL", &myenum);
  return(dtype_id);
}

/* typedef enum { H5S_SEL_ERROR = -1, H5S_SEL_NONE = 0, H5S_SEL_POINTS = 1, H5S_SEL_HYPERSLABS = 2, H5S_SEL_ALL = 3, H5S_SEL_N }H5S_sel_type; */
hid_t create_DT_H5S_sel_type(void) {
  H5S_sel_type myenum;
  hid_t base_type = get_h5_equiv(sizeof(H5S_sel_type), issigned(H5S_sel_type));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5S_SEL_ERROR;
  H5Tenum_insert(dtype_id, "H5S_SEL_ERROR", &myenum);
  myenum = H5S_SEL_NONE;
  H5Tenum_insert(dtype_id, "H5S_SEL_NONE", &myenum);
  myenum = H5S_SEL_POINTS;
  H5Tenum_insert(dtype_id, "H5S_SEL_POINTS", &myenum);
  myenum = H5S_SEL_HYPERSLABS;
  H5Tenum_insert(dtype_id, "H5S_SEL_HYPERSLABS", &myenum);
  myenum = H5S_SEL_ALL;
  H5Tenum_insert(dtype_id, "H5S_SEL_ALL", &myenum);
  myenum = H5S_SEL_N;
  H5Tenum_insert(dtype_id, "H5S_SEL_N", &myenum);
  return(dtype_id);
}

/* typedef enum H5S_seloper_t { H5S_SELECT_NOOP = -1, H5S_SELECT_SET = 0, H5S_SELECT_OR, H5S_SELECT_AND, H5S_SELECT_XOR, H5S_SELECT_NOTB, H5S_SELECT_NOTA, H5S_SELECT_APPEND, H5S_SELECT_PREPEND, H5S_SELECT_INVALID } H5S_seloper_t; */
hid_t create_DT_H5S_seloper_t(void) {
  enum H5S_seloper_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5S_seloper_t), issigned(enum H5S_seloper_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5S_SELECT_NOOP;
  H5Tenum_insert(dtype_id, "H5S_SELECT_NOOP", &myenum);
  myenum = H5S_SELECT_SET;
  H5Tenum_insert(dtype_id, "H5S_SELECT_SET", &myenum);
  myenum = H5S_SELECT_OR;
  H5Tenum_insert(dtype_id, "H5S_SELECT_OR", &myenum);
  myenum = H5S_SELECT_AND;
  H5Tenum_insert(dtype_id, "H5S_SELECT_AND", &myenum);
  myenum = H5S_SELECT_XOR;
  H5Tenum_insert(dtype_id, "H5S_SELECT_XOR", &myenum);
  myenum = H5S_SELECT_NOTB;
  H5Tenum_insert(dtype_id, "H5S_SELECT_NOTB", &myenum);
  myenum = H5S_SELECT_NOTA;
  H5Tenum_insert(dtype_id, "H5S_SELECT_NOTA", &myenum);
  myenum = H5S_SELECT_APPEND;
  H5Tenum_insert(dtype_id, "H5S_SELECT_APPEND", &myenum);
  myenum = H5S_SELECT_PREPEND;
  H5Tenum_insert(dtype_id, "H5S_SELECT_PREPEND", &myenum);
  myenum = H5S_SELECT_INVALID;
  H5Tenum_insert(dtype_id, "H5S_SELECT_INVALID", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_bkg_t { H5T_BKG_NO = 0, H5T_BKG_TEMP = 1, H5T_BKG_YES = 2 } H5T_bkg_t; */
hid_t create_DT_H5T_bkg_t(void) {
  enum H5T_bkg_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_bkg_t), issigned(enum H5T_bkg_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_BKG_NO;
  H5Tenum_insert(dtype_id, "H5T_BKG_NO", &myenum);
  myenum = H5T_BKG_TEMP;
  H5Tenum_insert(dtype_id, "H5T_BKG_TEMP", &myenum);
  myenum = H5T_BKG_YES;
  H5Tenum_insert(dtype_id, "H5T_BKG_YES", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_class_t { H5T_NO_CLASS = -1, H5T_INTEGER = 0, H5T_FLOAT = 1, H5T_TIME = 2, H5T_STRING = 3, H5T_BITFIELD = 4, H5T_OPAQUE = 5, H5T_COMPOUND = 6, H5T_REFERENCE = 7, H5T_ENUM = 8, H5T_VLEN = 9, H5T_ARRAY = 10, H5T_NCLASSES } H5T_class_t; */
hid_t create_DT_H5T_class_t(void) {
  enum H5T_class_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_class_t), issigned(enum H5T_class_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_NO_CLASS;
  H5Tenum_insert(dtype_id, "H5T_NO_CLASS", &myenum);
  myenum = H5T_INTEGER;
  H5Tenum_insert(dtype_id, "H5T_INTEGER", &myenum);
  myenum = H5T_FLOAT;
  H5Tenum_insert(dtype_id, "H5T_FLOAT", &myenum);
  myenum = H5T_TIME;
  H5Tenum_insert(dtype_id, "H5T_TIME", &myenum);
  myenum = H5T_STRING;
  H5Tenum_insert(dtype_id, "H5T_STRING", &myenum);
  myenum = H5T_BITFIELD;
  H5Tenum_insert(dtype_id, "H5T_BITFIELD", &myenum);
  myenum = H5T_OPAQUE;
  H5Tenum_insert(dtype_id, "H5T_OPAQUE", &myenum);
  myenum = H5T_COMPOUND;
  H5Tenum_insert(dtype_id, "H5T_COMPOUND", &myenum);
  myenum = H5T_REFERENCE;
  H5Tenum_insert(dtype_id, "H5T_REFERENCE", &myenum);
  myenum = H5T_ENUM;
  H5Tenum_insert(dtype_id, "H5T_ENUM", &myenum);
  myenum = H5T_VLEN;
  H5Tenum_insert(dtype_id, "H5T_VLEN", &myenum);
  myenum = H5T_ARRAY;
  H5Tenum_insert(dtype_id, "H5T_ARRAY", &myenum);
  myenum = H5T_NCLASSES;
  H5Tenum_insert(dtype_id, "H5T_NCLASSES", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_cmd_t { H5T_CONV_INIT = 0, H5T_CONV_CONV = 1, H5T_CONV_FREE = 2 } H5T_cmd_t; */
hid_t create_DT_H5T_cmd_t(void) {
  enum H5T_cmd_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_cmd_t), issigned(enum H5T_cmd_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_CONV_INIT;
  H5Tenum_insert(dtype_id, "H5T_CONV_INIT", &myenum);
  myenum = H5T_CONV_CONV;
  H5Tenum_insert(dtype_id, "H5T_CONV_CONV", &myenum);
  myenum = H5T_CONV_FREE;
  H5Tenum_insert(dtype_id, "H5T_CONV_FREE", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_conv_except_t { H5T_CONV_EXCEPT_RANGE_HI = 0, H5T_CONV_EXCEPT_RANGE_LOW = 1, H5T_CONV_EXCEPT_PRECISION = 2, H5T_CONV_EXCEPT_TRUNCATE = 3, H5T_CONV_EXCEPT_PINF = 4, H5T_CONV_EXCEPT_NINF = 5, H5T_CONV_EXCEPT_NAN = 6 } H5T_conv_except_t; */
hid_t create_DT_H5T_conv_except_t(void) {
  enum H5T_conv_except_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_conv_except_t), issigned(enum H5T_conv_except_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_CONV_EXCEPT_RANGE_HI;
  H5Tenum_insert(dtype_id, "H5T_CONV_EXCEPT_RANGE_HI", &myenum);
  myenum = H5T_CONV_EXCEPT_RANGE_LOW;
  H5Tenum_insert(dtype_id, "H5T_CONV_EXCEPT_RANGE_LOW", &myenum);
  myenum = H5T_CONV_EXCEPT_PRECISION;
  H5Tenum_insert(dtype_id, "H5T_CONV_EXCEPT_PRECISION", &myenum);
  myenum = H5T_CONV_EXCEPT_TRUNCATE;
  H5Tenum_insert(dtype_id, "H5T_CONV_EXCEPT_TRUNCATE", &myenum);
  myenum = H5T_CONV_EXCEPT_PINF;
  H5Tenum_insert(dtype_id, "H5T_CONV_EXCEPT_PINF", &myenum);
  myenum = H5T_CONV_EXCEPT_NINF;
  H5Tenum_insert(dtype_id, "H5T_CONV_EXCEPT_NINF", &myenum);
  myenum = H5T_CONV_EXCEPT_NAN;
  H5Tenum_insert(dtype_id, "H5T_CONV_EXCEPT_NAN", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_conv_ret_t { H5T_CONV_ABORT = -1, H5T_CONV_UNHANDLED = 0, H5T_CONV_HANDLED = 1 } H5T_conv_ret_t; */
hid_t create_DT_H5T_conv_ret_t(void) {
  enum H5T_conv_ret_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_conv_ret_t), issigned(enum H5T_conv_ret_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_CONV_ABORT;
  H5Tenum_insert(dtype_id, "H5T_CONV_ABORT", &myenum);
  myenum = H5T_CONV_UNHANDLED;
  H5Tenum_insert(dtype_id, "H5T_CONV_UNHANDLED", &myenum);
  myenum = H5T_CONV_HANDLED;
  H5Tenum_insert(dtype_id, "H5T_CONV_HANDLED", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_cset_t { H5T_CSET_ERROR = -1, H5T_CSET_ASCII = 0, H5T_CSET_UTF8 = 1, H5T_CSET_RESERVED_2 = 2, H5T_CSET_RESERVED_3 = 3, H5T_CSET_RESERVED_4 = 4, H5T_CSET_RESERVED_5 = 5, H5T_CSET_RESERVED_6 = 6, H5T_CSET_RESERVED_7 = 7, H5T_CSET_RESERVED_8 = 8, H5T_CSET_RESERVED_9 = 9, H5T_CSET_RESERVED_10 = 10, H5T_CSET_RESERVED_11 = 11, H5T_CSET_RESERVED_12 = 12, H5T_CSET_RESERVED_13 = 13, H5T_CSET_RESERVED_14 = 14, H5T_CSET_RESERVED_15 = 15 } H5T_cset_t; */
hid_t create_DT_H5T_cset_t(void) {
  enum H5T_cset_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_cset_t), issigned(enum H5T_cset_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_CSET_ERROR;
  H5Tenum_insert(dtype_id, "H5T_CSET_ERROR", &myenum);
  myenum = H5T_CSET_ASCII;
  H5Tenum_insert(dtype_id, "H5T_CSET_ASCII", &myenum);
  myenum = H5T_CSET_UTF8;
  H5Tenum_insert(dtype_id, "H5T_CSET_UTF8", &myenum);
  myenum = H5T_CSET_RESERVED_2;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_2", &myenum);
  myenum = H5T_CSET_RESERVED_3;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_3", &myenum);
  myenum = H5T_CSET_RESERVED_4;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_4", &myenum);
  myenum = H5T_CSET_RESERVED_5;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_5", &myenum);
  myenum = H5T_CSET_RESERVED_6;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_6", &myenum);
  myenum = H5T_CSET_RESERVED_7;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_7", &myenum);
  myenum = H5T_CSET_RESERVED_8;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_8", &myenum);
  myenum = H5T_CSET_RESERVED_9;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_9", &myenum);
  myenum = H5T_CSET_RESERVED_10;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_10", &myenum);
  myenum = H5T_CSET_RESERVED_11;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_11", &myenum);
  myenum = H5T_CSET_RESERVED_12;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_12", &myenum);
  myenum = H5T_CSET_RESERVED_13;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_13", &myenum);
  myenum = H5T_CSET_RESERVED_14;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_14", &myenum);
  myenum = H5T_CSET_RESERVED_15;
  H5Tenum_insert(dtype_id, "H5T_CSET_RESERVED_15", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_direction_t { H5T_DIR_DEFAULT = 0, H5T_DIR_ASCEND = 1, H5T_DIR_DESCEND = 2 } H5T_direction_t; */
hid_t create_DT_H5T_direction_t(void) {
  enum H5T_direction_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_direction_t), issigned(enum H5T_direction_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_DIR_DEFAULT;
  H5Tenum_insert(dtype_id, "H5T_DIR_DEFAULT", &myenum);
  myenum = H5T_DIR_ASCEND;
  H5Tenum_insert(dtype_id, "H5T_DIR_ASCEND", &myenum);
  myenum = H5T_DIR_DESCEND;
  H5Tenum_insert(dtype_id, "H5T_DIR_DESCEND", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_norm_t { H5T_NORM_ERROR = -1, H5T_NORM_IMPLIED = 0, H5T_NORM_MSBSET = 1, H5T_NORM_NONE = 2 } H5T_norm_t; */
hid_t create_DT_H5T_norm_t(void) {
  enum H5T_norm_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_norm_t), issigned(enum H5T_norm_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_NORM_ERROR;
  H5Tenum_insert(dtype_id, "H5T_NORM_ERROR", &myenum);
  myenum = H5T_NORM_IMPLIED;
  H5Tenum_insert(dtype_id, "H5T_NORM_IMPLIED", &myenum);
  myenum = H5T_NORM_MSBSET;
  H5Tenum_insert(dtype_id, "H5T_NORM_MSBSET", &myenum);
  myenum = H5T_NORM_NONE;
  H5Tenum_insert(dtype_id, "H5T_NORM_NONE", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_order_t { H5T_ORDER_ERROR = -1, H5T_ORDER_LE = 0, H5T_ORDER_BE = 1, H5T_ORDER_VAX = 2, H5T_ORDER_MIXED = 3, H5T_ORDER_NONE = 4 } H5T_order_t; */
hid_t create_DT_H5T_order_t(void) {
  enum H5T_order_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_order_t), issigned(enum H5T_order_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_ORDER_ERROR;
  H5Tenum_insert(dtype_id, "H5T_ORDER_ERROR", &myenum);
  myenum = H5T_ORDER_LE;
  H5Tenum_insert(dtype_id, "H5T_ORDER_LE", &myenum);
  myenum = H5T_ORDER_BE;
  H5Tenum_insert(dtype_id, "H5T_ORDER_BE", &myenum);
  myenum = H5T_ORDER_VAX;
  H5Tenum_insert(dtype_id, "H5T_ORDER_VAX", &myenum);
  myenum = H5T_ORDER_MIXED;
  H5Tenum_insert(dtype_id, "H5T_ORDER_MIXED", &myenum);
  myenum = H5T_ORDER_NONE;
  H5Tenum_insert(dtype_id, "H5T_ORDER_NONE", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_pad_t { H5T_PAD_ERROR = -1, H5T_PAD_ZERO = 0, H5T_PAD_ONE = 1, H5T_PAD_BACKGROUND = 2, H5T_NPAD = 3 } H5T_pad_t; */
hid_t create_DT_H5T_pad_t(void) {
  enum H5T_pad_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_pad_t), issigned(enum H5T_pad_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_PAD_ERROR;
  H5Tenum_insert(dtype_id, "H5T_PAD_ERROR", &myenum);
  myenum = H5T_PAD_ZERO;
  H5Tenum_insert(dtype_id, "H5T_PAD_ZERO", &myenum);
  myenum = H5T_PAD_ONE;
  H5Tenum_insert(dtype_id, "H5T_PAD_ONE", &myenum);
  myenum = H5T_PAD_BACKGROUND;
  H5Tenum_insert(dtype_id, "H5T_PAD_BACKGROUND", &myenum);
  myenum = H5T_NPAD;
  H5Tenum_insert(dtype_id, "H5T_NPAD", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_pers_t { H5T_PERS_DONTCARE = -1, H5T_PERS_HARD = 0, H5T_PERS_SOFT = 1 } H5T_pers_t; */
hid_t create_DT_H5T_pers_t(void) {
  enum H5T_pers_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_pers_t), issigned(enum H5T_pers_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_PERS_DONTCARE;
  H5Tenum_insert(dtype_id, "H5T_PERS_DONTCARE", &myenum);
  myenum = H5T_PERS_HARD;
  H5Tenum_insert(dtype_id, "H5T_PERS_HARD", &myenum);
  myenum = H5T_PERS_SOFT;
  H5Tenum_insert(dtype_id, "H5T_PERS_SOFT", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_sign_t { H5T_SGN_ERROR = -1, H5T_SGN_NONE = 0, H5T_SGN_2 = 1, H5T_NSGN = 2 } H5T_sign_t; */
hid_t create_DT_H5T_sign_t(void) {
  enum H5T_sign_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_sign_t), issigned(enum H5T_sign_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_SGN_ERROR;
  H5Tenum_insert(dtype_id, "H5T_SGN_ERROR", &myenum);
  myenum = H5T_SGN_NONE;
  H5Tenum_insert(dtype_id, "H5T_SGN_NONE", &myenum);
  myenum = H5T_SGN_2;
  H5Tenum_insert(dtype_id, "H5T_SGN_2", &myenum);
  myenum = H5T_NSGN;
  H5Tenum_insert(dtype_id, "H5T_NSGN", &myenum);
  return(dtype_id);
}

/* typedef enum H5T_str_t { H5T_STR_ERROR = -1, H5T_STR_NULLTERM = 0, H5T_STR_NULLPAD = 1, H5T_STR_SPACEPAD = 2, H5T_STR_RESERVED_3 = 3, H5T_STR_RESERVED_4 = 4, H5T_STR_RESERVED_5 = 5, H5T_STR_RESERVED_6 = 6, H5T_STR_RESERVED_7 = 7, H5T_STR_RESERVED_8 = 8, H5T_STR_RESERVED_9 = 9, H5T_STR_RESERVED_10 = 10, H5T_STR_RESERVED_11 = 11, H5T_STR_RESERVED_12 = 12, H5T_STR_RESERVED_13 = 13, H5T_STR_RESERVED_14 = 14, H5T_STR_RESERVED_15 = 15 } H5T_str_t; */
hid_t create_DT_H5T_str_t(void) {
  enum H5T_str_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5T_str_t), issigned(enum H5T_str_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5T_STR_ERROR;
  H5Tenum_insert(dtype_id, "H5T_STR_ERROR", &myenum);
  myenum = H5T_STR_NULLTERM;
  H5Tenum_insert(dtype_id, "H5T_STR_NULLTERM", &myenum);
  myenum = H5T_STR_NULLPAD;
  H5Tenum_insert(dtype_id, "H5T_STR_NULLPAD", &myenum);
  myenum = H5T_STR_SPACEPAD;
  H5Tenum_insert(dtype_id, "H5T_STR_SPACEPAD", &myenum);
  myenum = H5T_STR_RESERVED_3;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_3", &myenum);
  myenum = H5T_STR_RESERVED_4;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_4", &myenum);
  myenum = H5T_STR_RESERVED_5;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_5", &myenum);
  myenum = H5T_STR_RESERVED_6;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_6", &myenum);
  myenum = H5T_STR_RESERVED_7;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_7", &myenum);
  myenum = H5T_STR_RESERVED_8;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_8", &myenum);
  myenum = H5T_STR_RESERVED_9;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_9", &myenum);
  myenum = H5T_STR_RESERVED_10;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_10", &myenum);
  myenum = H5T_STR_RESERVED_11;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_11", &myenum);
  myenum = H5T_STR_RESERVED_12;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_12", &myenum);
  myenum = H5T_STR_RESERVED_13;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_13", &myenum);
  myenum = H5T_STR_RESERVED_14;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_14", &myenum);
  myenum = H5T_STR_RESERVED_15;
  H5Tenum_insert(dtype_id, "H5T_STR_RESERVED_15", &myenum);
  return(dtype_id);
}

/* typedef enum H5Z_cb_return_t { H5Z_CB_ERROR = -1, H5Z_CB_FAIL = 0, H5Z_CB_CONT = 1, H5Z_CB_NO = 2} H5Z_cb_return_t; */
hid_t create_DT_H5Z_cb_return_t(void) {
  enum H5Z_cb_return_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5Z_cb_return_t), issigned(enum H5Z_cb_return_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5Z_CB_ERROR;
  H5Tenum_insert(dtype_id, "H5Z_CB_ERROR", &myenum);
  myenum = H5Z_CB_FAIL;
  H5Tenum_insert(dtype_id, "H5Z_CB_FAIL", &myenum);
  myenum = H5Z_CB_CONT;
  H5Tenum_insert(dtype_id, "H5Z_CB_CONT", &myenum);
  myenum = H5Z_CB_NO;
  H5Tenum_insert(dtype_id, "H5Z_CB_NO", &myenum);
  return(dtype_id);
}

/* typedef enum H5Z_EDC_t { H5Z_ERROR_EDC = -1, H5Z_DISABLE_EDC = 0, H5Z_ENABLE_EDC = 1, H5Z_NO_EDC = 2 } H5Z_EDC_t; */
hid_t create_DT_H5Z_EDC_t(void) {
  enum H5Z_EDC_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5Z_EDC_t), issigned(enum H5Z_EDC_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5Z_ERROR_EDC;
  H5Tenum_insert(dtype_id, "H5Z_ERROR_EDC", &myenum);
  myenum = H5Z_DISABLE_EDC;
  H5Tenum_insert(dtype_id, "H5Z_DISABLE_EDC", &myenum);
  myenum = H5Z_ENABLE_EDC;
  H5Tenum_insert(dtype_id, "H5Z_ENABLE_EDC", &myenum);
  myenum = H5Z_NO_EDC;
  H5Tenum_insert(dtype_id, "H5Z_NO_EDC", &myenum);
  return(dtype_id);
}

/* typedef enum H5Z_SO_scale_type_t { H5Z_SO_FLOAT_DSCALE = 0, H5Z_SO_FLOAT_ESCALE = 1, H5Z_SO_INT = 2} H5Z_SO_scale_type_t; */
hid_t create_DT_H5Z_SO_scale_type_t(void) {
  enum H5Z_SO_scale_type_t myenum;
  hid_t base_type = get_h5_equiv(sizeof(enum H5Z_SO_scale_type_t), issigned(enum H5Z_SO_scale_type_t));
  hid_t dtype_id = H5Tenum_create(base_type);
  myenum = H5Z_SO_FLOAT_DSCALE;
  H5Tenum_insert(dtype_id, "H5Z_SO_FLOAT_DSCALE", &myenum);
  myenum = H5Z_SO_FLOAT_ESCALE;
  H5Tenum_insert(dtype_id, "H5Z_SO_FLOAT_ESCALE", &myenum);
  myenum = H5Z_SO_INT;
  H5Tenum_insert(dtype_id, "H5Z_SO_INT", &myenum);
  return(dtype_id);
}



/*************************************************************************
 *
 * Structs
 *
 *************************************************************************/


/* typedef struct H5_ih_info_t { hsize_t index_size; hsize_t heap_size} H5_ih_info_t; */
hid_t create_DT_H5_ih_info_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5_ih_info_t));
  H5Tinsert(dtype_id, "index_size", HOFFSET(H5_ih_info_t, index_size), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "heap_size", HOFFSET(H5_ih_info_t, heap_size), h5_datatype[DT_hsize_t]);
  return(dtype_id);
}

/* typedef struct { hbool_t corder_valid; H5O_msg_crt_idx_t corder; H5T_cset_t cset; hsize_t data_size} H5A_info_t; */
hid_t create_DT_H5A_info_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5A_info_t));
  H5Tinsert(dtype_id, "corder_valid", HOFFSET(H5A_info_t, corder_valid), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "corder", HOFFSET(H5A_info_t, corder), h5_datatype[DT_H5O_msg_crt_idx_t]);
  H5Tinsert(dtype_id, "cset", HOFFSET(H5A_info_t, cset), h5_datatype[DT_H5T_cset_t]);
  H5Tinsert(dtype_id, "data_size", HOFFSET(H5A_info_t, data_size), h5_datatype[DT_hsize_t]);
  return(dtype_id);
}

/* typedef struct H5AC_cache_config_t{ int version; hbool_t rpt_fcn_enabled; hbool_t open_trace_file; hbool_t close_trace_file; char trace_file_name[H5AC__MAX_TRACE_FILE_NAME_LEN + 1]; hbool_t evictions_enabled; hbool_t set_initial_size; size_t initial_size; double min_clean_fraction; size_t max_size; size_t min_size; long int epoch_length; enum H5C_cache_incr_mode incr_mode; double lower_hr_threshold; double increment; hbool_t apply_max_increment; size_t max_increment; enum H5C_cache_flash_incr_mode flash_incr_mode; double flash_multiple; double flash_threshold; enum H5C_cache_decr_mode decr_mode; double upper_hr_threshold; double decrement; hbool_t apply_max_decrement; size_t max_decrement; int epochs_before_eviction; hbool_t apply_empty_reserve; double empty_reserve; size_t dirty_bytes_threshold; int metadata_write_strategy} H5AC_cache_config_t; */
hid_t create_DT_H5AC_cache_config_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5AC_cache_config_t));
  H5Tinsert(dtype_id, "version", HOFFSET(H5AC_cache_config_t, version), h5_datatype[DT_int]);
  H5Tinsert(dtype_id, "rpt_fcn_enabled", HOFFSET(H5AC_cache_config_t, rpt_fcn_enabled), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "open_trace_file", HOFFSET(H5AC_cache_config_t, open_trace_file), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "close_trace_file", HOFFSET(H5AC_cache_config_t, close_trace_file), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "trace_file_name", HOFFSET(H5AC_cache_config_t, trace_file_name), h5_datatype[DT_char]);
  H5Tinsert(dtype_id, "evictions_enabled", HOFFSET(H5AC_cache_config_t, evictions_enabled), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "set_initial_size", HOFFSET(H5AC_cache_config_t, set_initial_size), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "initial_size", HOFFSET(H5AC_cache_config_t, initial_size), h5_datatype[DT_size_t]);
  H5Tinsert(dtype_id, "min_clean_fraction", HOFFSET(H5AC_cache_config_t, min_clean_fraction), h5_datatype[DT_double]);
  H5Tinsert(dtype_id, "max_size", HOFFSET(H5AC_cache_config_t, max_size), h5_datatype[DT_size_t]);
  H5Tinsert(dtype_id, "min_size", HOFFSET(H5AC_cache_config_t, min_size), h5_datatype[DT_size_t]);
  H5Tinsert(dtype_id, "epoch_length", HOFFSET(H5AC_cache_config_t, epoch_length), h5_datatype[DT_long_int]);
  H5Tinsert(dtype_id, "incr_mode", HOFFSET(H5AC_cache_config_t, incr_mode), h5_datatype[DT_H5C_cache_incr_mode]);
  H5Tinsert(dtype_id, "lower_hr_threshold", HOFFSET(H5AC_cache_config_t, lower_hr_threshold), h5_datatype[DT_double]);
  H5Tinsert(dtype_id, "increment", HOFFSET(H5AC_cache_config_t, increment), h5_datatype[DT_double]);
  H5Tinsert(dtype_id, "apply_max_increment", HOFFSET(H5AC_cache_config_t, apply_max_increment), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "max_increment", HOFFSET(H5AC_cache_config_t, max_increment), h5_datatype[DT_size_t]);
  H5Tinsert(dtype_id, "flash_incr_mode", HOFFSET(H5AC_cache_config_t, flash_incr_mode), h5_datatype[DT_H5C_cache_flash_incr_mode]);
  H5Tinsert(dtype_id, "flash_multiple", HOFFSET(H5AC_cache_config_t, flash_multiple), h5_datatype[DT_double]);
  H5Tinsert(dtype_id, "flash_threshold", HOFFSET(H5AC_cache_config_t, flash_threshold), h5_datatype[DT_double]);
  H5Tinsert(dtype_id, "decr_mode", HOFFSET(H5AC_cache_config_t, decr_mode), h5_datatype[DT_H5C_cache_decr_mode]);
  H5Tinsert(dtype_id, "upper_hr_threshold", HOFFSET(H5AC_cache_config_t, upper_hr_threshold), h5_datatype[DT_double]);
  H5Tinsert(dtype_id, "decrement", HOFFSET(H5AC_cache_config_t, decrement), h5_datatype[DT_double]);
  H5Tinsert(dtype_id, "apply_max_decrement", HOFFSET(H5AC_cache_config_t, apply_max_decrement), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "max_decrement", HOFFSET(H5AC_cache_config_t, max_decrement), h5_datatype[DT_size_t]);
  H5Tinsert(dtype_id, "epochs_before_eviction", HOFFSET(H5AC_cache_config_t, epochs_before_eviction), h5_datatype[DT_int]);
  H5Tinsert(dtype_id, "apply_empty_reserve", HOFFSET(H5AC_cache_config_t, apply_empty_reserve), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "empty_reserve", HOFFSET(H5AC_cache_config_t, empty_reserve), h5_datatype[DT_double]);
  H5Tinsert(dtype_id, "dirty_bytes_threshold", HOFFSET(H5AC_cache_config_t, dirty_bytes_threshold), h5_datatype[DT_size_t]);
  H5Tinsert(dtype_id, "metadata_write_strategy", HOFFSET(H5AC_cache_config_t, metadata_write_strategy), h5_datatype[DT_int]);
  return(dtype_id);
}

/* typedef struct H5AC_cache_image_config_t { int version; hbool_t generate_image; hbool_t save_resize_status; int entry_ageout} H5AC_cache_image_config_t; */
hid_t create_DT_H5AC_cache_image_config_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5AC_cache_image_config_t));
  H5Tinsert(dtype_id, "version", HOFFSET(H5AC_cache_image_config_t, version), h5_datatype[DT_int]);
  H5Tinsert(dtype_id, "generate_image", HOFFSET(H5AC_cache_image_config_t, generate_image), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "save_resize_status", HOFFSET(H5AC_cache_image_config_t, save_resize_status), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "entry_ageout", HOFFSET(H5AC_cache_image_config_t, entry_ageout), h5_datatype[DT_int]);
  return(dtype_id);
}

/* typedef struct H5D_info_t { int rank; char* dims; char* maxdims; H5T_class_t type_class; H5S_class_t space_class} H5D_info_t; */
hid_t create_DT_H5D_info_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5D_info_t));
  H5Tinsert(dtype_id, "rank", HOFFSET(H5D_info_t, rank), h5_datatype[DT_int]);
  H5Tinsert(dtype_id, "dims", HOFFSET(H5D_info_t, dims), h5_datatype[DT_char]);
  H5Tinsert(dtype_id, "maxdims", HOFFSET(H5D_info_t, maxdims), h5_datatype[DT_char]);
  H5Tinsert(dtype_id, "type_class", HOFFSET(H5D_info_t, type_class), h5_datatype[DT_H5T_class_t]);
  H5Tinsert(dtype_id, "space_class", HOFFSET(H5D_info_t, space_class), h5_datatype[DT_H5S_class_t]);
  return(dtype_id);
}

/* typedef struct H5E_error1_t { H5E_major_t maj_num; H5E_minor_t min_num; const char *func_name; const char *file_name; unsigned line; const char *desc} H5E_error1_t; */
hid_t create_DT_H5E_error1_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5E_error1_t));
  H5Tinsert(dtype_id, "maj_num", HOFFSET(H5E_error1_t, maj_num), h5_datatype[DT_H5E_major_t]);
  H5Tinsert(dtype_id, "min_num", HOFFSET(H5E_error1_t, min_num), h5_datatype[DT_H5E_minor_t]);
  H5Tinsert(dtype_id, "func_name", HOFFSET(H5E_error1_t, func_name), h5_datatype[DT_char]);
  H5Tinsert(dtype_id, "file_name", HOFFSET(H5E_error1_t, file_name), h5_datatype[DT_char]);
  H5Tinsert(dtype_id, "line", HOFFSET(H5E_error1_t, line), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "desc", HOFFSET(H5E_error1_t, desc), h5_datatype[DT_char]);
  return(dtype_id);
}

/* typedef struct H5E_error2_t { hid_t cls_id; hid_t maj_num; hid_t min_num; unsigned line; const char *func_name; const char *file_name; const char *desc} H5E_error2_t; */
hid_t create_DT_H5E_error2_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5E_error2_t));
  H5Tinsert(dtype_id, "cls_id", HOFFSET(H5E_error2_t, cls_id), h5_datatype[DT_hid_t]);
  H5Tinsert(dtype_id, "maj_num", HOFFSET(H5E_error2_t, maj_num), h5_datatype[DT_hid_t]);
  H5Tinsert(dtype_id, "min_num", HOFFSET(H5E_error2_t, min_num), h5_datatype[DT_hid_t]);
  H5Tinsert(dtype_id, "line", HOFFSET(H5E_error2_t, line), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "func_name", HOFFSET(H5E_error2_t, func_name), h5_datatype[DT_char]);
  H5Tinsert(dtype_id, "file_name", HOFFSET(H5E_error2_t, file_name), h5_datatype[DT_char]);
  H5Tinsert(dtype_id, "desc", HOFFSET(H5E_error2_t, desc), h5_datatype[DT_char]);
  return(dtype_id);
}

/* typedef struct H5F_info1_helper_t { hsize_t hdr_size; H5_ih_info_t msgs_info} H5F_info1_helper_t;  */
hid_t create_DT_H5F_info1_helper_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5F_info1_helper_t));
  H5Tinsert(dtype_id, "hdr_size", HOFFSET(H5F_info1_helper_t, hdr_size), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "msgs_info", HOFFSET(H5F_info1_helper_t, msgs_info), h5_datatype[DT_H5_ih_info_t]);
  return(dtype_id);
}

/* typedef struct H5F_info1_t { hsize_t super_ext_size; H5F_info1_helper_t sohm} H5F_info1_t; */
hid_t create_DT_H5F_info1_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5F_info1_t));
  H5Tinsert(dtype_id, "super_ext_size", HOFFSET(H5F_info1_t, super_ext_size), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "sohm", HOFFSET(H5F_info1_t, sohm), h5_datatype[DT_H5F_info1_helper_t]);
  return(dtype_id);
}

/* typedef struct H5F_info2_free_t { unsigned version; hsize_t meta_size; hsize_t tot_space} H5F_info2_free_t; */
hid_t create_DT_H5F_info2_free_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5F_info2_free_t));
  H5Tinsert(dtype_id, "version", HOFFSET(H5F_info2_free_t, version), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "meta_size", HOFFSET(H5F_info2_free_t, meta_size), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "tot_space", HOFFSET(H5F_info2_free_t, tot_space), h5_datatype[DT_hsize_t]);
  return(dtype_id);
}

/* typedef struct H5F_info2_sohm_t { unsigned version; hsize_t hdr_size; H5_ih_info_t msgs_info} H5F_info2_sohm_t; */
hid_t create_DT_H5F_info2_sohm_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5F_info2_sohm_t));
  H5Tinsert(dtype_id, "version", HOFFSET(H5F_info2_sohm_t, version), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "hdr_size", HOFFSET(H5F_info2_sohm_t, hdr_size), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "msgs_info", HOFFSET(H5F_info2_sohm_t, msgs_info), h5_datatype[DT_H5_ih_info_t]);
  return(dtype_id);
}

/* typedef struct H5F_info2_super_t { unsigned version; hsize_t super_size; hsize_t super_ext_size} H5F_info2_super_t; */
hid_t create_DT_H5F_info2_super_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5F_info2_super_t));
  H5Tinsert(dtype_id, "version", HOFFSET(H5F_info2_super_t, version), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "super_size", HOFFSET(H5F_info2_super_t, super_size), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "super_ext_size", HOFFSET(H5F_info2_super_t, super_ext_size), h5_datatype[DT_hsize_t]);
  return(dtype_id);
}

/* typedef struct H5F_info2_t { H5F_info2_super_t super; H5F_info2_free_t free; H5F_info2_sohm_t sohm} H5F_info2_t; */
hid_t create_DT_H5F_info2_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5F_info2_t));
  H5Tinsert(dtype_id, "super", HOFFSET(H5F_info2_t, super), h5_datatype[DT_H5F_info2_super_t]);
  H5Tinsert(dtype_id, "free", HOFFSET(H5F_info2_t, free), h5_datatype[DT_H5F_info2_free_t]);
  H5Tinsert(dtype_id, "sohm", HOFFSET(H5F_info2_t, sohm), h5_datatype[DT_H5F_info2_sohm_t]);
  return(dtype_id);
}

/* typedef struct H5F_retry_info_t { unsigned nbins; uint32_t *retries[H5F_NUM_METADATA_READ_RETRY_TYPES]} H5F_retry_info_t; */
hid_t create_DT_H5F_retry_info_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5F_retry_info_t));
  H5Tinsert(dtype_id, "nbins", HOFFSET(H5F_retry_info_t, nbins), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "retries", HOFFSET(H5F_retry_info_t, retries), h5_datatype[DT_uint32_t]);
  return(dtype_id);
}

/* typedef struct H5F_sect_info_t { haddr_t addr; hsize_t size} H5F_sect_info_t; */
hid_t create_DT_H5F_sect_info_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5F_sect_info_t));
  H5Tinsert(dtype_id, "addr", HOFFSET(H5F_sect_info_t, addr), h5_datatype[DT_haddr_t]);
  H5Tinsert(dtype_id, "size", HOFFSET(H5F_sect_info_t, size), h5_datatype[DT_hsize_t]);
  return(dtype_id);
}

/* typedef struct H5G_info_t { H5G_storage_type_t storage_type; hsize_t nlinks; int64_t max_corder; hbool_t mounted} H5G_info_t; */
hid_t create_DT_H5G_info_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5G_info_t));
  H5Tinsert(dtype_id, "storage_type", HOFFSET(H5G_info_t, storage_type), h5_datatype[DT_H5G_storage_type_t]);
  H5Tinsert(dtype_id, "nlinks", HOFFSET(H5G_info_t, nlinks), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "max_corder", HOFFSET(H5G_info_t, max_corder), h5_datatype[DT_int64_t]);
  H5Tinsert(dtype_id, "mounted", HOFFSET(H5G_info_t, mounted), h5_datatype[DT_hbool_t]);
  return(dtype_id);
}

/* typedef union H5L_info_helper_t { haddr_t address; size_t val_size} H5L_info_helper_t;  */
hid_t create_DT_H5L_info_helper_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5L_info_helper_t));
  H5Tinsert(dtype_id, "address", HOFFSET(H5L_info_helper_t, address), h5_datatype[DT_haddr_t]);
  return(dtype_id);
}

/* typedef struct H5L_info_t { H5L_type_t type; hbool_t corder_valid; int64_t corder; H5T_cset_t cset; H5L_info_helper_t u} H5L_info_t; */
hid_t create_DT_H5L_info_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5L_info_t));
  H5Tinsert(dtype_id, "type", HOFFSET(H5L_info_t, type), h5_datatype[DT_H5L_type_t]);
  H5Tinsert(dtype_id, "corder_valid", HOFFSET(H5L_info_t, corder_valid), h5_datatype[DT_hbool_t]);
  H5Tinsert(dtype_id, "corder", HOFFSET(H5L_info_t, corder), h5_datatype[DT_int64_t]);
  H5Tinsert(dtype_id, "cset", HOFFSET(H5L_info_t, cset), h5_datatype[DT_H5T_cset_t]);
  H5Tinsert(dtype_id, "u", HOFFSET(H5L_info_t, u), h5_datatype[DT_H5L_info_helper_t]);
  return(dtype_id);
}

/* typedef struct H5ls_info_t { char* name; int link_success; H5L_info_t link; int obj_type_success; H5I_type_t obj_type; int num_attrs; int group_success; H5G_info_t group; int dataset_success; H5D_info_t dataset; int type_success; H5T_class_t committed_type} H5ls_info_t; */
hid_t create_DT_H5ls_info_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5ls_info_t));
  H5Tinsert(dtype_id, "name", HOFFSET(H5ls_info_t, name), h5_datatype[DT_char]);
  H5Tinsert(dtype_id, "link_success", HOFFSET(H5ls_info_t, link_success), h5_datatype[DT_int]);
  H5Tinsert(dtype_id, "link", HOFFSET(H5ls_info_t, link), h5_datatype[DT_H5L_info_t]);
  H5Tinsert(dtype_id, "obj_type_success", HOFFSET(H5ls_info_t, obj_type_success), h5_datatype[DT_int]);
  H5Tinsert(dtype_id, "obj_type", HOFFSET(H5ls_info_t, obj_type), h5_datatype[DT_H5I_type_t]);
  H5Tinsert(dtype_id, "num_attrs", HOFFSET(H5ls_info_t, num_attrs), h5_datatype[DT_int]);
  H5Tinsert(dtype_id, "group_success", HOFFSET(H5ls_info_t, group_success), h5_datatype[DT_int]);
  H5Tinsert(dtype_id, "group", HOFFSET(H5ls_info_t, group), h5_datatype[DT_H5G_info_t]);
  H5Tinsert(dtype_id, "dataset_success", HOFFSET(H5ls_info_t, dataset_success), h5_datatype[DT_int]);
  H5Tinsert(dtype_id, "dataset", HOFFSET(H5ls_info_t, dataset), h5_datatype[DT_H5D_info_t]);
  H5Tinsert(dtype_id, "type_success", HOFFSET(H5ls_info_t, type_success), h5_datatype[DT_int]);
  H5Tinsert(dtype_id, "committed_type", HOFFSET(H5ls_info_t, committed_type), h5_datatype[DT_H5T_class_t]);
  return(dtype_id);
}

/* typedef struct H5O_hdr_info_helper_msg_t { uint64_t present; uint64_t shared} H5O_hdr_info_helper_msg_t;  */
hid_t create_DT_H5O_hdr_info_helper_msg_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5O_hdr_info_helper_msg_t));
  H5Tinsert(dtype_id, "present", HOFFSET(H5O_hdr_info_helper_msg_t, present), h5_datatype[DT_uint64_t]);
  H5Tinsert(dtype_id, "shared", HOFFSET(H5O_hdr_info_helper_msg_t, shared), h5_datatype[DT_uint64_t]);
  return(dtype_id);
}

/* typedef struct H5O_hdr_info_helper_space_t { hsize_t total; hsize_t meta; hsize_t mesg; hsize_t free} H5O_hdr_info_helper_space_t;  */
hid_t create_DT_H5O_hdr_info_helper_space_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5O_hdr_info_helper_space_t));
  H5Tinsert(dtype_id, "total", HOFFSET(H5O_hdr_info_helper_space_t, total), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "meta", HOFFSET(H5O_hdr_info_helper_space_t, meta), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "mesg", HOFFSET(H5O_hdr_info_helper_space_t, mesg), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "free", HOFFSET(H5O_hdr_info_helper_space_t, free), h5_datatype[DT_hsize_t]);
  return(dtype_id);
}

/* typedef struct H5O_hdr_info_t { unsigned version; unsigned nmesgs; unsigned nchunks; unsigned flags; H5O_hdr_info_helper_space_t space; H5O_hdr_info_helper_msg_t mesg} H5O_hdr_info_t; */
hid_t create_DT_H5O_hdr_info_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5O_hdr_info_t));
  H5Tinsert(dtype_id, "version", HOFFSET(H5O_hdr_info_t, version), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "nmesgs", HOFFSET(H5O_hdr_info_t, nmesgs), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "nchunks", HOFFSET(H5O_hdr_info_t, nchunks), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "flags", HOFFSET(H5O_hdr_info_t, flags), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "space", HOFFSET(H5O_hdr_info_t, space), h5_datatype[DT_H5O_hdr_info_helper_space_t]);
  H5Tinsert(dtype_id, "mesg", HOFFSET(H5O_hdr_info_t, mesg), h5_datatype[DT_H5O_hdr_info_helper_msg_t]);
  return(dtype_id);
}

/* typedef struct H5O_info_helper_t { H5_ih_info_t obj; H5_ih_info_t attr} H5O_info_helper_t;  */
hid_t create_DT_H5O_info_helper_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5O_info_helper_t));
  H5Tinsert(dtype_id, "obj", HOFFSET(H5O_info_helper_t, obj), h5_datatype[DT_H5_ih_info_t]);
  H5Tinsert(dtype_id, "attr", HOFFSET(H5O_info_helper_t, attr), h5_datatype[DT_H5_ih_info_t]);
  return(dtype_id);
}

/* typedef struct H5O_info_t { unsigned long fileno; haddr_t addr; H5O_type_t type; unsigned rc; time_t atime; time_t mtime; time_t ctime; time_t btime; hsize_t num_attrs; H5O_hdr_info_t hdr; H5O_info_helper_t meta_size} H5O_info_t; */
hid_t create_DT_H5O_info_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5O_info_t));
  H5Tinsert(dtype_id, "fileno", HOFFSET(H5O_info_t, fileno), h5_datatype[DT_unsigned_long]);
  H5Tinsert(dtype_id, "addr", HOFFSET(H5O_info_t, addr), h5_datatype[DT_haddr_t]);
  H5Tinsert(dtype_id, "type", HOFFSET(H5O_info_t, type), h5_datatype[DT_H5O_type_t]);
  H5Tinsert(dtype_id, "rc", HOFFSET(H5O_info_t, rc), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "atime", HOFFSET(H5O_info_t, atime), h5_datatype[DT_time_t]);
  H5Tinsert(dtype_id, "mtime", HOFFSET(H5O_info_t, mtime), h5_datatype[DT_time_t]);
  H5Tinsert(dtype_id, "ctime", HOFFSET(H5O_info_t, ctime), h5_datatype[DT_time_t]);
  H5Tinsert(dtype_id, "btime", HOFFSET(H5O_info_t, btime), h5_datatype[DT_time_t]);
  H5Tinsert(dtype_id, "num_attrs", HOFFSET(H5O_info_t, num_attrs), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "hdr", HOFFSET(H5O_info_t, hdr), h5_datatype[DT_H5O_hdr_info_t]);
  H5Tinsert(dtype_id, "meta_size", HOFFSET(H5O_info_t, meta_size), h5_datatype[DT_H5O_info_helper_t]);
  return(dtype_id);
}

/* typedef struct H5O_stat_t { hsize_t size; hsize_t free; unsigned nmesgs; unsigned nchunks} H5O_stat_t; */
hid_t create_DT_H5O_stat_t(void) {
  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(H5O_stat_t));
  H5Tinsert(dtype_id, "size", HOFFSET(H5O_stat_t, size), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "free", HOFFSET(H5O_stat_t, free), h5_datatype[DT_hsize_t]);
  H5Tinsert(dtype_id, "nmesgs", HOFFSET(H5O_stat_t, nmesgs), h5_datatype[DT_unsigned]);
  H5Tinsert(dtype_id, "nchunks", HOFFSET(H5O_stat_t, nchunks), h5_datatype[DT_unsigned]);
  return(dtype_id);
}


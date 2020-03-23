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



#ifndef _DATATYPE_EXPORT_H
#define _DATATYPE_EXPORT_H

#include "global.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "HelperStructs.h"

#define issigned(t) (((t)(-1)) < 0)

hid_t get_h5_equiv(int size, bool sign);
  

// initialize all the data types; to be called on package load from R
SEXP init_dtypes(void);
// create a dataframe with all type information
SEXP show_all_types_data_frame(void);

typedef enum {
  DT_H5T_IEEE_F32BE,
  DT_H5T_IEEE_F32LE,
  DT_H5T_IEEE_F64BE,
  DT_H5T_IEEE_F64LE,
  DT_H5T_STD_I8BE,
  DT_H5T_STD_I8LE,
  DT_H5T_STD_I16BE,
  DT_H5T_STD_I16LE,
  DT_H5T_STD_I32BE,
  DT_H5T_STD_I32LE,
  DT_H5T_STD_I64BE,
  DT_H5T_STD_I64LE,
  DT_H5T_STD_U8BE,
  DT_H5T_STD_U8LE,
  DT_H5T_STD_U16BE,
  DT_H5T_STD_U16LE,
  DT_H5T_STD_U32BE,
  DT_H5T_STD_U32LE,
  DT_H5T_STD_U64BE,
  DT_H5T_STD_U64LE,
  DT_H5T_STD_B8BE,
  DT_H5T_STD_B8LE,
  DT_H5T_STD_B16BE,
  DT_H5T_STD_B16LE,
  DT_H5T_STD_B32BE,
  DT_H5T_STD_B32LE,
  DT_H5T_STD_B64BE,
  DT_H5T_STD_B64LE,
  DT_H5T_STD_REF_OBJ,
  DT_H5T_STD_REF_DSETREG,
  DT_H5T_STD_REF,
  DT_H5T_UNIX_D32BE,
  DT_H5T_UNIX_D32LE,
  DT_H5T_UNIX_D64BE,
  DT_H5T_UNIX_D64LE,
  DT_H5T_C_S1,
  DT_H5T_FORTRAN_S1,
  DT_H5T_INTEL_I8,
  DT_H5T_INTEL_I16,
  DT_H5T_INTEL_I32,
  DT_H5T_INTEL_I64,
  DT_H5T_INTEL_U8,
  DT_H5T_INTEL_U16,
  DT_H5T_INTEL_U32,
  DT_H5T_INTEL_U64,
  DT_H5T_INTEL_B8,
  DT_H5T_INTEL_B16,
  DT_H5T_INTEL_B32,
  DT_H5T_INTEL_B64,
  DT_H5T_INTEL_F32,
  DT_H5T_INTEL_F64,
  DT_H5T_ALPHA_I8,
  DT_H5T_ALPHA_I16,
  DT_H5T_ALPHA_I32,
  DT_H5T_ALPHA_I64,
  DT_H5T_ALPHA_U8,
  DT_H5T_ALPHA_U16,
  DT_H5T_ALPHA_U32,
  DT_H5T_ALPHA_U64,
  DT_H5T_ALPHA_B8,
  DT_H5T_ALPHA_B16,
  DT_H5T_ALPHA_B32,
  DT_H5T_ALPHA_B64,
  DT_H5T_ALPHA_F32,
  DT_H5T_ALPHA_F64,
  DT_H5T_MIPS_I8,
  DT_H5T_MIPS_I16,
  DT_H5T_MIPS_I32,
  DT_H5T_MIPS_I64,
  DT_H5T_MIPS_U8,
  DT_H5T_MIPS_U16,
  DT_H5T_MIPS_U32,
  DT_H5T_MIPS_U64,
  DT_H5T_MIPS_B8,
  DT_H5T_MIPS_B16,
  DT_H5T_MIPS_B32,
  DT_H5T_MIPS_B64,
  DT_H5T_MIPS_F32,
  DT_H5T_MIPS_F64,
  DT_H5T_VAX_F32,
  DT_H5T_VAX_F64,
  DT_H5T_NATIVE_CHAR,
  DT_H5T_NATIVE_SCHAR,
  DT_H5T_NATIVE_UCHAR,
  DT_H5T_NATIVE_SHORT,
  DT_H5T_NATIVE_USHORT,
  DT_H5T_NATIVE_INT,
  DT_H5T_NATIVE_UINT,
  DT_H5T_NATIVE_LONG,
  DT_H5T_NATIVE_ULONG,
  DT_H5T_NATIVE_LLONG,
  DT_H5T_NATIVE_ULLONG,
  DT_H5T_NATIVE_FLOAT,
  DT_H5T_NATIVE_DOUBLE,
  DT_H5T_NATIVE_B8,
  DT_H5T_NATIVE_B16,
  DT_H5T_NATIVE_B32,
  DT_H5T_NATIVE_B64,
  DT_H5T_NATIVE_OPAQUE,
  DT_H5T_NATIVE_HADDR,
  DT_H5T_NATIVE_HSIZE,
  DT_H5T_NATIVE_HSSIZE,
  DT_H5T_NATIVE_HERR,
  DT_H5T_NATIVE_HBOOL,
  DT_H5T_NATIVE_INT8,
  DT_H5T_NATIVE_UINT8,
  DT_H5T_NATIVE_INT_LEAST8,
  DT_H5T_NATIVE_UINT_LEAST8,
  DT_H5T_NATIVE_INT_FAST8,
  DT_H5T_NATIVE_UINT_FAST8,
  DT_H5T_NATIVE_INT16,
  DT_H5T_NATIVE_UINT16,
  DT_H5T_NATIVE_INT_LEAST16,
  DT_H5T_NATIVE_UINT_LEAST16,
  DT_H5T_NATIVE_INT_FAST16,
  DT_H5T_NATIVE_UINT_FAST16,
  DT_H5T_NATIVE_INT32,
  DT_H5T_NATIVE_UINT32,
  DT_H5T_NATIVE_INT_LEAST32,
  DT_H5T_NATIVE_UINT_LEAST32,
  DT_H5T_NATIVE_INT_FAST32,
  DT_H5T_NATIVE_UINT_FAST32,
  DT_H5T_NATIVE_INT64,
  DT_H5T_NATIVE_UINT64,
  DT_H5T_NATIVE_INT_LEAST64,
  DT_H5T_NATIVE_UINT_LEAST64,
  DT_H5T_NATIVE_INT_FAST64,
  DT_H5T_NATIVE_UINT_FAST64,
  DT_H5E_major_t,
  DT_H5E_minor_t,
  DT_H5FD_mem_t,
  DT_H5G_link_t,
  DT_H5O_msg_crt_idx_t,
  DT_H5Z_filter_t,
  DT_haddr_t,
  DT_hbool_t,
  DT_herr_t,
  DT_hid_t,
  DT_hsize_t,
  DT_hssize_t,
  DT_htri_t,
  DT_int,
  DT_int64_t,
  DT_long,
  DT_long_int,
  DT_long_long,
  DT_off_t,
  DT_short,
  DT_size_t,
  DT_ssize_t,
  DT_time_t,
  DT_uint32_t,
  DT_uint64_t,
  DT_uint8_t,
  DT_unsigned,
  DT_unsigned_char,
  DT_unsigned_int,
  DT_unsigned_long,
  DT_unsigned_long_long,
  DT_unsigned_short,
  DT_char,
  DT_double,
  DT_float,
  DT_H5_index_t,
  DT_H5_iter_order_t,
  DT_H5C_cache_decr_mode,
  DT_H5C_cache_flash_incr_mode,
  DT_H5C_cache_incr_mode,
  DT_H5D_alloc_time_t,
  DT_H5D_chunk_index_t,
  DT_H5D_fill_time_t,
  DT_H5D_fill_value_t,
  DT_H5D_layout_t,
  DT_H5D_mpio_actual_chunk_opt_mode_t,
  DT_H5D_mpio_actual_io_mode_t,
  DT_H5D_mpio_no_collective_cause_t,
  DT_H5D_space_status_t,
  DT_H5D_vds_view_t,
  DT_H5E_direction_t,
  DT_H5E_type_t,
  DT_H5ES_status_t,
  DT_H5F_close_degree_t,
  DT_H5F_file_space_type_t,
  DT_H5F_fspace_strategy_t,
  DT_H5F_libver_t,
  DT_H5F_mem_t,
  DT_H5F_scope_t,
  DT_H5FD_file_image_op_t,
  DT_H5G_obj_t,
  DT_H5G_storage_type_t,
  DT_H5I_type_t,
  DT_H5L_type_t,
  DT_H5LT_lang_t,
  DT_H5O_mcdt_search_ret_t,
  DT_H5O_type_t,
  DT_H5PL_type_t,
  DT_H5R_type_t,
  DT_H5S_class_t,
  DT_H5S_sel_type,
  DT_H5S_seloper_t,
  DT_H5T_bkg_t,
  DT_H5T_class_t,
  DT_H5T_cmd_t,
  DT_H5T_conv_except_t,
  DT_H5T_conv_ret_t,
  DT_H5T_cset_t,
  DT_H5T_direction_t,
  DT_H5T_norm_t,
  DT_H5T_order_t,
  DT_H5T_pad_t,
  DT_H5T_pers_t,
  DT_H5T_sign_t,
  DT_H5T_str_t,
  DT_H5VL_map_get_t,
  DT_H5VL_map_specific_t,
  DT_H5Z_cb_return_t,
  DT_H5Z_EDC_t,
  DT_H5Z_SO_scale_type_t,
  DT_H5L_info1_helper_t,
  DT_H5L_info2_helper_t,
  DT_H5_ih_info_t,
  DT_H5A_info_t,
  DT_H5AC_cache_config_t,
  DT_H5AC_cache_image_config_t,
  DT_H5D_info_t,
  DT_H5E_error1_t,
  DT_H5E_error2_t,
  DT_H5F_info1_helper_t,
  DT_H5F_info1_t,
  DT_H5F_info2_free_t,
  DT_H5F_info2_sohm_t,
  DT_H5F_info2_super_t,
  DT_H5F_info2_t,
  DT_H5F_retry_info_t,
  DT_H5F_sect_info_t,
  DT_H5G_info_t,
  DT_H5L_info1_t,
  DT_H5L_info2_t,
  DT_H5ls_info_t,
  DT_H5O_hdr_info_helper_msg_t,
  DT_H5O_hdr_info_helper_space_t,
  DT_H5O_hdr_info_t,
  DT_H5O_info_helper_t,
  DT_H5O_info1_t,
  DT_H5O_info2_t,
  DT_H5O_native_info_t,
  DT_H5O_stat_t,
  DT_H5O_token_t,
  DT_H5R_ref_helper_t,
  DT_H5R_ref_t,
  DT_hdset_reg_ref_t,
#if H5_SIZEOF_LONG_DOUBLE !=0
  DT_H5T_NATIVE_LDOUBLE,
#endif
  DT_LAST_ITEM
} DT_enum;


extern hid_t h5_datatype[DT_LAST_ITEM];



/*************************************************************************
 * 
 * Enums
 * 
 *************************************************************************/

/* typedef enum H5_index_t { H5_INDEX_UNKNOWN = -1, H5_INDEX_NAME, H5_INDEX_CRT_ORDER, H5_INDEX_N } H5_index_t; */
hid_t create_DT_H5_index_t(void);

/* typedef enum { H5_ITER_UNKNOWN = -1, H5_ITER_INC, H5_ITER_DEC, H5_ITER_NATIVE, H5_ITER_N } H5_iter_order_t; */
hid_t create_DT_H5_iter_order_t(void);

/* typedef enum H5C_cache_decr_mode{ H5C_decr__off, H5C_decr__threshold, H5C_decr__age_out, H5C_decr__age_out_with_threshold} H5C_cache_decr_mode; */
hid_t create_DT_H5C_cache_decr_mode(void);

/* typedef enum H5C_cache_flash_incr_mode{ H5C_flash_incr__off, H5C_flash_incr__add_space} H5C_cache_flash_incr_mode; */
hid_t create_DT_H5C_cache_flash_incr_mode(void);

/* typedef enum H5C_cache_incr_mode{ H5C_incr__off, H5C_incr__threshold} H5C_cache_incr_mode; */
hid_t create_DT_H5C_cache_incr_mode(void);

/* typedef enum H5D_alloc_time_t { H5D_ALLOC_TIME_ERROR = -1, H5D_ALLOC_TIME_DEFAULT = 0, H5D_ALLOC_TIME_EARLY = 1, H5D_ALLOC_TIME_LATE = 2, H5D_ALLOC_TIME_INCR = 3} H5D_alloc_time_t; */
hid_t create_DT_H5D_alloc_time_t(void);

/* typedef enum H5D_chunk_index_t { H5D_CHUNK_IDX_BTREE = 0, H5D_CHUNK_IDX_SINGLE = 1, H5D_CHUNK_IDX_NONE = 2, H5D_CHUNK_IDX_FARRAY = 3, H5D_CHUNK_IDX_EARRAY = 4, H5D_CHUNK_IDX_BT2 = 5, H5D_CHUNK_IDX_NTYPES } H5D_chunk_index_t; */
hid_t create_DT_H5D_chunk_index_t(void);

/* typedef enum H5D_fill_time_t { H5D_FILL_TIME_ERROR = -1, H5D_FILL_TIME_ALLOC = 0, H5D_FILL_TIME_NEVER = 1, H5D_FILL_TIME_IFSET = 2} H5D_fill_time_t; */
hid_t create_DT_H5D_fill_time_t(void);

/* typedef enum H5D_fill_value_t { H5D_FILL_VALUE_ERROR =-1, H5D_FILL_VALUE_UNDEFINED =0, H5D_FILL_VALUE_DEFAULT =1, H5D_FILL_VALUE_USER_DEFINED =2} H5D_fill_value_t; */
hid_t create_DT_H5D_fill_value_t(void);

/* typedef enum H5D_layout_t { H5D_LAYOUT_ERROR = -1, H5D_COMPACT = 0, H5D_CONTIGUOUS = 1, H5D_CHUNKED = 2, H5D_VIRTUAL = 3, H5D_NLAYOUTS = 4 } H5D_layout_t; */
hid_t create_DT_H5D_layout_t(void);

/* typedef enum H5D_mpio_actual_chunk_opt_mode_t { H5D_MPIO_NO_CHUNK_OPTIMIZATION = 0, H5D_MPIO_LINK_CHUNK, H5D_MPIO_MULTI_CHUNK} H5D_mpio_actual_chunk_opt_mode_t; */
hid_t create_DT_H5D_mpio_actual_chunk_opt_mode_t(void);

/* typedef enum H5D_mpio_actual_io_mode_t { H5D_MPIO_NO_COLLECTIVE = 0x0, H5D_MPIO_CHUNK_INDEPENDENT = 0x1, H5D_MPIO_CHUNK_COLLECTIVE = 0x2, H5D_MPIO_CHUNK_MIXED = 0x1 | 0x2, H5D_MPIO_CONTIGUOUS_COLLECTIVE = 0x4} H5D_mpio_actual_io_mode_t; */
hid_t create_DT_H5D_mpio_actual_io_mode_t(void);

/* typedef enum H5D_mpio_no_collective_cause_t { H5D_MPIO_COLLECTIVE = 0x00, H5D_MPIO_SET_INDEPENDENT = 0x01, H5D_MPIO_DATATYPE_CONVERSION = 0x02, H5D_MPIO_DATA_TRANSFORMS = 0x04, H5D_MPIO_MPI_OPT_TYPES_ENV_VAR_DISABLED = 0x08, H5D_MPIO_NOT_SIMPLE_OR_SCALAR_DATASPACES = 0x10, H5D_MPIO_NOT_CONTIGUOUS_OR_CHUNKED_DATASET = 0x20, H5D_MPIO_PARALLEL_FILTERED_WRITES_DISABLED = 0x40, H5D_MPIO_ERROR_WHILE_CHECKING_COLLECTIVE_POSSIBLE = 0x80, H5D_MPIO_NO_COLLECTIVE_MAX_CAUSE = 0x100} H5D_mpio_no_collective_cause_t; */
hid_t create_DT_H5D_mpio_no_collective_cause_t(void);

/* typedef enum H5D_space_status_t { H5D_SPACE_STATUS_ERROR = -1, H5D_SPACE_STATUS_NOT_ALLOCATED = 0, H5D_SPACE_STATUS_PART_ALLOCATED = 1, H5D_SPACE_STATUS_ALLOCATED = 2} H5D_space_status_t; */
hid_t create_DT_H5D_space_status_t(void);

/* typedef enum H5D_vds_view_t { H5D_VDS_ERROR = -1, H5D_VDS_FIRST_MISSING = 0, H5D_VDS_LAST_AVAILABLE = 1} H5D_vds_view_t; */
hid_t create_DT_H5D_vds_view_t(void);

/* typedef enum H5E_direction_t { H5E_WALK_UPWARD = 0, H5E_WALK_DOWNWARD = 1 } H5E_direction_t; */
hid_t create_DT_H5E_direction_t(void);

/* typedef enum H5E_type_t { H5E_MAJOR, H5E_MINOR} H5E_type_t; */
hid_t create_DT_H5E_type_t(void);

/* typedef enum H5ES_status_t { H5ES_STATUS_IN_PROGRESS, H5ES_STATUS_SUCCEED, H5ES_STATUS_FAIL, H5ES_STATUS_CANCELED } H5ES_status_t; */
hid_t create_DT_H5ES_status_t(void);

/* typedef enum H5F_close_degree_t { H5F_CLOSE_DEFAULT = 0, H5F_CLOSE_WEAK = 1, H5F_CLOSE_SEMI = 2, H5F_CLOSE_STRONG = 3} H5F_close_degree_t; */
hid_t create_DT_H5F_close_degree_t(void);

/* typedef enum H5F_file_space_type_t { H5F_FILE_SPACE_DEFAULT = 0, H5F_FILE_SPACE_ALL_PERSIST = 1, H5F_FILE_SPACE_ALL = 2, H5F_FILE_SPACE_AGGR_VFD = 3, H5F_FILE_SPACE_VFD = 4, H5F_FILE_SPACE_NTYPES } H5F_file_space_type_t; */
hid_t create_DT_H5F_file_space_type_t(void);

/* typedef enum H5F_fspace_strategy_t { H5F_FSPACE_STRATEGY_FSM_AGGR = 0, H5F_FSPACE_STRATEGY_PAGE = 1, H5F_FSPACE_STRATEGY_AGGR = 2, H5F_FSPACE_STRATEGY_NONE = 3, H5F_FSPACE_STRATEGY_NTYPES } H5F_fspace_strategy_t; */
hid_t create_DT_H5F_fspace_strategy_t(void);

/* typedef enum H5F_libver_t { H5F_LIBVER_ERROR = -1, H5F_LIBVER_EARLIEST = 0, H5F_LIBVER_V18 = 1, H5F_LIBVER_V110 = 2, H5F_LIBVER_V112 = 3, H5F_LIBVER_NBOUNDS} H5F_libver_t; */
hid_t create_DT_H5F_libver_t(void);

/* typedef enum H5F_mem_t { H5FD_MEM_NOLIST = -1, H5FD_MEM_DEFAULT = 0, H5FD_MEM_SUPER = 1, H5FD_MEM_BTREE = 2, H5FD_MEM_DRAW = 3, H5FD_MEM_GHEAP = 4, H5FD_MEM_LHEAP = 5, H5FD_MEM_OHDR = 6, H5FD_MEM_NTYPES } H5F_mem_t; */
hid_t create_DT_H5F_mem_t(void);

/* typedef enum H5F_scope_t { H5F_SCOPE_LOCAL = 0, H5F_SCOPE_GLOBAL = 1 } H5F_scope_t; */
hid_t create_DT_H5F_scope_t(void);

/* typedef enum { H5FD_FILE_IMAGE_OP_NO_OP, H5FD_FILE_IMAGE_OP_PROPERTY_LIST_SET, H5FD_FILE_IMAGE_OP_PROPERTY_LIST_COPY, H5FD_FILE_IMAGE_OP_PROPERTY_LIST_GET, H5FD_FILE_IMAGE_OP_PROPERTY_LIST_CLOSE, H5FD_FILE_IMAGE_OP_FILE_OPEN, H5FD_FILE_IMAGE_OP_FILE_RESIZE, H5FD_FILE_IMAGE_OP_FILE_CLOSE} H5FD_file_image_op_t; */
hid_t create_DT_H5FD_file_image_op_t(void);

/* typedef enum H5G_obj_t { H5G_UNKNOWN = -1, H5G_GROUP, H5G_DATASET, H5G_TYPE, H5G_LINK, H5G_UDLINK, H5G_RESERVED_5, H5G_RESERVED_6, H5G_RESERVED_7 } H5G_obj_t; */
hid_t create_DT_H5G_obj_t(void);

/* typedef enum H5G_storage_type_t { H5G_STORAGE_TYPE_UNKNOWN = -1, H5G_STORAGE_TYPE_SYMBOL_TABLE, H5G_STORAGE_TYPE_COMPACT, H5G_STORAGE_TYPE_DENSE } H5G_storage_type_t; */
hid_t create_DT_H5G_storage_type_t(void);

/* typedef enum H5I_type_t { H5I_UNINIT = (-2), H5I_BADID = (-1), H5I_FILE = 1, H5I_GROUP, H5I_DATATYPE, H5I_DATASPACE, H5I_DATASET, H5I_MAP, H5I_ATTR, H5I_VFL, H5I_VOL, H5I_GENPROP_CLS, H5I_GENPROP_LST, H5I_ERROR_CLASS, H5I_ERROR_MSG, H5I_ERROR_STACK, H5I_SPACE_SEL_ITER, H5I_NTYPES } H5I_type_t; */
hid_t create_DT_H5I_type_t(void);

/* typedef enum { H5L_TYPE_ERROR = (-1), H5L_TYPE_HARD = 0, H5L_TYPE_SOFT = 1, H5L_TYPE_EXTERNAL = 64, H5L_TYPE_MAX = 255 } H5L_type_t; */
hid_t create_DT_H5L_type_t(void);

/* typedef enum H5LT_lang_t { H5LT_LANG_ERR = -1, H5LT_DDL = 0, H5LT_C = 1, H5LT_FORTRAN = 2, H5LT_NO_LANG = 3 } H5LT_lang_t; */
hid_t create_DT_H5LT_lang_t(void);

/* typedef enum H5O_mcdt_search_ret_t { H5O_MCDT_SEARCH_ERROR = -1, H5O_MCDT_SEARCH_CONT, H5O_MCDT_SEARCH_STOP } H5O_mcdt_search_ret_t; */
hid_t create_DT_H5O_mcdt_search_ret_t(void);

/* typedef enum H5O_type_t { H5O_TYPE_UNKNOWN = -1, H5O_TYPE_GROUP, H5O_TYPE_DATASET, H5O_TYPE_NAMED_DATATYPE, H5O_TYPE_MAP, H5O_TYPE_NTYPES } H5O_type_t; */
hid_t create_DT_H5O_type_t(void);

/* typedef enum H5PL_type_t { H5PL_TYPE_ERROR = -1, H5PL_TYPE_FILTER = 0, H5PL_TYPE_VOL = 1, H5PL_TYPE_NONE = 2 } H5PL_type_t; */
hid_t create_DT_H5PL_type_t(void);

/* typedef enum { H5R_BADTYPE = (-1), H5R_OBJECT1 = 0, H5R_DATASET_REGION1 = 1, H5R_OBJECT2 = 2, H5R_DATASET_REGION2 = 3, H5R_ATTR = 4, H5R_MAXTYPE = 5 } H5R_type_t; */
hid_t create_DT_H5R_type_t(void);

/* typedef enum H5S_class_t { H5S_NO_CLASS = -1, H5S_SCALAR = 0, H5S_SIMPLE = 1, H5S_NULL = 2 } H5S_class_t; */
hid_t create_DT_H5S_class_t(void);

/* typedef enum { H5S_SEL_ERROR = -1, H5S_SEL_NONE = 0, H5S_SEL_POINTS = 1, H5S_SEL_HYPERSLABS = 2, H5S_SEL_ALL = 3, H5S_SEL_N } H5S_sel_type; */
hid_t create_DT_H5S_sel_type(void);

/* typedef enum H5S_seloper_t { H5S_SELECT_NOOP = -1, H5S_SELECT_SET = 0, H5S_SELECT_OR, H5S_SELECT_AND, H5S_SELECT_XOR, H5S_SELECT_NOTB, H5S_SELECT_NOTA, H5S_SELECT_APPEND, H5S_SELECT_PREPEND, H5S_SELECT_INVALID } H5S_seloper_t; */
hid_t create_DT_H5S_seloper_t(void);

/* typedef enum H5T_bkg_t { H5T_BKG_NO = 0, H5T_BKG_TEMP = 1, H5T_BKG_YES = 2 } H5T_bkg_t; */
hid_t create_DT_H5T_bkg_t(void);

/* typedef enum H5T_class_t { H5T_NO_CLASS = -1, H5T_INTEGER = 0, H5T_FLOAT = 1, H5T_TIME = 2, H5T_STRING = 3, H5T_BITFIELD = 4, H5T_OPAQUE = 5, H5T_COMPOUND = 6, H5T_REFERENCE = 7, H5T_ENUM = 8, H5T_VLEN = 9, H5T_ARRAY = 10, H5T_NCLASSES } H5T_class_t; */
hid_t create_DT_H5T_class_t(void);

/* typedef enum H5T_cmd_t { H5T_CONV_INIT = 0, H5T_CONV_CONV = 1, H5T_CONV_FREE = 2 } H5T_cmd_t; */
hid_t create_DT_H5T_cmd_t(void);

/* typedef enum H5T_conv_except_t { H5T_CONV_EXCEPT_RANGE_HI = 0, H5T_CONV_EXCEPT_RANGE_LOW = 1, H5T_CONV_EXCEPT_PRECISION = 2, H5T_CONV_EXCEPT_TRUNCATE = 3, H5T_CONV_EXCEPT_PINF = 4, H5T_CONV_EXCEPT_NINF = 5, H5T_CONV_EXCEPT_NAN = 6 } H5T_conv_except_t; */
hid_t create_DT_H5T_conv_except_t(void);

/* typedef enum H5T_conv_ret_t { H5T_CONV_ABORT = -1, H5T_CONV_UNHANDLED = 0, H5T_CONV_HANDLED = 1 } H5T_conv_ret_t; */
hid_t create_DT_H5T_conv_ret_t(void);

/* typedef enum H5T_cset_t { H5T_CSET_ERROR = -1, H5T_CSET_ASCII = 0, H5T_CSET_UTF8 = 1, H5T_CSET_RESERVED_2 = 2, H5T_CSET_RESERVED_3 = 3, H5T_CSET_RESERVED_4 = 4, H5T_CSET_RESERVED_5 = 5, H5T_CSET_RESERVED_6 = 6, H5T_CSET_RESERVED_7 = 7, H5T_CSET_RESERVED_8 = 8, H5T_CSET_RESERVED_9 = 9, H5T_CSET_RESERVED_10 = 10, H5T_CSET_RESERVED_11 = 11, H5T_CSET_RESERVED_12 = 12, H5T_CSET_RESERVED_13 = 13, H5T_CSET_RESERVED_14 = 14, H5T_CSET_RESERVED_15 = 15 } H5T_cset_t; */
hid_t create_DT_H5T_cset_t(void);

/* typedef enum H5T_direction_t { H5T_DIR_DEFAULT = 0, H5T_DIR_ASCEND = 1, H5T_DIR_DESCEND = 2 } H5T_direction_t; */
hid_t create_DT_H5T_direction_t(void);

/* typedef enum H5T_norm_t { H5T_NORM_ERROR = -1, H5T_NORM_IMPLIED = 0, H5T_NORM_MSBSET = 1, H5T_NORM_NONE = 2 } H5T_norm_t; */
hid_t create_DT_H5T_norm_t(void);

/* typedef enum H5T_order_t { H5T_ORDER_ERROR = -1, H5T_ORDER_LE = 0, H5T_ORDER_BE = 1, H5T_ORDER_VAX = 2, H5T_ORDER_MIXED = 3, H5T_ORDER_NONE = 4 } H5T_order_t; */
hid_t create_DT_H5T_order_t(void);

/* typedef enum H5T_pad_t { H5T_PAD_ERROR = -1, H5T_PAD_ZERO = 0, H5T_PAD_ONE = 1, H5T_PAD_BACKGROUND = 2, H5T_NPAD = 3 } H5T_pad_t; */
hid_t create_DT_H5T_pad_t(void);

/* typedef enum H5T_pers_t { H5T_PERS_DONTCARE = -1, H5T_PERS_HARD = 0, H5T_PERS_SOFT = 1 } H5T_pers_t; */
hid_t create_DT_H5T_pers_t(void);

/* typedef enum H5T_sign_t { H5T_SGN_ERROR = -1, H5T_SGN_NONE = 0, H5T_SGN_2 = 1, H5T_NSGN = 2 } H5T_sign_t; */
hid_t create_DT_H5T_sign_t(void);

/* typedef enum H5T_str_t { H5T_STR_ERROR = -1, H5T_STR_NULLTERM = 0, H5T_STR_NULLPAD = 1, H5T_STR_SPACEPAD = 2, H5T_STR_RESERVED_3 = 3, H5T_STR_RESERVED_4 = 4, H5T_STR_RESERVED_5 = 5, H5T_STR_RESERVED_6 = 6, H5T_STR_RESERVED_7 = 7, H5T_STR_RESERVED_8 = 8, H5T_STR_RESERVED_9 = 9, H5T_STR_RESERVED_10 = 10, H5T_STR_RESERVED_11 = 11, H5T_STR_RESERVED_12 = 12, H5T_STR_RESERVED_13 = 13, H5T_STR_RESERVED_14 = 14, H5T_STR_RESERVED_15 = 15 } H5T_str_t; */
hid_t create_DT_H5T_str_t(void);

/* typedef enum H5VL_map_get_t { H5VL_MAP_GET_MAPL, H5VL_MAP_GET_MCPL, H5VL_MAP_GET_KEY_TYPE, H5VL_MAP_GET_VAL_TYPE, H5VL_MAP_GET_COUNT } H5VL_map_get_t; */
hid_t create_DT_H5VL_map_get_t(void);

/* typedef enum H5VL_map_specific_t { H5VL_MAP_ITER, H5VL_MAP_DELETE } H5VL_map_specific_t; */
hid_t create_DT_H5VL_map_specific_t(void);

/* typedef enum H5Z_cb_return_t { H5Z_CB_ERROR = -1, H5Z_CB_FAIL = 0, H5Z_CB_CONT = 1, H5Z_CB_NO = 2} H5Z_cb_return_t; */
hid_t create_DT_H5Z_cb_return_t(void);

/* typedef enum H5Z_EDC_t { H5Z_ERROR_EDC = -1, H5Z_DISABLE_EDC = 0, H5Z_ENABLE_EDC = 1, H5Z_NO_EDC = 2 } H5Z_EDC_t; */
hid_t create_DT_H5Z_EDC_t(void);

/* typedef enum H5Z_SO_scale_type_t { H5Z_SO_FLOAT_DSCALE = 0, H5Z_SO_FLOAT_ESCALE = 1, H5Z_SO_INT = 2} H5Z_SO_scale_type_t; */
hid_t create_DT_H5Z_SO_scale_type_t(void);

/*************************************************************************
 * 
 * Structs
 * 
 *************************************************************************/

/* typedef struct H5_ih_info_t { hsize_t index_size; hsize_t heap_size} H5_ih_info_t; */
hid_t create_DT_H5_ih_info_t(void);

/* typedef struct { hbool_t corder_valid; H5O_msg_crt_idx_t corder; H5T_cset_t cset; hsize_t data_size} H5A_info_t; */
hid_t create_DT_H5A_info_t(void);

/* typedef struct H5AC_cache_config_t{ int version; hbool_t rpt_fcn_enabled; hbool_t open_trace_file; hbool_t close_trace_file; char trace_file_name[H5AC__MAX_TRACE_FILE_NAME_LEN + 1]; hbool_t evictions_enabled; hbool_t set_initial_size; size_t initial_size; double min_clean_fraction; size_t max_size; size_t min_size; long int epoch_length; enum H5C_cache_incr_mode incr_mode; double lower_hr_threshold; double increment; hbool_t apply_max_increment; size_t max_increment; enum H5C_cache_flash_incr_mode flash_incr_mode; double flash_multiple; double flash_threshold; enum H5C_cache_decr_mode decr_mode; double upper_hr_threshold; double decrement; hbool_t apply_max_decrement; size_t max_decrement; int epochs_before_eviction; hbool_t apply_empty_reserve; double empty_reserve; size_t dirty_bytes_threshold; int metadata_write_strategy} H5AC_cache_config_t; */
hid_t create_DT_H5AC_cache_config_t(void);

/* typedef struct H5AC_cache_image_config_t { int version; hbool_t generate_image; hbool_t save_resize_status; int entry_ageout} H5AC_cache_image_config_t; */
hid_t create_DT_H5AC_cache_image_config_t(void);

/* typedef struct H5D_info_t { int rank; char* dims; char* maxdims; H5T_class_t type_class; H5S_class_t space_class} H5D_info_t; */
hid_t create_DT_H5D_info_t(void);

/* typedef struct H5E_error1_t { H5E_major_t maj_num; H5E_minor_t min_num; const char *func_name; const char *file_name; unsigned line; const char *desc} H5E_error1_t; */
hid_t create_DT_H5E_error1_t(void);

/* typedef struct H5E_error2_t { hid_t cls_id; hid_t maj_num; hid_t min_num; unsigned line; const char *func_name; const char *file_name; const char *desc} H5E_error2_t; */
hid_t create_DT_H5E_error2_t(void);

/* typedef struct H5F_info1_helper_t { hsize_t hdr_size; H5_ih_info_t msgs_info} H5F_info1_helper_t; */
hid_t create_DT_H5F_info1_helper_t(void);

/* typedef struct H5F_info1_t { hsize_t super_ext_size; H5F_info1_helper_t sohm} H5F_info1_t; */
hid_t create_DT_H5F_info1_t(void);

/* typedef struct H5F_info2_free_t { unsigned version; hsize_t meta_size; hsize_t tot_space} H5F_info2_free_t; */
hid_t create_DT_H5F_info2_free_t(void);

/* typedef struct H5F_info2_sohm_t { unsigned version; hsize_t hdr_size; H5_ih_info_t msgs_info} H5F_info2_sohm_t; */
hid_t create_DT_H5F_info2_sohm_t(void);

/* typedef struct H5F_info2_super_t { unsigned version; hsize_t super_size; hsize_t super_ext_size} H5F_info2_super_t; */
hid_t create_DT_H5F_info2_super_t(void);

/* typedef struct H5F_info2_t { H5F_info2_super_t super; H5F_info2_free_t free; H5F_info2_sohm_t sohm} H5F_info2_t; */
hid_t create_DT_H5F_info2_t(void);

/* typedef struct H5F_retry_info_t { unsigned nbins; uint32_t *retries[H5F_NUM_METADATA_READ_RETRY_TYPES]} H5F_retry_info_t; */
hid_t create_DT_H5F_retry_info_t(void);

/* typedef struct H5F_sect_info_t { haddr_t addr; hsize_t size} H5F_sect_info_t; */
hid_t create_DT_H5F_sect_info_t(void);

/* typedef struct H5G_info_t { H5G_storage_type_t storage_type; hsize_t nlinks; int64_t max_corder; hbool_t mounted} H5G_info_t; */
hid_t create_DT_H5G_info_t(void);

/* typedef union H5L_info1_helper_t { haddr_t address; size_t val_size} H5L_info1_helper_t; */
hid_t create_DT_H5L_info1_helper_t(void);

/* typedef struct H5L_info1_t { H5L_type_t type; hbool_t corder_valid; int64_t corder; H5T_cset_t cset; H5L_info1_helper_t u} H5L_info1_t; */
hid_t create_DT_H5L_info1_t(void);

/* typedef union H5L_info2_helper_t { H5O_token_t token; size_t val_size} H5L_info2_helper_t; */
hid_t create_DT_H5L_info2_helper_t(void);

/* typedef struct H5L_info2_t { H5L_type_t type; hbool_t corder_valid; int64_t corder; H5T_cset_t cset; H5L_info2_helper_t u} H5L_info2_t; */
hid_t create_DT_H5L_info2_t(void);

/* typedef struct H5ls_info_t { char* name; int link_success; H5L_info1_t link; int obj_type_success; H5I_type_t obj_type; int num_attrs; int group_success; H5G_info_t group; int dataset_success; H5D_info_t dataset; int type_success; H5T_class_t committed_type} H5ls_info_t; */
hid_t create_DT_H5ls_info_t(void);

/* typedef struct H5O_hdr_info_helper_msg_t { uint64_t present; uint64_t shared} H5O_hdr_info_helper_msg_t; */
hid_t create_DT_H5O_hdr_info_helper_msg_t(void);

/* typedef struct H5O_hdr_info_helper_space_t { hsize_t total; hsize_t meta; hsize_t mesg; hsize_t free} H5O_hdr_info_helper_space_t; */
hid_t create_DT_H5O_hdr_info_helper_space_t(void);

/* typedef struct H5O_hdr_info_t { unsigned version; unsigned nmesgs; unsigned nchunks; unsigned flags; H5O_hdr_info_helper_space_t space; H5O_hdr_info_helper_msg_t mesg} H5O_hdr_info_t; */
hid_t create_DT_H5O_hdr_info_t(void);

/* typedef struct H5O_info_helper_t { H5_ih_info_t obj; H5_ih_info_t attr} H5O_info_helper_t; */
hid_t create_DT_H5O_info_helper_t(void);

/* typedef struct H5O_info1_t { unsigned long fileno; haddr_t addr; H5O_type_t type; unsigned rc; time_t atime; time_t mtime; time_t ctime; time_t btime; hsize_t num_attrs; H5O_hdr_info_t hdr; H5O_info_helper_t meta_size} H5O_info1_t; */
hid_t create_DT_H5O_info1_t(void);

/* typedef struct H5O_info2_t { unsigned long fileno; H5O_token_t token; H5O_type_t type; unsigned rc; time_t atime; time_t mtime; time_t ctime; time_t btime; hsize_t num_attrs} H5O_info2_t; */
hid_t create_DT_H5O_info2_t(void);

/* typedef struct H5O_native_info_t { H5O_hdr_info_t hdr; H5O_info_helper_t meta_size} H5O_native_info_t; */
hid_t create_DT_H5O_native_info_t(void);

/* typedef struct H5O_stat_t { hsize_t size; hsize_t free; unsigned nmesgs; unsigned nchunks} H5O_stat_t; */
hid_t create_DT_H5O_stat_t(void);

/* typedef struct H5O_token_t { uint8_t __data[H5O_MAX_TOKEN_SIZE]} H5O_token_t; */
hid_t create_DT_H5O_token_t(void);

/* typedef struct H5R_ref_helper_t { uint64_t part0; uint64_t part1; uint64_t part2; uint64_t part3; uint64_t part4; uint64_t part5; uint64_t part6; uint64_t part7} H5R_ref_helper_t; */
hid_t create_DT_H5R_ref_helper_t(void);

/* typedef struct H5R_ref_t { H5R_ref_helper_t u} H5R_ref_t; */
hid_t create_DT_H5R_ref_t(void);

/* typedef struct { uint8_t __data[H5R_DSET_REG_REF_BUF_SIZE]} hdset_reg_ref_t; */
hid_t create_DT_hdset_reg_ref_t(void);



#endif

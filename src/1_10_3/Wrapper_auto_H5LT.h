#ifndef _WRAPPER_AUTO_H5LT_H_
#define _WRAPPER_AUTO_H5LT_H_
#include "global.h"
/* H5_HLDLL herr_t H5LTdtype_to_text(hid_t dtype, char *str, H5LT_lang_t lang_type, size_t *len); */
SEXP R_H5LTdtype_to_text(SEXP R_dtype, SEXP R_str, SEXP R_lang_type, SEXP R_len);
/* H5_HLDLL herr_t H5LTfind_attribute( hid_t loc_id, const char *name ); */
SEXP R_H5LTfind_attribute(SEXP R_loc_id, SEXP R_name);
/* H5_HLDLL herr_t H5LTfind_dataset( hid_t loc_id, const char *name ); */
SEXP R_H5LTfind_dataset(SEXP R_loc_id, SEXP R_name);
/* H5_HLDLL herr_t H5LTget_attribute( hid_t loc_id, const char *obj_name, const char *attr_name, hid_t mem_type_id, void *data ); */
SEXP R_H5LTget_attribute(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_mem_type_id, SEXP R_data, SEXP _dupl_data);
/* H5_HLDLL herr_t H5LTget_attribute_char( hid_t loc_id, const char *obj_name, const char *attr_name, char *data ); */
SEXP R_H5LTget_attribute_char(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_attribute_double( hid_t loc_id, const char *obj_name, const char *attr_name, double *data ); */
SEXP R_H5LTget_attribute_double(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_attribute_float( hid_t loc_id, const char *obj_name, const char *attr_name, float *data ); */
SEXP R_H5LTget_attribute_float(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_attribute_info( hid_t loc_id, const char *obj_name, const char *attr_name, hsize_t *dims, H5T_class_t *type_class, size_t *type_size ); */
SEXP R_H5LTget_attribute_info(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_dims, SEXP R_type_class, SEXP R_type_size);
/* H5_HLDLL herr_t H5LTget_attribute_int( hid_t loc_id, const char *obj_name, const char *attr_name, int *data ); */
SEXP R_H5LTget_attribute_int(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_attribute_long( hid_t loc_id, const char *obj_name, const char *attr_name, long *data ); */
SEXP R_H5LTget_attribute_long(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_attribute_long_long( hid_t loc_id, const char *obj_name, const char *attr_name, long long *data ); */
SEXP R_H5LTget_attribute_long_long(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_attribute_ndims( hid_t loc_id, const char *obj_name, const char *attr_name, int *rank ); */
SEXP R_H5LTget_attribute_ndims(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_rank);
/* H5_HLDLL herr_t H5LTget_attribute_short( hid_t loc_id, const char *obj_name, const char *attr_name, short *data ); */
SEXP R_H5LTget_attribute_short(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_attribute_string( hid_t loc_id, const char *obj_name, const char *attr_name, char *data ); */
SEXP R_H5LTget_attribute_string(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_attribute_uchar( hid_t loc_id, const char *obj_name, const char *attr_name, unsigned char *data ); */
SEXP R_H5LTget_attribute_uchar(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_attribute_uint( hid_t loc_id, const char *obj_name, const char *attr_name, unsigned int *data ); */
SEXP R_H5LTget_attribute_uint(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_attribute_ulong( hid_t loc_id, const char *obj_name, const char *attr_name, unsigned long *data ); */
SEXP R_H5LTget_attribute_ulong(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_attribute_ushort( hid_t loc_id, const char *obj_name, const char *attr_name, unsigned short *data ); */
SEXP R_H5LTget_attribute_ushort(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_data);
/* H5_HLDLL herr_t H5LTget_dataset_info( hid_t loc_id, const char *dset_name, hsize_t *dims, H5T_class_t *type_class, size_t *type_size ); */
SEXP R_H5LTget_dataset_info(SEXP R_loc_id, SEXP R_dset_name, SEXP R_dims, SEXP R_type_class, SEXP R_type_size);
/* H5_HLDLL herr_t H5LTget_dataset_ndims( hid_t loc_id, const char *dset_name, int *rank ); */
SEXP R_H5LTget_dataset_ndims(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank);
/* H5_HLDLL herr_t H5LTmake_dataset( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, hid_t type_id, const void *buffer ); */
SEXP R_H5LTmake_dataset(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_type_id, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTmake_dataset_char( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const char *buffer ); */
SEXP R_H5LTmake_dataset_char(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTmake_dataset_double( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const double *buffer ); */
SEXP R_H5LTmake_dataset_double(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTmake_dataset_float( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const float *buffer ); */
SEXP R_H5LTmake_dataset_float(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTmake_dataset_int( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const int *buffer ); */
SEXP R_H5LTmake_dataset_int(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTmake_dataset_long( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const long *buffer ); */
SEXP R_H5LTmake_dataset_long(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTmake_dataset_short( hid_t loc_id, const char *dset_name, int rank, const hsize_t *dims, const short *buffer ); */
SEXP R_H5LTmake_dataset_short(SEXP R_loc_id, SEXP R_dset_name, SEXP R_rank, SEXP R_dims, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTmake_dataset_string( hid_t loc_id, const char *dset_name, const char *buf ); */
SEXP R_H5LTmake_dataset_string(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buf);
/* H5_HLDLL hid_t H5LTopen_file_image(void *buf_ptr, size_t buf_size, unsigned flags); */
SEXP R_H5LTopen_file_image(SEXP R_buf_ptr, SEXP R_buf_size, SEXP R_flags, SEXP _dupl_buf_ptr);
/* H5_HLDLL htri_t H5LTpath_valid(hid_t loc_id, const char *path, hbool_t check_object_valid); */
SEXP R_H5LTpath_valid(SEXP R_loc_id, SEXP R_path, SEXP R_check_object_valid);
/* H5_HLDLL herr_t H5LTread_dataset( hid_t loc_id, const char *dset_name, hid_t type_id, void *buffer ); */
SEXP R_H5LTread_dataset(SEXP R_loc_id, SEXP R_dset_name, SEXP R_type_id, SEXP R_buffer, SEXP _dupl_buffer);
/* H5_HLDLL herr_t H5LTread_dataset_char( hid_t loc_id, const char *dset_name, char *buffer ); */
SEXP R_H5LTread_dataset_char(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTread_dataset_double( hid_t loc_id, const char *dset_name, double *buffer ); */
SEXP R_H5LTread_dataset_double(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTread_dataset_float( hid_t loc_id, const char *dset_name, float *buffer ); */
SEXP R_H5LTread_dataset_float(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTread_dataset_int( hid_t loc_id, const char *dset_name, int *buffer ); */
SEXP R_H5LTread_dataset_int(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTread_dataset_long( hid_t loc_id, const char *dset_name, long *buffer ); */
SEXP R_H5LTread_dataset_long(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTread_dataset_short( hid_t loc_id, const char *dset_name, short *buffer ); */
SEXP R_H5LTread_dataset_short(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer);
/* H5_HLDLL herr_t H5LTread_dataset_string( hid_t loc_id, const char *dset_name, char *buf ); */
SEXP R_H5LTread_dataset_string(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buf);
/* H5_HLDLL herr_t H5LTset_attribute_char( hid_t loc_id, const char *obj_name, const char *attr_name, const char *buffer, size_t size ); */
SEXP R_H5LTset_attribute_char(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size);
/* H5_HLDLL herr_t H5LTset_attribute_double( hid_t loc_id, const char *obj_name, const char *attr_name, const double *buffer, size_t size ); */
SEXP R_H5LTset_attribute_double(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size);
/* H5_HLDLL herr_t H5LTset_attribute_float( hid_t loc_id, const char *obj_name, const char *attr_name, const float *buffer, size_t size ); */
SEXP R_H5LTset_attribute_float(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size);
/* H5_HLDLL herr_t H5LTset_attribute_int( hid_t loc_id, const char *obj_name, const char *attr_name, const int *buffer, size_t size ); */
SEXP R_H5LTset_attribute_int(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size);
/* H5_HLDLL herr_t H5LTset_attribute_long( hid_t loc_id, const char *obj_name, const char *attr_name, const long *buffer, size_t size ); */
SEXP R_H5LTset_attribute_long(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size);
/* H5_HLDLL herr_t H5LTset_attribute_long_long( hid_t loc_id, const char *obj_name, const char *attr_name, const long long *buffer, size_t size ); */
SEXP R_H5LTset_attribute_long_long(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size);
/* H5_HLDLL herr_t H5LTset_attribute_short( hid_t loc_id, const char *obj_name, const char *attr_name, const short *buffer, size_t size ); */
SEXP R_H5LTset_attribute_short(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size);
/* H5_HLDLL herr_t H5LTset_attribute_string( hid_t loc_id, const char *obj_name, const char *attr_name, const char *attr_data ); */
SEXP R_H5LTset_attribute_string(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_attr_data);
/* H5_HLDLL herr_t H5LTset_attribute_uchar( hid_t loc_id, const char *obj_name, const char *attr_name, const unsigned char *buffer, size_t size ); */
SEXP R_H5LTset_attribute_uchar(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size);
/* H5_HLDLL herr_t H5LTset_attribute_uint( hid_t loc_id, const char *obj_name, const char *attr_name, const unsigned int *buffer, size_t size ); */
SEXP R_H5LTset_attribute_uint(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size);
/* H5_HLDLL herr_t H5LTset_attribute_ulong( hid_t loc_id, const char *obj_name, const char *attr_name, const unsigned long *buffer, size_t size ); */
SEXP R_H5LTset_attribute_ulong(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size);
/* H5_HLDLL herr_t H5LTset_attribute_ushort( hid_t loc_id, const char *obj_name, const char *attr_name, const unsigned short *buffer, size_t size ); */
SEXP R_H5LTset_attribute_ushort(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_buffer, SEXP R_size);
/* H5_HLDLL hid_t H5LTtext_to_dtype(const char *text, H5LT_lang_t lang_type); */
SEXP R_H5LTtext_to_dtype(SEXP R_text, SEXP R_lang_type);
#endif

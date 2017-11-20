#ifndef _WRAPPER_AUTO_H5A_H_
#define _WRAPPER_AUTO_H5A_H_
#include "global.h"
/* H5_DLL herr_t H5Aclose(hid_t attr_id); */
SEXP R_H5Aclose(SEXP R_attr_id);
/* H5_DLL hid_t H5Acreate_by_name(hid_t loc_id, const char *obj_name, const char *attr_name, hid_t type_id, hid_t space_id, hid_t acpl_id, hid_t aapl_id, hid_t lapl_id); */
SEXP R_H5Acreate_by_name(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_type_id, SEXP R_space_id, SEXP R_acpl_id, SEXP R_aapl_id, SEXP R_lapl_id);
/* H5_DLL hid_t H5Acreate2(hid_t loc_id, const char *attr_name, hid_t type_id, hid_t space_id, hid_t acpl_id, hid_t aapl_id); */
SEXP R_H5Acreate2(SEXP R_loc_id, SEXP R_attr_name, SEXP R_type_id, SEXP R_space_id, SEXP R_acpl_id, SEXP R_aapl_id);
/* H5_DLL herr_t H5Adelete(hid_t loc_id, const char *name); */
SEXP R_H5Adelete(SEXP R_loc_id, SEXP R_name);
/* H5_DLL herr_t H5Adelete_by_idx(hid_t loc_id, const char *obj_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, hid_t lapl_id); */
SEXP R_H5Adelete_by_idx(SEXP R_loc_id, SEXP R_obj_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_lapl_id);
/* H5_DLL herr_t H5Adelete_by_name(hid_t loc_id, const char *obj_name, const char *attr_name, hid_t lapl_id); */
SEXP R_H5Adelete_by_name(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_lapl_id);
/* H5_DLL htri_t H5Aexists(hid_t obj_id, const char *attr_name); */
SEXP R_H5Aexists(SEXP R_obj_id, SEXP R_attr_name);
/* H5_DLL htri_t H5Aexists_by_name(hid_t obj_id, const char *obj_name, const char *attr_name, hid_t lapl_id); */
SEXP R_H5Aexists_by_name(SEXP R_obj_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_lapl_id);
/* H5_DLL hid_t H5Aget_create_plist(hid_t attr_id); */
SEXP R_H5Aget_create_plist(SEXP R_attr_id);
/* H5_DLL herr_t H5Aget_info(hid_t attr_id, H5A_info_t *ainfo ); */
SEXP R_H5Aget_info(SEXP R_attr_id, SEXP R_ainfo);
/* H5_DLL herr_t H5Aget_info_by_idx(hid_t loc_id, const char *obj_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, H5A_info_t *ainfo , hid_t lapl_id); */
SEXP R_H5Aget_info_by_idx(SEXP R_loc_id, SEXP R_obj_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_ainfo, SEXP R_lapl_id);
/* H5_DLL herr_t H5Aget_info_by_name(hid_t loc_id, const char *obj_name, const char *attr_name, H5A_info_t *ainfo , hid_t lapl_id); */
SEXP R_H5Aget_info_by_name(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_ainfo, SEXP R_lapl_id);
/* H5_DLL ssize_t H5Aget_name(hid_t attr_id, size_t buf_size, char *buf); */
SEXP R_H5Aget_name(SEXP R_attr_id, SEXP R_buf_size, SEXP R_buf);
/* H5_DLL ssize_t H5Aget_name_by_idx(hid_t loc_id, const char *obj_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, char *name , size_t size, hid_t lapl_id); */
SEXP R_H5Aget_name_by_idx(SEXP R_loc_id, SEXP R_obj_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_name, SEXP R_size, SEXP R_lapl_id);
/* H5_DLL int H5Aget_num_attrs(hid_t loc_id); */
SEXP R_H5Aget_num_attrs(SEXP R_loc_id);
/* H5_DLL hid_t H5Aget_space(hid_t attr_id); */
SEXP R_H5Aget_space(SEXP R_attr_id);
/* H5_DLL hsize_t H5Aget_storage_size(hid_t attr_id); */
SEXP R_H5Aget_storage_size(SEXP R_attr_id);
/* H5_DLL hid_t H5Aget_type(hid_t attr_id); */
SEXP R_H5Aget_type(SEXP R_attr_id);
/* H5_DLL hid_t H5Aopen(hid_t obj_id, const char *attr_name, hid_t aapl_id); */
SEXP R_H5Aopen(SEXP R_obj_id, SEXP R_attr_name, SEXP R_aapl_id);
/* H5_DLL hid_t H5Aopen_by_idx(hid_t loc_id, const char *obj_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, hid_t aapl_id, hid_t lapl_id); */
SEXP R_H5Aopen_by_idx(SEXP R_loc_id, SEXP R_obj_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_aapl_id, SEXP R_lapl_id);
/* H5_DLL hid_t H5Aopen_by_name(hid_t loc_id, const char *obj_name, const char *attr_name, hid_t aapl_id, hid_t lapl_id); */
SEXP R_H5Aopen_by_name(SEXP R_loc_id, SEXP R_obj_name, SEXP R_attr_name, SEXP R_aapl_id, SEXP R_lapl_id);
/* H5_DLL hid_t H5Aopen_idx(hid_t loc_id, unsigned idx); */
SEXP R_H5Aopen_idx(SEXP R_loc_id, SEXP R_idx);
/* H5_DLL hid_t H5Aopen_name(hid_t loc_id, const char *name); */
SEXP R_H5Aopen_name(SEXP R_loc_id, SEXP R_name);
/* H5_DLL herr_t H5Aread(hid_t attr_id, hid_t type_id, void *buf); */
SEXP R_H5Aread(SEXP R_attr_id, SEXP R_type_id, SEXP R_buf, SEXP _dupl_buf);
/* H5_DLL herr_t H5Arename(hid_t loc_id, const char *old_name, const char *new_name); */
SEXP R_H5Arename(SEXP R_loc_id, SEXP R_old_name, SEXP R_new_name);
/* H5_DLL herr_t H5Arename_by_name(hid_t loc_id, const char *obj_name, const char *old_attr_name, const char *new_attr_name, hid_t lapl_id); */
SEXP R_H5Arename_by_name(SEXP R_loc_id, SEXP R_obj_name, SEXP R_old_attr_name, SEXP R_new_attr_name, SEXP R_lapl_id);
/* H5_DLL herr_t H5Awrite(hid_t attr_id, hid_t type_id, const void *buf); */
SEXP R_H5Awrite(SEXP R_attr_id, SEXP R_type_id, SEXP R_buf);
#endif

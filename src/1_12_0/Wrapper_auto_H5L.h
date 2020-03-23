#ifndef _WRAPPER_AUTO_H5L_H_
#define _WRAPPER_AUTO_H5L_H_
#include "global.h"
/* H5_DLL herr_t H5Lcopy(hid_t src_loc, const char *src_name, hid_t dst_loc, const char *dst_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lcopy(SEXP R_src_loc, SEXP R_src_name, SEXP R_dst_loc, SEXP R_dst_name, SEXP R_lcpl_id, SEXP R_lapl_id);
/* H5_DLL herr_t H5Lcreate_external(const char *file_name, const char *obj_name, hid_t link_loc_id, const char *link_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lcreate_external(SEXP R_file_name, SEXP R_obj_name, SEXP R_link_loc_id, SEXP R_link_name, SEXP R_lcpl_id, SEXP R_lapl_id);
/* H5_DLL herr_t H5Lcreate_hard(hid_t cur_loc, const char *cur_name, hid_t dst_loc, const char *dst_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lcreate_hard(SEXP R_cur_loc, SEXP R_cur_name, SEXP R_dst_loc, SEXP R_dst_name, SEXP R_lcpl_id, SEXP R_lapl_id);
/* H5_DLL herr_t H5Lcreate_soft(const char *link_target, hid_t link_loc_id, const char *link_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lcreate_soft(SEXP R_link_target, SEXP R_link_loc_id, SEXP R_link_name, SEXP R_lcpl_id, SEXP R_lapl_id);
/* H5_DLL herr_t H5Lcreate_ud(hid_t link_loc_id, const char *link_name, H5L_type_t link_type, const void *udata, size_t udata_size, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lcreate_ud(SEXP R_link_loc_id, SEXP R_link_name, SEXP R_link_type, SEXP R_udata, SEXP R_udata_size, SEXP R_lcpl_id, SEXP R_lapl_id);
/* H5_DLL herr_t H5Ldelete(hid_t loc_id, const char *name, hid_t lapl_id); */
SEXP R_H5Ldelete(SEXP R_loc_id, SEXP R_name, SEXP R_lapl_id);
/* H5_DLL herr_t H5Ldelete_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, hid_t lapl_id); */
SEXP R_H5Ldelete_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_lapl_id);
/* H5_DLL htri_t H5Lexists(hid_t loc_id, const char *name, hid_t lapl_id); */
SEXP R_H5Lexists(SEXP R_loc_id, SEXP R_name, SEXP R_lapl_id);
/* H5_DLL herr_t H5Lget_info1(hid_t loc_id, const char *name, H5L_info1_t *linfo , hid_t lapl_id); */
SEXP R_H5Lget_info(SEXP R_loc_id, SEXP R_name, SEXP R_linfo, SEXP R_lapl_id);
/* H5_DLL herr_t H5Lget_info_by_idx1(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, H5L_info1_t *linfo , hid_t lapl_id); */
SEXP R_H5Lget_info_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_linfo, SEXP R_lapl_id);
/* H5_DLL ssize_t H5Lget_name_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, char *name , size_t size, hid_t lapl_id); */
SEXP R_H5Lget_name_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_name, SEXP R_size, SEXP R_lapl_id);
/* H5_DLL herr_t H5Lget_val(hid_t loc_id, const char *name, void *buf, size_t size, hid_t lapl_id); */
SEXP R_H5Lget_val(SEXP R_loc_id, SEXP R_name, SEXP R_buf, SEXP R_size, SEXP R_lapl_id, SEXP _dupl_buf);
/* H5_DLL herr_t H5Lget_val_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, void *buf, size_t size, hid_t lapl_id); */
SEXP R_H5Lget_val_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_buf, SEXP R_size, SEXP R_lapl_id, SEXP _dupl_buf);
/* H5_DLL htri_t H5Lis_registered(H5L_type_t id); */
SEXP R_H5Lis_registered(SEXP R_id);
/* H5_DLL herr_t H5Lmove(hid_t src_loc, const char *src_name, hid_t dst_loc, const char *dst_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Lmove(SEXP R_src_loc, SEXP R_src_name, SEXP R_dst_loc, SEXP R_dst_name, SEXP R_lcpl_id, SEXP R_lapl_id);
/* H5_DLL herr_t H5Lunpack_elink_val(const void *ext_linkval, size_t link_size, unsigned *flags, const char **filename, const char **obj_path ); */
SEXP R_H5Lunpack_elink_val(SEXP R_ext_linkval, SEXP R_link_size, SEXP R_flags, SEXP R_filename, SEXP R_obj_path);
/* H5_DLL herr_t H5Lunregister(H5L_type_t id); */
SEXP R_H5Lunregister(SEXP R_id);
#endif

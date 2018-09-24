#ifndef _WRAPPER_AUTO_H5O_H_
#define _WRAPPER_AUTO_H5O_H_
#include "global.h"
/* H5_DLL herr_t H5Oare_mdc_flushes_disabled(hid_t object_id, hbool_t *are_disabled); */
SEXP R_H5Oare_mdc_flushes_disabled(SEXP R_object_id, SEXP R_are_disabled);
/* H5_DLL herr_t H5Oclose(hid_t object_id); */
SEXP R_H5Oclose(SEXP R_object_id);
/* H5_DLL herr_t H5Ocopy(hid_t src_loc_id, const char *src_name, hid_t dst_loc_id, const char *dst_name, hid_t ocpypl_id, hid_t lcpl_id); */
SEXP R_H5Ocopy(SEXP R_src_loc_id, SEXP R_src_name, SEXP R_dst_loc_id, SEXP R_dst_name, SEXP R_ocpypl_id, SEXP R_lcpl_id);
/* H5_DLL herr_t H5Odecr_refcount(hid_t object_id); */
SEXP R_H5Odecr_refcount(SEXP R_object_id);
/* H5_DLL herr_t H5Odisable_mdc_flushes(hid_t object_id); */
SEXP R_H5Odisable_mdc_flushes(SEXP R_object_id);
/* H5_DLL herr_t H5Oenable_mdc_flushes(hid_t object_id); */
SEXP R_H5Oenable_mdc_flushes(SEXP R_object_id);
/* H5_DLL htri_t H5Oexists_by_name(hid_t loc_id, const char *name, hid_t lapl_id); */
SEXP R_H5Oexists_by_name(SEXP R_loc_id, SEXP R_name, SEXP R_lapl_id);
/* H5_DLL herr_t H5Oflush(hid_t obj_id); */
SEXP R_H5Oflush(SEXP R_obj_id);
/* H5_DLL ssize_t H5Oget_comment(hid_t obj_id, char *comment, size_t bufsize); */
SEXP R_H5Oget_comment(SEXP R_obj_id, SEXP R_comment, SEXP R_bufsize);
/* H5_DLL ssize_t H5Oget_comment_by_name(hid_t loc_id, const char *name, char *comment, size_t bufsize, hid_t lapl_id); */
SEXP R_H5Oget_comment_by_name(SEXP R_loc_id, SEXP R_name, SEXP R_comment, SEXP R_bufsize, SEXP R_lapl_id);
/* H5_DLL herr_t H5Oget_info(hid_t loc_id, H5O_info_t *oinfo); */
SEXP R_H5Oget_info(SEXP R_loc_id, SEXP R_oinfo);
/* H5_DLL herr_t H5Oget_info_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, H5O_info_t *oinfo, hid_t lapl_id); */
SEXP R_H5Oget_info_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_oinfo, SEXP R_lapl_id);
/* H5_DLL herr_t H5Oget_info_by_name(hid_t loc_id, const char *name, H5O_info_t *oinfo, hid_t lapl_id); */
SEXP R_H5Oget_info_by_name(SEXP R_loc_id, SEXP R_name, SEXP R_oinfo, SEXP R_lapl_id);
/* H5_DLL herr_t H5Oincr_refcount(hid_t object_id); */
SEXP R_H5Oincr_refcount(SEXP R_object_id);
/* H5_DLL herr_t H5Olink(hid_t obj_id, hid_t new_loc_id, const char *new_name, hid_t lcpl_id, hid_t lapl_id); */
SEXP R_H5Olink(SEXP R_obj_id, SEXP R_new_loc_id, SEXP R_new_name, SEXP R_lcpl_id, SEXP R_lapl_id);
/* H5_DLL hid_t H5Oopen(hid_t loc_id, const char *name, hid_t lapl_id); */
SEXP R_H5Oopen(SEXP R_loc_id, SEXP R_name, SEXP R_lapl_id);
/* H5_DLL hid_t H5Oopen_by_addr(hid_t loc_id, haddr_t addr); */
SEXP R_H5Oopen_by_addr(SEXP R_loc_id, SEXP R_addr);
/* H5_DLL hid_t H5Oopen_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, hid_t lapl_id); */
SEXP R_H5Oopen_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_lapl_id);
/* H5_DLL herr_t H5Orefresh(hid_t oid); */
SEXP R_H5Orefresh(SEXP R_oid);
/* H5_DLL herr_t H5Oset_comment(hid_t obj_id, const char *comment); */
SEXP R_H5Oset_comment(SEXP R_obj_id, SEXP R_comment);
/* H5_DLL herr_t H5Oset_comment_by_name(hid_t loc_id, const char *name, const char *comment, hid_t lapl_id); */
SEXP R_H5Oset_comment_by_name(SEXP R_loc_id, SEXP R_name, SEXP R_comment, SEXP R_lapl_id);
#endif

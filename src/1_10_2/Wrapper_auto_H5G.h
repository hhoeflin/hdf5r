#ifndef _WRAPPER_AUTO_H5G_H_
#define _WRAPPER_AUTO_H5G_H_
#include "global.h"
/* H5_DLL herr_t H5Gclose(hid_t group_id); */
SEXP R_H5Gclose(SEXP R_group_id);
/* H5_DLL hid_t H5Gcreate_anon(hid_t loc_id, hid_t gcpl_id, hid_t gapl_id); */
SEXP R_H5Gcreate_anon(SEXP R_loc_id, SEXP R_gcpl_id, SEXP R_gapl_id);
/* H5_DLL hid_t H5Gcreate2(hid_t loc_id, const char *name, hid_t lcpl_id, hid_t gcpl_id, hid_t gapl_id); */
SEXP R_H5Gcreate2(SEXP R_loc_id, SEXP R_name, SEXP R_lcpl_id, SEXP R_gcpl_id, SEXP R_gapl_id);
/* H5_DLL herr_t H5Gflush(hid_t group_id); */
SEXP R_H5Gflush(SEXP R_group_id);
/* H5_DLL hid_t H5Gget_create_plist(hid_t group_id); */
SEXP R_H5Gget_create_plist(SEXP R_group_id);
/* H5_DLL herr_t H5Gget_info(hid_t loc_id, H5G_info_t *ginfo); */
SEXP R_H5Gget_info(SEXP R_loc_id, SEXP R_ginfo);
/* H5_DLL herr_t H5Gget_info_by_idx(hid_t loc_id, const char *group_name, H5_index_t idx_type, H5_iter_order_t order, hsize_t n, H5G_info_t *ginfo, hid_t lapl_id); */
SEXP R_H5Gget_info_by_idx(SEXP R_loc_id, SEXP R_group_name, SEXP R_idx_type, SEXP R_order, SEXP R_n, SEXP R_ginfo, SEXP R_lapl_id);
/* H5_DLL herr_t H5Gget_info_by_name(hid_t loc_id, const char *name, H5G_info_t *ginfo, hid_t lapl_id); */
SEXP R_H5Gget_info_by_name(SEXP R_loc_id, SEXP R_name, SEXP R_ginfo, SEXP R_lapl_id);
/* H5_DLL hid_t H5Gopen2(hid_t loc_id, const char *name, hid_t gapl_id); */
SEXP R_H5Gopen2(SEXP R_loc_id, SEXP R_name, SEXP R_gapl_id);
/* H5_DLL herr_t H5Grefresh(hid_t group_id); */
SEXP R_H5Grefresh(SEXP R_group_id);
/* H5_DLL herr_t H5Gset_comment(hid_t loc_id, const char *name, const char *comment); */
SEXP R_H5Gset_comment(SEXP R_loc_id, SEXP R_name, SEXP R_comment);
#endif

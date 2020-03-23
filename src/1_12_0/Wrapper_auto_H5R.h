#ifndef _WRAPPER_AUTO_H5R_H_
#define _WRAPPER_AUTO_H5R_H_
#include "global.h"
/* H5_DLL herr_t H5Rcopy(const H5R_ref_t *src_ref_ptr, H5R_ref_t *dst_ref_ptr); */
SEXP R_H5Rcopy(SEXP R_src_ref_ptr, SEXP R_dst_ref_ptr);
/* H5_DLL herr_t H5Rcreate(void *ref, hid_t loc_id, const char *name, H5R_type_t ref_type, hid_t space_id); */
SEXP R_H5Rcreate(SEXP R_ref, SEXP R_loc_id, SEXP R_name, SEXP R_ref_type, SEXP R_space_id, SEXP _dupl_ref);
/* H5_DLL herr_t H5Rcreate_attr(hid_t loc_id, const char *name, const char *attr_name, hid_t oapl_id, H5R_ref_t *ref_ptr); */
SEXP R_H5Rcreate_attr(SEXP R_loc_id, SEXP R_name, SEXP R_attr_name, SEXP R_oapl_id, SEXP R_ref_ptr);
/* H5_DLL herr_t H5Rcreate_object(hid_t loc_id, const char *name, hid_t oapl_id, H5R_ref_t *ref_ptr); */
SEXP R_H5Rcreate_object(SEXP R_loc_id, SEXP R_name, SEXP R_oapl_id, SEXP R_ref_ptr);
/* H5_DLL herr_t H5Rcreate_region(hid_t loc_id, const char *name, hid_t space_id, hid_t oapl_id, H5R_ref_t *ref_ptr); */
SEXP R_H5Rcreate_region(SEXP R_loc_id, SEXP R_name, SEXP R_space_id, SEXP R_oapl_id, SEXP R_ref_ptr);
/* H5_DLL hid_t H5Rdereference1(hid_t obj_id, H5R_type_t ref_type, const void *ref); */
SEXP R_H5Rdereference1(SEXP R_obj_id, SEXP R_ref_type, SEXP R_ref);
/* H5_DLL hid_t H5Rdereference2(hid_t obj_id, hid_t oapl_id, H5R_type_t ref_type, const void *ref); */
SEXP R_H5Rdereference2(SEXP R_obj_id, SEXP R_oapl_id, SEXP R_ref_type, SEXP R_ref);
/* H5_DLL herr_t H5Rdestroy(H5R_ref_t *ref_ptr); */
SEXP R_H5Rdestroy(SEXP R_ref_ptr);
/* H5_DLL htri_t H5Requal(const H5R_ref_t *ref1_ptr, const H5R_ref_t *ref2_ptr); */
SEXP R_H5Requal(SEXP R_ref1_ptr, SEXP R_ref2_ptr);
/* H5_DLL ssize_t H5Rget_attr_name(const H5R_ref_t *ref_ptr, char *buf, size_t size); */
SEXP R_H5Rget_attr_name(SEXP R_ref_ptr, SEXP R_buf, SEXP R_size);
/* H5_DLL ssize_t H5Rget_file_name(const H5R_ref_t *ref_ptr, char *buf, size_t size); */
SEXP R_H5Rget_file_name(SEXP R_ref_ptr, SEXP R_buf, SEXP R_size);
/* H5_DLL ssize_t H5Rget_name(hid_t loc_id, H5R_type_t ref_type, const void *ref, char *name, size_t size); */
SEXP R_H5Rget_name(SEXP R_loc_id, SEXP R_ref_type, SEXP R_ref, SEXP R_name, SEXP R_size);
/* H5_DLL ssize_t H5Rget_obj_name(H5R_ref_t *ref_ptr, hid_t rapl_id, char *buf, size_t size); */
SEXP R_H5Rget_obj_name(SEXP R_ref_ptr, SEXP R_rapl_id, SEXP R_buf, SEXP R_size);
/* H5_DLL herr_t H5Rget_obj_type2(hid_t id, H5R_type_t ref_type, const void *ref, H5O_type_t *obj_type); */
SEXP R_H5Rget_obj_type2(SEXP R_id, SEXP R_ref_type, SEXP R_ref, SEXP R_obj_type);
/* H5_DLL herr_t H5Rget_obj_type3(H5R_ref_t *ref_ptr, hid_t rapl_id, H5O_type_t *obj_type); */
SEXP R_H5Rget_obj_type3(SEXP R_ref_ptr, SEXP R_rapl_id, SEXP R_obj_type);
/* H5_DLL hid_t H5Rget_region(hid_t dataset, H5R_type_t ref_type, const void *ref); */
SEXP R_H5Rget_region(SEXP R_dataset, SEXP R_ref_type, SEXP R_ref);
/* H5_DLL H5R_type_t H5Rget_type(const H5R_ref_t *ref_ptr); */
SEXP R_H5Rget_type(SEXP R_ref_ptr);
/* H5_DLL hid_t H5Ropen_attr(H5R_ref_t *ref_ptr, hid_t rapl_id, hid_t aapl_id); */
SEXP R_H5Ropen_attr(SEXP R_ref_ptr, SEXP R_rapl_id, SEXP R_aapl_id);
/* H5_DLL hid_t H5Ropen_object(H5R_ref_t *ref_ptr, hid_t rapl_id, hid_t oapl_id); */
SEXP R_H5Ropen_object(SEXP R_ref_ptr, SEXP R_rapl_id, SEXP R_oapl_id);
/* H5_DLL hid_t H5Ropen_region(H5R_ref_t *ref_ptr, hid_t rapl_id, hid_t oapl_id); */
SEXP R_H5Ropen_region(SEXP R_ref_ptr, SEXP R_rapl_id, SEXP R_oapl_id);
#endif

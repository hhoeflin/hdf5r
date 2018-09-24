#ifndef _WRAPPER_AUTO_H5R_H_
#define _WRAPPER_AUTO_H5R_H_
#include "global.h"
/* H5_DLL herr_t H5Rcreate(void *ref, hid_t loc_id, const char *name, H5R_type_t ref_type, hid_t space_id); */
SEXP R_H5Rcreate(SEXP R_ref, SEXP R_loc_id, SEXP R_name, SEXP R_ref_type, SEXP R_space_id, SEXP _dupl_ref);
/* H5_DLL hid_t H5Rdereference1(hid_t obj_id, H5R_type_t ref_type, const void *ref); */
SEXP R_H5Rdereference1(SEXP R_obj_id, SEXP R_ref_type, SEXP R_ref);
/* H5_DLL hid_t H5Rdereference2(hid_t obj_id, hid_t oapl_id, H5R_type_t ref_type, const void *ref); */
SEXP R_H5Rdereference2(SEXP R_obj_id, SEXP R_oapl_id, SEXP R_ref_type, SEXP R_ref);
/* H5_DLL ssize_t H5Rget_name(hid_t loc_id, H5R_type_t ref_type, const void *ref, char *name , size_t size); */
SEXP R_H5Rget_name(SEXP R_loc_id, SEXP R_ref_type, SEXP R_ref, SEXP R_name, SEXP R_size);
/* H5_DLL herr_t H5Rget_obj_type2(hid_t id, H5R_type_t ref_type, const void *_ref, H5O_type_t *obj_type); */
SEXP R_H5Rget_obj_type2(SEXP R_id, SEXP R_ref_type, SEXP R__ref, SEXP R_obj_type);
/* H5_DLL hid_t H5Rget_region(hid_t dataset, H5R_type_t ref_type, const void *ref); */
SEXP R_H5Rget_region(SEXP R_dataset, SEXP R_ref_type, SEXP R_ref);
#endif

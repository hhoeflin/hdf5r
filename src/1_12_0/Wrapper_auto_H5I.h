#ifndef _WRAPPER_AUTO_H5I_H_
#define _WRAPPER_AUTO_H5I_H_
#include "global.h"
/* H5_DLL herr_t H5Iclear_type(H5I_type_t type, hbool_t force); */
SEXP R_H5Iclear_type(SEXP R_type, SEXP R_force);
/* H5_DLL int H5Idec_ref(hid_t id); */
SEXP R_H5Idec_ref(SEXP R_id);
/* H5_DLL int H5Idec_type_ref(H5I_type_t type); */
SEXP R_H5Idec_type_ref(SEXP R_type);
/* H5_DLL herr_t H5Idestroy_type(H5I_type_t type); */
SEXP R_H5Idestroy_type(SEXP R_type);
/* H5_DLL hid_t H5Iget_file_id(hid_t id); */
SEXP R_H5Iget_file_id(SEXP R_id);
/* H5_DLL ssize_t H5Iget_name(hid_t id, char *name, size_t size); */
SEXP R_H5Iget_name(SEXP R_id, SEXP R_name, SEXP R_size);
/* H5_DLL int H5Iget_ref(hid_t id); */
SEXP R_H5Iget_ref(SEXP R_id);
/* H5_DLL H5I_type_t H5Iget_type(hid_t id); */
SEXP R_H5Iget_type(SEXP R_id);
/* H5_DLL int H5Iget_type_ref(H5I_type_t type); */
SEXP R_H5Iget_type_ref(SEXP R_type);
/* H5_DLL int H5Iinc_ref(hid_t id); */
SEXP R_H5Iinc_ref(SEXP R_id);
/* H5_DLL int H5Iinc_type_ref(H5I_type_t type); */
SEXP R_H5Iinc_type_ref(SEXP R_type);
/* H5_DLL htri_t H5Iis_valid(hid_t id); */
SEXP R_H5Iis_valid(SEXP R_id);
/* H5_DLL herr_t H5Inmembers(H5I_type_t type, hsize_t *num_members); */
SEXP R_H5Inmembers(SEXP R_type, SEXP R_num_members);
/* H5_DLL hid_t H5Iregister(H5I_type_t type, const void *object); */
SEXP R_H5Iregister(SEXP R_type, SEXP R_object);
/* H5_DLL htri_t H5Itype_exists(H5I_type_t type); */
SEXP R_H5Itype_exists(SEXP R_type);
#endif

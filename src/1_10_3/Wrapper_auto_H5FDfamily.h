#ifndef _WRAPPER_AUTO_H5FDFAMILY_H_
#define _WRAPPER_AUTO_H5FDFAMILY_H_
#include "global.h"
/* H5_DLL hid_t H5FD_family_init(void); */
SEXP R_H5FD_family_init(void);
/* H5_DLL herr_t H5Pget_fapl_family(hid_t fapl_id, hsize_t *memb_size, hid_t *memb_fapl_id); */
SEXP R_H5Pget_fapl_family(SEXP R_fapl_id, SEXP R_memb_size, SEXP R_memb_fapl_id);
/* H5_DLL herr_t H5Pset_fapl_family(hid_t fapl_id, hsize_t memb_size, hid_t memb_fapl_id); */
SEXP R_H5Pset_fapl_family(SEXP R_fapl_id, SEXP R_memb_size, SEXP R_memb_fapl_id);
#endif

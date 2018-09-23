#ifndef _WRAPPER_AUTO_H5FDCORE_H_
#define _WRAPPER_AUTO_H5FDCORE_H_
#include "global.h"
/* H5_DLL herr_t H5Pget_fapl_core(hid_t fapl_id, size_t *increment, hbool_t *backing_store); */
SEXP R_H5Pget_fapl_core(SEXP R_fapl_id, SEXP R_increment, SEXP R_backing_store);
/* H5_DLL herr_t H5Pset_fapl_core(hid_t fapl_id, size_t increment, hbool_t backing_store); */
SEXP R_H5Pset_fapl_core(SEXP R_fapl_id, SEXP R_increment, SEXP R_backing_store);
#endif

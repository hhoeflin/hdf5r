#ifndef _WRAPPER_AUTO_H5FDSTDIO_H_
#define _WRAPPER_AUTO_H5FDSTDIO_H_
#include "global.h"
/* H5_DLL hid_t H5FD_stdio_init(void); */
SEXP R_H5FD_stdio_init(void);
/* H5_DLL herr_t H5Pset_fapl_stdio(hid_t fapl_id); */
SEXP R_H5Pset_fapl_stdio(SEXP R_fapl_id);
#endif

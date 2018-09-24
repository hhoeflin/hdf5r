#ifndef _WRAPPER_AUTO_H5FDSEC2_H_
#define _WRAPPER_AUTO_H5FDSEC2_H_
#include "global.h"
/* H5_DLL hid_t H5FD_sec2_init(void); */
SEXP R_H5FD_sec2_init(void);
/* H5_DLL herr_t H5Pset_fapl_sec2(hid_t fapl_id); */
SEXP R_H5Pset_fapl_sec2(SEXP R_fapl_id);
#endif

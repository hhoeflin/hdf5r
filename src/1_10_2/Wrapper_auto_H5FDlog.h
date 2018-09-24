#ifndef _WRAPPER_AUTO_H5FDLOG_H_
#define _WRAPPER_AUTO_H5FDLOG_H_
#include "global.h"
/* H5_DLL hid_t H5FD_log_init(void); */
SEXP R_H5FD_log_init(void);
/* H5_DLL herr_t H5Pset_fapl_log(hid_t fapl_id, const char *logfile, unsigned long long flags, size_t buf_size); */
SEXP R_H5Pset_fapl_log(SEXP R_fapl_id, SEXP R_logfile, SEXP R_flags, SEXP R_buf_size);
#endif

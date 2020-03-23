#ifndef _WRAPPER_AUTO_H5Z_H_
#define _WRAPPER_AUTO_H5Z_H_
#include "global.h"
/* H5_DLL htri_t H5Zfilter_avail(H5Z_filter_t id); */
SEXP R_H5Zfilter_avail(SEXP R_id);
/* H5_DLL herr_t H5Zget_filter_info(H5Z_filter_t filter, unsigned int *filter_config_flags); */
SEXP R_H5Zget_filter_info(SEXP R_filter, SEXP R_filter_config_flags);
/* H5_DLL herr_t H5Zregister(const void *cls); */
SEXP R_H5Zregister(SEXP R_cls);
/* H5_DLL herr_t H5Zunregister(H5Z_filter_t id); */
SEXP R_H5Zunregister(SEXP R_id);
#endif

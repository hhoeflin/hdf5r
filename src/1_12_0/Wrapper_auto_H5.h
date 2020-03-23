#ifndef _WRAPPER_AUTO_H5_H_
#define _WRAPPER_AUTO_H5_H_
#include "global.h"
/* H5_DLL herr_t H5check_version(unsigned majnum, unsigned minnum, unsigned relnum); */
SEXP R_H5check_version(SEXP R_majnum, SEXP R_minnum, SEXP R_relnum);
/* H5_DLL herr_t H5close(void); */
SEXP R_H5close(void);
/* H5_DLL herr_t H5dont_atexit(void); */
SEXP R_H5dont_atexit(void);
/* H5_DLL herr_t H5free_memory(void *mem); */
SEXP R_H5free_memory(SEXP R_mem, SEXP _dupl_mem);
/* H5_DLL herr_t H5garbage_collect(void); */
SEXP R_H5garbage_collect(void);
/* H5_DLL herr_t H5get_libversion(unsigned *majnum, unsigned *minnum, unsigned *relnum); */
SEXP R_H5get_libversion(SEXP R_majnum, SEXP R_minnum, SEXP R_relnum);
/* H5_DLL herr_t H5is_library_threadsafe(hbool_t *is_ts); */
SEXP R_H5is_library_threadsafe(SEXP R_is_ts);
/* H5_DLL herr_t H5open(void); */
SEXP R_H5open(void);
/* H5_DLL herr_t H5set_free_list_limits (int reg_global_lim, int reg_list_lim, int arr_global_lim, int arr_list_lim, int blk_global_lim, int blk_list_lim); */
SEXP R_H5set_free_list_limits(SEXP R_reg_global_lim, SEXP R_reg_list_lim, SEXP R_arr_global_lim, SEXP R_arr_list_lim, SEXP R_blk_global_lim, SEXP R_blk_list_lim);
#endif

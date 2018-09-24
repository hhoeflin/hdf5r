#ifndef _WRAPPER_AUTO_H5E_H_
#define _WRAPPER_AUTO_H5E_H_
#include "global.h"
/* H5_DLL herr_t H5Eauto_is_v2(hid_t err_stack, unsigned *is_stack); */
SEXP R_H5Eauto_is_v2(SEXP R_err_stack, SEXP R_is_stack);
/* H5_DLL herr_t H5Eclear2(hid_t err_stack); */
SEXP R_H5Eclear2(SEXP R_err_stack);
/* H5_DLL herr_t H5Eclose_msg(hid_t err_id); */
SEXP R_H5Eclose_msg(SEXP R_err_id);
/* H5_DLL herr_t H5Eclose_stack(hid_t stack_id); */
SEXP R_H5Eclose_stack(SEXP R_stack_id);
/* H5_DLL hid_t H5Ecreate_msg(hid_t cls, H5E_type_t msg_type, const char *msg); */
SEXP R_H5Ecreate_msg(SEXP R_cls, SEXP R_msg_type, SEXP R_msg);
/* H5_DLL hid_t H5Ecreate_stack(void); */
SEXP R_H5Ecreate_stack(void);
/* H5_DLL ssize_t H5Eget_class_name(hid_t class_id, char *name, size_t size); */
SEXP R_H5Eget_class_name(SEXP R_class_id, SEXP R_name, SEXP R_size);
/* H5_DLL hid_t H5Eget_current_stack(void); */
SEXP R_H5Eget_current_stack(void);
/* H5_DLL char *H5Eget_major(H5E_major_t maj); */
SEXP R_H5Eget_major(SEXP R_maj);
/* H5_DLL char *H5Eget_minor(H5E_minor_t min); */
SEXP R_H5Eget_minor(SEXP R_min);
/* H5_DLL ssize_t H5Eget_msg(hid_t msg_id, H5E_type_t *type, char *msg, size_t size); */
SEXP R_H5Eget_msg(SEXP R_msg_id, SEXP R_type, SEXP R_msg, SEXP R_size);
/* H5_DLL ssize_t H5Eget_num(hid_t error_stack_id); */
SEXP R_H5Eget_num(SEXP R_error_stack_id);
/* H5_DLL herr_t H5Epop(hid_t err_stack, size_t count); */
SEXP R_H5Epop(SEXP R_err_stack, SEXP R_count);
/* H5_DLL herr_t H5Epush2(hid_t err_stack, const char *file, const char *func, unsigned line, hid_t cls_id, hid_t maj_id, hid_t min_id, const char *msg, ...); */
SEXP R_H5Epush2(SEXP R_err_stack, SEXP R_file, SEXP R_func, SEXP R_line, SEXP R_cls_id, SEXP R_maj_id, SEXP R_min_id, SEXP R_msg);
/* H5_DLL hid_t H5Eregister_class(const char *cls_name, const char *lib_name, const char *version); */
SEXP R_H5Eregister_class(SEXP R_cls_name, SEXP R_lib_name, SEXP R_version);
/* H5_DLL herr_t H5Eset_current_stack(hid_t err_stack_id); */
SEXP R_H5Eset_current_stack(SEXP R_err_stack_id);
/* H5_DLL herr_t H5Eunregister_class(hid_t class_id); */
SEXP R_H5Eunregister_class(SEXP R_class_id);
#endif

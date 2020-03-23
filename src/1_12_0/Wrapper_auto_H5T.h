#ifndef _WRAPPER_AUTO_H5T_H_
#define _WRAPPER_AUTO_H5T_H_
#include "global.h"
/* H5_DLL hid_t H5Tarray_create2(hid_t base_id, unsigned ndims, const hsize_t dim[]); */
SEXP R_H5Tarray_create2(SEXP R_base_id, SEXP R_ndims, SEXP R_dim);
/* H5_DLL herr_t H5Tclose(hid_t type_id); */
SEXP R_H5Tclose(SEXP R_type_id);
/* H5_DLL herr_t H5Tcommit_anon(hid_t loc_id, hid_t type_id, hid_t tcpl_id, hid_t tapl_id); */
SEXP R_H5Tcommit_anon(SEXP R_loc_id, SEXP R_type_id, SEXP R_tcpl_id, SEXP R_tapl_id);
/* H5_DLL herr_t H5Tcommit2(hid_t loc_id, const char *name, hid_t type_id, hid_t lcpl_id, hid_t tcpl_id, hid_t tapl_id); */
SEXP R_H5Tcommit2(SEXP R_loc_id, SEXP R_name, SEXP R_type_id, SEXP R_lcpl_id, SEXP R_tcpl_id, SEXP R_tapl_id);
/* H5_DLL htri_t H5Tcommitted(hid_t type_id); */
SEXP R_H5Tcommitted(SEXP R_type_id);
/* H5_DLL htri_t H5Tcompiler_conv(hid_t src_id, hid_t dst_id); */
SEXP R_H5Tcompiler_conv(SEXP R_src_id, SEXP R_dst_id);
/* H5_DLL herr_t H5Tconvert(hid_t src_id, hid_t dst_id, size_t nelmts, void *buf, void *background, hid_t plist_id); */
SEXP R_H5Tconvert(SEXP R_src_id, SEXP R_dst_id, SEXP R_nelmts, SEXP R_buf, SEXP R_background, SEXP R_plist_id, SEXP _dupl_buf, SEXP _dupl_background);
/* H5_DLL hid_t H5Tcopy(hid_t type_id); */
SEXP R_H5Tcopy(SEXP R_type_id);
/* H5_DLL hid_t H5Tcreate(H5T_class_t type, size_t size); */
SEXP R_H5Tcreate(SEXP R_type, SEXP R_size);
/* H5_DLL hid_t H5Tdecode(const void *buf); */
SEXP R_H5Tdecode(SEXP R_buf);
/* H5_DLL htri_t H5Tdetect_class(hid_t type_id, H5T_class_t cls); */
SEXP R_H5Tdetect_class(SEXP R_type_id, SEXP R_cls);
/* H5_DLL herr_t H5Tencode(hid_t obj_id, void *buf, size_t *nalloc); */
SEXP R_H5Tencode(SEXP R_obj_id, SEXP R_buf, SEXP R_nalloc, SEXP _dupl_buf);
/* H5_DLL hid_t H5Tenum_create(hid_t base_id); */
SEXP R_H5Tenum_create(SEXP R_base_id);
/* H5_DLL herr_t H5Tenum_insert(hid_t type, const char *name, const void *value); */
SEXP R_H5Tenum_insert(SEXP R_type, SEXP R_name, SEXP R_value);
/* H5_DLL herr_t H5Tenum_nameof(hid_t type, const void *value, char *name, size_t size); */
SEXP R_H5Tenum_nameof(SEXP R_type, SEXP R_value, SEXP R_name, SEXP R_size);
/* H5_DLL herr_t H5Tenum_valueof(hid_t type, const char *name, void *value); */
SEXP R_H5Tenum_valueof(SEXP R_type, SEXP R_name, SEXP R_value, SEXP _dupl_value);
/* H5_DLL htri_t H5Tequal(hid_t type1_id, hid_t type2_id); */
SEXP R_H5Tequal(SEXP R_type1_id, SEXP R_type2_id);
/* H5_DLL herr_t H5Tflush(hid_t type_id); */
SEXP R_H5Tflush(SEXP R_type_id);
/* H5_DLL int H5Tget_array_dims2(hid_t type_id, hsize_t dims[]); */
SEXP R_H5Tget_array_dims2(SEXP R_type_id, SEXP R_dims);
/* H5_DLL int H5Tget_array_ndims(hid_t type_id); */
SEXP R_H5Tget_array_ndims(SEXP R_type_id);
/* H5_DLL H5T_class_t H5Tget_class(hid_t type_id); */
SEXP R_H5Tget_class(SEXP R_type_id);
/* H5_DLL hid_t H5Tget_create_plist(hid_t type_id); */
SEXP R_H5Tget_create_plist(SEXP R_type_id);
/* H5_DLL H5T_cset_t H5Tget_cset(hid_t type_id); */
SEXP R_H5Tget_cset(SEXP R_type_id);
/* H5_DLL size_t H5Tget_ebias(hid_t type_id); */
SEXP R_H5Tget_ebias(SEXP R_type_id);
/* H5_DLL herr_t H5Tget_fields(hid_t type_id, size_t *spos, size_t *epos, size_t *esize, size_t *mpos, size_t *msize); */
SEXP R_H5Tget_fields(SEXP R_type_id, SEXP R_spos, SEXP R_epos, SEXP R_esize, SEXP R_mpos, SEXP R_msize);
/* H5_DLL H5T_pad_t H5Tget_inpad(hid_t type_id); */
SEXP R_H5Tget_inpad(SEXP R_type_id);
/* H5_DLL H5T_class_t H5Tget_member_class(hid_t type_id, unsigned membno); */
SEXP R_H5Tget_member_class(SEXP R_type_id, SEXP R_membno);
/* H5_DLL int H5Tget_member_index(hid_t type_id, const char *name); */
SEXP R_H5Tget_member_index(SEXP R_type_id, SEXP R_name);
/* H5_DLL char *H5Tget_member_name(hid_t type_id, unsigned membno); */
SEXP R_H5Tget_member_name(SEXP R_type_id, SEXP R_membno);
/* H5_DLL size_t H5Tget_member_offset(hid_t type_id, unsigned membno); */
SEXP R_H5Tget_member_offset(SEXP R_type_id, SEXP R_membno);
/* H5_DLL hid_t H5Tget_member_type(hid_t type_id, unsigned membno); */
SEXP R_H5Tget_member_type(SEXP R_type_id, SEXP R_membno);
/* H5_DLL herr_t H5Tget_member_value(hid_t type_id, unsigned membno, void *value); */
SEXP R_H5Tget_member_value(SEXP R_type_id, SEXP R_membno, SEXP R_value, SEXP _dupl_value);
/* H5_DLL hid_t H5Tget_native_type(hid_t type_id, H5T_direction_t direction); */
SEXP R_H5Tget_native_type(SEXP R_type_id, SEXP R_direction);
/* H5_DLL int H5Tget_nmembers(hid_t type_id); */
SEXP R_H5Tget_nmembers(SEXP R_type_id);
/* H5_DLL H5T_norm_t H5Tget_norm(hid_t type_id); */
SEXP R_H5Tget_norm(SEXP R_type_id);
/* H5_DLL int H5Tget_offset(hid_t type_id); */
SEXP R_H5Tget_offset(SEXP R_type_id);
/* H5_DLL H5T_order_t H5Tget_order(hid_t type_id); */
SEXP R_H5Tget_order(SEXP R_type_id);
/* H5_DLL herr_t H5Tget_pad(hid_t type_id, H5T_pad_t *lsb, H5T_pad_t *msb); */
SEXP R_H5Tget_pad(SEXP R_type_id, SEXP R_lsb, SEXP R_msb);
/* H5_DLL size_t H5Tget_precision(hid_t type_id); */
SEXP R_H5Tget_precision(SEXP R_type_id);
/* H5_DLL H5T_sign_t H5Tget_sign(hid_t type_id); */
SEXP R_H5Tget_sign(SEXP R_type_id);
/* H5_DLL size_t H5Tget_size(hid_t type_id); */
SEXP R_H5Tget_size(SEXP R_type_id);
/* H5_DLL H5T_str_t H5Tget_strpad(hid_t type_id); */
SEXP R_H5Tget_strpad(SEXP R_type_id);
/* H5_DLL hid_t H5Tget_super(hid_t type); */
SEXP R_H5Tget_super(SEXP R_type);
/* H5_DLL char *H5Tget_tag(hid_t type); */
SEXP R_H5Tget_tag(SEXP R_type);
/* H5_DLL herr_t H5Tinsert(hid_t parent_id, const char *name, size_t offset, hid_t member_id); */
SEXP R_H5Tinsert(SEXP R_parent_id, SEXP R_name, SEXP R_offset, SEXP R_member_id);
/* H5_DLL htri_t H5Tis_variable_str(hid_t type_id); */
SEXP R_H5Tis_variable_str(SEXP R_type_id);
/* H5_DLL herr_t H5Tlock(hid_t type_id); */
SEXP R_H5Tlock(SEXP R_type_id);
/* H5_DLL hid_t H5Topen2(hid_t loc_id, const char *name, hid_t tapl_id); */
SEXP R_H5Topen2(SEXP R_loc_id, SEXP R_name, SEXP R_tapl_id);
/* H5_DLL herr_t H5Tpack(hid_t type_id); */
SEXP R_H5Tpack(SEXP R_type_id);
/* H5_DLL herr_t H5Treclaim(hid_t type_id, hid_t space_id, hid_t plist_id, void *buf); */
SEXP R_H5Treclaim(SEXP R_type_id, SEXP R_space_id, SEXP R_plist_id, SEXP R_buf, SEXP _dupl_buf);
/* H5_DLL herr_t H5Trefresh(hid_t type_id); */
SEXP R_H5Trefresh(SEXP R_type_id);
/* H5_DLL herr_t H5Tset_cset(hid_t type_id, H5T_cset_t cset); */
SEXP R_H5Tset_cset(SEXP R_type_id, SEXP R_cset);
/* H5_DLL herr_t H5Tset_ebias(hid_t type_id, size_t ebias); */
SEXP R_H5Tset_ebias(SEXP R_type_id, SEXP R_ebias);
/* H5_DLL herr_t H5Tset_fields(hid_t type_id, size_t spos, size_t epos, size_t esize, size_t mpos, size_t msize); */
SEXP R_H5Tset_fields(SEXP R_type_id, SEXP R_spos, SEXP R_epos, SEXP R_esize, SEXP R_mpos, SEXP R_msize);
/* H5_DLL herr_t H5Tset_inpad(hid_t type_id, H5T_pad_t pad); */
SEXP R_H5Tset_inpad(SEXP R_type_id, SEXP R_pad);
/* H5_DLL herr_t H5Tset_norm(hid_t type_id, H5T_norm_t norm); */
SEXP R_H5Tset_norm(SEXP R_type_id, SEXP R_norm);
/* H5_DLL herr_t H5Tset_offset(hid_t type_id, size_t offset); */
SEXP R_H5Tset_offset(SEXP R_type_id, SEXP R_offset);
/* H5_DLL herr_t H5Tset_order(hid_t type_id, H5T_order_t order); */
SEXP R_H5Tset_order(SEXP R_type_id, SEXP R_order);
/* H5_DLL herr_t H5Tset_pad(hid_t type_id, H5T_pad_t lsb, H5T_pad_t msb); */
SEXP R_H5Tset_pad(SEXP R_type_id, SEXP R_lsb, SEXP R_msb);
/* H5_DLL herr_t H5Tset_precision(hid_t type_id, size_t prec); */
SEXP R_H5Tset_precision(SEXP R_type_id, SEXP R_prec);
/* H5_DLL herr_t H5Tset_sign(hid_t type_id, H5T_sign_t sign); */
SEXP R_H5Tset_sign(SEXP R_type_id, SEXP R_sign);
/* H5_DLL herr_t H5Tset_size(hid_t type_id, size_t size); */
SEXP R_H5Tset_size(SEXP R_type_id, SEXP R_size);
/* H5_DLL herr_t H5Tset_strpad(hid_t type_id, H5T_str_t strpad); */
SEXP R_H5Tset_strpad(SEXP R_type_id, SEXP R_strpad);
/* H5_DLL herr_t H5Tset_tag(hid_t type, const char *tag); */
SEXP R_H5Tset_tag(SEXP R_type, SEXP R_tag);
/* H5_DLL hid_t H5Tvlen_create(hid_t base_id); */
SEXP R_H5Tvlen_create(SEXP R_base_id);
#endif

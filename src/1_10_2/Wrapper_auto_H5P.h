#ifndef _WRAPPER_AUTO_H5P_H_
#define _WRAPPER_AUTO_H5P_H_
#include "global.h"
/* H5_DLL herr_t H5Padd_merge_committed_dtype_path(hid_t plist_id, const char *path); */
SEXP R_H5Padd_merge_committed_dtype_path(SEXP R_plist_id, SEXP R_path);
/* H5_DLL htri_t H5Pall_filters_avail(hid_t plist_id); */
SEXP R_H5Pall_filters_avail(SEXP R_plist_id);
/* H5_DLL herr_t H5Pclose(hid_t plist_id); */
SEXP R_H5Pclose(SEXP R_plist_id);
/* H5_DLL herr_t H5Pclose_class(hid_t plist_id); */
SEXP R_H5Pclose_class(SEXP R_plist_id);
/* H5_DLL hid_t H5Pcopy(hid_t plist_id); */
SEXP R_H5Pcopy(SEXP R_plist_id);
/* H5_DLL herr_t H5Pcopy_prop(hid_t dst_id, hid_t src_id, const char *name); */
SEXP R_H5Pcopy_prop(SEXP R_dst_id, SEXP R_src_id, SEXP R_name);
/* H5_DLL hid_t H5Pcreate(hid_t cls_id); */
SEXP R_H5Pcreate(SEXP R_cls_id);
/* H5_DLL hid_t H5Pdecode(const void *buf); */
SEXP R_H5Pdecode(SEXP R_buf);
/* H5_DLL herr_t H5Pencode(hid_t plist_id, void *buf, size_t *nalloc); */
SEXP R_H5Pencode(SEXP R_plist_id, SEXP R_buf, SEXP R_nalloc, SEXP _dupl_buf);
/* H5_DLL htri_t H5Pequal(hid_t id1, hid_t id2); */
SEXP R_H5Pequal(SEXP R_id1, SEXP R_id2);
/* H5_DLL htri_t H5Pexist(hid_t plist_id, const char *name); */
SEXP R_H5Pexist(SEXP R_plist_id, SEXP R_name);
/* H5_DLL herr_t H5Pfill_value_defined(hid_t plist, H5D_fill_value_t *status); */
SEXP R_H5Pfill_value_defined(SEXP R_plist, SEXP R_status);
/* H5_DLL herr_t H5Pfree_merge_committed_dtype_paths(hid_t plist_id); */
SEXP R_H5Pfree_merge_committed_dtype_paths(SEXP R_plist_id);
/* H5_DLL herr_t H5Pget(hid_t plist_id, const char *name, void * value); */
SEXP R_H5Pget(SEXP R_plist_id, SEXP R_name, SEXP R_value, SEXP _dupl_value);
/* H5_DLL herr_t H5Pget_alignment(hid_t fapl_id, hsize_t *threshold, hsize_t *alignment); */
SEXP R_H5Pget_alignment(SEXP R_fapl_id, SEXP R_threshold, SEXP R_alignment);
/* H5_DLL herr_t H5Pget_alloc_time(hid_t plist_id, H5D_alloc_time_t *alloc_time); */
SEXP R_H5Pget_alloc_time(SEXP R_plist_id, SEXP R_alloc_time);
/* H5_DLL herr_t H5Pget_attr_creation_order(hid_t plist_id, unsigned *crt_order_flags); */
SEXP R_H5Pget_attr_creation_order(SEXP R_plist_id, SEXP R_crt_order_flags);
/* H5_DLL herr_t H5Pget_attr_phase_change(hid_t plist_id, unsigned *max_compact, unsigned *min_dense); */
SEXP R_H5Pget_attr_phase_change(SEXP R_plist_id, SEXP R_max_compact, SEXP R_min_dense);
/* H5_DLL herr_t H5Pget_btree_ratios(hid_t plist_id, double *left, double *middle, double *right); */
SEXP R_H5Pget_btree_ratios(SEXP R_plist_id, SEXP R_left, SEXP R_middle, SEXP R_right);
/* H5_DLL herr_t H5Pget_cache(hid_t plist_id, int *mdc_nelmts, size_t *rdcc_nslots, size_t *rdcc_nbytes, double *rdcc_w0); */
SEXP R_H5Pget_cache(SEXP R_plist_id, SEXP R_mdc_nelmts, SEXP R_rdcc_nslots, SEXP R_rdcc_nbytes, SEXP R_rdcc_w0);
/* H5_DLL herr_t H5Pget_char_encoding(hid_t plist_id, H5T_cset_t *encoding ); */
SEXP R_H5Pget_char_encoding(SEXP R_plist_id, SEXP R_encoding);
/* H5_DLL int H5Pget_chunk(hid_t plist_id, int max_ndims, hsize_t dim[]); */
SEXP R_H5Pget_chunk(SEXP R_plist_id, SEXP R_max_ndims, SEXP R_dim);
/* H5_DLL herr_t H5Pget_chunk_cache(hid_t dapl_id, size_t *rdcc_nslots, size_t *rdcc_nbytes, double *rdcc_w0); */
SEXP R_H5Pget_chunk_cache(SEXP R_dapl_id, SEXP R_rdcc_nslots, SEXP R_rdcc_nbytes, SEXP R_rdcc_w0);
/* H5_DLL herr_t H5Pget_chunk_opts(hid_t plist_id, unsigned *opts); */
SEXP R_H5Pget_chunk_opts(SEXP R_plist_id, SEXP R_opts);
/* H5_DLL hid_t H5Pget_class(hid_t plist_id); */
SEXP R_H5Pget_class(SEXP R_plist_id);
/* H5_DLL char *H5Pget_class_name(hid_t pclass_id); */
SEXP R_H5Pget_class_name(SEXP R_pclass_id);
/* H5_DLL hid_t H5Pget_class_parent(hid_t pclass_id); */
SEXP R_H5Pget_class_parent(SEXP R_pclass_id);
/* H5_DLL herr_t H5Pget_copy_object(hid_t plist_id, unsigned *crt_intmd ); */
SEXP R_H5Pget_copy_object(SEXP R_plist_id, SEXP R_crt_intmd);
/* H5_DLL herr_t H5Pget_core_write_tracking(hid_t fapl_id, hbool_t *is_enabled, size_t *page_size); */
SEXP R_H5Pget_core_write_tracking(SEXP R_fapl_id, SEXP R_is_enabled, SEXP R_page_size);
/* H5_DLL herr_t H5Pget_create_intermediate_group(hid_t plist_id, unsigned *crt_intmd ); */
SEXP R_H5Pget_create_intermediate_group(SEXP R_plist_id, SEXP R_crt_intmd);
/* H5_DLL ssize_t H5Pget_data_transform(hid_t plist_id, char* expression , size_t size); */
SEXP R_H5Pget_data_transform(SEXP R_plist_id, SEXP R_expression, SEXP R_size);
/* H5_DLL hid_t H5Pget_driver(hid_t plist_id); */
SEXP R_H5Pget_driver(SEXP R_plist_id);
/* H5_DLL H5Z_EDC_t H5Pget_edc_check(hid_t plist_id); */
SEXP R_H5Pget_edc_check(SEXP R_plist_id);
/* H5_DLL ssize_t H5Pget_efile_prefix(hid_t dapl_id, char* prefix , size_t size); */
SEXP R_H5Pget_efile_prefix(SEXP R_dapl_id, SEXP R_prefix, SEXP R_size);
/* H5_DLL herr_t H5Pget_elink_acc_flags(hid_t lapl_id, unsigned *flags); */
SEXP R_H5Pget_elink_acc_flags(SEXP R_lapl_id, SEXP R_flags);
/* H5_DLL hid_t H5Pget_elink_fapl(hid_t lapl_id); */
SEXP R_H5Pget_elink_fapl(SEXP R_lapl_id);
/* H5_DLL herr_t H5Pget_elink_file_cache_size(hid_t plist_id, unsigned *efc_size); */
SEXP R_H5Pget_elink_file_cache_size(SEXP R_plist_id, SEXP R_efc_size);
/* H5_DLL ssize_t H5Pget_elink_prefix(hid_t plist_id, char *prefix, size_t size); */
SEXP R_H5Pget_elink_prefix(SEXP R_plist_id, SEXP R_prefix, SEXP R_size);
/* H5_DLL herr_t H5Pget_est_link_info(hid_t plist_id, unsigned *est_num_entries , unsigned *est_name_len ); */
SEXP R_H5Pget_est_link_info(SEXP R_plist_id, SEXP R_est_num_entries, SEXP R_est_name_len);
/* H5_DLL herr_t H5Pget_evict_on_close(hid_t fapl_id, hbool_t *evict_on_close); */
SEXP R_H5Pget_evict_on_close(SEXP R_fapl_id, SEXP R_evict_on_close);
/* H5_DLL herr_t H5Pget_external(hid_t plist_id, unsigned idx, size_t name_size, char *name, off_t *offset, hsize_t *size); */
SEXP R_H5Pget_external(SEXP R_plist_id, SEXP R_idx, SEXP R_name_size, SEXP R_name, SEXP R_offset, SEXP R_size);
/* H5_DLL int H5Pget_external_count(hid_t plist_id); */
SEXP R_H5Pget_external_count(SEXP R_plist_id);
/* H5_DLL herr_t H5Pget_family_offset(hid_t fapl_id, hsize_t *offset); */
SEXP R_H5Pget_family_offset(SEXP R_fapl_id, SEXP R_offset);
/* H5_DLL herr_t H5Pget_fclose_degree(hid_t fapl_id, H5F_close_degree_t *degree); */
SEXP R_H5Pget_fclose_degree(SEXP R_fapl_id, SEXP R_degree);
/* H5_DLL herr_t H5Pget_file_space(hid_t plist_id, H5F_file_space_type_t *strategy, hsize_t *threshold); */
SEXP R_H5Pget_file_space(SEXP R_plist_id, SEXP R_strategy, SEXP R_threshold);
/* H5_DLL herr_t H5Pget_file_space_page_size(hid_t plist_id, hsize_t *fsp_size); */
SEXP R_H5Pget_file_space_page_size(SEXP R_plist_id, SEXP R_fsp_size);
/* H5_DLL herr_t H5Pget_file_space_strategy(hid_t plist_id, H5F_fspace_strategy_t *strategy, hbool_t *persist, hsize_t *threshold); */
SEXP R_H5Pget_file_space_strategy(SEXP R_plist_id, SEXP R_strategy, SEXP R_persist, SEXP R_threshold);
/* H5_DLL herr_t H5Pget_fill_time(hid_t plist_id, H5D_fill_time_t *fill_time); */
SEXP R_H5Pget_fill_time(SEXP R_plist_id, SEXP R_fill_time);
/* H5_DLL herr_t H5Pget_fill_value(hid_t plist_id, hid_t type_id, void *value); */
SEXP R_H5Pget_fill_value(SEXP R_plist_id, SEXP R_type_id, SEXP R_value, SEXP _dupl_value);
/* H5_DLL herr_t H5Pget_filter_by_id2(hid_t plist_id, H5Z_filter_t id, unsigned int *flags, size_t *cd_nelmts, unsigned cd_values[], size_t namelen, char name[], unsigned *filter_config); */
SEXP R_H5Pget_filter_by_id2(SEXP R_plist_id, SEXP R_id, SEXP R_flags, SEXP R_cd_nelmts, SEXP R_cd_values, SEXP R_namelen, SEXP R_name, SEXP R_filter_config);
/* H5_DLL H5Z_filter_t H5Pget_filter2(hid_t plist_id, unsigned filter, unsigned int *flags, size_t *cd_nelmts, unsigned cd_values[], size_t namelen, char name[], unsigned *filter_config ); */
SEXP R_H5Pget_filter2(SEXP R_plist_id, SEXP R_filter, SEXP R_flags, SEXP R_cd_nelmts, SEXP R_cd_values, SEXP R_namelen, SEXP R_name, SEXP R_filter_config);
/* H5_DLL herr_t H5Pget_gc_references(hid_t fapl_id, unsigned *gc_ref); */
SEXP R_H5Pget_gc_references(SEXP R_fapl_id, SEXP R_gc_ref);
/* H5_DLL herr_t H5Pget_hyper_vector_size(hid_t fapl_id, size_t *size); */
SEXP R_H5Pget_hyper_vector_size(SEXP R_fapl_id, SEXP R_size);
/* H5_DLL herr_t H5Pget_istore_k(hid_t plist_id, unsigned *ik); */
SEXP R_H5Pget_istore_k(SEXP R_plist_id, SEXP R_ik);
/* H5_DLL H5D_layout_t H5Pget_layout(hid_t plist_id); */
SEXP R_H5Pget_layout(SEXP R_plist_id);
/* H5_DLL herr_t H5Pget_libver_bounds(hid_t plist_id, H5F_libver_t *low, H5F_libver_t *high); */
SEXP R_H5Pget_libver_bounds(SEXP R_plist_id, SEXP R_low, SEXP R_high);
/* H5_DLL herr_t H5Pget_link_creation_order(hid_t plist_id, unsigned *crt_order_flags ); */
SEXP R_H5Pget_link_creation_order(SEXP R_plist_id, SEXP R_crt_order_flags);
/* H5_DLL herr_t H5Pget_link_phase_change(hid_t plist_id, unsigned *max_compact , unsigned *min_dense ); */
SEXP R_H5Pget_link_phase_change(SEXP R_plist_id, SEXP R_max_compact, SEXP R_min_dense);
/* H5_DLL herr_t H5Pget_local_heap_size_hint(hid_t plist_id, size_t *size_hint ); */
SEXP R_H5Pget_local_heap_size_hint(SEXP R_plist_id, SEXP R_size_hint);
/* H5_DLL herr_t H5Pget_mdc_config(hid_t plist_id, H5AC_cache_config_t * config_ptr);  */
SEXP R_H5Pget_mdc_config (SEXP R_plist_id, SEXP R_config_ptr);
/* H5_DLL herr_t H5Pget_mdc_image_config(hid_t plist_id, H5AC_cache_image_config_t *config_ptr ); */
SEXP R_H5Pget_mdc_image_config(SEXP R_plist_id, SEXP R_config_ptr);
/* H5_DLL herr_t H5Pget_mdc_log_options(hid_t plist_id, hbool_t *is_enabled, char *location, size_t *location_size, hbool_t *start_on_access); */
SEXP R_H5Pget_mdc_log_options(SEXP R_plist_id, SEXP R_is_enabled, SEXP R_location, SEXP R_location_size, SEXP R_start_on_access);
/* H5_DLL herr_t H5Pget_meta_block_size(hid_t fapl_id, hsize_t *size); */
SEXP R_H5Pget_meta_block_size(SEXP R_fapl_id, SEXP R_size);
/* H5_DLL herr_t H5Pget_metadata_read_attempts(hid_t plist_id, unsigned *attempts); */
SEXP R_H5Pget_metadata_read_attempts(SEXP R_plist_id, SEXP R_attempts);
/* H5_DLL herr_t H5Pget_multi_type(hid_t fapl_id, H5FD_mem_t *type); */
SEXP R_H5Pget_multi_type(SEXP R_fapl_id, SEXP R_type);
/* H5_DLL int H5Pget_nfilters(hid_t plist_id); */
SEXP R_H5Pget_nfilters(SEXP R_plist_id);
/* H5_DLL herr_t H5Pget_nlinks(hid_t plist_id, size_t *nlinks); */
SEXP R_H5Pget_nlinks(SEXP R_plist_id, SEXP R_nlinks);
/* H5_DLL herr_t H5Pget_nprops(hid_t id, size_t *nprops); */
SEXP R_H5Pget_nprops(SEXP R_id, SEXP R_nprops);
/* H5_DLL herr_t H5Pget_obj_track_times(hid_t plist_id, hbool_t *track_times); */
SEXP R_H5Pget_obj_track_times(SEXP R_plist_id, SEXP R_track_times);
/* H5_DLL herr_t H5Pget_page_buffer_size(hid_t plist_id, size_t *buf_size, unsigned *min_meta_per, unsigned *min_raw_per); */
SEXP R_H5Pget_page_buffer_size(SEXP R_plist_id, SEXP R_buf_size, SEXP R_min_meta_per, SEXP R_min_raw_per);
/* H5_DLL int H5Pget_preserve(hid_t plist_id); */
SEXP R_H5Pget_preserve(SEXP R_plist_id);
/* H5_DLL herr_t H5Pget_shared_mesg_index(hid_t plist_id, unsigned index_num, unsigned *mesg_type_flags, unsigned *min_mesg_size); */
SEXP R_H5Pget_shared_mesg_index(SEXP R_plist_id, SEXP R_index_num, SEXP R_mesg_type_flags, SEXP R_min_mesg_size);
/* H5_DLL herr_t H5Pget_shared_mesg_nindexes(hid_t plist_id, unsigned *nindexes); */
SEXP R_H5Pget_shared_mesg_nindexes(SEXP R_plist_id, SEXP R_nindexes);
/* H5_DLL herr_t H5Pget_shared_mesg_phase_change(hid_t plist_id, unsigned *max_list, unsigned *min_btree); */
SEXP R_H5Pget_shared_mesg_phase_change(SEXP R_plist_id, SEXP R_max_list, SEXP R_min_btree);
/* H5_DLL herr_t H5Pget_sieve_buf_size(hid_t fapl_id, size_t *size); */
SEXP R_H5Pget_sieve_buf_size(SEXP R_fapl_id, SEXP R_size);
/* H5_DLL herr_t H5Pget_size(hid_t id, const char *name, size_t *size); */
SEXP R_H5Pget_size(SEXP R_id, SEXP R_name, SEXP R_size);
/* H5_DLL herr_t H5Pget_sizes(hid_t plist_id, size_t *sizeof_addr, size_t *sizeof_size); */
SEXP R_H5Pget_sizes(SEXP R_plist_id, SEXP R_sizeof_addr, SEXP R_sizeof_size);
/* H5_DLL herr_t H5Pget_small_data_block_size(hid_t fapl_id, hsize_t *size); */
SEXP R_H5Pget_small_data_block_size(SEXP R_fapl_id, SEXP R_size);
/* H5_DLL herr_t H5Pget_sym_k(hid_t plist_id, unsigned *ik, unsigned *lk); */
SEXP R_H5Pget_sym_k(SEXP R_plist_id, SEXP R_ik, SEXP R_lk);
/* H5_DLL herr_t H5Pget_userblock(hid_t plist_id, hsize_t *size); */
SEXP R_H5Pget_userblock(SEXP R_plist_id, SEXP R_size);
/* H5_DLL herr_t H5Pget_version(hid_t plist_id, unsigned *boot, unsigned *freelist, unsigned *stab, unsigned *shhdr); */
SEXP R_H5Pget_version(SEXP R_plist_id, SEXP R_boot, SEXP R_freelist, SEXP R_stab, SEXP R_shhdr);
/* H5_DLL herr_t H5Pget_virtual_count(hid_t dcpl_id, size_t *count); */
SEXP R_H5Pget_virtual_count(SEXP R_dcpl_id, SEXP R_count);
/* H5_DLL ssize_t H5Pget_virtual_dsetname(hid_t dcpl_id, size_t index, char *name, size_t size); */
SEXP R_H5Pget_virtual_dsetname(SEXP R_dcpl_id, SEXP R_index, SEXP R_name, SEXP R_size);
/* H5_DLL ssize_t H5Pget_virtual_filename(hid_t dcpl_id, size_t index, char *name, size_t size); */
SEXP R_H5Pget_virtual_filename(SEXP R_dcpl_id, SEXP R_index, SEXP R_name, SEXP R_size);
/* H5_DLL ssize_t H5Pget_virtual_prefix(hid_t dapl_id, char* prefix , size_t size); */
SEXP R_H5Pget_virtual_prefix(SEXP R_dapl_id, SEXP R_prefix, SEXP R_size);
/* H5_DLL herr_t H5Pget_virtual_printf_gap(hid_t plist_id, hsize_t *gap_size); */
SEXP R_H5Pget_virtual_printf_gap(SEXP R_plist_id, SEXP R_gap_size);
/* H5_DLL hid_t H5Pget_virtual_srcspace(hid_t dcpl_id, size_t index); */
SEXP R_H5Pget_virtual_srcspace(SEXP R_dcpl_id, SEXP R_index);
/* H5_DLL herr_t H5Pget_virtual_view(hid_t plist_id, H5D_vds_view_t *view); */
SEXP R_H5Pget_virtual_view(SEXP R_plist_id, SEXP R_view);
/* H5_DLL hid_t H5Pget_virtual_vspace(hid_t dcpl_id, size_t index); */
SEXP R_H5Pget_virtual_vspace(SEXP R_dcpl_id, SEXP R_index);
/* H5_DLL htri_t H5Pisa_class(hid_t plist_id, hid_t pclass_id); */
SEXP R_H5Pisa_class(SEXP R_plist_id, SEXP R_pclass_id);
/* H5_DLL herr_t H5Pmodify_filter(hid_t plist_id, H5Z_filter_t filter, unsigned int flags, size_t cd_nelmts, const unsigned int cd_values[]); */
SEXP R_H5Pmodify_filter(SEXP R_plist_id, SEXP R_filter, SEXP R_flags, SEXP R_cd_nelmts, SEXP R_cd_values);
/* H5_DLL herr_t H5Premove(hid_t plist_id, const char *name); */
SEXP R_H5Premove(SEXP R_plist_id, SEXP R_name);
/* H5_DLL herr_t H5Premove_filter(hid_t plist_id, H5Z_filter_t filter); */
SEXP R_H5Premove_filter(SEXP R_plist_id, SEXP R_filter);
/* H5_DLL herr_t H5Pset(hid_t plist_id, const char *name, const void *value); */
SEXP R_H5Pset(SEXP R_plist_id, SEXP R_name, SEXP R_value);
/* H5_DLL herr_t H5Pset_alignment(hid_t fapl_id, hsize_t threshold, hsize_t alignment); */
SEXP R_H5Pset_alignment(SEXP R_fapl_id, SEXP R_threshold, SEXP R_alignment);
/* H5_DLL herr_t H5Pset_alloc_time(hid_t plist_id, H5D_alloc_time_t alloc_time); */
SEXP R_H5Pset_alloc_time(SEXP R_plist_id, SEXP R_alloc_time);
/* H5_DLL herr_t H5Pset_attr_creation_order(hid_t plist_id, unsigned crt_order_flags); */
SEXP R_H5Pset_attr_creation_order(SEXP R_plist_id, SEXP R_crt_order_flags);
/* H5_DLL herr_t H5Pset_attr_phase_change(hid_t plist_id, unsigned max_compact, unsigned min_dense); */
SEXP R_H5Pset_attr_phase_change(SEXP R_plist_id, SEXP R_max_compact, SEXP R_min_dense);
/* H5_DLL herr_t H5Pset_btree_ratios(hid_t plist_id, double left, double middle, double right); */
SEXP R_H5Pset_btree_ratios(SEXP R_plist_id, SEXP R_left, SEXP R_middle, SEXP R_right);
/* H5_DLL herr_t H5Pset_buffer(hid_t plist_id, size_t size, void *tconv, void *bkg); */
SEXP R_H5Pset_buffer(SEXP R_plist_id, SEXP R_size, SEXP R_tconv, SEXP R_bkg, SEXP _dupl_tconv, SEXP _dupl_bkg);
/* H5_DLL herr_t H5Pset_cache(hid_t plist_id, int mdc_nelmts, size_t rdcc_nslots, size_t rdcc_nbytes, double rdcc_w0); */
SEXP R_H5Pset_cache(SEXP R_plist_id, SEXP R_mdc_nelmts, SEXP R_rdcc_nslots, SEXP R_rdcc_nbytes, SEXP R_rdcc_w0);
/* H5_DLL herr_t H5Pset_char_encoding(hid_t plist_id, H5T_cset_t encoding); */
SEXP R_H5Pset_char_encoding(SEXP R_plist_id, SEXP R_encoding);
/* H5_DLL herr_t H5Pset_chunk(hid_t plist_id, int ndims, const hsize_t dim[]); */
SEXP R_H5Pset_chunk(SEXP R_plist_id, SEXP R_ndims, SEXP R_dim);
/* H5_DLL herr_t H5Pset_chunk_cache(hid_t dapl_id, size_t rdcc_nslots, size_t rdcc_nbytes, double rdcc_w0); */
SEXP R_H5Pset_chunk_cache(SEXP R_dapl_id, SEXP R_rdcc_nslots, SEXP R_rdcc_nbytes, SEXP R_rdcc_w0);
/* H5_DLL herr_t H5Pset_chunk_opts(hid_t plist_id, unsigned opts); */
SEXP R_H5Pset_chunk_opts(SEXP R_plist_id, SEXP R_opts);
/* H5_DLL herr_t H5Pset_copy_object(hid_t plist_id, unsigned crt_intmd); */
SEXP R_H5Pset_copy_object(SEXP R_plist_id, SEXP R_crt_intmd);
/* H5_DLL herr_t H5Pset_core_write_tracking(hid_t fapl_id, hbool_t is_enabled, size_t page_size); */
SEXP R_H5Pset_core_write_tracking(SEXP R_fapl_id, SEXP R_is_enabled, SEXP R_page_size);
/* H5_DLL herr_t H5Pset_create_intermediate_group(hid_t plist_id, unsigned crt_intmd); */
SEXP R_H5Pset_create_intermediate_group(SEXP R_plist_id, SEXP R_crt_intmd);
/* H5_DLL herr_t H5Pset_data_transform(hid_t plist_id, const char* expression); */
SEXP R_H5Pset_data_transform(SEXP R_plist_id, SEXP R_expression);
/* H5_DLL herr_t H5Pset_deflate(hid_t plist_id, unsigned aggression); */
SEXP R_H5Pset_deflate(SEXP R_plist_id, SEXP R_aggression);
/* H5_DLL herr_t H5Pset_driver(hid_t plist_id, hid_t driver_id, const void *driver_info); */
SEXP R_H5Pset_driver(SEXP R_plist_id, SEXP R_driver_id, SEXP R_driver_info);
/* H5_DLL herr_t H5Pset_edc_check(hid_t plist_id, H5Z_EDC_t check); */
SEXP R_H5Pset_edc_check(SEXP R_plist_id, SEXP R_check);
/* H5_DLL herr_t H5Pset_efile_prefix(hid_t dapl_id, const char* prefix); */
SEXP R_H5Pset_efile_prefix(SEXP R_dapl_id, SEXP R_prefix);
/* H5_DLL herr_t H5Pset_elink_acc_flags(hid_t lapl_id, unsigned flags); */
SEXP R_H5Pset_elink_acc_flags(SEXP R_lapl_id, SEXP R_flags);
/* H5_DLL herr_t H5Pset_elink_fapl(hid_t lapl_id, hid_t fapl_id); */
SEXP R_H5Pset_elink_fapl(SEXP R_lapl_id, SEXP R_fapl_id);
/* H5_DLL herr_t H5Pset_elink_file_cache_size(hid_t plist_id, unsigned efc_size); */
SEXP R_H5Pset_elink_file_cache_size(SEXP R_plist_id, SEXP R_efc_size);
/* H5_DLL herr_t H5Pset_elink_prefix(hid_t plist_id, const char *prefix); */
SEXP R_H5Pset_elink_prefix(SEXP R_plist_id, SEXP R_prefix);
/* H5_DLL herr_t H5Pset_est_link_info(hid_t plist_id, unsigned est_num_entries, unsigned est_name_len); */
SEXP R_H5Pset_est_link_info(SEXP R_plist_id, SEXP R_est_num_entries, SEXP R_est_name_len);
/* H5_DLL herr_t H5Pset_evict_on_close(hid_t fapl_id, hbool_t evict_on_close); */
SEXP R_H5Pset_evict_on_close(SEXP R_fapl_id, SEXP R_evict_on_close);
/* H5_DLL herr_t H5Pset_external(hid_t plist_id, const char *name, off_t offset, hsize_t size); */
SEXP R_H5Pset_external(SEXP R_plist_id, SEXP R_name, SEXP R_offset, SEXP R_size);
/* H5_DLL herr_t H5Pset_family_offset(hid_t fapl_id, hsize_t offset); */
SEXP R_H5Pset_family_offset(SEXP R_fapl_id, SEXP R_offset);
/* H5_DLL herr_t H5Pset_fclose_degree(hid_t fapl_id, H5F_close_degree_t degree); */
SEXP R_H5Pset_fclose_degree(SEXP R_fapl_id, SEXP R_degree);
/* H5_DLL herr_t H5Pset_file_image(hid_t fapl_id, void *buf_ptr, size_t buf_len); */
SEXP R_H5Pset_file_image(SEXP R_fapl_id, SEXP R_buf_ptr, SEXP R_buf_len, SEXP _dupl_buf_ptr);
/* H5_DLL herr_t H5Pset_file_space(hid_t plist_id, H5F_file_space_type_t strategy, hsize_t threshold); */
SEXP R_H5Pset_file_space(SEXP R_plist_id, SEXP R_strategy, SEXP R_threshold);
/* H5_DLL herr_t H5Pset_file_space_page_size(hid_t plist_id, hsize_t fsp_size); */
SEXP R_H5Pset_file_space_page_size(SEXP R_plist_id, SEXP R_fsp_size);
/* H5_DLL herr_t H5Pset_file_space_strategy(hid_t plist_id, H5F_fspace_strategy_t strategy, hbool_t persist, hsize_t threshold); */
SEXP R_H5Pset_file_space_strategy(SEXP R_plist_id, SEXP R_strategy, SEXP R_persist, SEXP R_threshold);
/* H5_DLL herr_t H5Pset_fill_time(hid_t plist_id, H5D_fill_time_t fill_time); */
SEXP R_H5Pset_fill_time(SEXP R_plist_id, SEXP R_fill_time);
/* H5_DLL herr_t H5Pset_fill_value(hid_t plist_id, hid_t type_id, const void *value); */
SEXP R_H5Pset_fill_value(SEXP R_plist_id, SEXP R_type_id, SEXP R_value);
/* H5_DLL herr_t H5Pset_filter(hid_t plist_id, H5Z_filter_t filter, unsigned int flags, size_t cd_nelmts, const unsigned int c_values[]); */
SEXP R_H5Pset_filter(SEXP R_plist_id, SEXP R_filter, SEXP R_flags, SEXP R_cd_nelmts, SEXP R_c_values);
/* H5_DLL herr_t H5Pset_fletcher32(hid_t plist_id); */
SEXP R_H5Pset_fletcher32(SEXP R_plist_id);
/* H5_DLL herr_t H5Pset_gc_references(hid_t fapl_id, unsigned gc_ref); */
SEXP R_H5Pset_gc_references(SEXP R_fapl_id, SEXP R_gc_ref);
/* H5_DLL herr_t H5Pset_hyper_vector_size(hid_t fapl_id, size_t size); */
SEXP R_H5Pset_hyper_vector_size(SEXP R_fapl_id, SEXP R_size);
/* H5_DLL herr_t H5Pset_istore_k(hid_t plist_id, unsigned ik); */
SEXP R_H5Pset_istore_k(SEXP R_plist_id, SEXP R_ik);
/* H5_DLL herr_t H5Pset_layout(hid_t plist_id, H5D_layout_t layout); */
SEXP R_H5Pset_layout(SEXP R_plist_id, SEXP R_layout);
/* H5_DLL herr_t H5Pset_libver_bounds(hid_t plist_id, H5F_libver_t low, H5F_libver_t high); */
SEXP R_H5Pset_libver_bounds(SEXP R_plist_id, SEXP R_low, SEXP R_high);
/* H5_DLL herr_t H5Pset_link_creation_order(hid_t plist_id, unsigned crt_order_flags); */
SEXP R_H5Pset_link_creation_order(SEXP R_plist_id, SEXP R_crt_order_flags);
/* H5_DLL herr_t H5Pset_link_phase_change(hid_t plist_id, unsigned max_compact, unsigned min_dense); */
SEXP R_H5Pset_link_phase_change(SEXP R_plist_id, SEXP R_max_compact, SEXP R_min_dense);
/* H5_DLL herr_t H5Pset_local_heap_size_hint(hid_t plist_id, size_t size_hint); */
SEXP R_H5Pset_local_heap_size_hint(SEXP R_plist_id, SEXP R_size_hint);
/* H5_DLL herr_t H5Pset_mdc_config(hid_t plist_id, H5AC_cache_config_t * config_ptr); */
SEXP R_H5Pset_mdc_config(SEXP R_plist_id, SEXP R_config_ptr);
/* H5_DLL herr_t H5Pset_mdc_image_config(hid_t plist_id, H5AC_cache_image_config_t *config_ptr); */
SEXP R_H5Pset_mdc_image_config(SEXP R_plist_id, SEXP R_config_ptr);
/* H5_DLL herr_t H5Pset_mdc_log_options(hid_t plist_id, hbool_t is_enabled, const char *location, hbool_t start_on_access); */
SEXP R_H5Pset_mdc_log_options(SEXP R_plist_id, SEXP R_is_enabled, SEXP R_location, SEXP R_start_on_access);
/* H5_DLL herr_t H5Pset_meta_block_size(hid_t fapl_id, hsize_t size); */
SEXP R_H5Pset_meta_block_size(SEXP R_fapl_id, SEXP R_size);
/* H5_DLL herr_t H5Pset_metadata_read_attempts(hid_t plist_id, unsigned attempts); */
SEXP R_H5Pset_metadata_read_attempts(SEXP R_plist_id, SEXP R_attempts);
/* H5_DLL herr_t H5Pset_multi_type(hid_t fapl_id, H5FD_mem_t type); */
SEXP R_H5Pset_multi_type(SEXP R_fapl_id, SEXP R_type);
/* H5_DLL herr_t H5Pset_nbit(hid_t plist_id); */
SEXP R_H5Pset_nbit(SEXP R_plist_id);
/* H5_DLL herr_t H5Pset_nlinks(hid_t plist_id, size_t nlinks); */
SEXP R_H5Pset_nlinks(SEXP R_plist_id, SEXP R_nlinks);
/* H5_DLL herr_t H5Pset_obj_track_times(hid_t plist_id, hbool_t track_times); */
SEXP R_H5Pset_obj_track_times(SEXP R_plist_id, SEXP R_track_times);
/* H5_DLL herr_t H5Pset_page_buffer_size(hid_t plist_id, size_t buf_size, unsigned min_meta_per, unsigned min_raw_per); */
SEXP R_H5Pset_page_buffer_size(SEXP R_plist_id, SEXP R_buf_size, SEXP R_min_meta_per, SEXP R_min_raw_per);
/* H5_DLL herr_t H5Pset_preserve(hid_t plist_id, hbool_t status); */
SEXP R_H5Pset_preserve(SEXP R_plist_id, SEXP R_status);
/* H5_DLL herr_t H5Pset_scaleoffset(hid_t plist_id, H5Z_SO_scale_type_t scale_type, int scale_factor); */
SEXP R_H5Pset_scaleoffset(SEXP R_plist_id, SEXP R_scale_type, SEXP R_scale_factor);
/* H5_DLL herr_t H5Pset_shared_mesg_index(hid_t plist_id, unsigned index_num, unsigned mesg_type_flags, unsigned min_mesg_size); */
SEXP R_H5Pset_shared_mesg_index(SEXP R_plist_id, SEXP R_index_num, SEXP R_mesg_type_flags, SEXP R_min_mesg_size);
/* H5_DLL herr_t H5Pset_shared_mesg_nindexes(hid_t plist_id, unsigned nindexes); */
SEXP R_H5Pset_shared_mesg_nindexes(SEXP R_plist_id, SEXP R_nindexes);
/* H5_DLL herr_t H5Pset_shared_mesg_phase_change(hid_t plist_id, unsigned max_list, unsigned min_btree); */
SEXP R_H5Pset_shared_mesg_phase_change(SEXP R_plist_id, SEXP R_max_list, SEXP R_min_btree);
/* H5_DLL herr_t H5Pset_shuffle(hid_t plist_id); */
SEXP R_H5Pset_shuffle(SEXP R_plist_id);
/* H5_DLL herr_t H5Pset_sieve_buf_size(hid_t fapl_id, size_t size); */
SEXP R_H5Pset_sieve_buf_size(SEXP R_fapl_id, SEXP R_size);
/* H5_DLL herr_t H5Pset_sizes(hid_t plist_id, size_t sizeof_addr, size_t sizeof_size); */
SEXP R_H5Pset_sizes(SEXP R_plist_id, SEXP R_sizeof_addr, SEXP R_sizeof_size);
/* H5_DLL herr_t H5Pset_small_data_block_size(hid_t fapl_id, hsize_t size); */
SEXP R_H5Pset_small_data_block_size(SEXP R_fapl_id, SEXP R_size);
/* H5_DLL herr_t H5Pset_sym_k(hid_t plist_id, unsigned ik, unsigned lk); */
SEXP R_H5Pset_sym_k(SEXP R_plist_id, SEXP R_ik, SEXP R_lk);
/* H5_DLL herr_t H5Pset_szip(hid_t plist_id, unsigned options_mask, unsigned pixels_per_block); */
SEXP R_H5Pset_szip(SEXP R_plist_id, SEXP R_options_mask, SEXP R_pixels_per_block);
/* H5_DLL herr_t H5Pset_userblock(hid_t plist_id, hsize_t size); */
SEXP R_H5Pset_userblock(SEXP R_plist_id, SEXP R_size);
/* H5_DLL herr_t H5Pset_virtual(hid_t dcpl_id, hid_t vspace_id, const char *src_file_name, const char *src_dset_name, hid_t src_space_id); */
SEXP R_H5Pset_virtual(SEXP R_dcpl_id, SEXP R_vspace_id, SEXP R_src_file_name, SEXP R_src_dset_name, SEXP R_src_space_id);
/* H5_DLL herr_t H5Pset_virtual_prefix(hid_t dapl_id, const char* prefix); */
SEXP R_H5Pset_virtual_prefix(SEXP R_dapl_id, SEXP R_prefix);
/* H5_DLL herr_t H5Pset_virtual_printf_gap(hid_t plist_id, hsize_t gap_size); */
SEXP R_H5Pset_virtual_printf_gap(SEXP R_plist_id, SEXP R_gap_size);
/* H5_DLL herr_t H5Pset_virtual_view(hid_t plist_id, H5D_vds_view_t view); */
SEXP R_H5Pset_virtual_view(SEXP R_plist_id, SEXP R_view);
/* H5_DLL herr_t H5Punregister(hid_t pclass_id, const char *name); */
SEXP R_H5Punregister(SEXP R_pclass_id, SEXP R_name);
#endif

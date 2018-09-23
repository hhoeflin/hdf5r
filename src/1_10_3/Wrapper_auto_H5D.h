#ifndef _WRAPPER_AUTO_H5D_H_
#define _WRAPPER_AUTO_H5D_H_
#include "global.h"
/* H5_DLL herr_t H5Dclose(hid_t dset_id); */
SEXP R_H5Dclose(SEXP R_dset_id);
/* H5_DLL hid_t H5Dcreate_anon(hid_t file_id, hid_t type_id, hid_t space_id, hid_t plist_id, hid_t dapl_id); */
SEXP R_H5Dcreate_anon(SEXP R_file_id, SEXP R_type_id, SEXP R_space_id, SEXP R_plist_id, SEXP R_dapl_id);
/* H5_DLL hid_t H5Dcreate2(hid_t loc_id, const char *name, hid_t type_id, hid_t space_id, hid_t lcpl_id, hid_t dcpl_id, hid_t dapl_id); */
SEXP R_H5Dcreate2(SEXP R_loc_id, SEXP R_name, SEXP R_type_id, SEXP R_space_id, SEXP R_lcpl_id, SEXP R_dcpl_id, SEXP R_dapl_id);
/* H5_DLL herr_t H5Ddebug(hid_t dset_id); */
SEXP R_H5Ddebug(SEXP R_dset_id);
/* H5_DLL herr_t H5Dfill(const void *fill, hid_t fill_type, void *buf, hid_t buf_type, hid_t space); */
SEXP R_H5Dfill(SEXP R_fill, SEXP R_fill_type, SEXP R_buf, SEXP R_buf_type, SEXP R_space, SEXP _dupl_buf);
/* H5_DLL herr_t H5Dflush(hid_t dset_id); */
SEXP R_H5Dflush(SEXP R_dset_id);
/* H5_DLL herr_t H5Dformat_convert(hid_t dset_id); */
SEXP R_H5Dformat_convert(SEXP R_dset_id);
/* H5_DLL hid_t H5Dget_access_plist(hid_t dset_id); */
SEXP R_H5Dget_access_plist(SEXP R_dset_id);
/* H5_DLL herr_t H5Dget_chunk_index_type(hid_t did, H5D_chunk_index_t *idx_type); */
SEXP R_H5Dget_chunk_index_type(SEXP R_did, SEXP R_idx_type);
/* H5_DLL herr_t H5Dget_chunk_storage_size(hid_t dset_id, const hsize_t *offset, hsize_t *chunk_bytes); */
SEXP R_H5Dget_chunk_storage_size(SEXP R_dset_id, SEXP R_offset, SEXP R_chunk_bytes);
/* H5_DLL hid_t H5Dget_create_plist(hid_t dset_id); */
SEXP R_H5Dget_create_plist(SEXP R_dset_id);
/* H5_DLL haddr_t H5Dget_offset(hid_t dset_id); */
SEXP R_H5Dget_offset(SEXP R_dset_id);
/* H5_DLL hid_t H5Dget_space(hid_t dset_id); */
SEXP R_H5Dget_space(SEXP R_dset_id);
/* H5_DLL herr_t H5Dget_space_status(hid_t dset_id, H5D_space_status_t *allocation); */
SEXP R_H5Dget_space_status(SEXP R_dset_id, SEXP R_allocation);
/* H5_DLL hsize_t H5Dget_storage_size(hid_t dset_id); */
SEXP R_H5Dget_storage_size(SEXP R_dset_id);
/* H5_DLL hid_t H5Dget_type(hid_t dset_id); */
SEXP R_H5Dget_type(SEXP R_dset_id);
/* H5_DLL hid_t H5Dopen2(hid_t file_id, const char *name, hid_t dapl_id); */
SEXP R_H5Dopen2(SEXP R_file_id, SEXP R_name, SEXP R_dapl_id);
/* H5_DLL herr_t H5Dread(hid_t dset_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t plist_id, void *buf); */
SEXP R_H5Dread(SEXP R_dset_id, SEXP R_mem_type_id, SEXP R_mem_space_id, SEXP R_file_space_id, SEXP R_plist_id, SEXP R_buf, SEXP _dupl_buf);
/* H5_DLL herr_t H5Dread_chunk(hid_t dset_id, hid_t dxpl_id, const hsize_t *offset, uint32_t *filters, void *buf); */
SEXP R_H5Dread_chunk(SEXP R_dset_id, SEXP R_dxpl_id, SEXP R_offset, SEXP R_filters, SEXP R_buf, SEXP _dupl_buf);
/* H5_DLL herr_t H5Drefresh(hid_t dset_id); */
SEXP R_H5Drefresh(SEXP R_dset_id);
/* H5_DLL herr_t H5Dset_extent(hid_t dset_id, const hsize_t size[]); */
SEXP R_H5Dset_extent(SEXP R_dset_id, SEXP R_size);
/* H5_DLL herr_t H5Dvlen_get_buf_size(hid_t dataset_id, hid_t type_id, hid_t space_id, hsize_t *size); */
SEXP R_H5Dvlen_get_buf_size(SEXP R_dataset_id, SEXP R_type_id, SEXP R_space_id, SEXP R_size);
/* H5_DLL herr_t H5Dvlen_reclaim(hid_t type_id, hid_t space_id, hid_t plist_id, void *buf); */
SEXP R_H5Dvlen_reclaim(SEXP R_type_id, SEXP R_space_id, SEXP R_plist_id, SEXP R_buf, SEXP _dupl_buf);
/* H5_DLL herr_t H5Dwrite(hid_t dset_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t plist_id, const void *buf); */
SEXP R_H5Dwrite(SEXP R_dset_id, SEXP R_mem_type_id, SEXP R_mem_space_id, SEXP R_file_space_id, SEXP R_plist_id, SEXP R_buf);
/* H5_DLL herr_t H5Dwrite_chunk(hid_t dset_id, hid_t dxpl_id, uint32_t filters, const hsize_t *offset, size_t data_size, const void *buf); */
SEXP R_H5Dwrite_chunk(SEXP R_dset_id, SEXP R_dxpl_id, SEXP R_filters, SEXP R_offset, SEXP R_data_size, SEXP R_buf);
#endif

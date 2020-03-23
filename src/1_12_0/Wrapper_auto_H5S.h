#ifndef _WRAPPER_AUTO_H5S_H_
#define _WRAPPER_AUTO_H5S_H_
#include "global.h"
/* H5_DLL herr_t H5Sclose(hid_t space_id); */
SEXP R_H5Sclose(SEXP R_space_id);
/* H5_DLL hid_t H5Scopy(hid_t space_id); */
SEXP R_H5Scopy(SEXP R_space_id);
/* H5_DLL hid_t H5Screate(H5S_class_t type); */
SEXP R_H5Screate(SEXP R_type);
/* H5_DLL hid_t H5Screate_simple(int rank, const hsize_t dims[], const hsize_t maxdims[]); */
SEXP R_H5Screate_simple(SEXP R_rank, SEXP R_dims, SEXP R_maxdims);
/* H5_DLL hid_t H5Sdecode(const void *buf); */
SEXP R_H5Sdecode(SEXP R_buf);
/* H5_DLL herr_t H5Sencode1(hid_t obj_id, void *buf, size_t *nalloc); */
SEXP R_H5Sencode(SEXP R_obj_id, SEXP R_buf, SEXP R_nalloc, SEXP _dupl_buf);
/* H5_DLL herr_t H5Sextent_copy(hid_t dst_id,hid_t src_id); */
SEXP R_H5Sextent_copy(SEXP R_dst_id, SEXP R_src_id);
/* H5_DLL htri_t H5Sextent_equal(hid_t sid1, hid_t sid2); */
SEXP R_H5Sextent_equal(SEXP R_sid1, SEXP R_sid2);
/* H5_DLL htri_t H5Sget_regular_hyperslab(hid_t spaceid, hsize_t start[], hsize_t stride[], hsize_t count[], hsize_t block[]); */
SEXP R_H5Sget_regular_hyperslab(SEXP R_spaceid, SEXP R_start, SEXP R_stride, SEXP R_count, SEXP R_block);
/* H5_DLL herr_t H5Sget_select_bounds(hid_t spaceid, hsize_t start[], hsize_t end[]); */
SEXP R_H5Sget_select_bounds(SEXP R_spaceid, SEXP R_start, SEXP R_end);
/* H5_DLL hssize_t H5Sget_select_elem_npoints(hid_t spaceid); */
SEXP R_H5Sget_select_elem_npoints(SEXP R_spaceid);
/* H5_DLL herr_t H5Sget_select_elem_pointlist(hid_t spaceid, hsize_t startpoint, hsize_t numpoints, hsize_t buf[]); */
SEXP R_H5Sget_select_elem_pointlist(SEXP R_spaceid, SEXP R_startpoint, SEXP R_numpoints, SEXP R_buf);
/* H5_DLL herr_t H5Sget_select_hyper_blocklist(hid_t spaceid, hsize_t startblock, hsize_t numblocks, hsize_t buf[]); */
SEXP R_H5Sget_select_hyper_blocklist(SEXP R_spaceid, SEXP R_startblock, SEXP R_numblocks, SEXP R_buf);
/* H5_DLL hssize_t H5Sget_select_hyper_nblocks(hid_t spaceid); */
SEXP R_H5Sget_select_hyper_nblocks(SEXP R_spaceid);
/* H5_DLL hssize_t H5Sget_select_npoints(hid_t spaceid); */
SEXP R_H5Sget_select_npoints(SEXP R_spaceid);
/* H5_DLL H5S_sel_type H5Sget_select_type(hid_t spaceid); */
SEXP R_H5Sget_select_type(SEXP R_spaceid);
/* H5_DLL int H5Sget_simple_extent_dims(hid_t space_id, hsize_t dims[], hsize_t maxdims[]); */
SEXP R_H5Sget_simple_extent_dims(SEXP R_space_id, SEXP R_dims, SEXP R_maxdims);
/* H5_DLL int H5Sget_simple_extent_ndims(hid_t space_id); */
SEXP R_H5Sget_simple_extent_ndims(SEXP R_space_id);
/* H5_DLL hssize_t H5Sget_simple_extent_npoints(hid_t space_id); */
SEXP R_H5Sget_simple_extent_npoints(SEXP R_space_id);
/* H5_DLL H5S_class_t H5Sget_simple_extent_type(hid_t space_id); */
SEXP R_H5Sget_simple_extent_type(SEXP R_space_id);
/* H5_DLL htri_t H5Sis_regular_hyperslab(hid_t spaceid); */
SEXP R_H5Sis_regular_hyperslab(SEXP R_spaceid);
/* H5_DLL htri_t H5Sis_simple(hid_t space_id); */
SEXP R_H5Sis_simple(SEXP R_space_id);
/* H5_DLL herr_t H5Smodify_select(hid_t space1_id, H5S_seloper_t op, hid_t space2_id); */
SEXP R_H5Smodify_select(SEXP R_space1_id, SEXP R_op, SEXP R_space2_id);
/* H5_DLL herr_t H5Soffset_simple(hid_t space_id, const hssize_t *offset); */
SEXP R_H5Soffset_simple(SEXP R_space_id, SEXP R_offset);
/* H5_DLL herr_t H5Ssel_iter_close(hid_t sel_iter_id); */
SEXP R_H5Ssel_iter_close(SEXP R_sel_iter_id);
/* H5_DLL hid_t H5Ssel_iter_create(hid_t spaceid, size_t elmt_size, unsigned flags); */
SEXP R_H5Ssel_iter_create(SEXP R_spaceid, SEXP R_elmt_size, SEXP R_flags);
/* H5_DLL herr_t H5Ssel_iter_get_seq_list(hid_t sel_iter_id, size_t maxseq, size_t maxbytes, size_t *nseq, size_t *nbytes, hsize_t *off, size_t *len); */
SEXP R_H5Ssel_iter_get_seq_list(SEXP R_sel_iter_id, SEXP R_maxseq, SEXP R_maxbytes, SEXP R_nseq, SEXP R_nbytes, SEXP R_off, SEXP R_len);
/* H5_DLL herr_t H5Sselect_adjust(hid_t spaceid, const hssize_t *offset); */
SEXP R_H5Sselect_adjust(SEXP R_spaceid, SEXP R_offset);
/* H5_DLL herr_t H5Sselect_all(hid_t spaceid); */
SEXP R_H5Sselect_all(SEXP R_spaceid);
/* H5_DLL herr_t H5Sselect_copy(hid_t dst_id, hid_t src_id); */
SEXP R_H5Sselect_copy(SEXP R_dst_id, SEXP R_src_id);
/* H5_DLL herr_t H5Sselect_elements(hid_t space_id, H5S_seloper_t op, size_t num_elem, const hsize_t *coord); */
SEXP R_H5Sselect_elements(SEXP R_space_id, SEXP R_op, SEXP R_num_elem, SEXP R_coord);
/* H5_DLL herr_t H5Sselect_hyperslab(hid_t space_id, H5S_seloper_t op, const hsize_t start[], const hsize_t _stride[], const hsize_t count[], const hsize_t _block[]); */
SEXP R_H5Sselect_hyperslab(SEXP R_space_id, SEXP R_op, SEXP R_start, SEXP R__stride, SEXP R_count, SEXP R__block);
/* H5_DLL htri_t H5Sselect_intersect_block(hid_t space_id, const hsize_t *start, const hsize_t *end); */
SEXP R_H5Sselect_intersect_block(SEXP R_space_id, SEXP R_start, SEXP R_end);
/* H5_DLL herr_t H5Sselect_none(hid_t spaceid); */
SEXP R_H5Sselect_none(SEXP R_spaceid);
/* H5_DLL hid_t H5Sselect_project_intersection(hid_t src_space_id, hid_t dst_space_id, hid_t src_intersect_space_id); */
SEXP R_H5Sselect_project_intersection(SEXP R_src_space_id, SEXP R_dst_space_id, SEXP R_src_intersect_space_id);
/* H5_DLL htri_t H5Sselect_shape_same(hid_t space1_id, hid_t space2_id); */
SEXP R_H5Sselect_shape_same(SEXP R_space1_id, SEXP R_space2_id);
/* H5_DLL htri_t H5Sselect_valid(hid_t spaceid); */
SEXP R_H5Sselect_valid(SEXP R_spaceid);
/* H5_DLL herr_t H5Sset_extent_none(hid_t space_id); */
SEXP R_H5Sset_extent_none(SEXP R_space_id);
/* H5_DLL herr_t H5Sset_extent_simple(hid_t space_id, int rank, const hsize_t dims[], const hsize_t max[]); */
SEXP R_H5Sset_extent_simple(SEXP R_space_id, SEXP R_rank, SEXP R_dims, SEXP R_max);
#endif

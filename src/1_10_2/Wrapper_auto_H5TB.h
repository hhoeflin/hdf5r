#ifndef _WRAPPER_AUTO_H5TB_H_
#define _WRAPPER_AUTO_H5TB_H_
#include "global.h"
/* H5_HLDLL herr_t H5TBadd_records_from( hid_t loc_id, const char *dset_name1, hsize_t start1, hsize_t nrecords, const char *dset_name2, hsize_t start2 ); */
SEXP R_H5TBadd_records_from(SEXP R_loc_id, SEXP R_dset_name1, SEXP R_start1, SEXP R_nrecords, SEXP R_dset_name2, SEXP R_start2);
/* H5_HLDLL htri_t H5TBAget_fill(hid_t loc_id, const char *dset_name, hid_t dset_id, unsigned char *dst_buf); */
SEXP R_H5TBAget_fill(SEXP R_loc_id, SEXP R_dset_name, SEXP R_dset_id, SEXP R_dst_buf);
/* H5_HLDLL herr_t H5TBAget_title( hid_t loc_id, char *table_title ); */
SEXP R_H5TBAget_title(SEXP R_loc_id, SEXP R_table_title);
/* H5_HLDLL herr_t H5TBappend_records( hid_t loc_id, const char *dset_name, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, const void *buf ); */
SEXP R_H5TBappend_records(SEXP R_loc_id, SEXP R_dset_name, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf);
/* H5_HLDLL herr_t H5TBcombine_tables( hid_t loc_id1, const char *dset_name1, hid_t loc_id2, const char *dset_name2, const char *dset_name3 ); */
SEXP R_H5TBcombine_tables(SEXP R_loc_id1, SEXP R_dset_name1, SEXP R_loc_id2, SEXP R_dset_name2, SEXP R_dset_name3);
/* H5_HLDLL herr_t H5TBdelete_field( hid_t loc_id, const char *dset_name, const char *field_name ); */
SEXP R_H5TBdelete_field(SEXP R_loc_id, SEXP R_dset_name, SEXP R_field_name);
/* H5_HLDLL herr_t H5TBdelete_record( hid_t loc_id, const char *dset_name, hsize_t start, hsize_t nrecords ); */
SEXP R_H5TBdelete_record(SEXP R_loc_id, SEXP R_dset_name, SEXP R_start, SEXP R_nrecords);
/* H5_HLDLL herr_t H5TBget_field_info( hid_t loc_id, const char *dset_name, char *field_names[], size_t *field_sizes, size_t *field_offsets, size_t *type_size ); */
SEXP R_H5TBget_field_info(SEXP R_loc_id, SEXP R_dset_name, SEXP R_field_names, SEXP R_field_sizes, SEXP R_field_offsets, SEXP R_type_size);
/* H5_HLDLL herr_t H5TBget_table_info ( hid_t loc_id, const char *dset_name, hsize_t *nfields, hsize_t *nrecords ); */
SEXP R_H5TBget_table_info(SEXP R_loc_id, SEXP R_dset_name, SEXP R_nfields, SEXP R_nrecords);
/* H5_HLDLL herr_t H5TBinsert_field( hid_t loc_id, const char *dset_name, const char *field_name, hid_t field_type, hsize_t position, const void *fill_data, const void *buf ); */
SEXP R_H5TBinsert_field(SEXP R_loc_id, SEXP R_dset_name, SEXP R_field_name, SEXP R_field_type, SEXP R_position, SEXP R_fill_data, SEXP R_buf);
/* H5_HLDLL herr_t H5TBinsert_record( hid_t loc_id, const char *dset_name, hsize_t start, hsize_t nrecords, size_t dst_size, const size_t *dst_offset, const size_t *dst_sizes, void *buf ); */
SEXP R_H5TBinsert_record(SEXP R_loc_id, SEXP R_dset_name, SEXP R_start, SEXP R_nrecords, SEXP R_dst_size, SEXP R_dst_offset, SEXP R_dst_sizes, SEXP R_buf, SEXP _dupl_buf);
/* H5_HLDLL herr_t H5TBmake_table( const char *table_title, hid_t loc_id, const char *dset_name, hsize_t nfields, hsize_t nrecords, size_t type_size, const char *field_names[], const size_t *field_offset, const hid_t *field_types, hsize_t chunk_size, void *fill_data, int compress, const void *buf ); */
SEXP R_H5TBmake_table(SEXP R_table_title, SEXP R_loc_id, SEXP R_dset_name, SEXP R_nfields, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_names, SEXP R_field_offset, SEXP R_field_types, SEXP R_chunk_size, SEXP R_fill_data, SEXP R_compress, SEXP R_buf, SEXP _dupl_fill_data);
/* H5_HLDLL herr_t H5TBread_fields_index( hid_t loc_id, const char *dset_name, hsize_t nfields, const int *field_index, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, void *buf ); */
SEXP R_H5TBread_fields_index(SEXP R_loc_id, SEXP R_dset_name, SEXP R_nfields, SEXP R_field_index, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf, SEXP _dupl_buf);
/* H5_HLDLL herr_t H5TBread_fields_name( hid_t loc_id, const char *dset_name, const char *field_names, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, void *buf ); */
SEXP R_H5TBread_fields_name(SEXP R_loc_id, SEXP R_dset_name, SEXP R_field_names, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf, SEXP _dupl_buf);
/* H5_HLDLL herr_t H5TBread_records( hid_t loc_id, const char *dset_name, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *dst_offset, const size_t *dst_sizes, void *buf ); */
SEXP R_H5TBread_records(SEXP R_loc_id, SEXP R_dset_name, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_dst_offset, SEXP R_dst_sizes, SEXP R_buf, SEXP _dupl_buf);
/* H5_HLDLL herr_t H5TBread_table( hid_t loc_id, const char *dset_name, size_t dst_size, const size_t *dst_offset, const size_t *dst_sizes, void *dst_buf ); */
SEXP R_H5TBread_table(SEXP R_loc_id, SEXP R_dset_name, SEXP R_dst_size, SEXP R_dst_offset, SEXP R_dst_sizes, SEXP R_dst_buf, SEXP _dupl_dst_buf);
/* H5_HLDLL herr_t H5TBwrite_fields_index( hid_t loc_id, const char *dset_name, hsize_t nfields, const int *field_index, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, const void *buf ); */
SEXP R_H5TBwrite_fields_index(SEXP R_loc_id, SEXP R_dset_name, SEXP R_nfields, SEXP R_field_index, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf);
/* H5_HLDLL herr_t H5TBwrite_fields_name( hid_t loc_id, const char *dset_name, const char *field_names, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, const void *buf ); */
SEXP R_H5TBwrite_fields_name(SEXP R_loc_id, SEXP R_dset_name, SEXP R_field_names, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf);
/* H5_HLDLL herr_t H5TBwrite_records( hid_t loc_id, const char *dset_name, hsize_t start, hsize_t nrecords, size_t type_size, const size_t *field_offset, const size_t *dst_sizes, const void *buf ); */
SEXP R_H5TBwrite_records(SEXP R_loc_id, SEXP R_dset_name, SEXP R_start, SEXP R_nrecords, SEXP R_type_size, SEXP R_field_offset, SEXP R_dst_sizes, SEXP R_buf);
#endif

#ifndef _WRAPPER_AUTO_H5IM_H_
#define _WRAPPER_AUTO_H5IM_H_
#include "global.h"
/* H5_HLDLL herr_t H5IMget_image_info( hid_t loc_id, const char *dset_name, hsize_t *width, hsize_t *height, hsize_t *planes, char *interlace, hssize_t *npals ); */
SEXP R_H5IMget_image_info(SEXP R_loc_id, SEXP R_dset_name, SEXP R_width, SEXP R_height, SEXP R_planes, SEXP R_interlace, SEXP R_npals);
/* H5_HLDLL herr_t H5IMget_npalettes( hid_t loc_id, const char *image_name, hssize_t *npals ); */
SEXP R_H5IMget_npalettes(SEXP R_loc_id, SEXP R_image_name, SEXP R_npals);
/* H5_HLDLL herr_t H5IMget_palette( hid_t loc_id, const char *image_name, int pal_number, unsigned char *pal_data ); */
SEXP R_H5IMget_palette(SEXP R_loc_id, SEXP R_image_name, SEXP R_pal_number, SEXP R_pal_data);
/* H5_HLDLL herr_t H5IMget_palette_info( hid_t loc_id, const char *image_name, int pal_number, hsize_t *pal_dims ); */
SEXP R_H5IMget_palette_info(SEXP R_loc_id, SEXP R_image_name, SEXP R_pal_number, SEXP R_pal_dims);
/* H5_HLDLL herr_t H5IMis_image( hid_t loc_id, const char *dset_name ); */
SEXP R_H5IMis_image(SEXP R_loc_id, SEXP R_dset_name);
/* H5_HLDLL herr_t H5IMis_palette( hid_t loc_id, const char *dset_name ); */
SEXP R_H5IMis_palette(SEXP R_loc_id, SEXP R_dset_name);
/* H5_HLDLL herr_t H5IMlink_palette( hid_t loc_id, const char *image_name, const char *pal_name ); */
SEXP R_H5IMlink_palette(SEXP R_loc_id, SEXP R_image_name, SEXP R_pal_name);
/* H5_HLDLL herr_t H5IMmake_image_24bit( hid_t loc_id, const char *dset_name, hsize_t width, hsize_t height, const char *interlace, const unsigned char *buffer ); */
SEXP R_H5IMmake_image_24bit(SEXP R_loc_id, SEXP R_dset_name, SEXP R_width, SEXP R_height, SEXP R_interlace, SEXP R_buffer);
/* H5_HLDLL herr_t H5IMmake_image_8bit( hid_t loc_id, const char *dset_name, hsize_t width, hsize_t height, const unsigned char *buffer ); */
SEXP R_H5IMmake_image_8bit(SEXP R_loc_id, SEXP R_dset_name, SEXP R_width, SEXP R_height, SEXP R_buffer);
/* H5_HLDLL herr_t H5IMmake_palette( hid_t loc_id, const char *pal_name, const hsize_t *pal_dims, const unsigned char *pal_data ); */
SEXP R_H5IMmake_palette(SEXP R_loc_id, SEXP R_pal_name, SEXP R_pal_dims, SEXP R_pal_data);
/* H5_HLDLL herr_t H5IMread_image( hid_t loc_id, const char *dset_name, unsigned char *buffer ); */
SEXP R_H5IMread_image(SEXP R_loc_id, SEXP R_dset_name, SEXP R_buffer);
/* H5_HLDLL herr_t H5IMunlink_palette( hid_t loc_id, const char *image_name, const char *pal_name ); */
SEXP R_H5IMunlink_palette(SEXP R_loc_id, SEXP R_image_name, SEXP R_pal_name);
#endif

#ifndef _WRAPPER_AUTO_H5DS_H_
#define _WRAPPER_AUTO_H5DS_H_
#include "global.h"
/* H5_HLDLL herr_t H5DSattach_scale( hid_t did, hid_t dsid, unsigned int idx); */
SEXP R_H5DSattach_scale(SEXP R_did, SEXP R_dsid, SEXP R_idx);
/* H5_HLDLL herr_t H5DSdetach_scale( hid_t did, hid_t dsid, unsigned int idx); */
SEXP R_H5DSdetach_scale(SEXP R_did, SEXP R_dsid, SEXP R_idx);
/* H5_HLDLL ssize_t H5DSget_label( hid_t did, unsigned int idx, char *label, size_t size); */
SEXP R_H5DSget_label(SEXP R_did, SEXP R_idx, SEXP R_label, SEXP R_size);
/* H5_HLDLL int H5DSget_num_scales( hid_t did, unsigned int dim); */
SEXP R_H5DSget_num_scales(SEXP R_did, SEXP R_dim);
/* H5_HLDLL ssize_t H5DSget_scale_name( hid_t did, char *name, size_t size); */
SEXP R_H5DSget_scale_name(SEXP R_did, SEXP R_name, SEXP R_size);
/* H5_HLDLL htri_t H5DSis_attached( hid_t did, hid_t dsid, unsigned int idx); */
SEXP R_H5DSis_attached(SEXP R_did, SEXP R_dsid, SEXP R_idx);
/* H5_HLDLL htri_t H5DSis_scale( hid_t did); */
SEXP R_H5DSis_scale(SEXP R_did);
/* H5_HLDLL herr_t H5DSset_label( hid_t did, unsigned int idx, const char *label); */
SEXP R_H5DSset_label(SEXP R_did, SEXP R_idx, SEXP R_label);
/* H5_HLDLL herr_t H5DSset_scale( hid_t dsid, const char *dimname); */
SEXP R_H5DSset_scale(SEXP R_dsid, SEXP R_dimname);
#endif

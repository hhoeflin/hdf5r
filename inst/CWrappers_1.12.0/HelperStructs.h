
#ifndef _HELPER_STRUCTS_H
#define _HELPER_STRUCTS_H

typedef struct H5F_info1_helper_t {
  hsize_t hdr_size;
  H5_ih_info_t msgs_info;
} H5F_info1_helper_t;

typedef struct H5O_hdr_info_helper_space_t {
  hsize_t total;
  hsize_t meta;
  hsize_t mesg;
  hsize_t free;
} H5O_hdr_info_helper_space_t;

typedef struct H5O_hdr_info_helper_msg_t {
  uint64_t present;
  uint64_t shared;
} H5O_hdr_info_helper_msg_t;

typedef struct H5O_info_helper_t {
  H5_ih_info_t   obj;
  H5_ih_info_t   attr;
} H5O_info_helper_t;

typedef union H5L_info1_helper_t {
  haddr_t address;
  size_t val_size;
} H5L_info1_helper_t;

typedef union H5L_info2_helper_t {
  H5O_token_t token;
  size_t val_size;
} H5L_info2_helper_t;

typedef struct H5F_info2_super_t {
	unsigned	version;
	hsize_t		super_size;
	hsize_t		super_ext_size;
    } H5F_info2_super_t;

typedef struct H5F_info2_free_t {
  unsigned	version;
  hsize_t		meta_size;
  hsize_t		tot_space;
} H5F_info2_free_t;

typedef struct H5F_info2_sohm_t {
  unsigned	version;
  hsize_t		hdr_size;
  H5_ih_info_t	msgs_info;
} H5F_info2_sohm_t;


typedef struct H5R_ref_helper_t {
    uint64_t part0;
    uint64_t part1;
    uint64_t part2;
    uint64_t part3;
    uint64_t part4;
    uint64_t part5;
    uint64_t part6;
    uint64_t part7;
} H5R_ref_helper_t;

// More structs to help with ls functionality

typedef struct H5D_info_t {
  int rank;
  char* dims;
  char* maxdims;
  H5T_class_t type_class;
  H5S_class_t space_class;
} H5D_info_t;

// and now for the info structs a version that stores the information to be gathered
typedef struct H5ls_info_t {
  char* name;
  int link_success;
  H5L_info1_t link;
  int obj_type_success;
  H5I_type_t obj_type;
  int num_attrs;
  int group_success;
  H5G_info_t group;
  int dataset_success;
  H5D_info_t dataset;
  int type_success;
  H5T_class_t committed_type;
} H5ls_info_t;



#endif

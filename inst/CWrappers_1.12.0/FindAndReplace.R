
#############################################################################
##
## Copyright 2016 Novartis Institutes for BioMedical Research Inc.
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
## http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
##
#############################################################################




## we replace nested struct definition by unnested ones
## the nested definitions are written into HelperStructs.h


fileReplace <- function(filename, what, replace, fixed=FALSE) {
    if(!file.exists(filename)) {
        stop(paste("File", filename, "does not exist"))
    }
    L <- readLines(filename)
    L <- paste(L, collapse="\n")

    ## collapse multiple spaces to single space
    replace <- paste(replace, collapse="\n")

    ## check if it can be found
    if(!grepl(what, L, fixed=fixed)) {
        stop(paste("In File:", filename, "\nCould not find:\n", what, "\n\nTo be replaced with:\n", replace))
    }

    L <- gsub(what, replace, L, fixed=fixed)
    cat(c(L, ""), file=filename, collapse="\n")
}

################################
### Replace H5F_info2_t
################################

H5Fpublic_what <- "typedef struct H5F_info2_t \\{.*\\} H5F_info2_t;"

H5Fpublic_replace <- "typedef struct H5F_info2_t {
    H5F_info2_super_t super;
    H5F_info2_free_t free;
    H5F_info2_sohm_t sohm;
} H5F_info2_t;"

H5Fpublic_file <- "src_nocomments/H5Fpublic.h.nocomments"
fileReplace(H5Fpublic_file, H5Fpublic_what, H5Fpublic_replace)


################################
### Replace H5F_info1_t
################################


H5Fpublic_what <- "typedef struct H5F_info1_t \\{.*\\} H5F_info1_t;"
H5Fpublic_replace <- "typedef struct H5F_info1_t {
    hsize_t		super_ext_size;	
    H5F_info1_helper_t sohm;
} H5F_info1_t;"
H5Fpublic_file <- "src_nocomments/H5Fpublic.h.nocomments"
fileReplace(H5Fpublic_file, H5Fpublic_what, H5Fpublic_replace)




################################
### Replace H5O_hdfr_info_t
################################


## do the same for the other 2 structs in H5Opublic.h.nocomments
H5Opublic_file <- "src_nocomments/H5Opublic.h.nocomments"
H5Opublic_hdr_info_what <- "typedef struct H5O_hdr_info_t \\{.*\\} H5O_hdr_info_t;"

H5Opublic_hdr_info_replace <- "typedef struct H5O_hdr_info_t {
    unsigned version;		
    unsigned nmesgs;		
    unsigned nchunks;		
    unsigned flags;             
    H5O_hdr_info_helper_space_t space;
    H5O_hdr_info_helper_msg_t  mesg;
} H5O_hdr_info_t;"
fileReplace(H5Opublic_file, H5Opublic_hdr_info_what, H5Opublic_hdr_info_replace)


################################
### Replace H5O_info_t
################################

H5Opublic_file <- "src_nocomments/H5Opublic.h.nocomments"
H5Opublic_native_info_what <- "typedef struct H5O_native_info_t \\{.*\\} H5O_native_info_t;"

H5Opublic_native_info_replace  <- "typedef struct H5O_native_info_t {
    H5O_hdr_info_t      hdr;            
    H5O_info_helper_t meta_size;
} H5O_native_info_t;"
fileReplace(H5Opublic_file, H5Opublic_native_info_what, H5Opublic_native_info_replace)


H5Opublic_info1_what <- "typedef struct H5O_info1_t \\{.*\\} H5O_info1_t;"

H5Opublic_info1_replace  <- "typedef struct H5O_info1_t {
    unsigned long       fileno;
    haddr_t             addr;
    H5O_type_t          type;
    unsigned            rc;
    time_t              atime;
    time_t              mtime;
    time_t              ctime;
    time_t              btime;
    hsize_t             num_attrs;
    H5O_hdr_info_t      hdr;
    H5O_info_helper_t meta_size;
} H5O_info1_t;"
fileReplace(H5Opublic_file, H5Opublic_info1_what, H5Opublic_info1_replace)

################################
### Replace H5L_info_t
################################

# note that this is very brittle; 
# we do it in this order as otherwise the regexp is too greedy
# and identifies the start of H5L_info2_t struct with the 
# end of H5L_info1_t struct and deletes too much of the file
H5Lpublic_info2_file <- "src_nocomments/H5Lpublic.h.nocomments"
H5Lpublic_info2_what <- "typedef struct {
    H5L_type_t          type;           
    hbool_t             corder_valid;   
    int64_t             corder;         
    H5T_cset_t          cset;           
    union {
        H5O_token_t     token;          
        size_t          val_size;       
    } u;
} H5L_info2_t;"
H5Lpublic_info2_replace <- "typedef struct H5L_info2_t {
    H5L_type_t          type;           
    hbool_t             corder_valid;   
    int64_t             corder;         
    H5T_cset_t          cset;           
    H5L_info2_helper_t u;
} H5L_info2_t;"
fileReplace(H5Lpublic_info2_file, H5Lpublic_info2_what, H5Lpublic_info2_replace, fixed=TRUE)

H5Lpublic_info1_file <- "src_nocomments/H5Lpublic.h.nocomments"
H5Lpublic_info1_what <- "typedef struct {
    H5L_type_t          type;           
    hbool_t             corder_valid;   
    int64_t             corder;         
    H5T_cset_t          cset;           
    union {
        haddr_t         address;        
        size_t          val_size;       
    } u;
} H5L_info1_t;"
H5Lpublic_info1_replace <- "typedef struct H5L_info1_t {
    H5L_type_t          type;           
    hbool_t             corder_valid;   
    int64_t             corder;         
    H5T_cset_t          cset;           
    H5L_info1_helper_t u;
} H5L_info1_t;"
fileReplace(H5Lpublic_info1_file, H5Lpublic_info1_what, H5Lpublic_info1_replace, fixed=TRUE)



################################
### Replace H5C_cache_incr_mode
################################


H5Cpublic_file <- "src_nocomments/H5Cpublic.h.nocomments"
H5Cpublic_what <- "enum H5C_cache_incr_mode
{
    H5C_incr__off,
    H5C_incr__threshold
};

enum H5C_cache_flash_incr_mode
{
     H5C_flash_incr__off,
     H5C_flash_incr__add_space
};

enum H5C_cache_decr_mode
{
    H5C_decr__off,
    H5C_decr__threshold,
    H5C_decr__age_out,
    H5C_decr__age_out_with_threshold
};"
H5Cpublic_replace <- "typedef enum H5C_cache_incr_mode
{
    H5C_incr__off,
    H5C_incr__threshold
} H5C_cache_incr_mode;

typedef enum H5C_cache_flash_incr_mode
{
     H5C_flash_incr__off,
     H5C_flash_incr__add_space
} H5C_cache_flash_incr_mode;

typedef enum H5C_cache_decr_mode
{
    H5C_decr__off,
    H5C_decr__threshold,
    H5C_decr__age_out,
    H5C_decr__age_out_with_threshold
} H5C_cache_decr_mode;"
fileReplace(H5Cpublic_file, H5Cpublic_what, H5Cpublic_replace, fixed=TRUE)



################################
### Replace H5Rpublic
################################


H5Rpublic_file <- "src_nocomments/H5Rpublic.h.nocomments"
H5Rpublic_what <- "typedef struct {
    union {
        uint8_t __data[H5R_REF_BUF_SIZE];       
        int64_t align;                          
    } u;
} H5R_ref_t;"
H5Rpublic_replace <- "typedef struct H5R_ref_t {
    H5R_ref_helper_t u;
} H5R_ref_t;"

fileReplace(H5Rpublic_file, H5Rpublic_what, H5Rpublic_replace, fixed=TRUE)



################################
### Replace H5FD_free_t
################################

## delete something in H5FD
H5FDpublic_file <- "src_nocomments/H5FDpublic.h.nocomments"
H5FDpublic_what <- "typedef struct H5FD_free_t \\{.*\\} H5FD_free_t;"
H5FDpublic_replace <- ""
fileReplace(H5FDpublic_file, H5FDpublic_what, H5FDpublic_replace)

################################
### Replace H5FD_file_image_callbacks_t
################################
H5FDpublic_what <- "typedef struct \\{.*\\} H5FD_file_image_callbacks_t;"
fileReplace(H5FDpublic_file, H5FDpublic_what, "")




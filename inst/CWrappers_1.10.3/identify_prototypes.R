

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



rm(list=ls())
library(plyr)
source("helperFunctions.R")
source("remove_c_comments.R")

hdf5.headers <- c("headers")

dir.create("output", showWarnings=FALSE)
dir.create("store", showWarnings=FALSE)


## This file should be run from the inst/CWrappers directory (that exists after the unpacking on linux)
h_files_to_scan <- list.files(hdf5.headers, pattern=glob2rx("*public.h"), full.names = TRUE)
fd_file_list <- c("H5FDcore.h", "H5FDfamily.h", "H5FDlog.h", "H5FDsec2.h", "H5FDstdio.h")
h_files_to_scan <- c(h_files_to_scan, file.path(hdf5.headers, fd_file_list))

## we also include our HelperStructs.h file
h_files_to_scan <- c(h_files_to_scan, "HelperStructs.h")

## create the command line calls to remove the comments
dir.create("src_nocomments", recursive = TRUE, showWarnings = FALSE)
h_files_output <- file.path("src_nocomments", paste0(basename(h_files_to_scan), ".nocomments"))

for(i in seq_along(h_files_to_scan)) {
    remove_c_comments_from_file(infile=h_files_to_scan[i], outfile=h_files_output[i])
}

## We don't want to scan all of them, only the public ones
h_files_basenames <- paste0("H5", c("DS", "IM", "LT", "PT", "TB" ,"", "A", "D", "E", "F", "G", "I", "L", "O", "P", "PL", "R", "S", "T", "Z"),
                           "public.h.nocomments")
h_files_basenames <- c(h_files_basenames, paste0(fd_file_list, ".nocomments"))
h_files_basenames <- c(h_files_basenames, "HelperStructs.h.nocomments")
h_files_for_proto <- file.path("src_nocomments", h_files_basenames)
h_files_for_proto  <- h_files_for_proto[file.exists(h_files_for_proto)]


## there are some nested struct definitions; these are only few, so we change them 'by hand'
## so that automatic processing works
source("FindAndReplace.R")

## describe various pattern pieces
pattern_var_type <- "((const\\s+)?(signed\\s+|unsigned\\s+|enum\\s+|struct\\s+)?(long\\s+)*[\\w_]*(\\s*\\*+\\s*|\\s+)(const\\s+\\*)?)"
pattern_name <- "([\\w_]+)"
pattern_const_with_numbers <- "([\\w_\\[\\]\\(\\)+\\s-]*)"
pattern_square_brackets <- "(\\[[\\w_+\\s-]*\\])"
pattern_typedef_se <- "typedef\\s+(struct|enum|union)"
pattern_prototype <- "^H5_H?L?DLL\\s*(unsigned|signed)?\\s+(\\w+)(\\s*\\*+\\s*|\\s+)(\\w+)\\s*\\(([^)]*)\\)\\s*;"
pattern_anything_in_curly <- "\\{([^\\}]*)\\}"


post_process_type <- function(type) {
    ## post-process the type information a little
    ## strip the space around the * and at the end
    type <- gsub(pattern_square_brackets, "*", type, perl=TRUE)
    type <- gsub("(\\w)\\s*(\\**)\\s*$", "\\1\\2", type, perl=TRUE)
    return(type)
}
## function that splits the arguments of a list into a vector (names are the names of the argument;
## content is the type of the variable
split_args <- function(dF, split_char=",") {
    args <- dF$arguments
    ## capture the case where the argument is just void
    if(grepl("^\\s*void\\s*$", args)) {
        return(NULL)
    }
    
    args_split <- strsplit(args, split=split_char)[[1]]
    ## throw away the ...
    args_split <- args_split[!grepl("^\\s*\\.\\.\\.\\s*$", args_split)]
    ## recognize an argument pattern
    pattern <- paste0("^\\s*", pattern_var_type, pattern_name, pattern_square_brackets, "?\\s*$")
    ## check that we don't have an argument that does not fit the pattern
    if(any(!grepl(pattern, args_split, perl=TRUE))) {
        offending_lines <- args_split[!grepl(pattern, args_split, perl=TRUE)]
        stop(paste("Arguments do not fit the argument pattern:", paste(offending_lines, collapse=split_char)))
    }
    args_type <- gsub(pattern, "\\1\\8", args_split, perl=TRUE)
    ## remove the words struct or type from the type; we don't want those
    args_type <- gsub("struct\\s*|enum\\s*|union\\s*", "", args_type, perl=TRUE)

    
    args_names <- gsub(pattern, "\\7", args_split, perl=TRUE)
    return(data.frame(type=args_type, name=args_names, position=seq_along(args_type), stringsAsFactors = FALSE))
}


split_enum <- function(dF, split_char=",") {
    args <- dF$arguments
    ## capture the case where the argument is just void
    if(grepl("\\s*void\\s*", args)) {
        return(NULL)
    }
    
    args_split <- strsplit(args, split=split_char)[[1]]
    pattern <- paste0("^\\s*", pattern_name, "\\s*=?\\s*", pattern_const_with_numbers, "?\\s*[|&]?\\s*", pattern_const_with_numbers, "?\\s*$")
    ## check that we don't have an argument that does not fit the pattern
    if(any(!grepl(pattern, args_split, perl=TRUE))) {
        offending_lines <- args_split[!grepl(pattern, args_split, perl=TRUE)]
        stop(paste("Arguments do not fit the enum pattern:", paste(offending_lines, collapse=split_char)))
    }
    args_name <- gsub(pattern, "\\1", args_split, perl=TRUE)
    
    args_value <- gsub(pattern, "\\2", args_split, perl=TRUE)
   
    return(data.frame(name=args_name, value=args_value, stringsAsFactors = FALSE))
}


type_properties <- function(dF) {
    dF$type_bare <- make_bare(dF$type)
    dF$const <- is_const(dF$type)
    dF$ref_depth <- get_ref_depth(dF$type)
    return(dF)    
}

#############################################################################
## Get the prototype definitions
#############################################################################


## simple function that intends to decompose (most) prototype definitions
find_prototypes_in_files <- function(filename) {
    pattern <- pattern_prototype
    ## simple rule; if a line doesn't have a semi-colon, merge with next line, unless next line is empty
    lines <- readLines(filename)
    lines_out <- character(length(lines))

    ## need to remove lines that are only for the preprocessor, i.e. start with a #
    lines <- lines[!grepl("^#", lines, perl=TRUE)]
    
    cur_line_out <- 1
    for(i in seq_along(lines)) {
        lines_out[cur_line_out] <- paste(lines_out[cur_line_out], lines[i], sep="")
        if(grepl(";", x=lines[i], fixed=TRUE) || lines[i]=="") {
            cur_line_out <- cur_line_out + 1
        }
    }

    cat(lines_out, file=paste0(filename, ".combined"), sep="\n")
    lines_prototype <- lines_out[grepl(pattern, lines_out, perl=TRUE)]
    ## throw away multiple spaces
    lines_prototype <- gsub("\\s+", " ", lines_prototype, perl=TRUE)
    cat(lines_prototype, file=paste0(filename, ".proto"), sep="\n")

    if(length(lines_prototype) > 0) {
        ## and now for every prototype, extract the name, return type and argument list
        info_df <- data.frame(filename=filename,
                              original=lines_prototype, 
                              func_name=gsub(pattern, "\\4", lines_prototype, perl=TRUE),
                              io="output",
                              type=gsub(pattern, "\\1 \\2 \\3", lines_prototype, perl=TRUE),
                              name=NA, position=-1,
                              arguments=gsub(pattern, "\\5", lines_prototype, perl=TRUE),
                              stringsAsFactors = FALSE)
        ## remove leading 0 of type
        info_df$type <- gsub("^\\s*|\\s*$", "", info_df$type)
        
        args_split <- ddply(info_df, c("filename", "original", "func_name"), split_args, split_char=',')
        if(nrow(args_split) > 0) {args_split$io <- "input"}
        info_df$arguments <- NULL
        info_df <- rbind.fill(info_df, args_split)

        ## post-process the type information a little
        ## strip the space around the * and at the end
        info_df$type <- gsub("(\\w)\\s*(\\**)\\s*$", "\\1\\2", info_df$type, perl=TRUE)

        info_df$type <- post_process_type(info_df$type)
        info_df <- type_properties(info_df)
        
        return(info_df)
    }
    else {
        return(NULL)
    }
}

all_functions <- ldply(as.list(h_files_for_proto), find_prototypes_in_files)
## deprecated functions; remove them from the list
funcs_deprecated <- c("H5Glink", "H5Glink2", "H5Gmove", "H5Gmove2", "H5Gopen1", "H5Giterate", "H5Gget_objtype_by_idx", "H5Gcreate1", "H5Gget_comment",
                      "H5Gget_linkval", "H5Gget_num_objs", "H5Gget_objinfo", "H5Gget_objname_by_idx", "H5Gunlink") 
all_functions <- subset(all_functions, !func_name %in% funcs_deprecated)

#############################################################################
## Now deal with the structs
#############################################################################

## simple function that intends to find most structs
find_structs_in_file <- function(filename) {
    pattern <- paste0("^", pattern_typedef_se, "\\s*", pattern_name, "?\\s*", pattern_anything_in_curly, "\\s*", pattern_name, "\\s*;\\s*$")
    lines <- readLines(filename)
    lines_out <- character(length(lines))

    cur_line_out <- 1
    in_struct_enum <- FALSE
    for(i in seq_along(lines)) {
        lines_out[cur_line_out] <- paste(lines_out[cur_line_out], lines[i], sep="")
        if(grepl(pattern_typedef_se, lines[i], perl=TRUE)) { # enter the curly braces or the
            in_struct_enum <- TRUE
        }
        if(in_struct_enum && grepl("\\}", lines[i], perl=TRUE)) { # exit the curly braces
            in_struct_enum <- FALSE
        }
        if(!in_struct_enum) {
            cur_line_out <- cur_line_out + 1
        }
    }

    lines_struct <- lines_out[grepl(pattern, lines_out, perl=TRUE)]
    lines_struct <- gsub("\\s+", " ", lines_struct, perl=TRUE)
    
    ## remove trailing semicolon in arguments list
    lines_struct <- gsub(";\\s*\\}", "\\}", lines_struct, perl=TRUE)

    ## write out the cleaned file
    cat(lines_struct, file=paste0(filename, ".struct"), sep="\n")
    
    if(length(lines_struct)==0) {
        return(NULL)
    }
    
    ## now get the names of the struct, then parse the arguments
    all_df <- data.frame(filename=filename, original=lines_struct,
                            category=gsub(pattern, "\\1", lines_struct, perl=TRUE),
                            category_name=gsub(pattern, "\\4", lines_struct, perl=TRUE),
                            arguments=gsub(pattern, "\\3", lines_struct, perl=TRUE), stringsAsFactors = FALSE)

    struct_df <- subset(all_df, category %in% c("struct", "union"))
    enum_df <- subset(all_df, category=="enum")
    struct_split <- ddply(struct_df, c("filename", "original", "category", "category_name"), split_args, split_char=';')
    struct_split$type <- post_process_type(struct_split$type)
    enum_split <- ddply(enum_df, c("filename", "original", "category", "category_name"), split_enum, split_char=',')

    struct_split$arguments <- NULL
    enum_split$arguments <- NULL
    res <- rbind.fill(struct_split, enum_split)
    res <- type_properties(res)
    return(res)
}

all_struct_enum <- ldply(as.list(h_files_output), find_structs_in_file)
all_struct_enum$has_rtype <- TRUE
all_struct_enum$has_rtype[all_struct_enum$category=="enum"] <- TRUE

struct_no_rtype <- c("H5FD_free_t")
struct_not_used <- c("hvl_t", "H5G_stat_t") # hvl_t is not used in a function itself and H5G_stat_t is only used by a deprecated function
all_struct_enum <- subset(all_struct_enum, !category_name %in% c(struct_no_rtype, struct_not_used))



## first the high level struct and enum types
struct_enum_types <- unique(all_struct_enum[, c("category", "category_name", "has_rtype")])

struct_member_types <- unique(subset(all_struct_enum, category %in% c("struct", "union") & !is.na(has_rtype))$type_bare)

## define various other types
## define the different parameters that are as of yet unknown
## parameters that are pointers to functions:
## which are currently still missing?
types_undefined <- setdiff(c(struct_member_types, all_functions$type_bare), all_struct_enum$category_name)
func_types <- types_undefined[grepl("^H5A_operator|^H5D_operator|^H5E_auto|^H5E_walk|^H5[A-Z]_iterate|^H5I_free_t$|^H5L_elink_traverse_t|^H5MM_free|^H5MM_allocate|H5T_conv_t|func_t|H5DS_iterate_t|H5FD_file_image_callbacks_t|H5D_append_cb_t|H5O_mcdt_search_cb_t|H5F_flush_cb_t$", types_undefined, perl=TRUE)]
ulong_types <- c("ssize_t", "hsize_t", "size_t", "haddr_t", "hssize_t", "unsigned long", "off_t", "uint64_t")
long_types <- c("long int", "int64_t", "time_t")
int_types <- c("hid_t", "herr_t", "htri_t", "int", "unsigned", "hbool_t", "unsigned int", "H5E_major_t", "H5E_minor_t", "H5G_link_t",
               "H5Z_filter_t", "H5FD_mem_t", "H5O_msg_crt_idx_t", "unsigned char", "long", "long long", "short", "unsigned short", "uint32_t", "unsigned long long")
char_types <- c("char")
double_types <- c("double", "float")
void_types <- "void"
file_types <- "FILE"
all_other <- rbind.fill(data.frame(category="function_ptr", category_name=func_types, has_rtype=FALSE, stringsAsFactors = FALSE),
                        data.frame(category="integer", category_name=ulong_types, has_rtype=TRUE, stringsAsFactors = FALSE),
                        data.frame(category="integer", category_name=long_types, has_rtype=TRUE, stringsAsFactors = FALSE),
                        data.frame(category="integer", category_name=int_types, has_rtype=TRUE, stringsAsFactors = FALSE),
                        data.frame(category="char", category_name=char_types, has_rtype=TRUE, stringsAsFactors = FALSE),
                        data.frame(category="float", category_name=double_types, has_rtype=TRUE, stringsAsFactors = FALSE),
                        data.frame(category="void", category_name=void_types, has_rtype=TRUE, stringsAsFactors = FALSE),
                        data.frame(category="file", category_name=file_types, has_rtype=FALSE, stringsAsFactors = FALSE))


all_types <- rbind.fill(struct_enum_types, all_other)

types_undefined <- setdiff(c(struct_member_types, all_functions$type_bare), all_types$category_name)
if(length(types_undefined) > 0) {
    stop("Don't know a type that is needed here")
}



## now there are structs that contain elements that don't have an r equivalent; sort those out
struct_with_rtype_details <- merge(subset(all_struct_enum, category %in% c("struct", "union")),
                                    all_types, by.x="type_bare", by.y="category_name", suffixes=c("_category", "_type"),
                                    all.x=TRUE, all.y=FALSE)
struct_all_elements_rtype <- ddply(struct_with_rtype_details, c("category_name", "has_rtype_category"),
                                    function(dF) {data.frame(all_rtype=all(dF$has_rtype_type))})
## also don't use H5T_cdata_t
struct_all_elements_rtype$all_rtype[struct_all_elements_rtype$category_name=="H5T_cdata_t"] <- FALSE

struct_all_elements_rtype <- subset(struct_all_elements_rtype, all_rtype)


all_types_with_complete_rtype <- rbind.fill(subset(struct_enum_types, !category %in% c("struct", "union") ||
                                               category_name %in% struct_all_elements_rtype$category_name), all_other)
all_types_with_complete_rtype <- subset(all_types_with_complete_rtype, has_rtype)

## merge the type information with the function information
all_functions_merged <- merge(all_functions, all_types_with_complete_rtype, by.x="type_bare", by.y="category_name", all.x=TRUE, all.y=FALSE)

## first we need an overview of the functions itself
function_summary <- function(dF) {
    ## get the return type
    dF_output <- subset(dF, io=="output")
    output_type <- dF_output$type
    if(length(output_type) > 1) {
        stop("There should be only one output type line")
    }
    is_getter <- any(grepl("get_", dF$func_name, fixed=TRUE)) # should only be a single function name
    num_args <- sum(dF$io=="input")
    num_args_reference <- sum(dF$io=="input" & grepl("*", dF$type, fixed=TRUE))
    num_args_non_const_FILE_reference <- sum(dF$io=="input" & dF$ref_depth > 0 & !dF$const &
                                             !grepl("FILE", dF$type, fixed=TRUE))
    has_all_rtype <- all(!is.na(dF$has_rtype))
    has_doubleref_void <- any(dF$ref_depth == 2 & dF$type_bare=="void")

    return(data.frame(output_type=output_type, is_getter=is_getter, num_args=num_args, num_args_reference=num_args_reference,
                      num_args_non_const_FILE_reference=num_args_non_const_FILE_reference,
                      has_all_rtype=has_all_rtype, has_doubleref_void=has_doubleref_void, stringsAsFactors = FALSE))    
}


## make a summary of the functions; for "getter" functions, return all objects that have been passed in by reference
all_functions_summary <- ddply(all_functions_merged, c("filename", "original", "func_name"), function_summary)

## create a list of separate "getter" functions, being those
additional_getters <- c("H5Eautos_is_v2", "H5Inmembers", "H5Pfill_value_defined", "H5Tfind")
all_functions_summary$is_getter[all_functions_summary$func_name %in% additional_getters] <- TRUE



## to the data from all_functions, add the info gained from the summary here
all_functions_merged_summary <- merge(all_functions_merged, all_functions_summary, all.x=TRUE)

all_functions_for_wrapping <- subset(all_functions_merged_summary, has_all_rtype & !has_doubleref_void)




## save the data frames we are interested in
## base types (including enums)
## structs
## and functions
all_types <- subset(all_types, category != "void" & has_rtype)
## subset the tpes with the allowed structs
all_types <- subset(all_types, category != "struct" | category_name %in% struct_all_elements_rtype$category_name)
saveRDS(all_types, file=file.path("store", "all_types.rds"))

## structs
saveRDS(subset(all_struct_enum, category_name %in% struct_all_elements_rtype$category_name), file=file.path("store", "struct_info.rds"))

## all the information on enums
saveRDS(subset(all_struct_enum, category=="enum"), file=file.path("store", "enum_info.rds"))

## functions
saveRDS(all_functions_for_wrapping, file=file.path("store", "functions_for_wrappping.rds"))



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





library(plyr)

## code for generating the hdf5 data types for the base types; this is only helper code and needs to be edited
all_types <- readRDS(file=file.path("store", "all_types.rds"))
## only do standard data types; enum and struct will be done later
base_types <- subset(all_types, !category %in% c("enum", "struct", "union"))

base_type_wrapping_func <- function(type_name, i, isEnum) {
    dt_type_name <- paste0("DT_", gsub("\\s+", "_", type_name, perl=TRUE))
    return(paste0("h5_datatype[", dt_type_name, "] = get_h5_equiv(sizeof(", type_name, "), issigned(", type_name, "));"))
}

base_type_enum_names <- paste0("DT_", gsub("\\s+", "_", base_types$category_name, perl=TRUE)) 

base_types$wrapping <- character(nrow(base_types))
for(i in seq_len(nrow(base_types))) {
    base_types$wrapping[i] <- base_type_wrapping_func(base_types$category_name[i], i - 1)
}

## write them out in files
base_types$enum_names <- base_type_enum_names
cat(base_types$enum_names, sep=",\n", file=file.path("output", "DT_enum_base_type.txt"))
cat(base_types$wrapping, sep="\n\t", file=file.path("output", "base_type_assign.txt"))

               


###################################
## create the code for enum datatypes
###################################
enum_info <- readRDS(file=file.path("store", "enum_info.rds"))

code_for_datatype_for_enum_c <- function(enum_info) {
    ## check which structs are not compatible
    enum_comment <- paste0("/* ", unique(enum_info$original), " */")
    code <- c("", enum_comment)
    
    enum_name <- unique(enum_info$category_name)

    ## check if it is an unnamed enum
    unnamed <- grepl("^typedef\\s+enum\\s*\\{", unique(enum_info$original), perl = TRUE)
    
    code <- c(code, paste0("hid_t create_DT_", enum_name, "(void) {"))

    if(unnamed) {
        code <- c(code, paste0("  ", enum_name, " myenum;"))
        code <- c(code, paste0("  hid_t base_type = get_h5_equiv(sizeof(", enum_name, "), issigned(", enum_name, "));"))
    }
    else {
        code <- c(code, paste0("  enum ", enum_name, " myenum;"))
        code <- c(code, paste0("  hid_t base_type = get_h5_equiv(sizeof(enum ", enum_name, "), issigned(enum ", enum_name, "));"))
    }
    code <- c(code, paste0("  hid_t dtype_id = H5Tenum_create(base_type);"))

    for(i in seq_len(nrow(enum_info))) {
        code <- c(code, paste0("  myenum = ", enum_info$name[i], ";"))
        code <- c(code, paste0("  H5Tenum_insert(dtype_id, \"", enum_info$name[i], "\", &myenum);"))
    }

    code <- c(code, "  return(dtype_id);")
    code <- c(code, "}")
    
}

code_for_datatype_for_enum_h <- function(enum_info) {
    ## check which structs are not compatible
    enum_comment <- paste0("/* ", unique(enum_info$original), " */")
    
    enum_name <- unique(enum_info$category_name)
    return(c("", enum_comment, paste0("hid_t create_DT_", enum_name, "(void);")))
}


enum_create_c <- dlply(enum_info, "category_name", code_for_datatype_for_enum_c)
enum_create_h <- dlply(enum_info, "category_name", code_for_datatype_for_enum_h)

enum_names_for_enum <- paste0("DT_", unique(enum_info$category_name))

datatype_generation_enum <- character(length(enum_names_for_enum))
for(i in seq_len(length(enum_names_for_enum))) {
    datatype_generation_enum[i] <- paste0("h5_datatype[", enum_names_for_enum[i], "] = create_", enum_names_for_enum[i], "();")
}


cat(enum_names_for_enum, sep=",\n", file=file.path("output", "DT_enum_enum.txt")) ## not needed; already created in datatype
cat(datatype_generation_enum, sep="\n", file=file.path("output", "enum_assign.txt"))
cat(unlist(enum_create_c), sep="\n", file=file.path("output", "enum_create_code_c.txt"))
cat(unlist(enum_create_h), sep="\n", file=file.path("output", "enum_create_code_h.txt"))


#####################################
## create the data types for structs
#####################################
struct_info <- readRDS(file=file.path("store", "struct_info.rds"))
# take out the "val_size" in H5L_info_helper_t
struct_info <- subset(struct_info, category_name != "H5L_info_helper_t" | name != "val_size")

code_for_datatype_for_struct_c <- function(struct_info) {
    ## check which structs are not compatible
    if(any(struct_info$type %in% c("void*"))) {
        return(NULL)
    }

    struct_comment <- paste0("/* ", unique(struct_info$original), " */")
    code <- c("", struct_comment)
    
    struct_name <- unique(struct_info$category_name)
    code <- c(code, paste0("hid_t create_DT_", struct_name, "(void) {"))

    code <- c(code, paste0("  hid_t dtype_id = H5Tcreate(H5T_COMPOUND, sizeof(", struct_name, "));"))

    for(i in seq_len(nrow(struct_info))) {
        h5_dt_name <- paste0("DT_", gsub("\\s+", "_", struct_info$type_bare[i]))
        code <- c(code, paste0("  H5Tinsert(dtype_id, \"", struct_info$name[i],
                  "\", HOFFSET(", struct_name, ", ", struct_info$name[i], "), h5_datatype[", h5_dt_name, "]);"))
    }

    code <- c(code, "  return(dtype_id);")
    code <- c(code, "}")
    
}

code_for_datatype_for_struct_h <- function(struct_info) {
    ## check which structs are not compatible
    if(any(struct_info$type %in% c("void*"))) {
        return(NULL)
    }
    struct_comment <- paste0("/* ", unique(struct_info$original), " */")
    
    struct_name <- unique(struct_info$category_name)
    return(c("", struct_comment, paste0("hid_t create_DT_", struct_name, "(void);")))
}


struct_create_c <- dlply(struct_info, "category_name", code_for_datatype_for_struct_c)
struct_create_h <- dlply(struct_info, "category_name", code_for_datatype_for_struct_h)


struct_names_for_enum <- paste0("DT_", unique(struct_info$category_name))

struct_names_ordered <- c("DT_H5_ih_info_t", "DT_H5AC_cache_config_t", "DT_H5A_info_t", "DT_H5E_error1_t",
                          "DT_H5E_error2_t", "DT_H5F_info1_helper_t", "DT_H5F_info1_t",
                          "DT_H5F_info2_super_t", "DT_H5F_info2_free_t", "DT_H5F_info2_sohm_t", "DT_H5F_info2_t", 
                          "DT_H5G_info_t",
                          "DT_H5L_info_helper_t", "DT_H5L_info_t", "DT_H5O_hdr_info_helper_msg_t", "DT_H5O_hdr_info_helper_space_t",
                          "DT_H5O_hdr_info_t", "DT_H5O_info_helper_t", "DT_H5O_info_t", "DT_H5O_stat_t")
struct_names_for_enum <- c(struct_names_ordered, setdiff(struct_names_for_enum, struct_names_ordered))
datatype_generation_struct <- character(length(struct_names_for_enum))
for(i in seq_len(length(struct_names_for_enum))) {
    datatype_generation_struct[i] <- paste0("h5_datatype[", struct_names_for_enum[i], "] = create_", struct_names_for_enum[i], "();")
}


cat(struct_names_for_enum, sep=",\n", file=file.path("output", "DT_enum_struct.txt"))
cat(datatype_generation_struct, sep="\n", file=file.path("output", "struct_assign.txt"))
cat(unlist(struct_create_c), sep="\n", file=file.path("output", "struct_create_code_c.txt"))
cat(unlist(struct_create_h), sep="\n", file=file.path("output", "struct_create_code_h.txt"))


##########################################################
## extract the built_in datatypes; they are all defined in H5Tpublic.h
## do this so that we can return a named list of things in R
##########################################################
h5t_public_file <- file.path("headers/H5Tpublic.h")
h5t_public <- readLines(h5t_public_file)
h5t_public <- h5t_public[grepl("#define H5T_", h5t_public, fixed=TRUE)]
h5t_public_types <- gsub("^\\#define\\s+([\\w_]+)\\s+.*$", "\\1", h5t_public, perl=TRUE)
not_types <- c("H5T_NCSET", "H5T_NSTR", "H5T_VARIABLE", "H5T_OPAQUE_TAG_MAX")
add_types <- c("H5T_C_S1", "H5T_FORTRAN_S1")
h5t_public_types <- union(setdiff(h5t_public_types, not_types), add_types)
h5t_public_types <- data.frame(name=h5t_public_types)
h5t_public_types$name_enum <- paste0("DT_", h5t_public_types$name)
h5t_public_types$category_output <- gsub("^H5T_([A-Z]+)_.*$", "\\1", h5t_public_types$name, perl=TRUE)
## need to correct string
h5t_public_types$category_output[h5t_public_types$name %in% c("H5T_C_S1", "H5T_FORTRAN_S1")] <- "STRING"


## create a list of all type names; and a list to which category they belong
all_types$category <- factor(all_types$category, levels=c("integer", "char", "float", "enum", "union", "struct"))
all_types <- all_types[order(all_types$category, all_types$category_name),]
category_mapping <- c(integer="C_API_types", char="C_API_types", float="C_API_types", enum="enum", union="struct", struct="struct")
all_types$category_output <- category_mapping[as.character(all_types$category)]
all_types <- all_types[, c("category_name", "category_output")]
colnames(all_types) <- c("name", "category_output")
all_types$name_enum <- paste0("DT_", gsub("\\s+", "_", all_types$name, perl=TRUE))
library(plyr)
all_types <- rbind.fill(h5t_public_types, all_types)

## write out a file with all DT_ names
cat(all_types$name_enum, sep=",\n", file=file.path("output", "DT_enum_all_types.txt"))

## for the h5t_public_types, create code that sets them
h5t_public_types$set_c <- paste0("h5_datatype[", h5t_public_types$name_enum, "] = ", h5t_public_types$name, ";")
cat(h5t_public_types$set_c, sep="\n", file=file.path("output", "h5t_public_types_assign.txt"))

## create C-code that creates a data frame in R that contains the name, the number, the category and the datatype_id
code_df_all_types <- function(all_types) {
    code <- "SEXP show_all_types_data_frame(void) {"
    ## create the basis of the data frame
    code <- c(code, "  SEXP df = PROTECT(allocVector(VECSXP, 3));")
    code <- c(code, "  SET_VECTOR_ELT(df, 0, NEW_CHARACTER(DT_LAST_ITEM));")
    code <- c(code, "  SET_VECTOR_ELT(df, 1, NEW_CHARACTER(DT_LAST_ITEM));")
    code <- c(code, "  SEXP R_type = PROTECT(NEW_NUMERIC(DT_LAST_ITEM));")
    code <- c(code, "  SET_CLASS(R_type, ScalarString(mkChar(\"integer64\")));")
    code <- c(code, "  SET_VECTOR_ELT(df, 2, R_type);")
    code <- c(code, "  SEXP df_rownames = PROTECT(NEW_INTEGER(DT_LAST_ITEM));")
    code <- c(code, "  for(R_xlen_t i = 0; i < DT_LAST_ITEM; ++i) {")
    code <- c(code, "    INTEGER(df_rownames)[i] = i + 1;")
    code <- c(code, "  }")
    code <- c(code, "  SET_CLASS(df, mkString(\"data.frame\"));")
    code <- c(code, "  SET_ATTR(df, install(\"row.names\"), df_rownames);")
    code <- c(code, "  SEXP df_names = PROTECT(NEW_CHARACTER(3));")
    code <- c(code, "  SET_STRING_ELT(df_names, 0, mkChar(\"Category\"));")
    code <- c(code, "  SET_STRING_ELT(df_names, 1, mkChar(\"Name\"));")
    code <- c(code, "  SET_STRING_ELT(df_names, 2, mkChar(\"Type_id\"));")
    code <- c(code, "  SET_NAMES(df, df_names);")
    ## get pointers to the 4 items for easier use
    code <- c(code, "  SEXP R_categ = VECTOR_ELT(df, 0);")
    code <- c(code, "  SEXP R_name = VECTOR_ELT(df, 1);")
    code <- c(code, "  R_type = VECTOR_ELT(df, 2);")
    ## and now set the actual ids
    for(i in seq_len(nrow(all_types))) {
        code <- c(code, "")
        if(all_types$name_enum[i]=="DT_H5T_NATIVE_LDOUBLE") {
            code <- c(code, "#if H5_SIZEOF_LONG_DOUBLE !=0")
        }
        code <- c(code, paste0("  SET_STRING_ELT(R_categ, ", all_types$name_enum[i], ", mkChar(\"", all_types$category_output[i], "\"));"))
        ## needed to remove the DT_ in front, but keep the _ in between words for the name in the string
        code <- c(code, paste0("  SET_STRING_ELT(R_name, ", all_types$name_enum[i], ", mkChar(\"",
                               gsub("^DT_", "", all_types$name_enum[i], perl=TRUE), "\"));")) 
        code <- c(code, paste0("  ((long long *) REAL(R_type))[", all_types$name_enum[i], "] = h5_datatype[", all_types$name_enum[i], "];"))
        if(all_types$name_enum[i]=="DT_H5T_NATIVE_LDOUBLE") {
            code <- c(code, "#endif")
        }
    }

    code <- c(code, "  UNPROTECT(4);")
    code <- c(code, "  return(df);")
    code <- c(code, "}")
}

cat(code_df_all_types(all_types), sep="\n", file=file.path("output", "all_types_dt_return_df.txt"))





## and now create datatype_export.h
## as well as datatype_export.c
library(brew)
datatype_export_h_env <- new.env()
datatype_export_h_env$dt_all_names_no_LDOUBLE <- paste(paste0("  ", subset(all_types, name!="H5T_NATIVE_LDOUBLE")$name_enum), collapse=",\n")
datatype_export_h_env$enum_create_func_def <- paste(unlist(enum_create_h), collapse="\n")
datatype_export_h_env$struct_create_func_def <- paste(unlist(struct_create_h), collapse="\n")
brew(file="datatype_export_h.brew", output=file.path("output_code", "datatype_export.h"), envir=datatype_export_h_env)

datatype_export_c_env <- new.env()
datatype_export_c_env$builtin_types_init_no_LDOUBLE <- paste(paste0("  ", subset(h5t_public_types, name!="H5T_NATIVE_LDOUBLE")$set_c), collapse="\n")
datatype_export_c_env$c_api_types_init_no_char_float <- paste(paste0("  ", subset(base_types, category=="integer")$wrapping), collapse = "\n")
datatype_export_c_env$enum_init <- paste(paste0("  ", datatype_generation_enum), collapse = "\n")
datatype_export_c_env$struct_init <- paste(paste0("  ", datatype_generation_struct), collapse = "\n")
datatype_export_c_env$show_all_types_code <- paste(code_df_all_types(all_types), collapse="\n")
datatype_export_c_env$create_enum_types_code <- paste(unlist(enum_create_c), collapse="\n")
datatype_export_c_env$create_struct_types_code <- paste(unlist(struct_create_c), collapse="\n")
brew(file="datatype_export_c.brew", output=file.path("output_code", "datatype_export.c"), envir=datatype_export_c_env)
file.copy("HelperStructs.h", "output_code/HelperStructs.h")

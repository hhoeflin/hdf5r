
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
source("helperFunctions.R")
dir.create("output_code", showWarnings=FALSE)

copyright_notice <- readLines("Apache_Copyright_Notice.txt")


## function that copies the robjects as needed
duplicate_object <- function(text, cname, ask=FALSE) {
    rname <- r_name(cname)
    if(ask) {
        boolname <- bool_dupl_name(cname)
        text <- c(text, paste0("  ", "if(SEXP_to_logical(", boolname, ")) {"))
        text <- c(text, paste0("    ", rname, " = PROTECT(duplicate(", rname, "));"))
        text <- c(text, paste0("    vars_protected++;"))
        text <- c(text, "  }")
    }
    else {
        text <- c(text, paste0("  ", rname, " = PROTECT(duplicate(", rname, "));"))
        text <- c(text, paste0("  vars_protected++;"))
    }
    return(text)
}

## function that generates code for unwrapping a variable
unwrap_variable <- function(text, cname, ctype, category, rname=r_name(cname)) {
    ctype_const <- is_const(ctype)
    ctype_ref_depth <- get_ref_depth(ctype)
    ctype_bare <- make_bare(ctype)
    ctype_DT <- paste0("DT_", gsub("\\s+", "_", ctype_bare))

    if(ctype_ref_depth==0) {
        ## could be integer, double, enum (same as integer) or struct
        ## for integer, double or enum, we have a specialized function for the conversion
        if(category %in% c("integer", "enum")) {
            text <- c(text, paste0("  ", ctype, " ", cname, " = SEXP_to_longlong(", rname, ", 0);"))
        }
        else if(category %in% c("float")) {
            text <- c(text, paste0("  ", ctype, " ", cname, " = SEXP_to_double(", rname, ");"))
        }
        else if(category %in% c("struct", "union")) {
            text <- c(text, paste0("  ", "R_helper = PROTECT(RToH5(", rname, "h5_datatype[", ctype_DT, "], 1));"))
            text <- c(text, paste0("  ", ctype, " ", cname, " = * ((", ctype, "*) VOIDPTR(R_helper));"))
            text <- c(text, paste0("  vars_protected++;"))

        }
        else {
            stop("Unknown category")
        }        
    }
    else if(ctype_ref_depth == 1) {
        ## potentially need to convert an input variable (but preferred not)
        if(ctype=="const char*") {
            text <- c(text, paste0("  ", ctype, " ", cname, " = CHAR(STRING_ELT(", rname, ", 0));"))
        }
        else if(ctype=="char*") {
            ## need to copy the string
            text <- c(text, paste0("  ", ctype, " ", cname, ";"))
            text <- c(text, paste0("  if(XLENGTH(", rname, ") == 0) {"))
            text <- c(text, paste0("    ", cname, " = NULL;"))
            text <- c(text, paste0("  }"))
            text <- c(text, paste0("  else {"))
            text <- c(text, paste0("    ", cname, " = R_alloc(strlen(CHAR(STRING_ELT(", rname, ", 0))) + 1, 1);"))
            text <- c(text, paste0("    ", "strcpy(", cname, ", CHAR(STRING_ELT(", rname, ", 0)));"))
            text <- c(text, paste0("  }"))
        }
        else if(ctype_bare=="void") {
            ## simply pass the object
            ## check if the object has size > 0, otherwise set NULL
            text <- c(text, paste0("  ", ctype, " ", cname, ";"))
            text <- c(text, paste0("  if(XLENGTH(", rname, ") == 0) {"))
            text <- c(text, paste0("    ", cname, " = NULL;"))
            text <- c(text, paste0("  }"))
            text <- c(text, paste0("  else {"))
            text <- c(text, paste0("    ", cname, " = (void *) VOIDPTR(", rname, ");"))
            text <- c(text, paste0("  }"))
        }
        else if(category=="struct") {
            ## treat it like the fixed case; translate from R to h5, then give the pointer instead of the address
            text <- c(text, paste0("  ", "R_helper = PROTECT(RToH5(", rname, ", h5_datatype[", ctype_DT,
                                   "], guess_nelem(", rname, ", h5_datatype[", ctype_DT, "])));"))
            text <- c(text, paste0("  ", ctype, " ", cname, "= (", ctype, ") VOIDPTR(R_helper);"))
            text <- c(text, paste0("  vars_protected++;"))

        }
        else if(category %in% c("integer", "float", "enum")) {
            text <- c(text, paste0("  ", ctype, " ", cname, ";"))
            text <- c(text, paste0("  if(XLENGTH(", rname, ") == 0) {"))
            text <- c(text, paste0("    ", cname, " = NULL;"))
            text <- c(text, paste0("  }"))
            text <- c(text, paste0("  else {"))
            text <- c(text, paste0("    ", "R_helper = PROTECT(RToH5(", rname, ", h5_datatype[", ctype_DT, "], XLENGTH(", rname, ")));"))
            text <- c(text, paste0("    ", cname, "= (", ctype, ") VOIDPTR(R_helper);"))
            text <- c(text, paste0("    vars_protected++;"))
            text <- c(text, paste0("  }"))
        }
        else {
            stop("Unknown type")
        }
    }
    else if(ctype_ref_depth == 2) {
        ## we only do this for const character vectors
        if(ctype=="const char**") {
            text <- c(text, paste0("  ", ctype, " ", cname, ";"))
            text <- c(text, paste0("  if(XLENGTH(", rname, ") == 0) {"))
            text <- c(text, paste0("    ", cname, " = NULL;"))
            text <- c(text, paste0("  }"))
            text <- c(text, paste0("  else {"))
            text <- c(text, paste0("    ", "R_helper = PROTECT(RToH5(", rname, ", h5_datatype[", ctype_DT, "], XLENGTH(", rname, ")));"))
            text <- c(text, paste0("    ", cname, "= (", ctype, ") VOIDPTR(R_helper);"))
            text <- c(text, paste0("    vars_protected++;"))
            text <- c(text, paste0("  }"))
        }
        else if(ctype=="char**") { ## we copy everything into R_alloced places
            text <- c(text, paste0("  ", ctype, " ", cname, ";"))
            text <- c(text, paste0("  if(XLENGTH(", rname, ") == 0) {"))
            text <- c(text, paste0("    ", cname, " = NULL;"))
            text <- c(text, paste0("  }"))
            text <- c(text, paste0("  else {"))
            text <- c(text, paste0("    ", "R_helper = PROTECT(RToH5(", rname, ", h5_datatype[", ctype_DT, "], XLENGTH(", rname, ")));"))
            text <- c(text, paste0("    ", cname, "= (", ctype, ") VOIDPTR(R_helper);"))
            text <- c(text, paste0("    vars_protected++;"))
            text <- c(text, paste0("    if(!inherits(", rname, ", \"_RToH5_empty\")) {"))
            text <- c(text, paste0("      for(int i = 0; i < XLENGTH(", rname, "); ++i) {"))
            text <- c(text, paste0("        if(XLENGTH(STRING_ELT(", rname, ", i)) == 0) {"))
            text <- c(text, paste0("          ", cname, "[i] = NULL;"))
            text <- c(text, paste0("        }"))
            text <- c(text, paste0("        else {"))
            text <- c(text, paste0("          ", cname, "[i] = (char*) R_alloc(XLENGTH(STRING_ELT(", rname, ", i)), 1);"))
            text <- c(text, paste0("          strcpy(", cname, "[i], CHAR(STRING_ELT(", rname, ", i)));"))
            text <- c(text, paste0("        }"))
            text <- c(text, paste0("      }"))
            text <- c(text, paste0("    }"))
            text <- c(text, paste0("  }"))
        }
        else {
            stop("Not supported type for double reference")
        }
    }
    
    return(text)
}    


## function for calling the hdf5 API function
create_API_call <- function(text, func_name, return_type, return_name, cnames) {
    ## now do the API call
    if(return_type != "void") {
        text <- c(text, paste0("  ", return_type, " ", return_name, " = ", func_name, "(", paste(cnames, collapse=", "), ");"))
    }
    else {
        text <- c(text, paste0("  ", func_name, "(", paste(cnames, collapse=", "), ");"))
    }
    return(text)
}    
    
## function for wrapping the c objects back into R
## function that generates code for unwrapping a variable
wrap_variable <- function(text, cname, ctype, category, rname=r_name(cname), define_r_var=FALSE) {
    ctype_const <- is_const(ctype)
    ctype_ref_depth <- get_ref_depth(ctype)
    ctype_bare <- make_bare(ctype)
    ctype_DT <- paste0("DT_", gsub("\\s+", "_", ctype_bare))
    
    if(define_r_var) { 
        text <- c(text, paste0("  ", "SEXP ", rname, "= R_NilValue;"))
    }
    
    if(ctype_ref_depth==0) {
        ## could be integer, double, enum (same as integer) or struct
        ## for integer, double or enum, we have a specialized function for the conversion
        if(category %in% c("integer")) {
            text <- c(text, paste0("  ", rname, " = PROTECT(ScalarInteger64_or_int(", cname, "));"))
            text <- c(text, paste0("  vars_protected++;"))
        }
        else if(category %in% "enum") {
            text <- c(text, paste0("  ", rname, " = PROTECT(ScalarFactor(", cname, ", h5_datatype[", ctype_DT, "]));"))
            text <- c(text, paste0("  vars_protected++;"))
        }
        else if(category %in% c("float")) {
            text <- c(text, paste0("  ", rname, " = PROTECT(ScalarReal(", cname, "));"))
            text <- c(text, paste0("  vars_protected++;"))
        }
        else if(category %in% c("struct", "union")) {
            text <- c(text, paste0("  ", rname, " = PROTECT(H5ToR_single_step(", cname, ", h5_datatype[", ctype_DT, "], 1, H5TOR_CONV_INT64_NOLOSS));"))
            text <- c(text, paste0("  vars_protected++;"))
        }
        else if(category == "void") {
            ## nothing to do; already set to R_NilValue
        }
        else {
            stop("Unknown category")
        }        
    }
    else if(ctype_ref_depth == 1) {
        ## potentially need to convert an input variable (but preferred not)
        if(ctype_bare=="char") {
            ## need to copy the string
            text <- c(text, paste0("  if(", cname, "==NULL) {"))
            text <- c(text, paste0("    ", rname, " = PROTECT(NEW_CHARACTER(0));"))
            text <- c(text, paste0("    vars_protected++;"))
            text <- c(text, paste0("  }"))
            text <- c(text, paste0("  else {"))
            text <- c(text, paste0("    ", rname, " = PROTECT(mkString(", cname,"));"))
            text <- c(text, paste0("    vars_protected++;"))
            text <- c(text, paste0("  }"))
        }
        else if(ctype=="void*") {
            ## simply pass the object
            ## do nothing; already worked on the R object itself
        }
        else if(category=="struct") {
            ## treat it like the fixed case; translate from R to h5, then give the pointer instead of the address
            text <- c(text, paste0("  ", "size_helper = guess_nelem(", rname, ", h5_datatype[", ctype_DT, "]);"))
            text <- c(text, paste0("  ", rname, " = PROTECT(H5ToR_single_step(", cname, ", h5_datatype[", ctype_DT, "], size_helper, H5TOR_CONV_INT64_NOLOSS));"))
            text <- c(text, paste0("  vars_protected++;"))
        }
        else if(category %in% c("integer", "float", "enum")) {
            ## treat it like the fixed case; translate from R to h5, then give the pointer instead of the address
            text <- c(text, paste0("  ", "size_helper = guess_nelem(", rname, ", h5_datatype[", ctype_DT, "]);"))
            text <- c(text, paste0("  ", rname, " = PROTECT(H5ToR_single_step(", cname, ", h5_datatype[", ctype_DT, "], size_helper, H5TOR_CONV_INT64_NOLOSS));"))
            text <- c(text, paste0("  vars_protected++;"))
        }
    }
    else if(ctype_ref_depth == 2 && ctype_bare=="char") {
        ## this is returned and as it is a double redirect, it can be used as output
            text <- c(text, paste0("  ", "size_helper = guess_nelem(", rname, ", h5_datatype[", ctype_DT, "]);"))
            text <- c(text, paste0("  ", rname, " = PROTECT(H5ToR_single_step(", cname, ", h5_datatype[", ctype_DT, "], size_helper, H5TOR_CONV_INT64_NOLOSS));"))
            text <- c(text, paste0("  vars_protected++;"))
    }
    else {
        stop("This case should not have happened")
    }
    
    return(text)
}
    

## function for generating the return list
create_return_list <- function(text, cnames) {
    rnames <- r_name(cnames)
    ## create the list
    text <- c(text, paste0("  ", "SEXP __ret_list;"))
    text <- c(text, paste0("  ", "PROTECT(__ret_list = allocVector(VECSXP, ", length(rnames), "));"))
    ## now set each of the vector elements, by name
    for(i in seq_along(rnames)) {
        text <- c(text, paste0("  ", "SET_VECTOR_ELT(__ret_list, ", i - 1, ", ", rnames[i], ");"))
    }
    ## create the names for the list and 
    text <- c(text, paste0("  ", "SEXP __ret_list_names;"))
    text <- c(text, paste0("  ", "PROTECT(__ret_list_names = allocVector(STRSXP, ", length(rnames), "));"))
    ## now set each of the vector elements, by name
    for(i in seq_along(rnames)) {
        text <- c(text, paste0("  ", "SET_STRING_ELT(__ret_list_names, ", i - 1, ", mkChar(\"", cnames[i], "\"));"))
    }
    text <- c(text, paste0("  ", "SET_NAMES(__ret_list, __ret_list_names);"))
    text <- c(text, paste0("  vars_protected += 2;"))
    return(text)
}




    
## wrapping all the above together for creating the function call for the API
## additional injection is a list with 4 components
## start, pre_call, post_call, pre_list, end
## each of these is a named list with funciton names;
## create_wrapper_API searches in there for pieces of code to inject
## at the appropriate places
create_wrapper_API <- function(api_info, add_injection) {
    ## order the input by position
    api_info <- api_info[order(api_info$position, decreasing=FALSE),]
    
    api_info_input <- subset(api_info, io=="input")
    api_info_output <- subset(api_info, io=="output")

    ## all input names that refer to non-const references and add a duplication switch
    api_info_ref_out <- subset(api_info_input, (!is_const(type) & get_ref_depth(type) > 0) | (type_bare=="char" & get_ref_depth(type)==2))
    api_info_ref_out$ask_dupl <- api_info_ref_out$type=="void*"
    all_input_names <- c(r_name(api_info_input$name), bool_dupl_name(with(api_info_ref_out, name[ask_dupl])))

    text_c <- character(0)
    ## comment at the beginning of the function giving the original api
    text_c <- c(text_c, paste0("/* ", unique(api_info$original), " */"))

    ## function definition, both for .h and .c file
    if(length(all_input_names) > 0) {
        func_def <- paste0("SEXP ", r_name(unique(api_info$func_name)), "(", paste("SEXP", all_input_names, collapse=", "), ")")
    }
    else {
        func_def <- paste0("SEXP ", r_name(unique(api_info$func_name)), "(void)")
    }

    func_name <- unique(api_info$func_name)
    text_h <- c(text_c, paste0(func_def, ";", ""))
    text_c <- c(text_c, paste0(func_def, "{"))
    text_exp <- paste0("{\"", r_name(func_name), "\", (DL_FUNC) &", r_name(func_name), ", ", length(all_input_names), "},")


    ## insert counter for number of protected vars
    text_c <- c(text_c, "  int vars_protected=0;")
    
    ## insert start code if it exists
    text_c <- c(text_c, add_injection$start[[func_name]])
    
    ## create the body of the functions
    ## create the necessary function duplication
    for(i in seq_len(nrow(api_info_ref_out))) {
        text_c <- duplicate_object(text_c, cname=api_info_ref_out$name[i], ask=api_info_ref_out$ask_dupl[i])
    }

    ## add the code for unwrapping the input variables
    for(i in seq_len(nrow(api_info_input))) {
        text_c <- unwrap_variable(text_c, cname=api_info_input$name[i], ctype=api_info_input$type[i], category=api_info_input$category[i])
    }


    ## add pre_api call code
    text_c <- c(text_c, add_injection$pre_call[[func_name]])

    ## add code for calling the api
    text_c <- create_API_call(text_c, func_name=unique(api_info$func_name), return_type=api_info_output$type,
                              return_name="return_val", cnames=api_info_input$name)

    text_c <- c(text_c, add_injection$post_call[[func_name]])

    ## create the info for the output
    api_info_output$name <- "return_val"
    api_info_output$define_r_var <- TRUE
    if(nrow(api_info_ref_out) > 0) {
        api_info_ref_out$define_r_var <- FALSE
    }
    api_info_return <- rbind.fill(api_info_output, api_info_ref_out)
    
    ## create the wrapping for the return variables
    for(i in seq_len(nrow(api_info_return))) {
        text_c <- wrap_variable(text_c, cname=api_info_return$name[i], ctype=api_info_return$type[i], category=api_info_return$category[i],
                                define_r_var=api_info_return$define_r_var[i])
    }

    text_c <- c(text_c, add_injection$pre_list[[func_name]])
    
    ## create the return list
    text_c <- create_return_list(text_c, api_info_return$name)

    ## need to free return character string
    if(api_info_output$type=="char*") {
        text_c <- c(text_c, "  H5free_memory(return_val);")
    }
    

    ## define the helper variables and add the beginning, if they are needed
    if(any(grepl("R_helper", text_c, fixed=TRUE))) {
        text_c <- c(text_c[1:2], "  SEXP R_helper = R_NilValue;", text_c[-(1:2)])
    }
    if(any(grepl("size_helper", text_c, fixed=TRUE))) {
        text_c <- c(text_c[1:2], "  hsize_t size_helper;", text_c[-(1:2)])
    }

    ## code injection before end of function
    text_c <- c(text_c, add_injection$end[[func_name]])

    ## unprotect as needed
    text_c <- c(text_c, "  UNPROTECT(vars_protected);")
    
    ## return and end
    text_c <- c(text_c, "  return(__ret_list);")
    text_c <- c(text_c, "}", "")
    return(list(text_c=text_c, text_h=text_h, text_exp=text_exp))
}





## a function that creates the minimal .h file needed for automatic wrapper functions
minimal_h_file <- function(filename, copyright_notice) {
    file_variable <- gsub(".", "_", toupper(filename), fixed=TRUE)

    ## put the copyright notice at the top
    text <- copyright_notice
    
    text <- paste0("#ifndef _", file_variable, "_")
    text <- c(text, paste0("#define _", file_variable, "_"))
    text <- c(text, "#include \"global.h\"")
}

minimal_c_file <- function(filename, copyright_notice) {
    filename <- gsub(".c", ".h", filename, fixed=TRUE)

    ## put the copyright notice at the top
    text <- copyright_notice

    text <- c(text, paste0("#include \"", filename, "\""))
    return(text)
}


minimal_export_file <- function(filename, copyright_notice) {
    file_variable <- gsub(".", "_", toupper(filename), fixed=TRUE)

    text <- copyright_notice

    text <- paste0("#ifndef _", file_variable, "_")
    text <- c(text, paste0("#define _", file_variable, "_"))
    return(text)
}


write_file <- function(api_info_file, exprt_file, outpath, add_injection, copyright_notice) {
    ## create rudimentary .h and .c files
    text_c <- minimal_c_file(unique(api_info_file$filename_c), copyright_notice)
    text_h <- minimal_h_file(unique(api_info_file$filename_h), copyright_notice)

    libname <- gsub(".H$", "", toupper(unique(api_info_file$filename_h)), perl=TRUE)
    
    func_output <- dlply(api_info_file, c("filename_c", "filename_h", "func_name"), create_wrapper_API, add_injection=add_injection)

    ## get the export file output
    export_content_h <- unlist(llply(func_output, function(x) {return(x$text_exp)}))
    func_c <- unlist(llply(func_output, function(x) {return(x$text_c)}))
    func_h <- unlist(llply(func_output, function(x) {return(x$text_h)}))

    text_c <- c(text_c, func_c)
    text_h <- c(text_h, func_h)
    text_h <- c(text_h, "#endif")

    export_content_h <- c(paste0("R_CallMethodDef library_", libname, "[] = {"), export_content_h)
    export_content_h <- c(export_content_h,  "{NULL, NULL, 0}\n};\n")
    
    ## write it out into the appropriate files
    cat(text_c, file=file.path(outpath, unique(api_info_file$filename_c)), append=FALSE, sep="\n")
    cat(text_h, file=file.path(outpath, unique(api_info_file$filename_h)), append=FALSE, sep="\n")
    cat(export_content_h, file=file.path(outpath, exprt_file), append=TRUE, sep="\n")

    
}

## read in the function definitions
api_info_all <- readRDS( file=file.path("store", "functions_for_wrappping.rds"))

excluded_funcs_obsolete <- c("H5Acreate1", "H5Dcreate1", "H5Dopen1",
                             "H5Eclear1", "H5Epush1", "H5Pget_filter1",
                             "H5Pget_filter_by_id1", "H5Rget_obj_type1", "H5Tcommit1",
                             "H5Tarray_create1", "H5Topen1", "H5Tget_array_dims1", "H5Dextend")
excluded_funcs_not_used <- c("H5Lregister", "H5Sselect_select", "H5Scombine_select", "H5Oget_num_attrs", "H5Scombine_hyperslab", "H5Iobject_verify",
                             "H5Iremove_verify", "H5Pget_driver_info", "H5allocate_memory", "H5resize_memory")

excluded_funcs_needs_parallel <- c("H5Fget_mpi_atomicity", "H5Fset_mpi_atomicity", "H5Pget_all_coll_metadata_ops",
                                   "H5Pget_coll_metadata_write", "H5Pget_mpio_actual_chunk_opt_mode", "H5Pget_mpio_actual_io_mode",
                                   "H5Pget_mpio_no_collective_cause", "H5Pset_all_coll_metadata_ops", "H5Pset_coll_metadata_write")

excluded_funcs_manual <- NULL



api_info_all <- subset(api_info_all, !(func_name %in% c(excluded_funcs_obsolete, excluded_funcs_manual, excluded_funcs_not_used, excluded_funcs_needs_parallel)))

h5_file_start <- function(filename) {
    filename <- gsub("public", "", filename)
    filename <- gsub("\\..*", "", filename)
    return(filename)
}

## define the names for the output_h and output_c files
api_info_all <- within(api_info_all, {
    filename_c <- paste0("Wrapper_auto_", h5_file_start(basename(filename)), ".c")
    filename_h <- paste0("Wrapper_auto_", h5_file_start(basename(filename)), ".h")
})



files_to_do <- c("Wrapper_auto_H5A.c", "Wrapper_auto_H5D.c", "Wrapper_auto_H5E.c",
                 "Wrapper_auto_H5F.c", "Wrapper_auto_H5G.c", "Wrapper_auto_H5I.c",
                 "Wrapper_auto_H5L.c", "Wrapper_auto_H5O.c", "Wrapper_auto_H5P.c",
                 "Wrapper_auto_H5.c",  "Wrapper_auto_H5R.c", "Wrapper_auto_H5S.c",
                 "Wrapper_auto_H5T.c", "Wrapper_auto_H5Z.c",
                 "Wrapper_auto_H5DS.c", "Wrapper_auto_H5IM.c", "Wrapper_auto_H5LT.c",
                 "Wrapper_auto_H5TB.c",
                 "Wrapper_auto_H5FDcore.c", "Wrapper_auto_H5FDfamily.c",
                 "Wrapper_auto_H5FDlog.c", "Wrapper_auto_H5FDsec2.c", "Wrapper_auto_H5FDstdio.c") 

## exclude "Wrapper_auto_H5FDdirect.c" as it is not necessarily supported and not clear why it would be used ast this point
## get the code for the injection
source("injectionCode.R")



cat(minimal_export_file("export_auto.h", copyright_notice), file=file.path("output_code", "export_auto.h"), sep="\n", append=FALSE)
# write_file(h5t_api, exprt_file = "export.h", outpath="Testing")
d_ply(subset(api_info_all, filename_c %in% files_to_do), c("filename_c", "filename_h"), write_file, exprt_file="export_auto.h", outpath="output_code",
      add_injection=add_injection, copyright_notice=copyright_notice)
cat("#endif", file=file.path("output_code", "export_auto.h"), append=TRUE)

## write out a file with the library names
cat(paste0("library_", toupper(gsub(".c", "", files_to_do, fixed=TRUE))), sep=",\n", file=file.path("output", "library_names.txt"))

## write out list of .h names
cat(paste0("#include \"", gsub(".c", ".h", files_to_do, fixed=TRUE), "\""), sep="\n", file=file.path("output", "include_file_names.txt"))


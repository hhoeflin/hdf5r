## function to create the names of objects
r_name <- function(cname) {
    if(length(cname)==0) {
        return(character(0))
    }
    ## check if the name already starts with an underscore
    ## we can't do double underscore as some of those variable names are reserved
    prepend <- rep("R_", length(cname))
    return(paste0(prepend, cname))
}

bool_dupl_name <- function(cname) {
    if(length(cname)==0) {
        return(character(0))
    }
    return(paste0("_dupl_", cname))
}


is_const <- function(type) {
    return(grepl("^const", type, perl=TRUE))
}

make_bare <- function(type) {
    return(gsub("(const\\s+|\\**)", "", type, perl=TRUE))
}

get_ref_depth <- function(type) {
    sapply(regmatches(type, gregexpr("*", type, fixed=TRUE)), length)
}

## names for wrapping and unwrapping structs; will also be used for the union (corner case)
unwrap_struct_func_name <- function(struct_name) {
    return(paste0("SEXP_to_", struct_name))
}

wrap_struct_func_name <- function(struct_name) {
    return(paste0(struct_name, "_to_SEXP"))
}

reset_alt_struct_func_name <- function(struct_name) {
    return(paste0("reset_alt_", struct_name))
}

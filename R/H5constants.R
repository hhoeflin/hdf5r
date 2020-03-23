


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





##' These are all types that are used in HDF5
##'
##' HDF5 provides many native datatypes. These are all stored in the \code{h5types}
##' environment. An overview of all available types can be seen using \code{h5types$overview}.
##' Any specific type can be accessed using the \code{$}-operator. See also the examples below.
##'
##' @author Holger Hoefling
##' @export
##' @name h5types
##' @examples
##' h5types$overview
##' h5types$H5T_NATIVE_INT
##' h5types$H5T_NATIVE_DOUBLE
NULL




##' All constants used in HDF5
##' 
##' These are all constants used in HDF5. They are stored in an environment with locked bindings so that
##' they cannot be changed. An overview of all constants can be seen with \code{h5const$overview}, listing all of them.
##' Each constant can be accessed using \code{$} and the name of the constant. See the examples below.
##'
##' There are also some flags that govern edge cases of conversion from HDF5 to R. This is related to how integers are being treated and
##' the issue of R not being able to natively represent 64bit integers and not at all being able to represent unsigned 64bit integers
##' (even using add-on packages).
##' The constants all start with the term \code{H5TOR}. There are currently possible values
##' \describe{
##'   \item{H5TOR_CONV_NONE}{Doesn't do any conversion. Every integer datatype with more than 32 bit is returned as 64bit integers. For
##'   unsigned 64bit integers, the conversion to signed 64bit integers is done by truncation}
##'   \item{H5TOR_CONV_INT64_INT_NOLOSS}{Under this setting, whenever a 64 bit integer would be returned, it is checked if it would also
##'   fit into a 32 bit integer without data loss and returned as such if possible}
##'   \item{H5TOR_CONV_INT64_FLOAT_NOLOSS}{Under this setting, whenever a 64 bit integer would be returned, it is checked if it would also
##'   fit into a 64 bit floating point value without data loss and returned as such if possible}
##'   \item{H5TOR_CONV_INT64_NOLOSS}{Combines \code{H5TOR_CONV_INT64_INT_NOLOSS} and \code{H5TOR_CONV_INT64_FLOAT_NOLOSS} and is set
##'   as the default in the \code{hdf5r.h5tor_default} option.}
##'   \item{H5TOR_CONV_INT64_FLOAT_FORCE}{Under this setting, whenever a 64 bit integer would be returned, it is coerced to a double
##'   even if this results in a loss of precision. If a loss of precision occurs, a warning is issued. Please note that this also overrides
##'   the use of \code{H5TOR_CONV_UNIT64_NA}. As loss of precision is already accepted, UINT64-values that are larger than LLONG_MAX will be represented
##'   as their next possible floating point value.}
##'   \item{H5TOR_CONV_UINT64_NA}{When converting an unsigned 64bit integer, any values that don't fit into a signed 64bit integer are
##'   set to NA. If this flag is not set, then the values will be truncated to \code{LLONG_MAX}, the largest 64bit signed integer.}
##'   \item{H5TOR_CONV_DEFAULT}{Is both \code{H5TOR_CONV_INT64_INT} and \code{H5TOR_CONV_UNIT64_FLOAT}}
##' }
##' 
##' @author Holger Hoefling
##' @export
##' @name h5const
##' @examples
##' h5const$overview
##' h5const$H5F_ACC_RDWR
##' h5const$H5F_ACC_DEFAULT
##' # Combining flags
##' bitwOr(h5const$H5TOR_CONV_UINT64_NA, h5const$H5TOR_CONV_INT64_INT_NOLOSS)
NULL

h5types <- new.env()
h5const <- new.env()




##' Retrieving a copy of a type
##'
##' The types are stored in the environment \code{\link{h5types}}. These types should not be accessed
##' directly. Therefor, the \code{$}-operator is overloaded to ensure that every type that is accessed is a copy of the
##' original type
##' @title Retrieving a copy of a type
##' @param x The environment to request it from
##' @param name The name of the type that is requested
##' @return Returns an object that is a copy of a type that was requested
##' @author Holger Hoefling
##' @export
##' @rdname types_env_access
"$.types_env" <- function(x, name) {
    a <- get(name, envir=x)
    if(inherits(a, "H5T")) {
        return(a$copy())
    }
    else {
        return(a)
    }
}


##' @rdname types_env_access
##' @export
"[[.types_env" <- function(x, name) {
    a <- get(name, envir=x)
    if(inherits(a, "H5T")) {
        return(a$copy())
    }
    else {
        return(a)
    }
}

install_types_const <- function(h5types, h5const) {
    all_types_frame <- .Call("show_all_types_data_frame", PACKAGE="hdf5r")
    all_const_frame <- .Call("show_all_const_data_frame", PACKAGE="hdf5r") 

    ## exclude H5F_ACC_DEBUG; listed as 0; not supported for end-users
    all_const_frame <- all_const_frame[all_const_frame$Name != "H5F_ACC_DEBUG",]
    
    ## of all the datatypes, get all individual values
    all_types_unique <- unique(all_types_frame$Type_id)
    names(all_types_unique) <- as.character(all_types_unique)

    all_types_unique_list <- H5T_factory(all_types_unique, do_copy=TRUE)
    
    ## now assign the types
    for(i in seq_len(nrow(all_types_frame))) {
        h5types[[all_types_frame$Name[i]]] <- all_types_unique_list[[as.character(all_types_frame$Type_id[i])]]
        lockBinding(all_types_frame$Name[i], h5types)
    }
   
    class(h5types) <- c("types_env", "environment")

    ## want to add an H5T_LOGICAL and H5T_LOGICAL_NA
    ## need to do it after class is assigned, otherwise copy doesn't work
    dtype_logical <- H5T_LOGICAL$new(include_NA=FALSE)
    dtype_logical_na <- H5T_LOGICAL$new(include_NA=TRUE)
    h5types[["H5T_LOGICAL"]] <- dtype_logical
    lockBinding("H5T_LOGICAL", h5types)
    h5types[["H5T_LOGICAL_NA"]] <- dtype_logical_na
    lockBinding("H5T_LOGICAL_NA", h5types)
    
    
    ## and assign the overview table
    all_types_frame <- rbind(all_types_frame, data.frame(Category=c("Custom", "Custom"), Name=c("H5T_LOGICAL", "H5T_LOGICAL_NA"),
                                                         Type_id=as.integer64(c(dtype_logical$id, dtype_logical_na$id))))
    h5types$overview <- all_types_frame
    lockBinding("overview", h5types)
    lockEnvironment(h5types)

    ## now extract constants from the enums
    all_enums <- subset(all_types_frame, Category=="enum")
    all_enum_const_list <- vector("list", length=nrow(all_enums))
    for(i in seq_len(nrow(all_enums))) {
        enum_df <- extract_enum_const(h5types[[all_enums$Name[i]]], all_enums$Name[i])
        enum_df$Constant <- as.integer64(enum_df$Constant)
        all_enum_const_list[[i]] <- enum_df
    }
    all_enum_const <- do.call("rbind", all_enum_const_list)

    all_const_frame <- rbind(all_const_frame, all_enum_const)
    
    ## split it by category into lists;
    ## add the overview, the lists and the individual numbers
    h5const$overview <- all_const_frame
    lockBinding("overview", h5const)

    ## take H5P_DEFAULT out and treat it separately;
    ## will not be a constant, but a special H5P object
    h5p_default_val <- all_const_frame$Constant[all_const_frame$Name=="H5P_DEFAULT"]
    all_const_frame <- subset(all_const_frame, Name!="H5P_DEFAULT")
    h5const$H5P_DEFAULT <- H5P_DEFAULT$new(id=h5p_default_val)
    lockBinding("H5P_DEFAULT", h5const)

    ## same for H5S_ALL, make it into a H5S object
    h5s_all_val <- all_const_frame$Constant[all_const_frame$Name=="H5S_ALL"]
    all_const_frame <- subset(all_const_frame, Name!="H5S_ALL")
    h5const$H5S_ALL <- H5S_ALL$new(id=h5s_all_val)
    lockBinding("H5S_ALL", h5const)
        
    ## each constant category as a named vector
    all_const_frame_split <- split(all_const_frame, all_const_frame$Category)
    for(i in seq_along(all_const_frame_split)) {
        labels <- all_const_frame_split[[i]]$Name
        values <- all_const_frame_split[[i]]$Constant
        h5const[[unique(all_const_frame_split[[i]]$Category)]] <- factor_ext(values, values=values, levels=labels)
        lockBinding(unique(all_const_frame_split[[i]]$Category), h5const)

        ## now make the constants into extended factors
        for(j in seq_len(nrow(all_const_frame_split[[i]]))) {
            item <- all_const_frame_split[[i]]$Constant[j]
            name <- all_const_frame_split[[i]]$Name[j]
            h5const[[name]] <- factor_ext(item, values=values, levels=labels)
            lockBinding(name, h5const)
        }
    }

    # if we use HDF5 version 1.12 or higher, we have
    # H5R_OBJECT1 and H5R_OBJECT2, not H5R_OBJECT
    # H5R_DATASET_REGION1 and H5R_DATASET_REGION2, not H5R_DATASET_REGION
    if(compareVersion(h5version(verbose=FALSE), "1.12.0") >= 0) {
        h5const[["H5R_OBJECT"]] <- h5const$H5R_OBJECT1
        lockBinding("H5R_OBJECT", h5const)
        h5const[["H5R_DATASET_REGION"]] <- h5const$H5R_DATASET_REGION1
        lockBinding("H5R_DATASET_REGION", h5const)
    }
    ## and each constant individually
    lockEnvironment(h5const)
    
    return(invisible(NULL))
}

extract_enum_const <- function(h5type, name) {
    return(data.frame(Category=name, Name=h5type$get_labels(), Constant=h5type$get_values(), stringsAsFactors=FALSE))
}


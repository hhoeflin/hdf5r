
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


##' Extract HDF5-ids and return as a vector
##'
##' Internal helper function. Given a list of id-type-objects, it extracts the
##' ids itself and returns them as a vector
##' @title Extract HDF5-ids and return as a vector
##' @param dtype_ids Ids itself or class objects to extract the ids from. 
##' @return The ids as a integer64-vector
##' @author Holger Hoefling
##' @importFrom bit64 as.integer64
##' @keywords internal
H5T_extractID <- function(dtype_ids) {
    if(inherits(dtype_ids, "H5T")) {
        dtype_ids_out <- dtype_ids$id
    }
    else if(is.list(dtype_ids)) {
        for(i in seq_along(dtype_ids)) {
            dtype_ids[[i]] <- H5T_extractID(dtype_ids[[i]])
        }
        dtype_ids_out <- unlist(dtype_ids)
        class(dtype_ids_out) <- "integer64"
    }
    else if(is.numeric(dtype_ids)) {
        if(any(bit64::as.integer64(dtype_ids)  != dtype_ids)) {
            stop("Numeric values cannot be coerced to integer")
        }
        else {
            dtype_ids_out <- bit64::as.integer64(dtype_ids)
            names(dtype_ids_out) <- names(dtype_ids)
        }
    }
    else {
        stop("'dtype_ids' has to be a vector or list with elements of type 'H5T' or integer (or coercible to integer)")
    }
    return(dtype_ids_out)
}


##' Turn ids into  \code{\link{H5T}} objects
##'
##' Gets the HDF5 internal class for an id and dispatches them so that the correct
##' R6es are being created.
##' @title Turn ids into  \code{\link{H5T}} objects
##' @param ids The ids to return as objects
##' @param do_copy Should the ids be copied using HDF5s internal copy mechanism
##' @return An object of type R6 class \code{\link{H5T}}
##' @author Holger Hoefling
##' @importFrom bit64 as.integer64
##' @keywords internal
H5T_factory <- function(ids, do_copy=FALSE) {
    if(!missing(ids)) {
        ids <- H5T_extractID(ids)

        ## look at the ids and their class, and produce the appropriate H5T class
        res <- vector("list", length=length(ids))
        for(i in seq_along(ids)) {
            if(do_copy) {
                foo <- .Call("R_H5Tcopy", bit64::as.integer64(ids[i]), PACKAGE="hdf5r")$return_val
                ids[i] <- foo
            }
            if(is.na(ids[i]) || ids[i] < 0) {
                stop("Invalid ids")
            }
            cls_id <- .Call("R_H5Tget_class", bit64::as.integer64(ids[i]), PACKAGE="hdf5r")$return_val
            if(cls_id == "H5T_NO_CLASS") {
                stop("Unknown cls_id")
            }
            class_name <- as.character(cls_id)

            ## now if it is a compound, need to check if it should be a H5T_COMPLEX
            if(class_name == "H5T_COMPOUND") {
                labels <- .Call("h5get_compound_names", ids[i], PACKAGE="hdf5r")$return_val
                if(length(labels) == 2 && all(labels == c("Real", "Imaginary"))) {
                    class_name <- "H5T_COMPLEX"
                }
            }

            ## if is enum, need to check if it is logical
            if(class_name == "H5T_ENUM") {
                labels = .Call("h5get_enum_labels", ids[i], PACKAGE="hdf5r")$return_val
                values = .Call("h5get_enum_values", ids[i], PACKAGE="hdf5r")$return_val
                if(length(labels) == 3 && length(values) == 3 && all(labels==c("FALSE", "TRUE", "NA")) && all(values==c(0,1,2))) {
                    class_name <- "H5T_LOGICAL"
                }
                else if(length(labels) == 2 && length(values) == 2 && all(labels==c("FALSE", "TRUE")) && all(values==c(0,1))) {
                    class_name <-"H5T_LOGICAL"
                }
            }
                           
            res[[i]] <- switch(class_name, H5T_COMPOUND=H5T_COMPOUND$new(id=ids[i]), H5T_COMPLEX=H5T_COMPLEX$new(id=ids[i]),
                               H5T_ENUM=H5T_ENUM$new(id=ids[i]), H5T_LOGICAL=H5T_LOGICAL$new(id=ids[i]),
                               H5T_ARRAY=H5T_ARRAY$new(id=ids[i]), H5T_STRING=H5T_STRING$new(id=ids[i]),
                               H5T_VLEN=H5T_VLEN$new(id=ids[i]), H5T_INTEGER=H5T_INTEGER$new(id=ids[i]), H5T_FLOAT=H5T_FLOAT$new(id=ids[i]),
                               H5T_BITFIELD=H5T_BITFIELD$new(id=ids[i]),
                               H5T$new(id=ids[i]))
        }
        if(length(ids)==1) {
            return(res[[1]])
        }
        else {
            names(res) <- names(ids)
            return(res)
        }
    }
    else {
        return(list())
    }
}

##' Convert a text description to a datatype
##'
##' Converts a text to a datatype using the HDF5 function H5LT_text_to_dtype. Documentation can be found at 
##' \url{https://www.hdfgroup.org/HDF5/doc/HL/RM_H5LT.html#H5LTtext_to_dtype}.
##' @title Convert a text description to a datatype
##' @param text The text to convert to the datatype
##' @param lang_type The type of language to use; currently only \code{H5LT_DDL} is supported.
##' @return A datatype corresponding to the text with the appropriate class inheriting from \code{\link{H5T}}.
##' @author Holger Hoefling
##' @export
text_to_dtype <- function(text, lang_type=h5const$H5LT_DDL) {
    id <- .Call("R_H5LTtext_to_dtype", paste(as.character(text), collapse = "\n"), h5const$H5LT_DDL, PACKAGE = "hdf5r")$return_val
    if(id < 0) {
        stop("Error trying to convert text to a datatype")
    }
    return(H5T_factory(ids=id))
}


#' Class for HDF5 datatypes.
#'
#' This is the base class for all datatypes, but most have a specialised class.
#' This class represents an HDF5 datatype. It inherits all functions of the
#' \code{\link{H5RefClass}}. It is also the base class for many other classes well, specifically
#' \describe{
#' \item{Integer}{\code{\link{H5T_INTEGER}}}
#' \item{Bitfield}{\code{\link{H5T_BITFIELD}} (currently identical to the integer class)}
#' \item{Float}{\code{\link{H5T_FLOAT}}}
#' \item{Enum}{\code{\link{H5T_ENUM}}}
#' \item{Compound}{\code{\link{H5T_COMPOUND}}}
#' \item{String}{\code{\link{H5T_STRING}}}
#' \item{Complex}{\code{\link{H5T_COMPLEX}}}
#' \item{Array}{\code{\link{H5T_ARRAY}}}
#' \item{Variable Length}{\code{\link{H5T_VLEN}}}
#' }
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link{H5T}}.
#' @author Holger Hoefling
#'
#' @examples
#' my_int <- h5types$H5T_NATIVE_INT
#' my_int$to_text()
#' my_int$get_size()
#'
#' # Show how to commit a datatype
#' fname <- tempfile(fileext = ".h5")
#' file <- H5File$new(fname, mode = "a")
#' my_int$is_committed()
#' file$commit("my_int", my_int)
#' my_int$is_committed()
#'
#' # can now also add attributes
#' h5attr(my_int, "test") <- "A string"
#' h5attributes(my_int)
#' 
#' file$close_all()
#' file.remove(fname)
#' @export
H5T <- R6Class("H5T",
               inherit=H5RefClass,
               public=list(
                   initialize=function(id) {
                       "Internal use only"
                       super$initialize(id)
                   },
                   get_class=function() {
                       "This function implements the HDF5-API function H5Tget_class."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_CLASS} for details."

                       cls_id <- .Call("R_H5Tget_class", self$id, PACKAGE="hdf5r")$return_val
                       return(cls_id)
                   },
                   get_size=function(...) {
                       "This function implements the HDF5-API function H5Tget_size."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_SIZE} for details."
                       "@param ... ignored"

                       return(.Call("R_H5Tget_size", self$id, PACKAGE="hdf5r")$return_val)
                   },
                   set_size=function(size) {
                       "This function implements the HDF5-API function H5Tset_size."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_SIZE} for details."

                       if(size==Inf) {
                           if(self$get_class() != h5const$H5T_STRING) {
                               stop("Can only set to infinite size if datatype is a string; use H5T_VLEN instead for variable length data")
                           }
                           herr <- .Call("R_H5Tset_size", self$id, Inf, PACKAGE="hdf5r")$return_val
                       }
                       else {
                           herr <- .Call("R_H5Tset_size", self$id, as.integer(size), PACKAGE="hdf5r")$return_val
                       }
                       if(herr < 0) {
                           stop("Could not set size to specified value")
                       }
                       return(invisible(self))
                   },
                   set_precision=function(precision) {
                       "This function implements the HDF5-API function H5Tset_precision."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_PRECISION} for details."

                       herr <- .Call("R_H5Tset_precision", self$id, as.integer(precision), PACKAGE = "hdf5r")$return_val
                       if(herr < 0) {
                           stop("Could not set precision")
                       }
                       return(invisible(self))
                   },
                   get_precision=function() {
                       "This function implements the HDF5-API function H5Tget_precision."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_PRECISION} for details."

                       prec <- .Call("R_H5Tget_precision", self$id, PACKAGE = "hdf5r")$return_val
                       if(prec < 0) {
                           stop("There was an error retrieving the precision")
                       }
                       return(prec)
                   },
                   set_order=function(order) {
                       "This function implements the HDF5-API function H5Tset_order."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_ORDER} for details."

                       herr <- .Call("R_H5Tset_order", self$id, as.integer(order), PACKAGE = "hdf5r")$return_val
                       if(herr < 0) {
                           stop("Could not set order")
                       }
                       return(invisible(self))
                   },
                   get_order=function() {
                       "This function implements the HDF5-API function H5Tget_order."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_ORDER} for details."

                       order <- .Call("R_H5Tget_order", self$id, PACKAGE = "hdf5r")$return_val
                       if(order < 0) {
                           stop("There was an error retrieving the order")
                       }
                       return(order)
                   },
                   set_offset=function(offset) {
                       "This function implements the HDF5-API function H5Tset_offset."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_OFFSET} for details."

                       herr <- .Call("R_H5Tset_offset", self$id, as.integer(offset), PACKAGE = "hdf5r")$return_val
                       if(herr < 0) {
                           stop("Could not set offset")
                       }
                       return(invisible(self))
                   },
                   get_offset=function() {
                       "This function implements the HDF5-API function H5Tget_offset."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_OFFSET} for details."

                       offset <- .Call("R_H5Tget_offset", self$id, PACKAGE = "hdf5r")$return_val
                       if(offset < 0) {
                           stop("There was an error retrieving the offset")
                       }
                       return(offset)
                   },
                   set_pad=function(pad) {
                       "This function implements the HDF5-API function H5Tset_pad."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_PAD} for details."

                       herr <- .Call("R_H5Tset_pad", self$id, as.integer(pad), PACKAGE = "hdf5r")$return_val
                       if(herr < 0) {
                           stop("Could not set pad")
                       }
                       return(invisible(self))
                   },
                   get_pad=function() {
                       "This function implements the HDF5-API function H5Tget_pad."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_PAD} for details."

                       pad <- .Call("R_H5Tget_pad", self$id, PACKAGE = "hdf5r")$return_val
                       if(pad < 0) {
                           stop("There was an error retrieving the pad")
                       }
                       return(pad)
                   },
                   copy=function() {
                       "This function implements the HDF5-API function H5Tcopy."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_COPY} for details."

                       id <- .Call("R_H5Tcopy", self$id, PACKAGE="hdf5r")$return_val
                       return(H5T_factory(id, do_copy=FALSE))
                   },
                   is_committed=function() {
                       "This function implements the HDF5-API function H5Tcommitted."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_COMMITTED} for details."

                       htri <- .Call("R_H5Tcommitted", self$id, PACKAGE="hdf5r")$return_val
                       if(htri < 0) {
                           stop("Error checking if a datatype has been committed")
                       }
                       return(as.logical(htri))
                   },
                   equal=function(dtype) {
                       "This function implements the HDF5-API function H5Tequal."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_EQUAL} for details."

                       if(is.numeric(dtype)) {
                           dtype <- bit64::as.integer64(dtype)
                       }
                       if(inherits(dtype, "H5T")) {
                           dtype <- dtype$id
                       }
                       if(!is.integer64(dtype)) {
                           stop("'dtype' has to be either numeric, coercible to integer of of class 'H5T'")
                       }
                       eq_res <- .Call("R_H5Tequal", self$id, dtype, PACKAGE="hdf5r")$return_val
                       if(eq_res < 0) {
                           stop("There was a problem in the comparison")
                       }
                       return(as.logical(eq_res))
                   },
                   is_vlen=function() {
                       "This function detects if the underlying type is H5T_VLEN or a variable length string. This is used to know if"
                       "after reading a dataset, memory has to be freed"

                       htri <- .Call("R_H5Tdetect_vlen", self$id, PACKAGE = "hdf5r")$return_val
                       if(htri < 0) {
                           stop("Error trying to detect if type is of variable length")
                       }
                       return(as.logical(htri))
                   },
                   detect_class=function(dtype_class) {
                       "This function implements the HDF5-API function H5Tdetect_class."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_DETECT_CLASS} for details."

                       htri <- .Call("R_H5Tdetect_class", self$id, dtype_class, PACKAGE = "hdf5r")$return_val
                       if(htri < 0) {
                           stop("Error trying to detect if type is of variable length")
                       }
                       return(as.logical(htri))
                   },
                   get_native_type=function(direction=h5const$H5T_DIR_ASCEND) {
                       "This function implements the HDF5-API function H5Tget_native_type."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_NATIVE_TYPE} for details."

                       id <- .Call("R_H5Tget_native_type", self$id, direction, PACKAGE="hdf5r")$return_val
                       if(id < 0) {
                           stop("Error retrieving native-c-type")
                       }
                       return(H5T_factory(id=id))
                   },
                   get_create_plist=function() {
                       "This function implements the HDF5-API function H5Tget_create_plist."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_CREATE_PLIST} for details."

                       id <- .Call("R_H5Tget_create_plist", self$id, PACKAGE="hdf5r")$return_val
                       if(id < 0) {
                           stop("Error retrieving type_creation_plist")
                       }
                       return(H5P_TYPE_CREATE$new(id=id))
                   },
                   to_text=function(lang_type=h5const$H5LT_DDL) {
                       "This function implements the HDF5-API function H5LTdtype_to_text."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/HL/RM_H5LT.html#H5LTdtype_to_text} for details."
                       res <- standalone_H5T_dtype_to_text(self$id, lang_type)

                       return(res)
                   },
                   print=function(...){
                       "Prints information for the group"
                       "@param ... ignored"
                       
                       is_valid <- self$is_valid
                       
                       print_class_id(self, is_valid)

                       if(is_valid) {
                           type_text <- self$to_text()
                           cat("Datatype: ", type_text, "\n", sep="")
                       }
                       return(invisible(self))
                   }
                   ),
               private=list(
                   closeFun=function(id) if(!is.na(id) && is.loaded("R_H5Tclose", PACKAGE="hdf5r")) {
                          invisible(.Call("R_H5Tclose", id, PACKAGE = "hdf5r"))
                   }
                   ),
               cloneable=FALSE
               )

## add a common function
R6_set_list_of_items(H5T, "public", commonFGDT, overwrite=TRUE)
R6_set_list_of_items(H5T, "public", commonFGT, overwrite=TRUE)


standalone_H5T_dtype_to_text <- function(h5t_id, lang_type) {
    res <- .Call("R_H5LTdtype_to_text", h5t_id, character(0), lang_type, request_empty(1), PACKAGE="hdf5r")
    if(res$return_val < 0) {
        stop("Could not retrieve the necessary size of the buffer to convert type to text")
    }
    char_buf <- paste(rep(" ", res$len + 1), collapse="")
    res <- .Call("R_H5LTdtype_to_text", h5t_id, char_buf, lang_type, nchar(char_buf), PACKAGE="hdf5r")
    if(res$return_val < 0) {
        stop("Could not convert type to text")
    }
    return(res$str)
}


#' Class for HDF5 integer-datatypes.
#'
#' Inherits from class \code{\link[=H5T]{H5T}}.
#' Users should not create integer datatypes themselves using this class. Instead, integer should be derived
#' from one of the base-types such as \code{h5types$H5T_NATIVE_INT} (which internally automatically creates a copy of the type).
#' For a complete list of types see \code{h5types$overview}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5T_INTEGER]{H5T_INTEGER}}.
#' @export
#' @aliases H5T_BITFIELD H5T_BITFIELD
#' @author Holger Hoefling
#' @seealso \code{\link[=H5T]{H5T}}
#'
#' @examples
#' my_int <- h5types$H5T_NATIVE_INT
#'
#' # make an int with 2 bit
#' my_int$set_sign(h5const$H5T_SGN_NONE)
#' my_int$set_size(1)
#' my_int$set_precision(2)
#' my_int$describe()
H5T_INTEGER <- R6Class("H5T_INTEGER",
                       inherit=H5T,
                       public=list(
                           set_sign=function(sign) {
                               "This function implements the HDF5-API function H5Tset_sign."
                               "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_SIGN} for details."

                               herr <- .Call("R_H5Tset_sign", self$id, as.integer(sign), PACKAGE = "hdf5r")$return_val
                               if(herr < 0) {
                                   stop("Could not set sign")
                               }
                               return(invisible(self))
                           },
                           get_sign=function() {
                               "This function implements the HDF5-API function H5Tget_sign."
                               "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_SIGN} for details."

                               sign <- .Call("R_H5Tget_sign", self$id, PACKAGE = "hdf5r")$return_val
                               return(sign)
                               if(sign < 0) {
                                   stop("There was an error retrieving the sign")
                               }
                           },
                           describe=function() {
                               "Return a vector that describes the key features of the datatype"
                               return(list(size=self$get_size(), precision=self$get_precision(), sign=self$get_sign(),
                                           order=self$get_order()))
                           }
                           ),
                       cloneable=FALSE)

H5T_BITFIELD <- H5T_INTEGER


#' Class for HDF5 floating point datatypes.
#'
#' Inherits from class \code{\link[=H5T]{H5T}}. Users should not create float types with this class, but instead
#' use e.g. \code{h5types$H5T_NATIVE_DOUBLE}. Using the functions of this class, many aspects of the representation of the
#' floating point number can then be manipulated.
#' 
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5T_FLOAT]{H5T_FLOAT}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5T]{H5T}}
H5T_FLOAT <- R6Class("H5T_FLOAT",
                       inherit=H5T,
                       public=list(
                           set_fields=function(spos, epos, esize, mpos, msize) {
                               "This function implements the HDF5-API function H5Tset_fields."
                               "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_FIELDS} for details."

                               herr <- .Call("R_H5Tset_fields", self$id, spos, epos, esize, mpos, msize, PACKAGE="hdf5r")$return_val
                               if(herr < 0) {
                                   stop("Error setting fields")
                               }
                           },
                           get_fields=function() {
                               "This function implements the HDF5-API function H5Tget_fields."
                               "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_FIELDS} for details."

                               res <- .Call("R_H5Tget_fields", self$id, request_empty(1), request_empty(1), request_empty(1), request_empty(1),
                                            request_empty(1), PACKAGE="hdf5r")
                               if(res$return_val < 0) {
                                   stop("Error retrieving fields")
                               }
                               return(list(spos=res$spos, epos=res$epos, esize=res$esize, mpos=res$mpos, msize=res$msize))
                           },
                           set_ebias=function(ebias) {
                               "This function implements the HDF5-API function H5Tset_ebias."
                               "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_EBIAS} for details."

                               herr <- .Call("R_H5Tset_ebias", self$id, as.integer(ebias), PACKAGE = "hdf5r")$return_val
                               if(herr < 0) {
                                   stop("Could not set ebias")
                               }
                               return(invisible(self))
                           },
                           get_ebias=function() {
                               "This function implements the HDF5-API function H5Tget_ebias."
                               "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_EBIAS} for details."

                               ebias <- .Call("R_H5Tget_ebias", self$id, PACKAGE = "hdf5r")$return_val
                               return(ebias)
                               if(ebias < 0) {
                                   stop("There was an error retrieving the ebias")
                               }
                           },
                           set_norm=function(norm) {
                               "This function implements the HDF5-API function H5Tset_norm."
                               "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_NORM} for details."

                               herr <- .Call("R_H5Tset_norm", self$id, as.integer(norm), PACKAGE = "hdf5r")$return_val
                               if(herr < 0) {
                                   stop("Could not set norm")
                               }
                               return(invisible(self))
                           },
                           get_norm=function() {
                               "This function implements the HDF5-API function H5Tget_norm."
                               "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_NORM} for details."

                               norm <- .Call("R_H5Tget_norm", self$id, PACKAGE = "hdf5r")$return_val
                               return(norm)
                               if(norm < 0) {
                                   stop("There was an error retrieving the norm")
                               }
                           },
                           set_inpad=function(inpad) {
                               "This function implements the HDF5-API function H5Tset_inpad."
                               "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_INPAD} for details."

                               herr <- .Call("R_H5Tset_inpad", self$id, as.integer(inpad), PACKAGE = "hdf5r")$return_val
                               if(herr < 0) {
                                   stop("Could not set inpad")
                               }
                               return(invisible(self))
                           },
                           get_inpad=function() {
                               "This function implements the HDF5-API function H5Tget_inpad."
                               "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_INPAD} for details."

                               inpad <- .Call("R_H5Tget_inpad", self$id, PACKAGE = "hdf5r")$return_val
                               return(inpad)
                               if(inpad < 0) {
                                   stop("There was an error retrieving the inpad")
                               }
                           },
                           describe=function() {
                               "Print a detailed description of the datatype; this is experimental"
                               return(list(size=self$get_size(), precision=self$get_precision(),
                                           fields=self$get_fields(), ebias=self$get_ebias(), norm=self$get_norm(),
                                           inpad=self$get_inpad()))
                           }
                           ),
                     cloneable=FALSE)

#' Class for HDF5 enumeration datatypes.
#'
#' Inherits from class \code{\link[=H5T]{H5T}}.
#' @docType class
#' @importFrom R6 R6Class
#' @importFrom utils compareVersion
#' @return Object of class \code{\link[=H5T_ENUM]{H5T_ENUM}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5T]{H5T}}
#'
#' @examples
#' nucleotide_enum <- H5T_ENUM$new(labels=c("A", "C", "G", "T"), values=0:3)
#' nucleotide_enum
#' # For HDF5 1.8.16 or higher, the size and precision are set optimally
#' nucleotide_enum$get_size()
#' nucleotide_enum$get_precision()
H5T_ENUM <- R6Class("H5T_ENUM",
                    inherit=H5T_INTEGER,
                    public=list(
                        initialize=function(labels, values=seq_along(labels), id=NULL) {
                            "Create an enumeration datatype. This is either a factor-like object or a logical variable (that is"
                            "internally represented as an ENUM-type."
                            "@param labels The labels of the ENUM-type"
                            "@param values The values corresponding to the labels"
                            "@param id Internal use only"
                            if(!is.null(id)) {
                                super$initialize(id=id)
                                return(self)
                            }
                            if(!missing(labels)) {
                                if(missing(values)) {
                                    values <- seq_along(labels)
                                }
                                max_abs <- max(abs(values))
                                has_neg <- any(values < 0)
                                needed_precision <- ceiling(log2(max_abs + 1))
                                if(has_neg) {
                                    needed_precision <- needed_precision + 1
                                }
                                size <- ceiling(needed_precision / 8)

                                if(has_neg) {
                                    if(size <= 1) {
                                        dtype_id <- h5types$H5T_NATIVE_CHAR
                                    }
                                    else if(size <= 2) {
                                        dtype_id <- h5types$H5T_NATIVE_SHORT
                                    }
                                    else if(size <= 4) {
                                        dtype_id <- h5types$H5T_NATIVE_INT
                                    }
                                    else {
                                        dtype_id <- h5types$H5T_NATIVE_LLONG
                                    }
                                }
                                else {
                                    if(size <= 1) {
                                        dtype_id <- h5types$H5T_NATIVE_UCHAR
                                    }
                                    else if(size <= 2) {
                                        dtype_id <- h5types$H5T_NATIVE_USHORT
                                    }
                                    else if(size <= 4) {
                                        dtype_id <- h5types$H5T_NATIVE_UINT
                                    }
                                    else {
                                        if(needed_precision==64) {
                                            stop("Can't support UINT64; unsigned precision of 64bit not possible")
                                        }
                                        else {
                                            dtype_id <- h5types$H5T_NATIVE_LLONG
                                        }
                                    }
                                }
                                if(compareVersion(h5version(verbose=FALSE), "1.8.16") >= 0) {
                                    ## can only do this for 1.8.16 or above
                                    ## lower version have problems getting native type of an enum based on a non-native type
                                    dtype_id$set_size(size)
                                    dtype_id$set_precision(needed_precision)
                                }
                                id <- .Call("h5create_enum_type", as.character(labels), values, dtype_id$id, PACKAGE="hdf5r")$return_val
                                super$initialize(id=id)
                                return(self)
                            }
                            stop("None of the parameters were set")
                        },
                        get_labels=function() {
                            "Return all the labels of the enumeration type"
                            return(.Call("h5get_enum_labels", self$id, PACKAGE="hdf5r")$return_val)
                        },
                        get_values=function() {
                            "Return the values of the enumeration type"
                            return(.Call("h5get_enum_values", self$id, PACKAGE = "hdf5r")$return_val)
                        },
                        set_size=function(size) {
                            "Base type of every enum is \\code{H5T_INTEGER}. This disables the set_size function"
                            stop("Function 'set_size' not allowed for 'H5T_ENUM'")
                        },
                        get_super=function() {
                            "Returns \\code{\\link{H5T_INTEGER}} that is the base type of the enumeration"
                            id <- .Call("R_H5Tget_super", self$id, PACKAGE="hdf5r")$return_val
                            if(id < 0) {
                                stop("Error retrieving super_type")
                            }
                            return(H5T_factory(id=id))
                        },
                        describe=function() {
                            "Print a detailed description of the datatype; this is experimental"

                            return(list(super=self$get_super()$describe(), labels=self$get_labels(), values=self$get_values()))
                        }

                        ),
                    cloneable=FALSE
                    )



#' Class for HDF5 logical datatypes. This is an enum with the 3 values FALSE, TRUE and NA mapped on values 0, 1 and 2.
#' Is transparently mapped onto a logical variable
#'
#' Inherits from class \code{\link[=H5T]{H5T}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5T_LOGICAL]{H5T_LOGICAL}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5T]{H5T}}, \code{\link[=H5T_ENUM]{H5T_ENUM}}
H5T_LOGICAL <-  R6Class("H5T_LOGICAL",
                    inherit=H5T_ENUM,
                    public=list(
                        initialize=function(include_NA=TRUE, id=NULL) {
                            "Create a logical datatype. This is"
                            "internally represented by an ENUM-type"
                            "@param id Internal use only"
                            if(!is.null(id)) {
                                super$initialize(id=id)
                                return(self)
                            }
                            if(include_NA) {
                                dtype_id <- h5types$H5T_NATIVE_UCHAR
                                if(compareVersion(h5version(verbose=FALSE), "1.8.16") >= 0) {
                                    ## can only do this for 1.8.16 or above
                                    ## lower version have problems getting native type of an enum based on a non-native type
                                        dtype_id$set_size(1)
                                        dtype_id$set_precision(2)
                                }
                                id <- .Call("h5create_enum_type", as.character(c("FALSE","TRUE", "NA")), as.integer(c(0,1,2)), dtype_id$id, PACKAGE="hdf5r")$return_val
                                super$initialize(id=id)
                                return(self)
                            }
                            else {
                                dtype_id <- h5types$H5T_NATIVE_UCHAR
                                if(compareVersion(h5version(verbose=FALSE), "1.8.16") >= 0) {
                                    ## can only do this for 1.8.16 or above
                                    ## lower version have problems getting native type of an enum based on a non-native type
                                        dtype_id$set_size(1)
                                        dtype_id$set_precision(1)
                                }
                                id <- .Call("h5create_enum_type", as.character(c("FALSE","TRUE")), as.integer(c(0,1)), dtype_id$id, PACKAGE="hdf5r")$return_val
                                super$initialize(id=id)
                                return(self)
                            }
                        }),
                        cloneable=FALSE
                        )

#' Class for HDF5 compound datatypes.
#'
#' Inherits from class \code{\link[=H5T]{H5T}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5T_COMPOUND]{H5T_COMPOUND}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5T]{H5T}}
#'
#' @examples
#' # create a H5T_COMPOUND  corresponding to a data-frame
#' my_cpd <- H5T_COMPOUND$new(c("name", "age", "salary"),
#'     dtypes=list(H5T_STRING$new(size=200), h5types$H5T_NATIVE_INT, h5types$H5T_NATIVE_DOUBLE))
#' my_cpd
H5T_COMPOUND <- R6Class("H5T_COMPOUND",
                        inherit=H5T,
                        public=list(
                            initialize=function(labels, dtypes, size=NULL, offset=NULL, id=NULL) {
                                "Create at compound type that is the HDF5 equivalent of a table"
                                "@param labels The labels of the columns of the compound object"
                                "@param dtypes The datatypes of the columns of the object; this is usually a list of objects"
                                "of class \\code{\\link{H5T}}"
                                "@param size The size of each datatype; if \\code{NULL}, automatically inferred"
                                "@param offset The offset where each datatype starts; can be different from the sum of the individual sizes"
                                "so that datatypes are aligned with memory addresses. If \\code{NULL}, inferred automatically"
                                "@param id Internal use only"
                                if(is.null(id)) {
                                    if(missing(dtypes) || missing(labels)) {
                                        stop("Either 'id' or ('dtype_ids' and 'labels') have to be given")
                                    }
                                    dtype_ids <- H5T_extractID(dtypes)
                                    if(length(labels) != length(dtype_ids)) {
                                        stop("'labels' and 'dtype_ids' have to have the same length")
                                    }
                                    if(!is.character(labels)) {
                                        stop("'labels' has to be a character vector")
                                    }
                                    labels <- as.character(labels)
                                    id <- .Call("h5create_compound_type", labels, dtype_ids, as.integer(size), as.integer(offset), PACKAGE="hdf5r")$return_val
                                }
                                super$initialize(id)
                            },
                            pack=function() {
                                "This function implements the HDF5-API function H5Tpack."
                                "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_PACK} for details."

                                herr <- .Call("R_H5Tpack", self$id, PACKAGE="hdf5r")$return_val
                                if(herr < 0) {
                                    stop("Error removing padding")
                                }
                                return(invisible(self))
                            },
                            get_cpd_types=function() {
                                "Return \\code{\\link{H5T}} objects that represent the datatypes of the columns of the "
                                "compound object. Returned as a list if more than 1"
                                dtype_ids <- .Call("h5get_compound_types", self$id, PACKAGE="hdf5r")$return_val
                                return(H5T_factory(ids=dtype_ids))
                            },
                            get_cpd_labels=function() {
                                "Return the labels of the columns as a character vector"
                                return(.Call("h5get_compound_names", self$id, PACKAGE="hdf5r")$return_val)
                            },
                            get_cpd_classes=function() {
                                "Return the classes of the columns as an object of type \\code{\\link{factor_ext}}"
                                return(.Call("h5get_compound_classes", self$id, PACKAGE="hdf5r")$return_val)
                            },
                            get_cpd_offsets=function() {
                                "Return the offsets of the datatypes"
                                return(.Call("h5get_compound_offsets", self$id, PACKAGE="hdf5r")$return_val)
                            },
                            describe=function() {
                                "Print a detailed description of the datatype; this is experimental"

                                cpd_types <- self$get_cpd_types()
                                if(!is.list(cpd_types)) {
                                    cpd_types <- list(cpd_types)
                                }
                                cpd_describe <- lapply(cpd_types, function(x) x$describe())
                                return(list(cpd_types=cpd_describe, labels=self$get_cpd_labels(),
                                            classes=self$get_cpd_classes(), offsets=self$get_cpd_offsets(),
                                            size=self$get_size()))
                            }
                            ),
                        cloneable=FALSE
                        )

#' Class for HDF5 string datatypes.
#'
#' Inherits from class \code{\link[=H5T]{H5T}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5T_STRING]{H5T_STRING}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5T]{H5T}}
#'
#' @examples
#' # fixed width string
#' str_flen <- H5T_STRING$new(size=100)
#' str_flen$is_vlen()
#' str_flen
#' 
#' # variable length string
#' str_vlen <- H5T_STRING$new(size=Inf)
#' str_vlen$is_vlen()
#' str_vlen
H5T_STRING <- R6Class("H5T_STRING",
                      inherit=H5T,
                      public=list(
                          initialize=function(type=c("c", "fortran"), size=1, id=NULL) {
                              "Create a string datatype"
                              "@param A C or fortran type string"
                              "@param size Size of the string object. Set to \\code{Inf} for variable size strings"
                              "@param id internal use only"
                              newid <- FALSE
                              if(is.null(id)) {
                                  type <- match.arg(type)
                                  id <- switch(type, c=h5types$H5T_C_S1, fortran=h5types$H5T_FORTRAN_S1)
                                  ## need to copy it through the low level function; copy function returns an
                                  ## object; and that object closes the id; so it needs to be copied this way
                                  id <- .Call("R_H5Tcopy", id$id, PACKAGE="hdf5r")$return_val
                                  newid <- TRUE
                              }
                              super$initialize(id=id)
                              if(newid) {
                                  self$set_size(size)
                              }
                              return(self)
                          },
                          get_size=function(variable_as_inf=TRUE) {
                              "Retrieves the length of the string, setting it to \\code{Inf} it is of variable length."
                              "This function implements the HDF5-API function H5Tis_variable_str."
                              "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_IS_VARIABLE_STR} for details."

                              ## needs to be overloaded to properly assess if it is a variable length string
                              ## first check if the string has variable length
                              if(variable_as_inf) {
                                  is_var_string = .Call("R_H5Tis_variable_str", self$id, PACKAGE = "hdf5r")$return_val
                                  if(is_var_string < 0) {
                                      error("Could not determine if datatype is a variable length string")
                                  }
                                  if(is_var_string) {
                                      return(Inf)
                                  }
                                  else {
                                      return(super$get_size())
                                  }
                              }
                              else {
                                  return(super$get_size())
                              }
                          },
                          get_cset=function() {
                              "This function implements the HDF5-API function H5Tget_cset."
                              "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_CSET} for details."

                              cset_res = .Call("R_H5Tget_cset", self$id, PACKAGE = "hdf5r")$return_val
                              return(cset_res)
                          },
                          set_cset=function(cset=c("unknown", "UTF-8")) {
                              "This function implements the HDF5-API function H5Tset_cset."
                              "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_CSET} for details."

                              if(is.character(cset)) {
                                  cset <- match.arg(cset)
                                  cset <- switch(cset, unknown=h5const$H5T_CSET_ASCII, "UTF-8"=h5const$H5T_CSET_UTF8)
                              }
                              cset_res <- .Call("R_H5Tset_cset", self$id, as.integer(cset), PACKAGE = "hdf5r")$return_val
                              if(cset_res < 0) {
                                  stop("Error when trying to set cset")
                              }
                              return(self)
                          },
                          set_strpad=function(strpad) {
                              "This function implements the HDF5-API function H5Tset_strpad."
                              "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_SET_STRPAD} for details."

                              herr <- .Call("R_H5Tset_strpad", self$id, as.integer(strpad), PACKAGE = "hdf5r")$return_val
                              if(herr < 0) {
                                  stop("Could not set strpad")
                              }
                              return(invisible(self))
                          },
                          get_strpad=function() {
                              "This function implements the HDF5-API function H5Tget_strpad."
                              "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_STRPAD} for details."

                              strpad <- .Call("R_H5Tget_strpad", self$id, PACKAGE = "hdf5r")$return_val
                              return(strpad)
                              if(strpad < 0) {
                                  stop("There was an error retrieving the strpad")
                              }
                          },
                          describe=function() {
                              "Print a detailed description of the datatype; this is experimental"

                              return(list(size=self$get_size(), cset=self$get_cset(), strpad=self$get_strpad()))
                          }

                          ),
                      cloneable=FALSE
                      )



#' Class for HDF5 complex datatypes
#'
#' In HDF5, complex numbers don't actually exist. They are represented as H5T_COMPOUND with two columns named \code{Real} and
#' \code{Imaginary}.
#' Inherits from class \code{\link[=H5T_COMPOUND]{H5T_COMPOUND}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5T_COMPLEX]{H5T_COMPLEX}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5T]{H5T}}, \code{\link[=H5T_COMPOUND]{H5T_COMPOUND}}
H5T_COMPLEX <- R6Class("H5T_COMPLEX",
                       inherit=H5T_COMPOUND,
                       public=list(
                           initialize=function(id=NULL) {
                               "Create a new complex datatype"
                               "@param id Internal use only"
                               if(is.null(id)) {
                                   labels <- c("Real", "Imaginary")
                                   dtypes <- rep(h5types$H5T_NATIVE_DOUBLE$id,2)
                                   super$initialize(labels=labels, dtypes=dtypes, size=NULL, offset=NULL)
                               }
                               else {
                                   super$initialize(id=id)
                               }
                           }
                           ),
                       cloneable=FALSE
                       )


#' Class for HDF5 array datatypes.
#'
#' Inherits from class \code{\link[=H5T]{H5T}}. This class represents an array. As datasets in HDF5
#' are itself already arrays, this datatype is not needed there. It is mostly useful when a column in a
#' \code{H5T_COMPUND} object is intended to be an array. This however makes it difficult to work
#' with such objects in R - as a column of the corresponding \code{data.frame} has to be an array. So please
#' use with care.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5T_ARRAY]{H5T_ARRAY}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5T]{H5T}}
H5T_ARRAY <- R6Class("H5T_ARRAY",
                     inherit=H5T,
                     public=list(
                         initialize=function(dims, dtype_base, id=NULL) {
                             "Create an array datatype."
                             "@param dims The dimension of the datatype"
                             "@param dtype_base The datatype that makes up the elements of the array"
                             "@param id internal use only"
                             if(is.null(id)) {
                                 ## ok, check that we have the right base type available
                                 if(missing(dims) || missing(dtype_base)) {
                                     stop("When creating a new array datatype, either id has to be given (for an existing one), or dims and dtype_base")
                                 }
                                 if(inherits(dtype_base, "H5T")) {
                                     dtype_base <- dtype_base$id
                                 }
                                 rank <- length(dims)
                                 dims <- rev(dims)
                                 id <- .Call("R_H5Tarray_create2", bit64::as.integer64(dtype_base), as.integer(rank), as.integer(dims), PACKAGE = "hdf5r")$return_val
                             }
                             super$initialize(id)
                         },
                         get_array_ndims=function() {
                             "This function implements the HDF5-API function H5Tget_array_ndims."
                             "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_ARRAY_NDIMS} for details."

                             res <- .Call("R_H5Tget_array_ndims", self$id, PACKAGE="hdf5r")$return_val
                             if(res < 0) {
                                 stop("Error trying to get rank of array-type")
                             }
                             return(res)
                         },
                         get_array_dims=function() {
                             "This function implements the HDF5-API function H5Tget_array_dims2."
                             "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_ARRAY_DIMS2} for details."

                             rank <- self$get_array_ndims()
                             dims <- integer(rank)
                             res <- .Call("R_H5Tget_array_dims2", self$id, dims, PACKAGE="hdf5r")
                             if(res$return_val < 0) {
                                 stop("Error trying to get array-type dimensions")
                             }
                             return(rev(res$dims))
                         },
                         get_super=function() {
                             "This function implements the HDF5-API function H5Tget_super."
                             "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_SUPER} for details."

                             id <- .Call("R_H5Tget_super", self$id, PACKAGE="hdf5r")$return_val
                             if(id < 0) {
                                 stop("Error retrieving super_type")
                             }
                             return(H5T_factory(id=id))
                         },
                         describe=function() {
                             "Print a detailed description of the datatype; this is experimental"

                             return(list(super=self$get_super()$describe(), array_dims=self$get_array_dims()))
                         }
                         ),
                     cloneable=FALSE
                     )



#' Class for HDF5 variable-length datatypes.
#'
#' Inherits from class \code{\link[=H5T]{H5T}}. This can make any datatype a variable length datatype.
#' This would mostly be intended for storing ragged arrays. 
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5T_VLEN]{H5T_VLEN}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5T]{H5T}}
#'
#' @examples
#' vlen_int <- H5T_VLEN$new(h5types$H5T_NATIVE_INT)
#' vlen_int
H5T_VLEN <- R6Class("H5T_VLEN",
                    inherit=H5T,
                    public=list(
                        initialize=function(dtype_base, id=NULL) {
                            "Create a variable length datatype"
                            "@param dtype_base The basis-type of the variable length datatype"
                            "@param id Internal use only"
                            if(is.null(id)) {
                                if(inherits(dtype_base, "H5T")) {
                                    dtype_base <- dtype_base$id
                                }
                                id <- .Call("R_H5Tvlen_create", bit64::as.integer64(dtype_base), PACKAGE="hdf5r")$return_val
                            }
                            super$initialize(id=id)
                        },
                        get_super=function() {
                            "This function implements the HDF5-API function H5Tget_super."
                            "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5T_GET_SUPER} for details."

                            id <- .Call("R_H5Tget_super", self$id, PACKAGE="hdf5r")$return_val
                            if(id < 0) {
                                stop("Error retrieving super_type")
                            }
                            return(H5T_factory(id=id))
                        },
                        describe=function() {
                            "Print a detailed description of the datatype; this is experimental"

                            return(list(super=self$get_super()$describe()))
                        }
                        ),
                    cloneable=FALSE
                    )

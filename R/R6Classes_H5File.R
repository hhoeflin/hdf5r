
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




##' Open an HDF5 file
##'
##' Open an HDF5 file. \code{a} creates a new file or opens an existing one for read/write. \code{r} opens an
##' existing file for reading, \code{r+} opens an existing file for read/write. \code{w} creates a file, truncating any
##' existing ones and \code{w-}/\code{x} are synonyms, creating a file and failing if it already exists.
##' @title Open an HDF5 file
##' @param name The name of the file to open
##' @param mode The mode how to open the file
##' @param file_create_pl File creation property list
##' @param file_access_pl File access property list
##' @return The file id (64bit-integer)
##' @author Holger Hoefling
H5File.open <-  function(name, mode=c("a", "r", "r+", "w", "w-", "x"), file_create_pl=h5const$H5P_DEFAULT, file_access_pl=h5const$H5P_DEFAULT) {
    check_pl(file_create_pl, "H5P_FILE_CREATE")
    check_pl(file_access_pl, "H5P_FILE_ACCESS")

    stopifnot(is.character(name))
    stopifnot(length(name) == 1)

    mode <- match.arg(mode)
    mode.save <- mode

    filename <- normalizePath(name, mustWork=FALSE)

    ## now do the appropriate thing depending on the mode
    if(mode=="a") { # read/write if exists, create otherwise
        if(file.exists(filename)) {
            if(is_hdf5(name=filename)) {
                mode <- "r+"
            }
            else { # a different type of file; delete it
                mode <- "w"
            }
        }
        else {
            mode <- "w"
        }
    }
    if(mode=="w") { # create file, truncate if exists
        fid <- .Call("R_H5Fcreate", filename, h5const$H5F_ACC_TRUNC, file_create_pl$id, file_access_pl$id, PACKAGE = "hdf5r")$return_val
    }
    else if(mode=="r") { # readonly, file must exist
        fid <- .Call("R_H5Fopen", filename, h5const$H5F_ACC_RDONLY, file_access_pl$id, PACKAGE = "hdf5r")$return_val
    }
    else if(mode=="r+") { # readwrite, file must exist
        fid <- .Call("R_H5Fopen", filename, h5const$H5F_ACC_RDWR, file_access_pl$id, PACKAGE = "hdf5r")$return_val
    }
    else if(mode=="w-" || mode=="x") { # create file, fail if exists
        fid <- .Call("R_H5Fcreate", filename, h5const$H5F_ACC_EXCL, file_create_pl$id, file_access_pl$id, PACKAGE = "hdf5r")$return_val
    }
    else {
        stop("unknown mode")
    }
    if(fid < 0) {
        stop(paste("Error opening file", filename, "in mode", mode.save))
    }
    return(fid)
}

##' Check if a file is an HDF5 file
##'
##' Uses the HDF5 function \code{H5Fis_hdf5} to check if a file is of type HDF5.
##' @title Check if a file is an HDF5 file
##' @param name The name of the file to check; doesn't check for existence
##' @return Logical, TRUE if file is of type HDF5
##' @author Holger Hoefling
##' @export
is_hdf5 <- function(name) {
    res <- .Call("R_H5Fis_hdf5", name, PACKAGE = "hdf5r")
    if(res < 0) {
        stop("Error testing if file is of type hdf5")
    }
    return(as.logical(res))
}


#' Class for interacting with HDF5 files.
#'
#' This class represents an open HDF5 File-id. It inherits all functions of the
#' \code{\link{H5RefClass-class}}. #'
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link{H5File}}.
#' @export
#' @author Holger Hoefling
H5File <- R6Class("H5File",
                  inherit=H5RefClass,
                  public=list(
                      mode = NULL,
                      filename = NULL,
                      initialize=function(filename=NULL, mode=c("a", "r", "r+", "w", "w-", "x"), file_create_pl=h5const$H5P_DEFAULT,
                          file_access_pl=h5const$H5P_DEFAULT, id=NULL) {
                          "Opens or creates a new HDF5 File"
                          "@param filename Name of the file"
                          "@param mode How to open it. \\code{a} creates a new file or opens an existing one for read/write. \\code{r} opens an"
                          "existing file for reading, \\code{r+} opens an existing file for read/write. \\code{w} creates a file, truncating any"
                          "existing ones and \\code{w-}/\\code{x} are synonyms, creating a file and failing if it already exists."


                          if (is.null(id)) {
                             if (!is.null(filename)) {
                               id <- H5File.open(filename, mode, file_create_pl, file_access_pl)
                             } else {
                               stop("Either filename or id must be given to initialize H5File.")
                             }
                          }

                          super$initialize(id)
                          self$mode <- mode
                          self$filename <- self$get_filename()
                      },
                      get_obj_count=function(types=h5const$H5F_OBJ_ALL) {
                          "This function implements the HDF5-API function H5Fget_obj_count."
                          "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-GetObjCount} for details."
                          count <- .Call("R_H5Fget_obj_count", self$id, types, PACKAGE = "hdf5r")$return_val
                          if(count < 0) {
                              stop("Couldn't get object count in file")
                          }
                          return(count)
                      },
                      get_obj_ids=function(types=h5const$H5F_OBJ_ALL) {
                          "This function implements the HDF5-API function H5Fget_obj_ids."
                          "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-GetObjIds} for details."

                          count <- self$get_obj_count(types=types)
                          res <- .Call("R_H5Fget_obj_ids", self$id, types, count, request_empty(count), PACKAGE = "hdf5r")
                          if(res$return_val != count) {
                              stop("Did not receive expected number of objects")
                          }
                          obj_ids <- res$obj_id_list
                          return(obj_ids)
                      },
                      get_filesize=function() {
                          "This function implements the HDF5-API function H5Fget_filesize."
                          "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-GetFilesize} for details."

                          res <- .Call("R_H5Fget_filesize", self$id, request_empty(1), PACKAGE = "hdf5r")
                          if(res$return_val < 0) {
                              stop("Error retrieving the file size")
                          }
                          return(res$size)
                      },
                      file_info=function() {
                          "This function implements the HDF5-API function H5Fget_info2."
                          "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-GetInfo2} for details."
                          "Please note that the returned information differs if HDF5 Version 1.8.16 or HDF5 Version >= 1.10.0 is being used"

                          if(is.loaded("R_H5Fget_info2", PACKAGE = "hdf5r")) {
                              res <- .Call("R_H5Fget_info2", self$id, request_empty(1), PACKAGE = "hdf5r")
                              if(res$return_val < 0) {
                                  stop("Error getting object info")
                              }
                              return(res$finfo)
                          }
                          else {
                              res <- .Call("R_H5Fget_info", self$id, request_empty(1), PACKAGE = "hdf5r")
                              if(res$return_val < 0) {
                                  stop("Error getting object info")
                              }
                              return(res$bh_info)
                          }
                      },
                      get_intent=function() {
                          "This function implements the HDF5-API function H5Fget_intent."
                          "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-GetIntent} for details."

                          res <- .Call("R_H5Fget_intent", self$id, request_empty(1), PACKAGE="hdf5r")
                          if(res$return_val < 0) {
                              stop("Error retrieving the file size")
                          }
                          h5f_acc <- h5const$H5F_ACC
                          intent <- factor_ext(res$intent, values=values(h5f_acc), levels=levels(h5f_acc))
                          return(intent)
                      },
                      close_all=function(close_self=TRUE) {
                          "Closes the file, flushes it and also closes all open objects that are still open in it. This is the recommended way of"
                          "closing any file. If not all objects in a file are closed, the file remains open and cannot be re-opened the regular way."

                          ## first trigger the garbage collection, so that lost, but not yet collected objects are closed
                          gc()
                          obj_ids <- self$get_obj_ids()
                          ## need to flush before closing objects; the file itself is returned as an object,
                          ## so would close the file before we can flush
                          self$flush()
                          obj_ids <- obj_ids[obj_ids != self$id]
                          for(i in seq_along(obj_ids)) {
                              H5_close_any(obj_ids[i])
                              rm_obj(obj_ids[i])
                          }
                          if(close_self) {
                              H5_close_any(self$id)
                              rm_obj(self$id)
                          }
                          return(invisible(self))
                      },
                      ## close=function(all=TRUE) {
                      ##     "Closes an object and calls the appropriate HDF5 function for the type of object"
                      ##     "@param all Closes all open objects of the file"
                      ##     if(self$is_valid) {
                      ##         if(all) {
                      ##             self$close_all(close_self=TRUE)
                      ##         }
                      ##         else {
                      ##             id <- private$pid$id
                      ##             private$closeFun(id)
                      ##             decr_count(id)
                      ##         }
                      ##         private$pid <- NA
                      ##     }
                      ##     return(invisible(self))
                      ## }
                      print=function(..., max.attributes=10, max.listing=10){
                          "Prints information for the file"
                          "@param max.attributes Maximum number of attribute names to print"
                          "@param max.listing Maximum number of ls-items to print"
                          "@param ... ignored"

                          is_valid <- self$is_valid
                          
                          print_class_id(self, is_valid)

                          if(is_valid) {
                              cat("Filename: ", normalizePath(self$filename, mustWork=FALSE), "\n", sep="")
                              cat("Access type: ", as.character(self$get_intent()), "\n", sep="")
                              print_attributes(self, max_to_print=max.attributes)
                              print_listing(self, max_to_print=max.listing)
                          }
                          
                          return(invisible(self))
                      }
                      ),
                  private=list(
                      closeFun=function(id) {
                          if(!is.na(id) && is.loaded("R_H5Fclose", PACKAGE="hdf5r")) {
                              ## potential call to ensure that all objects inside a file are closed
                              ## self$close_all(close_self=FALSE)
                              invisible(.Call("R_H5Fclose", id, PACKAGE = "hdf5r"))
                          }
                      }
                      ),
                  cloneable = FALSE
                  )


R6_set_list_of_items(H5File, "public", commonFG, overwrite=TRUE)
R6_set_list_of_items(H5File, "active", commonFG_active, overwrite=TRUE)
R6_set_list_of_items(H5File, "public", commonFGT, overwrite=TRUE)
R6_set_list_of_items(H5File, "public", commonFGDT, overwrite=TRUE)
R6_set_list_of_items(H5File, "public", commonFGDTA, overwrite=TRUE)




##' Closes any HDF5 id using the appropriate library function
##'
##' Internal function to help with management of open ids. It is used to close
##' an id that is no longer needed using the appropriate HDF5 library function.
##' @title Closes any HDF5 id using the appropriate library function
##' @param id The id to closes
##' @return NULL, invisibly
##' @author Holger Hoefling
H5_close_any <- function(id) {
    if(!is.na(id)) {
        type <-  as.character(.Call("R_H5Iget_type", id, PACKAGE="hdf5r")$return_val)

        ## get the reference count, and close it as often as it is open
        ref_count <- try(.Call("R_H5Iget_ref", id, PACKAGE="hdf5r")$return_val, silent=TRUE)

        if(inherits(ref_count, "try-error")) {
            return(invisible(NULL))
        }
        for(i in seq_len(ref_count)) {
            herr <- switch(type,
                           H5I_FILE=.Call("R_H5Fclose", id, PACKAGE="hdf5r"),
                           H5I_GROUP=.Call("R_H5Gclose", id, PACKAGE="hdf5r"),
                           H5I_DATATYPE=.Call("R_H5Tclose", id, PACKAGE="hdf5r"),
                           H5I_DATASET=.Call("R_H5Dclose", id, PACKAGE="hdf5r"),
                           H5I_DATASPACE=.Call("R_H5Sclose", id, PACKAGE="hdf5r"),
                           H5I_ATTR=.Call("R_H5Aclose", id, PACKAGE="hdf5r"),
                           H5I_REFERENCE=.Call("R_H5Rclose", id, PACKAGE="hdf5r"),
                           H5I_VFL=stop("Type H5I_VFL; can't close"),
                           H5I_GENPROP_CLS=.Call("R_H5Pclose_class", id, PACKAGE="hdf5r"),
                           H5I_GENPROP_LST=.Call("R_H5Pclose", id, PACKAGE="hdf5r"),
                           stop("Unknown type; can't close"))

            if(herr < 0) {
                stop(paste("Error closing id", id, "of type", type))
            }
        }
    }
    return(invisible(NULL))
}




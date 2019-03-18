
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



##' Base class that tracks the ids and allows for closing an id
##' 
##' This class is not intended for creating objects, but as a base class for all other
##' H5-derived classes to provide common functionality for id tracking
##' @docType class
##' @importFrom R6 R6Class
##' @return Object of reference class \code{\link{H5RefClass}}. 
##' @field id Returns the id of the object as an integer
##' @export
##' @importFrom bit64 as.integer64
##' @importFrom bit64 is.na.integer64
##' @author Holger Hoefling
H5RefClass <- R6Class("H5RefClass",
                      public=list(
                          initialize=function(id=NULL) {
                              "Constructor for the basic class for hdf5 objects. Takes an id and stores it appropriately, including"
                              "the necessary counting of object references that the package implements. This reference counting is"
                              "included in addition to R's internal method in order to allow for the invalidation of objects"
                              "in R itself when all open handles in an R-file are being closed."
                              if(is.null(id)) {
                                  stop("Id has to be specified")
                              }
                              if(is.na(id)) {
                                  stop("'id' cannot be NA")
                              }
                              if(!is.numeric(id) || (as.integer64(id) != id)) {
                                  stop("'id' has to be integer or can be coerced to integer")
                              }
                              ## check the r object count as well as the hdf5 object count
                              item <- incr_count(as.integer64(id))
                              private$pid <- item$obj

                              r_count <- item$count
                              h5_count <- self$get_ref()

                              # cat("ID: ", id, " R-count: ", r_count, " h5-count: ", h5_count, "\n")
                              
                              if(r_count == h5_count + 1) {
                                  new_count <- self$inc_ref()
                                  cat("New count is ", new_count, "\n")
                              }
                              else if(r_count > h5_count + 1) {
                                  stop("r_count can never be more than 1 larger than h5_count")
                              }
                              else if(r_count < h5_count) {
                                  stop("r_count can never be less than h5_count")
                              }
                              ## only for debug; file_ids can often exist more than once
                              #if(r_count==2) {
                              #    warning("Same object exists twice")
                              #}
                              
                              reg.finalizer(self, function(e) { e$close()}, onexit=TRUE)
                          },
                          close=function() {
                              "Closes an object and calls the appropriate HDF5 function for the type of object"
                              if(self$is_valid) {
                                  id <- private$pid$id
                                  private$closeFun(id)
                                  decr_count(id)
                              }
                              private$pid <- NA
                              return(invisible(self))

                          },
 #                         erase=function() {
 #                             private$pid <- NA
 #                             private$pmessage <- "erased"
 #                         },
                          print=function(...) {
                              "Prints the class of the object and the id"

                              is_valid <- self$is_valid

                              print_class_id(self, is_valid)
                              return(invisible(self))
                          },
                          methods=function() {
                              "Prints available methods on the screen"
                              cat(format(self), sep="\n")
                          }
                          ),
                      active=list(
                          id=function() {
                              "Returns the id of the object"
                              if(is.environment(private$pid)) {
                                  if(is.na(private$pid$id)) {
                                      stop("id is invalid")
                                  }
                                  else {
                                      return(private$pid$id)
                                  }
                              }
                              else {
                                  stop("id is invalid")
                              }
                          },
                          id_env=function() {
                              return(private$pid)
                          },
                          is_valid=function() {
                              "This function implements the HDF5-API function H5Iis_valid."
                              "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5I_IS_VALID} for details."
                              "Additionally, the R-object representing the HDF5-id can be invalidated as well. In this"
                              "case, the class id is set to \\code{NA} and \\code{is_valid} returns \\code{FALSE}."
                              
                              if(!is.environment(private$pid) || is.na(private$pid$id)) {
                                  return(FALSE)
                              }
                              if(!is.loaded("R_H5Iis_valid", PACKAGE = "hdf5r")) { ## package has already been unloaded; ignore
                                  return(FALSE)
                              }
                              res <- .Call("R_H5Iis_valid", self$id, PACKAGE = "hdf5r")$return_val
                              if(res < 0) {
                                  stop(paste("Error determining validity of id", as_hex(self$id)))
                              }
                              return(res > 0)
                          },
                          message=function() {
                              "Legacy function; currently not used; may be removed"
                              return(private$pmessage)
                          }
                          ),
                      private=list(
                          pid=NA,
                          closeFun=identity,
                          pmessage=character(0),
                          stopOnInvalid=function(error.msg="The object is invalid") {
                              if(!self$is_valid) {
                                  stop(error.msg)
                              }
                          }
                          ),
                      cloneable=FALSE                      
                      )

R6_set_list_of_items(H5RefClass, "public", interface, overwrite=TRUE)





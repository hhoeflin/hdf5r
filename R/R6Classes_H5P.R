
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


##' Create an \code{\link{H5P}} out of an id
##'
##' Function that determines the property list type of an id and creates
##' the appropriate class for it.
##' @title Create an \code{\link{H5P}} out of an id
##' @param id The id to wrap inside an object
##' @return An object of class \code{\link{H5P}}
##' @author Holger Hoefling
##' @keywords internal
H5P_factory <- function(id) {
    if(inherits(id, "H5P_CLASS")) {
        cls_id <- id$id
        id <- .Call("R_H5Pcreate", cls_id, PACKAGE="hdf5r")$return_val
        if(id < 0) {
            stop("Error creating new property list")
        }
    }
    else if(id %in% h5const$H5P) {
        cls_id <- id
        id <- .Call("R_H5Pcreate", cls_id, PACKAGE="hdf5r")$return_val
        if(id < 0) {
            stop("Error creating new property list")
        }
    }
    else {
        ## we don't create a full object, so need to take care of closing it ourselves
        ## it is also temporary and not to be returned
        cls_id <- .Call("R_H5Pget_class", id, PACKAGE="hdf5r")$return_val
        on.exit(.Call("R_H5Pclose_class", cls_id, PACKAGE="hdf5r"))
    }

    h5p_equal <- function(id1, id2) {
        htri <- .Call("R_H5Pequal", id1, id2, PACKAGE="hdf5r")
        if(htri < 0) {
            stop("Error comparing the ids")
        }
        return(as.logical(htri))
    }

    if(h5p_equal(cls_id, h5const$H5P_DATASET_CREATE)) {
        obj <- H5P_DATASET_CREATE$new(id=id)
    }
    else if(h5p_equal(cls_id, h5const$H5P_DATASET_ACCESS)) {
        obj <- H5P_DATASET_ACCESS$new(id=id)
    }
    else if(h5p_equal(cls_id, h5const$H5P_DATASET_XFER)) {
        obj <- H5P_DATASET_XFER$new(id=id)
    }
    else if(h5p_equal(cls_id, h5const$H5P_LINK_CREATE)) {
        obj <- H5P_LINK_CREATE$new(id=id)
    }
    else if(h5p_equal(cls_id, h5const$H5P_LINK_ACCESS)) {
        obj <- H5P_LINK_ACCESS$new(id=id)
    }
    else if(h5p_equal(cls_id, h5const$H5P_OBJECT_CREATE)) {
        obj <- H5P_OBJECT_CREATE$new(id=id)
    }
    else if(h5p_equal(cls_id, h5const$H5P_OBJECT_COPY)) {
        obj <- H5P_OBJECT_COPY$new(id=id)
    }
    else if(h5p_equal(cls_id, h5const$H5P_ATTRIBUTE_CREATE)) {
        obj <- H5P_ATTRIBUTE_CREATE$new(id=id)
    }
    else {
        obj <- H5P$new(id=id)

    }
    return(obj)
}

#' Class for HDF5 property lists.
#'
#' This is the base class for all property lists, but most have a specialized class.
#' It inherits all functions of the
#' \code{\link{H5RefClass}}. It is also the base class for many other classes, specifically
#' \describe{
#' \item{Dataset Creation}{\code{\link{H5P_DATASET_CREATE}}}
#' \item{Dataset Access}{\code{\link{H5P_DATASET_ACCESS}}}
#' \item{Dataset Transfer}{\code{\link{H5P_DATASET_XFER}}}
#' \item{Link Creation}{\code{\link{H5P_LINK_CREATE}}}
#' \item{Link Access}{\code{\link{H5P_LINK_ACCESS}}}
#' \item{Object Creation}{\code{\link{H5P_OBJECT_CREATE}}}
#' \item{Object Copy}{\code{\link{H5P_OBJECT_COPY}}}
#' \item{Attribute Creation}{\code{\link{H5P_ATTRIBUTE_CREATE}}}
#' }
#' The base class is unlikely to be needed by users - they should use the appropriate subclass required.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link{H5P}}.
#' @author Holger Hoefling
#' @examples 
#' fname <- tempfile(fileext = ".h5")
#' file <- H5File$new(fname, mode = "a")
#' file[["testdataset"]] <- 1:10
#' p <- file[["testdataset"]]$get_create_plist()
#' p$get_class()
#' p$get_class_name()
#' p$copy()
#' p$equal(p)
#' file$close_all()
#' @export
#' @aliases H5P-class
H5P <- R6Class("H5P",
               inherit=H5RefClass,
               public=list(
                   #' @description Create a new property list; this function itself is unlikely to be needed by users. Users should use the classes of the type they actually require
                   #' @param id Internal use only
                   initialize=function(id=NULL) {
                       if(is.null(id)) {
                           stop("Can't create H5P object without id")
                       }
                       super$initialize(id)
                   },
                   #' @description This function implements the HDF5-API function H5Pget_class. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                   get_class=function() {

                       id <- .Call("R_H5Pget_class", self$id, PACKAGE="hdf5r")$return_val
                       return(H5P_CLASS$new(id=id))
                   },
                   #' @description This function implements the HDF5-API function H5Pget_class_name. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                   get_class_name=function() {

                       cls <- self$get_class()
                       cls_name <- .Call("R_H5Pget_class_name", cls$id, PACKAGE="hdf5r")$return_val
                       return(cls_name)
                   },
                   #' @description This function implements the HDF5-API function H5Pcopy. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                   copy=function() {

                       propid <- .Call("R_H5Pcopy", self$id, PACKAGE="hdf5r")$return_val
                       return(H5P_factory(id=propid))
                   },
                   #' @description This function implements the HDF5-API function H5Pequal. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                   #' @param cmp The object to compare against.
                   equal=function(cmp) {

                       if(!inherits(cmp, "H5P")) {
                           stop("cmp has to be of class H5P")
                       }
                       htri <- .Call("R_H5Pequal", self$id, cmp$id, PACKAGE="hdf5r")
                       if(htri < 0) {
                           stop("Error comparing the ids")
                       }
                       return(as.logical(htri))
                   }
                   ),
               private=list(
                   closeFun=function(id) if(!is.na(id) && is.loaded("R_H5Pclose", PACKAGE="hdf5r")) {
                          invisible(.Call("R_H5Pclose", id, PACKAGE = "hdf5r"))}
                   ),
               cloneable=FALSE
               )


#' Class for default values for HDF5 property lists.
#'
#' This class represents default values for H5P property lists. As with \code{\link{H5S_ALL}}, the current choice is not optimal
#' for the same reasons and likely to be changed
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link{H5P}}.
#' @author Holger Hoefling
#' @keywords internal
#' @aliases H5P_DEFAULT-class
H5P_DEFAULT <- R6Class("H5P_DEFAULT",
                       inherit=H5P,
                       public=list(
                           #' @description Wraps the default property list. For internal use only.
                           #' @param id An HDF5 id; for internal use only.
                           initialize=function(id=NULL) {
                               private$pid <- new_id_obj(id)
                               return(self)
                           },
                           #' @description Just prints that it is the default class
                           #' @param ... ignored
                           print=function(...) {
                               cat("H5P_DEFAULT class\n")
                               return(invisible(self))
                           }
                           ),
                       private=list(
                           closeFun=identity
                           ),
                       cloneable=FALSE
                       )


#' Class for HDF5 property list classes (not HDF5 property lists)
#'
#' It inherits all functions of the \code{\link{H5RefClass}}. The intent of this class is to
#' provide a mechanism to compare the class of HDF5 property classes. This is mainly intended for internal use
#' to get the class type of an HDF5 identifier that is known to be a property list, but not of which type.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5P_CLASS]{H5P_CLASS}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5P]{H5P}}
#' @aliases H5P_CLASS-class
H5P_CLASS <- R6Class("H5P_CLASS",
                     inherit=H5RefClass,
                     public=list(
                         #' @description This function implements the HDF5-API function H5Pequal. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                         #' @param cmp The object to compare against.
                         equal=function(cmp) {

                             if(inherits(cmp, "H5P_CLASS")) {
                                 cls_id <- cmp$id
                             }
                             else if(cmp %in% h5const$H5P) {
                                 cls_id <- cmp
                             }
                             else {
                                 stop("cmp has to be of class H5P_CLASS or a class id from h5const$H5P")
                             }
                             htri <- .Call("R_H5Pequal", self$id, cls_id, PACKAGE="hdf5r")
                             if(htri < 0) {
                                 stop("Error comparing the ids")
                             }
                             return(as.logical(htri))
                         }
                         ),
                     private=list(
                         closeFun=function(id) if(!is.na(id) && is.loaded("R_H5Pclose", PACKAGE="hdf5r")) {
                             invisible(.Call("R_H5Pclose_class", id, PACKAGE = "hdf5r"))}
                         ),
                     cloneable=FALSE)




#' Class for HDF5 property list for file creation
#'
#' It inherits all functions of the \code{\link{H5P}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5P_FILE_CREATE]{H5P_FILE_CREATE}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5P]{H5P}}
#' @aliases H5P_FILE_CREATE-class
H5P_FILE_CREATE <-  R6Class("H5P_FILE_CREATE",
                              inherit=H5P,
                              public=list(
                                  #' @description Create a new class of type \code{\link{H5P_FILE_CREATE}}
                                  #' @param id Internal use only
                                  initialize=function(id=NULL) {

                                      if(is.null(id)) {
                                          id <- .Call("R_H5Pcreate", h5const$H5P_FILE_CREATE, PACKAGE="hdf5r")$return_val
                                          if(id < 0) {
                                              stop("Error creating new property list")
                                          }
                                      }
                                      super$initialize(id)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_userblock. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param size The size of the object in bytes; use \code{Inf} for variable-length strings.
                                  set_userblock=function(size) {

                                      ## ensure that it is a power of 2 with exponen >= 9
                                      log2_size <- log2(size)
                                      if(2^round(log2_size) != size) {
                                          stop("size has to be a power of 2")
                                      }
                                      if(size != 0 && size < 512) {
                                          stop("size has to bei either 0 or a power of 2 >= 512")
                                      }
                                      herr <- .Call("R_H5Pset_userblock", self$id, size, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error on setting userblock")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_userblock. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  get_userblock=function() {

                                      res <- .Call("R_H5Pget_userblock", self$id, request_empty(1), PACKAGE="hdf5r")
                                      if(res$return_val < 0) {
                                          stop("Error retrieving user-block size")
                                      }
                                      return(res$size)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_sizes. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param sizeof_addr The size of an address in the file, in bytes.
                                  #' @param sizeof_size The size of a size in the file, in bytes.
                                  set_sizes=function(sizeof_addr, sizeof_size) {

                                      if(!sizeof_addr %in% c(0, 2, 4, 8, 16)) {
                                          stop(paste("sizeof_addr has to be one of 0, 2, 4, 8, or 16"))
                                      }
                                      if(!sizeof_size %in% c(0, 2, 4, 8, 16)) {
                                          stop(paste("sizeof_size has to be one of 0, 2, 4, 8, or 16"))
                                      }
                                      herr <- .Call("R_H5Pset_sizes", self$id, sizeof_addr, sizeof_size, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error on setting size")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_sizes. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  get_sizes=function() {

                                      res <- .Call("R_H5Pget_sizes", self$id, request_empty(1), request_empty(1), PACKAGE="hdf5r")
                                      if(res$return_val < 0) {
                                          stop("Error retrieving user-block size")
                                      }
                                      return(list(sizeof_addr=res$sizeof_addr, sizeof_size=res$sizeof_size))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_sym_k. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param ik The 1/2 rank of the indexed storage or symbol table B-tree.
                                  #' @param lk The 1/2 rank of the symbol table leaf nodes.
                                  set_sym_k=function(ik, lk) {

                                      herr <- .Call("R_H5Pset_sym_k", self$id, ik, lk, PACKAGE="hdf5r")$return_val
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_sym_k. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  get_sym_k=function() {

                                      res <- .Call("R_H5Pget_sym_k", self$id, request_empty(1), request_empty(1), PACKAGE="hdf5r")
                                      if(res$return_val < 0) {
                                          stop("Error retrieving user-block size")
                                      }
                                      return(list(ik=res$ik, lk=res$lk))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_istore_k. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param ik The 1/2 rank of the indexed storage or symbol table B-tree.
                                  set_istore_k=function(ik) {

                                      herr <- .Call("R_H5Pset_istore_k", self$id, ik, PACKAGE="hdf5r")$return_val
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_istore_k. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  get_istore_k=function() {

                                      res <- .Call("R_H5Pget_istore_k", self$id, request_empty(1), PACKAGE="hdf5r")
                                      if(res$return_val < 0) {
                                          stop("Error retrieving user-block size")
                                      }
                                      return(res$ik)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_file_space. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param strategy The file space handling strategy; one of the \code{H5F_FSPACE_STRATEGY_*} values in \code{\link{h5const}}.
                                  #' @param threshold The smallest free-space section to track.
                                  set_file_space=function(strategy, threshold) {

                                      if(compareVersion(h5version(verbose=FALSE), "1.10.0") < 0) {
                                          stop("Function only available for 1.10.0 or higher")
                                      }
                                      else {
                                          herr <- .Call("R_H5Pset_file_space", self$id, strategy, threshold, PACKAGE="hdf5r")$return_val
                                          return(invisible(self))
                                      }
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_file_space. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  get_file_space=function() {

                                      if(compareVersion(h5version(verbose=FALSE), "1.10.0") < 0) {
                                          stop("Function only available for 1.10.0 or higher")
                                      }
                                      else {
                                          res <- .Call("R_H5Pget_file_space", self$id, request_empty(1), request_empty(1), PACKAGE="hdf5r")
                                          if(res$return_val < 0) {
                                              stop("Error retrieving user-block size")
                                          }
                                          return(res)
                                          return(list(strategy=res$strategy, threshold=res$threshold))
                                      }
                                  }
                                  ),
                              cloneable=FALSE
                              )




#' Class for HDF5 property list for file creation
#'
#' It inherits all functions of the \code{\link{H5P}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5P_FILE_ACCESS]{H5P_FILE_ACCESS}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5P]{H5P}}
#' @aliases H5P_FILE_ACCESS-class
H5P_FILE_ACCESS <-  R6Class("H5P_FILE_ACCESS",
                              inherit=H5P,
                              public=list(
                                  #' @description Create a new class of type \code{\link{H5P_FILE_ACCESS}}
                                  #' @param id Internal use only
                                  initialize=function(id=NULL) {

                                      if(is.null(id)) {
                                          id <- .Call("R_H5Pcreate", h5const$H5P_FILE_ACCESS, PACKAGE="hdf5r")$return_val
                                          if(id < 0) {
                                              stop("Error creating new property list")
                                          }
                                      }
                                      super$initialize(id)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_cache. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param rdcc_nslots The number of slots in the raw data chunk cache. Use -1 for the library default.
                                  #' @param rdcc_nbytes The size of the raw data chunk cache in bytes. Use -1 for the library default.
                                  #' @param rdcc_w0 The chunk preemption policy, between 0 and 1. Use -1 for the library default.
                                  set_cache=function(rdcc_nslots=521, rdcc_nbytes=2^20, rdcc_w0=0.75) {

                                      herr <- .Call("R_H5Pset_cache", self$id, 0, rdcc_nslots, rdcc_nbytes, rdcc_w0, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error setting chunk cache")
                                      }
                                      return(self)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_cache. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  get_cache=function() {

                                      res <- .Call("R_H5Pget_cache", self$id, 0, request_empty(1), request_empty(1), request_empty(1),
                                                    PACKAGE="hdf5r")
                                      if(res$return_val < 0) {
                                          stop("Error retrieving chunk cache parameters")
                                      }
                                      return(res[c("rdcc_nslots", "rdcc_nbytes", "rdcc_w0")])
                                  }
                                  ),
                              cloneable=FALSE
                              )



#' Class for HDF5 property list for dataset creation
#'
#' It inherits all functions of the \code{\link{H5P}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5P_DATASET_CREATE]{H5P_DATASET_CREATE}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5P]{H5P}}
#' @aliases H5P_DATASET_CREATE-class
H5P_DATASET_CREATE <- R6Class("H5P_DATASET_CREATE",
                              inherit=H5P,
                              public=list(
                                  #' @description Create a new class of type \code{\link{H5P_DATASET_CREATE}}
                                  #' @param id Internal use only
                                  initialize=function(id=NULL) {

                                      if(is.null(id)) {
                                          id <- .Call("R_H5Pcreate", h5const$H5P_DATASET_CREATE, PACKAGE="hdf5r")$return_val
                                          if(id < 0) {
                                              stop("Error creating new property list")
                                          }
                                      }
                                      super$initialize(id)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_layout. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param layout The dataset layout; one of the \code{H5D_*} layout values in \code{\link{h5const}}.
                                  set_layout=function(layout=h5const$H5D_CHUNKED) {

                                      herr <- .Call("R_H5Pset_layout", self$id, layout, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error on setting layout")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_layout. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  get_layout=function() {

                                      layout <- .Call("R_H5Pget_layout", self$id, PACKAGE="hdf5r")$return_val
                                      if(layout < 0) {
                                          stop("Error getting layout")
                                      }
                                      return(layout)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_chunk. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param chunk The chunk dimensions.
                                  set_chunk=function(chunk) {

                                      herr <- .Call("R_H5Pset_chunk", self$id, length(chunk), rev(chunk), PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error on setting chunk")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_chunk. If the layout is not chunked, returns NA. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param max_ndims The maximum number of dimensions to return.
                                  get_chunk=function(max_ndims) {

                                      layout <- self$get_layout()
                                      if(as.character(layout)!="H5D_CHUNKED") {
                                          return(NA)
                                      }
                                      res <- .Call("R_H5Pget_chunk", self$id, max_ndims, request_empty(max_ndims), PACKAGE="hdf5r")
                                      if(res$return_val < 0) {
                                          stop("Error getting chunk")
                                      }
                                      return(rev(res$dim))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_deflate. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param level The compression level, between 0 and 9.
                                  set_deflate=function(level) {

                                      if(level < 0 || level > 9) {
                                          stop("Compression level has to be between 0 and 9")
                                      }
                                      herr <- .Call("R_H5Pset_deflate", self$id, level, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error on setting deflate")
                                      }
                                      return(self)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_fill_value. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param dtype The datatype to use; an object of class \code{\link{H5T}}.
                                  #' @param value The value to assign.
                                  set_fill_value=function(dtype, value) {

                                      check_class(dtype, "H5T")
                                      ## value needs to be converted to an h5 object
                                      value_h5 <- RToH5(value, dtype, 1)
                                      herr <- .Call("R_H5Pset_fill_value", self$id, dtype$id, value_h5, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error on setting fill value")
                                      }
                                      return(self)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_fill_value. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param dtype The datatype to use; an object of class \code{\link{H5T}}.
                                  get_fill_value=function(dtype) {

                                      check_class(dtype, "H5T")
                                      value_h5 <- H5ToR_Pre(dtype, 1)
                                      res <- .Call("R_H5Pget_fill_value", self$id, dtype$id, value_h5, FALSE, PACKAGE="hdf5r")
                                      if(res$return_val < 0) {
                                          stop("Error retrieving fill value")
                                      }
                                      return(H5ToR_Post(value_h5, dtype, 1))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_fill_time. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param fill_time When the fill value is written; one of the \code{H5D_FILL_TIME_*} values in \code{\link{h5const}}.
                                  set_fill_time=function(fill_time=h5const$H5D_FILL_TIME_IFSET) {

                                      herr <- .Call("R_H5Pset_fill_time", self$id, fill_time, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error on setting fill_time")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_fill_time. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  get_fill_time=function() {

                                      res <- .Call("R_H5Pget_fill_time", self$id, request_empty(1), PACKAGE="hdf5r")
                                      if(res$return_val < 0) {
                                          stop("Error getting fill_time")
                                      }
                                      return(res$fill_time)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_alloc_time. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param alloc_time When storage is allocated; one of the \code{H5D_ALLOC_TIME_*} values in \code{\link{h5const}}.
                                  set_alloc_time=function(alloc_time=h5const$H5D_ALLOC_TIME_DEFAULT) {

                                      herr <- .Call("R_H5Pset_alloc_time", self$id, alloc_time, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error on setting alloc_time")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_alloc_time. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  get_alloc_time=function() {

                                      res <- .Call("R_H5Pget_alloc_time", self$id, request_empty(1), PACKAGE="hdf5r")
                                      if(res$return_val < 0) {
                                          stop("Error getting alloc_time")
                                      }
                                      return(res$alloc_time)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_filter. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param filter The filter to use; one of the \code{H5Z_FILTER_*} values in \code{\link{h5const}}.
                                  #' @param flags Flags governing the conversion from HDF5 to R. See the \code{H5TOR_*} values in \code{\link{h5const}}.
                                  #' @param cd_values Auxiliary data passed to the filter.
                                  set_filter=function(filter=h5const$H5Z_FILTER_DEFLATE, flags=h5const$H5Z_FLAG_OPTIONAL, cd_values=integer(0)) {

                                      herr <- .Call("R_H5Pset_filter", self$id, filter, flags, length(cd_values), cd_values,
                                                    PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error setting filter")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pall_filters_avail. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  all_filters_avail=function() {

                                      htri <- .Call("R_H5Pall_filters_avail", self$id, PACKAGE="hdf5r")$return_val
                                      if(htri < 0) {
                                          stop("Error checking if all filters are available")
                                      }
                                      return(as.logical(htri))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_nfilters. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  get_nfilters=function() {

                                      nfilters <- .Call("R_H5Pget_nfilters", self$id, PACKAGE="hdf5r")$return_val
                                      if(nfilters < 0) {
                                          stop("Error retrieving number of filters")
                                      }
                                      return(nfilters)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_filter2. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param idx The index of the item to access; zero-based.
                                  get_filter=function(idx) {

                                      num_filters <- self$get_nfilters()
                                      if(idx < 0 || idx >= num_filters) {
                                          stop(paste("idx has to be >= 0 and <", num_filters))
                                      }
                                      namelen <- 60
                                      char_buf <- paste(rep(" ", namelen), collapse="")
                                      res <- .Call("R_H5Pget_filter2", self$id, idx, request_empty(1),
                                                   0, request_empty(0), namelen, char_buf, request_empty(1), PACKAGE="hdf5r")
                                      if(res$return_val < 0) {
                                          stop("Error retrieving filter")
                                      }
                                      cd_nelmts <- res$cd_nelmts
                                      res <- .Call("R_H5Pget_filter2", self$id, idx, request_empty(1),
                                                   cd_nelmts, request_empty(cd_nelmts), namelen, char_buf, request_empty(1), PACKAGE="hdf5r")
                                      ## here the return value is not a factor, need to build it ourselves
                                      if(res$return_val < 0) {
                                          stop("Error retrieving filter")
                                      }
                                      filter_id <- res$return_val
                                      res$return_val <- NULL
                                      h5z_filter <- h5const$H5Z_FILTER
                                      filter_id <- factor_ext(filter_id, values=values(h5z_filter), levels=levels(h5z_filter))
                                      res$filter <- filter_id
                                      return(res)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pmodify_filter. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param filter The filter to use; one of the \code{H5Z_FILTER_*} values in \code{\link{h5const}}.
                                  #' @param flags Flags governing the conversion from HDF5 to R. See the \code{H5TOR_*} values in \code{\link{h5const}}.
                                  #' @param cd_values Auxiliary data passed to the filter.
                                  modify_filter=function(filter=h5const$H5Z_FILTER_DEFLATE, flags=h5const$H5Z_FLAG_OPTIONAL, cd_values=integer(0)) {

                                      herr <- .Call("R_H5Pmodify_filter", self$id, filter, flags, length(cd_values), cd_values,
                                                    PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error setting filter")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Premove_filter. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param filter The filter to use; one of the \code{H5Z_FILTER_*} values in \code{\link{h5const}}.
                                  remove_filter=function(filter=h5const$H5Z_FILTER_ALL) {

                                      herr <- .Call("R_H5Premove_filter", self$id, filter, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error removing filter")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_fletcher32. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  set_fletcher32=function() {

                                      herr <- .Call("R_H5Pset_fletcher32", self$id, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error setting filter fletcher32")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_nbit. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  set_nbit=function() {

                                      herr <- .Call("R_H5Pset_nbit", self$id, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error setting filter nbit")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_scaleoffset. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param scale_type The scale-offset filter type; one of the \code{H5Z_SO_*} values in \code{\link{h5const}}.
                                  #' @param scale_factor The scale factor used by the scale-offset filter.
                                  set_scaleoffset=function(scale_type=h5const$H5Z_SO_FLOAT_DSCALE, scale_factor=0) {

                                      herr <- .Call("R_H5Pset_scaleoffset", self$id, scale_type, scale_factor, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error setting filter scaleoffset")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_shuffle. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  set_shuffle=function() {

                                      herr <- .Call("R_H5Pset_shuffle", self$id, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error setting filter shuffle")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_szip. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  set_szip=function() {

                                      herr <- .Call("R_H5Pset_szip", self$id, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error setting filter szip")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pset_external. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param filename The name of the file.
                                  #' @param offset The offset to apply; see the corresponding HDF5 function for how it is interpreted.
                                  #' @param size The size of the object in bytes; use \code{Inf} for variable-length strings.
                                  set_external=function(filename, offset, size) {

                                      herr <- .Call("R_H5Pset_external", self$id, filename, offset, size, PACKAGE="hdf5r")$return_val
                                      if(herr < 0) {
                                          stop("Error setting external file")
                                      }
                                      return(invisible(self))
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_external_count. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  get_external_count=function() {

                                      count <- .Call("R_H5Pget_external_count", self$id, PACKAGE="hdf5r")$return_val
                                      if(count < 0) {
                                          stop("Error setting external file")
                                      }
                                      return(count)
                                  },
                                  #' @description This function implements the HDF5-API function H5Pget_external. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                                  #' @param idx The index of the item to access; zero-based.
                                  get_external=function(idx) {

                                      num_external <- self$get_external_count()
                                      if(idx < 0 || idx >= num_external) {
                                          stop(paste("idx has to be >= 0 and <", num_external))
                                      }
                                      max_filename_len <- 65536
                                      filename_buf <- paste(rep(" ", max_filename_len), collapse="")
                                      res <- .Call("R_H5Pget_external", self$id, idx, max_filename_len, filename_buf, request_empty(1),
                                                   request_empty(1), PACKAGE="hdf5r")
                                      if(res$return_val < 0) {
                                          stop("Error getting external file information")
                                      }
                                      return(res[c("name", "offset", "size")])
                                  }
                                  ),
                              cloneable=FALSE
                              )



#' Class for HDF5 property list for dataset access
#'
#' It inherits all functions of the \code{\link{H5P}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5P_DATASET_ACCESS]{H5P_DATASET_ACCESS}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5P]{H5P}}
#' @aliases H5P_DATASET_ACCESS-class
H5P_DATASET_ACCESS <- R6Class("H5P_DATASET_ACCESS",
                           inherit=H5P,
                           public=list(
                               #' @description Creates a new dataset access property list.
                               #' @param id An HDF5 id; for internal use only.
                               initialize=function(id=NULL) {
                                   if(is.null(id)) {
                                       id <- .Call("R_H5Pcreate", h5const$H5P_DATASET_ACCESS, PACKAGE="hdf5r")$return_val
                                       if(id < 0) {
                                           stop("Error creating new property list")
                                       }
                                   }
                                   super$initialize(id)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_chunk_cache. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param rdcc_nslots The number of slots in the raw data chunk cache. Use -1 for the library default.
                               #' @param rdcc_nbytes The size of the raw data chunk cache in bytes. Use -1 for the library default.
                               #' @param rdcc_w0 The chunk preemption policy, between 0 and 1. Use -1 for the library default.
                               set_chunk_cache=function(rdcc_nslots=-1, rdcc_nbytes=-1, rdcc_w0=-1) {

                                   herr <- .Call("R_H5Pset_chunk_cache", self$id, rdcc_nslots, rdcc_nbytes, rdcc_w0, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting chunk cache")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_chunk_cache. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_chunk_cache=function() {

                                   res <- .Call("R_H5Pget_chunk_cache", self$id, request_empty(1), request_empty(1),
                                                request_empty(1), PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error retrieving chunk cache information")
                                   }
                                   res$return_val <- NULL
                                   return(res)
                               }
                               ),
                           cloneable=FALSE
                           )

#' Class for HDF5 property list for dataset transfer
#'
#' It inherits all functions of the \code{\link{H5P}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5P_DATASET_XFER]{H5P_DATASET_XFER}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5P]{H5P}}
#' @aliases H5P_DATASET_XFER-class
H5P_DATASET_XFER <- R6Class("H5P_DATASET_XFER",
                           inherit=H5P,
                           public=list(
                               #' @description Create a new class of type \code{\link{H5P_DATASET_XFER}}
                               #' @param id Internal use only
                               initialize=function(id=NULL) {

                                   if(is.null(id)) {
                                       id <- .Call("R_H5Pcreate", h5const$H5P_DATASET_XFER, PACKAGE="hdf5r")$return_val
                                       if(id < 0) {
                                           stop("Error creating new property list")
                                          }
                                   }
                                   super$initialize(id)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_buffer. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param size The size of the object in bytes; use \code{Inf} for variable-length strings.
                               set_buffer=function(size=2^20) {

                                   tconv <- raw(0)
                                   bkg <- raw(0)
                                   herr <- .Call("R_H5Pset_buffer", self$id, size, tconv, bkg, FALSE, FALSE, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting buffer for type conversion and background")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pset_edc_check. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param check Logical; should the arguments be checked for validity.
                               set_edc_check=function(check=h5const$H5Z_ENABLE_EDC) {

                                   herr <- .Call("R_H5Pset_edc_check", self$id, check, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting edc check")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_edc_check. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_edc_check=function() {

                                   check <- .Call("R_H5Pget_edc_check", self$id, PACKAGE="hdf5r")$return_val
                                   if(check < 0) {
                                       stop("Error getting edc check")
                                   }
                                   return(check)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_hyper_vector_size. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param size The size of the object in bytes; use \code{Inf} for variable-length strings.
                               set_hyper_vector_size=function(size=2^10) {

                                   herr <- .Call("R_H5Pset_hyper_vector_size", self$id, size, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting edc check")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_hyper_vector_size. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_hyper_vector_size=function() {

                                   res <- .Call("R_H5Pget_hyper_vector_size", self$id, request_empty(1), PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting hyper vector size")
                                   }
                                   return(res$size)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_btree_ratios. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param left The B-tree split ratio for the left-most node.
                               #' @param middle The B-tree split ratio for interior nodes.
                               #' @param right The B-tree split ratio for the right-most node.
                               set_btree_ratios=function(left, middle, right) {

                                   herr <- .Call("R_H5Pset_btree_ratios", self$id, left, middle, right, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting btree ratios")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_btree_ratios. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_btree_ratios=function() {

                                   res <- .Call("R_H5Pget_btree_ratios", self$id, request_empty(1), request_empty(1),
                                                request_empty(1), PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting hyper vector size")
                                   }
                                   return(list(left=res$left, middle=res$middle, right=res$right))
                               }
                               ),
                           cloneable=FALSE
                           )




#' Class for HDF5 property list for link creation
#'
#' It inherits all functions of the \code{\link{H5P}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5P_LINK_CREATE]{H5P_LINK_CREATE}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5P]{H5P}}
#' @aliases H5P_LINK_CREATE-class
H5P_LINK_CREATE <- R6Class("H5P_LINK_CREATE",
                           inherit=H5P,
                           public=list(
                               #' @description Create a new class of type \code{\link{H5P_LINK_CREATE}}
                               #' @param id Internal use only
                               initialize=function(id=NULL) {

                                   if(is.null(id)) {
                                       id <- .Call("R_H5Pcreate", h5const$H5P_LINK_CREATE, PACKAGE="hdf5r")$return_val
                                       if(id < 0) {
                                           stop("Error creating new property list")
                                          }
                                   }
                                   super$initialize(id)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_char_encoding. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param encoding The character encoding to use; one of the \code{H5T_CSET_*} values in \code{\link{h5const}}.
                               set_char_encoding=function(encoding=h5const$H5T_CSET_UTF8) {

                                   herr <- .Call("R_H5Pset_char_encoding", self$id, encoding, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting char encoding")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_char_encoding. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_char_encoding=function() {

                                   res <- .Call("R_H5Pget_char_encoding", self$id, request_empty(1), PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting encoding")
                                   }
                                   return(res$encoding)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_create_intermediate_group. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param create Logical; should missing intermediate groups be created.
                               set_create_intermediate_group=function(create=TRUE) {

                                   herr <- .Call("R_H5Pset_create_intermediate_group", self$id, create, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting flag for creating intermediate groups")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_create_intermediate_group. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_create_intermediate_group=function() {

                                   res <- .Call("R_H5Pget_create_intermediate_group", self$id, request_empty(1), PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting intermediate group creation flag")
                                   }
                                   return(as.logical(res$crt_intmd))
                               }
                               ),
                           cloneable=FALSE
                           )


#' Class for HDF5 property list for link access
#'
#' It inherits all functions of the \code{\link{H5P}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5P_LINK_ACCESS]{H5P_LINK_ACCESS}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5P]{H5P}}
#' @aliases H5P_LINK_ACCESS-class
H5P_LINK_ACCESS <- R6Class("H5P_LINK_ACCESS",
                           inherit=H5P,
                           public=list(
                               #' @description Create a new class of type \code{\link{H5P_LINK_ACCESS}}
                               #' @param id Internal use only
                               initialize=function(id=NULL) {

                                   if(is.null(id)) {
                                       id <- .Call("R_H5Pcreate", h5const$H5P_LINK_ACCESS, PACKAGE="hdf5r")$return_val
                                       if(id < 0) {
                                           stop("Error creating new property list")
                                          }
                                   }
                                   super$initialize(id)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_nlinks. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param nlinks The maximum number of soft or external links to traverse.
                               set_nlinks=function(nlinks) {

                                   herr <- .Call("R_H5Pset_nlinks", self$id, nlinks, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting nlinks")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_nlinks. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_nlinks=function() {

                                   res <- .Call("R_H5Pget_nlinks", self$id, request_empty(1), PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting nlinks")
                                   }
                                   return(res$nlinks)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_elink_prefix. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param elink_prefix The prefix to prepend to external link file names.
                               set_elink_prefix=function(elink_prefix) {

                                   herr <- .Call("R_H5Pset_elink_prefix", self$id, elink_prefix, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting elink_prefix")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_elink_prefix. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_elink_prefix=function() {

                                   prefix_size <- .Call("R_H5Pget_elink_prefix", self$id, character(0), 0, PACKAGE="hdf5r")$return_val
                                   if(prefix_size < 0) {
                                       stop("Error getting prefix size")
                                   }
                                   char_buf <- paste(rep(" ", prefix_size+1), collapse="")
                                   res <- .Call("R_H5Pget_elink_prefix", self$id, char_buf, prefix_size+1, PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting elink_prefix")
                                   }
                                   return(res$prefix)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_elink_acc_flags. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param elink_acc_flags The file access flags to use when opening external link targets.
                               set_elink_acc_flags=function(elink_acc_flags=h5const$H5F_ACC_RDWR) {

                                   herr <- .Call("R_H5Pset_elink_acc_flags", self$id, elink_acc_flags, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting elink_acc_flags")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_elink_acc_flags. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_elink_acc_flags=function() {

                                   res <- .Call("R_H5Pget_elink_acc_flags", self$id, request_empty(1), PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting elink_acc_flags")
                                   }
                                   out <- res$flags
                                   out <- factor_ext(out, values=values(h5const$H5F_ACC), levels=levels(h5const$H5F_ACC))
                                   return(out)
                               }

                               ),
                           cloneable=FALSE
                           )


#' Class for HDF5 property list for object creation
#'
#' It inherits all functions of the \code{\link{H5P}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5P_OBJECT_CREATE]{H5P_OBJECT_CREATE}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5P]{H5P}}
#' @aliases H5P_OBJECT_CREATE-class
H5P_OBJECT_CREATE <- R6Class("H5P_OBJECT_CREATE",
                           inherit=H5P,
                           public=list(
                               #' @description Create a new class of type \code{\link{H5P_OBJECT_CREATE}}
                               #' @param id Internal use only
                               initialize=function(id=NULL) {

                                   if(is.null(id)) {
                                       id <- .Call("R_H5Pcreate", h5const$H5P_OBJECT_CREATE, PACKAGE="hdf5r")$return_val
                                       if(id < 0) {
                                           stop("Error creating new property list")
                                          }
                                   }
                                   super$initialize(id)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_obj_track_times. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param track_times Logical; should object times be recorded in the file.
                               set_obj_track_times=function(track_times=TRUE) {

                                   herr <- .Call("R_H5Pset_obj_track_times", self$id, track_times, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting track_times")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_obj_track_times. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_obj_track_times=function() {

                                   res <- .Call("R_H5Pget_obj_track_times", self$id, request_empty(1), PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting track_times")
                                   }
                                   return(as.logical(res$track_times))
                               },
                               #' @description This function implements the HDF5-API function H5Pset_attr_phase_change. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param max_compact The maximum number of links to store compactly in a group.
                               #' @param min_dense The minimum number of links before a group switches to dense storage.
                               set_attr_phase_change=function(max_compact, min_dense) {

                                   herr <- .Call("R_H5Pset_attr_phase_change", self$id, max_compact, min_dense, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting attribute phase change")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_attr_phase_change. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_attr_phase_change=function() {

                                   res <- .Call("R_H5Pget_attr_phase_change", self$id, request_empty(1), request_empty(1),PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting attribute phase change")
                                   }
                                   return(list(max_compact=res$max_compact, min_dense=res$min_dense))
                               },
                               #' @description This function implements the HDF5-API function H5Pset_attr_creation_order. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param crt_order_flags Flags governing whether link creation order is tracked and indexed.
                               set_attr_creation_order=function(crt_order_flags=0) {

                                   herr <- .Call("R_H5Pset_attr_creation_order", self$id, crt_order_flags, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting attribute creation order")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_attr_creation_order. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_attr_creation_order=function() {

                                   res <- .Call("R_H5Pget_attr_creation_order", self$id, request_empty(1), PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting attribute creation order")
                                   }
                                   out <- res$crt_order_flag
                                   return(out)
                               }
                               ),
                           cloneable=FALSE
                           )


#' Class for HDF5 property list for object copying
#'
#' It inherits all functions of the \code{\link{H5P}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5P_OBJECT_COPY]{H5P_OBJECT_COPY}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5P]{H5P}}
#' @aliases H5P_OBJECT_COPY-class
H5P_OBJECT_COPY <- R6Class("H5P_OBJECT_COPY",
                           inherit=H5P,
                           public=list(
                               #' @description Create a new class of type \code{\link{H5P_OBJECT_COPY}}
                               #' @param id Internal use only
                               initialize=function(id=NULL) {

                                   if(is.null(id)) {
                                       id <- .Call("R_H5Pcreate", h5const$H5P_OBJECT_COPY, PACKAGE="hdf5r")$return_val
                                       if(id < 0) {
                                           stop("Error creating new property list")
                                          }
                                   }
                                   super$initialize(id)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_copy_object. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param copy_options Flags governing how the object is copied.
                               set_copy_obj=function(copy_options=0) {

                                   herr <- .Call("R_H5Pset_copy_object", self$id, copy_options, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting attribute creation order")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_copy_object. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_copy_obj=function() {

                                   res <- .Call("R_H5Pget_copy_object", self$id, request_empty(1), PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting attribute creation order")
                                   }
                                   out <- res$crt_intmd
                                   return(out)
                               }
                               ),
                           cloneable=FALSE)



#' Class for HDF5 property list for attribute creation
#'
#' It inherits all functions of the \code{\link{H5P}}.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5P_ATTRIBUTE_CREATE]{H5P_ATTRIBUTE_CREATE}}.
#' @export
#' @author Holger Hoefling
#' @seealso \code{\link[=H5P]{H5P}}
#' @aliases H5P_ATTRIBUTE_CREATE-class
H5P_ATTRIBUTE_CREATE <- R6Class("H5P_ATTRIBUTE_CREATE",
                           inherit=H5P,
                           public=list(
                               #' @description Create a new class of type \code{\link{H5P_ATTRIBUTE_CREATE}}
                               #' @param id Internal use only
                               initialize=function(id=NULL) {

                                   if(is.null(id)) {
                                       id <- .Call("R_H5Pcreate", h5const$H5P_ATTRIBUTE_CREATE, PACKAGE="hdf5r")$return_val
                                       if(id < 0) {
                                           stop("Error creating new property list")
                                          }
                                   }
                                   super$initialize(id)
                               },
                               #' @description This function implements the HDF5-API function H5Pset_char_encoding. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               #' @param encoding The character encoding to use; one of the \code{H5T_CSET_*} values in \code{\link{h5const}}.
                               set_char_encoding=function(encoding=h5const$H5T_CSET_UTF8) {

                                   herr <- .Call("R_H5Pset_char_encoding", self$id, encoding, PACKAGE="hdf5r")$return_val
                                   if(herr < 0) {
                                       stop("Error setting char encoding")
                                   }
                                   return(invisible(self))
                               },
                               #' @description This function implements the HDF5-API function H5Pget_char_encoding. Please see the documentation at \url{https://support.hdfgroup.org/documentation/hdf5/latest/group___h5_p.html} for details.
                               get_char_encoding=function() {

                                   res <- .Call("R_H5Pget_char_encoding", self$id, request_empty(1), PACKAGE="hdf5r")
                                   if(res$return_val < 0) {
                                       stop("Error getting encoding")
                                   }
                                   return(res$encoding)
                               }
                               ),
                           cloneable=FALSE
                           )

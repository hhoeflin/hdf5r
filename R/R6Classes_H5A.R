
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





##' Class for representing HDF5 attributes
##' 
##' This class represents an HDF5 attribute. Usually it is easier to read and write attributes for
##' groups, datasets and committed datatypes using the functions documented in \code{\link{h5attributes}}.
##'
##' Otherwise, the functionality for attributes is very similar to that of datasets (\code{\link{H5D}}),
##' however with the notable exception that attributes always have to be read and written as a whole.
##'
##' @docType class
##' @importFrom R6 R6Class
##' @return Object of class \code{\link{H5A}}. 
##' @author Holger Hoefling
##' @examples 
##' fname <- tempfile(fileext = ".h5")
##' file <- H5File$new(fname, mode = "a")
##' h5attr(file, "attr_numeric") <- rnorm(10)
##' a <- file$attr_open("attr_numeric")
##' a$get_info()
##' a$attr_name()
##' a$get_space()
##' a$get_type()
##' a$get_storage_size()
##' a$read()
##' a$write(10:1)
##' a$print()
##' a$close()
##' file$close_all()
##' @export
H5A <- R6Class("H5A",
               inherit=H5RefClass,
               public=list(
                   get_info=function() {
                       "This function implements the HDF5-API function H5Aget_info."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5A_GET_INFO} for details."

                       res <- .Call("R_H5Aget_info", self$id, request_empty(1), PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error retrieving attribute info")
                       }
                       return(res$ainfo)
                   },
                   attr_name=function() {
                       "This function implements the HDF5-API function H5Aget_name."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5A_GET_NAME} for details."

                       ## get size of the name
                       name_size <- .Call("R_H5Aget_name", self$id, 0, character(0), PACKAGE="hdf5r")$return_val
                       if(name_size < 0) {
                           stop("Error returning name of object")
                       }
                       if(name_size == 0) {
                           return(NA)
                       }
                       ## create a character vector of sufficient size (it will be copied in the internal C function as is available for writign
                       char_buf=paste(rep(" ", name_size+1), collapse="")
                       res <- .Call("R_H5Aget_name", self$id, name_size + 1, char_buf, PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error returning name of object")
                       }
                       return(res$buf)
                   },
                   get_space=function() {
                       "This function implements the HDF5-API function H5Aget_space."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5A_GET_SPACE} for details."

                       id <- .Call("R_H5Aget_space", self$id, PACKAGE="hdf5r")$return_val
                       if(id < 0) {
                           stop("Error retrieving attribute type")
                       }
                       return(H5S$new(id=id))
                   },
                   get_type=function(native=TRUE) {
                       "This function implements the HDF5-API function H5Aget_type."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5A_GET_TYPE} for details."

                       id <- .Call("R_H5Aget_type", self$id, PACKAGE="hdf5r")$return_val
                       if(id < 0) {
                           stop("Error retrieving attribute type")
                       }
                       if(native) {
                           on.exit(.Call("R_H5Tclose", id, PACKAGE="hdf5r"))
                           ## return the native type
                           id_native <- .Call("R_H5Tget_native_type", id, h5const$H5T_DIR_ASCEND, PACKAGE="hdf5r")$return_val
                           if(id_native < 0) {
                               stop("Error retrieving native-c-type")
                           }
                           return(H5T_factory(id_native))
                       }
                       else {
                           return(H5T_factory(id))
                       }
                   },
                   get_storage_size=function() {
                       "This function implements the HDF5-API function H5Aget_storage_size."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5A_GET_STORAGE_SIZE} for details."

                       size <- .Call("R_H5Aget_storage_size", self$id, PACKAGE="hdf5r")$return_val
                       return(size)
                   },
                   read_low_level=function(buffer, mem_type, duplicate_buffer=FALSE) {
                       "Only for advanced users. See documentation for \\code{read} instead."
                       "This function implements the HDF5-API function H5Aread."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5A_READ} for details."

                       check_class(mem_type, "H5T")
                       res <- .Call("R_H5Aread", self$id, mem_type$id, buffer, duplicate_buffer, PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error reading dataset")
                       }
                       return(res$buffer)
                   },
                   read=function(flags=getOption("hdf5r.h5tor_default"), drop=TRUE) {
                       "Reads the data of the attribute and returns it as an R-object"
                       "@param flags Conversion rules for integer values. See also \\code{\\link{h5const}}"
                       "@param drop Logical. Should dimensions of length 1 be dropped (R-default for arrays)"
                       mem_type <- self$get_type()

                       check_class(mem_type, "H5T")
                       ## get the actual file-space and ascertain its size
                       attr_space <- self$get_space()
                       attr_space_type <- as.character(attr_space$get_simple_extent_type())
                           if(attr_space_type == "H5S_NULL"  ) {
                               nelem <- 0
                           }
                           else if(attr_space_type=="H5S_SCALAR") {
                               nelem <- 1
                           }
                           else {
                               nelem <- attr_space$get_select_npoints()
                           }
                       ## need to create the buffer to write this into
                       buffer <- H5ToR_Pre(mem_type, nelem)
                       
                       res <- .Call("R_H5Aread", self$id, mem_type$id, buffer, FALSE, PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error reading dataset")
                       }
                       buffer_post <- H5ToR_Post(res$buf, mem_type, nelem, flags, self$id)
                       ## reclaim vlen data; always do this, to make sure
                       ## there is no native reclaim function for attributes; use the H5D function for now
                       if(mem_type$is_vlen()) {
                           herr <- .Call("R_H5Dvlen_reclaim", mem_type$id, attr_space$id, h5const$H5P_DEFAULT$id, res$buf, FALSE,
                                         PACKAGE="hdf5r")$return_val
                           if(herr < 0 ) {
                               stop("Error trying to reclaim buffer vlen data")
                           }
                       }

                       ## apply the right dimension, if it is available
                       dim_to_set <- extract_dim(space=attr_space, dtype=mem_type)
                       if(drop) {
                           dim_to_set <- dim_to_set[dim_to_set != 1]
                       }
                           

                       if(length(dim_to_set) > 1) {
                           .Call("set_dim_attribute", buffer_post, as.numeric(dim_to_set), PACKAGE = "hdf5r")
                       }
                       return(buffer_post)
                   },
                   write_low_level=function(buffer, mem_type) {
                       "Only for advanced users. See documentation for \\code{write} instead."
                       "This function implements the HDF5-API function H5Awrite."
                       "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5A_WRITE} for details."

                       check_class(mem_type, "H5T")
                       res <- .Call("R_H5Awrite", self$id, mem_type$id, buffer, PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error reading dataset")
                       }
                       return(invisible(self))
                   },
                   write=function(robj, mem_type=NULL, flush=getOption("hdf5r.flush_on_write")) {
                       "Writes the data of \\code{robj} to the attribute"
                       "@param robj The object to write into the attribute"
                       "@param mem_type The memory data type to use when transferring from HDF5 to intermediate storage. This is an "
                       "advanced development feature and may be removed in the future."
                       if(is.null(mem_type)) {
                           mem_type <- self$get_type()
                       }

                       ## get the actual file-space and ascertain its size
                       attr_space <- self$get_space()
                       attr_space_type <- as.character(attr_space$get_simple_extent_type())
                       if(attr_space_type == "H5S_NULL"  ) {
                           nelem_file <- 0
                       }
                       else if(attr_space_type=="H5S_SCALAR") {
                           nelem_file <- 1
                       }
                       else {
                           nelem_file <- attr_space$get_select_npoints()
                       }
                       
                       nelem_robj <- guess_nelem(robj, mem_type)

                       if(nelem_robj != nelem_file) {
                           stop("Number of objects in robj does not match number of elements selected in file")
                       }
                       
                       buffer <- RToH5(robj, mem_type, nelem_robj)
                       res <- .Call("R_H5Awrite", self$id, mem_type$id, buffer, PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error writing dataset")
                       }
                       if(flush) {
                           self$flush()
                       }
                       return(invisible(self))
                   },
                   print=function(...){
                       "Prints information for the dataset"
                       "@param ... ignored"

                       is_valid <- self$is_valid
                       
                       print_class_id(self, is_valid)
                       
                       if(is_valid) {
                           ## get information about the file
                           ## get the dataset name
                           cat("Attribute: ", self$attr_name(), "\n", sep="")
                           this_dtype <- self$get_type()
                           type_text <- this_dtype$to_text()
                           cat("Datatype: ", type_text, "\n", sep="")
                           this_dtype$close()
                           ## get the dataspace
                           this_space <- self$get_space()
                           if(!this_space$is_simple()) {
                               ## has to be a NULL space
                               cat("Space: Type=NULL\n")
                           }
                           else {
                               extent_res <- this_space$get_simple_extent_dims()
                               if(extent_res$rank == 0) {
                                   cat("Space: Type=Scalar\n")
                               }
                               else {
                                   cat("Space: Type=Simple     ")
                                   cat("Dims=", paste(extent_res$dims, collapse=" x "), "     ", sep="")
                                   cat("Maxdims=", paste(extent_res$maxdims, collapse=" x "), "\n", sep="")
                               }
                           }
                           this_space$close()
                       }
                   }
                   ),
               private=list(
                   closeFun=function(id) if(!is.na(id) && is.loaded("R_H5Aclose", PACKAGE="hdf5r")) {
                       invisible(.Call("R_H5Aclose", id, PACKAGE = "hdf5r"))}
                   ),
               cloneable=FALSE
               )

R6_set_list_of_items(H5A, "public", commonFGDTA, overwrite=TRUE)

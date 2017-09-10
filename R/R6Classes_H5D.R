

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



setOldClass("H5R")


##' Class for representing HDF5 datasets
##'
##' This class represents an HDF5 group-id. It inherits all functions of the
##' \code{\link{H5RefClass-class}}.
##'
##' @docType class
##' @importFrom R6 R6Class
##' @return Object of class \code{\link{H5D}}.
##' @export
##' @author Holger Hoefling
##' @seealso H5Class_overview
H5D <- R6Class("H5D",
               inherit=H5RefClass,
               public=list(
                   initialize=function(id=NULL) {
                       "Intializes a new dataset-object. Only for internal use. Use the \\code{create_dataset} function for \\code{\\link{H5Group}}"
                       "and \\code{\\link{H5File}} objects"
                       "@param id For internal use only"
                       if(is.null(id)) {
                           stop("An id has to be provided for a dataset of class H5D. For creating a dataset, use 'create_dataset' for an H5File or H5Group")
                       }
                       super$initialize(id=id)
                   },
                   get_space=function() {
                       "This function implements the HDF5-API function H5Dget_space."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-GetSpace} for details."

                       id <- .Call("R_H5Dget_space", self$id, PACKAGE="hdf5r")$return_val
                       if(id < 0) {
                           stop("Error retrieving dataspace")
                       }
                       return(H5S$new(id=id))
                   },
                   get_space_status=function() {
                       "This function implements the HDF5-API function H5Dget_space_status."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-GetSpaceStatus} for details."

                       res <- .Call("R_H5Dget_space_status", self$id, request_empty(1), PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error retrieving space status")
                       }
                       return(res$allocation)
                   },
                   get_type=function(native=TRUE) {
                       "This function implements the HDF5-API function H5Dget_type."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-GetType} for details."

                       id <- standalone_H5D_get_type(h5d_id=self$id, native=native) 
                       return(H5T_factory(id))
                   },
                   get_create_plist=function() {
                       "This function implements the HDF5-API function H5Dget_create_plist."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-GetCreatePlist} for details."

                       id <- .Call("R_H5Dget_create_plist", self$id, PACKAGE="hdf5r")$return_val
                       if(id < 0) {
                           stop("Error retrieving dataset creation property list")
                       }
                       return(H5P_DATASET_CREATE$new(id=id))
                   },
                   get_access_plist=function() {
                       "This function implements the HDF5-API function H5Dget_access_plist."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-GetAccessPlist} for details."

                       id <- .Call("R_H5Dget_access_plist", self$id, PACKAGE="hdf5r")$return_val
                       if(id < 0) {
                           stop("Error retrieving dataset access property list")
                       }
                       return(H5P_DATASET_ACCESS$new(id=id))
                   },
                   get_offset=function() {
                       "This function implements the HDF5-API function H5Dget_offset."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-GetOffset} for details."

                       haddr <- .Call("R_H5Dget_offset", self$id, PACKAGE="hdf5r")$return_val
                       if(haddr < 0) {
                           stop("Error retrieving address; is undefined")
                       }
                       return(haddr)
                   },
                   get_storage_size=function() {
                       "This function implements the HDF5-API function H5Dget_storage_size."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-GetStorageSize} for details."

                       size <- .Call("R_H5Dget_storage_size", self$id, PACKAGE="hdf5r")$return_val
                       return(size)
                   },
                   vlen_get_buf_size=function(type, space) {
                       "This function implements the HDF5-API function H5Dvlen_get_buf_size."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-VlenGetBufSize} for details."

                       check_class(type, "H5T")
                       check_class(space, "H5S")

                       res <- .Call("R_H5Dvlen_get_buf_size", self$id, type$id, space$id, request_empty(1), PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error trying to calculate vlen buffer size")
                       }
                       return(res$size)
                   },
                   vlen_reclaim=function(buffer, type, space, dataset_xfer_pl=h5const$H5P_DEFAULT) {
                       "This function implements the HDF5-API function H5Dvlen_reclaim."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-VlenReclaim} for details."

                       check_class(type, "H5T")
                       check_class(space, "H5S")

                       check_pl(dataset_xfer_pl, "H5P_DATASET_XFER")
                       herr <- .Call("R_H5Dvlen_reclaim", type$id, space$id, dataset_xfer_pl$id, buffer, FALSE, PACKAGE="hdf5r")$return_val
                       if(herr < 0 ) {
                           stop("Error trying to reclaim buffer vlen data")
                       }
                       return(invisible(self))
                   },
                   read_low_level=function(file_space=h5const$H5S_ALL, mem_space=NULL, mem_type=NULL,
                       dataset_xfer_pl=h5const$H5P_DEFAULT, flags=getOption("hdf5r.h5tor_default"), set_dim=FALSE, dim_to_set=NULL, drop=TRUE) {
                       "This function is for advanced users. It is recommended to use \\code{read} instead or the \\code{[} interface."
                       "This function implements the HDF5-API function H5Dread, with minor changes to the API to accomodate R."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Read} for details."
                       "It reads the data in the dataset as specified by \\code{mem_space} and return it as an R-obj"
                       "@param file_space An HDF5-space, represented as class \\code{\\link{H5S-class}} that determines which part"
                       "of the dataset is being read. Can also be given as an id"
                       "@param mem_space The space as it is represented in memory; advanced feature; may be removed in the future."
                       "Can also be given as an id."
                       "@param mem_type Memory type; extracted from the dataset if null (can be passed in for efficiency reasons"
                       "Can also be given as an id."
                       "@param dataset_xfer_pl Dataset transfer property list. See \\code{\\link{H5P_DATASET_XFER-class}}"
                       "@param flags Conversion rules for integer values. See also \\code{\\link{h5const}}"
                       "@param set_dim If \\code{TRUE}, the dimension attribute is set in the return value. How it is set "
                       "is determined by \\code{dim_to_set}."
                       "@param dim_to_set The dimension to set; Has to be numeric and needs to be specified if \\code{set_dim} is \\code{TRUE}."
                       "If the result is a data.frame, i.e. the data-type is a compound, then the dimension is ignored as the"
                       "correct dimension is already set."
                       "@param drop Logical. Should dimensions of length 1 be dropped (R-default for arrays)"

                       ## first ensure that file_space of the correct types and extract the id
                       if(!inherits(file_space, "H5S") && !(is.integer64(file_space) && length(file_space) == 1)) {
                           stop("file_space has to be an id or of type H5T")
                       }
                       file_space_id <- get_id(file_space)
                       
                       if(file_space_id==h5const$H5S_ALL$id) {
                           ## get the actual file-space and ascertain its size
                           file_space_id <- .Call("R_H5Dget_space", self$id, PACKAGE="hdf5r")$return_val
                           on.exit(.Call("R_H5Sclose", file_space_id, PACKAGE = "hdf5r"), add=TRUE)
                           .Call("R_H5Sselect_all", file_space_id, PACKAGE = "hdf5r")

                           nelem <- .Call("R_H5Sget_select_npoints", file_space_id, PACKAGE = "hdf5r")$return_val
                           ## in this case, we ignore what mem_space is set to
                           mem_space_id <- h5const$H5S_ALL$id
                       }
                       else {
                            ## else, just get a linear space
                           nelem <- .Call("R_H5Sget_select_npoints", file_space_id, PACKAGE = "hdf5r")$return_val

                           if(is.null(mem_space)) {
                               ## use this simple space; this may come with some speed penalties
                               ## arguements are rank, dims, maxdims
                               mem_space_id <- as.integer64(.Call("R_H5Screate_simple", 1, nelem, nelem, PACKAGE="hdf5r")$return_val)
                               if(mem_space_id < 0) {
                                   stop("Error creating simple dataspace")
                               }
                               on.exit(.Call("R_H5Sclose", mem_space_id, PACKAGE = "hdf5r"), add=TRUE)

                           }
                           else {
                               if(!inherits(mem_space, "H5S") && !(is.integer64(mem_space) && length(mem_space) == 1)) {
                                   stop("mem_space has to be an id or of type H5T")
                               }
                               ## extract the id that was given
                               mem_space_id <- get_id(mem_space)
                           }
                       }
                       ## ok, now the file_space_id and the mem_space_id are set

                       if(is.null(mem_type)) {
                           mem_type_id <- standalone_H5D_get_type(h5d_id=self$id, native=TRUE)
                           on.exit(.Call("R_H5Tclose", mem_type_id, PACKAGE = "hdf5r"), add=TRUE)
                       }
                       else {
                           if(!inherits(mem_type, "H5T") && !(is.integer64(mem_type) && length(mem_type) == 1)) {
                               stop("mem_type has to be an id or of type H5T")
                           }
                           ## now extract the ids
                           mem_type_id <- get_id(mem_type)
                       }
                       
                       check_pl(dataset_xfer_pl, "H5P_DATASET_XFER")
                       
                       ## need to create the buffer to write this into 
                       buffer <- .Call("R_H5ToR_Pre", mem_type_id, nelem, PACKAGE="hdf5r")
                       res <- .Call("R_H5Dread", self$id, mem_type_id, mem_space_id, file_space_id, dataset_xfer_pl$id,
                                    buffer, FALSE, PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error reading dataset")
                       }
                       buffer_post <- .Call("R_H5ToR_Post", res$buf, mem_type_id, nelem, flags, self$id, PACKAGE="hdf5r")
                       
                       if(set_dim && !inherits(buffer_post, "data.frame")) {
                           if(is.null(dim_to_set)) {
                               stop("dim_to_set needs to be specified if set_dim is true")
                           }
                           if(length(buffer_post) != prod(dim_to_set)) {
                               stop("Length of read object unequal to product of dim_to_set")
                           }
                           if(drop) {
                               dim_to_set <- dim_to_set[dim_to_set != 1]
                           }
                           
                           if(length(dim_to_set) > 1) {
                               .Call("set_dim_attribute", buffer_post, as.numeric(dim_to_set), PACKAGE = "hdf5r")
                           }
                       }
                       ## reclaim vlen data if the mem_type is vlen
                       ## first need to know if it is vlen; may in future integrate with R_H5ToR_Post
                       mem_type_is_vlen <- as.logical(.Call("R_H5Tdetect_vlen", mem_type_id, PACKAGE = "hdf5r")$return_val)
                       if(mem_type_is_vlen) {
                           mem_space_explicit_id <- as.integer64(.Call("R_H5Screate_simple", 1, nelem, nelem, PACKAGE="hdf5r")$return_val)
                           if(mem_space_explicit_id < 0) {
                               stop("Error creating simple dataspace")
                           }
                           on.exit(.Call("R_H5Sclose", mem_space_explicit_id, PACKAGE = "hdf5r"), add=TRUE)
                           herr <- .Call("R_H5Dvlen_reclaim", mem_type_id, mem_space_explicit_id,
                                         dataset_xfer_pl$id, buffer, FALSE, PACKAGE="hdf5r")$return_val
                           if(herr < 0 ) {
                               stop("Error trying to reclaim buffer vlen data")
                           }
                       }

                       return(buffer_post)
                   },
                   read=function(args=NULL, dataset_xfer_pl=h5const$H5P_DEFAULT, flags=getOption("hdf5r.h5tor_default"), drop=TRUE, envir=parent.frame()) {
                       "Main interface for reading data from the dataset. It is the function that is used by \\code{[}, where"
                       "all indices are being passed in the parameter \\code{args}."
                       "@param args The indices for each dimension to subset given as a list. This makes this easier to use as a programmatic API."
                       "For interactive use we recomment the use of the \\code{[} operator. If set to \\code{NULL}, the entire dataset will be read."
                       "@param envir The environment in which to evaluate \\code{args}"
                       "@param dataset_xfer_pl An object of class \\code{\\link{H5P_DATASET_XFER-class}}." 
                       "@param flags Some flags governing edge cases of conversion from HDF5 to R. This is related to how integers are being treated and"
                       "the issue of R not being able to natively represent 64bit integers and not at all being able to represent unsigned 64bit integers"
                       "(even using add-on packages). The constants governing this are part of \\code{\\link{h5const}}. The relevant ones start with the term"
                       "\\code{H5TOR} and are documented there. The default set here returns a regular 32bit integer if it doesn't lead to an overflow"
                       "and returns a 64bit integer from the \\code{bit64} package otherwise. For 64bit unsigned int that are larger than 64bit signed int,"
                       "it return a \\code{double}. This looses precision, however."
                       "@param drop Logical. When reading data, should dimensions of size 1 be dropped."
                       "@return The data that was read as an R object"

                       self_space_id <- as.integer64(.Call("R_H5Dget_space", self$id, PACKAGE="hdf5r")$return_val)
                       on.exit(.Call("R_H5Sclose", self_space_id, PACKAGE = "hdf5r"), add=TRUE)
                       
                       self_space_is_simple <- as.logical(.Call("R_H5Sis_simple", self_space_id, PACKAGE = "hdf5r")$return_val)
                       if(!self_space_is_simple) {
                           stop("Dataspace has to be simple for a selection to occur")
                       }
                       simple_extent <- standalone_H5S_get_simple_extent_dims(self_space_id)
                       ## distinguish between scalar and non-scalar
                       if(simple_extent$rank == 0) {
                           if(is.null(args)) {
                               args <- list(quote(expr=))
                           }
                           ## is a scalar
                           if(are_args_scalar(args)) {
                               res <- self$read_low_level(file_space=self_space_id, mem_space=self_space_id, dataset_xfer_pl=dataset_xfer_pl)
                           }
                           else {
                               stop("Scalar dataspace; arguments have to be of length 1 and empty or equal to 1")
                           }
                       }
                       else {
                           if(is.null(args)) {
                               ## create arguments that are missing in every dimension, i.e. represent all
                               args <- rep(list(quote(expr=)), simple_extent$rank)
                           }
                           reg_eval_res <- args_regularity_evaluation(args=args, ds_dims=simple_extent$dims, envir=envir)
                           ## need to check if maximum dimension in indices are larger than dataset dimensions
                           ## if yes need to throw an error
                           if(any(reg_eval_res$max_dims > simple_extent$dims)) {
                               stop("The following coordinates are outside the dataset dimensions: ",
                                    paste(which(reg_eval_res$max_dims > simple_extent$dims), sep=", "))
                           }
                           robj_dim <- private$get_robj_dim(reg_eval_res) 
                           selection <- regularity_eval_to_selection(reg_eval_res=reg_eval_res) 
                           apply_selection(space_id=self_space_id, selection=selection) 

                           ## create the memory space
                           mem_space_dims <- reg_eval_res$result_dims_pre_shuffle
                           mem_space_rank <- length(mem_space_dims)
                           mem_space_id <- as.integer64(.Call("R_H5Screate_simple", mem_space_rank, rev(mem_space_dims), rev(mem_space_dims),
                                                 PACKAGE="hdf5r")$return_val)
                           if(mem_space_id < 0) {
                               stop("Error creating simple dataspace")
                           }
                           on.exit(.Call("R_H5Sclose", mem_space_id, PACKAGE = "hdf5r"), add=TRUE)
                           
                           ## check if we have a compound, where we don't have to set 
                           dim_to_set <- robj_dim$robj_dim_pre_shuffle
                           
                           res <- self$read_low_level(file_space=self_space_id, mem_space=mem_space_id,
                                         dataset_xfer_pl=dataset_xfer_pl, set_dim=TRUE, dim_to_set=dim_to_set, drop=drop)
                           
                           if(any(reg_eval_res$needs_reshuffle)) {
                               res <- do_reshuffle(res, reg_eval_res)
                           }
                       }
                       return(res)
                   },
                   write_low_level=function(robj, file_space=h5const$H5S_ALL, mem_space=NULL, mem_type=NULL, dataset_xfer_pl=h5const$H5P_DEFAULT,
                       flush=getOption("hdf5r.flush_on_write")) {
                       "This function is for advanced users. It is recommended to use \\code{read} instead or the \\code{[<-} interface"
                       "as used for arrays."
                       "This function implements the HDF5-API function H5Dwrite, with some changes to accomodate R."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Write} for details."
                       "It writes that data from the \\code{robj} into the dataset."
                       "@param robj The object to write into the dataset"
                       "@param mem_space The space as it is represented in memory; advanced feature; may be removed in the future"
                       "@param mem_type Memory type; extracted from the dataset if null (can be passed in for efficiency reasons"
                       "@param file_space An HDF5-space, represented as class \\code{\\link{H5S-class}} that determines which part"
                       "of the dataset is being written."
                       "@param dataset_xfer_pl Dataset transfer property list. See \\code{\\link{H5P_DATASET_XFER-class}}"
                       "@param flush Should a flush be done after the write"

                       ## first ensure that file_space of the correct types and extract the id
                       if(!inherits(file_space, "H5S") && !(is.integer64(file_space) && length(file_space) == 1)) {
                           stop("file_space has to be an id or of type H5T")
                       }
                       file_space_id <- get_id(file_space)

                       if(file_space_id==h5const$H5S_ALL$id) {
                           ## get the actual file-space and ascertain its size
                           file_space_id <- .Call("R_H5Dget_space", self$id, PACKAGE="hdf5r")$return_val
                           on.exit(.Call("R_H5Sclose", file_space_id, PACKAGE = "hdf5r"), add=TRUE)
                           .Call("R_H5Sselect_all", file_space_id, PACKAGE = "hdf5r")

                           nelem_file <- .Call("R_H5Sget_select_npoints", file_space_id, PACKAGE = "hdf5r")$return_val
                           ## in this case, we ignore what mem_space is set to
                           mem_space_id <- h5const$H5S_ALL$id
                       }
                       else {
                            ## else, just get a linear space
                           nelem_file <- .Call("R_H5Sget_select_npoints", file_space_id, PACKAGE = "hdf5r")$return_val

                           if(is.null(mem_space)) {
                               ## use this simple space; this may come with some speed penalties
                               ## arguements are rank, dims, maxdims
                               mem_space_id <- as.integer64(.Call("R_H5Screate_simple", 1, nelem_file, nelem_file, PACKAGE="hdf5r")$return_val)
                               if(mem_space_id < 0) {
                                   stop("Error creating simple dataspace")
                               }
                               on.exit(.Call("R_H5Sclose", mem_space_id, PACKAGE = "hdf5r"), add=TRUE)

                           }
                           else {
                               if(!inherits(mem_space, "H5S") && !(is.integer64(mem_space) && length(mem_space) == 1)) {
                                   stop("mem_space has to be an id or of type H5T")
                               }
                               ## extract the id that was given
                               mem_space_id <- get_id(mem_space)
                           }
                       }

                       if(is.null(mem_type)) {
                           mem_type_id <- standalone_H5D_get_type(h5d_id=self$id, native=TRUE)
                           on.exit(.Call("R_H5Tclose", mem_type_id, PACKAGE = "hdf5r"), add=TRUE)
                       }
                       else {
                           if(!inherits(mem_type, "H5T") && !(is.integer64(mem_type) && length(mem_type) == 1)) {
                               stop("mem_type has to be an id or of type H5T")
                           }
                           ## now extract the ids
                           mem_type_id <- get_id(mem_type)
                       }
                       
                       nelem_robj <- .Call("R_guess_nelem", robj, mem_type_id, PACKAGE="hdf5r")

                       if(nelem_robj != nelem_file && (nelem_file %% nelem_robj != 0 || nelem_file < nelem_robj)) {
                           stop("Number of objects in robj is not the same and not a multiple of number of elements selected in file")
                       }
                       buffer <- .Call("R_RToH5", robj, mem_type_id, nelem_robj, PACKAGE="hdf5r")
                       if(nelem_robj != nelem_file) {
                           ## need to multiply input buffer
                           buffer <- rep(buffer, times=nelem_file / nelem_robj)
                       }
                       
                       res <- .Call("R_H5Dwrite", self$id, mem_type_id, mem_space_id, file_space_id, dataset_xfer_pl$id,
                                    buffer, PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error writing dataset")
                       }
                       if(flush) {
                           self$flush
                       }
                       return(invisible(self))
                   },
                   write=function(args, value, dataset_xfer_pl=h5const$H5P_DEFAULT, envir=parent.frame()) {
                       "Main interface for writing data to the dataset. It is the function that is used by \\code{[<-}, where"
                       "all indices are being passed in the parameter \\code{args}."
                       "@param args The indices for each dimension to subset given as a list. This makes this easier to use as a programmatic API."
                       "For interactive use we recomment the use of the \\code{[} operator. If set to \\code{NULL}, the entire dataset will be read."
                       "@param value The data to write to the dataset"
                       "@param envir The environment in which to evaluate \\code{args}"
                       "@param dataset_xfer_pl An object of class \\code{\\link{H5P_DATASET_XFER-class}}." 
                       "@return The HDF5 dataset object, returned invisibly"

                       
                       self_space_id <- as.integer64(.Call("R_H5Dget_space", self$id, PACKAGE="hdf5r")$return_val)
                       on.exit(.Call("R_H5Sclose", self_space_id, PACKAGE = "hdf5r"), add=TRUE)
                       
                       self_space_is_simple <- as.logical(.Call("R_H5Sis_simple", self_space_id, PACKAGE = "hdf5r")$return_val)
                       if(!self_space_is_simple) {
                           stop("Dataspace has to be simple for a selection to occur")
                       }
                       simple_extent <- standalone_H5S_get_simple_extent_dims(self_space_id)
                       ## distinguish between scalar and non-scalar
                       if(simple_extent$rank == 0) {
                           if(is.null(args)) {
                               args <- list(quote(expr=))
                           }
                           ## is a scalar
                           if(are_args_scalar(args)) {
                               return(self$write_low_level(value, file_space=self_space_id, mem_space=self_space_id, dataset_xfer_pl=dataset_xfer_pl))
                           }
                           else {
                               stop("Scalar dataspace; arguments have to be of length 1 and empty or equal to 1")
                           }
                       }
                       else {
                           if(is.null(args)) {
                               ## create arguments that are missing in every dimension, i.e. represent all
                               args <- rep(list(quote(expr=)), simple_extent$rank)
                           }
                           reg_eval_res <- args_regularity_evaluation(args=args, ds_dims=simple_extent$dims, envir=envir, post_read=FALSE)

                           robj_dim <- private$get_robj_dim(reg_eval_res) 
                           if(any(reg_eval_res$needs_reshuffle)) {
                               ## need to ensure that the input has the right dimensions attached in case it is just a vector)
                               ## and dimensions doesn't need to be reset for data.frames; there they are automatically correct
                               if(!inherits(value, "data.frame")) {
                                   dim(value) <- robj_dim$robj_dim_pre_shuffle
                               }
                               value <- do_reshuffle(value, reg_eval_res)
                           }
                           ## need to check if maximum dimension in indices are larger than dataset dimensions
                           ## if yes need to throw an error
                           if(any(reg_eval_res$max_dims > simple_extent$dims)) {
                               ## need to reset the extent of the arguments
                               if(any(reg_eval_res$max_dims > simple_extent$maxdims)) {
                                   stop("The following coordinates are larger than the largest possible dataset dimensions (maxdims): ",
                                        paste(which(reg_eval_res$max_dims > simple_extent$maxdims), sep=", "))
                               }
                               ## need to check that value conforms to the right dimension for the arguments
                               ## this is needed before a possible expansion of arguments
                               mem_type_id <- standalone_H5D_get_type(h5d_id=self$id, native=TRUE)
                               nelem_value <- .Call("R_guess_nelem", value, mem_type_id, PACKAGE="hdf5r")                               
                               .Call("R_H5Tclose", mem_type_id, PACKAGE = "hdf5r")

                               num_args_elem <- prod(reg_eval_res$result_dims_post_shuffle)
                               if(nelem_value != num_args_elem && (num_args_elem %% nelem_value != 0 || num_args_elem < nelem_value)) {
                                   stop("Number of objects in robj is not the same and not a multiple of number of elements selected in file")
                               }

                               self$set_extent(pmax(reg_eval_res$max_dims, simple_extent$dims))
                               .Call("R_H5Sclose", self_space_id, PACKAGE = "hdf5r")
                               self_space_id <- as.integer64(.Call("R_H5Dget_space", self$id, PACKAGE="hdf5r")$return_val)
                               on.exit(.Call("R_H5Sclose", self_space_id, PACKAGE = "hdf5r"), add=FALSE)
                           }

                           ## create the memory space
                           ## go through all the robj-dimension
                           selection <- regularity_eval_to_selection(reg_eval_res=reg_eval_res) 
                           apply_selection(space_id=self_space_id, selection=selection) 
                           
                           mem_space_dims <- reg_eval_res$result_dims_post_shuffle
                           mem_space_rank <- length(mem_space_dims)
                           
                           mem_space_id <- as.integer64(.Call("R_H5Screate_simple", mem_space_rank, rev(mem_space_dims), rev(mem_space_dims),
                                                 PACKAGE="hdf5r")$return_val)
                           if(mem_space_id < 0) {
                               stop("Error creating simple dataspace")
                           }
                           on.exit(.Call("R_H5Sclose", mem_space_id, PACKAGE = "hdf5r"), add=TRUE)

                           return(self$write_low_level(value, file_space=self_space_id, mem_space=mem_space_id, dataset_xfer_pl=dataset_xfer_pl))
                       }
                   },
                   set_extent=function(dims) {
                       "This function implements the HDF5-API function H5Dset_extent."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-SetExtent} for details."

                       rank <- self$get_space()$get_simple_extent_ndims()
                       if(length(dims) != rank) {
                           stop(paste("Length of dims is", length(dims), "but has to be equal to the rank of the dataspace:", rank))
                       }
                       res <- .Call("R_H5Dset_extent", self$id, rev(dims), PACKAGE="hdf5r")$return_val
                       if(res < 0) {
                           stop("Error setting new extent")
                       }
                       return(invisible(self))
                   },
                   get_fill_value=function() {
                       "This function implements the HDF5-API function H5Pget_fill_value, automatically"
                       "supplying the datatype of the dataset for convenience."
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html#Property-GetFillValue} for details."

                       dtype <- self$get_type()
                       create_plist <- self$get_create_plist()
                       value_h5 <- H5ToR_Pre(dtype, 1)
                       res <- .Call("R_H5Pget_fill_value", create_plist$id, dtype$id, value_h5, FALSE, PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error retrieving fill value")
                       }
                       return(H5ToR_Post(value_h5, dtype, 1, -1))
                   },
                   reorder=function(reorder_dim, start, end, new_order, max_mem, dataset_xfer_pl=h5const$H5P_DEFAULT, key_info=NULL) {
                       "Reorder a subset of an HDF5 dataset along a specific dimension. It is mostly intended as a function to be"
                       "used by a sorting algorithm and is not checked for correct inputs. Incorrect use can corrupt a dataset"
                       "@param reorder_dim The number of the dimension along which the reordering should occur."
                       "@param start,end The start and end index where the reordering should occur (can be vectors of equal length)"
                       "@param new_order The new ordering of the items to re-order. The ith item gives the index in the source for the i-th item in"
                       "the destination (for the \\code{reorder_dim})"
                       "@param max_mem Memory usage of the function in bytes (a rough guide, can be somewhat exceeded)"
                       "@param dataset_xfer_pl The dataset transfer propery list"
                       "@param key_info The key_info returned by the \\code{key_info} method of the dataset"
                       
                       check_pl(dataset_xfer_pl, "H5P_DATASET_XFER")

                       if(is.null(key_info)) {
                           key_info <- self$key_info
                       }
                       ## divide memory by two as at least 2 buffers will be needed
                       max_mem <- max_mem / 2

                       ds_dims <- key_info$dims
                       chunk_dims <- key_info$chunk_dims
                       if(any(is.na(chunk_dims))) {
                           ## not chunked, every element separate
                           chunk_dims <- rep(1, length(ds_dims))
                       }
                       chunk_dims[reorder_dim] <- sum(end - start + 1)

                       ## calculate number of chunks that can be fitted into
                       ## memory size
                       ds_type_size <- key_info$type_size_raw
                       chunk_size <- ds_type_size * prod(chunk_dims)

                       ## check if we can then read in even one datapoint
                       if(chunk_size > max_mem) {
                           chunk_dims <- rep(1, length(ds_dims))
                           chunk_dims[reorder_dim] <- sum(end - start + 1)
                           chunk_size <- ds_type_size * prod(chunk_dims)
                           if(chunk_size > max_mem) {
                               stop("max_mem too small to read in necessary data for reordering")
                           }
                           else {
                               warning("Cannot process data along chunk lines, reverting to smaller sizes")
                           }
                       }

                       ## calculate the number of chunks per dimension we can read in at the same time
                       num_chunks <- ceiling(ds_dims / chunk_dims)
                       num_chunks[reorder_dim] <- 1
                       ## repurposing the function that calculates the number of elements in a chunk
                       ## to calculate the number of chunks in a hyperslab
                       ## for s
                       chunk_mult <- guess_chunks(space_maxdims=num_chunks, dtype_size=chunk_size, chunk_size=max_mem)
                       metachunk_dims <- chunk_dims * chunk_mult
                       metachunk_dims[reorder_dim] <- sum(end - start + 1)
                       num_metachunks <- ceiling(ds_dims / metachunk_dims)
                       num_metachunks[reorder_dim] <- 1

                       ## now we have defined the optimal chunk size; now need to read it in, reorder it
                       ## and write it back out one item at a time
                       ## will use the lowest level read function to get optimal speed
                       total_chunks <- prod(num_metachunks)
                       ## need to get a buffer of sufficient size
                       buffer_size <- ds_type_size * prod(metachunk_dims)
                       buffer <- raw(buffer_size)

                       ds_file_space <- key_info$space
                       ds_mem_space <- H5S$new(type="simple", dims=metachunk_dims, maxdims=metachunk_dims)
                       ds_mem_space_start <- rep(1, length(ds_dims))
                       ds_mem_space_count <- rep(1, length(ds_dims))
                       ds_mem_space_stride <- rep(1, length(ds_dims))
                       # print(metachunk_dims)
                       is_vlen_type <- key_info$type$is_vlen()
                       for(i in seq_len(prod(num_metachunks))) {
                           ds_file_space$select_none()
                           ds_mem_space$select_none()
                           chunk_indices <- array_counter(count=i-1, dims=num_metachunks)
                           # print(chunk_indices)

                           ## create a return similar to that of the evaluate_arugments function so that we can re-use the
                           ## space_selection function
                           slab_start <- chunk_indices * metachunk_dims + 1
                           slab_count <-  rep(1, length(ds_dims))
                           slab_stride <- rep(1, length(ds_dims))
                           slab_block <- pmin(metachunk_dims, ds_dims - slab_start + 1)

                           ## the memory block is simply one contiguous set
                           ds_mem_space_block <- slab_block
                           ds_mem_space_block[reorder_dim] <- metachunk_dims[reorder_dim] # this one is always maximal
                           ds_mem_space$select_hyperslab(start=ds_mem_space_start, count=ds_mem_space_count, stride=ds_mem_space_stride,
                                                         block=ds_mem_space_block, op=h5const$H5S_SELECT_SET)
                           ## need to build a complex selection here for the file space
                           for(i in seq_along(start)) {
                               slab_start[reorder_dim] <- start[i]
                               slab_block[reorder_dim] <- end[i] - start[i] + 1
                               ds_file_space$select_hyperslab(start=slab_start, count=slab_count, stride=slab_stride, block=slab_block,
                                                              op=h5const$H5S_SELECT_OR)                               
                           }
                           # print(ds_file_space$get_select_hyper_blocklist())
                           ## now read the data into the buffer; the buffer may be larger than the data
                           res_read <- .Call("R_H5Dread", self$id, key_info$type$id, ds_mem_space$id, ds_file_space$id, dataset_xfer_pl$id,
                                        buffer, FALSE, PACKAGE="hdf5r")
                           if(res_read$return_val < 0) {
                               stop("Error reading dataset")
                           }

                           ## reorder the columns; here we set the dimensions of the dataset to the metachunk dimensions
                           ## on the re-ordering dimension, this is exact, but it may be larger on the others.
                           ## in this case, we may be re-ordering a part of the larger array, that contains data that is not part
                           ## of the current selection; this is fine, as we ignore this part again later when writing the data back out
                           buffer_reordered <- array_reorder(res_read$buf, dims=metachunk_dims, reorder_dim=reorder_dim, new_order=new_order,
                                                             item_size = ds_type_size)

                           ## write the buffer back out
                           res_write <- .Call("R_H5Dwrite", self$id, key_info$type$id, ds_mem_space$id, ds_file_space$id, dataset_xfer_pl$id,
                                        buffer_reordered, PACKAGE="hdf5r")
                           
                           ## reclaim vlen data if the mem_type is vlen
                           if(is_vlen_type) {
                               self$vlen_reclaim(buffer=res_read$buf, type=key_info$type, space=ds_mem_space, dataset_xfer_pl=dataset_xfer_pl)
                           }                          
                           
                       }                     
                       ## only close the memory space we created here
                       ds_mem_space$close()
                       
                       return(self)
                   },
                   create_reference=function(...) {
                       "This function implements the HDF5-API function H5Rcreate. The parameters are interpreted as in '['."
                       "The function always create \\code{H5R_DATASET_REGION} references"
                       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5R.html#Reference-Create} for details."

                       space <- self$get_space()
                       do.call("[", c(list(space), list(...)))
                       
                       ref_type <- h5const$H5R_DATASET_REGION
                       ref_obj <- H5R_DATASET_REGION$new(1, self)
                       
                       res <- .Call("R_H5Rcreate", ref_obj$ref, self$id, ".", h5const$H5R_DATASET_REGION, space$id, FALSE, PACKAGE="hdf5r")
                       if(res$return_val < 0) {
                           stop("Error creating object reference")
                       }
                       ref_obj$ref <- res$ref
                       return(ref_obj)
                   },
                   print=function(..., max.attributes){
                          "Prints information for the dataset"
                          "@param ... ignored"
                          "@param max.attributes Maximum number of attribute names to print"


                          is_valid <- self$is_valid
                          
                          print_class_id(self, is_valid)
                          
                          if(is_valid) {
                              ## get information about the file
                              ## get the dataset name
                              cat("Dataset: ", self$get_obj_name(), "\n", sep="")
                              ## get information about the file
                              this_file <- self$get_file_id()
                              cat("Filename: ", normalizePath(this_file$filename, mustWork=FALSE), "\n", sep="")
                              cat("Access type: ", as.character(this_file$get_intent()), "\n", sep="")
                              this_file$close()
                              ## get attributes
                              print_attributes(self, max_to_print=max.attributes)
                              ## get the datatype
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
                              this_chunk_dims <- self$chunk_dims
                              if(length(this_chunk_dims) == 1 && is.na(this_chunk_dims)) {
                                  cat("Not chunked\n")
                              }
                              else {
                                  cat("Chunk: ", paste(this_chunk_dims, collapse=" x "), "\n", sep="")
                              }
                         }
                          
                          return(invisible(self))
                      }


                   ),
               active=list(
                   dims=function() {
                       "Get the dimension of the dataset"
                       ds_space <- self$get_space()
                       res <- ds_space$dims
                       ds_space$close()
                       return(res)
                   },
                   maxdims=function() {
                       "Get the maximal dimension of the dataset"
                       ds_space <- self$get_space()
                       res <- ds_space$maxdims
                       ds_space$close()
                       return(res)
                   },
                   chunk_dims=function() {
                       "Return the dimension of the chunks. NA if the dataset is not chunked"
                       dataset_create_pl <- self$get_create_plist()
                       ds_space <- self$get_space()
                       ndims <- ds_space$get_simple_extent_ndims()
                       ds_space$close()
                       res <- dataset_create_pl$get_chunk(ndims)
                       dataset_create_pl$close()
                       return(res)
                   },
                   key_info=function() {
                       "Returns the key types as a list, consisting of type, space, dataset_create_pl,"
                       "type_size_raw, type_size_variable, dims and chunk_dims."
                       "type_size_raw versus variable differs for variable length types, which return \\code{Inf}"
                       "for type_size_variable and the underlying size for type_size_raw"
                       ds_space <- self$get_space()
                       ds_type <- self$get_type(native=TRUE)
                       ds_create_pl <- self$get_create_plist()
                       ds_dims <- ds_space$dims
                       return(list(space=ds_space, type=ds_type, create_pl=ds_create_pl,
                                   type_size_raw=ds_type$get_size(variable_as_inf=FALSE), type_size_variable=ds_type$get_size(variable_as_inf=TRUE),
                                   dims=ds_dims, chunk_dims=ds_create_pl$get_chunk(length(ds_dims))))
                   }
                   ),
               private=list(
                   closeFun=function(id) {
                       nrt <- NA
                       if(!is.na(id) && is.loaded("R_H5Dclose", PACKAGE="hdf5r")) {
                           invisible(.Call("R_H5Dclose", id, PACKAGE = "hdf5r"))
                       }
                   },
                   get_robj_dim=function(reg_eval_res) {
                       "Get the size of the resulting R object"
                       ""
                       "For normal objects, just uses the size of the indices in the request, and evaluates"
                       "them bost pre- and post-shuffle. If the internal object is an array, additional dimensions"
                       "are appended at the end."
                       "@title Get the size of the resulting R object"
                       "@param reg_eval_res The result of the regularity evaluation"
                       "@param dtype The datatype under consideration"
                       "@return A list with the dimensions of the resulting object, pre- and post shuffle"
                       "@author Holger Hoefling"
                       "@keywords internal"
                       add_array_dims <- NULL
                       dtype_id <- standalone_H5D_get_type(h5d_id=self$id, native=TRUE)
                       on.exit(.Call("R_H5Tclose", dtype_id, PACKAGE = "hdf5r"), add=TRUE)

                       dtype_cls_id <- .Call("R_H5Tget_class", dtype_id, PACKAGE="hdf5r")$return_val
                       if(dtype_cls_id == h5const$H5T_ARRAY) {
                           ## here we call the function separately for efficiency reasons
                           rank <- .Call("R_H5Tget_array_ndims", dtype_id, PACKAGE="hdf5r")$return_val
                           dims <- integer(rank)
                           add_array_dims <- .Call("R_H5Tget_array_dims2", dtype_id, dims, PACKAGE="hdf5r")$dims
                       }
                       robj_dim_pre_shuffle <- c(reg_eval_res$result_dims_pre_shuffle, add_array_dims)
                       robj_dim_post_shuffle <- c(reg_eval_res$result_dims_post_shuffle, add_array_dims)
                       return(list(robj_dim_pre_shuffle=robj_dim_pre_shuffle,
                                   robj_dim_post_shuffle=robj_dim_post_shuffle, add_array_dims=add_array_dims))
                   }
                   
                   ),
               cloneable=FALSE
               )

R6_set_list_of_items(H5D, "public", commonFGDT, overwrite=TRUE)
R6_set_list_of_items(H5D, "public", commonFGDTA, overwrite=TRUE)



##' Get the id of an H5RefClass
##'
##' If it is a H5RefClass, returns the id, otherwise returns the
##' object itself as it assumes it is already an id.
##' @title Get the id of an H5RefClass
##' @param obj Object to get the id from
##' @return The id itself
##' @author Holger Hoefling
##' @keywords internal
get_id <- function(obj) {
    if(inherits(obj, "H5RefClass")) {
        return(obj$id)
    }
    else {
        return(obj)
    }
}


##' Get the id of a type of the dataset
##'
##' A function that just returns an id; it is written standalone so that
##' one can use it to avoid the creation of R6 classes that be a considerable overhead in
##' certain circumstances
##' @title Get the id of a type of the dataset
##' @param native Should it be ensured that it is a native type
##' @param h5d_id The id of the dataset to get the type from
##' @return An id; the user has to ensure that the id is eventually closed
##' @author Holger Hoefling
##' @keywords internal
standalone_H5D_get_type <- function(h5d_id, native=TRUE) {
    id <- .Call("R_H5Dget_type", h5d_id, PACKAGE="hdf5r")$return_val
    if(id < 0) {
        stop("Error retrieving datatype of dataset")
    }
    if(native) {
        ## return the native type
        id_native <- .Call("R_H5Tget_native_type", id, h5const$H5T_DIR_ASCEND, PACKAGE="hdf5r")$return_val
        ## have the new id, can close the old one
        .Call("R_H5Tclose", id, PACKAGE="hdf5r")
        if(id_native < 0) {
            stop("Error retrieving native-c-type")
        }
        return(id_native)
    }
    else {
        return(id)
    }
}



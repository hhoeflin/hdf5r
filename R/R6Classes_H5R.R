
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
setOldClass("H5R_OBJECT")
setOldClass("H5R_DATASET_REGION")


ref_obj_size <- new.env()


#' Class for HDF5 Reference datatypes. 
#'
#' \code{H5R} is only the common, class, and is never used. User should not create objects of this
#' class by themselves and instead use the \code{create_reference} methods of \code{H5D}, \code{H5Group}, \code{H5File} classes.
#' @docType class
#' @importFrom R6 R6Class
#' @return Object of class \code{\link[=H5R-class]{H5R}}.
#' @export
#' @author Holger Hoefling
H5R <- R6Class("H5R",
               inherit=H5RefClass,
               public=list(
                   subset_read=function(dim_index, drop=TRUE) {
                       "Method that returns a subset of the data in the H5R-object"
                       "@param dim_index A list of dimension indices as usually pasted into \\code{[}"
                       "@param drop Logical. Should dimensions of size 1 be dropped."
                       if(!is.list(dim_index)) {
                           dim_index <- list(dim_index)
                       }
                       
                       if(length(dim_index) != self$rank && length(dim_index) != 1) {
                           stop("dim_index has to have the same length as the dimension of the object (or 1 as vector access)")
                       }
                       ## will do a very simple implementation for now; more sophisticated to come later
                       dummy_array <- 0:(self$length-1)
                       if(self$rank > 1) {
                           dim(dummy_array) <- private$pdim
                           dimnames(dummy_array) <- private$pdimnames
                       }
                       else {
                           names(dummy_array) <- private$pnames
                       }

                       ## TODO check if this is needed; 
                       ## replace NULL with missing so that the internal subsetting will work as expected
                       for(i in seq_along(args)) {
                           if(is.null(dim_index[[i]])) {
                               dim_index[i] <- list(bquote(expr=))
                           }
                       }

                       subset_ind <- do.call("[", c(list(dummy_array), dim_index, list(drop=drop)))
                       if(any(is.na(subset_ind))) {
                           stop("NA in subset not allowed")
                       }

                       ref_subset <- .Call("R_read_raw_subset_generic", private$pref, subset_ind, private$size, PACKAGE="hdf5r")

                       h5r_sub <- self$clone()
                       h5r_sub$ref <- ref_subset
                       h5r_sub$dim <- dim(subset_ind)
                       h5r_sub$dimnames <- dimnames(subset_ind)
                       h5r_sub$names <- names(subset_ind)

                       return(h5r_sub)
                   },
                   subset2_read=function(i, exact=TRUE) {
                       "Method to read a single item"
                       "@param i The single item to read"
                       "@param exact Is the item name exact or should partial matching be allowed?"

                       if(length(i) != 1) {
                           stop("can only read single element")
                       }

                       if(is.character(i)) {
                           if(exact) {
                               i <- match(i, private$pnames) - 1
                           }
                           else {
                               i <- pmatch(i, private$pnames) - 1
                           }
                           if(is.na(i)) {
                               stop("Element could not be found")
                           }
                           
                       }
                       else {
                           i <- as.numeric(i) - 1
                           if(is.na(i)) {
                               stop("NA not allowed")
                           }
                       }

                       ref_subset <- .Call("R_read_raw_subset_generic", private$pref, i, private$size, PACKAGE="hdf5r")

                       h5r_sub <- self$clone()
                       h5r_sub$ref <- ref_subset
                       h5r_sub$dim <- NULL
                       h5r_sub$dimnames <- NULL
                       h5r_sub$names <- NULL

                       return(h5r_sub)
                   },
                   subset_assign=function(dim_index, value) {
                       "Assign values into a subset of the H5R-vector"
                       "@param dim_index A list of dimension indices as usually pased into \\code{[}"
                       "@param value The value to assign"
                       if(inherits(value, "H5R")) {
                           value <- value$ref
                       }
                       else if(!is.raw(value)) {
                           stop("Value has to inherit form 'H5R' or be a raw vector")
                       }
                                              
                       if(!is.list(dim_index)) {
                           dim_index <- list(dim_index)
                       }

                       ## TODO check if this is needed; 
                       ## check that is has the correct dimension
                       if(length(dim_index) != self$rank && length(dim_index) != 1) {
                           stop("dim_index has to have the same length as the dimension of the object (or 1 as vector access)")
                       }
                       ## will do a very simple implementation for now; more sophisticated to come later
                       dummy_array <- 0:(self$length-1)
                       if(self$rank > 1) {
                           dim(dummy_array) <- private$pdim
                           dimnames(dummy_array) <- private$pdimnames
                       }
                       else {
                           names(dummy_array) <- private$pnames
                       }

                       ## replace NULL with missing so that the internal subsetting will work as expected
                       for(i in seq_along(args)) {
                           if(is.null(dim_index[[i]])) {
                               dim_index[i] <- list(bquote(expr=))
                           }
                       }

                       subset_ind <- do.call("[", c(list(dummy_array), dim_index, list(drop=drop)))
                       ## check that value has the correct size
                       if(length(value) != length(subset_ind) * private$size) {
                           stop("value does not have the correct size")
                       }
                       
                       private$pref <- .Call("R_write_raw_subset_generic", private$pref, value, subset_ind, private$size, PACKAGE="hdf5r")

                       return(self)
                   },
                   subset2_assign=function(i, exact=TRUE, value) {
                       "Assign a value to a single value in the array"
                       "@param i the index where to assign the value"
                       "@param value The value to assign"
                       if(inherits(value, "H5R")) {
                           value <- value$ref
                       }
                       else if(!is.raw(value)) {
                           stop("Value has to inherit form 'H5R' or be a raw vector")
                       }
                       
                       if(length(i) != 1) {
                           stop("can only read single element")
                       }
                       
                       if(is.character(i)) {
                           if(exact) {
                               i <- match(i, private$pnames) - 1
                           }
                           else {
                               i <- pmatch(i, private$pnames) - 1
                           }
                           if(is.na(i)) {
                               stop("Element could not be found")
                           }
                       }
                       else {
                           i <- as.numeric(i) - 1
                           if(is.na(i)) {
                               stop("NA not allowed")
                           }
                       }

                       private$pref <- .Call("R_write_raw_subset_generic", private$pref, value, i, private$size, PACKAGE="hdf5r")

                       return(self)
                   },
                   t=function() {
                       "Transpose the object if it is a matrix (i.e. has rank 2"
                       ## we want to transpose it; check that it is a matrix
                       if(length(private$pdim) != 2) {
                           stop("Not a matrix; can't transpose")
                       }

                                             
                       private$pref <- .Call("R_transpose_general", private$pref, private$pdim, private$size, PACKAGE="hdf5r")
                       private$pdim <- rev(private$pdim)
                       private$pdimnames <- rev(private$pdimnames)
                       return(self)
                   }
                   ),
               active=list(
                   length=function() {
                       "Get the length of the object"
                       return(length(private$pref) / private$size)
                   },
                   ref=function(ref) {
                       "Get or assign the internal raw-vector representation of the data. Usually, user's shouldn't have to use this."
                       if(missing(ref)) {
                           return(private$pref)
                       }
                       else {
                           if(length(ref) != length(private$pref)) {
                               private$pdim <- NULL
                               private$pdimnames <- NULL
                               private$pnames <- NULL
                           }
                           if(!is.raw(ref)) {
                               stop("The references has to be a vector of type raw")
                           }
                           if(length(ref) %% private$size != 0) {
                               stop("ref has to be a length that is a multiple of the base size")
                           }
                           private$pref <- ref
                           return(self)
                       }
                   },
                   dim=function(x) {
                       "Get or assign the dimensionality of the object"
                       if(missing(x)) {
                           return(private$pdim)
                       }
                       else {
                           if(length(x) <= 1) {
                               private$pdim <- NULL
                               private$pdimnames <- NULL
                           }
                           else {
                               if(self$length != prod(x)) {
                                   stop("product of dimensions has to be equal to the length of the dataset")
                               }
                               else {
                                   private$pdim <- as.numeric(x)
                               }
                               private$pdimnames <- vector("list", length(x))
                               private$pnames <- NULL
                           }
                           return(self)
                       }
                   },
                   dimnames=function(x) {
                       "Get or assign the dimnames of the object"
                       if(missing(x)) {
                           return(private$pdimnames)
                       }
                       else {
                           if(!(is.null(x) || (is.list(x) && length(x) == self$rank))) {
                               stop("dimnames has to be a list with the same length as the rank of the dataset")
                           }
                           for(i in seq_along(x) ) {
                               x[[i]] <- as.character(x[[i]])
                           }
                           private$pdimnames <- x
                           return(self)
                       }
                   },
                   names=function(x) {
                       "Get or assign the names of the object"
                       if(missing(x)) {
                           return(private$pnames)
                       }
                       else {
                           if(!(is.null(x) || length(x) == self$length)) {
                               stop("names has to have the same length as x")
                           }
                           if(is.null(x)) {
                               private$pnames <- NULL
                           }
                           else {
                               private$pnames <- as.character(x)
                           }
                       }
                   },
                   rank=function() {
                       "Get the rank of the object"
                       return(max(1, length(private$pdim)))
                   }
                   ),
               private=list(
                   pref=raw(0),
                   size=0,
                   pdim=NULL,
                   pdimnames=NULL,
                   pnames=NULL,
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

ref_func_clone_public <- list(
    clone=function() {
        self$inc_ref()
        ## during initialization, the internal counter in R is increased; as this is
        ## not the case here, so has to be increased manually
        incr_count(as.integer64(self$id))
        cloned_obj <- private$pclone()
        reg.finalizer(cloned_obj, function(e) { e$close()}, onexit=TRUE)
        return(cloned_obj)
    }
    )
R6_set_list_of_items(H5R, "private", list(pclone=H5R$clone_method), overwrite=TRUE)
R6_set_list_of_items(H5R, "public", ref_func_clone_public, overwrite=TRUE)



##' @rdname H5R-class
##' @export
H5R_OBJECT <- R6Class("H5R_OBJECT",
                      inherit=H5R,
                      public=list(
                          initialize=function(num=0, id=NULL) {
                              "Create a new reference for object; Usually, users shouldn't have to call this, but use the \\code{create_reference}"
                              "method of a dataset, group of commited datatype"
                              if(inherits(id, "H5File")) {
                                  id$inc_ref()
                                  id <- id$id
                              }
                              else if(inherits(id, "H5RefClass")) {
                                  id <- id$get_file_id()
                                  id$inc_ref()
                                  id <- id$id
                              }
                              super$initialize(id=id)
                              private$size <- ref_obj_size$H5R_OBJECT
                              self$ref <- raw(private$size * num) 
                              return(self)
                          },
                          dereference=function(object_access_pl=h5const$H5P_DEFAULT, obj=NULL) {
                              "Dereference an H5R reference. The file the reference is pointing to is assigned automatically"
                              "This function implements the HDF5-API function H5Rdereference."
                              "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5R.html#Reference-Dereference} for details."
                              "@param obj Overriding the default file the reference is referring to"
                              "@param object_access_pl The object-access property list. Currently always the default"

                              res <- vector("list", length=self$length)
                              index_vec_end <- private$size * seq_along(res)
                              index_vec_start <- index_vec_end  - private$size + 1
                              if(is.null(obj)) {
                                  deref_id <- self$id
                              }
                              else {
                                  deref_id <- obj$id
                              }
                              if(grepl("^1\\.8\\.", h5version(verbose=FALSE))) {
                                  ## use the old api
                                  for(i in seq_along(res)) {
                                      myref <- private$pref[index_vec_start[i]:index_vec_end[i]]
                                      id <- .Call("R_H5Rdereference",deref_id, h5const$H5R_OBJECT, myref, PACKAGE = "hdf5r")$return_val
                                      res[[i]] <- H5GTD_factory(id)
                                  }
                              }
                              else {
                                  ## use the new api
                                  for(i in seq_along(res)) {
                                      myref <- private$pref[index_vec_start[i]:index_vec_end[i]]
                                      id <- .Call("R_H5Rdereference2",deref_id, object_access_pl$id, h5const$H5R_OBJECT, myref, PACKAGE = "hdf5r")$return_val
                                      res[[i]] <- H5GTD_factory(id)
                                  }
                              }
                              return(res)
                          }
                          ),
                      cloneable=FALSE
                      )


##' @rdname H5R-class
##' @export
H5R_DATASET_REGION <- R6Class("H5R_DATASET_REGION",
                      inherit=H5R,
                      public=list(
                          initialize=function(num=0, id=NULL) {
                              "Create a new reference for dataset regions; Usually, users shouldn't have to call this, but use the "
                              "\\code{create_reference} method of a dataset."
                              if(inherits(id, "H5File")) {
                                  id$inc_ref()
                                  id <- id$id
                              }
                              else if(inherits(id, "H5RefClass")) {
                                  id <- id$get_file_id()
                                  id$inc_ref()
                                  id <- id$id
                              }
                              super$initialize(id=id)
                              private$size <- ref_obj_size$H5R_DATASET_REGION
                              self$ref <- raw(private$size * num) 
                              return(self)
                          },
                          dereference=function(object_access_pl=h5const$H5P_DEFAULT, obj=NULL, get_value=FALSE) {
                              "Dereference an H5R reference for a dataset region. The file the reference is pointing to is assigned automatically."
                              "It returns a list where each item is a list with components \\code{dataset}, being an \\code{H5D-class} object and"
                              "\\code{space} being a \\code{H5S-class} object. When setting \\code{get_value=TRUE}, then instead of these objects"
                              "The data itself is returned"
                              "This function implements the HDF5-API function H5Rdereference."
                              "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5R.html#Reference-Dereference} for details."
                              "@param obj Overriding the default file the reference is referring to"
                              "@param object_access_pl The object-access property list. Currently always the default"

                              res <- vector("list", length=self$length)
                              index_vec_end <- private$size * seq_along(res)
                              index_vec_start <- index_vec_end  - private$size + 1

                              if(is.null(obj)) {
                                  deref_id <- self$id
                              }
                              else {
                                  deref_id <- obj$id
                              }

                              if(grepl("^1\\.8\\.", h5version(verbose=FALSE))) {
                                  ## use the old api
                                  for(i in seq_along(res)) {
                                      myref <- private$pref[index_vec_start[i]:index_vec_end[i]]
                                      id_ds <- .Call("R_H5Rdereference", deref_id, h5const$H5R_DATASET_REGION, myref, PACKAGE = "hdf5r")$return_val
                                      id_space <- .Call("R_H5Rget_region", deref_id, h5const$H5R_DATASET_REGION, myref, PACKAGE = "hdf5r")$return_val
                                      obj_ds <- H5D$new(id=id_ds)
                                      obj_space <- H5S$new(id=id_space)
                                      if(get_value) {
                                          ## need to determine which dimensionality the output should have
                                          obj_ds_dtype <- obj_ds$get_type()
                                          dim_to_set <- extract_dim(obj_space, obj_ds_dtype)
                                          res[[i]] <- obj_ds$read_low_level(file_space=obj_space, mem_type=obj_ds_dtype, set_dim=TRUE,
                                                                            dim_to_set=dim_to_set)
                                      }
                                      else {
                                          res[[i]] <- list(dataset=obj_ds, space=obj_space)
                                      }
                                  }
                              }
                              else {
                                  ## use the new api
                                  for(i in seq_along(res)) {
                                      myref <- private$pref[index_vec_start[i]:index_vec_end[i]]
                                      id_ds <- .Call("R_H5Rdereference2", deref_id, object_access_pl$id, h5const$H5R_DATASET_REGION,
                                                     myref, PACKAGE = "hdf5r")$return_val
                                      id_space <- .Call("R_H5Rget_region", deref_id, h5const$H5R_DATASET_REGION, myref, PACKAGE = "hdf5r")$return_val
                                      obj_ds <- H5D$new(id=id_ds)
                                      obj_space <- H5S$new(id=id_space)
                                      if(get_value) {
                                          ## need to determine which dimensionality the output should have
                                          obj_ds_dtype <- obj_ds$get_type()
                                          dim_to_set <- extract_dim(obj_space, obj_ds_dtype)
                                          res[[i]] <- obj_ds$read_low_level(file_space=obj_space, mem_type=obj_ds_dtype, set_dim=TRUE,
                                                                            dim_to_set=dim_to_set)
                                      }
                                      else {
                                          res[[i]] <- list(dataset=obj_ds, space=obj_space)
                                      }
                                  }
                              }
                              return(res)
                          }
                          ),
                      cloneable=FALSE
                      )




##' Compare the ids of objects
##'
##' When several \code{H5RefClass} objects are passed in
##' @title Compare the ids of objects
##' @param ... Any \code{H5RefClass} objects
##' @return Logical - are all ids the same of the objects passed in
##' @author Holger Hoefling
##' @keywords internal
##' @importFrom bit64 integer64
equal_id_check <- function(...) {
    objs <- list(...) 

    ids <- integer64(length(objs))
    
    for(i in seq_along(objs)) {
        if(!inherits(objs[[i]], "H5RefClass")) {
            stop("Need to inherit from H5RefClass")
        }
        ids[i] <- objs[[i]]$id
    }

    ## check that they are all equal
    ids <- unique(ids)
    if(length(ids) == 1 && !is.na(ids)) {
        return(TRUE)
    }
    else {
        return(FALSE)
    }
}

## the purpose of the base class is to provide the functionality so that it can behave like a vector, matrix or array

##' Checks if object is of a HDF5-Reference class
##'
##' Simple check if it inherits from \code{H5R}, \code{H5R_OBJECT} or \code{H5R_DATSET_REGION}.
##' @title Checks if object is of a HDF5-Reference class
##' @param x The object to check
##' @return Logical 
##' @author Holger Hoefling
##' @export
is.H5R <- function(x) inherits(x, "H5R")

##' @rdname is.H5R
##' @export
is.H5R_OBJECT <- function(x) inherits(x, "H5R_OBJECT")

##' @rdname is.H5R
##' @export
is.H5R_DATASET_REGION <- function(x) inherits(x, "H5R_DATASET_REGION")


##' Return the name-vector of an object
##'
##' Returns the name vector of the object
##' @title Return the name-vector of an object
##' @param x The object to get the names of
##' @return A character vector
##' @author Holger Hoefling
##' @export
names.H5R <- function(x) {
    return(x$names)
}


##' Retrieve length of an object
##'
##' Returns the slot that describes the length of the object
##' @title Retrieve length of an object
##' @param x The object to get the length of
##' @return Length of the object 
##' @author Holger Hoefling
##' @export
length.H5R <- function(x) {
    return(x$length)
}


##' Subset or assign into a vector/array
##'
##' The standard array/vector subsetting functions
##' @title Subset or assign into a vector/array
##' @param x The object to subset
##' @param i First dimension
##' @param j Second dimension
##' @param ... Any other dimensions
##' @param drop Should dimensions of size 1 be dropped; LOGICAL
##' @param value The value in an assignment
##' @return A corresponding object that is the subset of the vector
##' @author Holger Hoefling
##' @export
##' @rdname subset
'[.H5R' <- function(x, i, j, ..., drop=TRUE) {
    ## take the number of arguments and substract 2 (the functions and x)
    mdrop <- missing(drop)
    Narg <- nargs() - (!mdrop)
    if(Narg == 2) {
        dim_index <- eval(substitute(alist(i, ...)))
    }
    else {
        dim_index <- eval(substitute(alist(i, j, ...)))
    }
    ## check; if j is missing and it is of length 2, then also don't give j
    return(x$subset_read(dim_index, drop=drop))
}


##' @export
##' @rdname subset
'[<-.H5R' <- function(x, i, ..., value) {
    ## take the number of arguments and substract 3 (the functions, x, and value)
    dim_index <- eval(substitute(alist(i, ...)))

    return(x$subset_assign(dim_index, value=value))
}



## Not possible to include; interferes with the clone method sind R6 2.1.3
## as objects in the clone method are now accessed through [[
## ##' @export
## ##' @rdname subset
## '[[.H5R' <- function(x, i, ..., exact=TRUE) {
##     return(x$subset2_read(i, exact=exact))
## }


## ##' @export
## ##' @rdname subset
## '[[<-.H5R' <- function(x, i, ..., exact=TRUE, value) {
##     return(x$subset2_assign(i, exact=exact, value=value))
## }

##' Concatenate HDF5-Reference objects
##'
##' Concatenates HDF5-Reference objects; also concatenates the names, replacing empty strings
##' if the names are \code{NULL}.
##' @title Concatenate HDF5-Reference objects
##' @param ... The objects to concatenate; All have to be references with respect to the same class
##' @param recursive Ignored here
##' @return An object of the same class, with all components concatenated
##' @author Holger Hoefling
##' @export
c.H5R <- function(..., recursive=FALSE) {
    if(recursive) {
        stop("recursive=TRUE currently not supported") 
    }

    if(!equal_id_check(...)) {
        stop("All objects have to have the same file_id")
    }
    ## check that all objects have the same class
    args <- list(...)

    args_classes <- unlist(lapply(args, function(x) {return(paste(class(x), collapse=","))}))
    if(length(unique(args_classes)) > 1) {
        stop("All objects have to have the same class")
    }

    res <- args[[1]]$clone()

    res_ref <- lapply(args, function(x) x$ref)
    res_ref <- do.call(c, res_ref)

    res_names <- unlist(lapply(args, function(x) {
        x_names <- x$names
        if(is.null(x_names)) {
            x_names <- rep("", x$length)
        }
        return(x_names)
    }))
    
    if(all(res_names=="")) {
        res_names <- NULL
    }

    res$ref <- res_ref
    res$dimnames <- NULL
    res$dim <- NULL
    res$names <- res_names

    return(res)
}

##' Get/Assign dimension of an object
##'
##' Get/Assign the dimensionality of the objects.
##' @title Get/Assign dimension of an object
##' @param x The object to get/assign dimensions
##' @param value A vector specifiying the dimensions of the object
##' @return A vector with the dimensions
##' @author Holger Hoefling
##' @export
dim.H5R <- function(x) {
    return(x$dim)
}

##' @export
##' @rdname dim.H5R
'dim<-.H5R' <- function(x, value) {
    x$dim <- value
    return(x)
}


## for internal use only; written as I don't know how to access an active function from c-code
set_ref.H5R <- function(x, value) {
    x$ref <- value
    return(x)
}


##' Transpose a HDF5-Reference matrix
##'
##' Clones the matrix and returns a transpose of the clone
##' @title Transpose a HDF5-Reference matrix
##' @param x The matrix to transpose; will be cloned
##' @return A transposed version of the HDF5-Reference matrix; a clone
##' @author Holger Hoefling
##' @export
t.H5R <- function(x) {
    return(x$clone()$t())
}


##' Get/set dimnames
##'
##' Get/set the dimnames of an \code{H5R} object
##' @title Get/set dimnames
##' @param x The object to get/set the dimnames of
##' @param value The dimnames to set. Has to be a list of character vectors of length equal to the rank of the array
##' @return A list of length equal to the rank of the array, with each element being a character vector 
##' @author Holger Hoefling
##' @export
dimnames.H5R <- function(x) {
    return(x$dimnames)
}

##' @rdname dimnames.H5R
##' @export
'dimnames<-.H5R' <- function(x, value) {
    x$dimnames <- value
    return(x)
}


##' cbind/rbind of HDF5-Reference classes
##'
##' cbind/rbind functionality for HDF5-Reference classes
##' @title cbind/rbind of HDF5-Reference classes
##' @param ... The objects to put together by row/column
##' @param deparse.level Has to be 1; otherwise ignored
##' @return An HDF5-Reference object that is the result of binding the rows/columns of the arrays
##' @author Holger Hoefling
##' @export
cbind.H5R <- function(..., deparse.level=1) {
    if(deparse.level > 1) {
        stop("deparse.level > 1 currently not supported")
    }
    if(!equal_id_check(...)) {
        stop("All objects have to refer to the same underlying file")
    }
    args <- list(...)
    
    ## check that the classes are compatible
    args_classes <- unlist(lapply(args, function(x) {return(paste(class(x), collapse=","))}))
    if(length(unique(args_classes)) > 1) {
        stop("All objects have to have the same class")
    }

    ## check that the dimensions are compatible; all have same number of rows
    args_rank <- unlist(lapply(args, function(x) x$rank))

    if(any(args_rank > 2)) {
        stop("Not all objects have rank 1 or 2")
    }
    ## for any that have rank 1, coerce to a matrix with 1 column
    for(i in which(args_rank==1)) {
        args[[i]]$dim <- c(args[[i]]$length, 1)
    }
    
    args_nrow <- unlist(lapply(args, nrow))

    if(length(unique(args_nrow)) != 1) {
        stop("Not all objects have the same number of rows")
    }
    args_ncol <- unlist(lapply(args, ncol))
    
    ## in this case we just need to concatenate the results
    row_dimnames <- args[[1]]$dimnames[[1]]
    col_dimnames <- unlist(lapply(args, function(x) {
        x_colnames <- x$dimnames[[2]]
        if(is.null(x_colnames)) {
            x_colnames <- rep("", x$length)
        }
        x_colnames
    }))

    res_dimnames <- list(row_dimnames, col_dimnames)
    res_ref <- do.call(c, lapply(args, function(x) x$ref))
    res_dim <- c(args_nrow[1], sum(args_ncol))

    res <- args[[1]]$clone()
    res$ref <- res_ref
    res$dim <- res_dim
    res$dimnames <- res$dimnames

    return(res)
}

##' @rdname cbind.H5R
##' @export
rbind.H5R <- function(..., deparse.level=1) {
    if(deparse.level > 1) {
        stop("deparse.level > 1 currently not supported")
    }
    if(!equal_id_check(...)) {
        stop("All objects have to refer to the same underlying file")
    }

    ## currently not very efficient; but will leave as it is for now
    ## high efficiency not necessary for this datatype
    ## not clear how often this function will ever be needed
    args <- list(...)
    args <- lapply(args, function(x) x$clone())
    args <- lapply(args, function(x) x$t())
    res <- do.call(cbind, args)
    return(res$t())
}


##' Printing of an object of class \code{h5R}
##'
##' Rudimentary printing of information of the object, mainly its length
##' @title Printing of an object of class \code{h5R}
##' @param x The object to print
##' @param ... Ignored
##' @return The printed text as an invisible character vector
##' @author Holger Hoefling
##' @export
print.H5R <- function(x, ...) {
    cat(class(x)[1], " of length ", x$length, "\n")
}


##' Formatting of an H5R object
##'
##' Formatting of H5R objects
##' @title Formatting of an H5R object
##' @param x The object to format
##' @param ... ignored
##' @return Character vector with the class names in angle-brackets
##' @author Holger Hoefling
##' @export
format.H5R <- function(x, ...) {
    rep(paste0("<", class(x)[1], ">"), x$length)
}

##' Coerce an \code{H5R} object to a data.frame
##'
##' Coerce an \code{H5R} object to a data.frame
##' @title Coerce an \code{H5R} object to a data.frame
##' @param x The \code{H5R} object to coerce to a data-frame
##' @param row.names \code{NULL} or a character vector giving the row names for the
##' data frame.  Missing values are not allowed.
##' @param optional logical. If \code{TRUE}, setting row names and converting column
##' names (to syntactic names: see \code{make.names}) is optional.
##' @param ... additional arguments to be passed to or from methods.
##' @param nm The column names to use
##' @param width.cutoff ignored
##' @param collapse ignored
##' @return A data frame  
##' @author Holger Hoefling
##' @export
as.data.frame.H5R <-  function (x, row.names = NULL, optional = FALSE, ..., nm = paste(deparse(substitute(x), 
    width.cutoff = 500L), collapse = " ")) {
    if(x$rank == 1) {
        return(as.data.frame.vector(x=x, row.names=row.names, optional=optional, ..., nm=nm))
    }
    else {
        return(as.data.frame.matrix(x=x, row.names=row.names, optional=optional, ...))
    }
}


##' Coerce to a vector
##'
##' Coerce an \code{H5R} object to a vector - in practice this just means setting the \code{dim} to \code{NULL}.
##' @title Coerce to a vector
##' @param x The object to coerce into a vector
##' @param mode Only 'any' supported
##' @return The object cloned and coerced to a vector 
##' @author Holger Hoefling
##' @export
##' @method as.vector H5R
as.vector.H5R <- function(x, mode="any") {
    if(mode != "any") {
        stop("Only mode 'any' supported")
    }
    x <- x$clone()
    x$dim <- NULL
    return(x)
}




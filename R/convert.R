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






##' Low-level conversion functions from R to HDF5 and vice versa
##'
##' These are the low-level function that dispatch the R object to HDF5 object conversion to the underlying C code.
##' None of these should be accessed by the end-user under normal circumstances. See also \code{\link{convertRoundTrip}}
##' for an example of how to use them.
##' @title Low-level conversion functions from R to HDF5 and vice versa
##' @param Robj The R-object to transfer to HDF5
##' @param dtype Datatype of the HDF5 object. Of class \code{\link{H5T}}
##' @param nelem Number of elements to copy
##' @param flags Some flags governing edge cases of conversion from HDF5 to R. This is related to how integers are being treated and
##' the issue of R not being able to natively represent 64bit integers and not at all being able to represent unsigned 64bit integers
##' (even using add-on packages). The constants governing this are part of \code{\link{h5const}}. The relevant ones start with the term
##' \code{H5TOR} and are documented there. The default set here returns a regular 32bit integer if it doesn't lead to an overflow
##' and returns a 64bit integer from the \code{bit64} package otherwise. For 64bit unsigned int that are larger than 64bit signed int,
##' it is truncated (the default; but can also be set to NA).
##' @param id When creating a reference, an id for the file (or an object in the file) is needed. By default \code{-1}, which will work
##' with everything except references.
##' @return The converted object or the buffer into which the object is written. 
##' @author Holger Hoefling
##' @keywords internal
RToH5 <- function(Robj, dtype, nelem) {
    return(.Call("R_RToH5", Robj, dtype$id, nelem, PACKAGE="hdf5r"))
}

##' @rdname RToH5
H5ToR_Pre <- function(dtype, nelem) {
    return(.Call("R_H5ToR_Pre", dtype$id, nelem, PACKAGE="hdf5r"))
}

##' @rdname RToH5
H5ToR_Post <- function(Robj, dtype, nelem, flags=getOption("hdf5r.h5tor_default"), id=-1) {
    return(.Call("R_H5ToR_Post", Robj, dtype$id, nelem, flags, id, PACKAGE="hdf5r"))
}



##' Create an empty R-object according to a given HDF5 datatype
##'
##' With complex datatypes it can be useful to have a template that can be used so that the
##' data input into a dataset conforms to expectations.
##'
##' Given a datatype, this function creates an object of length \code{nelem}.
##' Here, an empty datatype refers to objects with value 0 for numeric objects and
##' empty strings.
##' @title Create an empty R-object according to a given HDF5 datatype
##' @param nelem The number of elements to use for the object
##' @param dtype The datatype based on which an empty R-object should be created
##' @return An empty R object corresponding to the datatype that was passed in
##' @author Holger Hoefling
##' @export
create_empty <- function(nelem, dtype) {
    flags <- h5const$H5TOR_CONV_INT64_NOLOSS ## in this case, does not matter

    ## create an r-object that represents a request to give HDF5-space of nelem elements
    Robj <- request_empty(nelem)
    h5val_raw <- RToH5(Robj, dtype, nelem)
    ## initialize to make sure
    
    retRobj <- H5ToR_Pre(dtype, nelem)
    dtype_size <- dtype$get_size()
    if(dtype_size==Inf) {
        dtype_size <- dtype$get_size(variable_as_inf=FALSE)
    }
    retRobj <- copyRVec(retRobj, h5val_raw, nelem * dtype_size);
    retRobj <- H5ToR_Post(retRobj, dtype, nelem, flags)
    return(retRobj)
}




copyRVec <- function(dst, src, nbytes) {
    return(.Call("copy_rvec", dst, src, as.integer(nbytes), PACKAGE="hdf5r"))
}


##' @rdname guess_dtype
##' @export
guess_nelem <- function(x, dtype) {
    return(.Call("R_guess_nelem", x, dtype$id, PACKAGE="hdf5r"))
}

##' @rdname guess_dtype
##' @export
guess_dim <- function(x) {
    if(inherits(x, "data.frame")) {
        return(nrow(x))
    }
    else if(!is.null(dim(x))) {
        return(dim(x))
    }
    else {
        return(length(x))
    }
}

##' Guess the HDF5 datatype of an R object
##'
##' Given an object, it creates a datatype in HDF5 that would match this object. For simple datasets like arrays, this
##' function is not so useful, but is very good for creating dataframes or hierarchical objects (like lists of dataframes) etc.
##' @title Guess the HDF5 datatype of an R object
##' @param x The object for which to guess the HDF5 datatype or the dimension or the number of elements
##' @param dtype datatype; used in guessing the number of dataset elements of an r object
##' @param ds_dim Can explicitly set the dimension of the dataset object. For \code{scalar}, this is one. Otherwise, this can be
##' used so that a multi-dimensional object can be represented so that some of its dimension are in the dataset, and some are inside an
##' \code{\link{H5T_ARRAY}}
##' @param scalar Should the datatype be created so that \code{x} can be represented as a scalar with that datatype? This is intended
##' to know if a vector/array should be represented as an \code{\link{H5T_ARRAY}} or not.
##' @param string_len If a string is in the R object, the length to which the corresponding HDF5 type should be set. If it is a
##' positive integer, the string is of that length. If it is \code{Inf}, it is variable length. If it is set to \code{estimate},
##' it is set to the length of the longest string in the \code{x}.
##' @return An object of class \code{\link{H5T}} that represents the HDF5-type of the Robj that was passed in
##' @author Holger Hoefling
##' @importFrom bit64 is.integer64
##' @export
guess_dtype <- function(x, ds_dim=NULL, scalar=FALSE, string_len=getOption("hdf5r.default_string_len")) {
    ## check for the different classes
    ## if could be:
    ## a data frame
    ## an regular array
    ## a ragged array (VLEN)
    ## a string
    ## an enumeration
    ## a complex number
    ## integer
    ## float
    ## reference data type
    
    guessed_dim <- guess_dim(x)

    if(is.null(ds_dim)) {
        if(scalar) {
            ds_dim <- 1
        }
        else {
            ds_dim <- guessed_dim
        }
    }
    
    ## first check if we need an array; for this look if the number of elements is the same
    ## as the number of elements in the Robj
    if(length(ds_dim) != length(guessed_dim) || any(ds_dim != guessed_dim)) {
        ## it could be an array, or it might simply not match
        if(ds_dim==1) { ## simply create an array
            dtype_base <- guess_dtype(x, ds_dim=guessed_dim, scalar=FALSE, string_len=string_len)
            array_type <- H5T_ARRAY$new(dims=guessed_dim, dtype_base=dtype_base)
            return(array_type)
        }
        else { ## check that the outer dimensions match
             ## equal also captured here; with equal size, all items  would have to be the same, but aren't
            ## as seen by previous if query
            if(length(ds_dim) >= length(guessed_dim)) {
                stop(paste("Dimensions don't match. Should be", str_dim(ds_dim), "but is", str_dim(guessed_dim)))
            }
            if(any(ds_dim != guessed_dim[seq_along(ds_dim)])) {
                stop(paste("Dimensions don't match. Should be", str_dim(ds_dim), "but is", str_dim(guessed_dim)))
            }
            rest_dim <- guessed_dim[-seq_along(ds_dim)]
            dtype_base <- guess_dtype(x, ds_dim=guessed_dim, scalar=FALSE, string_len=string_len)
            array_type <- H5T_ARRAY$new(dims=rest_dim, dtype_base=dtype_base)
            return(array_type)
        }
    }
    else { ## just find the appropriate data type
        if(inherits(x, "data.frame")) {
            dtypes <- lapply(x, guess_dtype, ds_dim=ds_dim, scalar=FALSE, string_len=string_len)
            dtype <- H5T_COMPOUND$new(labels=names(x), dtypes=dtypes)
            return(dtype)
        }
        else if(inherits(x, "list")) {
            ## if each item is of the same class, this could be a ragged array
            dtype_ids <- vector("list", length=length(x))
            item_dim <- vector("list", length=length(x))
            for(i in seq_along(x)) {
                dtype_ids[[i]] <- guess_dtype(x[[i]], ds_dim=length(x[[i]]), scalar=FALSE, string_len=string_len)
                item_dim[[i]] <- guess_dim(x[[i]])
            }
            ## now check that they are all the same
            if(length(x) == 0) {
                stop("Empty list; can't guess datatype")
            }
            type_equal <- TRUE
            length_equal <- TRUE
            if(length(x) > 1) {
                for(i in 2:length(x)) {
                    if(!(dtype_ids[[1]]$equal(dtype_ids[[i]]))) {
                        type_equal <- FALSE
                    }
                    if(any(item_dim[[1]] != item_dim[[i]])) {
                        length_equal <- FALSE
                    }
                }
            }

            if(!type_equal & !length_equal) {
                stop("Found a list where neither the length nor the types are the same. Cannot match h5-datatype.")
            }
            if(!type_equal & length_equal) {
                ## if some of these are not identical - can make a compound object out of it
                ## if all lengths are the same, a regular compound object;
                ## for all intents and purposed, this is a data.frame
                attr(x, "class") <- "data.frame"
                attr(x, "row.names") <- 1:item_dim[[1]][1]
                return(guess_dtype(x, ds_dim=item_dim[[1]][1], scalar=scalar, string_len=string_len))
            }
            if(type_equal) {
                ## note; if the length are equal, we could handle it as a regular array; but for now we will do a
                ## variable length array
                dtype_base <- dtype_ids[[1]]
                return(H5T_VLEN$new(dtype_base=dtype_base))
            }
            
        }
        else if(inherits(x, "factor_ext")) {
            return(H5T_ENUM$new(labels=levels(x), values=values(x)))
        }
        else if(is.factor(x)) {
            return(H5T_ENUM$new(labels=levels(x)))
        }
        else if(is.character(x)) {
            if(string_len=="estimate") {
                string_len <- max(nchar(x)) + 1
            }
            return(H5T_STRING$new(type="c", size=string_len))
        }
        else if(is.logical(x)) {
            return(H5T_LOGICAL$new(include_NA=TRUE))
        }
        else if(is.integer64(x)) {
            return(h5types$H5T_NATIVE_LLONG)
        }
        else if(is.integer(x)) {
            return(h5types$H5T_NATIVE_INT)
        }
        else if(is.double(x)) {
            return(h5types$H5T_NATIVE_DOUBLE)
        }
        else if(is.complex(x)) {
            return(H5T_COMPLEX$new())
        }
        else if(inherits(x, "H5R")) {
            if(inherits(x, "H5R_OBJECT")) {
                return(h5types$H5T_STD_REF_OBJ)
            }
            else if(inherits(x, "H5R_DATASET_REGION")) {
                return(h5types$H5T_STD_REF_DSETREG)
            }
            else {
                stop("Unknown reference type")
            }
        }
        else {
            stop("unknown type")
        }
    }
    stop("the function should never have reached this place")
}


##' Guess the dataspace of an object
##'
##' Creates a dataspace that fits an R object so that it can be written into a dataset. This is used
##' for example in dataset creation based on an R-object, not a specifically defined dimensions.
##' @title Guess the dataspace of an object
##' @param x The R object for which to guess the space
##' @param dtype Object of type \code{\link{H5T}}, that represents that datatype to use.
##' @param chunked Is the datatype chunked? If yes, \code{maxdims} of the space will be set to infinity,
##' otherwise \code{maxdims} will be set to the original extent of the space.
##' @return An object of type \code{\link{H5S}}
##' @author Holger Hoefling
##' @export
guess_space <- function(x, dtype, chunked=TRUE) {
    ## if a datatype is given and it is an array, take out that part of the dimension guess
    x_dim <- guess_dim(x)

    dtype_dim <- NULL
    if(inherits(dtype, "H5T")) {
        if(dtype$get_class() == h5const$H5T_ARRAY) {
            dtype_dim <- dtype$get_array_dims()
        }
    }

    ## check if the dtype_dimensions fit the guessed dimensions
    space_dim <- x_dim
    dtype_rank <- length(dtype_dim)
    x_rank <- length(x_dim)
    if(dtype_rank > 0) {
        if(x_rank < dtype_rank) {
            stop("rank of x is smaller than rank of dtype_dim; types don't fit")
        }
        else if(x_rank == dtype_rank) {
            if(any(x_dim != dtype_dim)) {
                stop("dimensions of x and dtype are different")
            }
            else {
                space_dim <- 1
            }
        }
        else {
            space_dim <- x_dim[1:(x_rank-dtype_rank)]
        }
    }
  
    ## now create the appropriate space
    if(chunked) {
        maxdims=rep(Inf, length(space_dim))
    }
    else {
        maxdims <- space_dim
    }
    return(H5S$new(type="simple", dims=space_dim, maxdims=maxdims))
}

##' Guess the dimension of a chunk
##'
##' The size of the chunk in bytes is first divided by the size of the datatype, giving the number of elements
##' to be stored in each chunk. This is taken as a rough guideline. Then, the number of dimensions of the dataset is used.
##' By default, the chunk is assumed to have the same size in each dimension, yielding an initial guess.
##'
##' If the resulting chunk is larger than the entire dataset for a maximal dimension, this dimension of the chunk is reduced and
##' redistributed to the other dimensions.
##'
##' As a chunk is never allowed to be larger than the maximum dimension of the dataset itself, 
##' @title Guess the dimension of a chunk
##' @param space_maxdims Maximal dimensions of the dataset
##' @param dtype_size Size of the datatype that is stored
##' @param chunk_size Size of each chunk in bytes
##' @return An integer vector giving the dimension of the chunk
##' @author Holger Hoefling
##' @export
guess_chunks <- function(space_maxdims, dtype_size, chunk_size=getOption("hdf5r.chunk_size")) {
    chunk_num_elem <- floor(chunk_size / dtype_size)

    ## now, given the dimension of the space, decide on the dimension of the chunks
    ## each dimension is, if possible identical in chunk size
    ## if the total dimension is too small, they are redistributed to other dimensions
    ## if the whole space is too small, the first dimension is being increased
    space_rank <- length(space_maxdims)
    chunk_dim <- rep(ceiling(chunk_num_elem^(1/space_rank)), space_rank)

    chunk_dim <- pmin(space_maxdims, chunk_dim)
    bounded <- chunk_dim == space_maxdims
    while(prod(chunk_dim) < chunk_num_elem & !all(bounded)) {
        mult_factor <- (chunk_num_elem / prod(chunk_dim))^(1/ sum(!bounded))
        chunk_dim[!bounded] <- ceiling(chunk_dim[!bounded] * mult_factor)
        chunk_dim <- pmin(space_maxdims, chunk_dim)
        bounded <- chunk_dim == space_maxdims
    }

    return(chunk_dim)
}

##' Get the correct dimensions for a space and datatype
##'
##' This function uses the space and the selection in it to get the correct dimension
##' for the resulting object (but without dropping dimensions). Furthermore, if the
##' datatype is an array, those dimensions are correctly determined as well.
##'
##' Internal use only; currently unused
##' @title Extract the dimension of a space and datatype
##' @param space The space with the selection that was used to read the dataset
##' @param dtype The datatype of the dataset
##' @return \code{x}, but with a new dimension attribute
##' @author Holger Hoefling
##' @keywords internal
extract_dim <- function(space, dtype) {
    dtype_dim <- NULL
    if(inherits(dtype, "H5T")) {
        if(dtype$get_class() == h5const$H5T_ARRAY) {
            dtype_dim <- dtype$get_array_dims()
        }
    }

    ## check if the dtype_dimensions fit the guessed dimensions
    if(!space$is_simple()) {
        space_dim <- NULL
    }
    else {
        ## now we need to check what the dimension of the dataspace-selection is
        space_sel_type <- space$get_select_type()
        if(space_sel_type == h5const$H5S_SEL_HYPERSLABS) {
            nblocks <- space$get_select_hyper_nblocks()
            if(nblocks == 1) {
                blocklist <- space$get_select_hyper_blocklist()
                space_dim <- blocklist[2,] - blocklist[1,] + 1
            }
            else {## cannot infer easily the size of each dimension
                space_dim <- space$get_select_npoints()
            }
        }
        else if(space_sel_type == h5const$H5S_SEL_POINTS) {
            space_dim <- space$get_select_npoints()
        }
        else if(space_sel_type == h5const$H5S_SEL_ALL) {
            space_dim <- space$get_simple_extent_dims()$dims
        }
        else if(space_sel_type == h5const$H5S_SEL_NONE) {
            return(NULL)
        }
        else {
            stop("Unknown selection in space")
        }
    }

    all_dim <- as.integer(c(space_dim, dtype_dim))

    return(all_dim)
}


##' Reorder an array
##'
##' Reorders an array using a fast underlying c-function. It is implemented
##' for its simple generality and only intended for internal use in the package.
##' @title Reorder an array
##' @param x The array; doesn't have to have a dim attribute; is just assumed to be a vector
##' @param dims The dimensionality of the array
##' @param reorder_dim The dimension to reorder
##' @param new_order The new ordering of the reorder_dim; not checked for correctness; 1-based
##' @param item_size The size in bytes of each array item; not discovered automatically
##' @return The re-ordered array
##' @author Holger Hoefling
##' @keywords internal
array_reorder <- function(x, dims, reorder_dim, new_order, item_size) {
    pre_reorder_dims <- dims[seq_len(reorder_dim -1)]
    post_reorder_dims <- dims[reorder_dim + seq_len(length(dims) - reorder_dim)]

    ## item size is the number of items in the dimensions before the re-order times the size of each item
    item_size <- prod(pre_reorder_dims) * item_size
    num_rows <- dims[reorder_dim]
    num_cols <- prod(post_reorder_dims)

    return(.Call("R_reorder", x, num_rows, num_cols, item_size, new_order - 1, PACKAGE="hdf5r"))
}



##' Round-trip of converting data to HDF5 and back to R
##'
##' Take an R-object, convert it to HDF5, convert it back and return input, output and intermediate steps
##' This is mainly intended for use in tests.
##' @title Round-trip of converting data to HDF5 and back to R
##' @param Robj The object to convert
##' @param dtype The datatype to convert it into
##' @param nelem The number of elements in the object
##' @param flags conversion flags from HDF5 to R
##' @return A list with input, number of elements, raw vector for intermediate storage and output
##' @author Holger Hoefling
##' @keywords internal
convertRoundTrip <- function(Robj, dtype, nelem=length(Robj), flags=h5const$H5TOR_CONV_INT64_NOLOSS) {
    if(missing(nelem)) {
        if(!is.data.frame(Robj)) {
            nelem <- length(Robj)
        }
        else {
            nelem <- nrow(Robj)
        }
    }
    h5val_raw <- RToH5(Robj, dtype, nelem)
    retRobj <- H5ToR_Pre(dtype, nelem)
    dtype_size <- dtype$get_size()
    if(dtype_size==Inf) {
        dtype_size <- dtype$get_size(variable_as_inf=FALSE)
    }
    retRobj <- copyRVec(retRobj, h5val_raw, nelem * dtype_size);
    retRobj <- H5ToR_Post(retRobj, dtype, nelem, flags)
    return(list(input=Robj, nelem=nelem, h5val_raw=h5val_raw, output=retRobj))
}

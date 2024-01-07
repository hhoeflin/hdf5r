
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










###################################################
## UI for operating on groups and files
###################################################

##' Get the names of the items in the group or at the \code{/} root of the file
##'
##' Works similar to the regular \code{names} function for a list. The names of the items of either a
##' \code{\link{H5File}} at the root or a \code{\link{H5Group}} are returned as a character vector.
##' The items are then accessed, again similar to a list, using \code{[[}.
##' @title Get the names of the items in the group or at the \code{/} root of the file
##' @param x An object of class \code{\link{H5File}} or \code{\link{H5Group}}
##' @return A character vector with the names of the items in the group/file.
##' @author Holger Hoefling
##' @export
names.H5Group <- function(x) {
    link_access_pl <- h5const$H5P_DEFAULT
    ginfo <- x$group_info()
    nlinks <- ginfo$nlinks
    res <- character(nlinks)
    for(i in seq_len(nlinks)) {
        res[i] <- x$link_name_by_idx(i-1, ".", idx_type=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_INC,
                                     link_access_pl=link_access_pl)
    }
    return(res)
}

##' @rdname names.H5Group
##' @export
names.H5File <- names.H5Group

##' Retrieve object from a group of file
##'
##' Works similar to retrieving objects in a list. \code{x[["my_name"]]} retrieves object \code{my_name} from the
##' HDF5-File or HDF5-Group \code{x}.
##'
##' One can also assign objects under a not yet existing name. For either a  \code{\link{H5Group}} or \code{\link{H5D}},
##' a hard link is created. If it is a datatype, \code{\link{H5T}}, this is committed under the chosen name \code{name}.
##' @title Retrieve object from a group of file
##' @param x An object of class \code{\link{H5File}} or \code{\link{H5Group}}
##' @param name Name of the object to retrieve. Has to be a character vector of length one. No integer values allowed.
##' @param ... Currently ignored
##' @param link_access_pl An object of class \code{\link{H5P_LINK_ACCESS}}.
##' @param dataset_access_pl An object of class \code{\link{H5P_DATASET_ACCESS}}.
##' @param type_access_pl Currently always \code{h5const$H5P_DEFAULT}
##' @param value What to assign. Has to be one of \code{\link{H5Group}},  \code{\link{H5D}} or  \code{\link{H5T}}
##' @return A \code{\link{H5Group}},  \code{\link{H5D}} or  \code{\link{H5T}}, depending on the object saved in the group under
##' the requested name.
##' @author Holger Hoefling
##' @rdname H5Group_access
##' @name H5Group_access
##' @export
'[[.H5Group' <- function(x, name, ..., link_access_pl=h5const$H5P_DEFAULT, dataset_access_pl=h5const$H5P_DEFAULT, type_access_pl=h5const$H5P_DEFAULT) {
    if(x$exists(name)) {
        return(x$open(name=name, link_access_pl=link_access_pl, dataset_access_pl=dataset_access_pl, type_access_pl=type_access_pl))
    }
    else {
        stop(paste("An object with name", name, "does not exist in this group"))
    }
}

##' @rdname H5Group_access
##' @export
'[[.H5File' <- get("[[.H5Group")


##' @rdname H5Group_access
##' @export
'[[<-.H5Group' <- function(x, name, ..., value) {
    ## if a group is given, make a link
    ## if a dataset is given, make a link
    ## if another r-obj is given, create a dataset for that object and write it
    ## if the object already exists, just fail
    if(x$exists(name)) {
        ## it is a peculiarity of the way R works that when assigning attributes,
        ## as it is done by value, the resulting object is written over itself (with the attribute attached)
        ## so here, we need to check if the object being assigned is itself
        if(inherits(value, "H5File") || inherits(value, "H5Group") || inherits(value, "H5D") || inherits(value, "H5T")) {
            value_oinfo <- value$obj_info()
            x_oinfo <- x[[name]]$obj_info()
            if(identical(value_oinfo, x_oinfo)) {
                return(invisible(x))
            }
        }

        stop("Cannot assign - already exists. Please use the 'link_delete' to delete the object before assigning a new one")
    }
    if(inherits(value, "H5Group")) {
        x$link_create_hard(value, ".", name)
    }
    else if(inherits(value, "H5D")) {
        x$link(value, name)
    }
    else if(inherits(value, "H5T")) {
        x$commit(name, value)
    }
    else {
        x$create_dataset(name, value)
    }
    return(invisible(x))
}

##' @rdname H5Group_access
##' @export
'[[<-.H5File' <- get("[[<-.H5Group")

###################################################
## UI for working with arguments
###################################################

##' Interface for HDF5 attributes
##'
##' Implements high-level functions that allows interactions with HDF5-attributes in a way very similar to regular R-object attributes
##' in R are handled.
##' @title Interface for HDF5 attributes
##' @param x The object to which to attach the attribute to or retrieve it from. Can be one of \code{\link{H5Group}},  \code{\link{H5D}},
##' \code{\link{H5T}} or  \code{\link{H5File}}
##' @param which The name of the attribute to assign it to
##' @param value The value to assign to the attribute.
##' @return For \code{h5attributes}, a named list with the content of the attributes read out. For \code{h5attr_names},
##' a vector of names of the attributes attached to the object \code{x}. For \code{h5attr}, the content of the attribute and
##' for \code{h5attr<-}, the assignment, the original object to which the attributes are attached (so that chaining is possible).
##' @author Holger Hoefling
##' @export
h5attributes <- function(x) {
    ## return a list with the names and content of all attributes
    ## first get number of attributes; used deprecated attr_get_number;
    ## reason is that H5Oget_info can be slow on large datasets (but should be ok on files)
    if(inherits(x, "H5File")) {
        num_attrs <- x$obj_info()$num_attrs
    }
    else {
        num_attrs <- x$attr_get_number()
    }
    attr_data <- vector("list", length=num_attrs)
    names(attr_data) <- h5attr_names(x)

    for(i in seq_along(attr_data)) {
        attr_obj <- x$attr_open_by_idx(i - 1, ".")
        attr_data[[i]] <- attr_obj$read()
    }
    return(attr_data)
}

##' @rdname h5attributes
##' @export
h5attr_names <- function(x) {
    ## get the number of attributes
    ## first get number of attributes; used deprecated attr_get_number;
    ## reason is that H5Oget_info can be slow on large datasets (but should be ok on files)
    if(inherits(x, "H5File")) {
        num_attrs <- x$obj_info()$num_attrs
    }
    else {
        num_attrs <- x$attr_get_number()
    }
    attr_names <- character(num_attrs)
    for(i in seq_along(attr_names)) {
        attr_names[i] <- x$attr_name_by_idx(i - 1, ".")
    }
    return(attr_names)
}

##' @rdname h5attributes
##' @export
h5attr <- function(x, which) {
    if(!x$attr_exists_by_name(which, ".")) {
        stop("Attribute does not exist")
    }
    attr_obj <- x$attr_open_by_name(which, ".")
    return(attr_obj$read())
}

##' @rdname h5attributes
##' @export
'h5attr<-' <- function(x, which, value) {
    if(x$attr_exists_by_name(which, ".")) {
        ## if it already exists, delete it first
        ## to make sure that unused object get closed
        gc()
        x$attr_delete_by_name(which, ".")
    }
    attr_obj <- x$create_attr(which, robj=value)
    return(invisible(x))
}


###################################################
## UI for working with datasets
###################################################

##' Selecting and assigning subsets of HDF5-Spaces and HDF5-Datasets
##'
##' Used for subsetting HDF5-Datasets or HDF5-Spaces or for assigning data into HDF5-Datasets. There are some differences to
##' consider with R itself.
##'
##' Most importantly HDF5-COMPOUND objects only have a single dimension internally to HDF5 (a vector), but they correspond to R-data.frames,
##' which are 2 dimensional. For an HDF5 COMPOUND object, it is currently not possible to only sub-select a specific column.
##' All columns have to be extracted (using 1-dimensional access with \code{[} and can then be subset in R itself.
##' The same is true for writing a COMPOUND object (\code{\link{H5T_COMPOUND}}). A complete data-frame
##' is needed, not just a subset of the columns.
##'
##' Another important differences is for datasets of HDF5-ARRAY type \code{\link{H5T_ARRAY}}
##' where the access to the object is only for the dimension of the object itself, not including the dimensions of the underlying array type.
##' @title Selecting and assigning subsets of HDF5-Spaces and HDF5-Datasets
##' @param x The  \code{\link{H5S}} or \code{\link{H5D}} to subset or assign values to
##' @param d1 First dimension of the object
##' @param ... Used for other dimension of the object
##' @param op Operation to perform on the \code{\link{H5S}}. Look into the HDF5 online help
##' \url{https://portal.hdfgroup.org/display/HDF5/H5S_SELECT_ELEMENTS} and
##' \url{https://portal.hdfgroup.org/display/HDF5/H5S_SELECT_HYPERSLAB}
##' @param dataset_xfer_pl An object of class \code{\link{H5P_DATASET_XFER}}.
##' @param flags Some flags governing edge cases of conversion from HDF5 to R. This is related to how integers are being treated and
##' the issue of R not being able to natively represent 64bit integers and not at all being able to represent unsigned 64bit integers
##' (even using add-on packages). The constants governing this are part of \code{\link{h5const}}. The relevant ones start with the term
##' \code{H5TOR} and are documented there. The default set here returns a regular 32bit integer if it doesn't lead to an overflow
##' and returns a 64bit integer from the \code{bit64} package otherwise. For 64bit unsigned int that are larger than 64bit signed int,
##' it return a \code{double}. This looses precision, however. See also documentation or \code{\link{h5const}}.
##' @param value The value to assign to the dataset
##' @param drop Logical. When reading data, should dimensions of size 1 be dropped.
##' @param envir The environment in which the dimension indices \code{d1, ...} are to be evaluated. Usually the environment from
##' where the function is called
##' @return For \code{x} being a \code{\link{H5S}}, the same object is returned, but with the selection set as requested. For
##' \code{\link{H5D}} it retrieves the subset of data requested or sets the subset of data assigned, as for any n-dimensional array
##' in R.
##' @author Holger Hoefling
##' @name H5S_H5D_subset_assign
NULL

#' @rdname H5S_H5D_subset_assign
#' @export
subset_h5.H5S <- function(x,d1, ..., op=h5const$H5S_SELECT_SET, envir=parent.frame()) {
    args <- eval(substitute(alist(d1, ...)))

    return(x$subset(args=args, op=op, envir=envir))
}



#' @rdname H5S_H5D_subset_assign
#' @export
'[.H5S' <- subset_h5.H5S

#' @rdname H5S_H5D_subset_assign
#' @export
subset_h5.H5D <- function(x, d1, ..., dataset_xfer_pl=h5const$H5P_DEFAULT,
                          flags=getOption("hdf5r.h5tor_default"), drop=TRUE, envir=parent.frame()) {
    args <- eval(substitute(alist(d1, ...)))
    return(x$read(args=args, dataset_xfer_pl=dataset_xfer_pl, flags=flags, drop=drop, envir=envir))
}

#' @rdname H5S_H5D_subset_assign
#' @export
"[.H5D" <- subset_h5.H5D


#' @rdname H5S_H5D_subset_assign
#' @export
subset_assign_h5.H5D <- function(x, d1, ..., dataset_xfer_pl=h5const$H5P_DEFAULT, envir=parent.frame(), value) {
    args <- eval(substitute(alist(d1, ...)))
    return(x$write(args=args, value=value, dataset_xfer_pl=dataset_xfer_pl, envir=envir))
}

#' @rdname H5S_H5D_subset_assign
#' @export
"[<-.H5D" <- subset_assign_h5.H5D


###############################################################
# Helper functions for evaluating arguments
###############################################################

##' Apply a selection to a space
##'
##' Calls the respective stand-alone functions for point-selection or multiple hyperslab selection. The reason for not
##' calling a method of an R6 object is to make it more efficient and make it useable without creating a full R6 object.
##' @title Apply a selection to a space
##' @param space_id The space_id of the space to which to apply the selection to
##' @param selection The selection object of class \code{point_selection} or \code{hyperslab_selection}
##' @return NULL
##' @author Holger Hoefling
##' @keywords internal
apply_selection <- function(space_id, selection) {
    op <- h5const$H5S_SELECT_SET
    if(inherits(selection, "point_selection")) {
        standalone_H5S_select_elements(id=space_id, coord=selection, op=h5const$H5S_SELECT_SET, byrow=TRUE)
    }
    else if(inherits(selection, "hyperslab_selection")) {
        standalone_H5S_select_multiple_hyperslab(id=space_id, hyperslab_array=selection)
    }
    else {
        stop("Unknown selection type; needs to be of class point_selection of hyperslab_selection")
    }
    return(invisible(NULL))
}



##' Can arguments be interpreted as a scalar?
##'
##' Check if there is only one argument and if it is either empty
##' of of length 1 with value 1, i.e. can be interpreted as a scalar.
##' @title Can arguments be interpreted as a scalar?
##' @param args The arguments to check
##' @return Logical if the arguments can be interpreted as a scalar
##' @author Holger Hoefling
##' @keywords internal
are_args_scalar <- function(args) {
    if(length(args) != 1) {
        return(FALSE)
    }
    if(args[[1]]==bquote(expr=) || args[[1]] == 1) {
        return(TRUE)
    }
    else {
        return(FALSE)
    }
}


##' Check argument for known functions that encode a hyperslab
##'
##' Checks for the functions \code{:}, \code{seq} and \code{seq_len}
##' @title Check argument for known functions that encode a hyperslab
##' @param x The argument to check
##' @param envir The environment in which to evaluate the argument
##' @return A vector of length 4 describing start, count, stride and block if appropriate
##' @author Holger Hoefling
##' @keywords internal
check_arg_for_hyperslab_func <- function(x, envir) {
    res <- c(NA, NA, NA, NA)
    if(is.call(x)) {
        if(length(x) > 1) {
            for(i in 2:length(x)) {
                x[[i]] <- eval(x[[i]], envir=envir)
            }
        }
        if(x[[1]] == ":") {
            if(length(x) == 3) {
                if(x[[3]] < x[[2]]) {
                    stop("Retrieving hyperslabs in reverse order not supported")
                }
                start <- as.numeric(x[[2]])
                block <- as.numeric(x[[3]]) - start + 1
                res <- c(start, 1, 1, block)
            }
        }
        else if(x[[1]] == "seq_len") {
            res <- c(1, 1, 1, as.numeric(x[[2]]))
        }
        else if(x[[1]] == "seq") {
            if(length(x) >= 2 && (is.integer(x[[2]]) || is.numeric(x[[2]]))) {
                ## in both cases use a matching to seq.default, as the signatures are the same
                matched_call <- match.call.withDef(seq.default, x)
                if(is.null(matched_call$length.out)) {
                    length.out <- floor(((as.numeric(matched_call$to) - as.numeric(matched_call$from)) / as.numeric(matched_call$by)) + 1)
                }
                else {
                    length.out <- as.numeric(matched_call$length.out)
                }
                stride <- as.numeric(matched_call$by)
                start <- as.numeric(matched_call$from)
                if(stride==1) {
                    ## it is one block
                    res <- c(start, 1, stride, length.out)
                }
                else {
                    ## it is length.out blocks, each of length 1
                    res <- c(start, length.out, stride, 1)
                }
            }
        }
    }
    if(!is.na(res[[1]]) && res[[1]] <= 0) {
        res <- c(NA, NA, NA, NA)
    }
    return(res)
}


##' Evaluate if the arguments are regular for hyperslab use
##'
##' For each argument check if it can be used as a hyperslab, potentially after sorting and making unique.
##' @title Evaluate if the arguments are regular for hyperslab use
##' @param args The arguments input; if it was empty, then set to NULL
##' @param ds_dims The dimensions of the input dataset
##' @param envir The environment in which to evaluate the arguments
##' @param post_read Should the reshuffle be computed for post-read (then \code{TRUE}) or pre-write (then \code{FALSE})
##' @return A list with 2 parts; Evaluated arguments, regularity report and reshuffle indicators. Will be returned as a list
##' with components \code{args_in}, \code{args_point}, \code{is_hyperslab}, \code{hyperslab},
##' \code{needs_reshuffle}, code{reshuffle}, \code{result_dims_pre_shuffle}, \code{result_dims_post_shuffle}, \code{max_dims}
##' @author Holger Hoefling
##' @keywords internal
args_regularity_evaluation <- function(args, ds_dims, envir, post_read=TRUE) {
    ## check that the number of arguments is the same as the dataset dimension
    if(length(args) != length(ds_dims)) {
        stop("Number of arguments not equal to number of dimensions: ", length(args), " vs. ", length(ds_dims))
    }

    ## create the skeleton for the regularity report
    ## has columns: start, count, stride, block
    hyperslab <- matrix(rep(NA, length(args) * 4), ncol=4)
    colnames(hyperslab) <- c("start", "count", "stride", "block")

    is_hyperslab <- rep(FALSE, length(args))
    needs_reshuffle <- is_hyperslab
    args_in <- args
    args_point <- vector("list", length(args))
    result_dims_pre_shuffle <- numeric(length(args))
    result_dims_post_shuffle <- numeric(length(args))
    max_dims <- result_dims_pre_shuffle
    reshuffle <- args_point

    for(i in seq_along(args)) {
        cur_arg <- args[[i]]
        if(length(args[[i]]) == 1 && args[[i]]==quote(expr=)) {
            ## set to maximal hyperslab for this dimension
            res_hyper <- c(1, 1, 1, ds_dims[[i]])
        }
        else if(is.call(cur_arg)) {
            res_hyper <- check_arg_for_hyperslab_func(cur_arg, envir)
        }
        else {
            res_hyper <- c(NA, NA, NA, NA)
        }
        ## res_hyper contains the information if the argument can be interpreted as a hyperslab

        if(!any(is.na(res_hyper))) { ## is a hyperslab made from a function
            is_hyperslab[i] <- TRUE
            hyperslab[i,] <- res_hyper
            needs_reshuffle[i] <- FALSE
            result_dims_pre_shuffle[i] <- res_hyper[2] * res_hyper[4] # count * block
            result_dims_post_shuffle[i] <- res_hyper[2] * res_hyper[4] # count * block
            max_dims[i] <- res_hyper[1] + (res_hyper[2] - 1) * res_hyper[3] + res_hyper[4] - 1 # start + (count - 1) * stride + block - 1
        }
        else {
            cur_arg <- eval(cur_arg, envir=envir)
            if(is.logical(cur_arg)) {
                ## expand it as necessary and convert to an integer vector
                cur_arg <- seq_len(ds_dims[[i]])[cur_arg]
            }
            if(is.null(cur_arg)) {
                ## make it into a numeric of length 0
                cur_arg <- numeric(0)
            }
            if(is.numeric(cur_arg) || is.integer(cur_arg) || is.integer64(cur_arg)) {
                cur_arg <- as.numeric(cur_arg)
                ## check if it has length 0 or 1; these are special cases
                if(length(cur_arg) == 0) {
                    is_hyperslab[i] <- FALSE
                    needs_reshuffle[i] <- FALSE
                    args_point[[i]] <- cur_arg
                    result_dims_pre_shuffle[i] <- 0
                    result_dims_post_shuffle[i] <- 0
                    max_dims[i] <- -Inf
                }
                else if(length(cur_arg) == 1) {
                    is_hyperslab[i] <- TRUE
                    needs_reshuffle[i] <- FALSE
                    result_dims_pre_shuffle[i] <- 1
                    result_dims_post_shuffle[i] <- 1
                    hyperslab[i, ] <- c(cur_arg, 1, 1, 1)
                    max_dims[i] <- cur_arg
                }
                else {
                    ## check it is all positive, negative or a mixture of both
                    if(all(cur_arg < 0)) {
                        cur_arg <- seq_len(ds_dims[[i]])[cur_arg]
                    }
                    else if(!all(cur_arg > 0)) {
                        stop("In index ", i, " not all subscripts are either positive or negative")
                    }
                    ## then check if it can be written as a hyperslab
                    cur_arg_diff_unique <- unique(diff(cur_arg))
                    if(all(cur_arg_diff_unique > 0)) { ## strictly increasing
                        needs_reshuffle[i] <- FALSE
                        max_dims[i] <- cur_arg[length(cur_arg)]
                        result_dims_pre_shuffle[i] <- length(cur_arg)
                        result_dims_post_shuffle[i] <- length(cur_arg)
                        if(length(cur_arg_diff_unique) == 1) {
                            is_hyperslab[i] <- TRUE

                            if(cur_arg_diff_unique == 1) {
                                hyperslab[i, ] <- c(cur_arg[[1]], 1, 1, length(cur_arg))
                            }
                            else {
                                hyperslab[i, ] <- c(cur_arg[[1]], length(cur_arg), cur_arg_diff_unique, 1)
                            }
                        }
                        else {
                            ## can only be done as points, not as a hyperslab
                            is_hyperslab[i] <- FALSE
                            args_point[[i]] <- cur_arg
                        }
                    }
                    else { ## not strictly increasing, so sort and make unique
                        ## see if a sorting and making unique could make it into a hyperslab
                        sort_arg <- sort(unique.default(cur_arg))
                        needs_reshuffle[i] <- TRUE
                        if(post_read) {
                            reshuffle[[i]] <- match(cur_arg, sort_arg)
                            result_dims_pre_shuffle[i] <- length(sort_arg)
                            result_dims_post_shuffle[i] <- length(cur_arg)
                        }
                        else {
                            ## need to invalidate the first instance of anything that is duplicated
                            reshuffle[[i]] <- order(cur_arg)[!duplicated(cur_arg, fromLast=TRUE)]
                            ## length of pre and post are reversed here
                            result_dims_post_shuffle[i] <- length(sort_arg)
                            result_dims_pre_shuffle[i] <- length(cur_arg)

                        }

                        sort_arg_diff <- diff(sort_arg)
                        sort_arg_diff_unique <- unique(sort_arg_diff)
                        ## now same as before for the unsorted one
                        ## but as is sorted and unique, know already that it is non-decreasing
                        max_dims[i] <- sort_arg[length(sort_arg)]
                        if(length(sort_arg_diff_unique) == 1) {
                            is_hyperslab[i] <- TRUE

                            if(sort_arg_diff_unique == 1) {
                                hyperslab[i, ] <- c(sort_arg[[1]], 1, 1, length(sort_arg))
                            }
                            else {
                                hyperslab[i, ] <- c(sort_arg[[1]], length(sort_arg), sort_arg_diff_unique, 1)
                            }
                        }
                        else {
                            ## can only be done as points, not as a hyperslab
                            is_hyperslab[i] <- FALSE
                            args_point[[i]] <- sort_arg
                        }
                    }
                }
            }
            else {
                stop("Can't evaluate argument ", i)
            }
        }

    }
    return(list(args_in=args_in, args_point=args_point, is_hyperslab=is_hyperslab, hyperslab=hyperslab,
                result_dims_pre_shuffle=result_dims_pre_shuffle, result_dims_post_shuffle=result_dims_post_shuffle,
                max_dims=max_dims, needs_reshuffle=needs_reshuffle, reshuffle=reshuffle))
}

##' Single hyperslab dimension to explicit vector
##'
##' Uses the information of a hyperslab and turns it into an explicit vector.
##' @title Single hyperslab dimension to explicit vector
##' @param hyperslab a length 4 vector describing the start, count, stride and block component of a single dimension of a hyperslab
##' @return An explicit vector describing the points in the hyperslab dimension
##' @author Holger Hoefling
##' @keywords internal
hyperslab_to_points <- function(hyperslab) {
    stopifnot(length(hyperslab)==4 && is.numeric(hyperslab))
    ## c("start", "count", "stride", "block")
    if(hyperslab[[2]] == 1) { # only one block
        res <- (seq_len(hyperslab[[4]]) - 1) + hyperslab[[1]] 
    }
    else if(hyperslab[[4]] == 1) { # only blocks of size 1
        res <- ((seq_len(hyperslab[[2]]) - 1) * hyperslab[[3]]) + hyperslab[[1]]
    }
    else { # mixed; should not occur for us but will write function to handle this anyway
        ## doesn't need to be overly efficient
        res <- rep(seq_len(hyperslab[[4]]), times=hyperslab[[2]])
        ## now add it the stride component
        res <- res + rep((seq_len(hyperslab[[2]]) - 1) * hyperslab[[3]], each=hyperslab[[4]])
        res <- res + hyperslab[[1]] - 1
    }
    return(res)
}

##' Turn regulation evaluation into a selection for a space object
##'
##' Analyzes the results of the regularity evaluation of each dimension and checks if
##' it needs to be into a hyperslab-selection or a point-selection. A hyperslab selection will be chosen
##' whenever there are significantly less of it than the number of selected points. The ratio is determined
##' by the option \code{hdf5r.point_to_hyperslab_ratio}. If this is 1, then always hyperslabs will be used.
##' @title Turn regulation evaluation into a selection for a space object
##' @param reg_eval_res The result of the \code{args_regularity_evaluation} function
##' @return Returns an object with either the point-matrix or the hyperslab-selection array. The resulting object is
##' of class \code{point_selection} or \code{hyperslab_selection}.
##' @author Holger Hoefling
##' @keywords internal
regularity_eval_to_selection <- function(reg_eval_res) {
    ## first calculate how many points need to be selected and how many hyperslabs would need to be necesary
    num_points <- prod(reg_eval_res$result_dims_pre_shuffle)
    num_hyperslabs <- prod(reg_eval_res$result_dims_pre_shuffle[!reg_eval_res$is_hyperslab])

    ## trivially any selection can always be written as a concatenation of hyperslabs; so should be ever do a pointlist?
    ## likely pointlist more efficient in selection. Use hyperslabs only if we have X-fold fewer hyperslabs than datapoints
    ## here choose X as >= 4 for now
    if(num_hyperslabs == 0) {
        point_hyperslab_ratio <- 0
    }
    else {
        point_hyperslab_ratio <- num_points / num_hyperslabs
    }
    if(point_hyperslab_ratio >= getOption("hdf5r.point_to_hyperslabs_ratio")) {
        ## use a hyperslab
        sel_type <- "hyperslab_selection"
        ## make a 3-dimensional array, each 2 dimensional sub-array (in the third dimension) is a complete hyperslab description
        if(any(!reg_eval_res$is_hyperslab)) {
            ## not just 1 hyperslab
            point_grid <- expand_point_grid(reg_eval_res$args_point[!reg_eval_res$is_hyperslab])
            hyperslab_array <- array(0, dim=c(nrow(reg_eval_res$hyperslab), nrow(point_grid), 4))
            for(i in 1:4) {
                hyperslab_array[,,i] <- reg_eval_res$hyperslab[,i]
            }
            ## c("start", "count", "stride", "block")
            ## set the dimensions that are the point grid; those currently have NA in them
            hyperslab_array[!reg_eval_res$is_hyperslab, , 1] <- t(point_grid)
            hyperslab_array[!reg_eval_res$is_hyperslab, , 2] <- 1
            hyperslab_array[!reg_eval_res$is_hyperslab, , 3] <- 1
            hyperslab_array[!reg_eval_res$is_hyperslab, , 4] <- 1
        }
        else {
            hyperslab_array <- array(reg_eval_res$hyperslab, dim=c(nrow(reg_eval_res$hyperslab), 1, 4))
        }
        sel <- hyperslab_array
    }
    else {
        sel_type <- "point_selection"
        ## if there are any hyperslab dimensions, expand them to a point list
        args_point <- reg_eval_res$args_point
        if(any(reg_eval_res$is_hyperslab)) {
            for(i in which(reg_eval_res$is_hyperslab)) {
                args_point[[i]] <- hyperslab_to_points(reg_eval_res$hyperslab[i,])
            }
        }

        sel <- expand_point_grid(args_point)
    }
    return(structure(.Data=sel, class=sel_type))
}





##' Expand list of points for each dimension into a matrix of all combinations
##'
##' The function is similar to the \code{expand.grid} function
##' @title Expand list of points for each dimension into a matrix of all combinations
##' @param point_list A list of the points in each dimension to include
##' @return A matrix with every combination of points for each dimension
##' @author Holger Hoefling
##' @keywords internal
expand_point_grid <- function(point_list) {
    point_list_size <- unlist(lapply(point_list, length))
    cum_prod_std <- c(1, cumprod(point_list_size))
    cum_prod_rev <- rev(c(1, cumprod(rev(point_list_size))))
    num_points <- prod(point_list_size)
    point_mat <- matrix(numeric(num_points * length(point_list)), ncol=length(point_list))
    for(i in seq_along(point_list)) {
        point_mat[, i] <- rep(point_list[[i]], each=cum_prod_std[i], times=cum_prod_rev[i+1])
    }
    return(point_mat)
}





##' Match arguments in a call to function and add default values
##'
##' Given the definition of a function and a call, it matches the arguments
##' so that they are named and inserts any default argument values where
##' those are missing
##' @title Match arguments in a call to function and add default values
##' @param definition Definition of the function to match against
##' @param call The call that should be matched
##' @return A call with named arguments and default values
##' @author Holger Hoefling
##' @keywords internal
match.call.withDef <- function(definition, call) {
    def.formals <- formals(definition)
    foo <- try(as.list(match.call(definition = definition, call=call)), silent=TRUE)

    if(inherits(foo, "try-error")) {
        return(foo)
    }
    ## add the default arguments if they are missing
    for(v in names(def.formals)) {
        if(!(v %in% names(foo))) {
            foo <- c(foo, def.formals[v])
        }
    }
    return(foo)
}

##' Reshuffle the input as needed - see \code{args_regularity_evaluation}
##'
##' When necessary, this function performs the reshuffle as defined by \code{args_regularity_evaluation}.
##' @title Reshuffle the input as needed - see \code{args_regularity_evaluation}
##' @param x The array to reshuffle
##' @param reg_eval_res The result of the regularity evaluation
##' @return The reshuffled input
##' @author Holger Hoefling
##' @keywords internal
do_reshuffle <- function (x, reg_eval_res) {
    ## for the post read shuffle, we just have to use the order as noted in reg_eval_res
    ## however, data.frames have an additional dimension the evaluator currently
    ## does not know about, so have to add it
    if(inherits(x, "data.frame")) {
        if(length(reg_eval_res$needs_reshuffle) != 1) {
            stop("For data.frame, the selection can only have 1 dimension")
        }
        reorder_params <- rep(list(quote(expr=)), 2)
        if(reg_eval_res$needs_reshuffle) {
            reorder_params[1] <- reg_eval_res$reshuffle[1]
        }
    }
    else {
        reorder_params <- rep(list(quote(expr=)), length(reg_eval_res$reshuffle))

        reorder_params[reg_eval_res$needs_reshuffle] <- reg_eval_res$reshuffle[reg_eval_res$needs_reshuffle]
    }
    res <- do.call("[", c(list(x), reorder_params))
    return(res)
}


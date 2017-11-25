
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






## Helper function that installs a list of functions in a class
R6_set_list_of_items <- function(r6class, type, item_list, overwrite=FALSE) {
    if(is.null(names(item_list))) {
        stop("The item_list has to be named!")
    }
    for(i in seq_along(item_list)) {
        r6class$set(which=type, name=names(item_list)[i], value=item_list[[i]], overwrite=overwrite)
    }
    return(invisible(NULL))
}


check_pl <- function(x, class) {
    xlab <- deparse(substitute(x))
    if(!inherits(x, "H5P_DEFAULT") && !inherits(x, class)) {
        stop(paste0(xlab, " has to be 'H5P_DEFAULT' or of class '", class, "'"))
    }
    return(invisible(NULL))
}

check_class <- function(x, class) {
    xlab <- deparse(substitute(x))
    if(!inherits(x, class)) {
        stop(paste0(xlab, " has to be of class '", class, "'"))
    }
    return(invisible(NULL))
}

request_empty <- function(len) {
    x <- raw(len)
    class(x) <- "R_RToH5_empty"
    return(x)
}

str_dim <- function(x) {
    if(length(x) == 0) {
        return("")
    }
    return(paste("(", paste(x, collapse=", "), ")", sep=""))
}



##' Flatten a nested data.frame
##'
##' HDF5 Compounds allow for nesting. Correspondingly, nested data.frames are being produced.
##' This function flattens such a nested data.frame.
##'
##' For easier printing to the screen, it also allows for coercion of \code{\link{factor_ext}} to
##' character variables.
##' @title Flatten a nested data.frame
##' @param df The data.frame to flatten
##' @param factor_ext_to_char Should extended factor variables be converted to characters (mainly for easy printing)
##' @return A flattened \code{\link{data.frame}}
##' @author Holger Hoefling
##' @export
flatten_df <- function(df, factor_ext_to_char=FALSE) {
    out_df <- NULL
    for(i in seq_len(length(df))) {
        if(inherits(df[[i]], "data.frame")) {
            flattened_df <- flatten_df(df[[i]], factor_ext_to_char = factor_ext_to_char)
            names(flattened_df) <- paste(names(df)[i], names(flattened_df), sep=".")
            to_bind <- flattened_df
        }
        else if(factor_ext_to_char && inherits(df[[i]], "factor_ext")) {
            df[[i]] <- as.character(df[[i]])
            to_bind <- df[i]
        }
        else {
            to_bind <- df[i]
        }
        if(is.null(out_df)) {
            out_df <- to_bind
        }
        else {
            out_df <- cbind(out_df, to_bind)
        }
    }
    rownames(out_df) <- rownames(df)
    class(out_df) <- class(df)
    return(out_df)
}


##' Cleaning result of internal \code{_H5ls} function
##'
##' For every \code{*_success} item that is \code{FALSE}, the corresponding row of the data.frame will be set to NA.
##' @title Cleaning result of internal \code{R_H5ls} function
##' @param df The result of the C-function \code{R_H5ls}
##' @return A data frame with content that was not successfully gathered set to \code{NA} and \code{*_success} columns removed
##' @author Holger Hoefling
##' @keywords internal
clean_ls_df <- function(df) {
    if(is.null(df) || nrow(df) == 0) {
        return(df)
    }
    df <- within(df, {
        ## make them into logical for now, will drop them at the end
        link_success <- as.logical(link_success)
        obj_type_success <- as.logical(obj_type_success)
        group_success <- as.logical(group_success)
        dataset_success <- as.logical(dataset_success)
        type_success <- as.logical(type_success)
    })
    df <- within(df, {
        link[!link_success,] <- NA
        obj_type[!obj_type_success] <- NA
        num_attrs[!obj_type_success] <- NA
        group[!group_success,] <- NA
        dataset[!dataset_success,] <- NA
        committed_type[!type_success] <- NA
    })
    df$link_success <- NULL
    df$obj_type_success <- NULL
    df$group_success <- NULL
    df$dataset_success <- NULL
    df$type_success <- NULL
    class(df) <- c("data.frame_ext", class(df))
    return(df)
    
}


##' Print a data frame that includes extended factor objects
##'
##' The regular print function for data-frames has special methods built-in for factors so that
##' the label is printed instead of the constant. This function is intended to provide the same functionality
##' for data frames with extended factors, by adding the class \code{data.frame_ext} to the class vector.
##' @title Print a data frame with extended factor objects
##' @param x The \code{data.frame_ext} object to print; Is returned by ls from \code{\link{H5File}}
##' and \code{\link{H5Group}} and this function allows for petter printing of \code{\link{factor_ext}}
##' so that the label instead of the value is printed.
##' @param ... Parameters to be passed on directly to \code{\link{print.data.frame}}
##' @return The object to print itself, invisibly
##' @author Holger Hoefling
##' @export
print.data.frame_ext <- function(x, ...) {
    df_flat <- flatten_df(x, factor_ext_to_char = TRUE)
    print.data.frame(df_flat, ...)
    return(invisible(x))
}


##' Cycle through n-dimensional array indices
##'
##' Cycles through all indices of an n-dimensional array. The first dimension
##' moves fastest. The counter is 0-based and the output is 0-based as well.
##' @title Cycle through n-dimensional array indices
##' @param count The counter (0-based)
##' @param dims The sizes of the dimension
##' @return An integer vector of the same length as \code{dim}, with 0-based indices 
##' @author Holger Hoefling
##' @keywords internal
array_counter <- function(count, dims) {
    dims_prod_for_div <- c(1, cumprod(dims)[1:(length(dims) - 1)])

    return((count %/% dims_prod_for_div) %% dims)
    
}



##' Print the class and ID
##'
##' Used by the print-methods
##' @title Print the class and ID
##' @param obj The object for which to print the class and id
##' @param is_valid is the object valid
##' @return invisible NULL
##' @author Holger Hoefling
##' @keywords internal
print_class_id <- function(obj, is_valid) {
    myclass <- class(obj)[1]
    cat("Class: ", myclass, "\n", sep="")
    if(!is_valid) {
        cat("ID: Object invalid\n")
    }
    else {
        if(getOption("hdf5r.print_id")) {
            id_as_hex <- as_hex(obj$id)
            cat("ID: ", id_as_hex, "\n", sep="")
        }
    }
    return(invisible(NULL))
}

##' Print attributes
##'
##' Prints the names of the attributes up to a given maximum number
##' @title Print attributes
##' @param obj The obj for which to print the attributes
##' @param max_to_print Maximum number of attributes to print
##' @return Invisible NULL
##' @author Holger Hoefling
##' @keywords internal
print_attributes <- function(obj, max_to_print) {
    obj_attr_names <- h5attr_names(obj)
    if(length(obj_attr_names) > 0) {
        if(length(obj_attr_names) <= max_to_print) {
            cat("Attributes: ", paste(obj_attr_names, collapse=", "), "\n", sep="")
        }
        else {
            cat("Attributes: ", paste(obj_attr_names[seq_len(max_to_print)], collapse=", "),
                " ... < truncated at ", max_to_print, " out of ", length(obj_attr_names), ">\n", sep="")
        }
    }
    return(invisible(NULL))
}

##' Print listing
##'
##' Prints a smaller part of the \code{ls} output of an object, up to a maximum number
##' @title Print listing 
##' @param obj Object for which to print the listing
##' @param max_to_print Maximum number of listing items to print
##' @return Invisible NULL
##' @author Holger Hoefling
##' @keywords internal
print_listing <- function(obj, max_to_print) {
    listing <- obj$ls(recursive=FALSE, detailed=FALSE)
    listing <- listing[, c("name", "obj_type", "dataset.dims", "dataset.type_class")]
    if(nrow(listing) > 0) {
        cat("Listing:\n")
        if(nrow(listing) <= max_to_print) {
            print(listing, row.names=FALSE)
        }
        else {
            print(listing[seq_len(max_to_print),], row.names=FALSE)
            cat("< Printed ", max_to_print, ", out of ", nrow(listing), ">\n", sep="")
        }
    }
    return(invisible(NULL))
}

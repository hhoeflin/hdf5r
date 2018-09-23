

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



##' Return the version of the HDF5-API
##'
##' Return the version of the HDF5-API and print it to the screen if requested
##' @title Return the version of the HDF5-API
##' @param verbose Should the information be printed to the screen as well
##' @return Version of the underlying HDF5 API as a string
##' @author Holger Hoefling
##' @importFrom utils packageVersion
##' @include Helper_functions.R
##' @export
h5version <- function(verbose=TRUE) {
    h5api_libversion <- .Call("R_H5get_libversion", request_empty(1), request_empty(1), request_empty(1), PACKAGE='hdf5r')
    h5api_version <- paste(c(h5api_libversion$majnum, h5api_libversion$minnum, h5api_libversion$relnum), collapse=".")
    if(verbose) {
        cat("hdf5r version", as.character(packageVersion("hdf5r")),
            "with C-library HDF5 Version ", h5api_version, "\n", sep=" ")
    }
    return(h5api_version)
}

##' Trigger the HDF5 garbage collection
##'
##' This function triggers the HDF5 internal garbage collection. It is independent of the
##' R garbage collection and currently has to be triggered by hand.
##' @title Trigger the HDF5 garbage collection
##' @return Invisible  \code{NULL} 
##' @author  Holger Hoefling
##' @export
h5garbage_collect <- function() {
    res <- .Call("R_H5garbage_collect", PACKAGE="hdf5r")$return_val
    if(res < 0) {
        stop("Error during HDF5 garbage collection")
    }
    return(invisible(NULL))
}



##' Convert a double or integer to hex
##'
##' Converts a double or integer to hex. Contrary to the built-in \code{\link{format}},
##' this is done without any conversion of integers in double-format to integers in integer format.
##' @title Convert a double or integer to hex
##' @param x The integer or double vector to convert
##' @return Character string with the hex value
##' @author Holger Hoefling
##' @export
as_hex <- function(x) {
    return(paste0("0x", .Call("R_as_hex", x, PACKAGE="hdf5r")))
}


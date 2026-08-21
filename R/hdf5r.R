


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





##' @useDynLib hdf5r, .registration = TRUE
NULL



##' hdf5r: A package to provide an interface to hdf5 from R
##'
##' 
##' A package that allows to interface with the HDF5 C-library. Provides access to most of its
##' functionality from inside R using R6 classes. For more details please see the README at
##' the github page \url{https://github.com/hhoeflin/hdf5r}.
##' 
##' @keywords internal
##' @examples 
##' test_file <- tempfile(fileext=".h5")
##' file.h5 <- H5File$new(test_file, mode="w")
##' 
##' data(cars)
##' file.h5$create_group("test")
##' file.h5[["test/cars"]] <- cars
##' cars_ds <- file.h5[["test/cars"]]
##' h5attr(cars_ds, "rownames") <- rownames(cars)
##' 
##' # Close the file at the end
##' # the 'close' method closes only the file-id, but leaves object inside the file open
##' # This may prevent re-opening of the file. 'close_all' closes the file and all objects in it
##' file.h5$close_all()
##' # now re-open it 
##' file.h5 <- H5File$new(test_file, mode="r+")
##' 
##' # lets look at the content
##' file.h5$ls(recursive=TRUE)
##' 
##' cars_ds <- file.h5[["test/cars"]]
##' # note that for now tables in HDF5 are 1-dimensional, not 2-dimensional
##' mycars <- cars_ds[]
##' h5attr_names(cars_ds)
##' h5attr(cars_ds, "rownames")
##' 
##' file.h5$close_all()
"_PACKAGE"





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

.onLoad <- function(libname, pkgname) {
#    .Call("R_H5dont_atexit", PACKAGE="hdf5r")
    .Call("R_H5open", PACKAGE="hdf5r")
    .Call("R_H5error", PACKAGE = "hdf5r")
    ## initialize the C data types
    .Call("init_dtypes", PACKAGE="hdf5r")
    install_types_const(h5types, h5const)

    ## install some global options
    op <- options
    op.hdf5r <- list(
        hdf5r.chunk_size = 2^13,
        hdf5r.default_string_len = Inf,
        hdf5r.flush_on_write=TRUE,
        hdf5r.h5tor_default=h5const$H5TOR_CONV_INT64_NOLOSS,
        hdf5r.point_to_hyperslabs_ratio=4,
        hdf5r.print_id=FALSE
        )
    toset <- !(names(op.hdf5r) %in% names(op))
    if(any(toset)) options(op.hdf5r[toset])

    ## need to set the size of the ref_obj for use in functions
    ref_obj_size$H5R_OBJECT <- h5types$H5T_STD_REF_OBJ$get_size()
    ref_obj_size$H5R_DATASET_REGION <- h5types$H5T_STD_REF_DSETREG$get_size()

    # adapt function calls to new functions in version 1.10.3
    adapt_classes()
    
    return(invisible())
    
}

.onUnload <- function(libpath) {
    if(is.loaded("R_H5close", PACKAGE="hdf5r")) {
        ## first close all open files
        gc()
        obj_ids <- as.integer64(ls(envir=obj_tracker))
        for(i in seq_along(obj_ids)) {
            H5_close_any(obj_ids[i])
            rm_obj(obj_ids[i])
        }
        ## need to call gc to ensure that all those untracked objects are
        ## actually deleted and the open handles closed
        gc()
        ## close all open objects in hdf5
                                        #    print("Before closing library")
        .Call("R_H5close", PACKAGE="hdf5r")
                                        #    print(".onUnload finished")
    }
    return(invisible())
}



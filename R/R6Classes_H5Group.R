
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








##' Class for representing HDF5 groups
##' 
##' HDF5-Groups are essentially equivalent to directories in a file system. Inside the groups, other groups or datasets can
##' be created. For the most parts, groups behave like files, so please also look at the documentation of \code{H5File}.
##' 
##' @docType class
##' @importFrom R6 R6Class
##' @return Object of class \code{\link{H5Group}}. 
##' @export
##' @author Holger Hoefling
##' @examples
##' fname <- tempfile(fileext = ".h5")
##' file <- H5File$new(fname, mode = "a")
##' group <- file$create_group("testgroup")
##' group$print()
##' group$close()
##' file$close_all()
##' @aliases H5Group-class
H5Group <- R6Class("H5Group",
                   inherit=H5RefClass,
                   public=list(
                       #' @description Prints information for the group
                       #' @param ... ignored
                       #' @param max.attributes Maximum number of attribute names to print
                       #' @param max.listing Maximum number of ls-items to print
                       print=function(..., max.attributes=10, max.listing=10){

                           is_valid <- self$is_valid

                           print_class_id(self, is_valid)
                           if(is_valid) {
                               cat("Filename: ", normalizePath(self$get_filename(), mustWork=FALSE), "\n", sep="")
                               cat("Group: ", self$get_obj_name(), "\n", sep="")
                               print_attributes(self, max_to_print=max.attributes)
                               print_listing(self, max_to_print=max.listing)
                           }
                           return(invisible(self))
                       }
            
                       ),
                   active=list(
                       #' @field names Returns the names of the items in the group or at the root of the file
                       names=function(...) {
                            ## Placeholder only, so that roxygen has somewhere to attach the
                            ## documentation. The real binding is installed from commonFG_active
                            ## by the R6_set_list_of_items call below.
                           .NotYetImplemented()
                       }
                       ),
                   private=list(
                       closeFun=function(id) if(!is.na(id) && is.loaded("R_H5Gclose", PACKAGE="hdf5r")) {
                          invisible(.Call("R_H5Gclose", id, PACKAGE = "hdf5r"))}
                       ),
                   cloneable = FALSE
               )

R6_set_list_of_items(H5Group, "public", commonFG, overwrite=TRUE)
R6_set_list_of_items(H5Group, "active", commonFG_active, overwrite=TRUE)
R6_set_list_of_items(H5Group, "public", commonFGT, overwrite=TRUE)
R6_set_list_of_items(H5Group, "public", commonFGDT, overwrite=TRUE)
R6_set_list_of_items(H5Group, "public", commonFGDTA, overwrite=TRUE)


##' Wrap an HDF5-id in the appropriate class
##'
##' This particular factory dispatches ids that can be of type Group, Datatype of dataset (these are
##' id types that can be the result of opening an object. For datatypes, the \code{\link{H5T_factory}} exists that can be used
##' @title Wrap an HDF5-id in the appropriate class
##' @param id The id to wrap in an R6 object
##' @return An R6 object corresponding to the HDF5 internal class of the ID
##' @author Holger Hoefling
##' @keywords internal
H5GTD_factory <- function(id) {
    ## find out the type, then stick it into the correct R6 (or send to the next factory)
    res <- .Call("R_H5Iget_type", id, PACKAGE = "hdf5r")$return_val
    res <- as.character(res)
    if(res == "H5I_BADID") {
        stop("Can identify object")
    }
    obj <- switch(res, H5I_FILE=H5File$new(id), H5I_GROUP=H5Group$new(id), H5I_DATATYPE=H5T_factory(id), H5I_DATASET=H5D$new(id),
           stop(paste("Can't open an R6 class object for the given type", res)))
    return(obj)
}

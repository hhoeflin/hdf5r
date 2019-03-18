adapt_classes <- function() {
    ## in 1.10.3 new version of H5Oget_info was introduced, so that we now have
    ## to use H5Oget_info2 and we have a "fields" paramater now
    ## similarly for H5Oget_info_by_idx as well as H5Oget_info_by_name
    if(compareVersion(h5version(verbose=FALSE), "1.10.3") >= 0) {
        commonFG_adapt <- list(
            obj_info_by_idx=function(n, group_name=".", index_field=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE, remove_internal_use_only=TRUE) {
                "This function implements the HDF5-API function H5Oget_info_by_idx."
                "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5O_GET_INFO_BY_IDX} for details."
                if(group_name!="." && !self$exists(group_name)) {
                    stop(paste(group_name, " does not exist"))
                }

                if(remove_internal_use_only) {
                    fields <- bitwOr(h5const$H5O_INFO_BASIC, h5const$H5O_INFO_NUM_ATTRS)
                }
                else {
                    fields <- h5const$H5O_INFO_ALL
                }

                res <- .Call("R_H5Oget_info_by_idx2", self$id, group_name, index_field, order, n, request_empty(1),
                             fields, h5const$H5P_DEFAULT$id,
                             PACKAGE = "hdf5r")
                if(res$return_val < 0) {
                    stop("Could not retrieve object info by index")
                }
                
                return(res$oinfo)
            },
            obj_info_by_name=function(object_name, remove_internal_use_only=TRUE) {
                "This function implements the HDF5-API function H5Oget_info_by_name."
                "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5O_GET_INFO_BY_NAME} for details."
                
                if(!self$exists(object_name)) {
                    stop(paste(object_name, " does not exist"))
                }
                
                if(remove_internal_use_only) {
                    fields <- bitwOr(h5const$H5O_INFO_BASIC, h5const$H5O_INFO_NUM_ATTRS)
                }
                else {
                    fields <- h5const$H5O_INFO_ALL
                }
                
                res <- .Call("R_H5Oget_info_by_name2", self$id, object_name, request_empty(1),
                             fields, h5const$H5P_DEFAULT$id,
                             PACKAGE = "hdf5r")
                if(res$return_val < 0) {
                    stop("Could not retrieve object info by index")
                }
                return(res$oinfo)
            })
        
        commonFGDT_adapt <- list(
            obj_info=function(remove_internal_use_only=TRUE) {
                "This function implements the HDF5-API function H5Oget_info."
                "Please see the documentation at \\url{https://portal.hdfgroup.org/display/HDF5/H5O_GET_INFO} for details."
                
                                        # request all info; could also make this more efficient
                if(remove_internal_use_only) {
                    fields <- bitwOr(h5const$H5O_INFO_BASIC, h5const$H5O_INFO_NUM_ATTRS)
                }
                else {
                    fields <- h5const$H5O_INFO_ALL
                }
                res <- .Call("R_H5Oget_info2", self$id, request_empty(1), fields, PACKAGE = "hdf5r")
                if(res$return_val < 0) {
                    stop("Error getting object info")
                }
                return(res$oinfo)
            })

        ## now it needs to be inserted into all relevant classes
        ## in there it will overwrite the already existing functions with these newer ones
        R6_set_list_of_items(H5File, "public", commonFG_adapt, overwrite=TRUE)
        R6_set_list_of_items(H5Group, "public", commonFG_adapt, overwrite=TRUE)
        R6_set_list_of_items(H5File, "public", commonFGDT_adapt, overwrite=TRUE)
        R6_set_list_of_items(H5Group, "public", commonFGDT_adapt, overwrite=TRUE)
        R6_set_list_of_items(H5D, "public", commonFGDT_adapt, overwrite=TRUE)
        R6_set_list_of_items(H5T, "public", commonFGDT_adapt, overwrite=TRUE)
    }
}

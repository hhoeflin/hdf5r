
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





interface <- list(
    get_file_id=function() {
        "This function implements the HDF5-API function H5Iget_file_id."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5I.html#Identify-GetFileId} for details."

        fid <- .Call("R_H5Iget_file_id", self$id, PACKAGE="hdf5r")$return_val
        return(H5File$new(id=fid))
    },
    get_obj_type=function() {
        "This function implements the HDF5-API function H5Iget_type."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5I.html#Identify-GetType} for details."

        res <- .Call("R_H5Iget_type", self$id, PACKAGE="hdf5r")$return_val
        return(res)
    },
    get_ref=function() {
        "This function implements the HDF5-API function H5Iget_ref."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5I.html#Identify-GetRef} for details."

        res <- .Call("R_H5Iget_ref", self$id, PACKAGE="hdf5r")$return_val
        if(res < 0) {
            stop("Error retrieving refernce count")
        }
        return(res)
    },
    inc_ref=function() {
        "This function implements the HDF5-API function H5Iinc_ref."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5I.html#Identify-IncRef} for details."

        res <- .Call("R_H5Iinc_ref", self$id, PACKAGE="hdf5r")$return_val
        if(res < 0) {
            stop("Error retrieving refernce count")
        }
        return(invisible(self))
    },
    dec_ref=function() {
        "This function implements the HDF5-API function H5Idec_ref."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5I.html#Identify-DecRef} for details."

        res <- .Call("R_H5Idec_ref", self$id, PACKAGE="hdf5r")$return_val
        if(res < 0) {
            stop("Error retrieving refernce count")
        }
        return(invisible(self))
    }
    )

commonFG <- list(
    open=function(name, link_access_pl=h5const$H5P_DEFAULT, dataset_access_pl=h5const$H5P_DEFAULT, type_access_pl=h5const$H5P_DEFAULT) {
        "Opens groups, datasets or types using the appropriate HDF5-API functions. Please see the documentation at"
        "\\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Open} for datasets, "
        "\\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-Open} for types and "
        "\\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-Open} for general objects."

        if (length(name)!=1 || !is.character(name)) stop("'name' must be a character string of length 1")

        ## check the property lists and get their ids if they aren't already default
        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        check_pl(dataset_access_pl, "H5P_DATASET_ACCESS")
        check_pl(type_access_pl, "H5P_TYPE_ACCESS")

        if(self$exists(name, link_access_pl=link_access_pl)) {
            ## check if any of the other properties are set; if yes - use them
            if(dataset_access_pl$id != h5const$H5P_DEFAULT$id) {
                ## use specialized method as it seems to be a dataset
                oid <- .Call("R_H5Dopen", self$id, name, dataset_access_pl$id, PACKAGE = "hdf5r")$return_val
            }
            else if(type_access_pl$id != h5const$H5P_DEFAULT$id) {
                oid <- .Call("R_H5Topen2", self$id, name, type_access_pl$id, PACKAGE = "hdf5r")$return_val
            }
            else {
                oid <- .Call("R_H5Oopen", self$id, name, link_access_pl$id, PACKAGE = "hdf5r")$return_val
            }
            if(oid < 0) {
                stop("Error opening object")
            }
            return(H5GTD_factory(oid))
        }
        else {
            stop(paste("An object with name", name, "does not exist"))
        }
    },
    open_by_idx=function(n, group_name=".", index_type=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Oopen_by_idx."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-OpenByIdx} for details."

        if (length(group_name)!=1 || !is.character(group_name)) stop("'group_name' must be a character string of length 1")

        ## check the property lists and get their ids if they aren't already default
        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        if(group_name=="." || self$exists(group_name, link_access_pl=link_access_pl)) {
            ## check if any of the other properties are set; if yes - use them
            oid <- .Call("R_H5Oopen_by_idx", self$id, group_name, index_type, order, n, link_access_pl$id, PACKAGE = "hdf5r")$return_val
            if(oid < 0) {
                stop("Error opening object")
            }
            return(H5GTD_factory(oid))
        }
        else {
            stop(paste("An object with name", group_name, "does not exist"))
        }
    },
    ls=function(recursive=FALSE, detailed=FALSE, index_type=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE, link_access_pl=h5const$H5P_DEFAULT,
        dataset_access_pl=h5const$H5P_DEFAULT, type_access_pl=h5const$H5P_DEFAULT) {
        "Returns the contents of a file or group as a data.frame."

        ls_res <- .Call("R_H5ls", self$id, recursive, index_type, order, link_access_pl$id,
                        dataset_access_pl$id, type_access_pl$id, PACKAGE='hdf5r')$return_val
        ls_res <- clean_ls_df(ls_res)
        if(detailed) {
            return(ls_res)
        }
        else {
            ls_res <- flatten_df(ls_res)
            ls_res_summary <- ls_res[, c("name", "link.type", "object.type", "object.num_attrs", "group.nlinks", "group.mounted", "dataset.rank",
                                         "dataset.dims", "dataset.maxdims", "dataset.type_class", "dataset.space_class", "committed_type")]
            return(ls_res_summary)
        }
    },
    exists=function(name, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lexists."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-Exists} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        res <- .Call("R_H5Lexists", self$id, name, link_access_pl$id, PACKAGE = "hdf5r")$return_val
        if(res < 0) {
            stop("Error trying to ascertain if link exists")
        }
        return(res > 0)
    },
    path_valid=function(path, check_object_valid=TRUE) {
        "This function implements the HDF5-API function H5LTpath_valid."
        "Please see the documentation at \\url{https://support.hdfgroup.org/HDF5/doc/HL/RM_H5LT.html#H5LTpath_valid} for details."

        res <- .Call("R_H5LTpath_valid", self$id, path, check_object_valid, PACKAGE = "hdf5r")$return_val
        if(res < 0) {
            stop("Error trying to ascertain if path is valid")
        }
        return(res > 0)
    },
    link=function(obj, new_link_name, link_create_pl=h5const$H5P_DEFAULT, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Olink."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-Link} for details."

        if(!(inherits(obj, "H5D") || inherits(obj, "H5Group") || inherits(obj, "H5T"))) {
            stop("obj has to be a group, dataset or type")
        }

        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        check_pl(link_create_pl, "H5P_LINK_CREATE")
        herr <- .Call("R_H5Olink", obj$id, self$id, new_link_name, link_create_pl$id, link_access_pl$id, PACKAGE = "hdf5r")$return_val
        if(herr < 0) {
            stop("Error trying to create a new link")
        }
        return(invisible(self))
    },
    obj_copy_to=function(dst_loc, dst_name, src_name, object_copy_pl=h5const$H5P_DEFAULT, link_create_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Ocopy."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-Copy} for details."

        if(!(inherits(dst_loc, "H5File") || inherits(dst_loc, "H5Group"))) {
            stop("dst_loc has to be a file or group")
        }
        check_pl(link_create_pl, "H5P_LINK_CREATE")
        check_pl(object_copy_pl, "H5P_OBJECT_COPY")

        herr <- .Call("R_H5Ocopy", self$id, src_name, dst_loc$id, dst_name, object_copy_pl$id, link_create_pl$id, PACKAGE = "hdf5r")$return_val
        if(herr < 0) {
            stop("Error copying object")
        }
        return(invisible(self))
    },
    obj_copy_from=function(src_loc, src_name, dst_name, object_copy_pl=h5const$H5P_DEFAULT, link_create_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Ocopy."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-Copy} for details."

        if(!(inherits(src_loc, "H5File") || inherits(src_loc, "H5Group"))) {
            stop("src_loc has to be a file or group")
        }
        check_pl(link_create_pl, "H5P_LINK_CREATE")
        check_pl(object_copy_pl, "H5P_OBJECT_COPY")

        herr <- .Call("R_H5Ocopy", src_loc$id, src_name, self$id, dst_name, object_copy_pl$id, link_create_pl$id, PACKAGE = "hdf5r")$return_val
        if(herr < 0) {
            stop("Error copying object")
        }
        return(invisible(self))
    },
    obj_info_by_idx=function(n, group_name=".", index_field=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE, remove_internal_use_only=TRUE) {
        "This function implements the HDF5-API function H5Oget_info_by_idx."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-GetInfoByIdx} for details."
        if(group_name!="." && !self$exists(group_name)) {
            stop(paste(group_name, " does not exist"))
        }
        res <- .Call("R_H5Oget_info_by_idx", self$id, group_name, index_field, order, n, request_empty(1), h5const$H5P_DEFAULT$id,
                     PACKAGE = "hdf5r")
        if(res$return_val < 0) {
            stop("Could not retrieve object info by index")
        }

        if(remove_internal_use_only) {
            oinfo <- res$oinfo
            oinfo$meta_size <- NULL
            return(oinfo)
        }
        else {
            return(res$oinfo)
        }
    },
    obj_info_by_name=function(object_name, remove_internal_use_only=TRUE) {
        "This function implements the HDF5-API function H5Oget_info_by_name."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-GetInfoByName} for details."

        if(!self$exists(object_name)) {
            stop(paste(object_name, " does not exist"))
        }
        res <- .Call("R_H5Oget_info_by_name", self$id, object_name, request_empty(1), h5const$H5P_DEFAULT$id,
                     PACKAGE = "hdf5r")
        if(res$return_val < 0) {
            stop("Could not retrieve object info by index")
        }
        if(remove_internal_use_only) {
            oinfo <- res$oinfo
            oinfo$meta_size <- NULL
            return(oinfo)
        }
        else {
            return(res$oinfo)
        }
    },
    group_info=function() {
        "This function implements the HDF5-API function H5Gget_info."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-GetInfo} for details."

        res <- .Call("R_H5Gget_info", self$id, request_empty(1), PACKAGE = "hdf5r")
        if(res$return_val < 0) {
            stop("Error getting object info")
        }
        return(res$ginfo)
    },
    group_info_by_name=function(name, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Gget_info_by_name."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-GetInfoByName} for details."

        res <- .Call("R_H5Gget_info_by_name", self$id, name, request_empty(1), link_access_pl$id,
                     PACKAGE = "hdf5r")
        if(res$return_val < 0) {
            stop("Could not retrieve object info by index")
        }
        return(res$ginfo)
    },
    group_info_by_idx=function(n, group_name=".",  index_field=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE,
        link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Gget_info_by_idx."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-GetInfoByIdx} for details."

        if(group_name!="." && !self$exists(group_name)) {
            stop(paste(group_name, " does not exist"))
        }
        res <- .Call("R_H5Gget_info_by_idx", self$id, group_name, index_field, order, n, request_empty(1), link_access_pl$id,
                     PACKAGE = "hdf5r")
        if(res$return_val < 0) {
            stop("Could not retrieve object info by index")
        }
        return(res$ginfo)
    },
    create_group=function(name, link_create_pl=h5const$H5P_DEFAULT, group_create_pl=h5const$H5P_DEFAULT,
        group_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Gcreate2 and H5Gcreate_anon (if name is NULL). Please see the documentation at"
        "\\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-Create2} for regular groups and"
        "\\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5G.html#Group-CreateAnon} for anonymous groups for details."

        if(!(is.null(name) || is.character(name))) {
            stop("name has to be NULL or a character vector")
        }
        if(length(name) > 1) {
            stop("name has to be of length at most 1")
        }

        check_pl(link_create_pl, "H5P_LINK_CREATE")
        check_pl(group_create_pl, "H5P_GROUP_CREATE")
        check_pl(group_access_pl, "H5P_GROUP_ACCESS")

        if(length(name)==0) { ## create anonymous group
            id <- .Call("R_H5Gcreate_anon", self$id, group_create_pl$id, group_access_pl$id, PACKAGE = "hdf5r")$return_val
        }
        else {
            id <- .Call("R_H5Gcreate2", self$id, name, group_create_pl$id, link_create_pl$id, group_access_pl$id, PACKAGE = "hdf5r")$return_val
        }
        if(id < 0) {
            stop("Error when creating group")
        }
        return(H5Group$new(id))
    },
    create_dataset=function(name, robj=NULL, dtype=NULL, space=NULL, chunk_dims="auto", gzip_level=4,
        link_create_pl=h5const$H5P_DEFAULT, dataset_create_pl=h5const$H5P_DEFAULT, dataset_access_pl=h5const$H5P_DEFAULT) {
        "This function is the main interface to create a new dataset. Its parameters allow for customization of the default"
        "behaviour, i.e. in order to get a specific datatype, a certain chunk size or dataset dimensionality."
        "Also note that this function implements the HDF5-API function H5Dcreate2 and H5Dcreate_anon (if name is NULL). Please see the documentation at"
        "\\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-Create2} for regular groups and"
        "\\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5D.html#Dataset-CreateAnon} for anonymous groups for details."
        "@param name The name of the new dataset. If missing, an anonymous dataset is created"
        "@param robj An R-object to take as a template for creating the dataset. Either \\code{robj} or both \\code{dtype} and {space}"
        "have to be provided"
        "@param dtype The datatype to use for the creation of the object. Can be null if \\code{robj} is given."
        "@param space The space to use for the object creation. Can be null if \\code{robj} is given. Otherwise an object of type \\code{H5S-class} which specifies the dimensions of the dataset."
        "@param chunk_dims Size of the chunk. Has to have the same length as the dataset dimension. If \\code{\"auto\"}"
        "then the size of each chunk is estimated so that each chunk is roughly as large in bytes as the value in"
        "the \\code{hdf5r.chunk_size} option. See also \\code{\\link{guess_chunks}} for a more detailed explanation."
        "@param gzip_level Only if \\code{chunk_dims} is not null. If given, then the \\code{dataset_create_pl} is set to enable zipping"
        "at the level given here. If set to NULL, then gzip is not set (but could be set otherwise in \\code{dataset_create_pl}"
        "@param link_create_pl Link creation property list. See \\code{\\link{H5P_LINK_CREATE-class}}"
        "@param dataset_create_pl Datatset creation property list. See \\code{\\link{H5P_DATASET_CREATE-class}}"
        "@param dataset_access_pl Dataset access property list. See \\code{\\link{H5P_DATASET_ACCESS-class}}"


        if(missing(name)) {
            name <- character(0)
        }
        else {
            if(self$exists(name)) {
                stop(paste("Can't create dataset", name, "- already exists!"))
            }
        }
        ## check that all parameters are of the expected type
        if(!is.character(name) && !is.null(name)) {
            stop("Name has to be a character vector or null")
        }
        if(length(name) > 1) {
            stop("name has to be of length at most 1")
        }

        ## adapt dtype, space as necessary
        if(is.null(robj) && (is.null(dtype) || is.null(space))) {
            stop("If a sample robj is not provided, both dtype and space have to be given")
        }
        if(is.null(dtype)) {
            dtype <- guess_dtype(x=robj, scalar=FALSE, string_len=Inf)
        }
        if(is.null(space)) {
            if(!is.null(chunk_dims)) {
                space <- guess_space(x=robj, dtype=dtype, chunked=TRUE)
            }
            else {
                space <- guess_space(x=robj, dtype=dtype, chunked=FALSE)
            }
        }

        ## now manipulate the dataset_create_pl
        if(!is.null(chunk_dims)) {
            if(dataset_create_pl$id == h5const$H5P_DEFAULT$id) {
                dataset_create_pl <- H5P_DATASET_CREATE$new()
            }
            else {
                dataset_create_pl <- dataset_create_pl$copy()
            }
            if(length(chunk_dims) == 1 && chunk_dims=="auto") {
                if(inherits(dtype, "H5T_STRING")) {
                    dtype_size <- dtype$get_size(variable_as_inf=FALSE)
                }
                else {
                    dtype_size <- dtype$get_size()
                }
                space_extent <- space$get_simple_extent_dims()
                chunk_dims <- guess_chunks(space_maxdims=space_extent$maxdims, dtype_size=dtype_size)
            }
            ## check that chunk_dims has the same rank as space
            if(!space$is_simple()) {
                stop("When chunking is enable, the space has to be simple")
            }
            space_rank <- space$get_simple_extent_ndims()
            if(space_rank != length(chunk_dims)) {
                stop(paste("The length of the chunk_dims is", length(chunk_dims), "and has to be the same as the rank of the space", space_rank))
            }
            dataset_create_pl$set_chunk(chunk_dims)
            if(!is.null(gzip_level)) {
                if(0 > gzip_level || gzip_level > 9) {
                    stop(paste("gzip_level has to be between 0 and 9, but is", gzip_level))
                }
                dataset_create_pl$set_deflate(gzip_level)
            }
        }

        check_class(dtype, "H5T")
        check_class(space, "H5S")
        check_pl(link_create_pl, "H5P_LINK_CREATE")
        check_pl(dataset_create_pl, "H5P_DATASET_CREATE")
        check_pl(dataset_access_pl, "H5P_DATASET_ACCESS")

        if(is.character(name) && length(name)==1) {
            id <- .Call("R_H5Dcreate2", self$id, name, dtype$id, space$id, link_create_pl$id, dataset_create_pl$id,
                        dataset_access_pl$id, PACKAGE="hdf5r")$return_val
        }
        else if(length(name)==0) {
            id <- .Call("R_H5Dcreate_anon", self$id, dtype$id, space$id,  dataset_create_pl$id,
                        dataset_access_pl$id, PACKAGE="hdf5r")$return_val
        }
        else {
            stop("This should not have happened! name has to be character or null")
        }
        if(id < 0) {
            stop("An error occured creating the dataset")
        }
        ds <- H5D$new(id)
        if(!is.null(robj)) {
            ## need to write the sample object data
            ds$write_low_level(robj)
        }
        return(invisible(ds))
    },
    commit=function(name, dtype, link_create_pl=h5const$H5P_DEFAULT, type_create_pl=h5const$H5P_DEFAULT,
        type_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Tcommit2."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5T.html#Datatype-Commit2} for details."

        if(missing(name)) {
            name <- character(0)
        }
        ## check that all parameters are of the expected type
        if(!is.character(name) && !is.null(name)) {
            stop("Name has to be a character vector or null")
        }
        if(length(name) > 1) {
            stop("name has to be of length at most 1")
        }

        check_pl(link_create_pl, "H5P_LINK_CREATE")
        check_pl(type_create_pl, "H5P_TYPE_CREATE")
        check_pl(type_access_pl, "H5P_TYPE_ACCESS")

        if(is.character(name) && length(name)==1) {
            herr <- .Call("R_H5Tcommit2", self$id, name, dtype$id, link_create_pl$id, type_create_pl$id,
                        type_access_pl$id, PACKAGE="hdf5r")$return_val
        }
        else if(length(name)==0) {
            herr <- .Call("R_H5Tcommit_anon", self$id, dtype$id, type_create_pl$id,
                        type_access_pl$id, PACKAGE="hdf5r")$return_val
        }
        else {
            stop("This should not have happened! name has to be character or null")
        }
        if(herr < 0) {
            stop("An error occured creating the dataset")
        }
        return(invisible(dtype))

    },
    ## functions around the link interface
    link_create_hard=function(obj_loc, obj_name, link_name, link_create_pl=h5const$H5P_DEFAULT, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lcreate_hard."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-CreateHard} for details."

        if(!(inherits(obj_loc, "H5File") || inherits(obj_loc, "H5Group"))) {
            stop("src_loc has to be a file or group")
        }
        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        check_pl(link_create_pl, "H5P_LINK_CREATE")

        herr <- .Call("R_H5Lcreate_hard", obj_loc$id, obj_name, self$id, link_name, link_create_pl$id,
                      link_access_pl$id, PACKAGE="hdf5r")$return_val
        if(herr < 0) {
            stop(paste("Error creating hard link for object", obj_name, "with link_name", link_name))
        }
        return(invisible(self))
    },
    link_create_soft=function(target_path, link_name, link_create_pl=h5const$H5P_DEFAULT, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lcreate_soft."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-CreateSoft} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        check_pl(link_create_pl, "H5P_LINK_CREATE")

        herr <- .Call("R_H5Lcreate_soft", target_path, self$id, link_name, link_create_pl$id,
                      link_access_pl$id, PACKAGE="hdf5r")$return_val
        if(herr < 0) {
            stop(paste("Error creating soft link for path", target_path, "with link_name", link_name))
        }
        return(invisible(self))

    },
    link_create_external=function(target_filename, target_obj_name, link_name, link_create_pl=h5const$H5P_DEFAULT,
        link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lcreate_external."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-CreateExternal} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        check_pl(link_create_pl, "H5P_LINK_CREATE")

        herr <- .Call("R_H5Lcreate_external", target_filename, target_obj_name, self$id, link_name, link_create_pl$id,
                      link_access_pl$id, PACKAGE="hdf5r")$return_val
        if(herr < 0) {
            stop(paste("Error creating external link for file", target_filename, "with target object", target_obj_name, " and link_name", link_name))
        }
        return(invisible(self))

    },
    link_exists=function(name, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lexists."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-Exists} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        htri <- .Call("R_H5Lexists", self$id, name, link_access_pl$id, PACKAGE="hdf5r")$return_val
        if(htri < 0) {
            stop(paste("Error verifying existence of link", name))
        }
        return(as.logical(htri))
    },
    link_move_from=function(src_loc, src_name, dst_name, link_create_pl=h5const$H5P_DEFAULT, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lmove."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-Move} for details."

        if(!(inherits(src_loc, "H5File") || inherits(src_loc, "H5Group"))) {
            stop("src_loc has to be a file or group")
        }
        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        check_pl(link_create_pl, "H5P_LINK_CREATE")

        herr <- .Call("R_H5Lmove", src_loc$id, src_name, self$id, dst_name, link_create_pl$id, link_access_pl$id, PACKAGE = "hdf5r")$return_val
        if(herr < 0) {
            stop("Error copying object")
        }
        return(invisible(self))

    },
    link_move_to=function(dst_loc, dst_name, src_name, link_create_pl=h5const$H5P_DEFAULT, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lmove."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-Move} for details."

        if(!(inherits(dst_loc, "H5File") || inherits(dst_loc, "H5Group"))) {
            stop("src_loc has to be a file or group")
        }
        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        check_pl(link_create_pl, "H5P_LINK_CREATE")

        herr <- .Call("R_H5Lmove", self$id, src_name, dst_loc$id, dst_name, link_create_pl$id, link_access_pl$id, PACKAGE = "hdf5r")$return_val
        if(herr < 0) {
            stop("Error copying object")
        }
        return(invisible(self))

    },
    link_copy_from=function(src_loc, src_name, dst_name, link_create_pl=h5const$H5P_DEFAULT, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lcopy."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-Copy} for details."

        if(!(inherits(src_loc, "H5File") || inherits(src_loc, "H5Group"))) {
            stop("src_loc has to be a file or group")
        }
        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        check_pl(link_create_pl, "H5P_LINK_CREATE")

        herr <- .Call("R_H5Lcopy", src_loc$id, src_name, self$id, dst_name, link_create_pl$id, link_access_pl$id, PACKAGE = "hdf5r")$return_val
        if(herr < 0) {
            stop("Error copying object")
        }
        return(invisible(self))

    },
    link_copy_to=function(dst_loc, dst_name, src_name, link_create_pl=h5const$H5P_DEFAULT, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lcopy."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-Copy} for details."

        if(!(inherits(dst_loc, "H5File") || inherits(dst_loc, "H5Group"))) {
            stop("src_loc has to be a file or group")
        }
        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        check_pl(link_create_pl, "H5P_LINK_CREATE")

        herr <- .Call("R_H5Lcopy", self$id, src_name, dst_loc$id, dst_name, link_create_pl$id, link_access_pl$id, PACKAGE = "hdf5r")$return_val
        if(herr < 0) {
            stop("Error copying object")
        }
        return(invisible(self))

    },
    link_delete=function(name, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Ldelete."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-Delete} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        herr <- .Call("R_H5Ldelete", self$id, name, link_access_pl$id, PACKAGE="hdf5r")$return_val
        if(herr < 0) {
            stop(paste("Error deleting link", name))
        }
        return(invisible(self))

    },
    link_delete_by_idx=function(n, group_name=".", index_field=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE,
        link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Ldelete_by_idx."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-DeleteByIdx} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        if(group_name!="." && !self$exists(group_name)) {
            stop(paste(group_name, " does not exist"))
        }

        herr <- .Call("R_H5Ldelete_by_idx", self$id, group_name, index_field, order, n, link_access_pl$id, PACKAGE="hdf5r")$return_val
        if(herr < 0) {
            stop(paste("Error deleting link number", n, "in group", group_name))
        }
        return(invisible(self))

    },
    link_info=function(name, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lget_info."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-GetInfo} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        res <- .Call("R_H5Lget_info", self$id, name, request_empty(1), link_access_pl$id, PACKAGE="hdf5r")
        if(res$return_val < 0) {
            stop(paste("Error getting info for link", name))
        }
        return(res$linfo)
    },
    link_info_by_idx=function(n, group_name=".", index_field=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE,
        link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lget_info_by_idx."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-GetInfoByIdx} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        if(group_name!="." && !self$exists(group_name)) {
            stop(paste(group_name, " does not exist"))
        }

        res <- .Call("R_H5Lget_info_by_idx", self$id, group_name, index_field, order, n, request_empty(1),
                      link_access_pl$id, PACKAGE="hdf5r")
        if(res$return_val < 0) {
            stop(paste("Error getting info for link number", n, "in group", group_name))
        }
        return(res$linfo)
    },
    link_value=function(name, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lget_val."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-GetVal} for details."

        ## first check if it is a soft or external link, otherwise return NA
        linfo <- self$link_info(name=name, link_access_pl=link_access_pl)
        if(!(as.character(linfo$type) %in% c("H5L_TYPE_SOFT", "H5L_TYPE_EXTERNAL"))) {
            return(NA)
        }
        ## first get the link-value; then unpack if necessary
        buffer <- raw(linfo$u$address) ## isn't the haddr, is the size_val; as it is a union, has been dropped
        res <- .Call("R_H5Lget_val", self$id, name, buffer, linfo$u$address, link_access_pl$id, FALSE, PACKAGE="hdf5r")
        if(res$return_val < 0) {
            stop(paste("Error retrieving link value of link", name))
        }
        if(as.character(linfo$type) == "H5L_TYPE_SOFT") {
            ## link is a character vector
            val <- rawToChar(res$buf)
            return(val)
        }
        else { ## external
            ## needs to be unpacked
            ## can do this here; just 2 null terminated strings; have it as raw, so just unpack it
            buffer <- res$buf
            string_ends <- which(buffer==0)
            if(length(string_ends) != 3) {
                stop("Expected 2 strings with a null at the beginning; received more")
            }
            file_name <- rawToChar(buffer[2:string_ends[2]])
            obj_name <- rawToChar(buffer[(string_ends[2] + 1):string_ends[3]])
            return(list(file_name=file_name, obj_name=obj_name))
        }
    },
    link_value_by_idx=function(n, group_name=".", index_field=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE,
        link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lget_val_by_idx."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-GetValByIdx} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        if(group_name!="." && !self$exists(group_name)) {
            stop(paste(group_name, " does not exist"))
        }

        linfo <- self$link_info_by_idx(n=n, group_name=group_name, index_field=index_field, order=order, link_access_pl=link_access_pl)
        if(!(as.character(linfo$type) %in% c("H5L_TYPE_SOFT", "H5L_TYPE_EXTERNAL"))) {
            return(NA)
        }
        ## first get the link-value; then unpack if necessary
        buffer <- raw(linfo$u$address) ## isn't the haddr, is the size_val; as it is a union, has been dropped
        res <- .Call("R_H5Lget_val_by_idx", self$id, group_name, index_field, order, n, buffer, linfo$u$address,
                     link_access_pl$id, FALSE, PACKAGE="hdf5r")
        if(res$return_val < 0) {
            stop(paste("Error retrieving link value of link", name))
        }
        if(as.character(linfo$type) == "H5L_TYPE_SOFT") {
            ## link is a character vector
            val <- rawToChar(res$buf)
            return(val)
        }
        else { ## external
            ## needs to be unpacked
            ## can do this here; just 2 null terminated strings; have it as raw, so just unpack it
            buffer <- res$buf
            string_ends <- which(buffer==0)
            if(length(string_ends) != 3) {
                stop("Expected 2 strings with a null at the beginning; received more")
            }
            file_name <- rawToChar(buffer[2:string_ends[2]])
            obj_name <- rawToChar(buffer[(string_ends[2] + 1):string_ends[3]])
            return(list(file_name=file_name, obj_name=obj_name))
        }

    },
    link_name_by_idx=function(n, group_name, idx_type=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Lget_name_by_idx."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5L.html#Link-GetNameByIdx} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        if(group_name!="." && !self$exists(group_name)) {
            stop(paste(group_name, " does not exist"))
        }
        name_size <- .Call("R_H5Lget_name_by_idx", self$id, group_name, idx_type, order, n, character(0), 0,
                           link_access_pl$id, PACKAGE="hdf5r")$return_val
        char_buf <- paste(rep(" ", name_size+1), collapse="")
        res <- .Call("R_H5Lget_name_by_idx", self$id, group_name, idx_type, order, n, char_buf, name_size+1,
                     link_access_pl$id, PACKAGE="hdf5r")

        if(res$return_val < 0) {
            stop("Problem getting name of link by index")
        }
        return(res$name)

    },
    mount=function(name, child) {
        "This function implements the HDF5-API function H5Fmount."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Mount} for details."
        if(!is.character(name) || length(name) != 1) {
            stop("name has to be a character vector of length 1")
        }
        ## check that name actually exists
        if(!self$path_valid(name)) {
            stop(paste("path", name, "does not exist"))
        }
        check_class(child, "H5File")
        file_mount_pl <- h5const$H5P_DEFAULT
        res <- .Call("R_H5Fmount", self$id, name, child$id, file_mount_pl$id, PACKAGE="hdf5r")$return_val
        if(res <- 0) {
            stop("Error mounting file onto group")
        }
        return(self$open(name))
    },
    unmount=function(name) {
        "This function implements the HDF5-API function H5Funmount."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Unmount} for details."
        if(!is.character(name) || length(name) != 1) {
            stop("name has to be a character vector of length 1")
        }
        ## check that name actually exists
        if(!self$path_valid(name)) {
            stop(paste("path", name, "does not exist"))
        }
        res <- .Call("R_H5Funmount", self$id, name, PACKAGE="hdf5r")$return_val
        if(res <- 0) {
            stop("Error mounting file onto group")
        }
        return(self)
    }
    )




commonFG_active <- list(
        names=function(link_access_pl=h5const$H5P_DEFAULT) {
        "Returns the names of the items in the group or at the root of the file"
        "@param link_access_pl The link-access property list. See \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5P.html} for more detail."
        ginfo <- self$group_info()
        nlinks <- ginfo$nlinks
        res <- character(nlinks)
        for(i in seq_len(nlinks)) {
            res[i] <- self$link_name_by_idx(i-1, ".", idx_type=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_INC,
                                         link_access_pl=link_access_pl)
        }
        return(res)
    }
)







commonFGDT <- list(
    obj_info=function(remove_internal_use_only=TRUE) {
        "This function implements the HDF5-API function H5Oget_info."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5O.html#Object-GetInfo} for details."

        res <- .Call("R_H5Oget_info", self$id, request_empty(1), PACKAGE = "hdf5r")
        if(res$return_val < 0) {
            stop("Error getting object info")
        }
        if(remove_internal_use_only) {
            oinfo <- res$oinfo
            oinfo$meta_size <- NULL
            return(oinfo)
        }
        else {
            return(res$oinfo)
        }
    },
    get_obj_name=function() {
        "This function implements the HDF5-API function H5Iget_name."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5I.html#Identify-GetName} for details."

        ## get size of the name
        name_size <- .Call("R_H5Iget_name", self$id, character(0), 0, PACKAGE="hdf5r")$return_val
        if(name_size < 0) {
            stop("Error returning name of object")
        }
        if(name_size == 0) {
            return(NA)
        }
        ## create a character vector of sufficient size (it will be copied in the internal C function as is available for writign
        char_buf=paste(rep(" ", name_size), collapse="")
        res <- .Call("R_H5Iget_name", self$id, char_buf, name_size + 1, PACKAGE="hdf5r")
        if(res$return_val < 0) {
            stop("Error returning name of object")
        }
        return(res$name)
    },
    ## functions that work on attributes
    create_attr=function(attr_name, robj=NULL, dtype=NULL, space=NULL) {
        "This function implements the HDF5-API function H5Acreate2."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Create2} for details."

        if(!is.character(attr_name) || length(attr_name) != 1) {
            stop("'attr_name' has to be a character vector of length 1")
        }
        if(self$attr_exists(attr_name)) {
            stop("Can't create attribute; already exists")
        }

        attr_create_pl <- h5const$H5P_DEFAULT
        attr_access_pl <- h5const$H5P_DEFAULT

        ## adapt dtype, space as necessary
        if(is.null(robj) && (is.null(dtype) || is.null(space))) {
            stop("If a sample robj is not provided, both dtype and space have to be given")
        }
        if(is.null(dtype)) {
            dtype <- guess_dtype(x=robj, scalar=FALSE, string_len=Inf)
        }
        if(is.null(space)) {
            space <- guess_space(x=robj, dtype=dtype, chunked=FALSE)
        }

        id <- .Call("R_H5Acreate2", self$id, attr_name, dtype$id, space$id,
                     attr_create_pl$id, attr_access_pl$id, PACKAGE="hdf5r")$return_val

        if(id < 0) {
            stop("Problem creating new attribute")
        }
        attr <- H5A$new(id=id)
        if(!is.null(robj)) {
            attr$write(robj)
        }
        return(attr)
    },
    attr_open=function(attr_name) {
        "This function implements the HDF5-API function H5Aopen."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Open} for details."

        if(!is.character(attr_name) || length(attr_name) != 1) {
            stop("'attr_name' has to be a character vector of length 1")
        }
        attr_access_pl=h5const$H5P_DEFAULT
        id <- .Call("R_H5Aopen", self$id, attr_name, attr_access_pl$id, PACKAGE="hdf5r")$return_val

        if(id < 0) {
            stop("Problem creating new attribute")
        }
        return(H5A$new(id=id))
    },
    create_attr_by_name=function(attr_name, obj_name, robj=NULL, dtype=NULL, space=NULL, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Acreate_by_name."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-CreateByName} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        if(!is.character(obj_name) || length(obj_name) != 1) {
            stop("'obj_name' has to be a character vector of length 1")
        }
        if(!is.character(attr_name) || length(attr_name) != 1) {
            stop("'attr_name' has to be a character vector of length 1")
        }
        attr_create_pl <- h5const$H5P_DEFAULT
        attr_access_pl <- h5const$H5P_DEFAULT

        if(is.null(robj) && (is.null(dtype) || is.null(space))) {
            stop("If a sample robj is not provided, both dtype and space have to be given")
        }
        if(is.null(dtype)) {
            dtype <- guess_dtype(x=robj, scalar=FALSE, string_len=Inf)
        }
        if(is.null(space)) {
            space <- guess_space(x=robj, dtype=dtype, chunked=FALSE)
        }

        id <- .Call("R_H5Acreate_by_name", self$id, obj_name, attr_name, dtype$id, space$id,
                     attr_create_pl$id, attr_access_pl$id, link_access_pl$id, PACKAGE="hdf5r")$return_val

        if(id < 0) {
            stop("Problem creating new attribute")
        }
        attr <- H5A$new(id=id)
        if(!is.null(robj)) {
            attr$write(robj)
        }
        return(attr)

    },
    attr_open_by_name=function(attr_name, obj_name, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Aopen_by_name."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-OpenByName} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        if(!is.character(obj_name) || length(obj_name) != 1) {
            stop("'obj_name' has to be a character vector of length 1")
        }
        if(!is.character(attr_name) || length(attr_name) != 1) {
            stop("'attr_name' has to be a character vector of length 1")
        }
        attr_access_pl=h5const$H5P_DEFAULT
        id <- .Call("R_H5Aopen_by_name", self$id, obj_name, attr_name, attr_access_pl$id, link_access_pl$id, PACKAGE="hdf5r")$return_val

        if(id < 0) {
            stop("Problem creating new attribute")
        }
        return(H5A$new(id=id))
    },
    attr_open_by_idx=function(n, obj_name, idx_type=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Aopen_by_idx."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-OpenByIdx} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        if(!is.character(obj_name) || length(obj_name) != 1) {
            stop("'obj_name' has to be a character vector of length 1")
        }
        attr_access_pl=h5const$H5P_DEFAULT
        id <- .Call("R_H5Aopen_by_idx", self$id, obj_name, idx_type, order, n, attr_access_pl$id, link_access_pl$id, PACKAGE="hdf5r")$return_val

        if(id < 0) {
            stop("Problem creating new attribute")
        }
        return(H5A$new(id=id))

    },
    attr_exists_by_name=function(attr_name, obj_name, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Aexists_by_name."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-ExistsByName} for details."
        check_pl(link_access_pl, "H5P_LINK_ACCESS")

        if(!is.character(obj_name) || length(obj_name) != 1) {
            stop("'obj_name' has to be a character vector of length 1")
        }
        if(!is.character(attr_name) || length(attr_name) != 1) {
            stop("'attr_name' has to be a character vector of length 1")
        }
        res <- .Call("R_H5Aexists_by_name", self$id, obj_name, attr_name, link_access_pl$id, PACKAGE="hdf5r")$return_val
        if(res < 0) {
            stop(paste("Error trying to check existence of attribute", attr_name))
        }
        return(as.logical(res))
    },
    attr_exists=function(attr_name) {
        "This function implements the HDF5-API function H5Aexists."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Exists} for details."

        if(!is.character(attr_name) || length(attr_name) != 1) {
            stop("'attr_name' has to be a character vector of length 1")
        }
        res <- .Call("R_H5Aexists", self$id, attr_name, PACKAGE="hdf5r")$return_val
        if(res < 0) {
            stop(paste("Error trying to check existence of attribute", attr_name))
        }
        return(as.logical(res))
    },
   attr_rename_by_name=function(old_attr_name, new_attr_name, obj_name, link_access_pl=h5const$H5P_DEFAULT) {
       "This function implements the HDF5-API function H5Arename_by_name."
       "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-RenameByName} for details."

       check_pl(link_access_pl, "H5P_LINK_ACCESS")

        if(!is.character(obj_name) || length(obj_name) != 1) {
            stop("'obj_name' has to be a character vector of length 1")
        }
        if(!is.character(old_attr_name) || length(old_attr_name) != 1) {
            stop("'old_attr_name' has to be a character vector of length 1")
        }
        if(!is.character(new_attr_name) || length(new_attr_name) != 1) {
            stop("'new_attr_name' has to be a character vector of length 1")
        }
        res <- .Call("R_H5Arename_by_name", self$id, obj_name, old_attr_name, new_attr_name, link_access_pl$id, PACKAGE="hdf5r")$return_val
        if(res < 0) {
            stop(paste("Error renaming attribute from", old_attr_name, "to", new_attr_name))
        }
        return(invisible(self))
    },
    attr_rename=function(old_attr_name, new_attr_name) {
        "This function implements the HDF5-API function H5Arename."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Rename} for details."

        if(!is.character(old_attr_name) || length(old_attr_name) != 1) {
            stop("'old_attr_name' has to be a character vector of length 1")
        }
        if(!is.character(new_attr_name) || length(new_attr_name) != 1) {
            stop("'new_attr_name' has to be a character vector of length 1")
        }
        res <- .Call("R_H5Arename", self$id, old_attr_name, new_attr_name, PACKAGE="hdf5r")$return_val
        if(res < 0) {
            stop(paste("Error renaming attribute from", old_attr_name, "to", new_attr_name))
        }
        return(invisible(self))
    },
    attr_delete=function(attr_name) {
        "This function implements the HDF5-API function H5Adelete."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-Delete} for details."

        if(!is.character(attr_name) || length(attr_name) != 1) {
            stop("'attr_name' has to be a character vector of length 1")
        }
        herr <- .Call("R_H5Adelete", self$id, attr_name, PACKAGE="hdf5r")$return_val
        if(herr < 0) {
            stop(paste("Error trying to delete attribute", attr_name))
        }
        return(invisible(self))
    },
    attr_delete_by_name=function(attr_name, obj_name, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Adelete_by_name."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-DeleteByName} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        if(!is.character(obj_name) || length(obj_name) != 1) {
            stop("'obj_name' has to be a character vector of length 1")
        }
        if(!is.character(attr_name) || length(attr_name) != 1) {
            stop("'attr_name' has to be a character vector of length 1")
        }
        id <- .Call("R_H5Adelete_by_name", self$id, obj_name, attr_name, link_access_pl$id, PACKAGE="hdf5r")$return_val

        if(id < 0) {
            stop("Problem deleting attribute by name")
        }
        return(invisible(self))
    },
    attr_delete_by_idx=function(n, obj_name, idx_type=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Adelete_by_idx."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-DeleteByIdx} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        if(!is.character(obj_name) || length(obj_name) != 1) {
            stop("'obj_name' has to be a character vector of length 1")
        }
        id <- .Call("R_H5Adelete_by_idx", self$id, obj_name, idx_type, order, n, link_access_pl$id, PACKAGE="hdf5r")$return_val

        if(id < 0) {
            stop("Problem deleting attribute by index")
        }
        return(invisible(self))

    },
    attr_info_by_name=function(attr_name, obj_name, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Aget_info_by_name."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-GetInfoByName} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        if(!is.character(obj_name) || length(obj_name) != 1) {
            stop("'obj_name' has to be a character vector of length 1")
        }
        if(!is.character(attr_name) || length(attr_name) != 1) {
            stop("'attr_name' has to be a character vector of length 1")
        }
        res <- .Call("R_H5Aget_info_by_name", self$id, obj_name, attr_name, request_empty(1), link_access_pl$id, PACKAGE="hdf5r")

        if(res$return_val < 0) {
            stop("Problem getting attribute info by name")
        }
        return(res$ainfo)
    },
    attr_info_by_idx=function(n, obj_name, idx_type=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Aget_info_by_idx."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-GetInfoByIdx} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        if(!is.character(obj_name) || length(obj_name) != 1) {
            stop("'obj_name' has to be a character vector of length 1")
        }
        res <- .Call("R_H5Aget_info_by_idx", self$id, obj_name, idx_type, order, n, request_empty(1), link_access_pl$id, PACKAGE="hdf5r")

        if(res$return_val < 0) {
            stop("Problem getting atribute info by index")
        }
        return(res$ainfo)
    },
    attr_name_by_idx=function(n, obj_name, idx_type=h5const$H5_INDEX_NAME, order=h5const$H5_ITER_NATIVE, link_access_pl=h5const$H5P_DEFAULT) {
        "This function implements the HDF5-API function H5Aget_name_by_idx."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5A.html#Annot-GetNameByIdx} for details."

        check_pl(link_access_pl, "H5P_LINK_ACCESS")
        if(!is.character(obj_name) || length(obj_name) != 1) {
            stop("'obj_name' has to be a character vector of length 1")
        }
        name_size <- .Call("R_H5Aget_name_by_idx", self$id, obj_name, idx_type, order, n, character(0), 0,
                           link_access_pl$id, PACKAGE="hdf5r")$return_val
        char_buf=paste(rep(" ", name_size+1), collapse="")
        res <- .Call("R_H5Aget_name_by_idx", self$id, obj_name, idx_type, order, n, char_buf, name_size+1,
                     link_access_pl$id, PACKAGE="hdf5r")

        if(res$return_val < 0) {
            stop("Problem getting attribute name by index")
        }
        return(res$name)
    }
)


## create reference for datasets is implemented separately to allower for better ease of use in creating
## H5R_DATASET_REGION references
commonFGT <- list(
    create_reference=function(name=".", space=NULL) {
        "This function implements the HDF5-API function H5Rcreate. If \\code{space=NULL} then a \\code{H5R_OBJECT} reference"
        "is created, otherwise a \\code{H5R_DATASET_REGION} reference"
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5R.html#Reference-Create} for details."

        if(is.null(space)) {
            ref_type <- h5const$H5R_OBJECT
            space_id <- -1
            ref_obj <- H5R_OBJECT$new(1, self)
        }
        else {
            ref_type <- h5const$H5R_DATASET_REGION
            space_id <- space$id
            ref_obj <- H5R_DATASET_REGION$new(1, self)
        }

        res <- .Call("R_H5Rcreate", ref_obj$ref, self$id, name, ref_type, space_id, FALSE, PACKAGE="hdf5r")
        if(res$return_val < 0) {
            stop("Error creating object reference")
        }
        ref_obj$ref <- res$ref
        return(ref_obj)
    }
)

commonFGDTA <- list(
    flush=function(scope=h5const$H5F_SCOPE_GLOBAL) {
        "This function implements the HDF5-API function H5Fflush."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-Flush} for details."

        if(self$is_valid) {
            res <- .Call("R_H5Fflush", self$id, scope, PACKAGE="hdf5r")$return_val
            if(res < 0) {
                stop("Error flushing associated file")
            }
            return(invisible(self))
        }
        else {
            return(invisible(self))
        }
    },
    get_filename=function() {
        "This function implements the HDF5-API function H5Fget_name."
        "Please see the documentation at \\url{https://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html#File-GetName} for details."

        ## get size of the name
        name_size <- .Call("R_H5Fget_name", self$id, character(0), 0, PACKAGE="hdf5r")$return_val
        if(name_size < 0) {
            stop("Error returning name of object")
        }
        if(name_size == 0) {
            return(NA)
        }
        ## create a character vector of sufficient size (it will be copied in the internal C function as is available for writign
        char_buf=paste(rep(" ", name_size), collapse="")
        res <- .Call("R_H5Fget_name", self$id, char_buf, name_size + 1, PACKAGE="hdf5r")
        if(res$return_val < 0) {
            stop("Error returning name of object")
        }
        return(res$name)
    }
)

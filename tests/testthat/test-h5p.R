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



context("H5P")

test_that("H5P works", {
    h5p_obj <- H5P_factory(h5const$H5P_DATASET_CREATE)
    ## now test out the various standard functions
    h5p_cls <- h5p_obj$get_class()
    expect_true(h5p_cls$equal(h5const$H5P_DATASET_CREATE))

    h5p_cls_name <- h5p_obj$get_class_name()
    expect_equal(h5p_cls_name, "dataset create")

    h5p_obj_cpy <- h5p_obj$copy()
    expect_true(h5p_obj$equal(h5p_obj_cpy))

})

test_that("H5P_FILE_CREATE works", {
    file_create_pl <- H5P_FILE_CREATE$new()
    file_create_pl$set_userblock(1024)
    expect_equal(file_create_pl$get_userblock(), 1024)

    file_create_pl$set_sizes(16, 16)
    expect_equal(file_create_pl$get_sizes(), list(sizeof_addr=16, sizeof_size=16))

    file_create_pl$set_sym_k(32, 8)
    expect_equal(file_create_pl$get_sym_k(), list(ik=32, lk=8))

    file_create_pl$set_istore_k(32)
    expect_equal(file_create_pl$get_istore_k(), 32)

    require(utils)
    if(compareVersion(h5version(verbose=FALSE), "1.10.0") >= 0) { # functions only available in 1.10.0
        file_create_pl$set_file_space(h5const$H5F_FILE_SPACE_ALL_PERSIST, 2)
        foo <- file_create_pl$get_file_space()
        expect_equal(foo$threshold, 2)
        expect_equal(as.character(foo$strategy), as.character(h5const$H5F_FILE_SPACE_ALL_PERSIST))
    }

})

test_that("H5P_FILE_ACCESS works", {
    file_access_pl <- H5P_FILE_ACCESS$new()
    file_access_pl$set_cache(953, 2^24, 0.5)
    cache_params <- file_access_pl$get_cache()
    expect_equal(cache_params, list(rdcc_nslots=953, rdcc_nbytes=2^24, rdcc_w0=0.5))
})


test_that("H5P_DATASET_CREATE works", {
    h5p_obj <- H5P_DATASET_CREATE$new()
    h5p_obj$set_layout(layout=h5const$H5D_CHUNKED)
    expect_equal(as.character(h5p_obj$get_layout()), "H5D_CHUNKED")

    ## get/set chunk
    h5p_obj$set_chunk(chunk=c(100, 200))
    expect_equal(h5p_obj$get_chunk(2), c(100,200))

    ## get/set fill value
    dtype_int <- h5types$H5T_NATIVE_INT
    h5p_obj$set_fill_value(dtype_int, 1)
    expect_equal(h5p_obj$get_fill_value(dtype_int), 1)

    ## get/set fill time
    h5p_obj$set_fill_time(h5const$H5D_FILL_TIME_NEVER)
    expect_equal(h5p_obj$get_fill_time(), h5const$H5D_FILL_TIME_NEVER)

    ## get/set alloc time
    h5p_obj$set_alloc_time(h5const$H5D_ALLOC_TIME_EARLY)
    expect_equal(h5p_obj$get_alloc_time(), h5const$H5D_ALLOC_TIME_EARLY)

    ## try out various filters
    h5p_obj$set_deflate(3)
    expect_equal(h5p_obj$get_nfilters(), 1)
    expect_equal(h5p_obj$get_filter(0)$filter, h5const$H5Z_FILTER_DEFLATE)
    expect_true(    h5p_obj$all_filters_avail())
    h5p_obj$remove_filter()
    expect_equal(h5p_obj$get_nfilters(), 0)

    h5p_obj$set_fletcher32()
    h5p_obj$set_nbit()
    h5p_obj$set_scaleoffset()
    h5p_obj$set_shuffle()

    expect_equal(h5p_obj$get_nfilters(), 4)
    expect_equal(h5p_obj$get_filter(0)$filter, h5const$H5Z_FILTER_FLETCHER32)
    expect_equal(h5p_obj$get_filter(1)$filter, h5const$H5Z_FILTER_NBIT)
    expect_equal(h5p_obj$get_filter(2)$filter, h5const$H5Z_FILTER_SCALEOFFSET)
    expect_equal(h5p_obj$get_filter(3)$filter, h5const$H5Z_FILTER_SHUFFLE)

    ## now set an external file
    h5p_obj$set_external("test", 10, 100)
    expect_equal(h5p_obj$get_external_count(), 1)
    external_1 <- h5p_obj$get_external(0)
    expect_equal(external_1$name, "test")
    expect_equal(external_1$offset, 10)
    expect_equal(external_1$size, 100)
})

test_that("H5P_DATASET_ACCESS works", {
    ## passing -1 asks for the library default. Don't hard-code what that default is:
    ## HDF5 2.0 raised rdcc_nslots from 521 to 8191 and rdcc_nbytes from 1MiB to 8MiB.
    ## Compare against a pristine property list instead.
    defaults <- H5P_DATASET_ACCESS$new()$get_chunk_cache()

    h5p_obj <- H5P_DATASET_ACCESS$new()
    h5p_obj$set_chunk_cache(rdcc_nslots=-1, rdcc_nbytes=-1, rdcc_w0=-1)
    expect_equal(h5p_obj$get_chunk_cache()$rdcc_nslots, defaults$rdcc_nslots)
    expect_equal(h5p_obj$get_chunk_cache()$rdcc_nbytes, defaults$rdcc_nbytes)
    expect_equal(h5p_obj$get_chunk_cache()$rdcc_w0, defaults$rdcc_w0)

    ## explicitly requested values have to round-trip unchanged
    h5p_obj$set_chunk_cache(rdcc_nslots=1031, rdcc_nbytes=2097152, rdcc_w0=0.5)
    expect_equal(h5p_obj$get_chunk_cache()$rdcc_nslots, 1031)
    expect_equal(h5p_obj$get_chunk_cache()$rdcc_nbytes, 2097152)
    expect_equal(h5p_obj$get_chunk_cache()$rdcc_w0, 0.5)
})

test_that("H5P_DATASET_XFER", {
    h5p_obj <- H5P_DATASET_XFER$new()
    h5p_obj$set_edc_check(h5const$H5Z_DISABLE_EDC)
    expect_equal(h5p_obj$get_edc_check(), h5const$H5Z_DISABLE_EDC)

    h5p_obj$set_hyper_vector_size(1000)
    expect_equal(h5p_obj$get_hyper_vector_size(), 1000)

    h5p_obj$set_btree_ratios(0.25, 0.5, 0.75)
    expect_equal(h5p_obj$get_btree_ratios(), list(left=0.25, middle=0.5, right=0.75))
})

test_that("H5P_LINK_CREATE", {
    h5p_obj <- H5P_LINK_CREATE$new()
    h5p_obj$set_char_encoding(h5const$H5T_CSET_ASCII)
    expect_equal(h5p_obj$get_char_encoding(), h5const$H5T_CSET_ASCII)
    h5p_obj$set_char_encoding(h5const$H5T_CSET_UTF8)
    expect_equal(h5p_obj$get_char_encoding(), h5const$H5T_CSET_UTF8)

    h5p_obj$set_create_intermediate_group(FALSE)
    expect_equal(h5p_obj$get_create_intermediate_group(), FALSE)
    h5p_obj$set_create_intermediate_group(TRUE)
    expect_equal(h5p_obj$get_create_intermediate_group(), TRUE)
})

test_that("H5P_LINK_ACCESS", {
    h5p_obj <- H5P_LINK_ACCESS$new()
    h5p_obj$set_nlinks(5)
    expect_equal(h5p_obj$get_nlinks(), 5)

    h5p_obj$set_elink_prefix("test")
    expect_equal(h5p_obj$get_elink_prefix(), "test")

    h5p_obj$set_elink_acc_flags(h5const$H5F_ACC_RDONLY)
    expect_equal(h5p_obj$get_elink_acc_flags(), h5const$H5F_ACC_RDONLY)
})

test_that("H5P_OBJECT_CREATE", {
    h5p_obj <- H5P_OBJECT_CREATE$new()

    h5p_obj$set_obj_track_times(FALSE)
    expect_equal(h5p_obj$get_obj_track_times(), FALSE)
    h5p_obj$set_obj_track_times(TRUE)
    expect_equal(h5p_obj$get_obj_track_times(), TRUE)

    h5p_obj$set_attr_phase_change(9,5)
    expect_equal(h5p_obj$get_attr_phase_change(), list(max_compact=9, min_dense=5))

    h5p_obj$set_attr_creation_order(h5const$H5P_CRT_ORDER_TRACKED + h5const$H5P_CRT_ORDER_INDEXED)
    expect_equal(h5p_obj$get_attr_creation_order(), as.integer(h5const$H5P_CRT_ORDER_TRACKED + h5const$H5P_CRT_ORDER_INDEXED))
})


test_that("H5P_OBJECT_COPY", {
    h5p_obj <- H5P_OBJECT_COPY$new()
    h5p_obj$set_copy_obj(h5const$H5O_COPY_SHALLOW_HIERARCHY_FLAG)
    expect_equal(h5p_obj$get_copy_obj(), as.integer(h5const$H5O_COPY_SHALLOW_HIERARCHY_FLAG))
})

test_that("H5P_ATTRIBUTE_CREATE", {
    h5p_obj <- H5P_ATTRIBUTE_CREATE$new()
    h5p_obj$set_char_encoding(h5const$H5T_CSET_ASCII)
    expect_equal(h5p_obj$get_char_encoding(), h5const$H5T_CSET_ASCII)
    h5p_obj$set_char_encoding(h5const$H5T_CSET_UTF8)
    expect_equal(h5p_obj$get_char_encoding(), h5const$H5T_CSET_UTF8)
})


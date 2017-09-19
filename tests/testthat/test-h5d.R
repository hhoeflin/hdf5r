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



context("H5D")

read_write_roundtrip <- function(ds, robj) {
    ds$write_low_level(robj)
    res <- ds$read()
    return(list(input=robj, output=res))
}

test_that("Basic dataset function", {
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")
    dtype_int64 <- h5types$H5T_NATIVE_LLONG
    dspace <- H5S$new(type="simple", dims=20, maxdims=20)
    ds_int64_chunked <- file.h5$create_dataset(name="int64_chunked", dtype=dtype_int64, space=dspace)
    
    ## test out the basic functions
    dspace_new <- ds_int64_chunked$get_space()
    expect_true(inherits(dspace_new, "H5S"))
    expect_equal(dspace_new$get_simple_extent_dims()$dims, 20)
    expect_equal(as.character(ds_int64_chunked$get_space_status()), "H5D_SPACE_STATUS_NOT_ALLOCATED")
    expect_equal(ds_int64_chunked$dims, 20)
    expect_equal(ds_int64_chunked$maxdims, 20)
    expect_equal(ds_int64_chunked$chunk_dims, 20)
    
    expect_true(ds_int64_chunked$get_type()$equal(h5types$H5T_NATIVE_LLONG))

    expect_equal(ds_int64_chunked$get_storage_size(), 0)
    expect_equal(ds_int64_chunked$vlen_get_buf_size(ds_int64_chunked$get_type(), ds_int64_chunked$get_space()), 0)
    res_int64 <- read_write_roundtrip(ds_int64_chunked, 1:20)

    file.h5$flush()

    expect_equal(ds_int64_chunked$get_storage_size(), 49)
    expect_true(inherits(try(ds_int64_chunked$get_offset(), silent=TRUE), "try-error"))
    ## vlen is still 0, as it is not variable length data
    expect_equal(ds_int64_chunked$vlen_get_buf_size(ds_int64_chunked$get_type(), ds_int64_chunked$get_space()), 0)

    ## now try the same, unchunked
    ds_int64_unchunked <- file.h5$create_dataset(name="int64_unchunked", dtype=dtype_int64, space=dspace, chunk_dim=NULL)
    res_int64_unchunked <- read_write_roundtrip(ds_int64_unchunked, 1:20)
    expect_equal(ds_int64_unchunked$get_storage_size(), 160)
    expect_equal(ds_int64_unchunked$chunk_dims, NA)


    ## now write a dataset directly
    ds_int64_robj <- file.h5$create_dataset(name="int64_robj", 1:20)
    ## check that we can read the data out
    expect_equal(ds_int64_robj$read_low_level(), 1:20)

    ## also try it with a 2-dimensional space; and a version with a one-dimensional space and an internal array
    array_type <- H5T_ARRAY$new(4, h5types$H5T_NATIVE_INT)
    ds_array <- file.h5$create_dataset(name="int_array", dtype=array_type, space=H5S$new(dims=5))
    res_array <- read_write_roundtrip(ds_array, matrix(1:20, ncol=4))
    expect_equal(res_array$input, res_array$output)

    ds_2_dim <- file.h5$create_dataset(name="int_2_dim", dtype=array_type, space=H5S$new(dims=c(5, 4)))
    res_2_dim <- read_write_roundtrip(ds_array, matrix(1:20, ncol=4))
    expect_equal(res_2_dim$input, res_2_dim$output)
    
    ## cleanup
    file.h5$close_all()
    file.remove(test_file)
})



test_that("Creating datasets of different types", {
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")

    ## now create different types
    ## integer, long integer, float, enum, compound, strings
    ## create a dataset for each of them
    dtype_int64 <- h5types$H5T_NATIVE_LLONG
    dtype_int32 <- h5types$H5T_NATIVE_INT
    dtype_float <- h5types$H5T_NATIVE_FLOAT
    dtype_double <- h5types$H5T_NATIVE_DOUBLE

    ## enums
    enum_logical <- H5T_LOGICAL$new()
    factor_levels <- paste("test", 1:10, sep="")
    enum_factor <- H5T_ENUM$new(labels=factor_levels)

    ## strings
    dtype_string_variable_utf8 <- H5T_STRING$new()$set_size(Inf)$set_cset(h5const$H5T_CSET_UTF8)
    dtype_string_short_utf8 <- H5T_STRING$new()$set_size(10)$set_cset(h5const$H5T_CSET_UTF8)

    ## compound
    dtype_cpd <- H5T_COMPOUND$new(dtypes=list(dtype_int32, dtype_int32), labels=c("a", "b"))


    ## now create a simple dataspace for the new objects;
    ## will be the same for all, single dimension of size 20
    dspace <- H5S$new(type="simple", dims=20, maxdims=20)

    ## create named datasets for all these types
    ds_int64 <- file.h5$create_dataset(name="int64", dtype=dtype_int64, space=dspace)
    ds_int32 <- file.h5$create_dataset(name="int32", dtype=dtype_int32, space=dspace)
    ds_float <- file.h5$create_dataset(name="float", dtype=dtype_float, space=dspace)
    ds_double <- file.h5$create_dataset(name="double", dtype=dtype_double, space=dspace)
    ds_logical <- file.h5$create_dataset(name="enum_logical", dtype=enum_logical, space=dspace)
    ds_factor <- file.h5$create_dataset(name="enum_factor", dtype=enum_factor, space=dspace)
    ds_string_short <- file.h5$create_dataset(name="string_short", dtype=dtype_string_short_utf8, space=dspace)
    ds_string_variable <- file.h5$create_dataset(name="string_variable", dtype=dtype_string_variable_utf8, space=dspace)
    ds_cpd <- file.h5$create_dataset(name="cpd", dtype=dtype_cpd, space=dspace)

    ## also create an anonymous dataset
    ds_anon <- file.h5$create_dataset(dtype=dtype_int64, space=dspace)
    
    ## now write data into the dataset, and read it back out again
    res_int32 <- read_write_roundtrip(ds_int32, 1:20)
    expect_equal(res_int32$input, res_int32$output)

    res_int64 <- read_write_roundtrip(ds_int64, 1:20)
    expect_equal(res_int64$input, res_int64$output)

    res_float <- read_write_roundtrip(ds_float, 1:20/4)
    expect_equal(res_float$input, res_float$output)

    res_double <- read_write_roundtrip(ds_double, 1:20/4)
    expect_equal(res_double$input, res_double$output)

    res_logical <- read_write_roundtrip(ds_logical, rep(c(FALSE, TRUE), 10))
    expect_equal(res_logical$input, res_logical$output)

    res_factor <- read_write_roundtrip(ds_factor, factor(rep(paste("test", 1:10, sep=""), 2), levels=paste("test", 1:10, sep="")))
    expect_equal(res_factor$input, res_factor$output)

    res_string_short <- read_write_roundtrip(ds_string_short, rep(paste("teststring", 1:20, sep="")))
    expect_equal(substr(res_string_short$input, 1,10), res_string_short$output)

    res_string_variable <- read_write_roundtrip(ds_string_variable, rep(paste("teststring", 1:20, sep="")))
    expect_equal(res_string_variable$input, res_string_variable$output)

    res_cpd <- read_write_roundtrip(ds_cpd, data.frame(a=1:20, b=21:40))
    expect_equal(res_cpd$input, res_cpd$output)

    ## check that the fill-value can be retrieved
    expect_equal(ds_int32$get_fill_value(), 0)
    expect_equal(ds_string_short$get_fill_value(), "")
    expect_equal(ds_cpd$get_fill_value(), data.frame(a=0, b=0))


    ## check other ways of creating a dataset
    ## using the dims parameter
    ds_dimsparam <- file.h5$create_dataset(name="dims_param", dtype=dtype_int32, dims=c(2,3,4))
    expect_equal(ds_dimsparam$dims, c(2,3,4))
    res_dimsparam <- read_write_roundtrip(ds_dimsparam, array(1:24 * 2, dim=c(2,3,4)))
    expect_equal(res_dimsparam$input, res_dimsparam$output)
    
    file.h5$close_all()
    file.remove(test_file)
})



test_that("Chunking failures as intended", {
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")

    ## create a dataset with a chunk-size that is larger than the dataset itself
    res1 <- try({file.h5$create_dataset("test", dtype=h5types$H5T_NATIVE_INT, space=H5S$new(dims=c(10), maxdims=c(Inf)),
                           chunk_dim=c(20))}, silent=TRUE)
    expect_true(!inherits(res1, "try-error"))
    res2 <- try({file.h5$create_dataset("test2", dtype=h5types$H5T_NATIVE_INT, space=H5S$new(dims=c(10, 10), maxdims=c(Inf, 10)),
                           chunk_dim=c(20, 10))}, silent=TRUE)
    expect_true(!inherits(res2, "try-error"))
    suppressWarnings({res3 <- try({file.h5$create_dataset("test3", dtype=h5types$H5T_NATIVE_INT, space=H5S$new(dims=c(10, 10), maxdims=c(Inf, 10)),
                           chunk_dim=c(20, 20))}, silent=TRUE)})
    expect_true(inherits(res3, "try-error"))

    file.h5$close_all()
    file.remove(test_file)
})



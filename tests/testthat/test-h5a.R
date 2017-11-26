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

context("H5A")

read_write_roundtrip <- function(h5attr, robj) {
    h5attr$write(robj)
    res <- h5attr$read()
    return(list(input=robj, output=res))
}

test_that("Basic dataset function", {
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")
    dtype_int64 <- h5types$H5T_NATIVE_LLONG
    dspace <- H5S$new(type="simple", dims=20, maxdims=20)
    attr_int64 <- file.h5$create_attr(attr_name="int64", dtype=dtype_int64, space=dspace)
    
    ## test out the basic functions
    dspace_new <- attr_int64$get_space()
    expect_true(inherits(dspace_new, "H5S"))
    expect_equal(dspace_new$get_simple_extent_dims()$dims, 20)

    expect_true(attr_int64$get_type()$equal(h5types$H5T_NATIVE_LLONG))

    expect_equal(attr_int64$get_storage_size(), 160)
    res_int64 <- read_write_roundtrip(attr_int64, 1:20)

    file.h5$flush()

    expect_equal(attr_int64$get_storage_size(), 160)

    ## rename the attributes; get info by name and by idx;
    ## try out the various functions that originate from the file or the group
    file.h5$create_group("sub")
    attr_int64_sub <- file.h5$create_attr_by_name("int64", "sub", dtype=dtype_int64, space=dspace)
    expect_equal(attr_int64_sub$attr_name(), "int64")

    attr_int64_sub_name <- file.h5$attr_open_by_name("int64", "sub")
    expect_equal(attr_int64_sub_name$attr_name(), "int64")

    attr_int64_sub_index <- file.h5$attr_open_by_idx(0, "sub")
    expect_equal(attr_int64_sub_index$attr_name(), "int64")

    ## check the exists function
    expect_true(file.h5$attr_exists_by_name("int64", "sub"))
    expect_true(file.h5$open("sub")$attr_exists("int64"))

    ## rename the attribute and then back again
    file.h5$attr_rename_by_name("int64", "int64_new", "sub")
    expect_true(file.h5$attr_exists_by_name("int64_new", "sub"))
    expect_true(!file.h5$attr_exists_by_name("int64", "sub"))
    file.h5$open("sub")$attr_rename("int64_new", "int64")
    expect_true(file.h5$attr_exists_by_name("int64", "sub"))
    expect_true(!file.h5$attr_exists_by_name("int64_new", "sub"))


    ## get attribute info by various ways
    attr_info_direct <- attr_int64_sub$get_info()
    attr_info_name <- file.h5$attr_info_by_name("int64", "sub")
    attr_info_idx <- file.h5$open("sub")$attr_info_by_idx(0, ".")
    expect_equal(attr_info_direct, attr_info_name)
    expect_equal(attr_info_direct, attr_info_idx)
    

    ## delete the attribute in various ways
    ## for that we first need to create a few more
    file.h5$create_attr_by_name("int64_copy_1", "sub", dtype=dtype_int64, space=dspace)
    file.h5$create_attr_by_name("int64_copy_2", "sub", dtype=dtype_int64, space=dspace)
    expect_equal(file.h5$obj_info_by_name("sub")$num_attrs, 3)

    ## check the attribute names by idx
    expect_equal(file.h5$attr_name_by_idx(0, "sub"), "int64")
    expect_equal(file.h5$attr_name_by_idx(1, "sub"), "int64_copy_1")
    expect_equal(file.h5$attr_name_by_idx(2, "sub"), "int64_copy_2")

    ## check that from the group we can retrieve the correct number of attributes
    group_sub <- file.h5[["sub"]]
    expect_equal(group_sub$attr_get_number(), 3)
    
    ## now delete each of them in one of the 3 possible ways
    file.h5$open("sub")$attr_delete("int64")
    file.h5$attr_delete_by_name("int64_copy_1", "sub")
    file.h5$attr_delete_by_idx(0, "sub")

    ## now check that there are no attributes left
    expect_equal(file.h5$obj_info_by_name("sub")$num_attrs, 0)
    
    ## cleanup
    file.h5$close_all()
    file.remove(test_file)
})

test_that("Creating attributes of different types", {
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
    attrspace <- H5S$new(type="simple", dims=20, maxdims=20)

    ## create named datasets for all these types
    attr_int64 <- file.h5$create_attr(attr_name="int64", dtype=dtype_int64, space=attrspace)
    attr_int32 <- file.h5$create_attr(attr_name="int32", dtype=dtype_int32, space=attrspace)
    attr_float <- file.h5$create_attr(attr_name="float", dtype=dtype_float, space=attrspace)
    attr_double <- file.h5$create_attr(attr_name="double", dtype=dtype_double, space=attrspace)
    attr_logical <- file.h5$create_attr(attr_name="enum_logical", dtype=enum_logical, space=attrspace)
    attr_factor <- file.h5$create_attr(attr_name="enum_factor", dtype=enum_factor, space=attrspace)
    attr_string_short <- file.h5$create_attr(attr_name="string_short", dtype=dtype_string_short_utf8, space=attrspace)
    attr_string_variable <- file.h5$create_attr(attr_name="string_variable", dtype=dtype_string_variable_utf8, space=attrspace)
    attr_cpd <- file.h5$create_attr(attr_name="cpd", dtype=dtype_cpd, space=attrspace)

        ## now write data into the dataset, and read it back out again
    res_int32 <- read_write_roundtrip(attr_int32, 1:20)
    expect_equal(res_int32$input, res_int32$output)

    res_int64 <- read_write_roundtrip(attr_int64, 1:20)
    expect_equal(res_int64$input, res_int64$output)

    res_float <- read_write_roundtrip(attr_float, 1:20/4)
    expect_equal(res_float$input, res_float$output)

    res_double <- read_write_roundtrip(attr_double, 1:20/4)
    expect_equal(res_double$input, res_double$output)

    res_logical <- read_write_roundtrip(attr_logical, rep(c(FALSE, TRUE), 10))
    expect_equal(res_logical$input, res_logical$output)

    res_factor <- read_write_roundtrip(attr_factor, factor(rep(paste("test", 1:10, sep=""), 2), levels=paste("test", 1:10, sep="")))
    expect_equal(res_factor$input, res_factor$output)

    res_string_short <- read_write_roundtrip(attr_string_short, rep(paste("teststring", 1:20, sep="")))
    expect_equal(substr(res_string_short$input, 1,10), res_string_short$output)

    res_string_variable <- read_write_roundtrip(attr_string_variable, rep(paste("teststring", 1:20, sep="")))
    expect_equal(res_string_variable$input, res_string_variable$output)

    res_cpd <- read_write_roundtrip(attr_cpd, data.frame(a=1:20, b=21:40))
    expect_equal(res_cpd$input, res_cpd$output)
    
    file.h5$close_all()
    file.remove(test_file)
})




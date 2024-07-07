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

context("Conversion")


truncateVec <- function(x, min, max) {
    x[is.na(x) | x < min] <- min
    x[!is.na(x) & x > max] <- max
    return(x)
}


test_that("Convert H5T_FLOAT works", {
    dtype_double <- h5types$H5T_NATIVE_DOUBLE
    dtype_float <- h5types$H5T_NATIVE_FLOAT
    ## with double input
    Robj <- (-10:10) / 2
    res_double <- convertRoundTrip(Robj, dtype_double)
    res_float <- convertRoundTrip(Robj, dtype_float)
    expect_equal(res_double$input, res_double$output)

    ## with integer input
    Robj_int <- -10:10
    res_int_double <- convertRoundTrip(Robj_int, dtype_double)
    res_int_float <- convertRoundTrip(Robj_int, dtype_float)
    expect_equal(as.double(res_int_double$input), res_int_double$output)
    expect_equal(as.double(res_int_float$input), res_int_float$output)

    ## with 64bit integer input
    Robj_int64 <- as.integer64(-10:10)
    res_int64_double <- convertRoundTrip(Robj_int64, dtype_double)
    res_int64_float <- convertRoundTrip(Robj_int64, dtype_float)
    expect_equal(as.double(res_int64_double$input), res_int64_double$output)
    expect_equal(as.double(res_int64_float$input), res_int64_float$output)
    
})


## Some constants relevant for integers here
SHORT_MIN <- -2^15
SHORT_MAX <- 2^15 - 1
INT_MIN <- as.integer64(-2^31)
INT_MAX <- as.integer64(2^31 - 1)
UINT_MIN <- as.integer64(0)
UINT_MAX <- as.integer64(2^32-1)
INT64_MAX <- as.integer64(2)^62 - 1 + as.integer64(2)^62

test_that("Convert H5T_INTEGER works", {
    dtype_int64 <- h5types$H5T_NATIVE_LLONG
    dtype_uint64 <- h5types$H5T_NATIVE_ULLONG
    dtype_int <- h5types$H5T_NATIVE_INT
    dtype_uint <- h5types$H5T_NATIVE_UINT
    dtype_short <- h5types$H5T_NATIVE_SHORT
    dtype_double <- h5types$H5T_NATIVE_DOUBLE

    robj_int64 <- c(as.integer64(c(-1, 1, 2^31-1, 2^31)), as.integer(2)^62, suppressWarnings(as.integer64(2^64)))
    robj_double <- c(-1, 1, 2^31-1, 2^31, 2^62, 2^64, 2^64+2^30)
    robj_double_int64 <- suppressWarnings(as.integer64(robj_double))
    robj_double_int64[is.na(robj_double_int64)] <- INT64_MAX
    robj_double_int64[robj_double_int64 < 0] <- 0
    
    res_double_uint64 <- convertRoundTrip(robj_double, dtype_uint64)
    res_int64_int64 <- convertRoundTrip(robj_int64, dtype_int64)
    res_int64_int <- suppressWarnings(convertRoundTrip(robj_int64, dtype_int))
    res_int64_uint <- suppressWarnings(convertRoundTrip(robj_int64, dtype_uint))
    res_int64_short <- suppressWarnings(convertRoundTrip(robj_int64, dtype_short))
    suppressWarnings(res_double_int64 <- convertRoundTrip(robj_double, dtype_int64))
    suppressWarnings(res_double_int <- convertRoundTrip(robj_double, dtype_int))
    suppressWarnings(res_double_uint <- convertRoundTrip(robj_double, dtype_uint))
    suppressWarnings(res_double_short <- convertRoundTrip(robj_double, dtype_short))

    expect_equal(res_int64_int64$input, res_int64_int64$output)
    expect_equal(suppressWarnings(as.integer(res_int64_int$input)), res_int64_int$output)
    expect_equal(as.numeric(truncateVec(res_int64_uint$input, UINT_MIN, UINT_MAX)), res_int64_uint$output)
    expect_equal(as.integer(truncateVec(res_int64_short$input, SHORT_MIN, SHORT_MAX)), res_int64_short$output)
    expect_true(sum(res_double_uint64$output - robj_double_int64) == 0)
})

test_that("Convert H5T_ENUM works", {
    ## Need to test logical, factors and enums with arbitrary values
    obj_logical <- c(FALSE, TRUE)
    obj_factor <- factor(paste("test", 1:10, sep=""))
    obj_factor_ext <- factor_ext(rep(-10:10, 2), levels=paste("test", -10:10, sep=""))
    
    ## object intended to provoke an error
    obj_error <- obj_factor_ext
    attr(obj_error, "values") <- 0:10
    obj_character <- paste("test", 1:10)

    ## create the enums for these cases
    enum_logical <- H5T_LOGICAL$new(include_NA=TRUE)
    enum_factor <- H5T_ENUM$new(labels=levels(obj_factor))
    enum_factor_ext <- H5T_ENUM$new(labels=attr(obj_factor_ext, "levels"), values=attr(obj_factor_ext, "values"))
    
    expect_equal(enum_logical$get_values(), as.integer(c(0,1,2)))
    expect_equal(enum_factor$get_values(), 1:10)
    expect_equal(enum_factor_ext$get_values(), -10:10)

    expect_equal(enum_logical$get_labels(), c("FALSE", "TRUE", "NA"))
    expect_equal(enum_factor$get_labels(), levels(obj_factor))
    expect_equal(enum_factor_ext$get_labels(), levels(obj_factor_ext))

    library(utils)
    if(compareVersion(h5version(verbose=FALSE), "1.8.16") >= 0) {
        expect_equal(enum_logical$get_precision(), 2)
        expect_equal(enum_factor$get_precision(), 4)
        expect_equal(enum_factor_ext$get_precision(), 5)
    }
    else { ## in 1.8.14 and below, there is an issue getting the native version of an enum
           ## that is based on an non-native type
        expect_equal(enum_logical$get_precision(), 8)
        expect_equal(enum_factor$get_precision(), 8)
        expect_equal(enum_factor_ext$get_precision(), 8)
    }
    
    res_logical <- convertRoundTrip(obj_logical, enum_logical)
    res_factor <- convertRoundTrip(obj_factor, enum_factor)
    res_factor_ext <- convertRoundTrip(obj_factor_ext, enum_factor_ext)
    expect_equal(res_logical$input, res_logical$output)
    expect_equal(res_factor$input, res_factor$output)
    expect_equal(res_factor_ext$input, res_factor_ext$output)

    res_error <- try(convertRoundTrip(obj_error, enum_factor_ext), silent=TRUE)
    res_character <- try(convertRoundTrip(obj_character, enum_factor_ext), silent=TRUE)
    expect_true(inherits(res_error, "try-error"))
    expect_true(inherits(res_character, "try-error"))

    ## check that enums work appropriate with 64 bit values
    enum_64bit <- H5T_ENUM$new(labels="Test", values=INT_MAX + 1)
    expect_equal(enum_64bit$get_values(), INT_MAX + 1)
})

test_that("Convert H5T_STRING works", {
#    string1.utf8 <- "\x46\x6F\x6F\x20\xC2\xA9\x20\x62\x61\x72\x20\xF0\x9D\x8C\x86\x20\x62\x61\x7A\x20\xE2\x98\x83\x20\x71\x75\x78"
#    Encoding(string1.utf8) <- "UTF-8"
    string.latin1 <- "H\xF6her w\xE4re sch\xF6ner!"
    Encoding(string.latin1) <- "latin1"
    string.utf8 <- enc2utf8(string.latin1)

    stringVec <- paste("test", 1:10)

    dtype_string_unknown <- H5T_STRING$new()$set_size(30)$set_cset("unknown")
    dtype_string_utf8 <- H5T_STRING$new()$set_size(30)$set_cset("UTF-8")
    dtype_string_short_unknown <- H5T_STRING$new()$set_size(10)$set_cset(h5const$H5T_CSET_ASCII)
    dtype_string_short_utf8 <- H5T_STRING$new()$set_size(10)$set_cset(h5const$H5T_CSET_UTF8)
    dtype_string_variable_unknown <- H5T_STRING$new()$set_size(Inf)$set_cset(h5const$H5T_CSET_ASCII)
    dtype_string_variable_utf8 <- H5T_STRING$new()$set_size(Inf)$set_cset(h5const$H5T_CSET_UTF8)

##    res_string1_utf8_unknown <- convertRoundTrip(string1.utf8, dtype_string_unknown)
##    res_string1_utf8_utf8 <- convertRoundTrip(string1.utf8, dtype_string_utf8)
##    res_string1_utf8_short_unknown <- convertRoundTrip(string1.utf8, dtype_string_short_unknown)
##    res_string1_utf8_short_utf8 <- convertRoundTrip(string1.utf8, dtype_string_short_utf8)
##    res_string1_utf8_variable_unknown <- convertRoundTrip(string1.utf8, dtype_string_variable_unknown)
##    res_string1_utf8_variable_utf8 <- convertRoundTrip(string1.utf8, dtype_string_variable_utf8)

    res_string_utf8_unknown <- convertRoundTrip(string.utf8, dtype_string_unknown)
    res_string_utf8_utf8 <- convertRoundTrip(string.utf8, dtype_string_utf8)
    res_string_utf8_short_unknown <- convertRoundTrip(string.utf8, dtype_string_short_unknown)
    res_string_utf8_short_utf8 <- convertRoundTrip(string.utf8, dtype_string_short_utf8)
    res_string_utf8_variable_unknown <- convertRoundTrip(string.utf8, dtype_string_variable_unknown)
    res_string_utf8_variable_utf8 <- convertRoundTrip(string.utf8, dtype_string_variable_utf8)

    res_string_latin1_unknown <- convertRoundTrip(string.latin1, dtype_string_unknown)
    res_string_latin1_utf8 <- convertRoundTrip(string.latin1, dtype_string_utf8)
    res_string_latin1_short_unknown <- convertRoundTrip(string.latin1, dtype_string_short_unknown)
    res_string_latin1_short_utf8 <- convertRoundTrip(string.latin1, dtype_string_short_utf8)
    res_string_latin1_variable_unknown <- convertRoundTrip(string.latin1, dtype_string_variable_unknown)
    res_string_latin1_variable_utf8 <- convertRoundTrip(string.latin1, dtype_string_variable_utf8)

    ## now check only the ones where we expect equality depending on the locale
    if(l10n_info()[["UTF-8"]]) { ## check if the current locale is UTF-8
        expect_equal(res_string_utf8_unknown$input, res_string_utf8_unknown$output)
        expect_equal(res_string_utf8_variable_unknown$input, res_string_utf8_variable_unknown$output)
    }
    if(l10n_info()[["Latin-1"]]) {
        expect_equal(res_string_latin1_unknown$input, res_string_latin1_unknown$output)
        expect_equal(res_string_latin1_variable_unknown$input, res_string_latin1_variable_unknown$output)
    }
    ## now the ones where we always expect equality, because the utf-8 charset is specified in the dtype
    expect_equal(res_string_utf8_utf8$input, res_string_utf8_utf8$output)
    expect_equal(res_string_utf8_variable_utf8$input, res_string_latin1_variable_utf8$output)
    expect_equal(res_string_latin1_utf8$input, res_string_utf8_utf8$output)
    expect_equal(res_string_latin1_variable_utf8$input, res_string_latin1_variable_utf8$output)

    ## for the short, we just check that the length of the returned string is 10
    expect_equal(length(charToRaw(res_string_utf8_short_utf8$output)), 10)
    expect_equal(length(charToRaw(res_string_utf8_short_unknown$output)), 10)
    expect_equal(length(charToRaw(res_string_latin1_short_utf8$output)), 10)
    expect_equal(length(charToRaw(res_string_latin1_short_utf8$output)), 10)

    ## convert an entire vector
    res_stringVec_fixed <- convertRoundTrip(stringVec, dtype_string_utf8)
    res_stringVec_variable <- convertRoundTrip(stringVec, dtype_string_variable_utf8)
    expect_equal(res_stringVec_fixed$input, res_stringVec_fixed$output)
    expect_equal(res_stringVec_variable$input, res_stringVec_variable$output)

    ## convert a string that is NA
    string_NA <- as.character(NA)
    res_stringNA <- convertRoundTrip(string_NA, dtype_string_variable_utf8)
    expect_equal("NA", res_stringNA$output)
})


test_that("Convert R_Complex works", {
    r_cmplx <- complex(real=-5:5, imaginary = 5:(-5))
    dtype_complex <- H5T_COMPLEX$new()
    res <- convertRoundTrip(r_cmplx, dtype_complex)
    expect_equal(res$input, res$output)
})


test_that("Convert H5T_COMPOUND works", {
    test_frame <- data.frame(a=1:3, b=4:6)
    test_frame_frame <- test_frame
    test_frame_frame$c <- test_frame

    dtype_int <- h5types$H5T_NATIVE_SHORT
    dtype_cpd <- H5T_COMPOUND$new(dtypes=list(dtype_int, dtype_int), labels=c("a", "b"))
    dtype_cpd_cpd <- H5T_COMPOUND$new(dtypes=list(dtype_int, dtype_int, dtype_cpd), labels=c("a", "b", "c"))

    res_test <- convertRoundTrip(test_frame, dtype_cpd)
    res_test2 <- convertRoundTrip(test_frame_frame, dtype_cpd_cpd)
    
    expect_equal(res_test$input, res_test$output)
    expect_equal(res_test2$input, res_test2$output)
})


test_that("Convert H5T_ARRAY works", {
    dtype_array <- H5T_ARRAY$new(dtype_base=h5types$H5T_NATIVE_LLONG, dims=c(2,3))
    test_data <- array(1:120, dim=c(20,2,3))
    res_test <- convertRoundTrip(test_data, dtype_array, nelem=20)
    expect_equal(as.integer(res_test$input), res_test$output)
    expect_equal(dtype_array$get_array_ndims(), 2)
    expect_equal(dtype_array$get_array_dims(), c(2,3))
})


test_that("Convert H5T_VLEN works", {
    dtype_vlen <- H5T_VLEN$new(dtype_base=h5types$H5T_NATIVE_LLONG)
    test_data <- list(a=1:4, b=3:12, c=c(-1.5, 2.5))
    res_test <- convertRoundTrip(test_data, dtype_vlen)
    res_test_input_as_int <- unname(lapply(res_test$input, as.integer))
    expect_equal(res_test_input_as_int, res_test$output)
})


test_that("guess_dtype", {
    ## test array types
    int_array <- guess_dtype(as.integer(1:4), scalar=TRUE)
    expect_equal(int_array$get_class(), h5const$H5T_ARRAY)
    expect_equal(int_array$get_super()$get_class(), h5const$H5T_INTEGER)
    expect_equal(int_array$get_array_dims(), 4)
    int_array2 <- guess_dtype(matrix(as.integer(1:4), ncol=2), scalar=TRUE)
    expect_equal(int_array2$get_class(), h5const$H5T_ARRAY)
    expect_equal(int_array2$get_super()$get_class(), h5const$H5T_INTEGER)
    expect_equal(int_array2$get_array_dims(), c(2,2))

    ## test data frame
    cpd_type <- guess_dtype(data.frame(a=1:4, b=5:8/2), scalar=FALSE)
    expect_equal(cpd_type$get_class(), h5const$H5T_COMPOUND)
    expect_equal(cpd_type$get_cpd_labels(), c("a", "b"))
    expect_equal(cpd_type$get_cpd_classes(), c(h5const$H5T_INTEGER, h5const$H5T_FLOAT))
    
    ## test list
    list_equal_length_type <- guess_dtype(list(a=1:4, b=5:8/2), scalar=FALSE)
    expect_equal(list_equal_length_type$get_class(), h5const$H5T_COMPOUND)

    list_unequal_length_type <- guess_dtype(list(a=1:4, b=1:8), scalar=FALSE)
    expect_equal(list_unequal_length_type$get_class(), h5const$H5T_VLEN)
    
    ## test factor_ext
    factor_ext_type <- guess_dtype(factor_ext(c("a", "b"), values=2:3))
    expect_equal(factor_ext_type$get_class(), h5const$H5T_ENUM)
    
    ## test factor
    factor_ext_type <- guess_dtype(factor(c("a", "b")))
    expect_equal(factor_ext_type$get_class(), h5const$H5T_ENUM)

    ## test character
    char_type <- guess_dtype("asdf", string_len="estimate")
    expect_equal(char_type$get_class(), h5const$H5T_STRING)
    expect_equal(char_type$get_size(), 5)

    char_10_type <- guess_dtype("asdf", string_len = 10)
    expect_equal(char_10_type$get_class(), h5const$H5T_STRING)
    expect_equal(char_10_type$get_size(), 10)

    char_Inf_type <- guess_dtype("asdf", string_len = Inf)
    expect_equal(char_Inf_type$get_class(), h5const$H5T_STRING)
    expect_equal(char_Inf_type$get_size(), Inf)

    ## test logical
    logical_type <- guess_dtype(TRUE)
    expect_equal(logical_type$get_class(), h5const$H5T_ENUM)
    expect_equal(logical_type$get_labels(), c("FALSE", "TRUE", "NA"))
    
    ## test integer64
    int64_type <- guess_dtype(as.integer64(1))
    expect_equal(int64_type$get_class(), h5const$H5T_INTEGER)
    expect_equal(int64_type$get_size(), 8)
    
    ## test integer
    int_type <- guess_dtype(as.integer(1))
    expect_equal(int_type$get_class(), h5const$H5T_INTEGER)
    expect_equal(int_type$get_size(), 4)

    ## test numeric
    double_type <- guess_dtype(as.double(1))
    expect_equal(double_type$get_class(), h5const$H5T_FLOAT)
    expect_equal(double_type$get_size(), 8)

    ## test complex
    complex_type <- guess_dtype(complex(length.out=1, real=1, imaginary=1))
    expect_equal(complex_type$get_class(), h5const$H5T_COMPOUND)
    expect_equal(complex_type$get_cpd_labels(), c("Real", "Imaginary"))

    ## test matrix; here was a bug where it always created an array for a matrix
    ## that is why we have the test here
    int_dtype <- guess_dtype(matrix(as.integer(1:10), ncol=2))
    expect_equal(int_dtype$get_class(), h5const$H5T_INTEGER)
})

test_that("guess_space", {
    Robj <- matrix(1:100, nrow=10)
    dtype_int <- h5types$H5T_NATIVE_INT
    dtype_array <- H5T_ARRAY$new(dims=10, dtype_base=dtype_int)

    space_int_chunked <- guess_space(Robj, dtype_int, chunked=TRUE)
    expect_equal(space_int_chunked$get_simple_extent_dims(), list(rank=2, dims=c(10,10), maxdims=c(Inf, Inf)))
    space_int_unchunked <- guess_space(Robj, dtype_int, chunked=FALSE)
    expect_equal(space_int_unchunked$get_simple_extent_dims(), list(rank=2, dims=c(10,10), maxdims=c(10, 10)))
    space_array_chunked <- guess_space(Robj, dtype_array, chunked=TRUE)
    expect_equal(space_array_chunked$get_simple_extent_dims(), list(rank=1, dims=c(10), maxdims=c(Inf)))
    space_array_unchunked <- guess_space(Robj, dtype_array, chunked=FALSE)
    expect_equal(space_array_unchunked$get_simple_extent_dims(), list(rank=1, dims=c(10), maxdims=c(10)))
})


test_that("guess_chunks", {
    expect_equal(guess_chunks(c(10, 10), 8, 8 * 200), c(10,10))
    expect_equal(guess_chunks(c(100, 100), 8, 8 * 200), c(15,15))

    expect_equal(guess_chunks(c(5, 2, 4), 8, 8 * 200), c(5, 2, 4))
    expect_equal(guess_chunks(c(5, 2, 50), 8, 8 * 200), c(5, 2, 20))
    expect_equal(guess_chunks(c(50, 2, 50), 8, 8 * 200), c(10, 2, 10))
})

test_that("reorder", {
    array_rank3 <- array(as.integer(1:60), dim=c(3,4,5))
    ## item size is 4 bytes per integer
    array_reorder_c <- array_reorder(array_rank3, c(3,4,5), 2, 4:1, 4)
    array_reorder_r <- array_rank3[, 4:1,]
    expect_equal(array_reorder_c, array_reorder_r)
})


test_that("Logical with and without NA", {
    logical_NA <- c(TRUE, FALSE, NA)
    logical_noNA <- c(TRUE, FALSE)

    dtype_logical_noNA <- h5types$H5T_LOGICAL
    dtype_logical_NA <- h5types$H5T_LOGICAL_NA

    res_noNA_noNA <- convertRoundTrip(logical_noNA, dtype_logical_noNA)  
    res_NA_noNA <- try(convertRoundTrip(logical_NA, dtype_logical_noNA), silent=TRUE)  
    res_noNA_NA <- convertRoundTrip(logical_noNA, dtype_logical_NA)  
    res_NA_NA <- convertRoundTrip(logical_NA, dtype_logical_NA)

    expect_equal(res_noNA_noNA$input, res_noNA_noNA$output)
    expect_true(inherits(res_NA_noNA, "try-error"));
    expect_equal(res_noNA_NA$input, res_noNA_NA$output)
    expect_equal(res_NA_NA$input, res_NA_NA$output)
})

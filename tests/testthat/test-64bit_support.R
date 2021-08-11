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

context("64bit-support")

test_that("Dataset with more than 2^31 rows", {
    ## but will only support to the length of LONG accuracy
    ## just as normal R arrays
    large_space <- H5S$new(type="simple", dim=as.integer64(2)^33)

    ## first try that writing a hyperslab is done correctly
    large_space$select_hyperslab(start=1, count=1, stride=1, block=as.integer64(2)^32)
    expect_equal(large_space$get_select_hyper_blocklist()[,1], setNames(c(1, 2^32), c("block_1_start", "block_1_end")))

    ## now test that the reading also works correctly using the high-level array functionality
    large_space$select_none()
    large_space[2:2^32]
    expect_equal(large_space$get_select_hyper_blocklist()[,1], setNames(c(2, 2^32), c("block_1_start", "block_1_end")))
    large_space$select_none()
    large_space[as.integer64(2):(as.integer64(2)^32)]
    expect_equal(large_space$get_select_hyper_blocklist()[,1], setNames(c(2, 2^32), c("block_1_start", "block_1_end")))

    ## create a large dataset on disk for read/write test (won't actually be physically large in size
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")
    large_ds <- file.h5$create_dataset("large_ds", dtype=h5types$H5T_NATIVE_INT, space=large_space, chunk_dims=1e6, gzip_level = 4)
    large_ds[(2^32-10):(2^32+10)] <- 1:21
    expect_equal(large_ds[(2^32-20):(2^32+20)], c(rep(0L,10), 1:21, rep(0L, 10)))
    file.h5$close_all()
    file.remove(test_file)

})

truncateVec <- function(x, min, max) {
    # truncate values, leave na alone
    x[!is.na(x) & x < min] <- min
    x[!is.na(x) & x > max] <- max
    return(x)
}

value_LLONG_MAX <- function() {
    res <- bit64::as.integer64(0)
    for(i in 0:62) {
        res <- res + bit64::as.integer64(2)^i
    }
    return(res)
}

test_that("Datatype conversion with 64bit", {
    ## note that some of this duplicates some other tests in test-convert
    LLONG_MAX <- value_LLONG_MAX()
    dtype_uint64 <- h5types$H5T_NATIVE_ULLONG
    dtype_int64 <- h5types$H5T_NATIVE_LLONG

    ## first test the uint64 behaviour
    ## Should differ between truncation, NA and FLOAT_FORCE
    dbl_vec_pos <- c(1, 2, 2^31-1, 2^31, 2^32, 2^33, 2^62, 2^63, 1.5 * 2^63, 2^65)
    dbl_vec <- c(-dbl_vec_pos, dbl_vec_pos)
    dbl_vec_int64 <- suppressWarnings(bit64::as.integer64(dbl_vec))

    res_dbl_uint64_default <- hdf5r:::convertRoundTrip(dbl_vec, dtype_uint64, flags=h5const$H5TOR_CONV_NONE)
    res_dbl_uint64_na <- suppressWarnings(hdf5r:::convertRoundTrip(dbl_vec, dtype_uint64, flags=h5const$H5TOR_CONV_UINT64_NA))
    res_dbl_uint64_force <- hdf5r:::convertRoundTrip(dbl_vec, dtype_uint64, flags=h5const$H5TOR_CONV_INT64_FLOAT_FORCE)


    ## for truncation - need to convert to int64, then set NA to LLONG_MAX
    dbl_vec_int64_trunc <- suppressWarnings(bit64::as.integer64(dbl_vec))
    dbl_vec_int64_trunc[dbl_vec < 0] <- 0
    dbl_vec_int64_trunc[is.na(dbl_vec_int64_trunc)] <- LLONG_MAX
    dbl_vec_int64_na <- suppressWarnings(bit64::as.integer64(dbl_vec))
    suppressWarnings({
      dbl_vec_int64_na[18] <- dbl_vec_int64_na[18] + 1
    })
    dbl_vec_int64_na[dbl_vec < 0] <- 0
    expect_equal(suppressWarnings(truncateVec(dbl_vec_int64_trunc, 0, LLONG_MAX)), res_dbl_uint64_default$output)
    expect_equal(suppressWarnings(truncateVec(dbl_vec_int64_na, 0, LLONG_MAX)), res_dbl_uint64_na$output)

    dbl_vec_force <- truncateVec(dbl_vec, 0, 2^64) ## only trunctaed at uint64, not int64
    expect_equal(dbl_vec_force, res_dbl_uint64_force$output)


    ## now test the regular integer behaviour
    ## first, no conversion
    res_dbl_int64_default <- suppressWarnings(hdf5r:::convertRoundTrip(dbl_vec, dtype_int64, flags=h5const$H5TOR_CONV_NONE))
    expect_equal(dbl_vec_int64, res_dbl_int64_default$output)

    ## conversion to integer if no loss is incurred
    res_dbl_int64_int_noloss_short_int <- hdf5r:::convertRoundTrip(dbl_vec[abs(dbl_vec) < 2^31], dtype_int64,
                                                                   flags=h5const$H5TOR_CONV_INT64_INT_NOLOSS)
    expect_equal(as.integer(dbl_vec[abs(dbl_vec) < 2^31]), res_dbl_int64_int_noloss_short_int$output)

    res_dbl_int64_int_noloss_short_int_withNA <- hdf5r:::convertRoundTrip(c(dbl_vec[abs(dbl_vec) < 2^31], NA), dtype_int64,
                                                                   flags=h5const$H5TOR_CONV_INT64_INT_NOLOSS)
    expect_equal(as.integer(c(dbl_vec[abs(dbl_vec) < 2^31], NA)), res_dbl_int64_int_noloss_short_int_withNA$output)

    res_dbl_int64_int_noloss <- suppressWarnings(hdf5r:::convertRoundTrip(dbl_vec, dtype_int64,
                                                         flags=h5const$H5TOR_CONV_INT64_INT_NOLOSS))
    expect_equal(dbl_vec_int64, res_dbl_int64_int_noloss$output)

    ## covnersion to float if no loss is incurred
    res_dbl_int64_float_noloss_short_float <- hdf5r:::convertRoundTrip(dbl_vec[abs(dbl_vec) < 2^51], dtype_int64,
                                                           flags=h5const$H5TOR_CONV_INT64_FLOAT_NOLOSS)
    expect_equal(as.numeric(dbl_vec[abs(dbl_vec) < 2^51]), res_dbl_int64_float_noloss_short_float$output)

    res_dbl_int64_float_noloss_short_float_withNA <- hdf5r:::convertRoundTrip(c(dbl_vec[abs(dbl_vec) < 2^51], NA), dtype_int64,
                                                           flags=h5const$H5TOR_CONV_INT64_FLOAT_NOLOSS)
    expect_equal(as.numeric(c(dbl_vec[abs(dbl_vec) < 2^51], NA)), res_dbl_int64_float_noloss_short_float_withNA$output)

    res_dbl_int64_float_noloss <- suppressWarnings(hdf5r:::convertRoundTrip(dbl_vec, dtype_int64,
                                                           flags=h5const$H5TOR_CONV_INT64_FLOAT_NOLOSS))
    expect_equal(dbl_vec_int64, res_dbl_int64_int_noloss$output)


    ## conversion to integer or float if no loss is incurred
    res_dbl_int64_noloss <- suppressWarnings(hdf5r:::convertRoundTrip(dbl_vec, dtype_int64, flags=h5const$H5TOR_CONV_INT64_NOLOSS))
    expect_equal(dbl_vec_int64, res_dbl_int64_noloss$output)

    res_dbl_int64_noloss_short_int <- hdf5r:::convertRoundTrip(dbl_vec[abs(dbl_vec) < 2^31], dtype_int64,
                                                               flags=h5const$H5TOR_CONV_INT64_NOLOSS)
    expect_equal(as.integer(dbl_vec[abs(dbl_vec) < 2^31]), res_dbl_int64_noloss_short_int$output)
    res_dbl_int64_noloss_short_float <- hdf5r:::convertRoundTrip(dbl_vec[abs(dbl_vec) < 2^51], dtype_int64,
                                                                 flags=h5const$H5TOR_CONV_INT64_NOLOSS)
    expect_equal(as.numeric(dbl_vec[abs(dbl_vec) < 2^51]), res_dbl_int64_noloss_short_float$output)


    ## forced coercion to double
    suppressWarnings(res_dbl_int64_force <- hdf5r:::convertRoundTrip(dbl_vec, dtype_int64, flags=h5const$H5TOR_CONV_INT64_FLOAT_FORCE))
    expect_equal(suppressWarnings(as.numeric(dbl_vec_int64)), res_dbl_int64_force$output)


})

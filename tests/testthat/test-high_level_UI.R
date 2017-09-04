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

context("High-level-UI")

test_that("Names and [[", {
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")
    test1 <- file.h5$create_group("test1")
    test2 <- test1$create_group("test2")
    test3 <- file.h5$create_group("test3")

    expect_equal(names(file.h5), c("test1", "test3"))
    expect_equal(file.h5$names, c("test1", "test3"))
    expect_equal(names(test1), "test2")
    expect_equal(names(test2), character(0))

    test4 <- file.h5[["test1", dataset_access_pl=h5const$H5P_DEFAULT]]
    expect_equal(test1$get_obj_name(), test4$get_obj_name())
    test.error <- try(file.h5[["asdf"]], silent=TRUE)
    expect_true(inherits(test.error, "try-error"))


    ## now test various assignments
    ## first the group
    ## here we have to try test2; test1 in fact does not raise an error, as an hdf5 object can be assigned onto itself
    expect_true(inherits(try(file.h5[["test1"]] <- test2, silent=TRUE), "try-error"))
    file.h5[["test_hard_link"]] <- test1
    test_hard_link <- file.h5[["test_hard_link"]]
    ## should contain the same
    expect_equal(test_hard_link$obj_info(), test1$obj_info())

    ## now a dataset
    robj <- matrix(as.integer(1:20), ncol=4)
    test_dataset <- test1$create_dataset("test_dataset", robj)
    file.h5[["dataset_hard_link"]] <- test_dataset
    test_dataset_hl <- file.h5[["dataset_hard_link"]]
    expect_equal(test_dataset_hl$obj_info(), test_dataset$obj_info())

    ## and a type
    file.h5[["test_type"]] <- h5types$H5T_NATIVE_INT64
    expect_true(h5types$H5T_NATIVE_INT64$equal(file.h5[["test_type"]]))

    ## and a dataset
    file.h5[["test_dataset2"]] <- robj
    expect_equal(file.h5[["test_dataset2"]]$read(), robj)

    file.h5$close_all()
    file.remove(test_file)
})


index_logical <- c(TRUE, FALSE, TRUE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE)
index_regular <- c(3, 4, 5, 6)
index_regular2 <- c(3, 5, 7, 9)
index_positive <- c(1, 5, 6, 10, 15)
index_ident <- c(1, 3, 3, 6)
index_ident2 <- c(1, 3, 5, 1)
index_decreasing <- c(5, 4, 2, 1)
index_negative_all <- -index_regular
index_negative_some <- c(1, 3, -2, 5, 6)
index_large <- c(1, 20)
index_empty <- list(quote(expr=))


test_that("args_regularity_evaluation to selection", {
    ## first, check arg for hyperslab func, i.e. for functions that can directly be interpreted as a
    ## a range of example arguments
    a <- 4
    example_calls <- list(call(":", a, 8),
                          call("seq_len", 6),
                          call("seq", from=4, to=9, by=2),
                          call("seq", from=4, length.out=4, by=1),
                          call(":", -2, 2),
                          expression(1:5 / 10 * 2))
    check_for_func_res <- lapply(example_calls, hdf5r:::check_arg_for_hyperslab_func, envir=sys.frame())
    expect_equal(check_for_func_res, list(c(4, 1, 1, 5), c(1, 1, 1, 6), c(4, 3, 2, 1), c(4, 1, 1, 4), c(NA, NA, NA, NA), c(NA, NA, NA, NA)))

    example_indices <- list(index_logical,
                            index_regular,
                            index_regular2,
                            index_positive,
                            index_ident,
                            index_ident2,
                            index_decreasing,
                            index_negative_all,
                            index_large,
                            quote(expr=))
    ## now do the argument regularity evaluation
    ds_dims <- rep(10, length(example_indices))
    example_indices_regularity <- hdf5r:::args_regularity_evaluation(example_indices, ds_dims, envir=sys.frame())
    ## now need to check every component
    NA_hyperslab_row <- c(NA, NA, NA, NA)
    example_indices_intended_output <- list(
        args_in=example_indices,
        args_point=list(c(1, 3, 4, 6, 10), NULL, NULL, index_positive, unique(index_ident), NULL, sort(index_decreasing),
            seq_len(10)[index_negative_all], NULL, NULL),
        is_hyperslab=c(FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, TRUE, TRUE),
        ## hyperslab components: c("start", "count", "stride", "block")
        hyperslab=matrix(c(NA_hyperslab_row, c(3, 1, 1, 4), c(3, 4, 2, 1), NA_hyperslab_row, NA_hyperslab_row, c(1, 3, 2, 1),
            NA_hyperslab_row, NA_hyperslab_row, c(1, 2, 19, 1), c(1, 1, 1, 10)),
            byrow=TRUE, ncol=4, dimnames=list(NULL, c("start", "count", "stride", "block"))),
        result_dims_pre_shuffle=c(5, 4, 4, 5, 3, 3, 4, 6, 2, 10),
        result_dims_post_shuffle=c(5, 4, 4, 5, 4, 4, 4, 6, 2, 10),
        max_dims=c(10, 6, 9, 15, 6, 5, 5, 10, 20, 10),
        needs_reshuffle=c(FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE),
        reshuffle=list(NULL, NULL, NULL, NULL, c(1, 2, 2, 3), c(1, 2, 3, 1), c(4, 3, 2, 1), NULL, NULL, NULL)
        )
    expect_equal(example_indices_regularity, example_indices_intended_output)
    expect_error(hdf5r:::args_regularity_evaluation(list(index_negative_some), ds_dims=10, envir=sys.frame()))

    ## now need to translate the regularity evaluation either into a hyperslab or a pointlist selection
    ## three cases; one with only points; one with a hyperslab and points and one with only hyperslabs
    only_points_regularity <- hdf5r:::args_regularity_evaluation(list(index_positive, index_positive), ds_dims=c(10, 10), envir=sys.frame())
    mixed_regularity <- hdf5r:::args_regularity_evaluation(list(index_regular, index_positive), ds_dims=c(10, 10), envir=sys.frame())
    only_hyperslab_regularity <- hdf5r:::args_regularity_evaluation(list(index_regular, index_regular2, quote(expr=)),
                                                            ds_dims=c(10, 10, 10), envir=sys.frame())

    only_points_selection <- hdf5r:::regularity_eval_to_selection(only_points_regularity)
    mixed_selection <- hdf5r:::regularity_eval_to_selection(mixed_regularity)
    only_hyperslab_selection <- hdf5r:::regularity_eval_to_selection(only_hyperslab_regularity)

    expect_equal(only_points_selection, structure(matrix(c(rep(index_positive, times=5), rep(index_positive, each=5)), ncol=2), class="point_selection"))
    mixed_selection_array <- array(0, dim=c(2, 5, 4))
    mixed_selection_array[1,,] <- rep(c(3, 1, 1, 4), each=5)
    mixed_selection_array[2,,] <- 1
    mixed_selection_array[2,,1] <- index_positive
    expect_equal(mixed_selection, structure(mixed_selection_array, class="hyperslab_selection"))

    only_hyperslab_array <- array(0, dim=c(3, 1, 4))
    only_hyperslab_array[1,,] <- c(3, 1, 1, 4)
    only_hyperslab_array[2,,] <- c(3, 4, 2, 1)
    only_hyperslab_array[3,,] <- c(1, 1, 1, 10)
    expect_equal(only_hyperslab_selection, structure(only_hyperslab_array, class="hyperslab_selection"))
})



test_that("subset_h5.H5S", {
    ## create a dataspace
    h5s_obj <- H5S$new(type="simple", dims=c(15, 15, 20), maxdims=c(15, 15, 20))
    subset_h5.H5S(h5s_obj, seq_len(3), seq(2,4,by=3), 5:9)
    expect_equal(h5s_obj$get_select_type(), h5const$H5S_SEL_HYPERSLABS)
    expect_equal(h5s_obj$get_select_hyper_blocklist(), matrix(c(1,3,2,2,5,9), nrow=2, dimnames=list(c("block_1_start", "block_1_end"), NULL)))

    subset_h5.H5S(h5s_obj, seq_len(3), seq(2,4,by=3), c(1,2,4))
    expect_equal(h5s_obj$get_select_type(), h5const$H5S_SEL_POINTS)


    ## setting one that is outside the limits of the space
    expect_error(h5s_obj[16, 1, 1], "The following coordinates are outside the dataset dimensions: 1")


    ## complicated subsetting in various forms
    ## using logial
    ## using non-uniform index
    ## using decreasing index
    ## using negative index (all of them)
    ## using index (some of them)
    ## using index with several identical values
    ## GOAL: Ensure that a hyperslab selection is being done in the intended places

    ## index_logical <- c(TRUE, FALSE, TRUE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE)
    ## index_regular <- 3:6
    ## index_positive <- c(1, 5, 6, 10)
    ## index_ident <- c(1, 3, 3, 6)
    ## index_decreasing <- c(5, 4, 2, 1)
    ## index_negative_all <- -index_regular
    ## index_negative_some <- c(1, 3, -2, 5, 6)
    ## index_large <- c(1, 15)

    ## now make the tests with these indices; will use the h5s_obj
    ## only use single indices
    h5s_logical <- subset_h5.H5S(h5s_obj, index_logical, , )
    expect_equal(h5s_logical$get_select_type(), h5const$H5S_SEL_HYPERSLABS)

    h5s_regular <- subset_h5.H5S(h5s_obj, index_regular, ,)
    expect_equal(h5s_regular$get_select_type(), h5const$H5S_SEL_HYPERSLABS)

    h5s_positive <- subset_h5.H5S(h5s_obj, index_positive, ,)
    expect_equal(h5s_positive$get_select_type(), h5const$H5S_SEL_HYPERSLABS)

    h5s_ident <- subset_h5.H5S(h5s_obj, index_ident, ,)
    expect_equal(h5s_ident$get_select_type(), h5const$H5S_SEL_HYPERSLABS)

    h5s_ident2 <- subset_h5.H5S(h5s_obj, index_ident2, ,)
    expect_equal(h5s_ident$get_select_type(), h5const$H5S_SEL_HYPERSLABS)

    h5s_decreasing <- subset_h5.H5S(h5s_obj, index_decreasing, ,)
    expect_equal(h5s_decreasing$get_select_type(), h5const$H5S_SEL_HYPERSLABS)

    h5s_negative_all <- subset_h5.H5S(h5s_obj, index_negative_all, ,)
    expect_equal(h5s_negative_all$get_select_type(), h5const$H5S_SEL_HYPERSLABS)

    expect_error(subset_h5.H5S(h5s_obj, index_negative_some, ,), regexp=".*not all subscripts are either positive or negative")
    expect_error(subset_h5.H5S(h5s_obj, index_large, ,), "The following coordinates are outside the dataset dimensions:.*")

    ## also a few using double or triple indices
    ## logical should work, as it is recycled
    h5s_logical_double <- subset_h5.H5S(h5s_obj, index_logical, index_logical, )
    expect_equal(h5s_logical_double$get_select_type(), h5const$H5S_SEL_HYPERSLABS)

    h5s_logical_triple <- subset_h5.H5S(h5s_obj, index_logical, index_logical, index_logical)
    expect_equal(h5s_logical_double$get_select_type(), h5const$H5S_SEL_POINTS)

    h5s_logical_regular <- subset_h5.H5S(h5s_obj, index_logical, , index_regular)
    expect_equal(h5s_logical_regular$get_select_type(), h5const$H5S_SEL_HYPERSLABS)
})

test_that("subset_h5.H5D", {
    ## create a file with a dataset in it
    ## fill it with simple numbers and read it back
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")

    robj <- matrix(as.integer(1:40), ncol=4)
    file.h5[["test"]] <- robj
    test <- file.h5[["test"]]

    expect_equal(test[1:3, 2:4], robj[1:3, 2:4])

    expect_equal(test[c(1,3,4),], robj[c(1,3,4),])

    test[1:3, 2:4] <- 1:9
    expect_equal(test[1:3, 2:4], matrix(1:9, ncol=3))

    ## write outside of the current set
    ## will trigger an automatic expansion of the current set if possible
    test[11:15, ] <- 1:20
    expect_equal(as.vector(test[11:15,]), 1:20)

    ## also test an indirect subsetting
    get_1 <- function(i, ds) {
        return(ds[i,])
    }
    expect_equal(get_1(11, test), c(1, 6, 11, 16))


    ## need to recreate an error where writing into an array failed when there was a missing dimension
    ## and the other given dimension was a a variable
    test2 <- file.h5$create_dataset("test_array", dtype=h5types$H5T_NATIVE_INT, space=H5S$new("simple", dims=c(10,10,100)),
                           chunk_dims=c(10,10,1))
    pos_list <- list(1)
    test2[,,pos_list[[1]]] <- 1:100
    expect_equal(test2[,,1], matrix(1:100, ncol=10))

    ## need to ensure that an error is thrown when requesting a too large dimension
    expect_error(test2[11, ,], "The following coordinates are outside the dataset dimensions: 1")

    file.h5$close_all()
    file.remove(test_file)
})


test_that("attributes", {
    ## open a file, set 2 attributes, read out their names
    ## read them both, read them separately

    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")

    robj1 <- matrix(as.integer(1:10), ncol=2)
    robj2 <- paste("Test", 1:10)

    h5attr(file.h5, "integer") <- robj1
    h5attr(file.h5, "character") <- robj2

    expect_equal(sort(h5attr_names(file.h5)), sort(c("integer", "character")))
    all_attr <- h5attributes(file.h5)
    expect_equal(all_attr$integer, robj1)
    expect_equal(all_attr$character, robj2)

    expect_equal(h5attr(file.h5, "integer"), robj1)
    expect_equal(h5attr(file.h5, "character"), robj2)

    h5attr(file.h5, "integer") <- robj2
    expect_equal(h5attr(file.h5, "integer"), robj2)



    file.h5$close_all()
    file.remove(test_file)
})


test_that("Subsetting dimensions, drop and write", {
    test_file <- tempfile(fileext=".h5")
    file.h5 <- H5File$new(test_file, mode="w")

    ex_array <- array(1:60, dim=c(3,4,5))
    file.h5[["ex_array"]] <- ex_array
    ex_arr_ds <- file.h5[["ex_array"]]

    expect_equal(ex_arr_ds[2,,],  ex_array[2,,])
    expect_equal(ex_arr_ds[,2,],  ex_array[,2,])
    expect_equal(ex_arr_ds[,,2],  ex_array[,,2])

    expect_equal(ex_arr_ds[2,,, drop=FALSE],  ex_array[2,,, drop=FALSE])
    expect_equal(ex_arr_ds[,2,, drop=FALSE],  ex_array[,2,, drop=FALSE])
    expect_equal(ex_arr_ds[,,2, drop=FALSE],  ex_array[,,2, drop=FALSE])

    ## now test the repeated write
    ex_arr_ds[,,] <- 1
    ex_array[,,] <- 1
    expect_equal(ex_array[,,], ex_arr_ds[,,])
    ex_arr_ds[,,] <- c(1,2,3)
    ex_array[,,] <- c(1,2,3)
    expect_equal(ex_array[,,], ex_arr_ds[,,])


    ## complicated subsetting in various forms
    ## using logial
    ## using non-uniform index
    ## using decreasing index
    ## using index with several identical values
    ## GOAL: Ensure the correct values are being returned
    ex_array2 <- array(as.numeric(seq_len(15 * 15* 20)), dim=c(15, 15, 20))
    file.h5[["ex_array2"]] <- ex_array2
    ex_array2_ds <- file.h5[["ex_array2"]]

    ## index_logical <- c(TRUE, FALSE, TRUE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE)
    ## index_regular <- 3:6
    ## index_regular2 <- c(3, 5, 7, 9)
    ## index_positive <- c(1, 5, 6, 8, 10)
    ## index_ident <- c(1, 3, 3, 6)
    ## index_decreasing <- c(5, 4, 2, 1)
    ## index_negative_all <- -index_regular
    ## index_negative_some <- c(1, 3, -3, 5, 6)
    ## index_large <- c(1, 15)

    ## a read/write test
    copy_change_test_reset_array <- function(hdf5_ds, r_ds, index) {
        ## make a read test
        expect_equal(hdf5_ds[index,,], r_ds[index,,])
        r_ds_changed <- r_ds
        replace_vals <- runif(length(r_ds[index,,]))
        r_ds_changed[index, ,] <- replace_vals
        hdf5_ds[index, ,] <- replace_vals
        hdf5_ds_read <- hdf5_ds[index, ,]
        ## and reset
        hdf5_ds[, ,] <- r_ds
        expect_equal(hdf5_ds_read, r_ds_changed[index, ,])
        return(invisible(NULL))
    }
    copy_change_test_reset_array(ex_array2_ds, ex_array2, index_logical)
    copy_change_test_reset_array(ex_array2_ds, ex_array2, index_regular)
    copy_change_test_reset_array(ex_array2_ds, ex_array2, index_regular2)
    copy_change_test_reset_array(ex_array2_ds, ex_array2, index_positive)
    copy_change_test_reset_array(ex_array2_ds, ex_array2, index_ident)
    copy_change_test_reset_array(ex_array2_ds, ex_array2, index_ident2)
    copy_change_test_reset_array(ex_array2_ds, ex_array2, index_decreasing)
    copy_change_test_reset_array(ex_array2_ds, ex_array2, index_negative_all)
    expect_equal(ex_array2_ds[,,], ex_array2[,,])

    expect_error(ex_array2_ds[index_large, ], "Number of arguments not equal to number of dimensions: 2 vs. 3")
    expect_error(ex_array2_ds[index_negative_some, ,], "In index 1 not all subscripts are either positive or negative")
    expect_error(ex_array2_ds[index_large,, ], "The following coordinates are outside the dataset dimensions:.*")

    ## also a few using double or triple indices
    ## logical should work, as it is recycled
    expect_equal(ex_array2_ds[index_logical, index_logical,], ex_array2[index_logical, index_logical,])
    expect_equal(ex_array2_ds[index_logical, index_logical, index_logical], ex_array2[index_logical, index_logical, index_logical])
    expect_equal(ex_array2_ds[index_logical, , index_regular], ex_array2[index_logical, , index_regular])


    ## we also want to try the same for compounds
    ex_cpd <- data.frame(a=LETTERS[1:15], b=1:15, stringsAsFactors = FALSE)
    file.h5[["ex_cpd"]] <- ex_cpd
    ex_cpd_ds <- file.h5[["ex_cpd"]]

    ## then also writing it
    copy_change_test_reset_cpd <- function(hdf5_cpd, r_cpd, index) {
        # and reset
        hdf5_cpd[] <- r_cpd
        ## make a read test
        ## for data.frame we currently ignore the row numbers
        hdf5_cpd_read <- hdf5_cpd[index]
        rownames(hdf5_cpd_read) <- NULL
        r_cpd_read <- r_cpd[index,]
        rownames(r_cpd_read) <- NULL
        expect_equal(hdf5_cpd_read, r_cpd_read)
        r_cpd_changed <- r_cpd
        replace_length <- nrow(r_cpd[index,])
        replace_vals <- data.frame(a=sample(LETTERS, size=replace_length), b=sample(1:50, size=replace_length), stringsAsFactors = FALSE)
        r_cpd_changed[index,] <- replace_vals
        hdf5_cpd[index] <- replace_vals

        hdf5_cpd_read <- hdf5_cpd[]
        # and reset
        hdf5_cpd[] <- r_cpd
        ## check everything after the write
        expect_equal(hdf5_cpd_read, r_cpd_changed[,])
        return(invisible(NULL))
    }
    copy_change_test_reset_cpd(ex_cpd_ds, ex_cpd, index_logical)
    copy_change_test_reset_cpd(ex_cpd_ds, ex_cpd, index_regular)
    copy_change_test_reset_cpd(ex_cpd_ds, ex_cpd, index_regular2)
    copy_change_test_reset_cpd(ex_cpd_ds, ex_cpd, index_positive)
    copy_change_test_reset_cpd(ex_cpd_ds, ex_cpd, index_ident)
    copy_change_test_reset_cpd(ex_cpd_ds, ex_cpd, index_decreasing)
    copy_change_test_reset_cpd(ex_cpd_ds, ex_cpd, index_negative_all)

    expect_error(ex_cpd_ds[index_large, ], "Number of arguments not equal to number of dimensions: 2 vs. 1")
    expect_error(ex_cpd_ds[index_negative_some], "In index 1 not all subscripts are either positive or negative")
    expect_error(ex_cpd_ds[index_large], "The following coordinates are outside the dataset dimensions:.*")

    ## create a dataset with maximal dimensions
    ## check that writing dimensions less than the maximum is ok, but larger than
    ## the maximum will fail
    h5s_finite_maxdims <- H5S$new(type="simple", dims=c(5, 10, 15), maxdims=c(10, 15, 20))
    h5d_finite_maxdims <- file.h5$create_dataset(name="ds_finite_maxdims", dtype=h5types$H5T_NATIVE_DOUBLE, space=h5s_finite_maxdims)
    h5d_finite_maxdims[10, ,1:10 ] <- 1:100
    expect_equal(h5d_finite_maxdims$dims, c(10, 10, 15))
    expect_error({h5d_finite_maxdims[11, , ] <- 151:300}, regexp="The following coordinates are larger than the largest possible dataset dimensions \\(maxdims\\): 1")




    file.h5$close_all()
    file.remove(test_file)

})


test_that("Check if index is ok before expand", {
    test_file <- tempfile(fileext=".h5")
    file.h5 <- H5File$new(test_file, mode="w")

    ex_dset <- array(81, dim=c(9,9))
    file.h5[["dset"]] <- ex_dset

    dset <- file.h5[["dset"]]

    ## needs to throw an error as too many elements
    expect_error({dset[10:11, 9] <- matrix(rep(0, 2*9), nrow = 2)})

    ## needs to throw an error if dimensions have changed
    expect_equal(dset$dims, c(9,9)) 
    file.h5$close_all()
    file.remove(test_file)
})


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




context("HDF5 Reference objects")
test_that("Subsetting raw vector with c code", {

    ## test reading and writing of a subset of a raw vector using C code
    subset_test <- as.raw(0:255)
    index <- c(1:5, 9)

    ## item_size 16
    subset_read <- .Call("R_read_raw_subset_generic", subset_test, index, 16, PACKAGE = "hdf5r")
    subset_write <- .Call("R_write_raw_subset_generic", subset_test, as.raw(0:95), index, 16, PACKAGE = "hdf5r")
    expect_equal(subset_read, subset_test[1:16 + 16 * rep(index, each=16)])
    subset_test_write <- subset_test
    subset_test_write[1:16 + 16 * rep(index, each=16)] <- as.raw(0:95)
    expect_equal(subset_write, subset_test_write)

    ## item_size 8
    subset_read <- .Call("R_read_raw_subset_generic", subset_test, index, 8, PACKAGE = "hdf5r")
    subset_write <- .Call("R_write_raw_subset_generic", subset_test, as.raw(0:47), index, 8, PACKAGE = "hdf5r")
    expect_equal(subset_read, subset_test[1:8 + 8 * rep(index, each=8)])
    subset_test_write <- subset_test
    subset_test_write[1:8 + 8 * rep(index, each=8)] <- as.raw(0:47)
    expect_equal(subset_write, subset_test_write)

    ## item_size 4
    subset_read <- .Call("R_read_raw_subset_generic", subset_test, index, 4, PACKAGE = "hdf5r")
    subset_write <- .Call("R_write_raw_subset_generic", subset_test, as.raw(0:23), index, 4, PACKAGE = "hdf5r")
    expect_equal(subset_read, subset_test[1:4 + 4 * rep(index, each=4)])
    subset_test_write <- subset_test
    subset_test_write[1:4 + 4 * rep(index, each=4)] <- as.raw(0:23)
    expect_equal(subset_write, subset_test_write)

    ## item_size 1
    subset_read <- .Call("R_read_raw_subset_generic", subset_test, index, 1, PACKAGE = "hdf5r")
    subset_write <- .Call("R_write_raw_subset_generic", subset_test, as.raw(0:5), index, 1, PACKAGE = "hdf5r")
    expect_equal(subset_read, subset_test[index + 1])
    subset_test_write <- subset_test
    subset_test_write[1 +  index] <- as.raw(0:5)
    expect_equal(subset_write, subset_test_write)


})

test_that("Subsetting reference vector", {
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")

    ref_obj <- H5R_OBJECT$new(id=file.h5)
    ref_obj$ref <- as.raw(0:191)
    
    ref_obj_vector <- ref_obj$clone()
    ref_obj_vector$names <- LETTERS[1:24]
    expect_equal(ref_obj_vector$length, 24)

    ## now test various ways of subsetting
    expect_equal(ref_obj_vector$subset_read(c("A", "C")), ref_obj_vector$subset_read(c(1, 3)))

    expect_equal(ref_obj_vector$subset_read(c("A", "C"))$ref, c(as.raw(0:7), as.raw(16:23)))
    expect_equal(ref_obj_vector$subset_read(c("A", "C"))$names, c("A", "C"))

    expect_equal(ref_obj_vector[c("A", "C")], ref_obj_vector$subset_read(c(1, 3)))
    

    ## test the subsetting as an array
    ref_obj_array <- ref_obj$clone()
    ref_obj_array$dim <- c(4,6)
    ref_obj_array$dimnames <- list(LETTERS[1:4], tolower(LETTERS[1:6]))
    expect_equal(ref_obj_array$length, 24)

    expect_equal(ref_obj_array$subset_read(list(c("A", "C"), "a")), ref_obj_array$subset_read(list(c(1, 3), 1)))
    expect_equal(ref_obj_array$subset_read(list(c("A", "C"), "a"))$ref, c(as.raw(0:7), as.raw(16:23)))
    expect_equal(ref_obj_array$subset_read(list(c("A", "C"), "a"))$dim, NULL)
    expect_equal(ref_obj_array$subset_read(list(c("A", "C"), "a"), drop=FALSE)$dim, c(2,1))
    
    expect_equal(ref_obj_array[c("A", "C"), "a"], ref_obj_array$subset_read(list(c(1, 3), 1)))

    ## test assigning data into the vector
    ## vector to insert into the other objects
    ref_inserted <- ref_obj$ref
    obj_to_insert <- as.raw(100:115)
    ref_inserted[c(1:8, 17:24)] <- obj_to_insert

    ref_obj_vector_inserted <- ref_obj_vector$clone()
    ref_obj_vector_inserted$ref <- ref_inserted

    ref_obj_array_inserted <- ref_obj_array$clone()
    ref_obj_array_inserted$ref <- ref_inserted

    ## Vector
    expect_equal(ref_obj_vector$clone()$subset_assign(c("A", "C"), value=obj_to_insert ), ref_obj_vector_inserted)
    expect_equal(ref_obj_vector$clone()$subset_assign(c(1,3), value=obj_to_insert), ref_obj_vector_inserted)

    ## [<-
    ref_obj_vector_cloned <- ref_obj_vector$clone()
    ref_obj_vector_cloned[c("A", "C")] <- obj_to_insert
    expect_equal(ref_obj_vector_cloned, ref_obj_vector_inserted)

    ## Array
    expect_equal(ref_obj_array$clone()$subset_assign(list(c("A", "C"), "a"), value=obj_to_insert ), ref_obj_array_inserted)
    expect_equal(ref_obj_array$clone()$subset_assign(list(c(1,3), 1), value=obj_to_insert), ref_obj_array_inserted)

    ## [<-
    ref_obj_array_cloned <- ref_obj_array$clone()
    ref_obj_array_cloned[c("A", "C"), "a"] <- obj_to_insert
    expect_equal(ref_obj_array_cloned, ref_obj_array_inserted)

    ref_obj <- H5R_DATASET_REGION$new(id=file.h5)
    ref_obj$ref <- as.raw(0:191)
    expect_equal(ref_obj$length, 16)


    ## test one item subsetting and writing
    ref_obj_subsetted <- H5R_OBJECT$new(id=file.h5)
    ref_obj_subsetted$ref <- ref_obj$ref[25:32]

    ref_obj_written <- ref_obj_vector$clone()
    ref_obj_written$ref[25:32] <- as.raw(0:7)

    expect_equal(ref_obj_vector$subset2_read(4), ref_obj_subsetted)
    expect_equal(ref_obj_vector$subset2_read("D"), ref_obj_subsetted)

    ## not doing [[, but [ as [[ is used by R6 itself
    ## [[
    ref_obj_vector_elemD <- ref_obj_vector["D"]
    ref_obj_vector_elemD$names <- NULL
    expect_equal(ref_obj_vector_elemD, ref_obj_subsetted)

    expect_equal(ref_obj_vector$clone()$subset2_assign(4, value=as.raw(0:7)), ref_obj_written)
    expect_equal(ref_obj_vector$clone()$subset2_assign("D", value=as.raw(0:7)), ref_obj_written)

    ## [[<-
    ref_obj_vector_cloned <- ref_obj_vector$clone()
    ref_obj_vector_cloned["D"] <- as.raw(0:7)
    expect_equal(ref_obj_vector_cloned, ref_obj_written)

    ## test that [i] and [i,] give different results
    expect_equal(ref_obj_array[1,]$length, 6)
    expect_equal(ref_obj_array[1]$length, 1)

    ## test setting of a dim attribute using the C-function
    .Call("set_dim_attribute", ref_obj_array, c(6, 4), PACKAGE = "hdf5r")
    expect_equal(ref_obj_array$dim, c(6, 4))
    
    file.h5$close_all()
    file.remove(test_file)

})


test_that("UI functions for reference vector", {
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")

    r1 <- H5R_OBJECT$new(id=file.h5)
    r1$ref <- as.raw(0:31)
    r1$names <- c("A", "B", "C", "D")
    r2 <- H5R_OBJECT$new(id=file.h5)
    r2$ref <- as.raw(8:23)
    r3 <- H5R_OBJECT$new(id=file.h5)
    r3$ref <- as.raw(16:31)
    r3$names <- c("E", "F")

    ## concatenate
    r_concat <- c(r1, r2, r3)
    r_concat_compare <- H5R_OBJECT$new(id=file.h5)
    r_concat_compare$ref <- c(r1$ref, r2$ref, r3$ref)
    r_concat_compare$names <- c("A", "B", "C", "D", "", "", "E", "F")
    expect_equal(r_concat, r_concat_compare)
    
    ## make them all to matrices
    r1$dim <- c(2, 2)
    r2$dim <- c(2, 1)
    r3$dim <- c(2, 1)

    ## assign dimnames to the first one
    r1$dimnames <- list(c("A", "B"), c("C", "D"))
    
    ## bind them together by columns
    r_cbind <- cbind(r1, r2, r3)

    ## transpose them and row bind them
    r1_t <- t(r1)
    r2_t <- t(r2)
    r3_t <- t(r3)
    r1_t_cmp <- cbind(r1[1,], r1[2,])
    dimnames(r1_t_cmp) <- dimnames(r1_t)
    expect_equal(r1_t, r1_t_cmp)
    
    r_rbind <- rbind(r1_t, r2_t, r3_t)
    expect_equal(t(r_rbind), r_cbind)
    

    ## put them into a data-frame
    r_df <- data.frame(r1=r1, r2=r2, r3=r3)
    expect_equal(dim(r_df), c(2,4))
    file.h5$close_all()
    file.remove(test_file)

})


test_that("Create and dereference references; save in a dataset", {
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")
    grp1 <- file.h5$create_group("test1")

    ## test an object reference
    ref <- grp1$create_reference()
    grp1_ref <- ref$dereference()[[1]]
    expect_equal(grp1$obj_info(), grp1_ref$obj_info())

    ## test a dataset region reference
    grp1[["test_data"]] <- matrix(1:40, ncol=4)

    ds <- grp1[["test_data"]]
    ds_space <- ds$get_space()
    ds_space <- ds_space[2:5, 1:2]
    ds_ref_1 <- ds$create_reference(2:5, 1:2)
    ds_ref_2 <- grp1$create_reference("test_data", ds_space)

    ## now de-reference again
    ds_ref_1$dereference()
    ds_ref_1$dereference(get_value=TRUE)

    expect_equal(ds_ref_1$dereference(get_value=TRUE)[[1]], ds[2:5, 1:2])
    expect_equal(ds_ref_2$dereference(get_value=TRUE)[[1]], ds[2:5, 1:2])

    ## now save them in a dataset and read them back out
    
    file.h5[["obj_ref_dataset"]] <- ref
    file.h5[["dset_ref_dataset"]] <- ds_ref_1

    ref_read <- file.h5[["obj_ref_dataset"]][]
    ds_ref_read <- file.h5[["dset_ref_dataset"]][]

    expect_equal(ref_read$dereference()[[1]]$obj_info(), grp1$obj_info())
    expect_equal(ds_ref_read$dereference(get_value=TRUE)[[1]], ds[2:5, 1:2])
    
    file.h5$close_all()
    file.remove(test_file)

})



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

context("H5File and H5Group")

test_that("File creation", {
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")
    ## test that ls works on an empty file
    file.h5$ls()
    
    test1 <- file.h5$create_group("test1")
    test2 <- test1$create_group("test2")

    file_ls <- file.h5$ls(recursive=TRUE)
    expect_equal(file_ls$name, c("test1", "test1/test2"))

    ## also check that ls prints the dimension of a file in the appropriate order when doing ls
    file.h5[["test_matrix"]] <- matrix(0, nrow=10, ncol=5)
    file.h5[["test_vector"]] <- numeric(10)
    ls_res <- file.h5$ls()
    ls_matrix <- ls_res[ls_res$name == "test_matrix",]
    expect_equal(ls_matrix$dataset.dims, "10 x 5")
    expect_equal(ls_matrix$dataset.rank, 2)
    ls_vector <- ls_res[ls_res$name == "test_vector",]
    expect_equal(ls_vector$dataset.dims, "10")
    expect_equal(ls_vector$dataset.rank, 1)
    
    ## test that we can open the group by name and by index
    test1_opened <- file.h5$open("test1")
    test1_opened_idx <- file.h5$open_by_idx(0)
    test2_opened <- test1_opened$open("test2")
    expect_equal(test1_opened$get_obj_name(), test1_opened_idx$get_obj_name())
    expect_equal(test2$get_obj_name(), test2_opened$get_obj_name())

    ## check that exists works
    expect_true(file.h5$exists("test1"))
    expect_true(file.h5$exists("/test1/test2"))
    expect_true(file.h5$path_valid("/test1/test2"))
    
    ## create a new link
    test3 <- test1$link(test2, "test3")

    ## create a new file; copy a group into it; copy a group out of it
    test_file2 <- tempfile(fileext=".h5")
    file.h5.new <- H5File$new(test_file2, mode="w")
    file.h5.new$obj_copy_from(file.h5, "test1", "test_1_copy_from")
    file.h5$obj_copy_to(file.h5.new, "test1_copy_to", "test1")

    ## test getting obj_info in various ways
    obj_info_test1 <- test1$obj_info()
    obj_info_test1_byname <- file.h5$obj_info_by_name("test1")
    obj_info_test1_byindex <- file.h5$obj_info_by_idx(0)
    expect_equal(obj_info_test1, obj_info_test1_byname)
    expect_equal(obj_info_test1, obj_info_test1_byindex)

    ## not just obj info, but also group info
    root_info <- file.h5$group_info()
    test1_info <- test1$group_info()
    root_info_by_name <- file.h5$group_info_by_name(".")
    root_info_by_idx <- file.h5$group_info_by_idx(0)
    expect_equal(root_info, root_info_by_name)
    expect_equal(test1_info, root_info_by_idx)

    ## retrieve the filesize and info and name
    ## in order not to get an error on OSx, need to replace // in filename
    expect_equal(normalizePath(file.h5$get_filename(), mustWork = FALSE), normalizePath(test_file, mustWork=FALSE))
    expect_true(nrow(file.h5$file_info()) == 1)
    expect_true(file.h5$get_filesize() > 0)
        
    ## close the testfile
    file.h5$close_all()
    file.h5.new$close_all()
    expect_true(is_hdf5(test_file))
    
    ## open the testfile again in various different modes
    file.h5 <- H5File$new(test_file, mode="a")
    expect_true(file.h5$exists("test1"))
    file.h5$close_all()
    
    file.h5 <- H5File$new(test_file, mode="r+")
    expect_true(file.h5$exists("test1"))
    file.h5$close_all()

    file.h5 <- H5File$new(test_file, mode="r")
    expect_true(file.h5$exists("test1"))
    file.h5$close_all()

    suppressWarnings(foo <- try({file.h5 <- H5File$new(test_file, mode="x")}, silent=TRUE))
    expect_true(inherits(foo, "try-error"))

    
    test_file3 <- tempfile(fileext=".h5")
    file.h5 <- H5File$new(test_file3, mode="x")
    expect_true(!is.na(file.h5$id))
    file.h5$close_all()
    
    file.remove(test_file)
    file.remove(test_file2)
    file.remove(test_file3)
})



test_that("File mounting", {
    test_file <- tempfile(fileext=".h5")
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")

    test_file2 <- tempfile(fileext=".h5")
    file2.h5 <- H5File$new(test_file2, mode="w")

    ## now create a a group in each of them, as well as some data
    grp1 <- file.h5$create_group("grp1")
    grp2 <- file2.h5$create_group("grp2")

    file.h5[["grp1"]][["num_vec"]] <- 1:10
    file2.h5[["grp2"]][["char_vec"]] <- LETTERS[1:10]

    
    file.h5$mount("grp1", file2.h5)

    grp1_mount <- file.h5[["grp1"]]

    ## now check what can be accesses using ls
    ## from grp1 - only the dataset
    ## from grp1_mount, we can access grp2
    expect_equal(grp1$ls()$name, "num_vec")
    expect_equal(grp1_mount$ls()$name, "grp2")

    expect_equal(grp1$group_info()$mounted, 1)
    expect_equal(grp1_mount$group_info()$mounted, 0)

    ## now unmount
    file.h5$unmount("grp1")
    expect_equal(grp1$group_info()$mounted, 0)
    expect_equal(file.h5[["grp1"]]$ls()$name, "num_vec")
   
    file.h5$close_all()
    file2.h5$close_all()
    file.remove(test_file)
    file.remove(test_file2)
})

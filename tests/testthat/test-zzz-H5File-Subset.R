context("h5-H5File-Subset")
fname <- tempfile(fileext=".h5")

test_that("H5File-Subset-Group",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")

  f <- function() file[[c("1", "2", "3")]]
  expect_that(f(), throws_error("An object with name 1 does not exist in this group"))

  group3 <- createGroup(file, "/testgroup3")
  expect_that(group3, is_a("H5Group"))
  expect_that(group3$get_obj_name(), is_identical_to("/testgroup3"))

  groupnested <- createGroup(group3, "test")
  expect_that(groupnested, is_a("H5Group"))
  expect_that(groupnested$get_obj_name(), is_identical_to("/testgroup3/test"))
  h5close(groupnested)
  h5close(group3)

  group3 <- file[["/testgroup3"]]
  grouprelative <- group3[["test"]]
  expect_that(grouprelative, is_a("H5Group"))
  expect_that(grouprelative$get_obj_name(), is_identical_to("/testgroup3/test"))
  h5close(grouprelative)
  h5close(group3)

  # TODO(mario): recursive group creation
  # group5 <- file["/test1/test2/test3/test4/test5"]


  # expect_that(group5, is_a("H5Group"))
  # expect_that(group5@location, is_identical_to("/test1/test2/test3/test4/test5"))
  # h5close(group5)
  h5close(file)
  expect_true(file.remove(fname))
})

test_that("H5File-Subset-DataSet",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")

  # TODO(mario): Implicit, recursive group creation?
  # group5 <- file["/test1/test2/test3/test4/test5"]

  g1 <- createGroup(file, "test/test1/test2/test3")
  g1[["dset1"]] <- 1:10
  g1[["dset2"]] <- matrix(1:9, nrow = 3)
  g1[["dset3"]] <- array(1:6, dim = c(1, 2, 3))
  file[["dset4"]] <- matrix(1:10, nrow = 5)

  # TODO: should work without h5close()
  h5close(g1)
  h5close(file)

  file <- h5file(fname, "r")
  dset <- file[["test/test1/test2/test3/dset1"]]
  expect_that(readDataSet(dset), is_identical_to(1:10))
  h5close(dset)

  dset <- file[["test/test1/test2/test3/dset2"]]
  expect_that(readDataSet(dset), is_identical_to(matrix(1:9, nrow = 3)))
  h5close(dset)

  # TODO(mario): Does array retrieval work?
  # dset <- file[["test/test1/test2/test3/dset3"]]
  # expect_that(readDataSet(dset), is_identical_to(array(1:6, dim = c(1, 2, 3))))
  # h5close(dset)

  dset <- file[["dset4"]]
  expect_that(readDataSet(dset), is_identical_to(matrix(1:10, nrow = 5)))
  h5close(dset)

  # check subsets
  # TODO: should work without h5close()
  dset <- file[["test/test1/test2/test3/dset1"]]
  expect_that(dset[1:5], is_identical_to(1:5))
  h5close(dset)

  dset <- file[["test/test1/test2/test3/dset2"]]
  expect_that(dset[1:2,], is_identical_to(matrix(1:9, nrow = 3)[1:2,]))
  h5close(dset)

  # TODO(mario): Does array retrieval work?
  # dset <- file[["test/test1/test2/test3/dset3"]]
  # expect_that(dset[1,1:2,3],
  #     is_identical_to(array(1:6, dim = c(1, 2, 3))[1,1:2,3,drop = FALSE]))
  # h5close(dset)

  # set subsets
  # TODO: include test cases
  h5close(file)
  expect_true(file.remove(fname))
})


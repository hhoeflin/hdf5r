context("h5-DataSet-createDataset")

fname <- tempfile(fileext=".h5")

test_that("DataSet-createDataset",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")

  f <- function() dset1 <- createDataSet(file, "testmat_n")
  expect_that(f(), throws_error("If a sample robj is not provided, then dtype has to be given"))

  h5close(file)
  expect_true(file.remove(fname))
})

test_that("DataSet-createDataset-chunksize",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")

  f <- function() dset1 <- createDataSet(file, "testmat_n", 1:10, chunk_dims = "test")
  expect_that(f(), throws_error("In RToH5_INTEGER can't convert type of object passed"))

  dset_c9 <- createDataSet(file, "test_chunk_9", 1:10, chunk_dims = 9)
  h5close(dset_c9)

  dset_c1 <- createDataSet(file, "test_chunk_1", 1:10, chunk_dims = 1)
  h5close(dset_c1)

  f <- function() dset_c0 <- createDataSet(file, "test_chunk_0", 1:10, chunk_dims = 0)
  expect_that(f(), throws_error("all chunk dimensions must be positive"))

  # TODO (mario): Create dataset without chunking?
  # ds_nochunk <- createDataSet(file, "dset", 1:3, chunk_dims = NA)
  # expect_that(ds_nochunk@chunksize, is_identical_to(NA_real_))
  # expect_that(ds_nochunk@maxdim, is_identical_to(3))
  # expect_that(ds_nochunk@compression, is_identical_to(character(0)))
  # h5close(ds_nochunk)

  # TODO (mario): Get Chunk size from dataset
  # ds_chunk <- createDataSet(file, name = "dset2", robj = 1:3)
  # expect_that(ds_chunk@chunksize, is_identical_to(3))
  # expect_that(ds_chunk@maxdim, is_more_than(1e+19))
  # expect_that(ds_chunk@compression , is_identical_to("H5Z_FILTER_DEFLATE"))
  # expect_that(ds_chunk@datatype, is_identical_to("i"))
  # h5close(ds_chunk)
  h5close(file)
  expect_true(file.remove(fname))
})

test_that("DataSet-createDataset-maxdimensions",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")

  # TODO(mario): H5S$new(maxdims = "test") should immediately throw error
  dspace <- H5S$new(maxdims = "test")
  #f <- function() dset1 <- createDataSet(file, "testmat_n", 1:10, chunk_dims = "test", space = dspace)
  #expect_that(f(), throws_error("Parameter maxdimensions must be of type integer"))

  f <- function() dspace2 <- H5S$new(dims = c(10), maxdims = c(Inf, Inf))
  expect_that(f(), throws_error("maxdims, if it is not NULL, has to be of the same length as dims"))

  f <- function() dspace2 <- H5S$new(dims = c(10), maxdims = c(9))
  expect_that(f(), throws_error("maxdims is smaller than dims"))

  dspace2 <- H5S$new(dims = c(10), maxdims = c(10))
  dset_md_10 <- createDataSet(file, "test_md_10", 1:10, space = dspace2)
  h5close(dset_md_10)

  testmat <- matrix(rep(1:10, 10), nrow = 10)

  f <- function() dspace2 <- H5S$new(dims = c(10, 10), maxdims = c(9, 10))
  expect_that(f(), throws_error("maxdims is smaller than dims"))

  dspace2 <- H5S$new(dims = c(10, 10), maxdims = c(10, 10))
  dset_md_10_10 <- createDataSet(file, "test_md_10_10", testmat, space = dspace2)
  h5close(dset_md_10_10)

  h5close(file)
  expect_true(file.remove(fname))
})

test_that("DataSet-createDataset-compression",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")

  f <- function() dset_cp_type <- createDataSet(file, "cp_type_n", 1:10, gzip = "test")
  expect_that(f(), throws_error("gzip_level has to be between 0 and 9"))

  f <- function() dset_cp_-1 <- createDataSet(file, "cp_-1", 1:10, gzip = -1)
  expect_that(f(), throws_error("gzip_level has to be between 0 and 9"))

  f <- function() dset_cp_10 <- createDataSet(file, "cp_10", 1:10, gzip = 10)
  expect_that(f(), throws_error("gzip_level has to be between 0 and 9"))

  for(i in 0:9) {
    dset <- createDataSet(file, sprintf("cp_%d", i), 1:10, gzip = i)
    h5close(dset)
  }

  h5close(file)
  expect_true(file.remove(fname))
})

test_that("DataSet-list-dataset",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")

  f <- function() list.datasets(file, path = "path doesn't exist")
  expect_that(f(), throws_error("An object with name path doesn't exist does not exist in this group"))

  expect_that(list.datasets(file), is_identical_to(character(0)))

  group <- createGroup(file, "testgroup")
  group[["testset"]] <- 1:3
  expect_that(list.datasets(file), is_identical_to(c("testgroup/testset")))

  # TODO: Fix Bug implicit group extract/create
  #expect_that(list.datasets(file["/testgroup"], recursive = FALSE),
  #    is_identical_to(c("/testgroup/testset")))
  testgroup <- file[["/testgroup"]]
  expect_that(list.datasets(testgroup, recursive = FALSE),
      is_identical_to(c("testset")))
  h5close(testgroup)
  expect_that(list.datasets(file), is_identical_to(c("testgroup/testset")))

  g1 <- createGroup(file, "testgroup/testgroup1")
  file[["testgroup/testgroup1/testset1"]] <- 1:3

  g2 <- createGroup(file, "testgroup/testgroup2")
  file[["testgroup/testgroup2/testset2"]] <- 1:3

  g3 <- createGroup(file, "testgroup3")
  createGroup(file, "testgroup3/testgroup3")
  file[["testgroup3/testgroup3/testset3"]] <- 1:3

  group <- createGroup(file, "testgroupN")
  h5close(group)

  ex <- c("testgroup/testgroup1/testset1", "testgroup/testgroup2/testset2",
          "testgroup/testset", "testgroup3/testgroup3/testset3")
  expect_that(list.datasets(file), is_identical_to(ex))

  #ex <- c("testset1", "testset2", "testset", "testset3")
  #expect_that(list.datasets(file), is_identical_to(ex))

  ex <- c("testgroup1/testset1", "testgroup2/testset2",
          "testset")
  testgroup <- file[["testgroup"]]
  expect_that(list.datasets(testgroup), is_identical_to(ex))
  h5close(testgroup)
  h5close(file)
  expect_true(file.remove(fname))
})

test_that("DataSet-list-dataset",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")
  abc <- createGroup(file, "ABC")

  file[["ABC/1A"]] <- 1:3
  file[["ABC/1B"]] <- 1:3
  file[["ABC/1C"]] <- 1:3
  file[["ABC/1D"]] <- 1:3
  file[["ABC/1E"]] <- 1:3
  file[["ABC/1F"]] <- 1:3

  ex <- c("ABC/1A", "ABC/1B", "ABC/1C", "ABC/1D", "ABC/1E", "ABC/1F")
  expect_that(list.datasets(file), is_identical_to(ex))

  expect_that(list.datasets(file, recursive = FALSE), is_identical_to(character(0)))

  h5close(file)
  expect_true(file.remove(fname))

})

test_that("DataSet-list-dataset-link",{
  fname <- system.file("test-h5link.h5", package = "hdf5r", mustWork = TRUE)
  file <- h5file(fname, "r")

  # TODO(mario): check why H5T_STD_I64LE is not mapped to 64bit integer
  expect_that(file[["hardlink/test2"]][], is_identical_to(1:3))
  expect_that(file[["softlink/test3/test"]][], is_identical_to(1:3))

  expect_that(list.datasets(file[["softlink"]]), is_identical_to(character(0)))

  # TODO(mario): Implement follow.link
  # exp1 <- c("softlink/test3/subgroup/test-sub", "softlink/test3/test")
  # expect_that(list.datasets(file[["softlink"]], follow.link = TRUE), is_identical_to(exp1))

  exp2 <- c("hardlink/test2", "testgroup/subgroup/test-sub", "testgroup/test")
  expect_that(list.datasets(file), is_identical_to(exp2))

  #exp3 <- "softlink/test3/test"
  expect_that(list.datasets(file[["softlink/test3"]], recursive = FALSE), is_identical_to("test"))

  h5close(file)
})

test_that("DataSet-Bug-F32-Issue10",{
  fname <- system.file("test-f32.h5", package = "hdf5r", mustWork = TRUE)
  file <- h5file(fname, "r")
  expect_that(file[["floats"]][], is_identical_to(c(1, 2, 3)))
  h5close(file)
})


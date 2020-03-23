context("h5-DataSet-extend")

fname <- tempfile(fileext=".h5")

test_that("DataSet-extend",{  
  testmat_n <- matrix(as.integer(1:90), ncol = 9)
  
  # Test normal usecase with unlimited dset
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")
  dspace <- H5S$new(maxdims = dim(testmat_n)) 
  # TODO(mario): this should work without setting chunk size:
  #dset1 <- createDataSet(file, "testmat_1", testmat_n, space = dspace)
  dset1 <- createDataSet(file, "testmat_1", robj = testmat_n)
  
  dimtestmat_n <- dim(testmat_n)
  dimtestmat_n_x1 <- dimtestmat_n_y1 <- dimtestmat_n
  dimtestmat_n_x1[1] <- dimtestmat_n_x1[1] - 1
  dimtestmat_n_y1[2] <- dimtestmat_n_y1[2] - 1
  
  f <- function() extendDataSet(dset1, dimtestmat_n_x1)
  expect_that(f(), throws_error("Number of extendible dimensions must be greater or equal than DataSet dimensions"))
  
  f <- function() extendDataSet(dset1, dimtestmat_n_y1)
  expect_that(f(), throws_error("Number of extendible dimensions must be greater or equal than DataSet dimensions"))
  
  
  dimtestmat_n_x1[1] <- dimtestmat_n[1] + 1
  f <- function() extendDataSet(dset1, dimtestmat_n_x1)
  # TODO(mario): How to set up dataset with specified maximum dimensions, only using set_extend?
  # expect_that(f(), throws_error("Number of extendible dimensions exceeds maximum dimensions of DataSet"))
  h5close(dset1)
  
  testmat_n_2 <- dim(testmat_n) * 2
  dset2 <- createDataSet(file, "testmat_2", robj = testmat_n)
  dset2 <- extendDataSet(dset2, testmat_n_2)
  expect_equal(dset2$dims, testmat_n_2)
  
  testmat <- rbind(cbind(testmat_n, 
      matrix(rep(0, length(testmat_n)), nrow = nrow(testmat_n))), 
      matrix(rep(0, dim(testmat_n)[1] * dim(testmat_n)[2] * 2), nrow = nrow(testmat_n)))
  
  expect_equal(readDataSet(dset2), testmat)

  h5close(dset2)
  h5close(file)
  expect_true(file.remove(fname))
})

test_that("DataSet-extend-matrix-rbind",{  
  testmat_n <- matrix(as.integer(1:90), ncol = 9)
  
  # Test normal usecase with unlimited dset
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")
  dset1 <- createDataSet(file, "testmat_1", testmat_n)
  
  f <- function() rbind(dset1, matrix(1:8, ncol = 8))
  expect_that(f(), throws_error("Data to append does not match dataset dimensions"))
  
  # TODO(mario): Check datatype before dataset is extended
  #f <- function() rbind(dset1, matrix(LETTERS[1:9], ncol = 9))
  #expect_that(f(), throws_error("In RToH5_INTEGER can't convert type of object passed"))
  #  f <- function() rbind(dset1, matrix(integer(0), ncol = dset1@dim[2L]))
  #  expect_that(f(), throws_error("H5Sget_select_bounds failed in DataSpace::getSelectBounds"))
  dset1 <- rbind(dset1, matrix(rep(1L, dset1$dims[2]), ncol = dset1$dims[2]))
  h5close(dset1)
  dset2 <- createDataSet(file, "testmat_2", testmat_n)
  dset2 <- rbind(dset2, testmat_n)
  h5close(dset2)
  h5close(file)

  file <- h5file(fname, "r")
  dset1 <- openLocation(file, "testmat_1")
  expect_that(readDataSet(dset1), is_identical_to(rbind(testmat_n, 1L)))
  h5close(dset1)
  dset2 <- openLocation(file, "testmat_2")
  expect_that(readDataSet(dset2), is_identical_to(rbind(testmat_n, testmat_n)))
  h5close(dset2)
  h5close(file)
  expect_true(file.remove(fname))
})

test_that("DataSet-extend-matrix-cbind",{  
  testmat_n <- matrix(as.integer(1:90), nrow = 10)
  
  # Test normal usecase with unlimited dset
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")
  dset1 <- createDataSet(file, "testmat_1", testmat_n)
  
  f <- function() cbind(dset1, matrix(1:9, nrow = 9))
  expect_that(f(), throws_error("Data to append does not match dataset dimensions"))
  
  # TODO(mario): Check datatype before dataset is extended
  # f <- function() cbind(dset1, matrix(LETTERS[1:10], nrow = 10))
  # expect_that(f(), throws_error("In RToH5_INTEGER can't convert type of object passed"))
  # f <- function() cbind(dset1, matrix(integer(0), nrow = dset1@dim[1L]))
  # expect_that(f(), throws_error("Elements of parameter count must be greater than zero"))
  
  dset1 <- cbind(dset1, matrix(as.integer(rep(1, nrow(testmat_n))), ncol = 1))
  h5close(dset1)
  dset2 <- createDataSet(file, "testmat_2", testmat_n)
  dset2 <- cbind(dset2, testmat_n)
  h5close(dset2)
  h5close(file)
  
  file <- h5file(fname, "r")
  dset1 <- openLocation(file, "testmat_1")
  expect_that(readDataSet(dset1), is_identical_to(cbind(testmat_n, 1L)))
  h5close(dset1)
  dset2 <- openLocation(file, "testmat_2")
  expect_that(readDataSet(dset2), is_identical_to(cbind(testmat_n, testmat_n)))
  h5close(dset2)
  h5close(file)
  expect_true(file.remove(fname))
})

test_that("DataSet-extend-vector-c",{  
  testmat_n <- as.integer(1:90)
  
  # Test normal usecase with unlimited dset
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")
  dset1 <- createDataSet(file, "testmat_1", testmat_n)
  
  f <- function() c(dset1, integer(0))
  expect_that(f(), throws_error("Retrieving hyperslabs in reverse order not supported"))
  
  dset1 <- c(dset1, rep(1L, length(testmat_n)), rep(2L, length(testmat_n)))
  h5close(dset1)
  h5close(file)
  
  file <- h5file(fname, "r")
  dset1 <- openLocation(file, "testmat_1")
  testmat_n_extend <- c(testmat_n, rep(1L, length(testmat_n)), rep(2L, length(testmat_n)))
  expect_that(readDataSet(dset1), is_identical_to(testmat_n_extend))
  h5close(dset1)
  h5close(file)
  expect_true(file.remove(fname))
})



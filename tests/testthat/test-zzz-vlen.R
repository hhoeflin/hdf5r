context("h5-DataSet-VLEN-Vector")

fname <- tempfile(fileext=".h5")

# test_that("DataSet-VLEN-Vector-create",{
#   if(file.exists(fname)) file.remove(fname)
#   file <- h5file(fname, "a")
#   group <- createGroup(file, "/testgroup")
#   
#   dset1 <- createDataSet(group, "testvec_n", type = "vlen-double", dimensions = 30L)
#   expect_that(dset1@datatype, is_identical_to("x"))
#   h5close(dset1)
#   
#   f <- function() createDataSet(group, "testvec_l", type = "vlen-logical", dimensions = 30L)
#   expect_that(f(), throws_error("Type 'vlen-logical' not supported yet"))
#   
#   dset3 <- createDataSet(group, "testvec_i", type = "vlen-integer", dimensions = 30L)
#   expect_that(dset3@datatype, is_identical_to("y"))
#   h5close(dset3)
#   
#   f <- function() createDataSet(group, "testvec_c", type = "vlen-character", dimensions = 30L)
#   expect_that(f(), throws_error("Type 'vlen-character' not supported yet"))
#   
#   f <- function() createDataSet(group, "testvec_c4", type = "vlen-character", dimensions = 30L, size = 9)
#   expect_that(f(), throws_error("Type 'vlen-character' not supported yet"))
# 
#   h5close(group)
#   h5close(file)
#  
#   expect_that(file.remove(fname), is_true())
# })

test_that("DataSet-VLEN-Vector",{
  if(file.exists(fname)) file.remove(fname)
  
  testvec_n <- rnorm(120)
  testvec_i <- as.integer(runif(120)*10000)
  testvec_l <- as.logical(round(runif(120)))
  testvec_c <-rep(paste0(LETTERS[1:3], rev(LETTERS)[1:3]), 120/3)
  testvec_c[1] <- paste0(testvec_c[1], testvec_c[1])
  testvec_c[40] <- paste0(testvec_c[1], testvec_c[1])
  
  testlist_n <- list(testvec_n[1:10], testvec_n[11:30], testvec_n[31:120])
  testlist_i <- list(testvec_i[1:10], testvec_i[11:30], testvec_i[31:120])
  testlist_l <- list(testvec_l[1:10], testvec_l[11:30], testvec_l[31:120])
  testlist_c <- list(testvec_c[1:10], testvec_c[11:30], testvec_c[31:120])
  
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")
  group <- createGroup(file, "/testgroup")
  
  dset1 <- createDataSet(group, "testlist_n", testlist_n)
  h5close(dset1)
  
  dset2 <- createDataSet(group, "testlist_i", testlist_i)
  h5close(dset2)
  
  dset3 <- createDataSet(group, "testlist_l", testlist_l)
  h5close(dset3)
  
  dset4 <- createDataSet(group, "testlist_c", testlist_c)
  h5close(dset4)

  h5close(group)
  h5close(file)
  
  file <- h5file(fname, "a")
  testlist_n_in <- file[["/testgroup/testlist_n"]]
  expect_that(testlist_n_in[], is_identical_to(testlist_n))
  h5close(testlist_n_in)
  testlist_i_in <- file[["/testgroup/testlist_i"]] 
  expect_that(testlist_i_in[], is_identical_to(testlist_i))
  h5close(testlist_i_in)
  testlist_l_in <- file[["/testgroup/testlist_l"]] 
  expect_that(testlist_l_in[], is_identical_to(testlist_l))
  h5close(testlist_l_in)
  testlist_c_in <- file[["/testgroup/testlist_c"]] 
  expect_that(testlist_c_in[], is_identical_to(testlist_c))
  h5close(testlist_c_in)
  h5close(file)
  expect_true(file.remove(fname))
})

test_that("DataSet-VLEN-Vector-Attribute",{
  testvec_n <- rnorm(120)
  testvec_i <- as.integer(runif(120)*10000)
  testvec_l <- as.logical(round(runif(120)))
  testvec_c <-rep(paste0(LETTERS[1:3], rev(LETTERS)[1:3]), 120/3)
  testvec_c[1] <- paste0(testvec_c[1], testvec_c[1])
  testvec_c[40] <- paste0(testvec_c[1], testvec_c[1])
  
  testlist_n <- list(testvec_n[1:10], testvec_n[11:30], testvec_n[31:120])
  testlist_i <- list(testvec_i[1:10], testvec_i[11:30], testvec_i[31:120])
  testlist_l <- list(testvec_l[1:10], testvec_l[11:30], testvec_l[31:120])
  testlist_c <- list(testvec_c[1:10], testvec_c[11:30], testvec_c[31:120])
  
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")
  group <- createGroup(file, "/testgroup")
  
  h5attr(group, "testlist_n") <- testlist_n
  h5attr(group, "testlist_i") <- testlist_i
  h5attr(group, "testlist_l") <- testlist_l
  h5attr(group, "testlist_c") <- testlist_c
 
  h5close(group)
  h5close(file)
  
  file <- h5file(fname, "a")
# TODO: check why this leaves open file handle
#  testlist_n_in <- h5attr(file["/testgroup"], "testlist_n") 
#  expect_that(testlist_n_in, is_identical_to(testlist_n))
#  testlist_i_in <- h5attr(file["/testgroup"], "testlist_i") 
#  expect_that(testlist_i_in[], is_identical_to(testlist_i))
  
  testgroup <- file[["/testgroup"]]
  testlist_n_in <- h5attr(testgroup, "testlist_n") 
  expect_that(testlist_n_in, is_identical_to(testlist_n))
  testlist_i_in <- h5attr(testgroup, "testlist_i") 
  expect_that(testlist_i_in[], is_identical_to(testlist_i))
  testlist_l_in <- h5attr(testgroup, "testlist_l") 
  expect_that(testlist_l_in[], is_identical_to(testlist_l))
  testlist_c_in <- h5attr(testgroup, "testlist_c") 
  expect_that(testlist_c_in[], is_identical_to(testlist_c))
  
  h5close(testgroup)
  h5close(file)
  expect_true(file.remove(fname))
})

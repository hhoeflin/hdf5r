context("h5-Attribute")

fname <- tempfile(fileext=".h5")

testvec_i <- as.integer(1:90)
testmat_i <- matrix(testvec_i, ncol = 9)
testarray_i <- array(testvec_i, dim = c(3, 3, 10))

testvec_n <- as.numeric(1:90)
testmat_n <- matrix(testvec_n, ncol = 9)
testarray_n <- array(testvec_n, dim = c(3, 3, 10))

testvec_s <- paste0(LETTERS[1:90], LETTERS[seq(90, 1)])
testmat_s <- matrix(testvec_s, ncol = 9)
testarray_s <- array(testvec_s, dim = c(3, 3, 10))
maxchar <- max(nchar(testvec_s))


testvec_l <- rep(c(TRUE, FALSE), 45)
testmat_l <- matrix(testvec_l, ncol = 9)
testarray_l <- array(testvec_l, dim = c(3, 3, 10))

testall <- list(
    testvec_i, testmat_i, testarray_i,
    testvec_n, testmat_n, testarray_n, 
    testvec_l, testmat_l, testarray_l,
    testvec_s, testmat_s, testarray_s,
    testvec_s, testmat_s, testarray_s
    )

    
test_that("Attribute-Errors", {   
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")

  f <- function() h5attr(file, "test")
  expect_that(f(), throws_error("Attribute does not exist"))    
  h5attr(file, "test") <- c("A", "BE", "BU")
  
  f <- function() h5attr(file, "test") <- c("a", "be", "bu")
  
  group <- createGroup(file, "testgroup")
  f <- function() h5attr(group, "test")
  expect_that(f(), throws_error("Attribute does not exist"))    
  h5attr(group, "test") <- c("A", "BE", "BU")
  
  group[["testset"]] <- 1:10
  dset <- group[["testset"]] 
  f <- function() h5attr(dset, "test")
  expect_that(f(), throws_error("Attribute does not exist"))    
  h5attr(dset, "test") <- c("A", "BE", "BU")
  h5close(dset)
  h5close(group)
  h5close(file)
  
  file <- h5file(fname, "r")
  expect_that(h5attr(file, "test"), is_identical_to(c("A", "BE", "BU")))
  group <- file[["testgroup"]]
  expect_that(h5attr(group, "test"), is_identical_to(c("A", "BE", "BU")))
  dset <- group[["testset"]]
  expect_that(h5attr(dset, "test"), is_identical_to(c("A", "BE", "BU")))
  h5close(dset)
  h5close(group)
  h5close(file)
  expect_true(file.remove(fname))
})      
      
test_that("Attribute-H5Type-File", {      
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")
  
  for(i in 1:length(testall)) {
    aname <- sprintf("attribute_%02d", i)
    #if(i < length(testall))
    h5attr(file, aname) <- testall[[i]]
    #else
    #  h5attr(file, aname, size = maxchar) <- testall[[i]]
  }
  
  group <- createGroup(file, "testgroup")
  
  for(i in 1:length(testall)) {
    aname <- sprintf("attribute_%02d", i)
    #if(i < length(testall))
    h5attr(group, aname) <- testall[[i]]
    #else
    #  h5attr(group, aname, size = maxchar) <- testall[[i]]
  }
 
  file[["testgroup/dset"]] <- 1:10
  dset <- file[["testgroup/dset"]]
  for(i in 1:length(testall)) {
    aname <- sprintf("attribute_%02d", i)
    #if(i < length(testall))
    h5attr(dset, aname) <- testall[[i]]
    #else
    #  h5attr(dset, aname, size = maxchar) <- testall[[i]]
  }
  h5close(group)
  h5close(dset)
  h5close(file) 
  
  file <- h5file(fname, "r")
  for(i in 1:length(testall)) {
    aname <- sprintf("attribute_%02d", i)
    expect_that(h5attr(file, aname), is_identical_to(testall[[i]]))
  }
  
  group <- file[["testgroup"]]
  for(i in 1:length(testall)) {
    aname <- sprintf("attribute_%02d", i)
    expect_that(h5attr(group, aname), is_identical_to(testall[[i]]))
  }
  
  dset <- group[["dset"]]
  for(i in 1:length(testall)) {
    aname <- sprintf("attribute_%02d", i)
    expect_that(h5attr(dset, aname), is_identical_to(testall[[i]]))
  }
  h5close(group)
  h5close(dset)
  h5close(file) 
  expect_true(file.remove(fname))
})    

test_that("Attribute-list-attributes", {      
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname)
  
  # TODO(mario): Support on-the-fly group creation?
  #file[["testgroup/testset"]] <- 1:10
  g1 <- createGroup(file, "testgroup")
  g1[["testset"]] <- 1:10
  
  h5attr(file, "fileattr1") <- 1:10
  h5attr(file, "fileattr2") <- 1:10
  h5attr(file, "fileattr3") <- 1:10
  
  testset <- file[["testgroup/testset"]]
  h5attr(testset, "dsetattr1") <- 1:10
  h5attr(testset, "dsetattr2") <- 1:10
  h5attr(testset, "dsetattr3") <- 1:10
  
  # TODO(mario): check why  Attribute-list-attributes not working for file subset
  #  h5attr(file["testgroup/testset"], "dsteattr1") <- 1:10
  #  h5attr(file["testgroup/testset"], "dsteattr2") <- 1:10
  #  h5attr(file["testgroup/testset"], "dsteattr3") <- 1:10
  
  # TODO(mario): Implement list.attributes
  expect_that(list.attributes(file),
      is_identical_to(c("fileattr1", "fileattr2", "fileattr3")))
  expect_that(list.attributes(testset),
      is_identical_to(c("dsetattr1", "dsetattr2", "dsetattr3")))
  
  h5close(testset)
  # TODO(mario): check why  Attribute-list-attributes not working for file subset
  # h5attr(file[["testgroup"]], "groupattr1") <- 1:10
  # h5attr(file[["testgroup"]], "groupattr2") <- 1:10
  # h5attr(file[["testgroup"]], "groupattr3") <- 1:10
  # expect_that(list.attributes(file["testgroup"]),
  #     is_identical_to(c("groupattr1", "groupattr2", "groupattr3")))

  h5close(file) 
  expect_true(file.remove(fname))
})

test_that("Bug_AttributeGroupSubset", {        
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname)
  file[["testdataset"]] <- 1:10
  h5attr(file, "testattrib") <- LETTERS[1:10]
  createGroup(file, "testgroup")
  file[["testgroup/testdataset2"]] <- 1:10

  h5attr(file[["testdataset"]], "test") <- 1:10
  h5close(file) 
  expect_true(file.remove(fname))
})

test_that("Attribute-Bug-Scalar-Issue09",{	
  fname <- system.file("test-f32.h5", package = "hdf5r", mustWork = TRUE)
  file <- h5file(fname, "r")
  expect_that(substr(h5attr(file[["floats"]], "scalar"), 1, 5), is_identical_to("Hello"))
  h5close(file)
})

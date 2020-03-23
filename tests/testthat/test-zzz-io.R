context("h5-datatypes-IO")

test_that("datatypes-IO",{
	
	testmat <- matrix(rnorm(120), ncol = 3)
	fname <- tempfile(fileext=".h5")
	if(file.exists(fname)) file.remove(fname)
	dsetname <- c("testmat1", "testmat2")
	
	file <- h5file(fname, "a")
	group <- createGroup(file, "/testgroup")
	dset <- createDataSet(group, dsetname[1], testmat)
	h5close(dset)
	h5close(group)
	h5close(file)
	
	file <- h5file(fname, "r")
	group <- openLocation(file, "/testgroup")
	dset <- openLocation(group, dsetname[1])
	outmat <- readDataSet(dset)
	expect_that(testmat, is_identical_to(outmat))
	h5close(dset)
	h5close(group)
	h5close(file)
	
	file <- h5file(fname, "a")
	group2 <- createGroup(file, "/testgroup/testgroup2")
	dset2 <- createDataSet(group2, dsetname[2], testmat)
	outmat2 <- readDataSet(dset2)
	expect_that(testmat, is_identical_to(outmat2))
	h5close(dset2)
	h5close(group2)
	h5close(file)
	
	file2 <- h5file(fname, "r")
	group3 <- openLocation(file2, "/testgroup/testgroup2")
	dset3 <- openLocation(group3, dsetname[2]) 
	outmat3 <- readDataSet(dset3)
	expect_that(testmat, is_identical_to(outmat3))
	h5close(dset3)
	h5close(group3)
	h5close(file2)
	
  expect_true(file.remove(fname))
})


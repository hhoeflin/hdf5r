context("h5-H5File")
fname <- tempfile(fileext=".h5")

test_that("H5File-param",{
	f <- function() file <- h5file(1, "a")
	expect_that(f(), throws_error("is.character\\(name\\) is not TRUE"))

	f <- function() file <- h5file(c("a", "a"), "a")
	expect_that(f(), throws_error("length\\(name\\) == 1 is not TRUE"))

	f <- function() file <- h5file("a", 1)
  expect_that(f(), throws_error("'arg' must be NULL or a character vector"))

	f <- function() file <- h5file("a", c("a", "a"))
	expect_that(f(), throws_error("'arg' must be of length 1"))

	f <- function() file <- h5file("a", c("a", "a"))
  expect_that(f(), throws_error("'arg' must be of length 1"))

	f <- function() file <- h5file("path", "w--")
	expect_that(f(), throws_error("'arg' should be one of.*"))
})

test_that("H5File-FileMode-param-a",{
	if(file.exists(fname)) file.remove(fname)
	file <- h5file(fname)
	expect_that(file, is_a("H5File"))
	# TODO: add mode to file
	#expect_that(file$mode, is_identical_to("a"))
	expect_that(normalizePath(file$get_filename(), mustWork=FALSE), is_identical_to(normalizePath(fname, mustWork=FALSE)))
	group1 <- createGroup(file, "testgroup")
	expect_that(group1, is_a("H5Group"))
	h5close(group1)
	h5close(file)

	# Open existing file for append
	expect_true(file.exists(fname))
	file <- h5file(fname, "a")
	expect_that(file, is_a("H5File"))
	expect_true(existsGroup(file, "testgroup"))
	group2 <- createGroup(file, "testgroup2")
	h5close(group2)
	h5close(file)
})

test_that("H5File-FileMode-param-w-",{
	expect_true(file.exists(fname))
	f <- function() file <- h5file(fname, "w-")
	expect_that(f(), throws_error("Unable to open file"))
	expect_true(file.remove(fname))

	file <- h5file(fname, "w-")
	expect_that(file$mode, is_identical_to("w-"))
	expect_that(normalizePath(file$filename, mustWork=FALSE), is_identical_to(normalizePath(fname, mustWork=FALSE)))
	group1 <- createGroup(file, "testgroup1")
	expect_true(existsGroup(file, "testgroup1"))
	h5close(group1)
	h5close(file)
})

test_that("H5File-FileMode-param-w",{
  expect_true(file.exists(fname))
  # Seems HDF5 since 1.8.15 does not detect that file does exist but is already
  # closed, see also https://www.hdfgroup.org/HDF5/doc/RM/RM_H5F.html
  # We therefore need to delete file
  expect_true(file.remove(fname))

  file <- h5file(fname, "w")
  expect_that(file$mode, is_identical_to("w"))
  expect_that(normalizePath(file$filename, mustWork=FALSE), is_identical_to(normalizePath(fname, mustWork=FALSE)))
  expect_false(existsGroup(file, "testgroup1"))
  group2 <- createGroup(file, "testgroup1")
  h5close(group2)
  h5close(file)

  expect_true(file.exists(fname))
  # See above
  expect_true(file.remove(fname))

  file <- h5file(fname, "w")
  expect_that(file$mode, is_identical_to("w"))
  expect_that(normalizePath(file$filename, mustWork=FALSE), is_identical_to(normalizePath(fname, mustWork=FALSE)))
  expect_false(existsGroup(file, "testgroup1"))
  h5close(file)

})

test_that("H5File-FileMode-param-r",{
	expect_true(file.exists(fname))
  file <- h5file(fname, "r")
  expect_that(file$mode, is_identical_to("r"))

  # TODO(mario): Check why for osx we have
  # > file$filename
  # [1] "/private/var/folders/q3/0dypvmy96jv26m3qk49pp85r0000gn/T/Rtmpl0x2xf/fileb2287a7a7b98.h5"
  # > fname
  # [1] "/var/folders/q3/0dypvmy96jv26m3qk49pp85r0000gn/T//Rtmpl0x2xf/fileb2287a7a7b98.h5"

  expect_that(normalizePath(file$filename, mustWork=FALSE), is_identical_to(normalizePath(fname, mustWork=FALSE)))
  h5close(file)

  expect_true(file.remove(fname))
  f <- function() file <- h5file(fname, "r")
  expect_that(f(), throws_error("Unable to open file"))
})

test_that("H5File-FileMode-param-r+",{
  if(file.exists(fname)) file.remove(fname)
  f <- function() file <- h5file(fname, "r+")
  expect_that(f(), throws_error("Unable to open file"))

  file <- h5file(fname, "a")
  group1 <- createGroup(file, "testgroup")
  expect_that(group1, is_a("H5Group"))
  h5close(group1)
  h5close(file)

  file <- h5file(fname, "r+")
  expect_true(existsGroup(file, "testgroup"))
  expect_that(group1, is_a("H5Group"))
  h5close(group1)
  h5close(file)
  expect_true(file.remove(fname))
})


test_that("H5File-show",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname)
  group1 <- createGroup(file, "testgroup")
  group2 <- createGroup(file, "testgroup2")
  group3 <- createGroup(group2, "testgroup3")
  h5close(group1)
  h5close(group2)
  h5close(group3)
  h5close(file)
  expect_true(file.remove(fname))
})

test_that("H5File-is-h5file",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname)
  group1 <- createGroup(file, "testgroup")
  h5close(group1)
  h5close(file)

  expect_true(is.h5file(fname))
  expect_warning(expect_false(is.h5file("abc")))
  fnametxt <- "test.txt"
  writeLines("abc", fnametxt)
  expect_false(is.h5file(fnametxt))
  expect_true(file.remove(fname))
  expect_true(file.remove(fnametxt))
})

test_that("H5File-flush",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname)
  group1 <- createGroup(file, "testgroup")
  ds <- createDataSet(group1, "testset", 1:100)
  h5flush(file)
  h5close(file)
})


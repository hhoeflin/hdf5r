context("h5-H5Group")
fname <- tempfile(fileext=".h5")

test_that("H5Group-param",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname)

  group1 <- createGroup(file, "//testgroup")
  expect_that(group1, is_a("H5Group"))
  h5close(group1)

  group2 <- createGroup(file, "testgroup2//")
  expect_that(group2, is_a("H5Group"))
  h5close(group2)

  # Does not need to throw an error
  # f <- function() grouproot <- createGroup(file, "/")
  # expect_that(f(), throws_error("H5Gcreate failed"))

  # Test very long groupname
  gname <- paste(rep(LETTERS, 1000), collapse = "")
  groupn <- createGroup(file, gname)
  expect_that(group1, is_a("H5Group"))
  h5close(groupn)
  h5close(file)
  expect_true(file.remove(fname))
})

test_that("H5Group-createGroup",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname)

  # Not Fail for nested (non-existent) group name
  # f <- function() group1 <- createGroup(file, "/testgroup/test")
  # expect_that(f(), throws_error("H5Gcreate failed"))

  group3 <- createGroup(file, "/testgroup3")
  expect_that(group3, is_a("H5Group"))
  expect_that(group3$get_obj_name(), is_identical_to("/testgroup3"))

  groupnested <- createGroup(group3, "/test")
  expect_that(groupnested, is_a("H5Group"))
  expect_that(groupnested$get_obj_name(), is_identical_to("/testgroup3/test"))
  h5close(groupnested)
  h5close(group3)
  h5close(file)
})

test_that("H5Group-openLocation",{
  expect_true(file.exists(fname))
  file <- h5file(fname, "r")
  # Fail for nested (non-existent) group name
  f <- function() group1 <- openLocation(file, "/testgroup/test")
  expect_that(f(), throws_error()) # error message varies between versions

  group3 <- openLocation(file, "/testgroup3")
  expect_that(group3, is_a("H5Group"))
  expect_that(group3$get_obj_name(), is_identical_to("/testgroup3"))

  groupnested <- openLocation(group3, "test")
  expect_that(groupnested, is_a("H5Group"))
  expect_that(groupnested$get_obj_name(), is_identical_to("/testgroup3/test"))
  h5close(groupnested)
  h5close(group3)

  group3 <- openLocation(file, "/testgroup3")
  grouprelative <- openLocation(group3, "test")
  expect_that(grouprelative, is_a("H5Group"))
  expect_that(grouprelative$get_obj_name(), is_identical_to("/testgroup3/test"))
  # TODO: should absolute path be displayed?
  # eg. expect_that(grouprelative@name, is_identical_to("/testgroup3/test"))

  h5close(grouprelative)
  h5close(group3)
  h5close(file)
})

test_that("H5Group-openGroup",{
  expect_true(file.exists(fname))
  file <- h5file(fname, "r")
  # Fail for nested (non-existent) group name
  f <- function() group1 <- openGroup(file, "/testgroup/test")
  expect_that(f(), throws_error()) # specific message check removed as message varies
  
  group3 <- openGroup(file, "/testgroup3")
  expect_that(group3, is_a("H5Group"))
  expect_that(group3$get_obj_name(), is_identical_to("/testgroup3"))
  
  groupnested <- openGroup(group3, "test")
  expect_that(groupnested, is_a("H5Group"))
  expect_that(groupnested$get_obj_name(), is_identical_to("/testgroup3/test"))
  h5close(groupnested)
  h5close(group3)
  
  group3 <- openGroup(file, "/testgroup3")
  grouprelative <- openGroup(group3, "test")
  expect_that(grouprelative, is_a("H5Group"))
  expect_that(grouprelative$get_obj_name(), is_identical_to("/testgroup3/test"))
  # TODO: should absolute path be displayed?
  # eg. expect_that(grouprelative@name, is_identical_to("/testgroup3/test"))
  
  h5close(grouprelative)
  h5close(group3)
  h5close(file)
})

test_that("H5Group-existsGroup",{
  expect_true(file.exists(fname))
  file <- h5file(fname, "r")
  # Fail for nested (non-existent) group name
  expect_false(existsGroup(file, "/testgroup/test"))
  expect_true(existsGroup(file, "/testgroup3"))
  expect_true(existsGroup(file, "/testgroup3/test"))

  group3 <- openLocation(file, "/testgroup3")
  expect_true(existsGroup(group3, "test"))
  h5close(group3)
  h5close(file)
  expect_true(file.remove(fname))
})

test_that("CommonFG-list-groups",{
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")

  # TODO(mario): Adjust error message if object[[path]] is nonexistent
  f <- function() list.groups(file, path = "a/be/bu")
  expect_that(f(), throws_error()) # specific error message removed as message varies
  expect_that(list.groups(file), is_identical_to(character(0)))

  g1 <- createGroup(file, "testgroup")
  g1[["testset"]] <- 1:3
  expect_that(list.groups(file), is_identical_to(c("testgroup")))
  expect_that(list.groups(file, recursive = FALSE), is_identical_to(c("testgroup")))
  expect_that(list.groups(file), is_identical_to(c("testgroup")))

  g11 <- createGroup(g1, "testgroup1")
  g12 <- createGroup(g1, "testgroup2")
  g13 <- createGroup(g1, "testgroup3")

  g11[["testset1"]] <- 1:3
  g12[["testset2"]] <- 1:3
  g13[["testset3"]] <- 1:3
  h5close(g1)

  group <- createGroup(file, "testgroupN")
  h5close(group)

  ex <- c("testgroup", "testgroup/testgroup1", "testgroup/testgroup2",
 	"testgroup/testgroup3", "testgroupN")
  expect_that(list.groups(file), is_identical_to(ex))

  ex <- c("testgroup", "testgroup1", "testgroup2", "testgroup3", "testgroupN")
  expect_that(basename(list.groups(file)), is_identical_to(ex))

  ex <- c("testgroup", "testgroupN")
  expect_that(list.groups(file, recursive = FALSE), is_identical_to(ex))

  ex <- c("testgroup1", "testgroup2", "testgroup3")
  testgroup <- file[["testgroup"]]
  expect_that(list.groups(file[["testgroup"]], full.names = TRUE), is_identical_to(paste0("/testgroup/", ex)))
  expect_that(list.groups(testgroup), is_identical_to(ex))
  h5close(testgroup)

  h5close(file)
  expect_true(file.remove(fname))
})

test_that("CommonFG-unlink",{
  if(file.exists(fname)) file.remove(fname)

  file <- h5file(fname)
  g1 <- createGroup(file, "testgroup")
  g2 <- createGroup(file, "testgroup2")
  g1[["testset"]] <- 1:3
  g1[["testset2"]] <- 1:3
  g2[["testset"]] <- 1:3

  h5close(file)

  file <- h5file(fname, "r+")

  # unlink group
  ex <- c("testgroup/testset",  "testgroup/testset2", "testgroup2/testset")
  expect_that(list.datasets(file, recursive = TRUE),
      is_identical_to(ex))

  # unlink dataset
  expect_true(h5unlink(file, "testgroup"))
  expect_true(h5unlink(file, "testgroup2/testset"))
  expect_that(list.datasets(file, recursive = TRUE),
      is_identical_to(character(0)))
  expect_that(list.groups(file, recursive = TRUE),
      is_identical_to("testgroup2"))

  # remove last group
  expect_true(h5unlink(file, "testgroup2"))
  expect_that(list.groups(file, recursive = TRUE),
      is_identical_to(character(0)))

  # remove non-existing
  # expect_that(h5unlink(file, "testgroup2"), is_false())
  # expect_that(h5unlink(file, "testgroup2/testset"), is_false())

  # add data sets again
  g1 <- createGroup(file, "testgroup")
  g2 <- createGroup(file, "testgroup2")
  g1[["testset"]] <- 5:6
  g1[["testset2"]] <- 5:6
  g2[["testset"]] <- 5:6
  h5close(file)

  file <- h5file(fname, "a")

  # TODO(mario): check why this still leaves an open file handle
  expect_that(file[["testgroup/testset"]][], is_identical_to(5:6))
  expect_that(file[["testgroup/testset2"]][], is_identical_to(5:6))
  expect_that(file[["testgroup2/testset"]][], is_identical_to(5:6))

  testset <- file[["testgroup/testset"]]
  expect_that(testset[], is_identical_to(5:6))
  h5close(testset)
  testset2 <- file[["testgroup/testset2"]]
  expect_that(testset2[], is_identical_to(5:6))
  h5close(testset2)
  testset3 <- file[["testgroup2/testset"]]
  expect_that(testset3[], is_identical_to(5:6))
  h5close(testset3)

  # remove multiple datasets, 1 missing
  # TODO: check if file is read-only mode
  res <- h5unlink(file, c("testgroup/testset", "testgroup/testset2",
          "testgroup2/testset", "testgroup2/missing"))
  names(res) <- NULL
  expect_that(res, is_identical_to(c(TRUE, TRUE, TRUE, FALSE)))
  h5close(file)

  expect_true(file.remove(fname))
})

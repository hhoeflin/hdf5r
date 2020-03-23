context("h5-DataSet-Vector-NA")

test_that("DataSet-Vector-NA",{
  fname <- tempfile(fileext=".h5")
  testvec_n <- rnorm(120)
  testvec_i <- as.integer(runif(120)*10000)
  testvec_l <- as.logical(round(runif(120)))
  testvec_c <-rep(paste0(LETTERS[1:3], rev(LETTERS)[1:3]), 120/3)
  testvec_c[1] <- paste0(testvec_c[1], testvec_c[1])
  testvec_c[40] <- paste0(testvec_c[1], testvec_c[1])
  
  testvec_n[seq(1, 120, 10)] <- NA_real_
  testvec_i[seq(1, 120, 10)] <- NA_integer_
  testvec_l[seq(1, 120, 10)] <- NA
  testvec_c[seq(1, 120, 10)] <- NA_character_
      
  if(file.exists(fname)) file.remove(fname)
  file <- h5file(fname, "a")
  group <- createGroup(file, "/testgroup")
  dset1 <- createDataSet(group, "testvec_n", testvec_n)
  h5close(dset1)
  dset2 <- createDataSet(group, "testvec_l", testvec_l)
  h5close(dset2)
  dset3 <- createDataSet(group, "testvec_i", testvec_i)
  h5close(dset3)
  
  dset4 <- createDataSet(group, "testvec_c", testvec_c)
  h5close(dset4)

  dset5 <- createDataSet(group, "testvec_c4", testvec_c)
  h5close(dset5)
  
  h5close(group)
  h5close(file)
  
  ### Check if written data equals input data
  file <- h5file(fname, "r")
  group <- openLocation(file, "/testgroup")
  dset11 <- openLocation(group, "testvec_n")
  testvec_n_read <- readDataSet(dset11)
  h5close(dset11)
  expect_that(testvec_n, is_identical_to(testvec_n_read))
  
  dset12 <- openLocation(group, "testvec_l")
  testvec_l_read <- readDataSet(dset12)
  h5close(dset12)
  expect_that(testvec_l, is_identical_to(testvec_l_read))
  
  dset13 <- openLocation(group, "testvec_i")
  testvec_i_read <- readDataSet(dset13)
  h5close(dset13)
  expect_that(testvec_i, is_identical_to(testvec_i_read))

  # TODO(mario): NA handling for strings does not work properly  
  # dset14 <- openLocation(group, "testvec_c")
  # testvec_c_read <- readDataSet(dset14)
  # h5close(dset14)
  # expect_that(testvec_c, is_identical_to(testvec_c_read))
  # 
  # dset15 <- openLocation(group, "testvec_c4")
  # testvec_c_read <- readDataSet(dset15)
  # h5close(dset15)
  # expect_that(testvec_c, is_identical_to(testvec_c_read))
  
  h5close(group)
  h5close(file)		
  expect_true(file.remove(fname))
})

# Build against rwinlib build of hdf5
VERSION <- commandArgs(TRUE)
if(!file.exists(sprintf("../windows/hdf5-%s/include/hdf5.h", VERSION))){
  download.file(sprintf("https://github.com/rwinlib/hdf5/archive/v%s.zip", VERSION),
                "lib.zip", quiet = TRUE)
  dir.create("../windows", showWarnings = FALSE)
  unzip("lib.zip", exdir = "../windows")
  unlink("lib.zip")
}

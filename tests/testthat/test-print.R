context("Print-method")

escape_regexp <- function(string) {
    gsub("([.|()\\^{}+$*?]|\\[|\\])", "\\\\\\1", string)
}

test_that("Print functions work as expected", {
    ## create a file and call print
    test_file <- tempfile(fileext=".h5")

    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")
    h5group <- file.h5$create_group("test")

    ## add some attributes
    h5attr(file.h5, "attr1") <- 1.0
    h5attr(file.h5, "attr2") <- "A"
    h5attr(h5group, "grp_attr") <- "a group"
    
    ## H5File has its location as part of its output
    expect_output(file.h5$print(), regexp=paste0("Class: H5File\nFilename: ",
                                                 escape_regexp(normalizePath(test_file, mustWork=FALSE)),
                                                 "\nAccess type: H5F_ACC_RDWR\n",
                                                 "Attributes: attr1, attr2\n",
                                                 "Listing:\n",
                                                 " name    object.type dataset.dims dataset.type_class\n",
                                                 " test H5O_TYPE_GROUP         <NA>               <NA>"))

    #H5Group also prints the name of the group
    expect_output(h5group$print(), regexp=paste0("Class: H5Group\nID: 0x[0-9A-F]+\nFilename: ",
                                                 escape_regexp(normalizePath(test_file, mustWork=FALSE)),
                                                 "\nGroup: /test"))
    
    ## cleanup
    file.h5$close_all()
    file.remove(test_file)

})

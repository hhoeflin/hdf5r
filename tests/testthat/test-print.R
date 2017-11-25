context("Print-method")

escape_regexp <- function(string) {
    gsub("([.|()\\^{}+$*?]|\\[|\\])", "\\\\\\1", string)
}

test_that("Print functions work as expected", {
    ## create a file and call print
    test_file <- tempfile(fileext=".h5")

    ## H5S default class
    expect_output(h5const$H5S_ALL$print(), "H5S_ALL class")
    expect_output(h5const$H5P_DEFAULT$print(), "H5P_DEFAULT class")
    
    ## open a new one, truncate if it exists
    file.h5 <- H5File$new(test_file, mode="w")
    h5group <- file.h5$create_group("test")

    ## add some attributes
    h5attr(file.h5, "attr1") <- 1.0
    h5attr(file.h5, "attr2") <- "A"
    h5attr(h5group, "grp_attr") <- "a group"

    ## create a space that defines the nsize fo the new dataset
    dset_space <- H5S$new(type="simple", dims=c(5,10,15))
    h5dset <- h5group$create_dataset("test_dset", dtype=h5types$H5T_IEEE_F64LE, space=dset_space)

    ## check that the pring output for spaces is ok
    expect_output(dset_space$print(), regexp="Class: H5S\nType: Simple\nDims: 5 x 10 x 15\nMaxdims: 5 x 10 x 15", fixed=TRUE)

    ## also test output for a scalar and a null space
    expect_output(H5S$new(type="scalar")$print(),
                  regexp="Class: H5S\nType: Scalar", fixed=TRUE)
    expect_output(H5S$new(type="null")$print(),
                  regexp="Class: H5S\nType: NULL", fixed=TRUE)
    
    ## H5File has its location as part of its output
    expect_output(file.h5$print(), regexp=paste0("Class: H5File\nFilename: ",
                                                 normalizePath(test_file, mustWork=FALSE),
                                                 "\nAccess type: H5F_ACC_RDWR\n",
                                                 "Attributes: attr1, attr2\n",
                                                 "Listing:\n",
                                                 " name  obj_type dataset.dims dataset.type_class\n",
                                                 " test H5I_GROUP         <NA>               <NA>"), fixed=TRUE)

    #H5Group also prints the name of the group
    expect_output(h5group$print(), regexp=paste0("Class: H5Group\nFilename: ",
                                                 normalizePath(test_file, mustWork=FALSE),
                                                 "\nGroup: /test\nAttributes: grp_attr\n",
                                                 "Listing:\n",
                                                 "      name    obj_type dataset.dims dataset.type_class\n",
                                                 " test_dset H5I_DATASET  5 x 10 x 15          H5T_FLOAT"), fixed=TRUE)

    ## create a dataset inside the group
    expect_output(h5dset$print(), regexp=paste0("Class: H5D\n",
                                                "Dataset: /test/test_dset\n",
                                                "Filename: ",
                                                normalizePath(test_file, mustWork=FALSE),
                                                "\nAccess type: H5F_ACC_RDWR\n",
                                                "Datatype: H5T_IEEE_F64LE\n",
                                                "Space: Type=Simple     Dims=5 x 10 x 15     Maxdims=5 x 10 x 15\n",
                                                "Chunk: 5 x 10 x 15"), fixed=TRUE)


    ## test the printing of datatypes
    test_type <- h5types$H5T_STD_I32LE
    expect_output(test_type$print(), regexp=paste0("Class: H5T_INTEGER\nDatatype: H5T_STD_I32LE"), fixed=TRUE)

    group_attr <- h5group$attr_open_by_name("grp_attr", ".")
    expect_output(group_attr$print(), regexp=paste0("Class: H5A\n",
                                                    "Attribute: grp_attr\n",
                                                    "Datatype: H5T_STRING {\n",
                                                    "      STRSIZE H5T_VARIABLE;\n",
                                                    "      STRPAD H5T_STR_NULLTERM;\n",
                                                    "      CSET H5T_CSET_ASCII;\n",
                                                    "      CTYPE H5T_C_S1;\n",
                                                    "   }\n",
                                                    "Space: Type=Simple     Dims=1     Maxdims=1"), fixed=TRUE)
    
    ## cleanup
    file.h5$close_all()
    file.remove(test_file)

})

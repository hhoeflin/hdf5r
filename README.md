| Check         | Engine | Status
| ------------- |--------|:-------------:|
| **Linux, OSX**|[Travis](https://travis-ci.org)|[![Build Status](https://travis-ci.org/hhoeflin/hdf5r.svg?branch=master)](https://travis-ci.org/hhoeflin/hdf5r)|
|**Windows**|[AppVeyor](https://www.appveyor.com)|[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/hhoeflin/hdf5r?branch=master&svg=true)](https://ci.appveyor.com/project/hhoeflin/hdf5r)|
|**ASAN, valgrind**|[Wercker](http://www.wercker.com)|[![wercker status](https://app.wercker.com/status/6a30e9d63b5d38539e28505b2fe6c440/s/master "wercker status")](https://app.wercker.com/project/byKey/6a30e9d63b5d38539e28505b2fe6c440)|
|**Code Coverage**|[Codecov](https://codecov.io/)|[![codecov.io](http://codecov.io/github/hhoeflin/hdf5r/coverage.svg?branch=master)](http://codecov.io/github/hhoeflin/hdf5r?branch=master)|

**hdf5r** is an R interface to the [HDF5](https://www.hdfgroup.org/HDF5) library. It is implemented using [R6](https://CRAN.R-project.org/package=R6) classes based on the [HDF5-C-API](https://support.hdfgroup.org/HDF5/doc/RM/RM_H5Front.html). The package supports all data-types as specified by HDF5 (including references) and provides many convenience functions yet also an extensive selection of the native HDF5-C-API functions. **hdf5r** is available on [Github](https://github.com/hhoeflin/hdf5r) and has already been released on [CRAN](https://cran.r-project.org/web/packages/hdf5r/index.html) for all major platforms (Windows, OS X, Linux). It is also 
tested using several hundred assertions.

[HDF5](https://www.hdfgroup.org/HDF5/) is an excellent library and data model to 
store huge amounts of data in a binary file format. Supporting most major 
platforms and programming languages it can be used to exchange data files in a 
language independent format. Compared to R's integrated *save()* and *load()* 
functions it also supports access to only parts of the binary data files and can
therefore be used to process data not fitting into memory.

# Install

**hdf5r** is available for all major platforms, namely Linux, OS X and Windows. 
The package is compatible with HDf5 version 1.8.13 or higher (also Version 1.10.0). 

## Requirements

For OS X and Linux the HDF5 library needs to be installed via one of the (shell) commands specified below:

| System                                    | Command
|:------------------------------------------|:---------------------------------|
|**OS X (using Homebrew)**                  | `brew install hdf5`
|**Debian-based systems (including Ubuntu)**| `sudo apt-get install libhdf5-dev` 
|**Systems supporting yum and RPMs**        | `sudo yum install hdf5-devel`

HDF5 1.8.14 has been pre-compiled for Windows and is available at https://github.com/mannau/h5-libwin - thus no manual installation is required.

## Basic Install

The latest release version of **hdf5r** can be installed from any CRAN [Mirror](https://cran.r-project.org/mirrors.html) using the R command
```r
install.packages("hdf5r")
```
For the latest development version from Github you can use
```r
devtools::install_github("hhoeflin/hdf5r")
```

# Getting Started

## How to Get Help

The package provides most of the regular HDF5-API in addition to a number of convenience functions. As such, the number of available methods is 
quite large. As the package uses R6 classes, all applicable methods for a class are contained in that class. The easiest way to get an 
overview of the available methods is to call the *methods* method. 

```r
native_int_type <- h5types$H5T_NATIVE_INT
native_int_type$methods()
```

Of course, there is also the regular R help that you can call for each class. These help pages tend to be long, as they also document all
methods of that class.

```r
help("H5T-class")
```

Last, I very much recomment reading the included vignette. You can view all vignettes included in the pacakge with

```r
vignette(package="hdf5r")
```

and call up the introduction vignette with

```r
vignette("hdf5r", package="hdf5r")
```


## Simple Code Example

If you don't have time to read the vignette, which contains more code example, here is a very brief code example to 
create a file, write some data and read it back again.

```r
test_file <- tempfile(fileext=".h5")
file.h5 <- H5File$new(test_file, mode="w")

data(cars)
file.h5$create_group("test")
file.h5[["test/cars"]] <- cars
cars_ds <- file.h5[["test/cars"]]
h5attr(cars_ds, "rownames") <- rownames(cars)

## Close the file at the end
## the 'close' method closes only the file-id, but leaves object inside the file open
## This may prevent re-opening of the file. 'close_all' closes the file and all objects in it
file.h5$close_all()
```


```r
## now re-open it 
file.h5 <- H5File$new(test_file, mode="r+")

## lets look at the content
file.h5$ls(recursive=TRUE)

cars_ds <- file.h5[["test/cars"]]
## note that for now tables in HDF5 are 1-dimensional, not 2-dimensional
mycars <- cars_ds[]
h5attr_names(cars_ds)
h5attr(cars_ds, "rownames")

file.h5$close_all()
```

# 64-bit Integers

Please note that for 64-bit signed integers, the bit64 package is used. For technical reasons, it is possible for a function that is not bit64-aware to misrepresent 64bit values from the bit64 package as 'doubles' of a completely different value. Therefore, please be advised to ensure that the functions you are using are bit64-aware or cast the values to regular numeric values (but be aware - this may result in a loss of precision). For illustration of this issue see the difference between `print(as.integer64(1))` and `cat(as.integer64(1), "\n")`. Another possible source of issues can be `matrix(as.integer64(1))` or `min(as.integer64(1), as.integer64(2))`, among possibly others. By default, hdf5r tries to return regular R objects (integer or double) wherever this is possible without loss of precision. If you need 64bit integers, proceed with care keeping these issues in mind.

# License

The hdf5r package is licensend under Apache License Version 2.0. HDF5 itself doesn't ship with the hdf5r package on Linux or Mac, but on windows the downloadable binary compiled on CRAN has the HDF5 binary included. The HDF5 Copyright notice can be found below.

## hdf5r package

Copyright 2016 Novartis Institutes for BioMedical Research Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


## HDF5

The licensing terms of HDF5 can as of this writing be found in the inst/HDF5_COPYRIGHTS file or online at

https://www.hdfgroup.org/ftp/HDF5/releases/hdf5-1.10/hdf5-1.10.0/src/unpacked/COPYING

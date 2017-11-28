#' Wrapper functions to provide an \pkg{h5} compatible interface.
#' 
#' The functions listed below provide a wrapper-interface compatible to 
#' functions specified in the \pkg{h5} package. The author(s)
#' have decided to deprecate \pkg{h5} and join forces and still 
#' make the transition for \pkg{h5} users as smooth as possible.
#' Additionally, almost all testcases could be transferred to \pkg{hdf5r} 
#' to improve test coverage even more.
#' 
#' Below you can find a list of all \strong{h5} functions including \strong{hdf5r} \emph{mappings}.
#' \describe{
#'   \item{h5file}{Directly maps to \code{H5File$new}, see also \code{\link{H5File}}.}
#'   \item{createGroup}{Maps to \code{object$create_group} where object implements \emph{CommonFG}.}
#'   \item{openLocation}{Uses \code{object$open} where object implements \emph{CommonFG}.}
#'   \item{createDataSet}{Maps to \code{object$create_dataset} where object implements \emph{CommonFG}.}
#'   \item{readDataSet}{Maps to \code{object$read}, see also \code{\link{H5D}}.}
#'   \item{h5close}{Maps to \code{object$close_all} for \code{\link{H5File}} and \code{object$close} 
#'     for other.}
#'   \item{h5flush}{Maps to \code{object$flush} where object implements \emph{CommonFGDTA}.}
#' }
#' 
#' The following \strong{interfaces} are defined:
#' \describe{
#'   \item{CommonFG}{Implemented by objects of class 
#'     \code{\link{H5File}} and 
#'     \code{\link{H5Group}}.}
#'   \item{CommonFGDTA}{Implemented by objects of class
#'     \code{\link{H5File}}, 
#'     \code{\link{H5Group}}, 
#'     \code{\link{H5D}}, 
#'     \code{\link{H5T}} and
#'     \code{\link{H5A}}.}
#' }
#' 
#' @references Mario Annau (2017). \emph{\pkg{h5}: Interface to the 'HDF5' Library}. R package version 0.9.9.
#' \url{https://github.com/mannau/h5}
#' @name h5-wrapper
#' @aliases h5
NULL

#' @rdname h5-wrapper
#' @export
h5file <- H5File$new

#' @rdname h5-wrapper
#' @param object \code{CommonFG}; Object implementing the CommonFG Interface (e.g. \code{\link{H5File}}, \code{\link{H5Group}}).
#' @param name Name of the group to create.
#' @param ... Additional parameters passed to \code{create_group} or \code{h5file}.
#' @export
createGroup <- function(object, name, ...) {
  paths <- strsplit(name, "/")[[1]]
  paths <- paths[paths != ""]
  currentpath <- ""
  currentgroup <- NULL
  for(p in paths) {
    currentpath <- paste(currentpath, p, sep = "/")
    currentpath <- gsub("^\\/", "", currentpath)
    if (! object$exists(currentpath) ) {
      currentgroup <- object$create_group(currentpath, ...)
    }
  }
  currentgroup
}

#' @rdname h5-wrapper
#' @export
openLocation <- function(object, name) object$open(name=name)

#' @rdname h5-wrapper
#' @export
createDataSet <- function(object, name, ...) object$create_dataset(name, ...)

#' @rdname h5-wrapper
#' @export
readDataSet <- function(object) object$read()

#' @rdname h5-wrapper
#' @export
h5close <- function(object) {
    if(inherits(object, "H5File")) {
        object$close_all()
    }
    else {
        object$close()
    }
}

#' @rdname h5-wrapper
#' @export
h5flush <- function(object) object$flush()

#' @rdname h5-wrapper
#' @export
existsGroup <- function(object, name) {
  out <- tryCatch({
    object$exists(name)
  }, error = function(e) FALSE)
  out
}

#' @rdname h5-wrapper
#' @export
is.h5file <-
function(name) {
  res <- FALSE
  if(file.exists(name)) {
    res <- as.logical(.Call('R_H5Fis_hdf5', PACKAGE = 'hdf5r', name))
  } else {
    warning("File does not exist.")
  }
  res
}

#' List Groups and Datasets in object
#' 
#' List all Group (\code{\link{H5Group}}) and Dataset (\code{\link{H5D}}) 
#' names in the current object. This function is part of the \strong{h5} wrapper classes and
#' uses \code{$ls()} to retrieve group names.
#' 
#' @param object \code{CommonFG}; Object implementing the CommonFG Interface (e.g. \code{\link{H5File}}, \code{\link{H5Group}}).
#' @param path character; Path named to be used for iteration.
#' @param full.names character; Specify if absolute DataSet path names should be returned.
#' @param obj_type character; Object type to be returned.
#' @param recursive logical; Specify if object should be traversed recursively.
#' @param ... Additional Parameters passed to \code{$ls()}
#' @return \code{\link{character}}
#' @name list-groups-datasets
NULL

#' @rdname list-groups-datasets
#' @export
list.groups <- function(object, path = "/", full.names = FALSE, recursive = TRUE, ...) {
  list.objects(object, "H5I_GROUP", path, full.names, recursive, ...)
}

#' @rdname list-groups-datasets
#' @export
list.datasets <- function(object, path = "/", full.names = FALSE, recursive = TRUE, ...) {
  list.objects(object, "H5I_DATASET", path, full.names, recursive, ...)
}

#' @rdname list-groups-datasets
#' @export
list.objects <- function(object, obj_type = c("H5I_GROUP", "H5I_DATASET", "H5I_DATATYPE"), 
  path = "/", full.names = FALSE, recursive = TRUE, ...) {
  
  obj_type = match.arg(obj_type, several.ok = TRUE)
  if (path != "/") object <- object[[path]]
  df <- object$ls(... , recursive = recursive)
  onames <- df[as.character(df$obj_type) %in% obj_type, "name"]
  if (full.names) {
    onames <- sprintf("%s/%s", object$get_obj_name(), onames)
    onames <- gsub("^/+", "/", onames)
  }
  onames
}

GetDimensions <- function(data) {
  datadim <- NULL
  if(is.vector(data)) {
    datadim <- length(data)
  } else if (is.matrix(data)) {
    datadim <- dim(data)
  } else if (is.array(data)) {
    datadim <- dim(data)
  } else {
    stop("Argument data must be of type vector, matrix or array.")
  }
  datadim
}

#' @rdname h5-wrapper
#' @param dims numeric; Dimension vector to which dataset should be extended.
#' @export
extendDataSet <- function(object, dims) {
  ddset <- object$dims
  #dobj <- GetDimensions(object)
  if (length(dims) != length(ddset)) {
    stop("Number of extendible dimensions must agree with DataSet dimensions.")
  }
  if(!all(dims >= ddset)) {
    stop("Number of extendible dimensions must be greater or equal than DataSet dimensions.")
  }

  if(!all(dims <= object$maxdims)) {
    stop("Number of extendible dimensions exceeds maximum dimensions of DataSet.")
  }

  object$set_extent(dims = dims)
  invisible(object)
}

#' @rdname h5-wrapper
#' @param x An object of class H5D; the dataset to add rows or columns to; Needs to be a matrix
#' @param mat The matrix to add to x
#' @param deparse.level Set to 1; ignored otherwise; only present as required by generic
#' @export
rbind.H5D <- function(x, mat, ..., deparse.level=1) {
  xdims <- x$dims
  if(length(xdims) != 2) {
      stop("x needs to be a matrix (2-dimensionsal)")
  }
  startx <- xdims[1] + 1
  endx <- xdims[1] + nrow(mat)

  if(xdims[2] != ncol(mat)) {
    stop(sprintf("Data to append does not match dataset dimensions (%d != %d).",
                 xdims[2], ncol(mat)))
  }

  x[startx:endx, 1:xdims[2]] <- mat
  invisible(x)
}

#' @rdname h5-wrapper
#' @export
cbind.H5D <- function(x, mat, ..., deparse.level=1) {
  xdims <- x$dims
  if(length(xdims) != 2) {
      stop("x needs to be a matrix (2-dimensionsal)")
  }
  starty <- xdims[2] + 1
  endy <- xdims[2] + ncol(mat)

  if(xdims[1] != nrow(mat)) {
    stop(sprintf("Data to append does not match dataset dimensions (%d != %d).",
                 xdims[1], nrow(mat)))
  }

  x[1:xdims[1], starty:endy] <- mat
  invisible(x)
}

#' @rdname h5-wrapper
#' @export
c.H5D <- function(x, ...) {
  vec <- do.call(c, list(...))
  start <- x$dims + 1
  end <- x$dims + length(vec)

  if(length(x$dims) != length(GetDimensions(vec))) {
    stop(sprintf("Data to append does not match dataset dimensions (%d != %d).",
                 length(x$dims), length(GetDimensions(vec))))
  }
  x[start:end] <- vec
  invisible(x)
}

#' @rdname h5-wrapper
#' @export
h5unlink <- function(object, name) {
  out <- sapply(name, function(n) {
    tryCatch({
      object$link_delete(n)
      TRUE
      }, error = function(e) FALSE)
  })
  invisible(out)
}

#' @rdname h5-wrapper
#' @export
list.attributes <- function(object) {
  h5attr_names(object)
}

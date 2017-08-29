#' h5 wrapper functions
#'
#' Wrapper functions to provide h5 compatible interface.
#' @param object H5RefClass; H5 Reference Class to be used
#' @param name character; Group/Filename to be created
#' @param path character; Path named to be used for iteration.
#' @param recursive logical; Specify if object should be traversed recursively.
#' @param ... Additional Parameters passed to \code{file$create_group}, \code{file$create_dataset} or ignored for \code{cbind} and \code{rbind}.
#'
#' @rdname h5-wrapper
#' @export
h5file <- H5File$new

#' @rdname h5-wrapper
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

#' @rdname h5-wrapper
#' @export
list.groups <- function(object, path = "/", recursive = TRUE, ...) {
  obj <- object
  if (path != "/") obj <- object[[path]]
  df <- obj$ls(... ,recursive = recursive)
  df[df$object.type == "H5O_TYPE_GROUP", 1]
}

#' @rdname h5-wrapper
#' @export
list.datasets <- function(object, path = "/", recursive = TRUE, ...) {
  obj <- object
  if (path != "/") obj <- object[[path]]
  df <- obj$ls(... ,recursive = recursive)
  df[df$object.type == "H5O_TYPE_DATASET", 1]
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

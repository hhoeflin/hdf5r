

#############################################################################
##
## Copyright 2016 Novartis Institutes for BioMedical Research Inc.
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
## http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
##
#############################################################################







setOldClass("factor_ext")


INT_MIN <- as.integer64(-2^31)
INT_MAX <- as.integer64(2^31 - 1)


##' Create an extended factor
##'
##' An extended version of a regular \code{factor} variable. Instead of the levels having values from
##' 1 to n where n is the number of levels, any integer value can be used for any level (including 64bit integers). If
##' all values are in the range of a regular 32-bit integer, it is coerced to int. Automatic coercion of extended factors
##' to factors in \code{\link{H5ToR_Post}} for enums only works for 32-bit integer base types.
##' In this page this is heavily used, as constants in HDF5 can be arbitrary integer values.
##' @title Create an extended factor
##' @param x The object to convert to an \code{factor_ext}
##' @param values The values used for the levels; This is were \code{factor_ext} is different from a
##' \code{factor}, as values for levels do not have to be consecutive or start at 1.
##' @param levels The levels of the object; character string
##' @param drop Should non-occurring levels be dropped
##' @return An object of S3 class \code{factor_ext}
##' @author Holger Hoefling
##' @importFrom methods setOldClass
##' @export
factor_ext <- function(x, values, levels, drop=FALSE) {
    if(inherits(x, "factor_ext") && missing(values)) {
        values <- attr(x, "values")
    }
    if(inherits(x, "factor_ext") && missing(levels)) {
        levels <- attr(x, "levels")
    }
    if(is.numeric(x) && missing(values)) {
        values <- sort(unique(x))
    }
    
    ## treat values first
    if(is.integer(values)) {
        values <- as.integer(values)
    }
    else if(is.numeric(values) && !is.integer64(values)) {
        if(any(as.numeric(as.integer64(values)) != values)) {
            stop("x needs to be integer valued")
        }
        values <- as.integer64(values)
    }

    if(is.integer64(values)) {
        ## check if it can be forced into an integer
        if(all(values >= INT_MIN & values <= INT_MAX)) {
            values <- as.integer(values)
        }
    }
    
    if(is.numeric(x)) {
        if(missing(levels)) {
            stop("For x numeric, levels have to be set")
        }
        if(missing(values)) {
            ## already taken care of above; not relevant anymore
        }
        if(length(values) != length(levels)) {
            stop("values and levels have to have the same length")
        }
        if(drop) {
            incl <- values %in% x
            values <- unname(values[incl])
            levels <- levels[incl]
        }
        ## coerce x to the same type as values
        if(is.integer64(values)) {
            x <- as.integer64(x)
        }
        else {
            x <- as.integer(x)
        }
        
        x[!(x %in% values)] <- NA
    }
    else if(is.character(x)) {
        if(missing(values)) {
            stop("For x character, values have to be set")
        }
        if(missing(levels)) {
            levels <- sort(unique(x))
        }
        if(length(values) != length(levels)) {
            stop("values and levels have to have the same length")
        }
        if(drop) {
            incl <- levels %in% x
            values <- unname(values[incl])
            levels <- levels[incl]
        }
        x[!(x %in% levels)] <- NA
        x <- values[match(x, levels)]        
    }
    else {
        stop("x has to be numeric or character")
    }

    ## now sort the levels by increasing values
    val_order <- order(values, decreasing=FALSE)
    levels <- levels[val_order]
    values <- values[val_order]

    if(is.integer64(x)) {
        class(x) <- c("factor_ext", "integer64")
    }
    else {
        class(x) <- "factor_ext"
    }
    levels(x) <- levels
    attr(x, "values") <- values
    return(x)
}

## need to overload the same functions that are also available for factors
## also, is.factor and a conversion function as.factor (which should be really simple)




##' Various functions for \code{factor_ext} objects
##'
##' \describe{
##'   \item{values}{Extracts the underlying values of an object (the generic here)}
##'   \item{values.factor_ext}{Extracts the underlying values of a \code{factor_ext} object}
##'   \item{values.factor}{Extracts the underlying values of a \code{factor}}
##'   \item{values.default}{Default of the values function; currently returns an error}
##'   \item{as.character}{Coerces \code{factor_ext} to a character-representation using it levels, not values}
##'   \item{[[.factor_ext}{Single-item subsetting of a \code{factor_ext} object}
##'   \item{[[<-.factor_ext}{Single-item subset assignment to a \code{factor_ext} object}
##'   \item{[.factor_ext}{Subsetting of a \code{factor_ext} object}
##'   \item{[<-.factor_ext}{Subset assignment to a \code{factor_ext} object}
##'   \item{is.factor_ext}{Check if it is a \code{factor_ext} object. Returns a logical}
##'   \item{coercible_to_factor}{Checks if a \code{factor_ext} could be coerced to a \code{factor}. Return a logical.}
##'   \item{coerce_to_factor}{Coerces to a \code{factor}, otherwise throws an error if not possible.}
##'   \item{print.factor_ext}{Prints a \code{factor_ext} object.}
##'   \item{==.factor_ext}{Compare two \code{factor_ext} for equality.}
##'   \item{!=.factor_ext}{Compare two \code{factor_ext} for inequality.}
##'   \item{c.factor_ext}{Concatenate objects of type \code{factor_ext}.}
##' }
##' @title Various functions for \code{factor_ext} objects
##' @param x Object of type \code{factor_ext}
##' @param quote logical, indicating whether or not strings should be printed with surrounding quotes.
##' @param max.levels integer, indicating how many levels should be printed. if '0', no extra "Levels" line will be printed.  The
##' default, 'NULL', entails choosing 'max.levels' such that the levels print on one line of width 'width' (same for values).
##' @param width only used when \code{max.levels} is NULL (see above)
##' @param e1,e2 The two objects in the equality or inequality comparison.
##' @param ... Currently ignored
##' @param drop Should dimensions of size 1 be dropped?
##' @param value The object to assign; here has be a level of \code{factor_ext}
##' @return Depending on the function
##' @author Holger Hoefling
##' @name factor_ext_functions
NULL


##' @export
##' @rdname factor_ext_functions 
values <- function(x, ...) {
    UseMethod("values")
}

##' @export
##' @rdname factor_ext_functions 
values.factor_ext <- function(x, ...) {
    attr(x, "values")
}

##' @export
##' @rdname factor_ext_functions 
values.factor <- function(x, ...) {
    as.numeric(x)
}

##' @export
##' @rdname factor_ext_functions 
values.default <- function(x, ...) {
    stop("Currently not implemented")
}

## internal helper function
position <- function(x) {
    .match <- function(x, y) match(unclass(x), unclass(y))
    if(is.integer64(values(x)) && is.integer(x)) {
        .match(as.integer64(unclass(x)), as.integer64(values(x)))
    }
    else if(is.integer(values(x)) && is.integer64(x)) {
        .match(x, as.integer64(values(x)))
    }
    else {
        .match(x, values(x))
    }
}

##' @export
##' @rdname factor_ext_functions 
as.character.factor_ext <- function (x, ...) {
    levels(x)[position(x)]
}

##' @export
##' @rdname factor_ext_functions 
"[[.factor_ext" <- function (x, ...) {
    y <- NextMethod("[[")
    attr(y, "contrasts") <- attr(x, "contrasts")
    attr(y, "levels") <- attr(x, "levels")
    attr(y, "values") <- attr(x, "values")
    class(y) <- oldClass(x)
    y
}

##' @export
##' @rdname factor_ext_functions 
"[[<-.factor_ext" <- function(x, ..., value) {    
    lx <- levels(x)
    vx <- values(x)
    cx <- oldClass(x)
    if (is.factor_ext(value)) 
        value <- levels(value)[position(value)]
    m <- vx[match(value, lx)]
    if (any(is.na(m) & !is.na(value))) 
        warning("invalid factor_ext level, NA generated")
    class(x) <- NULL
    x[[...]] <- m
    attr(x, "levels") <- lx
    attr(x, "values") <- vx
    class(x) <- cx
    x
}


##' @export
##' @rdname factor_ext_functions 
"[.factor_ext" <- function (x, ..., drop = FALSE) 
{
    y <- NextMethod("[")
    attr(y, "contrasts") <- attr(x, "contrasts")
    attr(y, "levels") <- attr(x, "levels")
    attr(y, "values") <- attr(x, "values")
    class(y) <- oldClass(x)
    if (drop) 
        factor(y, exclude = if (anyNA(levels(x))) 
            NULL
        else NA)
    else y
}

##' @export
##' @rdname factor_ext_functions 
"[<-.factor_ext" <- function(x, ..., value) {
    lx <- levels(x)
    vx <- values(x)
    cx <- oldClass(x)
    if (is.factor_ext(value)) 
        value <- levels(value)[position(value)]
    m <- vx[match(value, lx)]
    if (any(is.na(m) & !is.na(value))) 
        warning("invalid factor_ext level, NA generated")
    class(x) <- NULL
    x[...] <- m
    attr(x, "levels") <- lx
    attr(x, "values") <- vx
    class(x) <- cx
    x
}

##' @export
##' @rdname factor_ext_functions 
is.factor_ext <- function(x) {
    return(inherits(x, "factor_ext"))
}

##' @export
##' @rdname factor_ext_functions 
coercible_to_factor <- function(x) {
    if(!inherits(x, "factor_ext")) {
        stop("Only for objects of factor_ext classes")
    }
    vx <- values(x)
    if(all(vx == seq_along(vx))) {
        return(TRUE)
    }
    else {
        return(FALSE)
    }
}

##' @export
##' @rdname factor_ext_functions 
coerce_to_factor <- function(x) {
    if(!inherits(x, "factor_ext")) {
        stop("Only for objects of factor_ext classes")
    }
    if(coercible_to_factor(x)) {
        y <- factor(as.character(x), levels=levels(x))
        return(y)
    }
    else {
        stop("Cannot coerce to factor; values not a sequence starting at 1")
    }
}


##' @export
##' @rdname factor_ext_functions 
print.factor_ext <- function (x, quote = FALSE, max.levels = NULL, width = getOption("width"), ...) {
    if (length(x) == 0L) 
        cat("factor_ext", "(0)\n", sep = "")
    else {
        xx <- x
        class(xx) <- NULL
        levels(xx) <- NULL
        attr(xx, "values") <- NULL
        xx[] <- as.character(x)
        print(xx, quote = quote, ...)
    }
    maxl <- if (is.null(max.levels)) 
        TRUE
    else max.levels
    if (maxl) {
        n <- length(lev <- encodeString(levels(x), quote = ifelse(quote, 
            "\"", "")))
        colsep <- " "
        T0 <- "Levels: "
        if (is.logical(maxl)) 
            maxl <- {
                width <- width - (nchar(T0, "w") + 3L + 1L + 
                  3L)
                lenl <- cumsum(nchar(lev, "w") + nchar(colsep, 
                  "w"))
                if (n <= 1L || lenl[n] <= width) 
                  n
                else max(1L, which.max(lenl > width) - 1L)
            }
        drop <- n > maxl
        cat(if (drop) 
            paste(format(n), ""), T0, paste(if (drop) 
            c(lev[1L:max(1, maxl - 1)], "...", if (maxl > 1) lev[n])
        else lev, collapse = colsep), "\n", sep = "")
    }
    if (maxl) {
        n <- length(val <- encodeString(values(x), quote = ifelse(quote, 
                                                       "\"", "")))
        colsep <- " "
        T0 <- "Values: "
        if (is.logical(maxl)) 
            maxl <- {
                width <- width - (nchar(T0, "w") + 3L + 1L + 
                  3L)
                lenl <- cumsum(nchar(val, "w") + nchar(colsep, 
                  "w"))
                if (n <= 1L || lenl[n] <= width) 
                  n
                else max(1L, which.max(lenl > width) - 1L)
            }
        drop <- n > maxl
        cat(if (drop) 
            paste(format(n), ""), T0, paste(if (drop) 
            c(val[1L:max(1, maxl - 1)], "...", if (maxl > 1) val[n])
        else val, collapse = colsep), "\n", sep = "")
    }
    invisible(x)
}

##' @export
##' @rdname factor_ext_functions 
"==.factor_ext" <- function(e1, e2){
    if(inherits(e2, "factor_ext")) {
        e1 <- as.character(e1)
        e2 <- as.character(e2)
        return(e1==e2)
    }
    if(is.character(e2)) {
        e1 <- as.character(e1)
        return(e1 == e2)
    }
    else {
        class(e1) <- NULL
        return(e1 == e2)
    }
}

##' @export
##' @rdname factor_ext_functions 
"!=.factor_ext" <- function(e1, e2){
    if(inherits(e2, "factor_ext")) {
        e1 <- as.character(e1)
        e2 <- as.character(e2)
        return(e1!=e2)
    }
    if(is.character(e2)) {
        e1 <- as.character(e1)
        return(e1 != e2)
    }
    else {
        class(e1) <- NULL
        return(e1 != e2)
    }
}


##' @export
##' @rdname factor_ext_functions 
c.factor_ext <- function(...) {
    l <- list(...)
    ## check that the values and the levels for all of them the same and the class is all the same
    inherits_factor_ext <- unique(unlist(lapply(l, inherits, what="factor_ext")))
    if(all(inherits_factor_ext)) {
        item1_levels <- levels(l[[1]])
        item1_values <- values(l[[1]])
        all_levels <- unique(unlist(lapply(l, levels)))
        all_values <- unique(unlist(lapply(l, values)))
        if(length(item1_levels)==length(all_levels) && length(item1_values)==length(all_values)) {
            y <- do.call("c", lapply(l, as.integer))
            class(y) <- "factor_ext"
            attr(y, "levels") <- item1_levels
            attr(y, "values") <- item1_values
            return(y)
        }
        else {
            stop("Not all factor_ext the same levels")
        }
    }
    else {
        stop("Can only concatenate with factor_ext object if all are of the same class")        
    }
}

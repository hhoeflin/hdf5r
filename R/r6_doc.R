## Documentation helpers for the R6 classes.
##
## Most hdf5r methods carry their documentation as "docstrings" - bare string
## literals at the top of the method body:
##
##     create_attr=function(attr_name, robj=NULL, dtype=NULL, space=NULL) {
##         "This function implements the HDF5-API function H5Acreate2."
##         "@param attr_name The name of the attribute."
##
## Methods defined directly inside an R6Class() call are documented with normal
## roxygen comments. The shared method lists in Common_functions.R cannot be:
## they are attached to the generators at run time by R6_set_list_of_items(), so
## roxygen never sees a comment attached to them. For those, r6_doc() turns the
## docstrings into roxygen tags at documentation time via
##
##     #' @eval r6_doc("H5File", "create_attr")
##     NULL
##
## which roxygen2 re-parses into an external @R6method block. See R/r6_docs.R.


## Return the leading string literals of a function body.
r6_docstrings <- function(fn) {
    b <- body(fn)
    if(!is.call(b) || !identical(b[[1]], as.name("{"))) {
        return(character())
    }
    out <- character()
    for(i in seq_along(b)[-1]) {
        el <- b[[i]]
        if(is.character(el) && length(el) == 1) {
            out <- c(out, el)
        }
        else {
            break
        }
    }
    out
}


## Split docstrings into description, @param and @return. A tag runs until the
## next tag, so plain lines after "@param x ..." continue that parameter.
r6_parse_docstrings <- function(ds) {
    description <- character()
    params <- list()
    returns <- character()
    current <- NULL

    for(line in ds) {
        if(grepl("^@param[[:space:]]+", line)) {
            nm <- sub("^@param[[:space:]]+([^[:space:]]+).*$", "\\1", line)
            params[[nm]] <- trimws(sub("^@param[[:space:]]+[^[:space:]]+[[:space:]]*", "", line))
            current <- nm
        }
        else if(grepl("^@return[[:space:]]+", line)) {
            returns <- trimws(sub("^@return[[:space:]]*", "", line))
            current <- ".__return__."
        }
        else if(grepl("^@", line)) {
            ## some other tag; ignore it and anything continuing it
            current <- NA_character_
        }
        else if(is.null(current)) {
            description <- c(description, trimws(line))
        }
        else if(identical(current, "\1return")) {
            returns <- paste(returns, trimws(line))
        }
        else if(!is.na(current)) {
            params[[current]] <- paste(params[[current]], trimws(line))
        }
    }

    list(description=description, params=params, returns=returns)
}


## Fallback descriptions for arguments that the docstrings don't cover. Keyed by
## argument name, so the same argument reads identically everywhere it appears.
##
## Built with unlist(list(...)) rather than c(...) on purpose: c() has its own
## 'recursive' and 'use.names' formals, so c(recursive = "...") would be matched
## as an argument to c() and silently dropped from the result.
.r6_param_glossary <- unlist(list(
    ## --- identifiers and names ---
    id                       = "An HDF5 id; for internal use only.",
    name                     = "The name of the object, relative to the object the method is called on.",
    obj_name                 = "The name of the object, relative to the object the method is called on.",
    object_name              = "The name of the object, relative to the object the method is called on.",
    group_name               = "The name of the group, relative to the object the method is called on.",
    link_name                = "The name of the link.",
    new_link_name            = "The new name of the link.",
    attr_name                = "The name of the attribute.",
    old_attr_name            = "The current name of the attribute.",
    new_attr_name            = "The new name of the attribute.",
    src_name                 = "The name of the source object.",
    dst_name                 = "The name of the destination object.",
    src_loc                  = "The source location; an object of class \\code{\\link{H5File}} or \\code{\\link{H5Group}}.",
    dst_loc                  = "The destination location; an object of class \\code{\\link{H5File}} or \\code{\\link{H5Group}}.",
    obj_loc                  = "The location of the object; an object of class \\code{\\link{H5File}} or \\code{\\link{H5Group}}.",
    path                     = "The path of the object inside the file.",
    target_path              = "The path of the target object.",
    target_filename          = "The name of the file that holds the target object.",
    target_obj_name          = "The name of the target object.",
    child                    = "The object to mount; an object of class \\code{\\link{H5File}}.",
    cmp                      = "The object to compare against.",
    x                        = "The object to operate on.",

    ## --- iteration and indexing ---
    n                        = "The index of the item to access; zero-based.",
    idx                      = "The index of the item to access; zero-based.",
    num                      = "The number of items.",
    idx_type                 = "The index to iterate over; one of the \\code{H5_INDEX_*} values in \\code{\\link{h5const}}.",
    index_type               = "The index to iterate over; one of the \\code{H5_INDEX_*} values in \\code{\\link{h5const}}.",
    index_field              = "The index to iterate over; one of the \\code{H5_INDEX_*} values in \\code{\\link{h5const}}.",
    order                    = "The order in which to iterate; one of the \\code{H5_ITER_*} values in \\code{\\link{h5const}}.",
    recursive                = "Logical; should the listing descend into subgroups.",
    detailed                 = "Logical; should a more detailed listing be returned.",
    remove_internal_use_only = "Logical; should fields that are only of internal use be dropped from the result.",
    check_object_valid       = "Logical; should the object be checked for validity first.",

    ## --- property lists ---
    link_access_pl           = "The link access property list. See \\code{\\link{H5P_LINK_ACCESS}}.",
    link_create_pl           = "The link creation property list. See \\code{\\link{H5P_LINK_CREATE}}.",
    file_create_pl           = "The file creation property list. See \\code{\\link{H5P_FILE_CREATE}}.",
    file_access_pl           = "The file access property list. See \\code{\\link{H5P_FILE_ACCESS}}.",
    dataset_create_pl        = "The dataset creation property list. See \\code{\\link{H5P_DATASET_CREATE}}.",
    dataset_access_pl        = "The dataset access property list. See \\code{\\link{H5P_DATASET_ACCESS}}.",
    dataset_xfer_pl          = "The dataset transfer property list. See \\code{\\link{H5P_DATASET_XFER}}.",
    attr_create_pl           = "The attribute creation property list. See \\code{\\link{H5P_ATTRIBUTE_CREATE}}.",
    attr_access_pl           = "The attribute access property list.",
    object_copy_pl           = "The object copy property list. See \\code{\\link{H5P_OBJECT_COPY}}.",
    object_create_pl         = "The object creation property list. See \\code{\\link{H5P_OBJECT_CREATE}}.",
    group_create_pl          = "The group creation property list.",
    group_access_pl          = "The group access property list.",
    type_create_pl           = "The datatype creation property list.",
    type_access_pl           = "The datatype access property list.",

    ## --- datatypes and dataspaces ---
    dtype                    = "The datatype to use; an object of class \\code{\\link{H5T}}.",
    dtype_class              = "The datatype class to look for; one of the \\code{H5T_*} class values in \\code{\\link{h5const}}.",
    mem_type                 = "The memory datatype to use for the transfer; an object of class \\code{\\link{H5T}}.",
    space                    = "The dataspace to use; an object of class \\code{\\link{H5S}}.",
    types                    = "The types of object to count; one or more of the \\code{H5F_OBJ_*} values in \\code{\\link{h5const}}.",
    robj                     = "An R object to use as a template for the datatype and dataspace.",
    dims                     = "The dimensions of the object.",
    size                     = "The size of the object in bytes; use \\code{Inf} for variable-length strings.",
    precision                = "The precision of the datatype, in bits.",
    pad                      = "The padding to use for unused bits; one of the \\code{H5T_PAD_*} values in \\code{\\link{h5const}}.",
    sign                     = "The signedness of the integer; one of the \\code{H5T_SGN_*} values in \\code{\\link{h5const}}.",
    native                   = "Logical; should the native version of the datatype be returned.",
    direction                = "The direction in which to search for a native type; one of the \\code{H5T_DIR_*} values in \\code{\\link{h5const}}.",
    lang_type                = "The language to produce the text representation in; one of the \\code{H5LT_LANG_*} values in \\code{\\link{h5const}}.",
    cset                     = "The character set to use; one of the \\code{H5T_CSET_*} values in \\code{\\link{h5const}}.",
    encoding                 = "The character encoding to use; one of the \\code{H5T_CSET_*} values in \\code{\\link{h5const}}.",
    strpad                   = "The string padding to use; one of the \\code{H5T_STR_*} values in \\code{\\link{h5const}}.",
    variable_as_inf          = "Logical; should variable-length strings report their size as \\code{Inf}.",
    include_NA               = "Logical; should the enumeration include a level for \\code{NA}.",

    ## --- floating point layout (H5T_FLOAT) ---
    spos                     = "The bit position of the sign bit.",
    epos                     = "The bit position of the exponent field.",
    esize                    = "The size of the exponent field, in bits.",
    mpos                     = "The bit position of the mantissa field.",
    msize                    = "The size of the mantissa field, in bits.",
    ebias                    = "The exponent bias.",
    norm                     = "The mantissa normalisation; one of the \\code{H5T_NORM_*} values in \\code{\\link{h5const}}.",
    inpad                    = "How to fill unused internal bits; one of the \\code{H5T_PAD_*} values in \\code{\\link{h5const}}.",

    ## --- dataspace selection (H5S) ---
    start                    = "The offset at which the hyperslab starts, one value per dimension.",
    count                    = "The number of blocks to select, one value per dimension.",
    stride                   = "The distance between successive blocks, one value per dimension.",
    block                    = "The size of each block, one value per dimension.",
    coord                    = "The coordinates of the elements to select.",
    byrow                    = "Logical; are the coordinates given row-wise.",
    startblock               = "The first block to return; zero-based.",
    numblocks                = "The number of blocks to return.",
    startpoint               = "The first point to return; zero-based.",
    numpoints                = "The number of points to return.",
    h5s_source               = "The dataspace to copy the extent from; an object of class \\code{\\link{H5S}}.",
    h5s_cmp                  = "The dataspace to compare the extent against; an object of class \\code{\\link{H5S}}.",
    max_ndims                = "The maximum number of dimensions to return.",

    ## --- references (H5R) ---
    ref                      = "The reference to use.",
    get_value                = "Logical; should the referenced values be returned instead of the objects.",

    ## --- storage, filters and file layout ---
    layout                   = "The dataset layout; one of the \\code{H5D_*} layout values in \\code{\\link{h5const}}.",
    chunk                    = "The chunk dimensions.",
    filter                   = "The filter to use; one of the \\code{H5Z_FILTER_*} values in \\code{\\link{h5const}}.",
    cd_values                = "Auxiliary data passed to the filter.",
    level                    = "The compression level, between 0 and 9.",
    scale_type               = "The scale-offset filter type; one of the \\code{H5Z_SO_*} values in \\code{\\link{h5const}}.",
    scale_factor             = "The scale factor used by the scale-offset filter.",
    fill_time                = "When the fill value is written; one of the \\code{H5D_FILL_TIME_*} values in \\code{\\link{h5const}}.",
    alloc_time               = "When storage is allocated; one of the \\code{H5D_ALLOC_TIME_*} values in \\code{\\link{h5const}}.",
    track_times              = "Logical; should object times be recorded in the file.",
    rdcc_nslots              = "The number of slots in the raw data chunk cache. Use -1 for the library default.",
    rdcc_nbytes              = "The size of the raw data chunk cache in bytes. Use -1 for the library default.",
    rdcc_w0                  = "The chunk preemption policy, between 0 and 1. Use -1 for the library default.",
    sizeof_addr              = "The size of an address in the file, in bytes.",
    sizeof_size              = "The size of a size in the file, in bytes.",
    ik                       = "The 1/2 rank of the indexed storage or symbol table B-tree.",
    lk                       = "The 1/2 rank of the symbol table leaf nodes.",
    strategy                 = "The file space handling strategy; one of the \\code{H5F_FSPACE_STRATEGY_*} values in \\code{\\link{h5const}}.",
    threshold                = "The smallest free-space section to track.",
    max_compact              = "The maximum number of links to store compactly in a group.",
    min_dense                = "The minimum number of links before a group switches to dense storage.",
    crt_order_flags          = "Flags governing whether link creation order is tracked and indexed.",
    nlinks                   = "The maximum number of soft or external links to traverse.",
    elink_prefix             = "The prefix to prepend to external link file names.",
    elink_acc_flags          = "The file access flags to use when opening external link targets.",
    create                   = "Logical; should missing intermediate groups be created.",
    copy_options             = "Flags governing how the object is copied.",
    left                     = "The B-tree split ratio for the left-most node.",
    middle                   = "The B-tree split ratio for interior nodes.",
    right                    = "The B-tree split ratio for the right-most node.",

    ## --- reading and writing ---
    buffer                   = "The raw buffer to read into or write from.",
    duplicate_buffer         = "Logical; should the buffer be copied before it is returned.",
    flags                    = "Flags governing the conversion from HDF5 to R. See the \\code{H5TOR_*} values in \\code{\\link{h5const}}.",
    scope                    = "The scope of the flush; one of the \\code{H5F_SCOPE_*} values in \\code{\\link{h5const}}.",
    close_self               = "Logical; should the object itself be closed as well.",
    check                    = "Logical; should the arguments be checked for validity.",
    envir                    = "The environment in which to evaluate the selection arguments.",
    drop                     = "Logical; should dimensions of size 1 be dropped.",
    args                     = "The selection for each dimension, given as a list.",
    value                    = "The value to assign.",
    flush                    = "Logical; should the file be flushed after the write.",
    exact                    = "Logical; does the subscript have to match exactly.",

    ## --- remaining ---
    obj                      = "The HDF5 object to use.",
    op                       = "The selection operator to apply; one of the \\code{H5S_SELECT_*} values in \\code{\\link{h5const}}.",
    offset                   = "The offset to apply; see the corresponding HDF5 function for how it is interpreted.",
    type                     = "The type to use. For a dataspace one of \\code{\"simple\"}, \\code{\"scalar\"} or \\code{\"null\"}; otherwise an object of class \\code{\\link{H5T}}.",
    filename                 = "The name of the file.",
    maxdims                  = "The maximum dimensions of the dataspace; use \\code{Inf} for unlimited."
))


## Build the roxygen block for one R6 method. Errors rather than emitting an
## incomplete block, so a missing description fails documentation loudly.
r6_doc <- function(class, method) {
    gen <- get(class, envir=asNamespace("hdf5r"))
    fn <- gen$public_methods[[method]]
    if(is.null(fn)) {
        fn <- gen$active[[method]]
    }
    if(!is.function(fn)) {
        stop("r6_doc: can't find method ", class, "$", method)
    }

    parsed <- r6_parse_docstrings(r6_docstrings(fn))

    out <- paste0("@R6method ", class, "$", method)
    if(length(parsed$description)) {
        out <- c(out, paste0("@description ", paste(parsed$description, collapse=" ")))
    }
    else {
        stop("r6_doc: no description for ", class, "$", method)
    }

    for(arg in names(formals(fn))) {
        txt <- parsed$params[[arg]]
        if((is.null(txt) || !nzchar(txt)) && identical(arg, "...")) {
            txt <- "Further arguments; currently ignored."
        }
        if((is.null(txt) || !nzchar(txt)) && arg %in% names(.r6_param_glossary)) {
            txt <- .r6_param_glossary[[arg]]
        }
        if(is.null(txt) || is.na(txt) || !nzchar(txt)) {
            stop("r6_doc: no description for argument '", arg, "' of ", class, "$", method,
                 ". Add an '@param' docstring to the method or an entry to .r6_param_glossary.")
        }
        out <- c(out, paste0("@param ", arg, " ", txt))
    }

    if(length(parsed$returns) && nzchar(parsed$returns)) {
        out <- c(out, paste0("@return ", parsed$returns))
    }
    out
}

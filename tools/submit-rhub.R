#!/usr/bin/env Rscript

usage <- function(status = 0) {
    cat(
        "Usage: Rscript tools/submit-rhub.R [PACKAGE_TARBALL]\n",
        "\n",
        "Submit an R package tarball to the R-hub Consortium runners.\n",
        "The default tarball is builds/<Package>_<Version>.tar.gz.\n",
        "Set RHUB_PLATFORMS to a comma-separated list of R-hub platforms\n",
        "and RHUB_EMAIL when the maintainer email is not inferred.\n",
        file = if (status == 0) stdout() else stderr()
    )
    quit(save = "no", status = status)
}

args <- commandArgs(trailingOnly = TRUE)
if (any(args %in% c("-h", "--help"))) {
    usage()
}
if (length(args) > 1L) {
    usage(1)
}

if (!requireNamespace("rhub", quietly = TRUE)) {
    stop(
        "The 'rhub' package is required. Install it with install.packages('rhub').",
        call. = FALSE
    )
}

package_tarball <- if (length(args) == 1L) {
    args[[1L]]
} else {
    description <- file.path("DESCRIPTION")
    if (!file.exists(description)) {
        stop(
            "No tarball was supplied and DESCRIPTION was not found in the current directory.",
            call. = FALSE
        )
    }
    metadata <- read.dcf(description, fields = c("Package", "Version"))
    file.path("builds", sprintf("%s_%s.tar.gz", metadata[1L, "Package"], metadata[1L, "Version"]))
}

if (!file.exists(package_tarball)) {
    stop(sprintf("Package tarball does not exist: %s", package_tarball), call. = FALSE)
}

platforms <- Sys.getenv("RHUB_PLATFORMS", unset = "ubuntu-release")
platforms <- trimws(strsplit(platforms, ",", fixed = TRUE)[[1L]])
platforms <- platforms[nzchar(platforms)]
if (!length(platforms)) {
    stop("RHUB_PLATFORMS must contain at least one platform.", call. = FALSE)
}

email <- Sys.getenv("RHUB_EMAIL", unset = "")
email <- if (nzchar(email)) email else NULL

submission <- rhub::rc_submit(
    path = package_tarball,
    platforms = platforms,
    email = email,
    confirmation = TRUE
)

if (!is.null(submission$actions_url)) {
    cat("R-hub checks: ", submission$actions_url, "\n", sep = "")
}

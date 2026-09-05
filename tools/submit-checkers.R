#!/usr/bin/env Rscript

usage <- function(status = 0) {
    cat(
        "Usage: Rscript tools/submit-checkers.R TARGET [PACKAGE_TARBALL]\n",
        "\n",
        "TARGET is one of: linux, macos, windows, all.\n",
        "The default tarball is builds/<Package>_<Version>.tar.gz.\n",
        "\n",
        "Environment variables:\n",
        "  RHUB_PLATFORMS         Comma-separated R-hub platforms\n",
        "  RHUB_EMAIL             Email for a locally stored R-hub token\n",
        "  MAC_R_FLAVOR           Mac Builder R flavor (default: r-devel)\n",
        "  MAC_DEPFILES           Optional comma-separated dependency files\n",
        "  WINBUILDER_VERSIONS    Comma-separated Win-builder versions\n",
        "                         (default: R-release,R-devel,R-oldrelease)\n",
        file = if (status == 0) stdout() else stderr()
    )
    quit(save = "no", status = status)
}

args <- commandArgs(trailingOnly = TRUE)
if (any(args %in% c("-h", "--help"))) {
    usage()
}
if (length(args) < 1L || length(args) > 2L) {
    usage(1)
}

target <- tolower(args[[1L]])
target <- switch(
    target,
    win = "windows",
    windows = "windows",
    mac = "macos",
    macos = "macos",
    linux = "linux",
    all = "all",
    stop(sprintf("Unknown target: %s", args[[1L]]), call. = FALSE)
)

if (!requireNamespace("curl", quietly = TRUE) && target != "linux") {
    stop(
        "The 'curl' package is required. Install it with install.packages('curl').",
        call. = FALSE
    )
}
if (!requireNamespace("rhub", quietly = TRUE) && target %in% c("linux", "all")) {
    stop(
        "The 'rhub' package is required for Linux submissions. Install it with install.packages('rhub').",
        call. = FALSE
    )
}

package_tarball <- if (length(args) == 2L) {
    args[[2L]]
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

split_env <- function(name, default = "") {
    value <- Sys.getenv(name, unset = "")
    if (!nzchar(value)) {
        value <- default
    }
    value <- trimws(strsplit(value, ",", fixed = TRUE)[[1L]])
    value[nzchar(value)]
}

check_http_response <- function(response, service) {
    if (response$status_code < 200L || response$status_code >= 300L) {
        body <- rawToChar(response$content)
        stop(
            sprintf("%s returned HTTP status %s: %s", service, response$status_code, body),
            call. = FALSE
        )
    }
}

submit_linux <- function() {
    platforms <- split_env("RHUB_PLATFORMS", "ubuntu-release")
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
}

submit_macos <- function() {
    mac_flavor <- Sys.getenv("MAC_R_FLAVOR", unset = "")
    if (!nzchar(mac_flavor)) {
        mac_flavor <- "r-devel"
    }
    if (!identical(mac_flavor, "r-devel")) {
        stop("Mac Builder currently accepts only MAC_R_FLAVOR=r-devel.", call. = FALSE)
    }

    dependency_files <- split_env("MAC_DEPFILES")
    missing <- dependency_files[!file.exists(dependency_files)]
    if (length(missing)) {
        stop(
            sprintf("Mac Builder dependency file does not exist: %s", missing[[1L]]),
            call. = FALSE
        )
    }

    form <- list(
        pkgfile = curl::form_file(package_tarball),
        rflavor = mac_flavor
    )
    if (length(dependency_files)) {
        form <- c(
            form,
            setNames(
                lapply(dependency_files, curl::form_file),
                rep("depfiles", length(dependency_files))
            )
        )
    }

    handle <- curl::new_handle()
    curl::handle_setform(handle, .list = form)
    response <- curl::curl_fetch_memory(
        "https://mac.r-project.org/macbuilder/v1/submit",
        handle = handle
    )
    check_http_response(response, "Mac Builder")
    cat("Mac Builder response:\n", rawToChar(response$content), "\n", sep = "")
}

submit_windows <- function() {
    versions <- split_env(
        "WINBUILDER_VERSIONS",
        "R-release,R-devel,R-oldrelease"
    )
    allowed <- c("R-release", "R-devel", "R-oldrelease")
    invalid <- versions[!versions %in% allowed]
    if (length(invalid)) {
        stop(
            sprintf("Unknown Win-builder version: %s", invalid[[1L]]),
            call. = FALSE
        )
    }

    for (version in versions) {
        url <- sprintf(
            "ftp://win-builder.r-project.org/%s/%s",
            version,
            basename(package_tarball)
        )
        cat("Uploading to Win-builder ", version, "...\n", sep = "")
        curl::curl_upload(
            package_tarball,
            url,
            verbose = TRUE,
            username = "anonymous",
            password = ""
        )
    }
    cat("Win-builder results will be sent to the DESCRIPTION maintainer email.\n")
}

if (target %in% c("linux", "all")) {
    submit_linux()
}
if (target %in% c("macos", "all")) {
    submit_macos()
}
if (target %in% c("windows", "all")) {
    submit_windows()
}

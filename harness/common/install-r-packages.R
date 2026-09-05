# Install and verify the R packages needed by `R CMD check`.
packages <- c(
    "devtools",
    "roxygen2",
    "R6",
    "bit64",
    "testthat",
    "knitr",
    "rmarkdown",
    "nycflights13",
    "reshape2",
    "formatR"
)

args <- commandArgs(trailingOnly = TRUE)
check_only <- identical(args, "--check")
library_path <- Sys.getenv("R_LIBS_USER", unset = .libPaths()[1L])
repository <- Sys.getenv("CRAN_REPO", unset = "https://cloud.r-project.org")

dir.create(library_path, recursive = TRUE, showWarnings = FALSE)
.libPaths(c(library_path, .libPaths()))
options(repos = c(CRAN = repository))
if (grepl("/__linux__/", repository, fixed = TRUE)) {
    options(HTTPUserAgent = sprintf(
        "R/%s R (%s)",
        getRversion(),
        paste(getRversion(), R.version$platform, R.version$arch, R.version$os)
    ))
}

missing_packages <- function() {
    installed <- rownames(installed.packages(lib.loc = library_path))
    setdiff(packages, installed)
}

missing <- missing_packages()
if (length(missing) && !check_only) {
    cores <- parallel::detectCores()
    if (is.na(cores)) cores <- 1L
    install.packages(missing, lib = library_path, Ncpus = max(1L, cores))
    missing <- missing_packages()
}

if (length(missing)) {
    stop("missing R packages: ", paste(missing, collapse = ", "))
}

message("R check dependencies are available in ", library_path)

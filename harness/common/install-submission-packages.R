# Install the R packages used by the local builder submission scripts.
packages <- c("rhub", "curl")
library_path <- Sys.getenv("R_LIBS_USER", unset = .libPaths()[1L])
repository <- Sys.getenv("CRAN_REPO", unset = "https://cloud.r-project.org")

dir.create(library_path, recursive = TRUE, showWarnings = FALSE)
.libPaths(c(library_path, .libPaths()))
options(repos = c(CRAN = repository))

installed <- rownames(installed.packages(lib.loc = library_path))
missing <- setdiff(packages, installed)
if (length(missing)) {
    cores <- parallel::detectCores()
    if (is.na(cores)) cores <- 1L
    install.packages(missing, lib = library_path, Ncpus = max(1L, cores))
}

installed <- rownames(installed.packages(lib.loc = library_path))
missing <- setdiff(packages, installed)
if (length(missing)) {
    stop("missing submission packages: ", paste(missing, collapse = ", "))
}

message("Submission packages are available in ", library_path)

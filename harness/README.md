# hdf5r test harness

This directory tests hdf5r against multiple R and HDF5 versions and build
systems.

- Linux uses Docker.
- macOS uses native source builds under `harness/installs/`.
- Builds and checks are always separate.
- Every check runs `R CMD check --as-cran`.
- An ERROR fails the combination; WARNINGs are allowed by default and NOTEs are
  allowed. Set `FAIL_ON_WARNINGS=true` to fail on WARNINGs as well.

Run `make help` to see the command summary. On macOS, use `gmake` in place of
`make` throughout this document.

## Versions

The matrix is defined once, near the top of `Makefile`.

- R: 4.3.3, 4.4.3, 4.5.1, 4.6.1, devel
- HDF5 profiles: 1.8.23/autotools, 1.10.11/autotools,
  1.12.3/autotools, 1.14.6/autotools, 1.14.6/CMake, 2.0.0/CMake,
  2.1.1/CMake, 2.2.0/CMake

HDF5 2.x is always built with CMake. The additional `devel:1.14.6:cmake`
combination reproduces the CMake-wrapper case from issue #246.

The build scripts also accept versions outside this list.
R-devel source builds are refreshed at most once per day.

## Linux

Requirements: Docker with BuildKit support.

Build one combination:

```sh
cd harness
make build-linux R_VERSION=4.6.1 HDF5_VERSION=2.2.0
```

This builds two cached images in order, using `debian:testing`:

1. `hhoeflin/hdf5r-base-r:r4.6.1`
2. `hhoeflin/hdf5r-deps:r4.6.1-hdf5v2.2.0`

Run its check separately:

```sh
make check-linux R_VERSION=4.6.1 HDF5_VERSION=2.2.0
```

Run the CMake HDF5 1.14.6 regression combination:

```sh
make build-linux R_VERSION=devel HDF5_VERSION=1.14.6 HDF5_BUILD_SYSTEM=cmake
make check-linux R_VERSION=devel HDF5_VERSION=1.14.6 HDF5_BUILD_SYSTEM=cmake
```

The check does not build missing images. It prints the required build command
and exits non-zero instead.

To use Debian's system HDF5 package, which provides the serial library names
used by the R checker:

```sh
make build-linux R_VERSION=4.6.1 HDF5_VERSION=system
make check-linux R_VERSION=4.6.1 HDF5_VERSION=system
```

Optional variables:

- `REGISTRY=example` changes the Docker image namespace.
- `PLATFORM=linux/amd64` selects a Docker platform explicitly.
- `INSTALL_DOCS_DEPS=false` omits documentation tools. Do not use this for a
  full `R CMD check --as-cran`.

## macOS

Requirements:

- Xcode Command Line Tools
- Homebrew

Run the one-time setup target. It installs GNU Make (`gmake`), the autotools
and shell-checking tools (`autoconf`, `automake`, `checkbashisms`), `pandoc`,
`qpdf`, the text-shaping libraries (`pkgconf`, FreeType, HarfBuzz, and
FriBidi), BasicTeX (`pdflatex`), and a Java runtime (Temurin JDK). The TeX and
Java installers ask for your admin password:

```sh
gmake setup-macos
```

Afterwards, open a new shell so the installed tools are on `PATH`. The check
scripts add `/Library/TeX/texbin` themselves; no manual `PATH` changes are
needed.

If a check later reports a missing LaTeX package, add it with
`sudo tlmgr install <package>`.

Build one combination:

```sh
cd harness
make build-macos R_VERSION=4.6.1 HDF5_VERSION=2.2.0
```

The build installs:

- R under `harness/installs/R/<version>`
- HDF5 under `harness/installs/hdf5/<version>`
- R check dependencies under `harness/installs/R-libs/<R-version>`
- Submission dependencies under `harness/installs/R-libs-submission/devel`

Homebrew build dependencies are installed when missing. Run the check
separately:

```sh
make check-macos R_VERSION=4.6.1 HDF5_VERSION=2.2.0
```

The CMake HDF5 1.14.6 regression combination is selected with
`HDF5_BUILD_SYSTEM=cmake` in the same way as the Linux command above.

The check uses only the selected R, HDF5, and harness-owned R library.

Warnings are allowed by default. To make warnings fail the check:

```sh
make check-macos R_VERSION=devel HDF5_VERSION=1.14.6 FAIL_ON_WARNINGS=true
```

To run the repository's top-level CRAN build and check with the selected native
installations, use the `HARNESS_*` variables from the repository root:

```sh
gmake check-cran HARNESS_R_VERSION=4.6.1 HARNESS_HDF5_VERSION=2.2.0
```

This uses the harness R, HDF5, and R library for every top-level R command.
`R CMD build` is run without `--no-build-vignettes`, so the vignettes are built
before `R CMD check --as-cran` runs. Build the selected installations first with
`gmake build-macos R_VERSION=4.6.1 HDF5_VERSION=2.2.0` from `harness/`.

## Matrices

Build before checking:

```sh
make build-matrix-linux
make check-matrix-linux

make build-matrix-macos
make check-matrix-macos
```

`build-matrix-macos` builds each R and HDF5 version once. `FULL=1` changes
only the check matrix, because both matrix sizes use the same native installs.

The default matrix is an explicit list of 13 combinations: every HDF5 profile
on R 4.6.1, plus HDF5 2.2.0 on every R version, Debian's system HDF5 on R
4.6.1, and the CMake HDF5 1.14.6 regression combination on R-devel.

Use `FULL=1` for all 36 explicit combinations:

```sh
make build-matrix-linux FULL=1
make check-matrix-linux FULL=1
```

## Results

Results are written under `harness/logs/`:

- `build-*.log` contains build output.
- `check-<combination>/check.log` contains package build and check output.
- `check-<combination>/preflight.log` contains platform preflight output;
  `dependencies.log` contains macOS R dependency installation output.
- `check-<combination>/status` contains `RUNNING`, `PASS`, or `FAIL`.
- `check-<combination>/runner.log` contains platform runner output and startup
  failures.
- `check-<combination>/hdf5r/hdf5r.Rcheck/` contains the complete R check artifacts,
  including `00check.log` and `00install.out`.

Each check replaces its own `check-<combination>/` directory at the start of a
run. This keeps all artifacts for one combination together while preventing a
rerun from using stale files.

Show results with:

```sh
make summary
make summary PLATFORM=linux
make summary PLATFORM=macos
```

Starting a platform matrix clears old check directories for that platform, so
its summary cannot report stale results.

## Layout

```text
Makefile                    human-facing build, check, and matrix commands
common/                     shared HDF5 builder, R dependencies, check runner
docker/                     Linux Dockerfiles and parameterized build scripts
macos/                      native setup, build, and check scripts
installs/                   ignored native R, HDF5, and R package installs
logs/                       ignored build logs and per-check artifacts
```

`installs/` and `logs/` are gitignored: they exist on disk but never appear in
`git status` or in commits.

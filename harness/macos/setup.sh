#!/usr/bin/env bash
# One-time macOS setup for the hdf5r test harness.
#
# Installs everything needed to build R/HDF5 and run `R CMD check --as-cran`:
#   formulas: make (gmake), autoconf, automake, checkbashisms, pandoc, qpdf,
#             pkgconf, freetype, harfbuzz, fribidi
#   casks:    basictex (pdflatex), temurin (Java)
#
# The TeX and Java installers require your admin password (Homebrew will
# prompt for sudo). Run this interactively, once.
set -euo pipefail

log() { echo "setup.sh: $*"; }
die() { echo "setup.sh: ERROR: $*" >&2; exit 1; }

command -v brew >/dev/null || die "Homebrew required (see https://brew.sh)"

for formula in make autoconf automake checkbashisms pandoc qpdf pkgconf freetype harfbuzz fribidi; do
    brew list --formula "${formula}" >/dev/null 2>&1 || brew install "${formula}"
done

brew list --cask basictex >/dev/null 2>&1 || brew install --cask basictex
brew list --cask temurin  >/dev/null 2>&1 || brew install --cask temurin

# BasicTeX is minimal; add the LaTeX pieces `R CMD check` needs for the
# package PDF manual.
export PATH="/Library/TeX/texbin:${PATH}"
command -v pdflatex >/dev/null || die "pdflatex still missing after basictex install"
sudo tlmgr update --self
sudo tlmgr install inconsolata upquote

log "verifying prerequisites"
for command in gmake autoreconf aclocal checkbashisms pandoc pdflatex qpdf; do
    command -v "${command}" >/dev/null \
        || die "${command} still not on PATH; open a new shell and retry"
done
java -version >/dev/null 2>&1 \
    || die "java still not working; open a new shell and retry"

log "setup complete"

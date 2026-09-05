.ONESHELL:
SHELL:=/bin/bash
CURRENT_DIR := $(shell pwd)

R_BIN := R
RSCRIPT_BIN := Rscript

# Set both variables to use native macOS installations created by the harness:
#
#   gmake -C harness build-macos R_VERSION=4.6.1 HDF5_VERSION=2.2.0
#   gmake check-cran HARNESS_R_VERSION=4.6.1 HARNESS_HDF5_VERSION=2.2.0
#
# R CMD build below intentionally does not pass --no-build-vignettes.
HARNESS_REQUESTED := $(strip $(HARNESS_R_VERSION)$(HARNESS_HDF5_VERSION))
ifneq ($(HARNESS_REQUESTED),)
ifeq ($(strip $(HARNESS_R_VERSION)),)
$(error HARNESS_R_VERSION and HARNESS_HDF5_VERSION must be set together)
endif
ifeq ($(strip $(HARNESS_HDF5_VERSION)),)
$(error HARNESS_R_VERSION and HARNESS_HDF5_VERSION must be set together)
endif

HARNESS_DIR := $(CURRENT_DIR)/harness
HARNESS_R_PREFIX := $(HARNESS_DIR)/installs/R/$(HARNESS_R_VERSION)
HARNESS_R_LIBRARY := $(HARNESS_DIR)/installs/R-libs/$(HARNESS_R_VERSION)
HARNESS_HDF5_PREFIX := $(HARNESS_DIR)/installs/hdf5/$(HARNESS_HDF5_VERSION)
HARNESS_H5CC := $(HARNESS_HDF5_PREFIX)/bin/h5cc
HARNESS_CPPFLAGS := $(CPPFLAGS)
HARNESS_LDFLAGS := $(LDFLAGS)
HARNESS_CPATH := $(CPATH)
HARNESS_LIBRARY_PATH := $(LIBRARY_PATH)
HARNESS_DYLD_LIBRARY_PATH := $(DYLD_LIBRARY_PATH)
HARNESS_PKG_CONFIG_PATH := $(PKG_CONFIG_PATH)

R_BIN := $(HARNESS_R_PREFIX)/bin/R
RSCRIPT_BIN := $(HARNESS_R_PREFIX)/bin/Rscript
export PATH := $(HARNESS_R_PREFIX)/bin:$(HARNESS_HDF5_PREFIX)/bin:$(PATH)
export R_LIBS_USER := $(HARNESS_R_LIBRARY)
export R_ENVIRON_USER := /dev/null
export R_PROFILE_USER := /dev/null
unexport R_LIBS R_LIBS_SITE
export CPPFLAGS := -I$(HARNESS_HDF5_PREFIX)/include $(HARNESS_CPPFLAGS)
export LDFLAGS := -L$(HARNESS_HDF5_PREFIX)/lib $(HARNESS_LDFLAGS)
export CPATH := $(HARNESS_HDF5_PREFIX)/include$(if $(HARNESS_CPATH),:$(HARNESS_CPATH))
export LIBRARY_PATH := $(HARNESS_HDF5_PREFIX)/lib$(if $(HARNESS_LIBRARY_PATH),:$(HARNESS_LIBRARY_PATH))
export DYLD_LIBRARY_PATH := $(HARNESS_HDF5_PREFIX)/lib$(if $(HARNESS_DYLD_LIBRARY_PATH),:$(HARNESS_DYLD_LIBRARY_PATH))
export PKG_CONFIG_PATH := $(HARNESS_HDF5_PREFIX)/lib/pkgconfig$(if $(HARNESS_PKG_CONFIG_PATH),:$(HARNESS_PKG_CONFIG_PATH))
export HDF5_ROOT := $(HARNESS_HDF5_PREFIX)
export HDF5_VERSION := $(HARNESS_HDF5_VERSION)
export H5CC := $(HARNESS_H5CC)
endif

R := $(R_BIN) --slave --vanilla -e
Rscript := $(RSCRIPT_BIN) -e

PKG_VERSION := $(shell grep -i ^version DESCRIPTION | cut -d : -d \  -f 2)
PKG_NAME := $(shell grep -i ^package DESCRIPTION | cut -d : -d \  -f 2)

#DATA_FILES := $(wildcard data/*.rda)
R_FILES := $(wildcard R/*.R)
TEST_FILES := $(wildcard tests/*.R) $(wildcard tests/testthat/*.R)
ALL_SRC_FILES := $(wildcard src/*.c) $(wildcard src/*.h) src/Makevars.in
RMD_FILES := README.Rmd
MD_FILES := $(RMD_FILES:.Rmd=.md)
SRC_FILES := $(filter-out src/RcppExports.cpp, $(ALL_SRC_FILES))
HEADER_FILES := $(wildcard src/*.h)
ROXYGENFILES := $(wildcard man/*.Rd) NAMESPACE
PKG_FILES := DESCRIPTION $(ROXYGENFILES) $(R_FILES) $(SRC_FILES) \
	$(HEADER_FILES) $(TEST_FILES) configure
OBJECTS := $(wildcard src/*.o) $(wildcard src/*.o-*) $(wildcard src/*.dll) $(wildcard src/*.so) $(wildcard src/*.rds)
CHECKPATH := $(PKG_NAME).Rcheck
CHECKLOG := `cat $(CHECKPATH)/00check.log`
BUILD_OUTPUT := builds/$(PKG_NAME)_$(PKG_VERSION).tar.gz
SRC_FILES_COPIED := $(wildcard src/Wrapper_auto*) src/HelperStructs.h \
					src/const_export.c src/const_export.h src/export_auto.h \
					src/datatype_export.c src/datatype_export.h


.PHONY: all build check manual install clean compileAttributes roxygen \
	build-cran check-cran doc harness-preflight

.PHONY: harness-preflight
harness-preflight:
ifneq ($(HARNESS_REQUESTED),)
	@case "$(HARNESS_R_VERSION)" in \
	    ''|*[!A-Za-z0-9_.-]*) echo "ERROR: HARNESS_R_VERSION contains unsafe characters" >&2; exit 2;; \
	esac
	@case "$(HARNESS_HDF5_VERSION)" in \
	    ''|*[!A-Za-z0-9_.-]*) echo "ERROR: HARNESS_HDF5_VERSION contains unsafe characters" >&2; exit 2;; \
	esac
	@test -x "$(HARNESS_R_PREFIX)/bin/R" || { \
	    echo "ERROR: harness R $(HARNESS_R_VERSION) is missing" >&2; \
	    echo "Build it with: gmake -C harness build-macos R_VERSION=$(HARNESS_R_VERSION) HDF5_VERSION=$(HARNESS_HDF5_VERSION)" >&2; \
	    exit 2; \
	}
	@test -x "$(HARNESS_R_PREFIX)/bin/Rscript" || { \
	    echo "ERROR: harness Rscript $(HARNESS_R_VERSION) is missing" >&2; \
	    echo "Build it with: gmake -C harness build-macos R_VERSION=$(HARNESS_R_VERSION) HDF5_VERSION=$(HARNESS_HDF5_VERSION)" >&2; \
	    exit 2; \
	}
	@test -x "$(HARNESS_H5CC)" || { \
	    echo "ERROR: harness HDF5 $(HARNESS_HDF5_VERSION) is missing" >&2; \
	    echo "Build it with: gmake -C harness build-macos R_VERSION=$(HARNESS_R_VERSION) HDF5_VERSION=$(HARNESS_HDF5_VERSION)" >&2; \
	    exit 2; \
	}
	@test -f "$(HARNESS_HDF5_PREFIX)/.hdf5r-harness-complete" || { \
	    echo "ERROR: harness HDF5 $(HARNESS_HDF5_VERSION) install is incomplete" >&2; \
	    echo "Build it with: gmake -C harness build-macos R_VERSION=$(HARNESS_R_VERSION) HDF5_VERSION=$(HARNESS_HDF5_VERSION)" >&2; \
	    exit 2; \
	}
else
	@:
endif

all:
	install

build: harness-preflight $(BUILD_OUTPUT)

$(BUILD_OUTPUT): $(PKG_FILES)
	@$(MAKE) roxygen
	mkdir -p builds
	cd builds
	$(R_BIN) CMD build --resave-data ..

build-cran: harness-preflight
	@$(MAKE) clean
	@$(MAKE) roxygen
	@$(MAKE) build

roxygen: harness-preflight $(ROXYGENFILES)

configure: configure.ac
	autoconf

# uses grouped targets https://www.gnu.org/software/make/manual/html_node/Multiple-Targets.html
$(ROXYGENFILES) &: $(R_FILES)
	$(Rscript) 'devtools::load_all(".", reset=TRUE, recompile = FALSE, export_all=FALSE)';
	$(Rscript) 'devtools::document(".")';
	touch $(ROXYGENFILES)

sitedoc: harness-preflight
	$(Rscript) 'pkgdown::build_site()';

check: harness-preflight $(BUILD_OUTPUT)
	@rm -rf $(CHECKPATH)
	$(R_BIN) CMD check --no-clean $(BUILD_OUTPUT)

check-valgrind: harness-preflight $(BUILD_OUTPUT)
	@rm -rf $(CHECKPATH)
	$(R_BIN) CMD check --no-clean --use-valgrind $(BUILD_OUTPUT)

check-cran: harness-preflight
	@$(MAKE) build-cran
	@rm -rf $(CHECKPATH)
	$(R_BIN) CMD check --no-clean --as-cran $(BUILD_OUTPUT)

check-asan-gcc: $(BUILD_OUTPUT)
	@boot2docker up
	$(shell boot2docker shellinit)
	@docker run -v "$(CURRENT_DIR):/mnt" mannau/r-devel-san /bin/bash -c \
		"cd /mnt; apt-get update; apt-get clean; apt-get install -y libhdf5-dev; \
		R -e \"install.packages(c('Rcpp', 'testthat', 'roxygen2', 'highlight', 'zoo', 'microbenchmark'))\"; \
		R CMD check $(BUILD_OUTPUT); \
		cat /mnt/h5.Rcheck/00install.out"

00check.log: check
	@mv $(CHECKPATH)\\00check.log .
	@rm -rf $(CHECKPATH)

manual: harness-preflight $(PKG_NAME)-manual.pdf

$(PKG_NAME)-manual.pdf: $(ROXYGENFILES)
	$(R_BIN) CMD Rd2pdf --no-preview -o $(PKG_NAME)-manual.pdf .

install: harness-preflight $(BUILD_OUTPUT)
	$(R_BIN) CMD INSTALL --byte-compile $(BUILD_OUTPUT)

clean:
	@rm -f $(OBJECTS)
	@rm -f ${SRC_FILES_COPIED}
	@rm -rf $(wildcard *.Rcheck)
	@rm -rf $(wildcard *.cache)
	@rm -f $(wildcard *.tar.gz)
	@rm -f $(wildcard *.pdf)
	@echo '*** PACKAGE CLEANUP COMPLETE ***'

doc: harness-preflight $(MD_FILES)
	$(R_BIN) -e 'staticdocs::build_site(examples = TRUE)'
	$(Rscript) 'file.copy(list.files("inst/staticdocs", pattern = "*.css", full.names = TRUE), "inst/web/css")'
	$(Rscript) 'file.copy(list.files("inst/staticdocs", pattern = "*.js", full.names = TRUE), "inst/web/js")'

$(MD_FILES): $(RMD_FILES)
	echo "library(knitr); library(h5); sapply(list.files(pattern = '*.Rmd'), knit);if(file.exists('test.h5')) file.remove('test.h5')" | $(R_BIN) --slave --vanilla

testthat: harness-preflight
	$(Rscript) 'testthat::test_local(path = ".", reporter = NULL, load_package = "source")'

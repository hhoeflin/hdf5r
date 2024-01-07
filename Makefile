.ONESHELL:
SHELL:=/bin/bash

R_REVISION?=85786
HDF5_VERSION?=System
DOCKER_CRAN_CHECK_ARG=''
# DOCKER_CRAN_CHECK_ARG='--as-cran'

R := R --slave --vanilla -e
Rscript := Rscript -e

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
CURRENT_DIR := $(shell pwd)
BUILD_OUTPUT := builds/$(PKG_NAME)_$(PKG_VERSION).tar.gz
SRC_FILES_COPIED := $(wildcard src/Wrapper_auto*) src/HelperStructs.h \
					src/const_export.c src/const_export.h src/export_auto.h \
					src/datatype_export.c src/datatype_export.h


.PHONY: all build check manual install clean compileAttributes roxygen \
	build-cran check-cran doc

all:
	install

build: $(BUILD_OUTPUT)

$(BUILD_OUTPUT): $(PKG_FILES)
	@make roxygen
	mkdir -p builds
	cd builds
	R CMD build --resave-data ..

build-cran:
	@make clean
	@make roxygen
	@make build

roxygen: $(ROXYGENFILES)

configure: configure.ac
	autoconf

# uses grouped targets https://www.gnu.org/software/make/manual/html_node/Multiple-Targets.html
$(ROXYGENFILES) &: $(R_FILES)
	$(Rscript) 'devtools::load_all(".", reset=TRUE, recompile = FALSE, export_all=FALSE)';
	$(Rscript) 'devtools::document(".")';
	touch $(ROXYGENFILES)

sitedoc:
	$(Rscript) 'pkgdown::build_site()';

check: $(BUILD_OUTPUT)
	@rm -rf $(CHECKPATH)
	R CMD check --no-clean $(BUILD_OUTPUT)

check-docker: $(BUILD_OUTPUT)
	if [[ "${HDF5_VERSION}" = "System" ]]; then
		echo HDF is System
		$(MAKE) -C docker build-system R_REVISION=${R_REVISION} HDF5_VERSION=${HDF5_VERSION}
	else
		$(MAKE) -C docker build-custom R_REVISION=${R_REVISION} HDF5_VERSION=${HDF5_VERSION}
	fi
	export DOCKER_BUILDKIT=1
	mkdir -p logs
	SOURCE_IMAGE=hhoeflin/hdf5-debian-gcc-devel:r${R_REVISION}-v${HDF5_VERSION}
	TARGET_IMAGE=hhoeflin/hdf5r-install-debian-gcc-devel:r${R_REVISION}-v${HDF5_VERSION}
	LOG_FILE=logs/hdf5r-install-r${R_REVISION}-v${HDF5_VERSION}
	RCHECK_DIR=$${LOG_FILE}.Rcheck
	BUILD_OUTPUT=${BUILD_OUTPUT}
	rm -rf hdf5r.Rcheck
	rm -rf $${RCHECK_DIR}
	docker build -f docker/Dockerfile_check \
		-t $${TARGET_IMAGE}\
		--build-arg DEB_HDF5_IMG=$${SOURCE_IMAGE} \
		--build-arg BUILD_OUTPUT=$${BUILD_OUTPUT} \
		--build-arg CRAN_CHECK_ARG=${DOCKER_CRAN_CHECK_ARG} \
		. 2>&1 \
		| tee $${LOG_FILE}
	# get the artifacts
	docker rm tc || true
	docker cp $$(docker create --name tc $${TARGET_IMAGE}):/home/docker/hdf5r/hdf5r.Rcheck\
		$${RCHECK_DIR} && docker rm tc

check-valgrind: $(BUILD_OUTPUT)
	@rm -rf $(CHECKPATH)
	R CMD check --no-clean --use-valgrind $(BUILD_OUTPUT)

check-cran:
	@make build-cran
	@rm -rf $(CHECKPATH)
	R CMD check --no-clean --as-cran $(BUILD_OUTPUT)

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

manual: $(PKG_NAME)-manual.pdf

$(PKG_NAME)-manual.pdf: $(ROXYGENFILES)
	R CMD Rd2pdf --no-preview -o $(PKG_NAME)-manual.pdf .

install: $(BUILD_OUTPUT)
	R CMD INSTALL --byte-compile $(BUILD_OUTPUT)

clean:
	@rm -f $(OBJECTS)
	@rm -f ${SRC_FILES_COPIED}
	@rm -rf $(wildcard *.Rcheck)
	@rm -rf $(wildcard *.cache)
	@rm -f $(wildcard *.tar.gz)
	@rm -f $(wildcard *.pdf)
	@echo '*** PACKAGE CLEANUP COMPLETE ***'

doc: $(MD_FILES)
	R -e 'staticdocs::build_site(examples = TRUE)'
	$(Rscript) 'file.copy(list.files("inst/staticdocs", pattern = "*.css", full.names = TRUE), "inst/web/css")'
	$(Rscript) 'file.copy(list.files("inst/staticdocs", pattern = "*.js", full.names = TRUE), "inst/web/js")'

$(MD_FILES): $(RMD_FILES)
	echo "library(knitr); library(h5); sapply(list.files(pattern = '*.Rmd'), knit);if(file.exists('test.h5')) file.remove('test.h5')" | R --slave --vanilla

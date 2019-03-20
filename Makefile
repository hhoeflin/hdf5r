R := R --slave --vanilla -e

PKG_VERSION := $(shell grep -i ^version DESCRIPTION | cut -d : -d \  -f 2)
PKG_NAME := $(shell grep -i ^package DESCRIPTION | cut -d : -d \  -f 2)

#DATA_FILES := $(wildcard data/*.rda)
R_FILES := $(wildcard R/*.R)
TEST_FILES := $(wildcard tests/*.R) $(wildcard tests/testthat/*.R)
ALL_SRC_FILES := $(wildcard src/*.cpp) $(wildcard src/*.h) src/Makevars.in
RMD_FILES := README.Rmd
MD_FILES := $(RMD_FILES:.Rmd=.md)
SRC_FILES := $(filter-out src/RcppExports.cpp, $(ALL_SRC_FILES))
HEADER_FILES := $(wildcard src/*.h)
RCPPEXPORTS := src/RcppExports.cpp R/RcppExports.R
ROXYGENFILES := $(wildcard man/*.Rd) NAMESPACE 
PKG_FILES := DESCRIPTION $(ROXYGENFILES) $(R_FILES) $(SRC_FILES) \
	$(HEADER_FILES) $(TEST_FILES) $(RCPPEXPORTS)
OBJECTS := $(wildcard src/*.o) $(wildcard src/*.o-*) $(wildcard src/*.dll) $(wildcard src/*.so) $(wildcard src/*.rds)
CHECKPATH := $(PKG_NAME).Rcheck
CHECKLOG := `cat $(CHECKPATH)/00check.log`
CURRENT_DIR := $(shell pwd)

# Makevars used for CRAN release
HDF5_VERSION_USE=1_8_14
WINC=$${LIB_HDF5}/include
WLIB=$${LIB_HDF5}/lib$${R_ARCH}
HDF5R_CPPFLAGS=
DEFINE_H5FREE_MEMORY=0
HDF5R_LIBS=-L${WLIB} -lhdf5 -lhdf5_hl -lz -lm
HDF5R_CFLAGS=-I${WINC}/hdf5 -I${WINC}/hdf5_hl -I${WINC}/cmakeconf -I${HDF5_VERSION_USE} -I.
# Makevars end

.PHONY: all build check manual install clean compileAttributes roxygen\
	build-cran check-cran doc 

all: 
	install
	
build: $(PKG_NAME)_$(PKG_VERSION).tar.gz
	
$(PKG_NAME)_$(PKG_VERSION).tar.gz: $(PKG_FILES)
	@make roxygen
	R CMD build --resave-data .

build-cran:
	@make clean
	@make roxygen
	# Generate src/Makevars.win
	sed -e 's#@HDF5_VERSION_USE@#${HDF5_VERSION_USE}#g' -e 's#@HDF5R_CFLAGS@#${HDF5R_CFLAGS}#g'  \
-e  's#@HDF5R_CPPFLAGS@#${HDF5R_CPPFLAGS}#g' -e  's#@HDF5R_LIBS@#${HDF5R_LIBS}#g' \
-e  's#@DEFINE_H5FREE_MEMORY@#${DEFINE_H5FREE_MEMORY}#g' \
src/Makevars.in > src/Makevars.win
	# Swap configure.win
	@cp configure.win configure.win.temp; cat /dev/null >| configure.win
	R CMD build --resave-data .
	# Unswap configure.win
	@cp configure.win.temp configure.win; rm configure.win.temp
	# Remove src/Makevars.win
	rm src/Makevars.win

roxygen: $(R_FILES)
	$(R) 'devtools::load_all(".", reset=TRUE, recompile = FALSE, export_all=FALSE)';
	$(R) 'devtools::document(".")';

sitedoc:
	$(R) 'pkgdown::build_site()';

$(RCPPEXPORTS): compileAttributes
	
compileAttributes: $(SRC_FILES)
	$(Rscript) 'library(Rcpp); Rcpp::compileAttributes()'
	
check: $(PKG_NAME)_$(PKG_VERSION).tar.gz 
	@rm -rf $(CHECKPATH)
	R CMD check --no-clean $(PKG_NAME)_$(PKG_VERSION).tar.gz

check-valgrind: $(PKG_NAME)_$(PKG_VERSION).tar.gz 
	@rm -rf $(CHECKPATH)
	R CMD check --no-clean --use-valgrind $(PKG_NAME)_$(PKG_VERSION).tar.gz

check-cran: 
	@make build-cran
	@rm -rf $(CHECKPATH)
	R CMD check --no-clean --as-cran $(PKG_NAME)_$(PKG_VERSION).tar.gz

check-asan-gcc: $(PKG_NAME)_$(PKG_VERSION).tar.gz
	@boot2docker up
	$(shell boot2docker shellinit)
	@docker run -v "$(CURRENT_DIR):/mnt" mannau/r-devel-san /bin/bash -c \
		"cd /mnt; apt-get update; apt-get clean; apt-get install -y libhdf5-dev; \
		R -e \"install.packages(c('Rcpp', 'testthat', 'roxygen2', 'highlight', 'zoo', 'microbenchmark'))\"; \
		R CMD check $(PKG_NAME)_$(PKG_VERSION).tar.gz; \
		cat /mnt/h5.Rcheck/00install.out"

00check.log: check
	@mv $(CHECKPATH)\\00check.log .
	@rm -rf $(CHECKPATH)

manual: $(PKG_NAME)-manual.pdf

$(PKG_NAME)-manual.pdf: $(ROXYGENFILES)
	R CMD Rd2pdf --no-preview -o $(PKG_NAME)-manual.pdf .
	
install: $(PKG_NAME)_$(PKG_VERSION).tar.gz
	R CMD INSTALL --byte-compile $(PKG_NAME)_$(PKG_VERSION).tar.gz

clean:
	@rm -f $(OBJECTS)
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

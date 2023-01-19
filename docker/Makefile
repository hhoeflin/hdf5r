.ONESHELL:
SHELL:=/bin/bash

R_REVISION=83640
HDF5_VERSION?=1.10.9

BUILD_LOGS=logs/hdf5-debian-gcc-devel-r${R_REVISION}-v${HDF5_VERSION}

.PHONY: all

all: ${BUILD_LOGS}

${BUILD_LOGS}: Dockerfile_deps
	mkdir -p logs
	export DOCKER_BUILDKIT=1
	docker build -f Dockerfile_deps \
		-t hhoeflin/hdf5_debian-gcc-devel:r${R_REVISION}-v${HDF5_VERSION}\
		--build-arg HDF5_VERSION=${HDF5_VERSION} \
		--build-arg DEB_BASE_IMG=hhoeflin/base-debian-gcc-devel:r${R_REVISION} . > $@ 2>&1


.ONESHELL:
SHELL:=/bin/bash

R_REVISION?=83640
HDF5_VERSION?=1.10.9

BUILD_LOG_CUSTOM=logs/hdf5-debian-gcc-devel-r${R_REVISION}-v${HDF5_VERSION}
BUILD_LOG_SYSTEM=logs/hdf5-debian-gcc-devel-r${R_REVISION}-vSystem

.PHONY: all build

all: build-system

build-custom: Dockerfile_deps_custom_hdf5
	echo ${R_REVISION}
	$(MAKE) -C debian-gcc-devel R_REVISION=${R_REVISION}
	mkdir -p logs
	export DOCKER_BUILDKIT=1
	docker build -f Dockerfile_deps_custom_hdf5 \
		-t hhoeflin/hdf5-debian-gcc-devel:r${R_REVISION}-v${HDF5_VERSION}\
		--build-arg HDF5_VERSION=${HDF5_VERSION} \
		--build-arg DEB_BASE_IMG=hhoeflin/base-debian-gcc-devel:r${R_REVISION} . 2>&1 \
		| tee ${BUILD_LOG_CUSTOM}

build-system: Dockerfile_deps_system_hdf5
	echo ${R_REVISION}
	$(MAKE) -C debian-gcc-devel R_REVISION=${R_REVISION}
	mkdir -p logs
	export DOCKER_BUILDKIT=1
	docker build -f Dockerfile_deps_system_hdf5 \
		-t hhoeflin/hdf5-debian-gcc-devel:r${R_REVISION}-vSystem\
		--build-arg DEB_BASE_IMG=hhoeflin/base-debian-gcc-devel:r${R_REVISION} . 2>&1 \
		| tee ${BUILD_LOG_SYSTEM}


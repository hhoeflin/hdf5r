#!/usr/bin/env bash
# Build one Linux dependency image for an R/HDF5 combination.
set -euo pipefail

R_VERSION="${1:?usage: build.sh <R_VERSION> <HDF5_VERSION|system>}"
HDF5_VERSION="${2:?usage: build.sh <R_VERSION> <HDF5_VERSION|system>}"
REGISTRY="${REGISTRY:-hhoeflin}"
INSTALL_DOCS_DEPS="${INSTALL_DOCS_DEPS:-true}"
IMAGE_SUFFIX="${IMAGE_SUFFIX:-}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
HARNESS_DIR="$(cd "${SCRIPT_DIR}/../.." && pwd)"

common_args=(
    --build-arg "R_VERSION=${R_VERSION}"
    --build-arg "REGISTRY=${REGISTRY}"
    --build-arg "R_BASE_TAG=r${R_VERSION}${IMAGE_SUFFIX}"
    --build-arg "INSTALL_DOCS_DEPS=${INSTALL_DOCS_DEPS}"
)
if [ -n "${PLATFORM:-}" ]; then
    common_args+=(--platform "${PLATFORM}")
fi

case "${HDF5_VERSION}" in
    system|System)
        dockerfile="${HARNESS_DIR}/docker/Dockerfile_deps_system_hdf5"
        tag="${REGISTRY}/hdf5r-deps:r${R_VERSION}-hdf5vSystem${IMAGE_SUFFIX}"
        ;;
    *)
        dockerfile="${HARNESS_DIR}/docker/Dockerfile_deps_custom_hdf5"
        tag="${REGISTRY}/hdf5r-deps:r${R_VERSION}-hdf5v${HDF5_VERSION}${IMAGE_SUFFIX}"
        common_args+=(--build-arg "HDF5_VERSION=${HDF5_VERSION}")
        ;;
esac

DOCKER_BUILDKIT=1 docker build \
    -f "${dockerfile}" \
    "${common_args[@]}" \
    -t "${tag}" \
    "${HARNESS_DIR}"

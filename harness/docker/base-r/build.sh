#!/usr/bin/env bash
# Build one Linux image containing R compiled from source.
set -euo pipefail

R_VERSION="${1:?usage: build.sh <R_VERSION>}"
REGISTRY="${REGISTRY:-hhoeflin}"
BASE_IMAGE="${BASE_IMAGE:-debian:testing}"
IMAGE_SUFFIX="${IMAGE_SUFFIX:-}"

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
HARNESS_DIR="$(cd "${SCRIPT_DIR}/../.." && pwd)"

args=(
    build
    -f "${HARNESS_DIR}/docker/Dockerfile_r_base"
    --build-arg "R_VERSION=${R_VERSION}"
    --build-arg "BASE_IMAGE=${BASE_IMAGE}"
    -t "${REGISTRY}/hdf5r-base-r:r${R_VERSION}${IMAGE_SUFFIX}"
)
if [ "${R_VERSION}" = "devel" ]; then
    args+=(--build-arg "R_DEVEL_CACHE_DATE=$(date -u +%Y-%m-%d)")
fi
if [ -n "${PLATFORM:-}" ]; then
    args+=(--platform "${PLATFORM}")
fi
args+=("${HARNESS_DIR}")

DOCKER_BUILDKIT=1 docker "${args[@]}"

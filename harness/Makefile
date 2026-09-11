.ONESHELL:
SHELL := /bin/bash
.SHELLFLAGS := -eu -o pipefail -c
.DEFAULT_GOAL := help

ifeq ($(filter 4.% 5.%,$(MAKE_VERSION)),)
$(error GNU Make 4 or newer is required; on macOS run `brew install make` and use `gmake`)
endif

REGISTRY ?= hhoeflin
INSTALL_DOCS_DEPS ?= true
FAIL_ON_WARNINGS ?= false
PLATFORM ?=
LINUX_BASE_IMAGE ?= debian:testing
LINUX_IMAGE_SUFFIX ?=
MAKE_COMMAND := $(notdir $(MAKE))

R_VERSIONS := 4.3.3 4.4.3 4.5.1 4.6.1 devel

# Matrix entries are R:HDF5:build-system. HDF5 2.x always uses CMake; the
# additional 1.14.6 CMake entry exercises the HDF5 wrapper configuration from
# issue #246.
HDF5_PROFILES := \
	1.8.23:autotools \
	1.10.11:autotools \
	1.12.3:autotools \
	1.14.6:autotools \
	1.14.6:cmake \
	2.0.0:cmake \
	2.1.1:cmake \
	2.2.0:cmake

DEFAULT_COMBOS := \
	4.6.1:system:system \
	4.6.1:1.8.23:autotools \
	4.6.1:1.10.11:autotools \
	4.6.1:1.12.3:autotools \
	4.6.1:1.14.6:autotools \
	4.6.1:2.0.0:cmake \
	4.6.1:2.1.1:cmake \
	4.6.1:2.2.0:cmake \
	4.3.3:2.2.0:cmake \
	4.4.3:2.2.0:cmake \
	4.5.1:2.2.0:cmake \
	devel:2.2.0:cmake \
	devel:1.14.6:cmake

FULL_COMBOS := \
	4.3.3:1.8.23:autotools 4.3.3:1.10.11:autotools 4.3.3:1.12.3:autotools 4.3.3:1.14.6:autotools 4.3.3:2.0.0:cmake 4.3.3:2.1.1:cmake 4.3.3:2.2.0:cmake \
	4.4.3:1.8.23:autotools 4.4.3:1.10.11:autotools 4.4.3:1.12.3:autotools 4.4.3:1.14.6:autotools 4.4.3:2.0.0:cmake 4.4.3:2.1.1:cmake 4.4.3:2.2.0:cmake \
	4.5.1:1.8.23:autotools 4.5.1:1.10.11:autotools 4.5.1:1.12.3:autotools 4.5.1:1.14.6:autotools 4.5.1:2.0.0:cmake 4.5.1:2.1.1:cmake 4.5.1:2.2.0:cmake \
	4.6.1:1.8.23:autotools 4.6.1:1.10.11:autotools 4.6.1:1.12.3:autotools 4.6.1:1.14.6:autotools 4.6.1:2.0.0:cmake 4.6.1:2.1.1:cmake 4.6.1:2.2.0:cmake \
	devel:1.8.23:autotools devel:1.10.11:autotools devel:1.12.3:autotools devel:1.14.6:autotools devel:1.14.6:cmake devel:2.0.0:cmake devel:2.1.1:cmake devel:2.2.0:cmake

PKG_DIR := $(realpath ..)
COMMON_DIR := $(CURDIR)/common
MACOS_DIR := $(CURDIR)/macos
LOG_DIR := $(CURDIR)/logs
HDF5_BUILD_SYSTEM ?= auto
HDF5_BUILD_SYSTEM_EFFECTIVE = $(if $(filter system System,$(HDF5_VERSION)),system,$(if $(filter auto,$(HDF5_BUILD_SYSTEM)),$(if $(filter 2.%,$(HDF5_VERSION)),cmake,autotools),$(HDF5_BUILD_SYSTEM)))
HDF5_CMAKE_SUFFIX = $(if $(filter 1.%,$(HDF5_VERSION)),$(if $(filter cmake,$(HDF5_BUILD_SYSTEM_EFFECTIVE)),-cmake,))
HDF5_TAG = $(if $(filter system,$(HDF5_BUILD_SYSTEM_EFFECTIVE)),System,$(HDF5_VERSION)$(HDF5_CMAKE_SUFFIX))
DEPS_IMAGE = $(REGISTRY)/hdf5r-deps:r$(R_VERSION)-hdf5v$(HDF5_TAG)$(LINUX_IMAGE_SUFFIX)
LINUX_CHECK_NAME = linux-r$(R_VERSION)-hdf5v$(HDF5_TAG)$(LINUX_IMAGE_SUFFIX)
LINUX_CHECK_DIR = $(LOG_DIR)/check-$(LINUX_CHECK_NAME)

define require_r
	@if [ -z "$(R_VERSION)" ]; then echo "ERROR: R is required (example: R_VERSION=4.6.1)" >&2; exit 2; fi
endef

define require_hdf5
	@if [ -z "$(HDF5_VERSION)" ]; then echo "ERROR: HDF5 is required (example: HDF5_VERSION=2.2.0)" >&2; exit 2; fi
endef

define require_safe_versions
	@case "$(R_VERSION)" in *[!A-Za-z0-9_.-]*|'') echo "ERROR: R_VERSION contains unsafe characters" >&2; exit 2;; esac
	@case "$(HDF5_VERSION)" in *[!A-Za-z0-9_.-]*|'') echo "ERROR: HDF5_VERSION contains unsafe characters" >&2; exit 2;; esac
	@case "$(HDF5_BUILD_SYSTEM_EFFECTIVE)" in autotools|cmake|system) ;; *) echo "ERROR: unsupported HDF5 build system" >&2; exit 2;; esac
endef

combo_list = $(if $(filter 1,$(FULL)),$(FULL_COMBOS),$(DEFAULT_COMBOS))

.PHONY: help
help:
	@echo "hdf5r test harness"
	@echo
	@echo "One-time setup:"
	@echo "  $(MAKE_COMMAND) setup-macos                       macOS prerequisites (TeX, Java, pandoc, qpdf)"
	@echo
	@echo "Single combination:"
	@echo "  $(MAKE_COMMAND) build-linux R_VERSION=4.6.1 HDF5_VERSION=2.2.0"
	@echo "  $(MAKE_COMMAND) check-linux R_VERSION=4.6.1 HDF5_VERSION=2.2.0"
	@echo "  $(MAKE_COMMAND) build-linux R_VERSION=devel HDF5_VERSION=1.14.6 HDF5_BUILD_SYSTEM=cmake"
	@echo "  $(MAKE_COMMAND) check-linux R_VERSION=devel HDF5_VERSION=1.14.6 HDF5_BUILD_SYSTEM=cmake"
	@echo "  $(MAKE_COMMAND) build-macos R_VERSION=4.6.1 HDF5_VERSION=2.2.0"
	@echo "  $(MAKE_COMMAND) check-macos R_VERSION=4.6.1 HDF5_VERSION=2.2.0"
	@echo
	@echo "Matrices (build and check are separate):"
	@echo "  $(MAKE_COMMAND) build-matrix-linux [FULL=1]"
	@echo "  $(MAKE_COMMAND) check-matrix-linux [FULL=1]"
	@echo "  $(MAKE_COMMAND) build-matrix-macos              each macOS R and HDF5 version once"
	@echo "  $(MAKE_COMMAND) check-matrix-macos [FULL=1]"
	@echo
	@echo "Check options: FAIL_ON_WARNINGS=true fails checks with warnings"
	@echo
	@echo "Results:"
	@echo "  $(MAKE_COMMAND) summary [PLATFORM=linux|macos]"
	@echo
	@echo "R versions:    $(R_VERSIONS)"
	@echo "HDF5 profiles: $(HDF5_PROFILES) (Linux also accepts HDF5_VERSION=system)"

.PHONY: build-linux-r
build-linux-r:
	$(require_r)
	@mkdir -p "$(LOG_DIR)"
	@echo "==> building Linux R $(R_VERSION)"
	@REGISTRY="$(REGISTRY)" PLATFORM="$(PLATFORM)" BASE_IMAGE="$(LINUX_BASE_IMAGE)" IMAGE_SUFFIX="$(LINUX_IMAGE_SUFFIX)" \
	    docker/base-r/build.sh "$(R_VERSION)" 2>&1 | tee "$(LOG_DIR)/build-linux-r$(R_VERSION)$(LINUX_IMAGE_SUFFIX).log"

.PHONY: build-linux-deps
build-linux-deps:
	$(require_r)
	$(require_hdf5)
	@mkdir -p "$(LOG_DIR)"
	@echo "==> building Linux R $(R_VERSION) / HDF5 $(HDF5_VERSION) ($(HDF5_BUILD_SYSTEM_EFFECTIVE)) dependencies"
	@REGISTRY="$(REGISTRY)" INSTALL_DOCS_DEPS="$(INSTALL_DOCS_DEPS)" PLATFORM="$(PLATFORM)" IMAGE_SUFFIX="$(LINUX_IMAGE_SUFFIX)" HDF5_BUILD_SYSTEM="$(HDF5_BUILD_SYSTEM_EFFECTIVE)" \
	    docker/deps/build.sh "$(R_VERSION)" "$(HDF5_VERSION)" 2>&1 \
	    | tee "$(LOG_DIR)/build-linux-r$(R_VERSION)-hdf5v$(HDF5_TAG)$(LINUX_IMAGE_SUFFIX).log"

.PHONY: build-linux
build-linux:
	$(require_r)
	$(require_hdf5)
	@$(MAKE) --no-print-directory build-linux-r R_VERSION="$(R_VERSION)"
	@$(MAKE) --no-print-directory build-linux-deps R_VERSION="$(R_VERSION)" HDF5_VERSION="$(HDF5_VERSION)" HDF5_BUILD_SYSTEM="$(HDF5_BUILD_SYSTEM_EFFECTIVE)"

.PHONY: check-linux
check-linux:
	$(require_r)
	$(require_hdf5)
	$(require_safe_versions)
	@rm -rf "$(LINUX_CHECK_DIR)"
	@mkdir -p "$(LINUX_CHECK_DIR)"
	@printf '%s\n' RUNNING > "$(LINUX_CHECK_DIR)/status"
	@printf '%s\n' "=== hdf5r preflight: $(LINUX_CHECK_NAME) ===" > "$(LINUX_CHECK_DIR)/preflight.log"
	@printf '%s\n' "=== started: $$(date -u '+%Y-%m-%dT%H:%M:%SZ') ===" >> "$(LINUX_CHECK_DIR)/preflight.log"
	@mkdir -p "$(LOG_DIR)"
	@echo "==> checking Linux R $(R_VERSION) / HDF5 $(HDF5_VERSION) ($(HDF5_BUILD_SYSTEM_EFFECTIVE))"
	@status="$(LINUX_CHECK_DIR)/status"
	@if ! docker image inspect "$(DEPS_IMAGE)" >/dev/null 2>&1; then \
	    echo FAIL > "$${status}"; \
	    { echo "ERROR: missing image $(DEPS_IMAGE)"; \
	      echo "Build it with: $(MAKE_COMMAND) build-linux R_VERSION=$(R_VERSION) HDF5_VERSION=$(HDF5_VERSION) HDF5_BUILD_SYSTEM=$(HDF5_BUILD_SYSTEM_EFFECTIVE)"; \
	    } | tee -a "$(LINUX_CHECK_DIR)/preflight.log" >&2; \
	    exit 2; \
	fi
	@if ! docker run --rm \
	    -v "$(PKG_DIR):/pkg:ro" \
	    -v "$(COMMON_DIR):/opt/scripts:ro" \
	    -v "$(LINUX_CHECK_DIR):/out" \
	    -e "HDF5_VERSION=$(HDF5_VERSION)" \
	    -e "HDF5_BUILD_SYSTEM=$(HDF5_BUILD_SYSTEM_EFFECTIVE)" \
	    -e "FAIL_ON_WARNINGS=$(FAIL_ON_WARNINGS)" \
	    "$(DEPS_IMAGE)" \
	    bash /opt/scripts/run-check.sh /pkg /out "$(LINUX_CHECK_NAME)" \
	    2>&1 | tee "$(LINUX_CHECK_DIR)/runner.log"; then \
	    echo FAIL > "$${status}"; \
	    echo "ERROR: Docker check failed; see runner.log" | tee -a "$(LINUX_CHECK_DIR)/preflight.log" >&2; \
	    exit 1; \
	fi

.PHONY: setup-macos
setup-macos:
	@"$(MACOS_DIR)/setup.sh"

.PHONY: build-macos-r
build-macos-r:
	$(require_r)
	@mkdir -p "$(LOG_DIR)"
	@"$(MACOS_DIR)/build-r.sh" "$(R_VERSION)" 2>&1 | tee "$(LOG_DIR)/build-macos-r$(R_VERSION).log"

.PHONY: build-macos-hdf5
build-macos-hdf5:
	$(require_hdf5)
	@"$(MACOS_DIR)/build-hdf5.sh" "$(HDF5_VERSION)" "$(HDF5_BUILD_SYSTEM_EFFECTIVE)"

.PHONY: build-macos
build-macos:
	$(require_r)
	$(require_hdf5)
	@$(MAKE) --no-print-directory build-macos-r R_VERSION="$(R_VERSION)"
	@$(MAKE) --no-print-directory build-macos-hdf5 HDF5_VERSION="$(HDF5_VERSION)" HDF5_BUILD_SYSTEM="$(HDF5_BUILD_SYSTEM_EFFECTIVE)"

.PHONY: check-macos
check-macos:
	$(require_r)
	$(require_hdf5)
	$(require_safe_versions)
	@mkdir -p "$(LOG_DIR)"
	@echo "==> checking macOS R $(R_VERSION) / HDF5 $(HDF5_VERSION) ($(HDF5_BUILD_SYSTEM_EFFECTIVE))"
	@FAIL_ON_WARNINGS="$(FAIL_ON_WARNINGS)" \
	    "$(MACOS_DIR)/run-check.sh" "$(R_VERSION)" "$(HDF5_VERSION)" "$(HDF5_BUILD_SYSTEM_EFFECTIVE)" "$(PKG_DIR)" "$(LOG_DIR)"

.PHONY: build-matrix-linux
build-matrix-linux:
	@failed=""
	@for combo in $(combo_list); do \
	    IFS=: read -r r h build_system <<< "$${combo}"; \
	    if ! $(MAKE) --no-print-directory build-linux R_VERSION="$${r}" HDF5_VERSION="$${h}" HDF5_BUILD_SYSTEM="$${build_system}"; then \
	        failed="$${failed} r$${r}-hdf5v$${h}-$${build_system}"; \
	    fi; \
	done
	@if [ -n "$${failed}" ]; then echo "FAILED BUILDS:$${failed}"; exit 1; fi

.PHONY: prepare-check-matrix-linux
prepare-check-matrix-linux:
	@mkdir -p "$(LOG_DIR)"
	@rm -rf "$(LOG_DIR)"/check-linux-*

.PHONY: check-matrix-linux
check-matrix-linux: prepare-check-matrix-linux
	@failed=""
	@for combo in $(combo_list); do \
	    IFS=: read -r r h build_system <<< "$${combo}"; \
	    if ! $(MAKE) --no-print-directory check-linux R_VERSION="$${r}" HDF5_VERSION="$${h}" HDF5_BUILD_SYSTEM="$${build_system}"; then \
	        failed="$${failed} r$${r}-hdf5v$${h}-$${build_system}"; \
	    fi; \
	done
	@$(MAKE) --no-print-directory summary PLATFORM=linux
	@if [ -n "$${failed}" ]; then echo "FAILED CHECKS:$${failed}"; exit 1; fi

.PHONY: build-matrix-macos
build-matrix-macos:
	@failed=""
	@for r in $(R_VERSIONS); do \
	    if ! $(MAKE) --no-print-directory build-macos-r R_VERSION="$${r}"; then \
	        failed="$${failed} r$${r}"; \
	    fi; \
	done
	@for profile in $(HDF5_PROFILES); do \
	    IFS=: read -r h build_system <<< "$${profile}"; \
	    if ! $(MAKE) --no-print-directory build-macos-hdf5 HDF5_VERSION="$${h}" HDF5_BUILD_SYSTEM="$${build_system}"; then \
	        failed="$${failed} hdf5v$${h}-$${build_system}"; \
	    fi; \
	done
	@if [ -n "$${failed}" ]; then echo "FAILED BUILDS:$${failed}"; exit 1; fi

.PHONY: prepare-check-matrix-macos
prepare-check-matrix-macos:
	@mkdir -p "$(LOG_DIR)"
	@rm -rf "$(LOG_DIR)"/check-macos-*

.PHONY: check-matrix-macos
check-matrix-macos: prepare-check-matrix-macos
	@failed=""
	@for combo in $(combo_list); do \
	    IFS=: read -r r h build_system <<< "$${combo}"; \
	    if ! $(MAKE) --no-print-directory check-macos R_VERSION="$${r}" HDF5_VERSION="$${h}" HDF5_BUILD_SYSTEM="$${build_system}"; then \
	        failed="$${failed} r$${r}-hdf5v$${h}-$${build_system}"; \
	    fi; \
	done
	@$(MAKE) --no-print-directory summary PLATFORM=macos
	@if [ -n "$${failed}" ]; then echo "FAILED CHECKS:$${failed}"; exit 1; fi

.PHONY: summary
summary:
	@case "$(PLATFORM)" in \
	    linux|macos) pattern="$(LOG_DIR)/check-$(PLATFORM)-*/status" ;; \
	    "") pattern="$(LOG_DIR)/check-*/status" ;; \
	    *) echo "ERROR: PLATFORM must be linux or macos" >&2; exit 2 ;; \
	esac
	@echo "=== hdf5r check summary ($$(date '+%Y-%m-%d %H:%M')) ==="
	@printf '%-38s %s\n' "COMBINATION" "STATUS"
	@found=0
	@for status in $${pattern}; do \
	    [ -e "$${status}" ] || continue; \
	    found=1; \
	    printf '%-38s %s\n' "$$(basename "$$(dirname "$${status}")")" "$$(cat "$${status}")"; \
	done
	@if [ "$${found}" -eq 0 ]; then echo "(no results)"; fi

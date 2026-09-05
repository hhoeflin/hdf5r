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
MAKE_COMMAND := $(notdir $(MAKE))

R_VERSIONS := 4.3.3 4.4.3 4.5.1 4.6.1 devel
HDF5_VERSIONS := 1.8.23 1.10.11 1.12.3 1.14.6 2.0.0 2.1.1 2.2.0
LATEST_R := 4.6.1
LATEST_HDF5 := 2.2.0

PKG_DIR := $(realpath ..)
COMMON_DIR := $(CURDIR)/common
MACOS_DIR := $(CURDIR)/macos
LOG_DIR := $(CURDIR)/logs
HDF5_TAG = $(if $(filter system System,$(HDF5_VERSION)),System,$(HDF5_VERSION))
DEPS_IMAGE = $(REGISTRY)/hdf5r-deps:r$(R_VERSION)-hdf5v$(HDF5_TAG)

define require_r
	@if [ -z "$(R_VERSION)" ]; then echo "ERROR: R is required (example: R_VERSION=4.6.1)" >&2; exit 2; fi
endef

define require_hdf5
	@if [ -z "$(HDF5_VERSION)" ]; then echo "ERROR: HDF5 is required (example: HDF5_VERSION=2.2.0)" >&2; exit 2; fi
endef

# Default matrix: every HDF5 on the latest R, plus the latest HDF5 on every R.
# FULL=1 selects the complete cross product.
define combo_list
	if [ "$(FULL)" = "1" ]; then \
	    for r in $(R_VERSIONS); do for h in $(HDF5_VERSIONS); do echo "$${r}:$${h}"; done; done; \
	else \
	    { for h in $(HDF5_VERSIONS); do echo "$(LATEST_R):$${h}"; done; \
	      for r in $(R_VERSIONS); do echo "$${r}:$(LATEST_HDF5)"; done; } | sort -u; \
	fi
endef

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
	@echo "HDF5 versions: $(HDF5_VERSIONS) (Linux also accepts HDF5_VERSION=system)"

.PHONY: build-linux-r
build-linux-r:
	$(require_r)
	@mkdir -p "$(LOG_DIR)"
	@echo "==> building Linux R $(R_VERSION)"
	@REGISTRY="$(REGISTRY)" PLATFORM="$(PLATFORM)" \
	    docker/base-r/build.sh "$(R_VERSION)" 2>&1 | tee "$(LOG_DIR)/build-linux-r$(R_VERSION).log"

.PHONY: build-linux-deps
build-linux-deps:
	$(require_r)
	$(require_hdf5)
	@mkdir -p "$(LOG_DIR)"
	@echo "==> building Linux R $(R_VERSION) / HDF5 $(HDF5_VERSION) dependencies"
	@REGISTRY="$(REGISTRY)" INSTALL_DOCS_DEPS="$(INSTALL_DOCS_DEPS)" PLATFORM="$(PLATFORM)" \
	    docker/deps/build.sh "$(R_VERSION)" "$(HDF5_VERSION)" 2>&1 \
	    | tee "$(LOG_DIR)/build-linux-r$(R_VERSION)-hdf5v$(HDF5_TAG).log"

.PHONY: build-linux
build-linux:
	$(require_r)
	$(require_hdf5)
	@$(MAKE) --no-print-directory build-linux-r R_VERSION="$(R_VERSION)"
	@$(MAKE) --no-print-directory build-linux-deps R_VERSION="$(R_VERSION)" HDF5_VERSION="$(HDF5_VERSION)"

.PHONY: check-linux
check-linux:
	$(require_r)
	$(require_hdf5)
	@mkdir -p "$(LOG_DIR)"
	@echo "==> checking Linux R $(R_VERSION) / HDF5 $(HDF5_VERSION)"
	@status="$(LOG_DIR)/linux-r$(R_VERSION)-hdf5v$(HDF5_TAG).status"
	@if ! docker image inspect "$(DEPS_IMAGE)" >/dev/null 2>&1; then \
	    echo FAIL > "$${status}"; \
	    echo "ERROR: missing image $(DEPS_IMAGE)" >&2; \
	    echo "Build it with: $(MAKE_COMMAND) build-linux R_VERSION=$(R_VERSION) HDF5_VERSION=$(HDF5_VERSION)" >&2; \
	    exit 2; \
	fi
	@docker run --rm \
	    -v "$(PKG_DIR):/pkg:ro" \
	    -v "$(COMMON_DIR):/opt/scripts:ro" \
	    -v "$(LOG_DIR):/out" \
	    -e "HDF5_VERSION=$(HDF5_VERSION)" \
	    -e "FAIL_ON_WARNINGS=$(FAIL_ON_WARNINGS)" \
	    "$(DEPS_IMAGE)" \
	    bash /opt/scripts/run-check.sh /pkg /out "linux-r$(R_VERSION)-hdf5v$(HDF5_TAG)"

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
	@"$(MACOS_DIR)/build-hdf5.sh" "$(HDF5_VERSION)"

.PHONY: build-macos
build-macos:
	$(require_r)
	$(require_hdf5)
	@$(MAKE) --no-print-directory build-macos-r R_VERSION="$(R_VERSION)"
	@$(MAKE) --no-print-directory build-macos-hdf5 HDF5_VERSION="$(HDF5_VERSION)"

.PHONY: check-macos
check-macos:
	$(require_r)
	$(require_hdf5)
	@mkdir -p "$(LOG_DIR)"
	@echo "==> checking macOS R $(R_VERSION) / HDF5 $(HDF5_VERSION)"
	@FAIL_ON_WARNINGS="$(FAIL_ON_WARNINGS)" \
	    "$(MACOS_DIR)/run-check.sh" "$(R_VERSION)" "$(HDF5_VERSION)" "$(PKG_DIR)" "$(LOG_DIR)"

.PHONY: build-matrix-linux
build-matrix-linux:
	@failed=""
	@for combo in $$($(combo_list)); do \
	    r="$${combo%%:*}"; h="$${combo##*:}"; \
	    if ! $(MAKE) --no-print-directory build-linux R_VERSION="$${r}" HDF5_VERSION="$${h}"; then \
	        failed="$${failed} r$${r}-hdf5v$${h}"; \
	    fi; \
	done
	@if [ -n "$${failed}" ]; then echo "FAILED BUILDS:$${failed}"; exit 1; fi

.PHONY: prepare-check-matrix-linux
prepare-check-matrix-linux:
	@mkdir -p "$(LOG_DIR)"
	@rm -f "$(LOG_DIR)"/linux-*.status

.PHONY: check-matrix-linux
check-matrix-linux: prepare-check-matrix-linux
	@failed=""
	@for combo in $$($(combo_list)); do \
	    r="$${combo%%:*}"; h="$${combo##*:}"; \
	    if ! $(MAKE) --no-print-directory check-linux R_VERSION="$${r}" HDF5_VERSION="$${h}"; then \
	        failed="$${failed} r$${r}-hdf5v$${h}"; \
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
	@for h in $(HDF5_VERSIONS); do \
	    if ! $(MAKE) --no-print-directory build-macos-hdf5 HDF5_VERSION="$${h}"; then \
	        failed="$${failed} hdf5v$${h}"; \
	    fi; \
	done
	@if [ -n "$${failed}" ]; then echo "FAILED BUILDS:$${failed}"; exit 1; fi

.PHONY: prepare-check-matrix-macos
prepare-check-matrix-macos:
	@mkdir -p "$(LOG_DIR)"
	@rm -f "$(LOG_DIR)"/macos-*.status

.PHONY: check-matrix-macos
check-matrix-macos: prepare-check-matrix-macos
	@failed=""
	@for combo in $$($(combo_list)); do \
	    r="$${combo%%:*}"; h="$${combo##*:}"; \
	    if ! $(MAKE) --no-print-directory check-macos R_VERSION="$${r}" HDF5_VERSION="$${h}"; then \
	        failed="$${failed} r$${r}-hdf5v$${h}"; \
	    fi; \
	done
	@$(MAKE) --no-print-directory summary PLATFORM=macos
	@if [ -n "$${failed}" ]; then echo "FAILED CHECKS:$${failed}"; exit 1; fi

.PHONY: summary
summary:
	@case "$(PLATFORM)" in \
	    linux|macos) pattern="$(LOG_DIR)/$(PLATFORM)-*.status" ;; \
	    "") pattern="$(LOG_DIR)/*.status" ;; \
	    *) echo "ERROR: PLATFORM must be linux or macos" >&2; exit 2 ;; \
	esac
	@echo "=== hdf5r check summary ($$(date '+%Y-%m-%d %H:%M')) ==="
	@printf '%-38s %s\n' "COMBINATION" "STATUS"
	@found=0
	@for status in $${pattern}; do \
	    [ -e "$${status}" ] || continue; \
	    found=1; \
	    printf '%-38s %s\n' "$$(basename "$${status}" .status)" "$$(cat "$${status}")"; \
	done
	@if [ "$${found}" -eq 0 ]; then echo "(no results)"; fi

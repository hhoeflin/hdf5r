.ONESHELL:

ifndef R_REVISION
$(error R_REVISION is not set)
endif

logs/build-${R_REVISION}: Dockerfile
	export DOCKER_BUILDKIT=1
	mkdir -p logs
	docker build -f Dockerfile -t hhoeflin/base-debian-gcc-devel:r${R_REVISION}\
		--build-arg R_REVISION=${R_REVISION} . > $@ 2>&1

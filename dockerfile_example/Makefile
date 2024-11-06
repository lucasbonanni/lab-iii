# Compiler settings
CC = gcc
CFLAGS = -pedantic-errors -Wall -O3 -std=gnu89

# Binary names (adjust as needed for each project)
BINS = program1
BINS_AMD64 = $(addsuffix -amd64,$(BINS))
BINS_I386 = $(addsuffix -i386,$(BINS))

# Docker images
DOCKER_AMD64 = lpenz/ubuntu-gutsy-amd64
DOCKER_I386 = lpenz/ubuntu-gutsy-i386

# Docker build commands with package installation
DOCKER_BUILD_CMD = apt-get update && apt-get install -y build-essential && gcc $(CFLAGS)

.PHONY: all clean test test-local test-docker verify docker-build

all: $(BINS)

# Local compilation
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Build for different architectures using Docker
docker-build:
	@echo "Building for AMD64..."
	@for src in $(BINS:=.c); do \
		bin=$${src%.c}-amd64; \
		docker run --rm -v "$(PWD):/app" -w /app $(DOCKER_AMD64) \
			/bin/bash -c "apt-get update && apt-get install -y build-essential && gcc $(CFLAGS) -o $$bin $$src" || exit 1; \
	done
	@echo "Building for i386..."
	@for src in $(BINS:=.c); do \
		bin=$${src%.c}-i386; \
		docker run --rm -v "$(PWD):/app" -w /app $(DOCKER_I386) \
			/bin/bash -c "apt-get update && apt-get install -y build-essential && gcc $(CFLAGS) -o $$bin $$src" || exit 1; \
	done

clean:
	rm -f $(BINS) $(BINS_AMD64) $(BINS_I386)

# Local testing
test-local: all
	@echo "Running local tests..."
	@./verify.sh local $(BINS)

# Docker testing
test-docker: docker-build
	@echo "Running tests in Docker containers..."
	@./verify.sh docker-amd64 $(BINS_AMD64)
	@./verify.sh docker-i386 $(BINS_I386)

# Full verification
verify: test-local test-docker
	@echo "All verification steps completed successfully!"

build:
	$(CC) $(CFLAGS) -o $(BINS) $(BINS).c

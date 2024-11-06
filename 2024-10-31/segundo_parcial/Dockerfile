FROM lpenz/ubuntu-gutsy-amd64

# Set working directory
WORKDIR /app

# Install dependencies with verification
RUN apt-get update && \
    apt-get install -y \
    make \
    libc6-dev \
    gdb \
    build-essential \
    libpthread-stubs0-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    # Create symbolic link for gcc
    # Verify installation
    && gcc --version

# Set environment variables
ENV PATH="/usr/bin:${PATH}"

# Copy source files
COPY . .

# Set appropriate permissions
RUN chown -R root:root /app

# Build command with error checking
RUN make all || (echo "Build failed" && exit 1)

# Add healthcheck
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD ps aux | grep "[g]cc" || exit 1

CMD ["./program1"]

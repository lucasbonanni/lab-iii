# First build the image (assuming Dockerfile is in current directory)
docker build -t my-gcc-app .

# Run container in interactive mode with terminal
docker run -it my-gcc-app /bin/bash

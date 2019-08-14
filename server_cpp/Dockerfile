FROM ubuntu:latest
# Dependencies
COPY install_deps.sh .
RUN ./install_deps.sh
# Build
WORKDIR /app
COPY . .
RUN mkdir -p build && cd build && cmake .. && cmake --build .
CMD /app/build/server_cpp
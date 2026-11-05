FROM ubuntu:24.04 AS build
RUN apt-get update && apt-get install -y cmake g++ && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . .
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF && cmake --build build
FROM ubuntu:24.04
COPY --from=build /app/build/matrix_calculator /usr/local/bin/matrix_calculator
CMD ["matrix_calculator"]

FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    openmpi-bin \
    libopenmpi-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY main.c /app/

RUN mpicc -fopenmp -o mpi_openmp_app main.c -lm

CMD ["mpirun", "--allow-run-as-root", "--oversubscribe", "-np", "4", "./mpi_openmp_app"]
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE 10000000 // 10 Milyon Eleman
#define NUM_THREADS 4
#define MASTER 0

void fill_array(int *arr, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000 + 1; // 1-1000 arası değerler
    }
}

int main(int argc, char **argv) {
    int rank, size;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    omp_set_num_threads(NUM_THREADS);

    int chunk_size = ARRAY_SIZE / size;
    int *sub_array = (int *)malloc(chunk_size * sizeof(int));
    int *array = NULL;
    
    if (rank == MASTER) {
        array = (int *)malloc(ARRAY_SIZE * sizeof(int));
        fill_array(array, ARRAY_SIZE);
        printf("Veri kümesi oluşturuldu. Paralel işlem başlatılıyor...\n");
    }

    start_time = MPI_Wtime(); // Zaman ölçümünü başlat

    MPI_Scatter(array, chunk_size, MPI_INT, sub_array, chunk_size, MPI_INT, MASTER, MPI_COMM_WORLD);

    double local_sqrt_sum = 0.0;
    double local_log_sum = 0.0;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        #pragma omp for reduction(+:local_sqrt_sum, local_log_sum)
        for (int i = 0; i < chunk_size; i++) {
            local_sqrt_sum += sqrt(sub_array[i]);
            local_log_sum += log(sub_array[i]);
        }

        printf("MPI Süreci %d - OpenMP Thread %d / %d çalışıyor\n", rank, thread_id, num_threads);
    }

    double global_sqrt_sum = 0.0;
    double global_log_sum = 0.0;
    MPI_Reduce(&local_sqrt_sum, &global_sqrt_sum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
    MPI_Reduce(&local_log_sum, &global_log_sum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

    end_time = MPI_Wtime(); // Zaman ölçümünü durdur

    if (rank == MASTER) {
        printf("Karekök Toplamı: %f\n", global_sqrt_sum);
        printf("Logaritma Toplamı: %f\n", global_log_sum);
        printf("Toplam Süre: %f saniye\n", end_time - start_time);
        free(array);
    }
    
    free(sub_array);
    MPI_Finalize();
    return 0;
}
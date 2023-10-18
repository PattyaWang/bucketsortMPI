#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define MAX_VALUE 1000000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n, local_size;

    if (rank == 0) {
        // Get user input for array size (im lazy to make it appear in the terminal)
        printf("Enter the size of the array: ");
        scanf("%d", &n);

        if (n % size != 0) {
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    // Broadcast array size to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    local_size = n / size;

    // Allocate memory for local data
    int *local_data = (int *)malloc(sizeof(int) * local_size);

    // Generate random data
    srand(time(NULL) + rank);
    for (int i = 0; i < local_size; i++) {
        local_data[i] = rand() % MAX_VALUE;
    }

    // Gather local data from all processes to rank 0
    int *data = NULL;
    if (rank == 0) {
        data = (int *)malloc(sizeof(int) * n);
    }

    MPI_Gather(local_data, local_size, MPI_INT, data, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Start timer
    double start_time = MPI_Wtime();

    // Sort locally
    qsort(local_data, local_size, sizeof(int), compare);

    // Gather sorted data from all processes to rank 0
    MPI_Gather(local_data, local_size, MPI_INT, data, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // End timer
    double end_time = MPI_Wtime();

    if (rank == 0) {
        // Print runtime
        printf("Time taken: %f seconds\n", end_time - start_time);

        // merging
        // qsort(data, n, sizeof(int), compare);
        // for (int i = 0; i < n; i++) {
        //     printf("%d ", data[i]);
        // }
        // printf("\n");

        free(data);
    }

    free(local_data);
    MPI_Finalize();
    return 0;
}
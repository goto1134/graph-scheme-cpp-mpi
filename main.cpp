#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {

    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    std::cout << world_size << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
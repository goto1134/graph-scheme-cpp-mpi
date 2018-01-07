//
// Created by goto1134 on 07.01.18.
//

#include <mpi.h>
#include <Module.h>
#include <boost/format.hpp>
#include <boost/array.hpp>
#include <valarray>
#include "SimpleMPIController.h"

void SimpleMPIController::start() {
    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    std::map<int, ModuleId> moduleMap = getModuleMap(world_size, rank);

    if (rank == MASTER_NODE) {
        for (auto moduleEntry : moduleMap) {
            std::cout << moduleEntry.first << " : " << moduleEntry.second << std::endl;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);


    auto sendbuf = new bool[world_size]{0, 1};
    auto receivebuf = new bool[world_size]{0, 0};

    MPI_Alltoall(sendbuf, 1, MPI_CXX_BOOL, receivebuf, 1, MPI_CXX_BOOL, MPI_COMM_WORLD);

    std::valarray<bool> result = std::valarray<bool>(sendbuf, world_size) | std::valarray<bool>(receivebuf, world_size);


    for (int i = 0; i < world_size; ++i) {
        if (i == rank)
            continue;
        if (result[i]) {
            int data_to_send = i;
            int data_to_receive;
            MPI_Status status;
            MPI_Sendrecv(&data_to_send, 1, MPI_INT, i, 0, &data_to_receive, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            std::cout << boost::format("WITH %3% %1% to send, %2% to receive") % data_to_send % data_to_receive % i
                      << std::endl;
        }
        std::cout << boost::format("%1% Need to communicate with %2% %3% %4% %5%") % rank % i % receivebuf[i] %
                     sendbuf[i] % result[i]
                  << std::endl;
    }

    if (rank == MASTER_NODE) {
        std::cout << world_size << std::endl;
        std::cout << "Hello, World!" << std::endl;
    }

    MPI_Finalize();
}


std::map<int, ModuleId> SimpleMPIController::getModuleMap(int world_size, int rank) {
    auto modules = moduleloader->getModules();

    const auto moduleCount = modules.size();
    const auto intBufferLength = 2 * moduleCount;
    auto buffer = new int[intBufferLength];
    if (rank == MASTER_NODE) {
        for (unsigned long i = 0; i < moduleCount; i++) {
            const auto module = modules.at(i);
            auto nodeId = i % world_size;
            buffer[2 * i] = static_cast<int>(nodeId);
            buffer[2 * i + 1] = module.id;
        }

    }
    MPI_Bcast(buffer, (int) intBufferLength, MPI_INT, MASTER_NODE, MPI_COMM_WORLD);

    std::map<int, ModuleId> moduleMap;
    for (auto i = 0; i < moduleCount; i++) {
        moduleMap.insert(std::make_pair(buffer[2 * i], buffer[2 * i + 1]));
    }

    delete [] buffer;
    return moduleMap;
}

fruit::Component<fruit::Required<ModuleLoader>, MPIController> getSimpleControllerComponent() {
    return fruit::createComponent().bind<MPIController, SimpleMPIController>();
}

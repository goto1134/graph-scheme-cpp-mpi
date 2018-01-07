//
// Created by goto1134 on 07.01.18.
//

#include <mpi.h>
#include <Module.h>
#include <map>
#include <iostream>
#include "SimpleMPIController.h"

void SimpleMPIController::start() {
    int provided_thread_level;
    MPI_Init_thread(0, 0, MPI_THREAD_FUNNELED, &provided_thread_level);
    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == MASTER_NODE) {
        std::cout << "Provided Thread Level = " << provided_thread_level << std::endl;
    }

    std::map<int, ModuleId> moduleMap = getModuleMap(world_size, rank);

    if (rank == MASTER_NODE) {
        for (auto moduleEntry : moduleMap) {
            std::cout << moduleEntry.first << " : " << moduleEntry.second << std::endl;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);


    auto sendbuf = new bool[world_size];
    auto receivebuf = new bool[world_size];

//    MPI_Alltoall(sendbuf, world_size,)

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

    free(buffer);
    return moduleMap;
}

fruit::Component<fruit::Required<ModuleLoader>, MPIController> getSimpleControllerComponent() {
    return fruit::createComponent().bind<MPIController, SimpleMPIController>();
}

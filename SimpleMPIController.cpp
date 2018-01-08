//
// Created by goto1134 on 07.01.18.
//

#include <mpi.h>
#include <Module.h>
#include <boost/format.hpp>
#include <boost/array.hpp>
#include <valarray>
#include <DataBuffer.h>
#include <ResultBuffer.h>
#include <SimpleResultBuffer.h>
#include <fstream>
#include <sstream>
#include "SimpleDataBuffer.h"
#include "SimpleMPIController.h"
#include "SimpleDataListener.h"

fruit::Component<DataBuffer, ResultBuffer> getGraphSchemeComponents(std::vector<ModuleData> *localModules,
                                                                    std::map<ModuleId, MPIGraphSchemeModule> *allModules);

void SimpleMPIController::start() {
    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    std::cout << boost::format("WORLD SIZE IS %1%") % world_size << std::endl;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::map<ModuleId, int> moduleMap = getModuleMap(world_size, rank);

    if (rank == MASTER_NODE) {
        for (auto moduleEntry : moduleMap) {
            std::cout << moduleEntry.first << " : " << moduleEntry.second << std::endl;
        }
    }


    std::vector<ModuleData> localModules;
    for (auto moduleLocation : moduleMap) {
        if (moduleLocation.second == rank) {
            localModules.push_back(mpiGraphSchemeModules->at(moduleLocation.first).moduleData);
        }
    }

    fruit::Injector<DataBuffer, ResultBuffer> injector(getGraphSchemeComponents, &localModules, mpiGraphSchemeModules);

    auto resultBuffer = injector.get<ResultBuffer *>();
    auto dataBuffer = injector.get<DataBuffer *>();
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == MASTER_NODE)
        readInputFile(resultBuffer);

    auto needToSend = new bool[world_size]{0};
    auto needToReceive = new bool[world_size]{0};

    Result *resultToSend;
    if (!resultBuffer->empty()) {
        resultToSend = resultBuffer->take();
        const auto address = resultToSend->inputAddress;
        const ModuleId id = address.moduleId;
        const auto targetId = moduleMap[id];
        if (targetId == rank) {
            dataBuffer->put(id, address.input, resultToSend->tag, resultToSend->data);
        } else {
            needToSend[targetId] = true;
        }
    }

    MPI_Alltoall(needToSend, 1, MPI_CXX_BOOL, needToReceive, 1, MPI_CXX_BOOL, MPI_COMM_WORLD);

    std::valarray<bool> needToCommunicate =
            std::valarray<bool>(needToSend, world_size) | std::valarray<bool>(needToReceive, world_size);


    for (int i = 0; i < world_size; ++i) {
        if (i == rank)
            continue;
        if (needToCommunicate[i]) {
            bool isSending = i > rank;
            for (int j = 0; j < 2; ++j) {
                if (isSending && needToSend[i]) {
                    int metadata[] = {resultToSend->inputAddress.moduleId, resultToSend->inputAddress.input,
                                      resultToSend->tag,
                                      resultToSend->data.length};
                    MPI_Send(metadata, 4, MPI_INT, i, 0, MPI_COMM_WORLD);
                    MPI_Send(resultToSend->data.array, resultToSend->data.length, MPI_BYTE, i, 0, MPI_COMM_WORLD);
                    delete resultToSend;
                } else if (needToReceive[i]) {
                    int metadata[4];
                    MPI_Status status;
                    MPI_Recv(metadata, 4, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                    char *data = new char[metadata[3]];
                    MPI_Recv(data, metadata[3], MPI_BYTE, i, 0, MPI_COMM_WORLD, &status);
                    dataBuffer->put(metadata[0], metadata[1], metadata[2], Data(data, metadata[3]));
                }
                isSending = !isSending;
            }
        }
    }

}


std::map<ModuleId, int> SimpleMPIController::getModuleMap(int world_size, int rank) {

    const auto moduleCount = mpiGraphSchemeModules->size();
    const auto intBufferLength = 2 * moduleCount;
    auto buffer = new int[intBufferLength];
    if (rank == MASTER_NODE) {
        int i = 0;
        for (const auto &module : *mpiGraphSchemeModules) {
            auto nodeId = (i + 1) % world_size;
            buffer[2 * i] = module.first;
            buffer[2 * i + 1] = nodeId;
            i++;
        }

    }
    MPI_Bcast(buffer, (int) intBufferLength, MPI_INT, MASTER_NODE, MPI_COMM_WORLD);

    std::map<ModuleId, int> moduleMap;
    for (auto i = 0; i < moduleCount; i++) {
        moduleMap.insert(std::make_pair(buffer[2 * i], buffer[2 * i + 1]));
    }

    delete[] buffer;
    return moduleMap;
}

void SimpleMPIController::readInputFile(ResultBuffer *resultBuffer) {
    int initialModuleId;
    for (auto &module :*mpiGraphSchemeModules) {
        if (module.second.moduleData.isInitial) {
            initialModuleId = module.first;
        }
    }

    std::ifstream inputFile("input.data");
    std::string line;
    Tag tag = 0;
    while (std::getline(inputFile, line)) {
        const char *const array = line.c_str();
        char *copiedLine = new char[line.size()];
        memcpy(copiedLine, array, line.size());
        resultBuffer->put(new Result(tag, InputAddress(initialModuleId, 0), Data(copiedLine, line.size())));
        tag++;
    }
    inputFile.close();
}

fruit::Component<fruit::Required<std::map<ModuleId, MPIGraphSchemeModule>>, MPIController>
getSimpleControllerComponent() {
    return fruit::createComponent().bind<MPIController, SimpleMPIController>();
}

fruit::Component<fruit::Required<DataReadyListener, std::vector<ModuleData>>, DataBuffer> getSimpleDataBuffer();

fruit::Component<DataBuffer, ResultBuffer> getGraphSchemeComponents(std::vector<ModuleData> *localModules,
                                                                    std::map<ModuleId, MPIGraphSchemeModule> *allModules) {

    return fruit::createComponent()
            .install(getSimpleDataBuffer)
            .install(getSimpleResultBuffer)
            .install(getSimpleDataListener)
            .bindInstance(*localModules)
            .bindInstance(*allModules);
}


fruit::Component<fruit::Required<DataReadyListener, std::vector<ModuleData>>, DataBuffer> getSimpleDataBuffer() {
    return fruit::createComponent().bind<DataBuffer, SimpleDataBuffer>();
};


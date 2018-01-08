//
// Created by goto1134 on 07.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_SIMPLEMPICONTROLLER_H
#define GRAPH_SCHEME_CPP_MPI_SIMPLEMPICONTROLLER_H


#include <fruit/fruit.h>
#include <map>
#include <ostream>
#include "MPIController.h"
#include "MPIGraphSchemeModule.h"

#define MASTER_NODE 0

class SimpleMPIController : public MPIController {
private:
    std::map<ModuleId, MPIGraphSchemeModule> *mpiGraphSchemeModules;
//    std::map<ModuleId, ModuleData> modules;

    std::map<ModuleId, int> getModuleMap(int world_size, int rank);

    void readInputFile(ResultBuffer *resultBuffer);

public:
    INJECT(SimpleMPIController(std::map<ModuleId, MPIGraphSchemeModule> * mpiGraphSchemeModules))
            : mpiGraphSchemeModules(mpiGraphSchemeModules) {};

    void start() override;

};

fruit::Component<fruit::Required<std::map<ModuleId, MPIGraphSchemeModule>>, MPIController>
getSimpleControllerComponent();

#endif //GRAPH_SCHEME_CPP_MPI_SIMPLEMPICONTROLLER_H

//
// Created by goto1134 on 07.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_SIMPLEMPICONTROLLER_H
#define GRAPH_SCHEME_CPP_MPI_SIMPLEMPICONTROLLER_H


#include <fruit/fruit.h>
#include <map>
#include <ostream>
#include "MPIController.h"
#include "ModuleLoader.h"

#define MASTER_NODE 0

class SimpleMPIController : public MPIController {
private:
    ModuleLoader *moduleloader;

    std::map<int, ModuleId> getModuleMap(int world_size, int rank);

public:
    INJECT(SimpleMPIController(ModuleLoader * moduleLoader)) : moduleloader(moduleLoader) {};

    void start() override;

};

fruit::Component<fruit::Required<ModuleLoader>,MPIController> getSimpleControllerComponent();

#endif //GRAPH_SCHEME_CPP_MPI_SIMPLEMPICONTROLLER_H

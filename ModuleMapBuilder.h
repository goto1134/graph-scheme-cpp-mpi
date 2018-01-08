//
// Created by goto1134 on 07.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_MODULEMAPBUILDER_H
#define GRAPH_SCHEME_CPP_MPI_MODULEMAPBUILDER_H

#include <map>
#include <utility>
#include <Module.h>
#include "MPIGraphSchemeModule.h"

class ModuleMapBuilder {
private:
    std::map<ModuleId, MPIGraphSchemeModule> result;
public:
    ModuleMapBuilder add(MPIGraphSchemeModule moduleData);

    std::map<ModuleId, MPIGraphSchemeModule> build();
};

#endif //GRAPH_SCHEME_CPP_MPI_MODULEMAPBUILDER_H

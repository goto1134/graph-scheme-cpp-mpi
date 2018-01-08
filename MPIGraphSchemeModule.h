//
// Created by goto1134 on 08.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_MPIGRAPHSCHEMEMODULE_H
#define GRAPH_SCHEME_CPP_MPI_MPIGRAPHSCHEMEMODULE_H


#include <Module.h>
#include "Procedure.h"

struct MPIGraphSchemeModule {
    ModuleData moduleData;
    std::function<Procedure *(Tag, std::map<int, Data>, ResultBuffer *)> procedureGenerator;

    MPIGraphSchemeModule(const ModuleData &moduleData, const std::function<Procedure *(Tag, std::map<int, Data>,
                                                                                       ResultBuffer *)> &procedureGenerator);
};


#endif //GRAPH_SCHEME_CPP_MPI_MPIGRAPHSCHEMEMODULE_H

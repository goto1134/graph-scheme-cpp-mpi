//
// Created by goto1134 on 09.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_MPIGRAPHSCHEME_H
#define GRAPH_SCHEME_CPP_MPI_MPIGRAPHSCHEME_H

#include <fruit/component.h>
#include <Module.h>
#include "MPIController.h"
#include "MPIGraphSchemeModule.h"
#include "SimpleMPIController.h"

void MPIGraphSchemeInit(int *argc, char ***argv, int *provided_thread_level);

void MPIGraphSchemeFinalize();

void MPIGraphSchemeStart(std::map<ModuleId, MPIGraphSchemeModule> *modules);

fruit::Component<MPIController> createMPIGraphScheme(std::map<ModuleId, MPIGraphSchemeModule> *modules);

#endif //GRAPH_SCHEME_CPP_MPI_MPIGRAPHSCHEME_H

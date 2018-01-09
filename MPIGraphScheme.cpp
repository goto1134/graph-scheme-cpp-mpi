//
// Created by goto1134 on 09.01.18.
//

#include <mpi.h>
#include "MPIGraphScheme.h"

fruit::Component<MPIController> createMPIGraphScheme(std::map<ModuleId, MPIGraphSchemeModule> *modules) {
    return fruit::createComponent()
            .install(getSimpleControllerComponent)
            .bindInstance(*modules);
}

void MPIGraphSchemeStart(std::map<ModuleId, MPIGraphSchemeModule> *modules) {
    fruit::Injector<MPIController> injector(createMPIGraphScheme, &modules);
    MPIController *controller(injector);
    controller->start();
}

void MPIGraphSchemeInit(int *argc, char ***argv, int *provided_thread_level) {
    MPI_Init_thread(argc, argv, MPI_THREAD_FUNNELED, provided_thread_level);

    if (*provided_thread_level < MPI_THREAD_FUNNELED) {
        exit(-1);
    }
}

void MPIGraphSchemeFinalize() {
    MPI_Finalize();
}

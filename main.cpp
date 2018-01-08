
#include <fruit/fruit.h>
#include <iostream>
#include <mpi.h>
#include <Data.h>
#include "MPIController.h"
#include "SimpleMPIController.h"
#include "ModuleMapBuilder.h"

#define MASTER_NODE 0

fruit::Component<MPIController> getComponent(std::map<ModuleId, MPIGraphSchemeModule> *modules);

class PrintToStdProcedure : public Procedure {
public:
    PrintToStdProcedure(Tag tag, const std::map<int, Data> &data, ResultBuffer *resultBuffer) : Procedure(tag, data,
                                                                                                          resultBuffer) {}

    void run() override {
        const auto string = data.at(1);
        auto basic_string = std::string(string.array);
        std::cout << basic_string << std::endl;
    }
};

int main(int argc, char **argv) {

    std::cout << "Before start" << std::endl;

    int provided_thread_level;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided_thread_level);

    if (provided_thread_level < MPI_THREAD_FUNNELED) {
        exit(-1);
    }

    std::cout << "Provided Thread Level = " << provided_thread_level << std::endl;

    auto map = ModuleMapBuilder().add(
            MPIGraphSchemeModule(ModuleData(1, 1, true), Procedure::constructor<PrintToStdProcedure>())).build();

    fruit::Injector<MPIController> injector(getComponent, &map);
    MPIController *controller(injector);
    controller->start();
    MPI_Finalize();
    return 0;
}

fruit::Component<MPIController> getComponent(std::map<ModuleId, MPIGraphSchemeModule> *modules) {
    return fruit::createComponent()
            .install(getSimpleControllerComponent)
            .bindInstance(*modules);
}

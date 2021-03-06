
#include <iostream>
#include <mpi.h>
#include <Data.h>
#include <fstream>
#include "SimpleMPIController.h"
#include "ModuleMapBuilder.h"
#include "MPIGraphScheme.h"

#define MASTER_NODE 0

class PrintToStdProcedure : public Procedure {
public:
    PrintToStdProcedure(Tag tag, const std::map<int, Data> &data, ResultBuffer *resultBuffer) :
            Procedure(tag, data, resultBuffer) {}

    void run() override {
        const auto string = data.at(0);
        auto basic_string = std::string(string.array, static_cast<unsigned long>(string.length));
        std::cout << basic_string << std::endl;
        resultBuffer->put(new Result(tag, InputAddress(3, 0), Data(new char[1]{1}, 1)));
    }
};

class MiddleProcedure : public Procedure {
public:
    MiddleProcedure(Tag tag, const std::map<int, Data> &data, ResultBuffer *resultBuffer) :
            Procedure(tag, data, resultBuffer) {}

    void run() override {
        resultBuffer->put(new Result(tag, InputAddress(2, 0), Data(new char[1]{1}, 1)));
    }
};

class GoodByeProcedure : public Procedure {
public:
    GoodByeProcedure(Tag tag, const std::map<int, Data> &data, ResultBuffer *resultBuffer) : Procedure(tag, data,
                                                                                                       resultBuffer) {}

    void run() override {
        std::cout << "Program finished\n";
        resultBuffer->finish(tag);
    }
};

int main(int argc, char **argv) {

    int provided_thread_level;
    MPIGraphSchemeInit(&argc, &argv, &provided_thread_level);

    auto map = ModuleMapBuilder()
            .add(MPIGraphSchemeModule(ModuleData(1, 1, INITIAL), Procedure::constructor<PrintToStdProcedure>()))
            .add(MPIGraphSchemeModule(ModuleData(2, 1, FINAL), Procedure::constructor<GoodByeProcedure>()))
            .add(MPIGraphSchemeModule(ModuleData(3, 1), Procedure::constructor<MiddleProcedure>())).build();


    MPIGraphSchemeStart(&map);

    MPIGraphSchemeFinalize();
    return 0;
}
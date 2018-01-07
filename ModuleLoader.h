//
// Created by goto1134 on 07.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_MODULELOADER_H
#define GRAPH_SCHEME_CPP_MPI_MODULELOADER_H

#include <Module.h>
#include <vector>
#include <component.h>

class Module {
private:
public:
    const ModuleId id;
    const int inputCount;
    const bool isInititial;

    Module(const ModuleId id, const int inputCount, const bool isInititial = false) : id(id), inputCount(inputCount),
                                                                                      isInititial(isInititial) {}
};

class ModuleLoader {
public:
    virtual std::vector <Module> getModules() = 0;
};

#endif //GRAPH_SCHEME_CPP_MPI_MODULELOADER_H

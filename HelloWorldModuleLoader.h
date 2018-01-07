//
// Created by goto1134 on 07.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_MODULELOADERIMPL_H
#define GRAPH_SCHEME_CPP_MPI_MODULELOADERIMPL_H


#include <fruit/fruit.h>
#include "ModuleLoader.h"

class HelloWorldModuleLoader : public ModuleLoader {
public:
    INJECT(HelloWorldModuleLoader()) = default;

    std::vector<Module> getModules() override;
};

fruit::Component<ModuleLoader> getHelloWorldModuleLoader();

#endif //GRAPH_SCHEME_CPP_MPI_MODULELOADERIMPL_H

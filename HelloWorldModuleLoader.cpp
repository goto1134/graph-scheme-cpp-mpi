//
// Created by goto1134 on 07.01.18.
//

#include "HelloWorldModuleLoader.h"

std::vector<Module> HelloWorldModuleLoader::getModules() {
    std::vector<Module> modules;
    modules.emplace_back(1, 1);
    modules.emplace_back(2, 1);
    return modules;
}


fruit::Component<ModuleLoader> getHelloWorldModuleLoader() {
    return fruit::createComponent().bind<ModuleLoader, HelloWorldModuleLoader>();
}

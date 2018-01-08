//
// Created by goto1134 on 07.01.18.
//

#include "ModuleMapBuilder.h"

ModuleMapBuilder ModuleMapBuilder::add(MPIGraphSchemeModule moduleData) {
    result.insert(std::make_pair(moduleData.moduleData.id, moduleData));
    return *this;
}

std::map<ModuleId, MPIGraphSchemeModule> ModuleMapBuilder::build() {
    return result;
}

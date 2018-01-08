//
// Created by goto1134 on 08.01.18.
//

#include "MPIGraphSchemeModule.h"

MPIGraphSchemeModule::MPIGraphSchemeModule(const ModuleData &moduleData,
                                           const std::function<Procedure *(Tag, std::map<int, Data>,
                                                                           ResultBuffer *)> &procedureGenerator)
        : moduleData(moduleData), procedureGenerator(procedureGenerator) {}

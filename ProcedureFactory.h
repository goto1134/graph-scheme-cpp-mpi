//
// Created by goto1134 on 08.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_PROCEDUREFACTORY_H
#define GRAPH_SCHEME_CPP_MPI_PROCEDUREFACTORY_H

#include <vector>
#include <functional>
#include <unordered_map>
#include <fruit/fruit.h>
#include "MPIGraphSchemeModule.h"
#include <ResultBuffer.h>

class ProcedureFactory {
private:
    ResultBuffer *resultBuffer;
    std::unordered_map<int, std::function<Procedure *(int, std::map<int, Data>, ResultBuffer *)>> impl;

public:

    INJECT(ProcedureFactory(ResultBuffer * resultBuffer, std::map<ModuleId, MPIGraphSchemeModule> *
                                                         moduleVector)) : resultBuffer(resultBuffer) {
        for (auto &module: *moduleVector) {
            impl[module.first] = module.second.procedureGenerator;
        }
    }

    Procedure *instantiate(const int &name, int tag, std::map<int, Data> data);

};


fruit::Component<fruit::Required<ResultBuffer, std::map<ModuleId, MPIGraphSchemeModule>>,
        ProcedureFactory> getProcedureFactory();

#endif //GRAPH_SCHEME_CPP_MPI_PROCEDUREFACTORY_H

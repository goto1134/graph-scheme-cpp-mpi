//
// Created by goto1134 on 06.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_SIMPLEDATALISTENER_H
#define GRAPH_SCHEME_CPP_MPI_SIMPLEDATALISTENER_H

#include "Procdure.h"
#include <DataReadyListener.h>
#include <experimental/any>
#include <Tag.h>
#include <Module.h>
#include <map>

class SimpleDataListener : public DataReadyListener {
private:
public:
    void
    start(ModuleId moduleId, Tag tag, const std::map<int, Data> &data) override {
        const auto procedure = ProcedureFactory::instantiate(moduleId, tag, data);
        procedure->run();
    }
};

#endif //GRAPH_SCHEME_CPP_MPI_SIMPLEDATALISTENER_H

//
// Created by goto1134 on 06.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_SIMPLEDATALISTENER_H
#define GRAPH_SCHEME_CPP_MPI_SIMPLEDATALISTENER_H

#include <fruit/fruit.h>
#include <DataReadyListener.h>
#include "ProcedureFactory.h"

class SimpleDataListener : public DataReadyListener {
private:
    ProcedureFactory *procedureFactory;
public:
    INJECT(SimpleDataListener(ProcedureFactory * procedureFactory)) : procedureFactory(procedureFactory) {};

    void
    start(ModuleId moduleId, Tag tag, const std::map<int, Data> &data) override;
};

fruit::Component<fruit::Required<ProcedureFactory>, DataReadyListener> getSimpleDataListener();

#endif //GRAPH_SCHEME_CPP_MPI_SIMPLEDATALISTENER_H

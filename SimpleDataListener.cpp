//
// Created by goto1134 on 08.01.18.
//

#include <thread>
#include "SimpleDataListener.h"

fruit::Component<fruit::Required<ProcedureFactory>, DataReadyListener> getSimpleDataListener() {
    return fruit::createComponent().bind<DataReadyListener, SimpleDataListener>();
}

void SimpleDataListener::start(ModuleId moduleId, Tag tag, const std::map<int, Data> &data) {
    const auto procedure = procedureFactory->instantiate(moduleId, tag, data);
    std::thread t1(&Procedure::run, procedure);
}

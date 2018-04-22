//
// Created by goto1134 on 08.01.18.
//

#include "ProcedureFactory.h"

Procedure *ProcedureFactory::instantiate(const int &moduleId, int tag, std::map<int, Data> data) {
    auto it = impl.find(moduleId);
    return it == impl.end() ? nullptr : (it->second)(tag, data, resultBuffer);
}

fruit::Component<fruit::Required<ResultBuffer, std::map<ModuleId, MPIGraphSchemeModule>>,
        ProcedureFactory> getProcedureFactory() {
    return fruit::createComponent();
}

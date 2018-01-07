//
// Created by goto1134 on 06.01.18.
//

#ifndef GRAPH_SCHEME_CPP_MPI_PROCDURE_H
#define GRAPH_SCHEME_CPP_MPI_PROCDURE_H

#include <experimental/any>
#include <Tag.h>
#include <unordered_map>
#include <functional>
#include <vector>
#include <Module.h>
#include <map>
#include <iostream>
#include <Data.h>

class Procedure {
protected:
    const Tag tag;
    const std::map<int, Data> data;
public:
    Procedure(Tag tag, std::map<int, Data> data) : tag(tag), data(move(data)) {}

    virtual void run() = 0;
};

class ProcedureFactory {
public:
    typedef std::unordered_map<ModuleId, std::function<Procedure *(Tag,
                                                                   std::map<int, Data>)>> registry_map;

    // use this to instantiate the proper Derived class
    static Procedure *
    instantiate(const ModuleId &name, Tag tag, std::map<int, Data> data) {
        auto it = ProcedureFactory::registry().find(name);
        return it == ProcedureFactory::registry().end() ? nullptr : (it->second)(tag, data);
    }

    static registry_map &registry() {
        static registry_map impl;
        return impl;
    }

};

template<typename T>
struct ProcedureFactoryRegister {
    ProcedureFactoryRegister(ModuleId name) {
        ProcedureFactory::registry()[name] = [](Tag tag, std::map<int, Data> data) {
            return new T(tag, data);
        };
        std::cout << "registered" << std::endl;
    }
};

class TestProcedure : public Procedure {
private:
    static ProcedureFactoryRegister<TestProcedure> FactoryRegistrar;
public:
    TestProcedure(Tag tag, std::map<int, Data> data) : Procedure(tag, data) {
        std::cout << "created" << std::endl;
    }

    void run() override {
        std::cout << "run" << std::endl;
    }
};

ProcedureFactoryRegister<TestProcedure> TestProcedure::FactoryRegistrar(1);

#endif //GRAPH_SCHEME_CPP_MPI_PROCDURE_H

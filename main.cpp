
#include <fruit/fruit.h>
#include "MPIController.h"
#include "SimpleMPIController.h"
#include "HelloWorldModuleLoader.h"

#define MASTER_NODE 0
//
//class Module {
//private:
//public:
//    const ModuleId id;
//    const int inputCount;
//    const bool isInititial;
//
//    Module(const ModuleId id, const int inputCount, const bool isInititial = false) : id(id), inputCount(inputCount),
//                                                                                      isInititial(isInititial) {}
//};
//
//
//class ModuleLoader {
//public:
//    std::vector<Module> getModules() {
//        std::vector<Module> modules;
//        modules.emplace_back(1, 1);
//        modules.emplace_back(2, 1);
//        return modules;
//    }
//};
//
//std::map<int, ModuleId> getModuleMap(int world_size, int rank, ModuleLoader &loader);
//
//class Stringer {
//public:
//    virtual std::string getString() const = 0;
//};
//
//class HelloStringer : public Stringer {
//public:
//    INJECT(HelloStringer()) {}
//
//    std::string getString() const override {
//        return "Hello World";
//    }
//};
//
//class HelloWorlder {
//private:
//    const Stringer *stringer;
//public:
//    INJECT(HelloWorlder(const Stringer *stringer)) : stringer(stringer) {}
//
//    void print() {
//        std::cout << stringer->getString() << std::endl;
//    }
//};

//fruit::Component<HelloWorlder> getCheckedAdderComponent() {
//    return fruit::createComponent().bind<Stringer, HelloStringer>();
//}

fruit::Component<MPIController> getComponent();

int main(int argc, char **argv) {

//    MPI_Init(&argc, &argv);
//    // Get the number of processes
//    int world_size;
//    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
//    int rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    ModuleLoader loader;
//    std::map<int, ModuleId> moduleMap = getModuleMap(world_size, rank, loader);
//
//    if (rank == MASTER_NODE) {
//        for (auto moduleEntry : moduleMap) {
//            std::cout << moduleEntry.first << " : " << moduleEntry.second << std::endl;
//        }
//    }
//
//    MPI_Barrier(MPI_COMM_WORLD);
//
//    if (rank == MASTER_NODE) {
//        std::cout << world_size << std::endl;
//        std::cout << "Hello, World!" << std::endl;
//    }

    fruit::Injector<MPIController> injector(getComponent);
    MPIController *controller(injector);
    controller->start();
//    HelloWorlder *helloWorlder(injector);
//    helloWorlder->print();
//    MPI_Finalize();
    return 0;
}

fruit::Component<MPIController> getComponent() {
    return fruit::createComponent().install(getHelloWorldModuleLoader).install(getSimpleControllerComponent);
}
//
//std::map<int, ModuleId> getModuleMap(int world_size, int rank, ModuleLoader &loader) {
//    auto modules = loader.getModules();
//
//    const auto moduleCount = modules.size();
//    const auto intBufferLength = 2 * moduleCount;
//    auto buffer = new int[intBufferLength];
//    if (rank == MASTER_NODE) {
//        for (unsigned long i = 0; i < moduleCount; i++) {
//            const auto module = modules.at(i);
//            auto nodeId = i % world_size;
//            buffer[2 * i] = static_cast<int>(nodeId);
//            buffer[2 * i + 1] = module.id;
//        }
//
//    }
//    MPI_Bcast(buffer, (int) intBufferLength, MPI_INT, MASTER_NODE, MPI_COMM_WORLD);
//
//    std::map<int, ModuleId> moduleMap;
//    for (auto i = 0; i < moduleCount; i++) {
//        moduleMap.insert(std::make_pair(buffer[2 * i], buffer[2 * i + 1]));
//    }
//    return moduleMap;
//}




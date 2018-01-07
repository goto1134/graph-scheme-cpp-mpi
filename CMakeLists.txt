cmake_minimum_required(VERSION 3.9)
project(graph_scheme_cpp_mpi)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(Fruit REQUIRED)
find_package(MPI REQUIRED)
find_package(Boost REQUIRED)

include_directories(${FRUIT_INCLUDE_DIR} ${MPI_INCLUDE_PATH} ${BOOST_INCLUDE_PATH} /usr/include/fruit)

#include_directories(fruit-framework/include)
add_library(graph_scheme_cpp INTERFACE)
target_include_directories(graph_scheme_cpp INTERFACE graph-scheme-cpp/)


add_executable(graph_scheme_cpp_mpi main.cpp Procdure.h SimpleDataListener.h MPIController.h SimpleMPIController.cpp SimpleMPIController.h ModuleLoader.h HelloWorldModuleLoader.cpp HelloWorldModuleLoader.h)

#[[graph-scheme-cpp/DataBuffer.h graph-scheme-cpp/Input.h graph-scheme-cpp/Module.h graph-scheme-cpp/Tag.h graph-scheme-cpp/ProcedureFactory.h graph-scheme-cpp/Result.h graph-scheme-cpp/ResultBuffer.h]]

target_link_libraries(graph_scheme_cpp_mpi graph_scheme_cpp ${FRUIT_LIBRARIES} ${MPI_LIBRARIES} ${BOOST_LIBRARIES})

if (MPI_COMPILE_FLAGS)
    set_target_properties(graph_scheme_cpp_mpi PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif ()

if (MPI_LINK_FLAGS)
    set_target_properties(graph_scheme_cpp_mpi PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif ()


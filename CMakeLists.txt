cmake_minimum_required(VERSION 3.9)
project(graph_scheme_cpp_mpi)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
#add_subdirectory(fruit-framework)
find_package(Fruit REQUIRED)

include_directories(${FRUIT_INCLUDE_DIR})

add_library(graph_scheme_cpp INTERFACE)
target_include_directories(graph_scheme_cpp INTERFACE graph-scheme-cpp/)

add_executable(graph_scheme_cpp_mpi graph-scheme-cpp/DataBuffer.h graph-scheme-cpp/Input.h graph-scheme-cpp/Module.h graph-scheme-cpp/Tag.h main.cpp)
target_link_libraries(graph_scheme_cpp_mpi graph_scheme_cpp ${FRUIT_LIBRARIES})

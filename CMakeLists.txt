cmake_minimum_required(VERSION 3.15)
project(queens_solver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(pybind11 REQUIRED)

pybind11_add_module(queens_solver
    src/bindings.cpp
    src/queensSolver.cpp
    src/board.cpp
    src/queens.cpp
)
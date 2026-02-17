#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <fstream>
#include <vector>
#include <string>

#include "board.h"
#include "queensSolver.h"

namespace py = pybind11;

std::vector<std::vector<char>> loadBoardFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) throw std::runtime_error("File tidak ditemukan");

    std::vector<std::vector<char>> tempBoard;
    std::string line;

    while (getline(file, line))
    {
        std::vector<char> row;
        for (char c : line) row.push_back(c);
        tempBoard.push_back(row);
    }

    file.close();
    return tempBoard;
}

SolveResult solveBoard(const std::vector<std::vector<char>>& boardInput,
    bool optimized,
    py::function callback = py::none())
{
    Board board;
    board.setBoard(boardInput);

    if (!board.isValidBoard()) throw std::runtime_error("Board tidak valid");

    std::function<void(const std::vector<std::vector<char>>&)> stepCallback = nullptr;

    if (!callback.is_none())
    {
        stepCallback = [callback](const std::vector<std::vector<char>>& state)
        {
            py::gil_scoped_acquire acquire;
            callback(state);
        };
    }

    QueensSolver solver(board, optimized, stepCallback);
    return solver.solve();
}

PYBIND11_MODULE(queens_solver, m)
{
    py::class_<SolveResult>(m, "SolveResult")
        .def_readonly("solution", &SolveResult::solution)
        .def_readonly("countCases", &SolveResult::countCases)
        .def_readonly("durationMs", &SolveResult::durationMs)
        .def_readonly("board", &SolveResult::board)
        .def_readonly("found", &SolveResult::found);

    m.def("loadBoardFile", &loadBoardFile);
    m.def("solveBoard", &solveBoard,
        py::arg("boardInput"),
        py::arg("optimized") = true,
        py::arg("callback") = py::none());
}

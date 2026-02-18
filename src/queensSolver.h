#ifndef QUEENSSOLVER_H
#define QUEENSSOLVER_H

#include <chrono>
#include <vector>
#include <iostream>
#include <functional>
#include <thread>

#include "board.h"
#include "queens.h"

using namespace std;

struct SolveResult
{
    vector<vector<char>> solution;
    vector<vector<char>> board;
    long long countCases;
    long long durationMs;
    bool found;
};

class QueensSolver
{
private:
    const Board &board;
    vector<vector<char>> solution;
    vector<Queen> queens;
    vector<int> currentPlacement;
    function<void(const vector<vector<char>> &)> stepCallback;

    int n;
    long long countCases = 0, cnt = 0;
    bool found = false;
    bool optimized;
    
    bool isSafe(int row, int col);
    bool isValidPlacement();
    void bruteforceopt(int row);
    void bruteforce(int row);

public:
    QueensSolver(const Board &b, bool optimized, function<void(const vector<vector<char>> &)> callback = nullptr);
    SolveResult solve();
};

#endif
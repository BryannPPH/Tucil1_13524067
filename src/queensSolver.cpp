#include "queensSolver.h"

QueensSolver::QueensSolver(const Board &b, bool optimized, function<void(const vector<vector<char>> &)> callback) : board(b), optimized(optimized), stepCallback(callback)
{
    n = board.getSize();
    solution = board.getBoard();
    queens.resize(n);
    currentPlacement.resize(n);
}

bool QueensSolver::isSafe(int row, int col)
{
    for (int r = 0; r < row; r++)
    {
        int c = currentPlacement[r];
        //cek sama kolom
        if (c == col) return false;
        // Cek tetangga
        if (abs(r - row) <= 1 && abs(c - col) <= 1) return false;
        // Cek sama warna
        if (board.getElmt(r, c) == board.getElmt(row, col)) return false;
    }

    return true;
}

bool QueensSolver::isValidFullPlacement()
{
    for (int r1 = 0; r1 < n; r1++)
    {
        for (int r2 = r1 + 1; r2 < n; r2++)
        {
            int c1 = currentPlacement[r1];
            int c2 = currentPlacement[r2];

            if (c1 == c2) return false;

            if (abs(r1 - r2) <= 1 && abs(c1 - c2) <= 1) return false;

            if (board.getElmt(r1, c1) == board.getElmt(r2, c2)) return false;
        }
    }
    return true;
}

void QueensSolver::bruteforceopt(int row)
{
    if (found) return;

    if (row == n)
    {
        found = true;
        if (stepCallback) stepCallback(solution);
        return;
    }

    for (int col = 0; col < n; col++)
    {
        countCases++;
        cnt++;

        if (!isSafe(row, col)) continue;

        currentPlacement[row] = col;
        solution[row][col] = '#';

        if (stepCallback && cnt % 50 == 0) stepCallback(solution);

        bruteforceopt(row + 1);

        if (found) return;

        solution[row][col] = '.';

        if (stepCallback && cnt % 50 == 0) stepCallback(solution);
    }
}

void QueensSolver::bruteforce(int row)
{
    if (found) return;

    if (row == n)
    {
        countCases++;

        if (isValidFullPlacement())
        {
            found = true;

            for (int r = 0; r < n; r++) solution[r][currentPlacement[r]] = '#';

            if (stepCallback) stepCallback(solution);
        }
        return;
    }

    for (int col = 0; col < n; col++)
    {
        currentPlacement[row] = col;
        solution[row][col] = '#';

        cnt++;

        // if (stepCallback && cnt % 50000 == 0) stepCallback(solution);

        bruteforce(row + 1);

        if (found) return;

        solution[row][col] = '.';

        // if (stepCallback && cnt % 50000 == 0) stepCallback(solution);
    }
}

SolveResult QueensSolver::solve()
{
    int distinctColors = board.countDistinctColors();
    if (distinctColors != n)
    {
        SolveResult result;
        result.countCases = 0;
        result.durationMs = 0;
        result.found = false;
        result.board = board.getBoard();
        result.solution = {};
        return result;
    }

    auto start = std::chrono::high_resolution_clock::now();

    if (optimized) bruteforceopt(0);
    else bruteforce(0);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    SolveResult result;
    result.countCases = countCases;
    result.durationMs = duration.count();
    result.found = found;
    result.board = board.getBoard();

    if (found) result.solution = solution;
    else result.solution = {};

    return result;
}
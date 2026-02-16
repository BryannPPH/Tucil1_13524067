#ifndef QUEENSSOLVER_H
#define QUEENSSOLVER_H

#include "board.h"
#include "queens.h"
#include <chrono>
#include <vector>
#include <iostream>

using namespace std;

class QueensSolver
{
private:
    const Board &board;
    vector<vector<char>> solution;
    vector<Queen> queens;

    int n;
    long long countCases = 0;
    bool found = false;
    vector<int> currentPlacement;

    bool isValidPlacement(const vector<int> &placement)
    {
        vector<bool> usedCols(n, false);
        for (int row = 0; row < n; row++)
        {
            int col = placement[row];
            if (usedCols[col]) return false;
            usedCols[col] = true;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int row1 = i, col1 = placement[i];
                int row2 = j, col2 = placement[j];

                if (abs(row1 - row2) <= 1 && abs(col1 - col2) <= 1)
                {
                    return false;
                }
            }
        }

        vector<char> usedColors;
        for (int row = 0; row < n; row++)
        {
            char color = board.getElmt(row, placement[row]);

            for (char c : usedColors)
            {
                if (c == color) return false;
            }
            usedColors.push_back(color);
        }

        return true;
    }

    void bruteForce(int row)
    {
        if (found) return;

        if (row == n)
        {
            countCases++;
            
            if (isValidPlacement(currentPlacement))
            {
                found = true;
                for (int r = 0; r < n; r++)
                {
                    solution[r][currentPlacement[r]] = '#';
                    queens[r].setPosition(r, currentPlacement[r]);
                }
            }
            return;
        }

        for (int col = 0; col < n; col++)
        {
            currentPlacement[row] = col;
            bruteForce(row + 1);
        }
    }

public:

    QueensSolver(const Board &b) : board(b)
    {
        n = board.getSize();
        solution = board.getBoard();
        queens.resize(n);
        currentPlacement.resize(n);
    }

    void solve()
    {
        auto start = chrono::high_resolution_clock::now();

        bruteForce(0);

        auto end = chrono::high_resolution_clock::now();

        auto duration =
            chrono::duration_cast<chrono::milliseconds>(end - start);

        if (found)
        {
            cout << "Solusi ditemukan:\n";
            board.printBoard(solution);
        }
        else
        {
            cout << "Tidak ada solusi.\n";
        }

        cout << "Waktu pencarian: " << duration.count() << " ms\n";
        cout << "Banyak kasus ditinjau: " << countCases << " kasus\n";
    }
};

#endif

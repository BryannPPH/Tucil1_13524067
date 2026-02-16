#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "board.h"
#include "queensSolver.h"

using namespace std;

int main()
{
    string filename;
    cout << "Masukkan nama file input: ";
    cin >> filename;

    string path = "test/" + filename;

    ifstream file(path);

    if (!file.is_open())
    {
        cout << "File tidak ditemukan di folder test.\n";
        return 0;
    }

    vector<vector<char>> tempBoard;
    string line;

    while (getline(file, line))
    {
        vector<char> row;

        for (char c : line)
        {
            row.push_back(c);
        }

        tempBoard.push_back(row);
    }

    file.close();

    Board board;
    board.setBoard(tempBoard);

    if (!board.isValidBoard())
    {
        cout << "Board tidak valid.\n";
        return 0;
    }

    cout << "\nBoard awal:\n";
    board.printBoard(board.getBoard());

    QueensSolver solver(board);
    solver.solve();

    return 0;
}

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>

using namespace std;

class Board
{

private:
    vector<vector<char>> board;
    int size = 0;

public:
    Board(){}

    void setBoard(const vector<vector<char>> &inputBoard)
    {
        board = inputBoard;
        size = board.size();
    }

    bool isSquare() const
    {
        for (int i = 0; i < size; i++) 
        {
            if ((int)board[i].size() != size) return false;
        }

        return true;
    }

    bool isValidBoard() const
    {
        if (size == 0) return false;

        if (!isSquare()) return false;

        return true;
    }

    int getSize() const
    {
        return size;
    }

    char getElmt(int row, int col) const
    {
        return board[row][col];
    }

    const vector<vector<char>> &getBoard() const
    {
        return board;
    }

    void printBoard(const vector<vector<char>> &board) const
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << board[i][j];
            }
            cout << '\n';
        }
        cout << '\n';
    }
};

#endif

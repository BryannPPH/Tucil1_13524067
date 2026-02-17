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
    Board();
    void setBoard(const vector<vector<char>> &inputBoard);
    bool isSquare() const;
    bool isValidBoard() const;
    int getSize() const;
    char getElmt(int row, int col) const;
    const vector<vector<char>> &getBoard() const;
};

#endif
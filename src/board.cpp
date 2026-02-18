#include "board.h"

Board::Board() {}

void Board::setBoard(const vector<vector<char>> &inputBoard)
{
    board = inputBoard;
    size = board.size();
}

bool Board::isSquare() const
{
    for (int i = 0; i < size; i++)
    {
        if ((int)board[i].size() != size) return false;
    }
    return true;
}

bool Board::isValidBoard() const
{
    if (size == 0) return false;
    if (!isSquare()) return false;

    return true;
}

int Board::getSize() const
{
    return size;
}

char Board::getElmt(int row, int col) const
{
    return board[row][col];
}

const vector<vector<char>> &Board::getBoard() const
{
    return board;
}

int Board::countDistinctColors() const
{
    std::unordered_set<char> colors;
    for (const auto &row : board)
    {
        for (char c : row) colors.insert(c);
    }
    return static_cast<int>(colors.size());
}
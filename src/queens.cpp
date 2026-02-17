#include "queens.h"

Queen::Queen() : row(-1), col(-1) {}

Queen::Queen(int r, int c)
{
    row = r;
    col = c;
}

int Queen::getRow() const
{
    return row;
}

int Queen::getCol() const
{
    return col;
}

void Queen::setPosition(int r, int c)
{
    row = r;
    col = c;
}
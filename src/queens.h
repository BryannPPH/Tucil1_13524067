#ifndef QUEENS_H
#define QUEENS_H

class Queen
{
private:
    int row;
    int col;

public:
    Queen() : row(-1), col(-1) {}

    Queen(int r, int c)
    {
        row = r;
        col = c;
    }

    int getRow() const
    {
        return row;
    }

    int getCol() const
    {
        return col;
    }

    void setPosition(int r, int c)
    {
        row = r;
        col = c;
    }
};

#endif

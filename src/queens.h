#ifndef QUEENS_H
#define QUEENS_H

class Queen
{
private:
    int row;
    int col;

public:
    Queen();
    Queen(int r, int c);
    int getRow() const;
    int getCol() const;
    void setPosition(int r, int c);
};

#endif
#include "Position.h"

Position::Position(int row, int col)
{
    this->row = row;
    this->col = col;
}

Position::Position(std::string pos)
{
    *this = pos;
}

Position& Position::operator=(std::string pos)
{
    if (pos.size() == 2)
    {
        this->row = pos[1] - '0' - 1;
        this->col = pos[0] - 'a';
    }
    return *this;
}

Position& Position::operator=(Position& other)
{
    this->row = other.row;
    this->col = other.col;
    return *this;
}

bool Position::operator==(std::string otherPos) const
{
    Position other = otherPos;
    return this->row == other.row && this->col == other.col;
}

bool Position::operator!=(std::string otherPos) const
{
    Position other = otherPos;
    return !(this->row == other.row && this->col == other.col);
}

bool Position::operator==(Position other) const
{
    return this->row == other.row && this->col == other.col;
}

bool Position::operator!=(Position other) const
{
    return !(this->row == other.row && this->col == other.col);
}
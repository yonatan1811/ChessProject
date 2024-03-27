#pragma once

#include <iostream>

struct Position
{
    int row;
    int col;

    Position(int row, int col);
    Position(std::string pos);
    Position& operator=(std::string pos);
    Position& operator=(Position& other);
    bool operator==(std::string pos) const;
    bool operator!=(std::string otherPos) const;
    bool operator==(Position other) const;
    bool operator!=(Position other) const;
};

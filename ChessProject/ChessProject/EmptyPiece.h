#pragma once
#include "Piece.h"

#define EMPTY_CHAR '#'

class EmptyPiece : public Piece
{
public:

	EmptyPiece(const Position pos);
	~EmptyPiece();

	char getType() const override;
	std::vector<Position> returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const override;
};

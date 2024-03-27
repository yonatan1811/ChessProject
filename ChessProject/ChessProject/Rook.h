#pragma once
#include "ComplicatedPiece.h"

#define ROOK_CHAR 'R'

class Rook : public ComplicatedPiece
{
public:
	// ctor, dtor
	Rook(Color color, const Position pos);
	~Rook();

	// getter
	char getType() const override;

	// override methods
	MoveCode canMove(const Position postion , Piece* board[BOARD_SIZE][BOARD_SIZE]) const override;
	std::vector<Position> returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const override;
};
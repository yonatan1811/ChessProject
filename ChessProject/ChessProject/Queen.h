#pragma once

#include "Piece.h"
#define QUEEN_CHAR 'Q'


class Queen : public Piece
{
public:
	// ctor, dtor
	Queen(Color color, const Position Pos);
	~Queen();

	// getter
	char getType() const override;
	
	// override methods
	MoveCode canMove(const Position postion, Piece* board[BOARD_SIZE][BOARD_SIZE]) const override; //we need to get position here to check if its valid
	std::vector<Position> returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const override;

};
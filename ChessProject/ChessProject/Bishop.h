#pragma once
#include "Piece.h"

#define BISHOP_CHAR 'B'

class Bishop : public Piece
{
public:
	// ctor and dtor
	Bishop(Color color, const Position Pos);
	~Bishop();

	// getter
	char getType() const override;

	// override methods
	MoveCode canMove(const Position postion, Piece* board[BOARD_SIZE][BOARD_SIZE]) const override; //we need to get position here to check if its valid
	std::vector<Position> returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const override;
};


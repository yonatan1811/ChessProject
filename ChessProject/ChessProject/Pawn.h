#pragma once
#include "ComplicatedPiece.h"

#define PAWN_CHAR 'P'

class Pawn : public ComplicatedPiece
{
public:
	Pawn(Color color, const Position pos);
	~Pawn();

	// getter
	char getType() const override;

	// override methods
	virtual MoveCode canMove(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const override;
	std::vector<Position> returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const override;
};
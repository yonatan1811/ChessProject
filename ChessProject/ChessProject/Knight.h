#pragma once
#include "Piece.h"


#define KNIGHT_CHAR 'N'


class Knight : public Piece
{
public:

	Knight(Color color , const Position pos);
	~Knight();

	// getter
	char getType() const override;

	// override methods
	virtual MoveCode canMove(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const override;
	std::vector<Position> returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const override;


};

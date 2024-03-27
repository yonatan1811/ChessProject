#pragma once
#include "ComplicatedPiece.h"

#define KING_CHAR 'K'

// enum CheckCode { NO_CHECK, CHECK, MATE };

class King : public ComplicatedPiece
{
public:
	// i think this is how we should implement all piece ctors
	King(Color color, const Position pos);
	~King();

	// getter
	char getType() const override;

	// override methods
	MoveCode canMove(const Position postion , Piece* board[BOARD_SIZE][BOARD_SIZE]) const override;
	std::vector<Position> returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const override;

	// king special attributes
 	// a function that will check if the king is in check
	std::vector<Piece*> inCheck(Piece* board[BOARD_SIZE][BOARD_SIZE], std::vector<Piece*> enemyPieces) const;
	 // a castle is when the king is trying to move 2 pieces to his side. and switching with the rook
	bool castling(Position position  , Piece* board[BOARD_SIZE][BOARD_SIZE])const;
};
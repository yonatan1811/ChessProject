#include "EmptyPiece.h"

EmptyPiece::EmptyPiece(const Position pos) 
	: Piece::Piece(Color::none , EMPTY_CHAR , pos) 
{
}

EmptyPiece::~EmptyPiece()
{
}

char EmptyPiece::getType() const
{
	return EMPTY_CHAR;
}

std::vector<Position> EmptyPiece::returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	return std::vector<Position>();
}
#include "Knight.h"

Knight::Knight(Color color, const Position pos) 
	: Piece(color  , KNIGHT_CHAR + ((color == white) ? (0) : (BLACK_WHITE_DIFFERENCE)), pos)
{
}



Knight::~Knight()
{
}


char Knight::getType() const
{
	return KNIGHT_CHAR;
}


/*
	checks if the move we got is legal
	a knight can only move 2 steps forward and one left or right to every direction you look at
*/
MoveCode Knight::canMove(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const 
{
	MoveCode code = Piece::canMove(pos, board);
	if (code)
	{
		return code;
	}
	int diffRows = abs(_pos.row - pos.row);
	int diffCols = abs(_pos.col - pos.col);
	if (!((diffCols == 1 && diffRows == 2) || (diffCols == 2 && diffRows == 1))) // changed the if statement here
	{
		return MoveCode::FAIL_illegal_move;
	}
	return MoveCode::ACK;
}

std::vector<Position> Knight::returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	std::vector<Position> squaresBetween;
	squaresBetween.push_back(_pos);
	return squaresBetween;
}
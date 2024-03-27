#include "Queen.h"


Queen::Queen(Color color, const Position pos) : Piece(color , QUEEN_CHAR + ((color == white) ? (0) : (BLACK_WHITE_DIFFERENCE)) , pos)
{}

Queen::~Queen()
{}

/*
* a queen can move either on the y and x axis or in both.
* as a result we will have to check both diagonal and cross
*/
MoveCode Queen::canMove(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const //we need to get position here to check if its valid
{
	MoveCode code = Piece::canMove(pos, board);
	if (code)
	{
		return code;
	}

	if (!(this->checkCross(pos, board) || this->checkDiagonal(pos, board)))
	{
		return MoveCode::FAIL_illegal_move;
	}
	return MoveCode::ACK;
}

char Queen::getType() const
{
	return QUEEN_CHAR;
}

std::vector<Position> Queen::returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	std::vector<Position> squaresBetween;
	if (!(squaresBetween = this->returnCrossSquares(pos, board)).empty() 
	 || !(squaresBetween = this->returnDiagonalSquares(pos, board)).empty())
	{
	}
	return squaresBetween;
}
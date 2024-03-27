#include "Bishop.h"


Bishop::Bishop(Color color, const Position pos) : Piece(color , BISHOP_CHAR + ((color == white) ? (0) : (BLACK_WHITE_DIFFERENCE)), pos)
{
}

Bishop::~Bishop()
{
}


char Bishop::getType() const 
{
	return BISHOP_CHAR;
}

MoveCode Bishop::canMove(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const //we need to get position here to check if its valid
{
	MoveCode code = Piece::canMove(pos, board);
	if (code)
	{
		return code;
	}
	if (!this->checkDiagonal(pos , board))
	{
		return MoveCode::FAIL_illegal_move;
	}
	return MoveCode::ACK;
}

std::vector<Position> Bishop::returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	return this->returnDiagonalSquares(pos, board);
}
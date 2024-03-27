#include "Rook.h"

Rook::Rook(Color color, const Position pos)
	: ComplicatedPiece(color , ROOK_CHAR + ((color == white) ? (0) : (BLACK_WHITE_DIFFERENCE)), pos)
{
}

Rook::~Rook()
{
}

char Rook::getType() const 
{
	return ROOK_CHAR;
}

MoveCode Rook::canMove(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const //we need to get pos here to check if its valid
{
	MoveCode code = Piece::canMove(pos, board);
	if (code)
	{
		return code;
	}
	if (!this->checkCross(pos, board))
	{
		return MoveCode::FAIL_illegal_move;
	}

	return MoveCode::ACK;
}

std::vector<Position> Rook::returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	return this->returnCrossSquares(pos, board);
}
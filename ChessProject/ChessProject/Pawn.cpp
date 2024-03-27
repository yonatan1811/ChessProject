#include "Pawn.h"

Pawn::Pawn(Color color, const Position pos)
	: ComplicatedPiece(color, PAWN_CHAR + ((color == white) ? (0) : (BLACK_WHITE_DIFFERENCE)), pos)
{
}

Pawn::~Pawn()
{

}

char Pawn::getType() const 
{
	return PAWN_CHAR;
}


/*
* a pawn can only move 1 step forward (if he didnt move at all.) can eat in diagonal
*/
MoveCode Pawn::canMove(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	MoveCode code = Piece::canMove(pos, board);
	if (code)
	{
		return code;
	}
	int col = pos.col, row = pos.row, oldCol = _pos.col, oldRow = _pos.row, 
		moveRowBy = (this->getColor() == white) ? (1) : (-1);
	Piece* destPiece = board[row][col];

	if	(!(destPiece->getColor() == Color::none &&
			(col == oldCol &&
				((row - oldRow == moveRowBy) ||
				(!_hasMoved && (row - oldRow == 2 * moveRowBy) && this->checkCross(pos, board)))
			))
		&& !((abs(col - oldCol) == 1) && ((row - oldRow == moveRowBy)) && (destPiece->getColor() == !this->getColor()))
		)
	{
		return MoveCode::FAIL_illegal_move;
	}
	return ACK;
}

std::vector<Position> Pawn::returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	std::vector<Position> squaresBetween;
	squaresBetween.push_back(_pos);
	return squaresBetween;
}
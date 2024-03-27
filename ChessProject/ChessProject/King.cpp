#include "King.h"

King::King(Color color, const Position pos)
	: ComplicatedPiece(color, KING_CHAR + ((color == white) ? (0) : (BLACK_WHITE_DIFFERENCE)), pos)
	// if color == white, typeChar = 'K' 
	// if color == black, typeChar = 'K' + BLACK_WHITE_DIFFERENCE = 'k'
	// the char is always constant (depending of the color) so it shouldn't be passed as a parameter
{
}

King::~King()
{

}

char King::getType() const 
{
	return KING_CHAR;
}

MoveCode King::canMove(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	MoveCode code = Piece::canMove(pos, board);
	int row = _pos.row, col = _pos.col, newRow = pos.row, newCol = pos.col;
	if (code)
	{
		return code;
	}
	if (this->castling(pos , board))
	{
		return MoveCode::CASTLE;
	}
	if 	(!(((row - newRow >= -1) && (row - newRow <= 1)) && ((col - newCol >= -1) && (row - newRow <= 1))))
	{
		return MoveCode::FAIL_illegal_move;
	}
	return MoveCode::ACK;
}

std::vector<Piece*> King::inCheck(Piece* board[BOARD_SIZE][BOARD_SIZE], std::vector<Piece*> enemyPieces) const// a function that will check if the king is in check.
{
	std::vector<Piece*> checkingPieces;
	Piece* p = nullptr;
	for (int i = 0; i < enemyPieces.size(); i++)
	{
		p = enemyPieces[i];
		if (!p->canMove(this->_pos, board))
		{
			checkingPieces.push_back(p);
		}
	}
	return checkingPieces;
}

// a castle is when the king is trying to move 2 pieces to his side. and switching with the rook
bool King::castling(Position pos , Piece* board[BOARD_SIZE][BOARD_SIZE]) const // a2 a= col and 2 row? 
{
	int row = 0, col = 0 , kingsCol = 0 , kingsRow = 0;
	row = pos.row, col = pos.col , kingsCol = _pos.col , kingsRow = _pos.row;
	Position newPos = Position(pos.row, pos.col + 2); // if its castling to the right , moving twice to the right
	Position leftRook = Position(pos.row, pos.col - 2); // castle for the left
	Piece* nearRook = nullptr;
	if (_hasMoved == true || abs(col - kingsCol) == 1 || kingsCol ==col || _pos == pos) // the castle can only be on the sides so we will only check on the rows and if both pieces hasnt move
	{
		return false; // no moving on the x axis
	}
	if (nearRook == nullptr)
	{
		return true;
	}
	if (!this->checkCross(pos, board))
	{
		return false;
	}
	return true;
}

std::vector<Position> King::returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	return std::vector<Position>();
}
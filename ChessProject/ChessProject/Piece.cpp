#include "Piece.h"


Piece::Piece(Color color, char PieceType, Position pos) 
	: _color(color) , _pieceType(PieceType), _pos(pos)
{
}

Piece::~Piece()
{
}

//just a function to get the string that represents the position
Position Piece::getPos() const
{
	return _pos;
}

//a function to get the color
Color Piece::getColor() const
{
	return _color;
}

char Piece::getPieceChar() const
{

	return _pieceType;
}

/*
	function recieves a position and a board and checks if the Piece instance that called it can move to the position
	input: the dest position, the board
	output: the code of the move, to know what is wrong with the move or 
*/
MoveCode Piece::canMove(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	int col = pos.col, row = pos.row;
	if (col >= BOARD_SIZE || col < 0 || row >= BOARD_SIZE || row < 0) // check that the position is in the board's bounds
	{
		return MoveCode::FAIL_invalid_square;
	}
	if (pos == _pos) // check if the positions are equal
	{
		return MoveCode::FAIL_dest_equals_src;
	}
	if (board[row][col]->getColor() == _color) // check that the destination doesn't contain friends piece
	{
		return MoveCode::FAIL_dest_contains_friend_piece;
	}
	return MoveCode::ACK; // if nothing went wrong, return acknoledgement
}

/*
	function recieves a dest position and checks if there are any pieces between the instance's position and the dest position,
	checks in a diagonal path, meaning both the row and col change
	input: the dest position, the board
	output: true if no pieces on the diagonal path, false if the path is blocked or if the path between the 
	instance's position and the dest position is not a diagonal path
*/
bool Piece::checkDiagonal(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	int oldRow = _pos.row, oldCol = _pos.col, newRow = pos.row, newCol = pos.col,
		addRow = 0, addCol = 0;

	Position currentPosition = this->_pos;
	if (abs(oldRow - newRow) != abs(oldCol - newCol) || pos == _pos) // a diagonal move has to have the same difference in the rows and cols 
	{
		return false;
	}
	(oldRow > newRow) ? (addRow = -1) : (addRow = 1);
	(oldCol > newCol) ? (addCol = -1) : (addCol = 1);
	
	for (int i = oldRow + addRow, j = oldCol + addCol; i != newRow && j != newCol ; i+= addRow , j+= addCol)
	{
		if (board[i][j]->getType() != '#')
		{
			return false;
		}
	}
	
	return true; // just for now
}

/*
	function recieves a dest position and checks if there are any pieces between the instance's position and the dest position,
	checks in a cross path, meaning either the col changes or the row changes, but not both.
	input: the dest position, the board
	output:  true if no pieces on the cross path, false if the path is blocked or if the path between the 
	instance's position and the dest position is not a straight path
*/
bool Piece::checkCross(Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	int oldRow = _pos.row, oldCol = _pos.col, newRow = pos.row, newCol = pos.col, target = 0, start = 0;
	if (oldRow == newRow)
	{
		target = oldCol, start = newCol;
		if (newCol > oldCol)
		{
			target = newCol, start = oldCol;
		}
		for (int i = start + 1; i < target; i++)//added one to start , so we wont count the current piece
		{
			if (board[oldRow][i]->getType() != '#') // changed the board to be an empty pieces instead of nulls.
			{
				return false;
			}
		}
	}
	else if (oldCol == newCol)
	{
		target = oldRow, start = newRow;
		if (newRow > oldRow)
		{
			target = newRow, start = oldRow;
		}
		for (int i = start + 1; i < target; i++) //added one to start , so we wont count the current piece
		{
			if (board[i][oldCol]->getType() != '#')// changed the board to be an empty pieces instead of nulls.
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

/*
	function recieves a dest position and checks if there are any pieces between the instance's position and the dest position,
	checks in a diagonal path, meaning both the row and col change
	input: the dest position, the board
	output: vector of all the squares between the src and the dest (including the piece's original sqaure) if the path is valid,
	else an empty vector
*/
std::vector<Position> Piece::returnDiagonalSquares(Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const // we will get the src pos and dst pos and check if there is a piece in between (true if no piece in between else false)
{
	std::vector<Position> positions;
	int oldRow = _pos.row, oldCol = _pos.col, newRow = pos.row, newCol = pos.col,
		addRow = 0, addCol = 0;

	if (abs(oldRow - newRow) != abs(oldCol - newCol) || pos == _pos) // if move is invalid
	// a diagonal move has to have the same difference in the rows and cols 
	{
		return positions;
	}
	(oldRow > newRow) ? (addRow = -1) : (addRow = 1);
	(oldCol > newCol) ? (addCol = -1) : (addCol = 1);
	
	positions.push_back(this->_pos);
	for (int i = oldRow + addRow, j = oldCol + addCol; i != newRow && j != newCol ; i+= addRow , j+= addCol)
	{
		if (board[i][j]->getType() != '#')  // if the Position is not empty
		{
			positions.clear(); // clear vector
			return positions; // return empty vector
		}
		positions.push_back(Position(i, j)); // if the Position is valid (doesn;t contain another piece) add position to the vector
	}
	
	return positions; // just for now
}

/*
	function recieves a dest position and checks if there are any pieces between the instance's position and the dest position,
	checks in a cross path, meaning either the col changes or the row changes, but not both.
	input: the dest position, the board
	output: vector of all the squares between the src and the dest (including the piece's original sqaure) if the path is valid,
	else an empty vector
*/
std::vector<Position> Piece::returnCrossSquares(Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const
{
	std::vector<Position> positions;
	int oldRow = _pos.row, oldCol = _pos.col, newRow = pos.row, newCol = pos.col, moveRowBy = 0, moveColBy = 0;
	bool useCol = false;

	if ((oldCol == newCol && oldRow == newRow) || this->Piece::canMove(pos, board)) // if move is invalid
	{
		return positions; // returns empty vector
	}
	if (oldCol == newCol) // if oldCol is equal to newCol, you only need to move the row
	{
		moveRowBy = (oldRow > newRow) ? (-1) : (1);
	}
	else if (oldRow == newRow) // if oldRow is equal to newRow, you only need to move the col
	{
		useCol = true;
		moveColBy = (oldCol > newCol) ? (-1) : (1);
	}

	positions.push_back(this->_pos);
	for (
			int col = oldCol + moveColBy, row = oldRow + moveRowBy;
			(useCol) ? (col != newCol) : (row != newRow); 
			col += moveColBy, row += moveRowBy
		)
	{
		if (board[row][col]->getType() != '#') // if the Position is not empty
		{
			positions.clear(); // clear vector
			return positions; // return empty vector
		}
		positions.push_back(Position(row, col)); // if the Position is valid (doesn;t contain another piece) add position to the vector
	}
	
	return positions; // returns a vector if 
}

// function to change the current position of the piece
void Piece::move(Position pos)
{
	this->_pos = pos;
}


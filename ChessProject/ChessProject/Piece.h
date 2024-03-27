#pragma once
#include "stdafx.h"
#include "Position.h"

#define COLORS 2
#define BOARD_SIZE 8
#define BLACK_WHITE_DIFFERENCE 'a' - 'A' // the difference between big letters and small letters

using std::string;

enum Color
{
	white,
	black,
	none
};

enum MoveCode
{
	ACK, ACK_check, // success codes
	FAIL_square_does_not_contain_friend_piece, FAIL_dest_contains_friend_piece,
	FAIL_move_leads_to_check, FAIL_invalid_square, FAIL_illegal_move, FAIL_dest_equals_src,
	CHECKMATE  , CASTLE// end of game
	// EAT // no need for this
};

enum PieceColomn { rook1, knight1, bishop1, queen, king, bishop2, knight2, rook2 };


/*
	The parent class of all the different types of piece.
	Manages checking if a piece can move, if a row or diagonal is clear of pieces
*/
class Piece
{
public:
	// parent ctor, dtor
	Piece(Color color, char PieceType, Position);
	virtual ~Piece();
	
	// other functions, mainly to check if the move is valid or leads to check/checkmate
	virtual MoveCode canMove(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const;

	// function recieves a position and returns all sqaures between current position and dest position if path valid, else returns empty vector
	virtual std::vector<Position> returnSquaresBetween(const Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const = 0;

	// setters
	virtual void move(Position pos); // changes the position

	// getters
	Position getPos() const;
	Color getColor() const;
	virtual char getType() const = 0; // returns the char of the specific subclass (always returns a capital letter)
	char getPieceChar() const; // returns the char of the piece, capital if the color is white, otherwise non-capital letters
	
private:
	char _pieceType;
	Color _color;

protected:
	Position _pos;

	// protected methods, to check for valid moves and for checks/checkmates
	bool checkDiagonal(const Position, Piece* board[BOARD_SIZE][BOARD_SIZE]) const;
	bool checkCross(const Position, Piece* board[BOARD_SIZE][BOARD_SIZE]) const;
	std::vector<Position> returnCrossSquares(Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const;
	std::vector<Position> returnDiagonalSquares(Position pos, Piece* board[BOARD_SIZE][BOARD_SIZE]) const;
};

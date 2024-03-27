#pragma once
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "King.h"
#include "EmptyPiece.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "Communication.h"

class Chess
{
public:
	// ctor, dtor
	Chess(Color startingColor = white); // gets starting color, if not sets to white
	~Chess();

	// other methods
	void runChess(); // main function to game
	static string getSrcPos(string pos); // from the frontend to stc and dst
	static string getDstPos(string pos);
	string boardToStr() const;
	string boardToStrForConsole()const;



private:
	Piece* _board[BOARD_SIZE][BOARD_SIZE];
	King* _kings[COLORS]; // 0 - white king , 1 - black king
	std::vector<Piece*> _pieces[COLORS]; // 0 - white pieces , 1 - black pieces
	Color _currentTurn;
	Communication _pipe;

	// private methods
	void setKingRow(Color);
	void setPawnRow(Color);
	MoveCode MovePiece(const Position srcPos, const Position dstPos);
	MoveCode updateMove(string move); // gets move from user/frontend and returns the code of the move
	void updateBoard(Position src, Position dst);
	Piece* updateBoardAndSavePiece(Position src, Position dst);
	void returnBoard(Piece* returnPiece, Position src, Position dst);
	bool moveToSeeCheck(Piece* movedPiece, const Position dst, King* king);
	void moveAndReplacePiece(int dstRow, int dstCol, int srcRow, int srcCol, Piece* replace);
	void eatPiece(Position);
	void printCodeMessage(MoveCode code);

	MoveCode mate(King* checkKing); // 
	bool kingCanMove(King*);
	bool canBlockCheckingPiece(King* checkKing, Piece* checkingPiece);


	//for castle
	bool moveCastle(Rook* nearRook, King* king);
	bool movePositionForCastle(Position pos);
};
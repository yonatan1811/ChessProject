#include "Chess.h"

Chess::Chess(Color startingColor) : _pipe(Communication()) // initialize the board and set 
{
	this->_currentTurn = startingColor;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_board[i][j] = new EmptyPiece(Position(i, j));
		}
	}
	// setting the board
	setKingRow(white);
	setKingRow(black);
	setPawnRow(white);
	setPawnRow(black);
}

Chess::~Chess()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (this->_board[i][j] != nullptr)
			{
				delete this->_board[i][j];
				_board[i][j] = nullptr;
			}
		}
	}
	_pipe.~Communication();
}

// set the first row by color
void Chess::setKingRow(Color color)
{
	int row = (color == white) ? (0) : (BOARD_SIZE - 1); // if color == white, row = 0, else row = BOARD_SIZE - 1

	delete _board[row][rook1];
	_pieces[color].push_back((_board[row][rook1] = new Rook(color, Position(row, rook1))));
	delete _board[row][rook2];
	_pieces[color].push_back((_board[row][rook2] = new Rook(color, Position(row, rook2))));

	delete _board[row][knight1];
	_pieces[color].push_back((_board[row][knight1] = new Knight(color, Position(row, knight1))));
	delete _board[row][knight2];
	_pieces[color].push_back((_board[row][knight2] = new Knight(color, Position(row, knight2))));

	delete _board[row][bishop1];
	_pieces[color].push_back((_board[row][bishop1] = new Bishop(color, Position(row, bishop1))));
	delete _board[row][bishop2];
	_pieces[color].push_back((_board[row][bishop2] = new Bishop(color, Position(row, bishop2))));

	delete _board[row][queen];
	_pieces[color].push_back((_board[row][queen] = new Queen(color, Position(row, queen))));

	delete _board[row][king];
	_board[row][king] = _kings[color] = new King(color, Position(row, king));
}

// set the second row by color
void Chess::setPawnRow(Color color)
{
	int row = (color == white) ? (1) : (BOARD_SIZE - 2); // if color == white, row = 1, else row = BOARD_SIZE - 2
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		delete _board[row][i];
		_pieces[color].push_back((_board[row][i] = new Pawn(color, Position(row, i))));
	}
}

string Chess::boardToStrForConsole()const
{
	string board = "";
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_board[i][j] != nullptr)
			{
				board += _board[i][j]->getPieceChar();
			}
		}
		board += "\n";
	}
	return board;
}

// returns the board in a string
string Chess::boardToStr() const
{
	string board = "";
	for (int i = BOARD_SIZE - 1; i >= 0; i--)
	{
		// i think the protocol is a bit different, so this won't work with the forntend ,:: we dont send the board to the frontEnd
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_board[i][j] != nullptr)
			{
				board +=_board[i][j]->getPieceChar();
			}
		}
	}
	board += _currentTurn + '0';
	return board;
}

// checks if a piece can move, if it can -> moves piece and eats (revomes piece from _pieces) the enemy piece in that position.
MoveCode Chess::MovePiece(const Position srcPos, const Position dstPos)
{

	Color turn = _currentTurn;
	int col = srcPos.col, row = srcPos.row, dstRow = 0, dstCol = 0;
	MoveCode code = ACK;
	if (col >= BOARD_SIZE || col < 0 || row >= BOARD_SIZE || row < 0) // check the src square exists on the board
	{
		return MoveCode::FAIL_invalid_square;
	}

	dstRow = dstPos.row, dstCol = dstPos.col;
	if (dstCol >= BOARD_SIZE || dstCol < 0 || dstRow >= BOARD_SIZE || dstRow < 0) // check the dest square exists on the board
	{
		return MoveCode::FAIL_invalid_square;
	}

	Piece* p = _board[row][col];
	if (p->getColor() != turn) // checking if the poosition contains a piece from the same color
	{
		return MoveCode::FAIL_square_does_not_contain_friend_piece;
	}

	code = p->canMove(dstPos, _board); // if we can move a piece
	if (code && code != CASTLE) // if did not get ACK
	{
		return code; // return corresponding error
	}
	if (code == CASTLE) // if its a king we will move the king and the rook
	{
		if (movePositionForCastle(dstPos))
		{
			return MoveCode::ACK;
		}
		return MoveCode::FAIL_illegal_move;
	}
	if (this->moveToSeeCheck(p, dstPos, _kings[turn])) // checking if moving the piece would lead to check
	{
		return MoveCode::FAIL_move_leads_to_check; // return corresponding error
	}
	p->move(dstPos);
	this->updateBoard(srcPos, dstPos);

	// if (!_kings[!turn]->inCheck(_board, _pieces[turn]).empty()) // regular implementation
	// {
	// 	return MoveCode::ACK_check;
	// }

	return this->mate(_kings[!turn]); // bonus implementation 99% sure it works now
}

// a function that will move the piece , check if there is a check when it moves , if there is we will return true , else false
// (and of course we are going to return the piece to its original location)
bool Chess::moveToSeeCheck(Piece* movedPiece, const Position dst, King* king)
{
	bool inCheck = false;
	Position pos = movedPiece->getPos();
	Piece* savePiece = updateBoardAndSavePiece(pos, dst);
	movedPiece->Piece::move(dst);
	if (!king->inCheck(_board, _pieces[!king->getColor()]).empty())
	{
		inCheck = true;
	}
	returnBoard(savePiece, pos, dst);
	movedPiece->Piece::move(pos);
	return inCheck;
}

void Chess::updateBoard(Position src, Position dst)
{
	int dstRow = dst.row, dstCol = dst.col, srcRow = src.row, srcCol = src.col;
	this->eatPiece(dst);
	delete _board[dstRow][dstCol];
	moveAndReplacePiece(dstRow, dstCol, srcRow, srcCol, new EmptyPiece(Position(srcRow, srcCol)));
	_currentTurn = (_currentTurn == white) ? (black) : (white); // can also be _currentTurn = !_currentTurn
}

Piece* Chess::updateBoardAndSavePiece(Position src, Position dst)
{
	int dstRow = dst.row, dstCol = dst.col, srcRow = src.row, srcCol = src.col;
	Piece* destPiece = _board[dstRow][dstCol];
	this->eatPiece(dst);
	moveAndReplacePiece(dstRow, dstCol, srcRow, srcCol, new EmptyPiece(Position(srcRow, srcCol)));
	return destPiece;
}

void Chess::returnBoard(Piece* returnPiece, Position src, Position dst)
{
	int dstRow = dst.row, dstCol = dst.col, srcRow = src.row, srcCol = src.col;
	Color pieceColor = returnPiece->getColor();
	if (pieceColor != Color::none)
	{
		_pieces[pieceColor].push_back(returnPiece);
	}
	delete _board[srcRow][srcCol];
	moveAndReplacePiece(srcRow, srcCol, dstRow, dstCol, returnPiece);
}

void Chess::moveAndReplacePiece(int dstRow, int dstCol, int srcRow, int srcCol, Piece* replace)
{
	_board[dstRow][dstCol] = _board[srcRow][srcCol];
	_board[srcRow][srcCol] = replace;
}

void Chess::eatPiece(Position dst)
{
	int dstRow = dst.row, dstCol = dst.col;
	Piece* dstPiece = _board[dstRow][dstCol];
	Color pieceColor = dstPiece->getColor();
	if (pieceColor != Color::none)
	{
		_pieces[pieceColor].erase(std::remove(_pieces[pieceColor].begin(), _pieces[pieceColor].end(), dstPiece), _pieces[pieceColor].end());
	}
}

MoveCode Chess::mate(King* checkKing)
{
	std::vector<Piece*> checkingPieces = checkKing->inCheck(_board, _pieces[!checkKing->getColor()]); // if im right these are the pieces that can do check on the king
	if (checkingPieces.size() == 0)
	{
		return MoveCode::ACK;
	}
	if (this->kingCanMove(checkKing))
	{
		return MoveCode::ACK_check;
	}
	if (checkingPieces.size() == 1 &&
		(
			this->canBlockCheckingPiece(checkKing, checkingPieces[0])
			)
		)
	{
		return MoveCode::ACK_check;
	}
	return MoveCode::CHECKMATE;
}

bool Chess::kingCanMove(King* checkKing) // works
{
	Position pos = checkKing->getPos();
	int col = pos.col, row = pos.row;
	for (int i = -1; i <= 1; i++)
	{
		if (!(row + i < BOARD_SIZE && row + i >= 0))
		{
			continue;
		}
		for (int j = -1; j <= 1; j++)
		{
			if (!(col + i < BOARD_SIZE && col + i >= 0))
			{
				continue; // skip iteration
			}
			if (_board[row + i][col + j]->getColor() != checkKing->getColor())
			{
				if (!this->moveToSeeCheck(checkKing, Position(row + i, col + j), checkKing))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Chess::canBlockCheckingPiece(King* checkKing, Piece* checkingPiece)
{
	std::vector<Piece*> friendlyPieces = this->_pieces[checkKing->getColor()];
	std::vector<Position> squaresBetween = checkingPiece->returnSquaresBetween(checkKing->getPos(), _board);
	Piece* piece = nullptr;
	for (int i = 0; i < friendlyPieces.size(); i++)
	{
		piece = friendlyPieces[i];
		for (auto pos : squaresBetween)
		{
			if (!piece->canMove(pos, _board) && !this->moveToSeeCheck(piece, pos, checkKing))
			{
				return true;
			}
		}
	}
	return false;
}

void Chess::runChess() // main function to game
{
	string msgToFrontend = this->boardToStr(), msgFromFrontend;
	MoveCode code = MoveCode::ACK;
	string dst;
	do
	{
		_pipe.SendMessege(msgToFrontend.c_str());
		msgFromFrontend = _pipe.receiveMessege();
		if (msgFromFrontend != "quit")
		{
			code = this->MovePiece(Chess::getSrcPos(msgFromFrontend), Chess::getDstPos(msgFromFrontend));
			if (code == CASTLE)
			{
				code = ACK;
			}
			msgToFrontend = std::to_string(code);
		}
		std::cout << boardToStrForConsole();
		system("CLS");
	} while (msgFromFrontend != "quit");
	_pipe.SendMessege(std::to_string(0).c_str());
	_pipe.~Communication();
}

void Chess::printCodeMessage(MoveCode code)
{
	switch (code)
	{
	case MoveCode::ACK:
		std::cout << "Valid Move" << std::endl;
		break;
	case MoveCode::ACK_check:
		std::cout << ((_currentTurn == white) ? ("Black") : ("White")) << " king is in check" << std::endl;
		break;
	case MoveCode::FAIL_square_does_not_contain_friend_piece:
		std::cout << "ERROR: Source square does not contain you piece" << std::endl;
		break;
	case MoveCode::FAIL_dest_contains_friend_piece:
		std::cout << "ERROR: Destination sqaure contains your piece" << std::endl;
		break;
	case MoveCode::FAIL_move_leads_to_check:
		std::cout << "ERROR: This move would lead to check" << std::endl;
		break;
	case MoveCode::FAIL_invalid_square:
		std::cout << "ERROR:: Invalid Square" << std::endl;
		break;
	case MoveCode::FAIL_illegal_move:
		std::cout << "ERROR: Illegal Move" << std::endl;
		break;
	case MoveCode::FAIL_dest_equals_src:
		std::cout << "ERROR: Source and Destination are eqaul" << std::endl;
		break;
	case MoveCode::CHECKMATE:
		std::cout << "CHECKMATE: " << std::endl
			<< ((_currentTurn == white) ? ("White") : ("Black")) << " player won!" << std::endl;
		break;
	default:
		break;
	}
}

string Chess::getSrcPos(string pos)// from the frontend to stc and dst
{
	string src = "";
	src += pos[0];
	src += pos[1];
	return src;
}
string Chess::getDstPos(string pos)
{
	string dst = "";
	dst += pos[2];
	dst += pos[3];
	return dst;
}

bool Chess::moveCastle(Rook* nearRook, King* king)
{
	if (nearRook->getMoveStatus() == false)
	{
		Position newKingPos = Position(nearRook->getPos());
		Position newRookPos = Position(king->getPos());
		Position originalKingPos = Position(king->getPos());
		Position originalRookPos = Position(nearRook->getPos());
		if (king->getPos().col > nearRook->getPos().col)
		{
			newRookPos.col = bishop1; // the old king
			newKingPos.col = knight1;// the old rook
		}
		else
		{
			newRookPos.col = bishop2;
			newKingPos.col = knight2;
		}
		updateBoard(king->getPos(), newKingPos);
		updateBoard(nearRook->getPos(), newRookPos);
		king->move(newKingPos);
		nearRook->move(newRookPos);
		if (_kings[_currentTurn]->inCheck(_board, _pieces[!_currentTurn]).size() > 0)
		{
			updateBoard(king->getPos(), originalKingPos);
			updateBoard(nearRook->getPos(), originalRookPos);
			king->move(originalKingPos);
			nearRook->move(originalRookPos);
			return false;
		}
		return true;
	}

	return false;
}


bool Chess::movePositionForCastle(Position pos)
{
	//need to do something about the caslte
		//need to get the rook
	Position rooksPos = pos;
	Piece* nearRook;
	int col = (pos.col > king) ? (col = rook2) : (col = rook1);
	if ((_kings[_currentTurn]->inCheck(_board, _pieces[!_currentTurn]).size()) > 0)
	{
		return false; // if the king is check we cant move
	}
	nearRook = _board[pos.row][col];
	if (nearRook->getPieceChar() == 'R')
	{
		if (moveCastle((Rook*)nearRook, _kings[_currentTurn]))
		{
			return true;
		}
	}
	return false;
}
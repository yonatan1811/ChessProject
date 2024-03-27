#include "ComplicatedPiece.h"

ComplicatedPiece::ComplicatedPiece(const Color color, const char pieceChar, const Position pos)
    : Piece(color, pieceChar, pos)
{
    _hasMoved = false;
}

ComplicatedPiece::~ComplicatedPiece()
{
}

void ComplicatedPiece::move(Position pos)
{
    Piece::move(pos);
    _hasMoved = true;
}

bool ComplicatedPiece::getMoveStatus() const
{
    return _hasMoved;
}
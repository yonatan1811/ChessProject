#pragma once
#include "Piece.h"

class ComplicatedPiece : public Piece
{
protected:
    bool _hasMoved;
public:
    ComplicatedPiece(const Color color, const char pieceChar, const Position pos);
    ~ComplicatedPiece();

    // override methods
    void move(Position) override;
    virtual char getType() const = 0;

    // Complicated piece getter
    bool getMoveStatus() const;
};
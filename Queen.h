#pragma once
#include "Piece.h"
#include "Helper.h"
class Queen : public Piece
{
public:
    Queen(Position p, COLOR c, Board* b);
    bool isLegal(Position dest) override;
    void draw(int x) override;
    char getSymbol() const override;
};


#pragma once
#include "Piece.h"
#include "Helper.h"
class King :public Piece
{
public:
    King(Position p, COLOR c, Board* b);
    bool isLegal(Position dest) override;
    void draw(int x) override;
    char getSymbol() const override;
};


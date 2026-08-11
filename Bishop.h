#pragma once
#include "Piece.h"
#include "Helper.h"
class Bishop :public Piece
{
public:
    Bishop(Position p, COLOR c, Board* b);
    bool isLegal(Position dest) override;
    void draw(int x) override;
    char getSymbol() const override;
};


#pragma once
#include "Piece.h"
#include "Helper.h"
#include <cmath>
class Knight :public Piece
{
public:
	Knight(Position p, COLOR c, Board* b);
	bool isLegal(Position dest) override;
	void draw(int x) override;
	char getSymbol() const override;

};

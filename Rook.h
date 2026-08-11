#pragma once
#include <iostream>
#include "Piece.h"
using namespace std;
class Rook : public Piece
{
public:
	Rook(Position P, COLOR c, Board* b);
	bool isLegal(Position dest) override;
	void draw(int x) override;
	char getSymbol() const override;
};

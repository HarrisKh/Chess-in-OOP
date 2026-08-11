#pragma once
#include <iostream>
using namespace std;
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(Position p, COLOR c, Board* b);
	bool isLegal(Position dest)override;
	void draw(int x)override;
	char getSymbol() const override;
};

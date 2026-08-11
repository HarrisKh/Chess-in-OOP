#pragma once
#include"Player.h"
#include "Helper.h"

class Board;
class Piece
{
protected:
	Position pos;
	COLOR color;
	Board* board;
public:
	Piece(Position p, COLOR c, Board* b);
	virtual ~Piece(){}
	virtual bool isLegal(Position dest) = 0;
	virtual void draw(int x) = 0;
	virtual char getSymbol() const = 0;

	COLOR getColor()const;
	Position getPosition()const;
	void move(Position dest); 
	static bool isHorizontal(Position src, Position dest);
	static bool isVertical(Position src, Position dest);
	static bool isDiagonal(Position src, Position dest);
	static bool isPathClear(Position src, Position dest, Board* b);

};


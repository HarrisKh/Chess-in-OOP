#include "Pawn.h"
#include "Board.h"
#include <iostream>

Pawn::Pawn(Position p, COLOR c, Board* b) : Piece(p, c, b) {}

bool Pawn::isLegal(Position dest)
{
	int dir = (color == CWHITE) ? -1 : 1;
	int startRow = (color == CWHITE) ? 6 : 1;
	if (dest.col == pos.col and dest.row == pos.row + dir) {
		return board->pieceAt(dest) == nullptr;
	}
	if (dest.col == pos.col and dest.row == pos.row + 2 * dir and pos.row == startRow) {
		Position s1 = { pos.row + dir,pos.col };
		return board->pieceAt(s1)==nullptr and board->pieceAt(dest) == nullptr;
	}
	int colDiff = dest.col - pos.col;
	if (colDiff == 1 and dest.row == pos.row + dir) {
		Piece* target = board->pieceAt(dest);
		return target != nullptr and target->getColor() != color;
	}
	return false;
}
void Pawn::draw(int squareSize) 
{
    Texture2D tex = tex_b_pawn;
    if (color == CWHITE) {
        tex = tex_w_pawn;
    }

    Rectangle sourceRect = { 0, 0, (float)tex.width, (float)tex.height };

    Rectangle destRect = { (float)(pos.col * squareSize), (float)(pos.row * squareSize), (float)squareSize, (float)squareSize };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(tex, sourceRect, destRect, origin, 0, WHITE);
}

char Pawn::getSymbol() const
{
	return 'p';
}

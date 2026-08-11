#include "Knight.h"
#include <cmath>

Knight::Knight(Position p, COLOR c, Board* b) : Piece(p, c, b) {}

bool Knight::isLegal(Position dest)
{
	int rowDiff = std::abs(pos.row - dest.row);
	int colDiff = std::abs(pos.col- dest.col);

	return (rowDiff == 2 and colDiff == 1) or (rowDiff == 1 and colDiff == 2);
}
void Knight::draw(int squareSize) 
{
    Texture2D tex = tex_b_knight;
    if (color == CWHITE) {
        tex = tex_w_knight;
    }
    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { (float)(pos.col * squareSize), (float)(pos.row * squareSize), (float)squareSize, (float)squareSize };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(tex, source, dest, origin, 0, WHITE);
}

char Knight::getSymbol() const
{
    return 'n';
}

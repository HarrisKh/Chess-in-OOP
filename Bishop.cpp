#include "Bishop.h"

Bishop::Bishop(Position p, COLOR c, Board* b) : Piece(p, c, b) {}

bool Bishop::isLegal(Position dest)
{
	if (isDiagonal(pos, dest)) {
		return isPathClear(pos, dest, board);
	}
	return false;
}

void Bishop::draw(int squareSize)
{
    Texture2D tex = tex_b_bishop;
    if (color == CWHITE) {
        tex = tex_w_bishop;
    }
    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { (float)(pos.col * squareSize), (float)(pos.row * squareSize), (float)squareSize, (float)squareSize };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(tex, source, dest, origin, 0, WHITE);
}

char Bishop::getSymbol() const
{
    return 'b';
}

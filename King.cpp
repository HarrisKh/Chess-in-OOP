#include "King.h"
#include <cmath>

King::King(Position p, COLOR c, Board* b) : Piece(p, c, b) {}

bool King::isLegal(Position dest)
{
    int rowDiff = abs(pos.row - dest.row);
    int colDiff = abs(pos.col - dest.col);

    return (rowDiff <= 1 and colDiff <= 1) and (rowDiff != 0 or colDiff != 0);
}
void King::draw(int squareSize) 
{
    Texture2D tex = tex_b_king;
    if (color == CWHITE) {
        tex = tex_w_king;
    }
    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { (float)(pos.col * squareSize), (float)(pos.row * squareSize), (float)squareSize, (float)squareSize };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(tex, source, dest, origin, 0, WHITE);
}

char King::getSymbol() const
{
    return 'k';
}

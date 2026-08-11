#include "Queen.h"

Queen::Queen(Position p, COLOR c, Board* b) : Piece(p, c, b) {}

bool Queen::isLegal(Position dest)
{
    if (isHorizontal(pos, dest) or isVertical(pos, dest) or isDiagonal(pos, dest)) {
        return isPathClear(pos, dest, board);
    }
    return false;
}
void Queen::draw(int squareSize)
{
    Texture2D tex = tex_b_queen;
    if (color == CWHITE) {
        tex = tex_w_queen;
    }
    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { (float)(pos.col * squareSize), (float)(pos.row * squareSize), (float)squareSize, (float)squareSize };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(tex, source, dest, origin, 0, WHITE);
}

char Queen::getSymbol() const
{
    return 'q';
}

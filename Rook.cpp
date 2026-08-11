#include "Rook.h"

Rook::Rook(Position P, COLOR c, Board* b) :Piece(P, c, b) {}
bool Rook::isLegal(Position dest)
{
    if (isHorizontal(pos, dest) or isVertical(pos, dest)) {
        return isPathClear(pos, dest, board);
    }
    return false;
}

void Rook::draw(int squareSize) {
    Texture2D tex = tex_b_rook;
    if (color == CWHITE) {
        tex = tex_w_rook;
    }
    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { (float)(pos.col * squareSize), (float)(pos.row * squareSize), (float)squareSize, (float)squareSize };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(tex, source, dest, origin, 0, WHITE);
}

char Rook::getSymbol() const
{
    return 'r';
}

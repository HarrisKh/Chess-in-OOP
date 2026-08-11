#include "Piece.h"
#include "Board.h"
Piece::Piece(Position p, COLOR c, Board* b) : pos(p), color(c), board(b) {}


COLOR Piece::getColor() const
{
	return color;
}

Position Piece::getPosition() const
{
	return pos;
}

void Piece::move(Position dest)
{
	pos = dest;
}

bool Piece::isHorizontal(Position src, Position dest)
{
	return src.row==dest.row;
}

bool Piece::isVertical(Position src, Position dest)
{
	return src.col == dest.col;
}

bool Piece::isDiagonal(Position src, Position dest)
{
	return std::abs(src.row - dest.row) == std::abs(src.col - dest.col);
}

bool Piece::isPathClear(Position src, Position dest, Board* b)
{
	if (src.row == dest.row and src.col == dest.col)
		return false;
	int rowD;
	int colD;
	if (dest.row > src.row)
		rowD = 1;
	else if (dest.row < src.row)
		rowD = -1;
	else
		rowD = 0;

	if (dest.col > src.col)
		colD = 1;
	else if (dest.col< src.col)
		colD = -1;
	else
		colD = 0;
	int currRow = src.row + rowD;
	int currCol = src.col+ colD;
	while (currRow != dest.row or currCol != dest.col) {
		Position p= { currRow, currCol };
		if (b->pieceAt(p) != nullptr) {
			return false;
		}
		currRow += rowD;
		currCol += colD;
	}
	return true;
	}


#pragma once
#include "Piece.h"
#include "Player.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <string>

class Board
{
	Piece* grid[8][8];
public:
	Board();
	~Board();

	void init();
	void drawPieces(int squareSize);
	Piece* pieceAt(Position pos);
	void update(Position src, Position dest);
	void clearBoard();

	void save(string filename, COLOR currentTurn);
	COLOR load(string filename, COLOR currentTurn);
	string serialize(COLOR currentTurn);
	COLOR deserialize(string data);
	bool isCheck(COLOR c);
	bool isCheckmate(COLOR c);
	bool isStalemate(COLOR c);
	bool simulateAndCheck(Position src, Position dest, COLOR c);
};


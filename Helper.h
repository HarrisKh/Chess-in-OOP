#pragma once
#include <iostream>
#include <string>
#include <raylib.h>
using namespace std;

enum COLOR { CBLACK, CWHITE, NONE };

struct Position {
	int row;
	int col;
};

extern Texture2D tex_w_pawn, tex_b_pawn;
extern Texture2D tex_w_rook, tex_b_rook;
extern Texture2D tex_w_knight, tex_b_knight;
extern Texture2D tex_w_bishop, tex_b_bishop;
extern Texture2D tex_w_queen, tex_b_queen;
extern Texture2D tex_w_king, tex_b_king;

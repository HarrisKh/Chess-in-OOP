#include "Board.h"
#include <fstream>

Board::Board()
{
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            grid[r][c] = nullptr;
        }
    }
}

Board::~Board()
{
    clearBoard();
}

void Board::clearBoard()
{
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (grid[r][c] != nullptr) {
                delete grid[r][c];
                grid[r][c] = nullptr;
            }
        }
    }
}

void Board::init()
{
    grid[0][0] = new Rook({ 0, 0 }, CBLACK, this);
    grid[0][1] = new Knight({ 0, 1 }, CBLACK, this);
    grid[0][2] = new Bishop({ 0, 2 }, CBLACK, this);
    grid[0][3] = new Queen({ 0, 3 }, CBLACK, this);
    grid[0][4] = new King({ 0, 4 }, CBLACK, this);
    grid[0][5] = new Bishop({ 0, 5 }, CBLACK, this);
    grid[0][6] = new Knight({ 0, 6 }, CBLACK, this);
    grid[0][7] = new Rook({ 0, 7 }, CBLACK, this);


    for (int i = 0; i < 8; i++) {
        grid[1][i] = new Pawn({ 1, i }, CBLACK, this);
    }
    for (int i = 0; i < 8; i++) {
        grid[6][i] = new Pawn({ 6, i }, CWHITE, this);
    }
    grid[7][0] = new Rook({ 7, 0 }, CWHITE, this);
    grid[7][1] = new Knight({ 7, 1 }, CWHITE, this);
    grid[7][2] = new Bishop({ 7, 2 }, CWHITE, this);
    grid[7][3] = new Queen({ 7, 3 }, CWHITE, this);
    grid[7][4] = new King({ 7, 4 }, CWHITE, this);
    grid[7][5] = new Bishop({ 7, 5 }, CWHITE, this);
    grid[7][6] = new Knight({ 7, 6 }, CWHITE, this);
    grid[7][7] = new Rook({ 7, 7 }, CWHITE, this);
}

void Board::drawPieces(int squareSize)
{
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (grid[r][c] != nullptr) {
                 grid[r][c]->draw(squareSize);
            }
        }
    }
}
Piece* Board::pieceAt(Position pos)
{
    if (pos.row >= 0 and pos.row < 8 and pos.col >= 0 and pos.col < 8) {
        return grid[pos.row][pos.col];
    }
    return nullptr;
}

void Board::update(Position src, Position dest)
{
    Piece* p = grid[src.row][src.col];
    if (p != nullptr) {
        if (grid[dest.row][dest.col] != nullptr) {
            delete grid[dest.row][dest.col];
        }
        grid[dest.row][dest.col] = p;
        grid[src.row][src.col] = nullptr;
        p->move(dest);
    }
}

void Board::save(string filename, COLOR currentTurn)
{
    ofstream out(filename);
    if (!out) return;
    out << serialize(currentTurn);
    out.close();
}

COLOR Board::load(string filename, COLOR currentTurn)
{
    ifstream in(filename);
    if (!in) return currentTurn;
    
    string data = "", line;
    while(getline(in, line)) {
        data += line + "\n";
    }
    in.close();
    
    return deserialize(data);
}

string Board::serialize(COLOR currentTurn)
{
    string out = "";
    if (currentTurn == CWHITE) 
        out += "W\n";
    else
        out += "B\n";

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = grid[r][c];
            if (p == nullptr) {
                out += "-";
            } else {
                char sym = p->getSymbol();
                COLOR col = p->getColor();

                if (col == CWHITE) {
                    sym = toupper(sym);
                }
                out += sym;
            }
        }
        out += "\n";
    }

    return out;
}

COLOR Board::deserialize(string data)
{
    clearBoard();
    int r = 0, c = 0;
    COLOR currentTurn = CWHITE;
    bool turnRead = false;
    
    for (int i = 0; i < data.length(); i++) {
        char sym = data[i];
        
        if (!turnRead) {
            if (sym == 'W') 
                currentTurn = CWHITE;
            else if (sym == 'B')
                currentTurn = CBLACK;
            else if (sym == '\n') 
                turnRead = true;
            continue;
        }

        if (sym == '\n') {
            if (r < 8) 
                r++;
            c = 0;
            continue;
        }

        if (r < 8 and c < 8) {
            if (sym == '-') {
                grid[r][c] = nullptr;
            } else {
                COLOR col = isupper(sym) ? CWHITE : CBLACK;
                char lowerSym = tolower(sym);
                switch (lowerSym) {
                    case 'p': grid[r][c] = new Pawn({r, c}, col, this); break;
                    case 'r': grid[r][c] = new Rook({r, c}, col, this); break;
                    case 'n': grid[r][c] = new Knight({r, c}, col, this); break;
                    case 'b': grid[r][c] = new Bishop({r, c}, col, this); break;
                    case 'q': grid[r][c] = new Queen({r, c}, col, this); break;
                    case 'k': grid[r][c] = new King({r, c}, col, this); break;
                }
            }
            c++;
        }
    }
    return currentTurn;
}

bool Board::simulateAndCheck(Position src, Position dest, COLOR c)
{

    Piece* p = grid[src.row][src.col];
    Piece* target = grid[dest.row][dest.col];
    
    grid[dest.row][dest.col] = p;
    grid[src.row][src.col] = nullptr;
    Position oldPos = p->getPosition();
    p->move(dest);
    bool inCheck = isCheck(c);

    p->move(oldPos);
    grid[src.row][src.col] = p;
    grid[dest.row][dest.col] = target;


    return inCheck;
}

bool Board::isCheck(COLOR c)
{
    Position kingPos = {-1, -1};
    for (int r = 0; r < 8; r++) {
        for (int col = 0; col < 8; col++) {
            Piece* p = grid[r][col];
            if (p != nullptr and p->getColor() == c and p->getSymbol() == 'k') {
                kingPos = {r, col};
                break;
            }
        }
    }
    
    if (kingPos.row == -1)
        return false;

    for (int r = 0; r < 8; r++) {
        for (int col = 0; col < 8; col++) {
            Piece* p = grid[r][col];
            if (p != nullptr and p->getColor() != c) {
                if (p->isLegal(kingPos)) return true;
            }
        }
    }
    return false;
}

bool Board::isCheckmate(COLOR c)
{
    if (!isCheck(c)) return false;

    for (int r = 0; r < 8; r++) {
        for (int col = 0; col < 8; col++) {
            Piece* p = grid[r][col];
            if (p != nullptr and p->getColor() == c) {
                for (int destR = 0; destR < 8; destR++) {
                    for (int destC = 0; destC < 8; destC++) {
                        Position destPos = {destR, destC};
                        if (p->isLegal(destPos)) {
                            if (!simulateAndCheck(p->getPosition(), destPos, c)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool Board::isStalemate(COLOR c)
{
    if (isCheck(c)) return false;

    for (int r = 0; r < 8; r++) {
        for (int col = 0; col < 8; col++) {
            Piece* p = grid[r][col];
            if (p != nullptr and p->getColor() == c) {
                for (int destR = 0; destR < 8; destR++) {
                    for (int destC = 0; destC < 8; destC++) {
                        Position destPos = {destR, destC};
                        if (p->isLegal(destPos)) {
                            if (!simulateAndCheck(p->getPosition(), destPos, c)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

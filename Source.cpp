//#include <iostream>
//#include <string>
//#include "Board.h"
//#include "Player.h"
//using namespace std;
//
//int main() {
//	Player p1("Harris", WHITE);
//	Player p2("Abdullah", BLACK);
//	int srcRow, srcCol, destRow, destCol;
//	Board gameBoard;
//	gameBoard.init();
//	while (true) {
//		gameBoard.displayBoard();
//		cout << "Enter source coordinates: ";
//		cin>>srcRow>>srcCol;
//		cout << "Enter destination coordinates: ";
//		cin>>destRow>>destCol;
//		if (srcRow < 0 or srcRow > 7 or srcCol < 0 or srcCol > 7 or
//			destRow < 0 or destRow > 7 or destCol < 0 or destCol > 7) {
//			cout << "Inalid coordinates" << endl;
//			continue;
//		}
//		Piece* selectedPiece = gameBoard.pieceAt({ srcRow, srcCol });
//
//		if (selectedPiece == nullptr) {
//			cout << "This position has no piece" << endl;
//			continue;
//		}
//		if (selectedPiece->isLegal({ destRow, destCol })) {
//			gameBoard.update({ srcRow, srcCol }, { destRow, destCol });
//			cout << "Successful" << endl;
//		}
//		else {
//			cout << "ILLEGAL Move" << (selectedPiece->getColor() == WHITE ? " of White" : "of Black")  << endl;
//		}
//	}
//	
//	return 0;
//}


#include <raylib.h>
#include <iostream>
#include <vector>
#include "Board.h"
#include "Player.h"

using namespace std;

Texture2D tex_w_pawn, tex_b_pawn;
Texture2D tex_w_rook, tex_b_rook;
Texture2D tex_w_knight, tex_b_knight;
Texture2D tex_w_bishop, tex_b_bishop;
Texture2D tex_w_queen, tex_b_queen;
Texture2D tex_w_king, tex_b_king;

const int SQUARE_SIZE = 80;
const int BOARD_SIZE = SQUARE_SIZE * 8;
const int WINDOW_WIDTH = BOARD_SIZE + 300;
const int WINDOW_HEIGHT = BOARD_SIZE;

void LoadPiecesTextures() {
    tex_w_pawn = LoadTexture("w_pawn.png");
    tex_w_rook = LoadTexture("w_rook.png");
    tex_w_knight = LoadTexture("w_knight.png");
    tex_w_bishop = LoadTexture("w_bishop.png");
    tex_w_queen = LoadTexture("w_queen.png");
    tex_w_king = LoadTexture("w_king.png");
    tex_b_pawn = LoadTexture("b_pawn.png");
    tex_b_rook = LoadTexture("b_rook.png");
    tex_b_knight = LoadTexture("b_knight.png");
    tex_b_bishop = LoadTexture("b_bishop.png");
    tex_b_queen = LoadTexture("b_queen.png");
    tex_b_king = LoadTexture("b_king.png");
}

void UnloadPiecesTextures() {
    UnloadTexture(tex_w_pawn);
    UnloadTexture(tex_w_rook);
    UnloadTexture(tex_w_knight);
    UnloadTexture(tex_w_bishop);
    UnloadTexture(tex_w_queen);
    UnloadTexture(tex_w_king);
    UnloadTexture(tex_b_pawn);
    UnloadTexture(tex_b_rook);
    UnloadTexture(tex_b_knight);
    UnloadTexture(tex_b_bishop);
    UnloadTexture(tex_b_queen);
    UnloadTexture(tex_b_king);
}


int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Chess in OOP");
    SetTargetFPS(60);

    LoadPiecesTextures();
    Player p1("Harris", CWHITE);
    Player p2("Ali", CBLACK);

    Board gameBoard;
    gameBoard.init();


    Position selectedPos = { -1, -1 };
    bool isPieceSelected = false;

    COLOR currentTurn = CWHITE;
    
    vector<string> history;
    int historyIndex = 0;
    history.push_back(gameBoard.serialize(currentTurn));

    int gameStatus = 0;
    bool showSaveMsg = false;
    bool showLoadMsg = false;
    float msgTimer = 0.0;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_S)) {
            gameBoard.save("savegame.txt", currentTurn);
            showSaveMsg = true;
            showLoadMsg = false;
            msgTimer = 2.0;
        }
        if (IsKeyPressed(KEY_L)) {
            currentTurn = gameBoard.load("savegame.txt", currentTurn);
            showLoadMsg = true;
            showSaveMsg = false;
            msgTimer = 2.0;
            isPieceSelected = false;
            
            history.clear();
            history.push_back(gameBoard.serialize(currentTurn));
            historyIndex = 0;
            gameStatus = 0;
        }
        
        if (IsKeyPressed(KEY_U) and historyIndex > 0) {
            historyIndex--;
            currentTurn = gameBoard.deserialize(history[historyIndex]);
            isPieceSelected = false;
            gameStatus = 0;
        }
        
        if (IsKeyPressed(KEY_R) and historyIndex < history.size() - 1) {
            historyIndex++;
            currentTurn = gameBoard.deserialize(history[historyIndex]);
            isPieceSelected = false;
            
            if (gameBoard.isCheckmate(currentTurn)) {
                gameStatus = (currentTurn == CWHITE) ? 2 : 1;
            } else if (gameBoard.isStalemate(currentTurn)) {
                gameStatus = 3;
            }
        }
        if (msgTimer > 0) {
            msgTimer -= GetFrameTime();
        } else {
            showSaveMsg = false;
            showLoadMsg = false;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) and gameStatus == 0) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            if (mouseX < BOARD_SIZE and mouseY < BOARD_SIZE) {
                int clickedCol = mouseX / SQUARE_SIZE;
                int clickedRow = mouseY / SQUARE_SIZE;

                if (!isPieceSelected) {
                    Piece* p = gameBoard.pieceAt({ clickedRow, clickedCol });

                    if (p != nullptr and p->getColor() == currentTurn) {
                        selectedPos = { clickedRow, clickedCol };
                        isPieceSelected = true;
                    }
                }
                else {
                    Position destPos = { clickedRow, clickedCol };
                    Piece* selectedPiece = gameBoard.pieceAt(selectedPos);

                    if (selectedPiece != nullptr and selectedPiece->isLegal(destPos)) {
                        if (!gameBoard.simulateAndCheck(selectedPos, destPos, currentTurn)) {
                            gameBoard.update(selectedPos, destPos);
                            
                            if (currentTurn == CWHITE) 
                                currentTurn = CBLACK;
                            else 
                                currentTurn = CWHITE;
                            
                            history.resize(historyIndex + 1);
                            history.push_back(gameBoard.serialize(currentTurn));
                            historyIndex++;
                            
                            if (gameBoard.isCheckmate(currentTurn)) {
                                gameStatus = (currentTurn == CWHITE) ? 2 : 1;
                            } else if (gameBoard.isStalemate(currentTurn)) {
                                gameStatus = 3;
                            }
                        }
                    }
                   
                    isPieceSelected = false;
                    selectedPos = { -1, -1 };
                }
            }
        }
        BeginDrawing();
        ClearBackground(WHITE);

        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                Color squareColor;
                if ((r + c) % 2 == 0) {
                    squareColor = LIGHTGRAY;
                }
                else {
                    squareColor = DARKGRAY;
                }
                DrawRectangle(c * SQUARE_SIZE, r * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, squareColor);
            }
        }

        if (isPieceSelected) {
            DrawRectangle(selectedPos.col * SQUARE_SIZE, selectedPos.row * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, YELLOW);
            Piece* selectedPiece = gameBoard.pieceAt(selectedPos);

            if (selectedPiece != nullptr) {
                for (int r = 0; r < 8; r++) {
                    for (int c = 0; c < 8; c++) {
                        if (selectedPiece->isLegal({ r, c })) {
                            DrawCircle(c* SQUARE_SIZE + SQUARE_SIZE / 2, r* SQUARE_SIZE + SQUARE_SIZE / 2, 10, GREEN);
                        }
                    }
                }
            }
        }

        gameBoard.drawPieces(SQUARE_SIZE);
        DrawText("CHESS GAME", BOARD_SIZE + 20, 20, 30, BLACK);

        string turnText = "Current Turn: ";
        if (currentTurn == CWHITE) {
            turnText += p1.getName();
            DrawText(turnText.c_str(), BOARD_SIZE + 20, 70, 20, BLUE);
        }
        else {
            turnText += p2.getName();
            DrawText(turnText.c_str(), BOARD_SIZE + 20, 70, 20, RED);
        }
        if (showSaveMsg) {
            DrawText("Game Saved!", BOARD_SIZE + 20, 150, 20, DARKGREEN);
        } else if (showLoadMsg) {
            DrawText("Game Loaded!", BOARD_SIZE + 20, 150, 20, BLUE);
        }
        
        if (gameStatus == 1) {
            DrawText("CHECKMATE", BOARD_SIZE + 20, 200, 30, GREEN);
            DrawText("WHITE WINS", BOARD_SIZE + 20, 240, 20, BLUE);
        } else if (gameStatus == 2) {
            DrawText("CHECKMATE", BOARD_SIZE + 20, 200, 30, GREEN);
            DrawText("BLACK WINS", BOARD_SIZE + 20, 240, 20, RED);
        } else if (gameStatus == 3) {
            DrawText("STALEMATE", BOARD_SIZE + 20, 200, 30, YELLOW);
        } else if (gameBoard.isCheck(currentTurn)) {
            DrawText("CHECK!", BOARD_SIZE + 20, 200, 30, ORANGE);
        }

        EndDrawing();
    }

    UnloadPiecesTextures();
    CloseWindow();

    return 0;
}
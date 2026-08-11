# Chess Game in C++

## Overview

This project is a graphical chess game written in C++ using Raylib.

The main goal of the project is to implement chess using Object-Oriented Programming. Instead of putting all the chess logic in one large file, the project separates the board, players, pieces, and individual piece movement into different classes.

The project includes:

- A graphical 8x8 chess board
- White and black players
- All six chess piece types
- Individual movement rules for each piece
- Capturing
- Turn management
- Check detection
- Checkmate detection
- Stalemate detection
- Move validation
- Save and load
- Undo and redo
- Mouse-based piece selection
- Visual highlighting of legal moves
- Raylib-based graphics

---

## Technologies Used

- C++
- Object-Oriented Programming
- Raylib
- File handling
- Dynamic memory
- STL `vector`
- Polymorphism
- Inheritance

---

# Project Structure

```text
Chess Game
|
+-- Source.cpp
|   +-- Main program
|   +-- Game loop
|   +-- Keyboard and mouse input
|   +-- Turn management
|
+-- Board
|   +-- Stores the 8x8 board
|   +-- Creates and removes pieces
|   +-- Handles movement
|   +-- Checks
|   +-- Checkmate
|   +-- Stalemate
|   +-- Save/load
|
+-- Player
|   +-- Stores player name and color
|
+-- Piece
|   +-- Base class for all pieces
|   +-- Common movement helpers
|
+-- Pawn
+-- Rook
+-- Knight
+-- Bishop
+-- Queen
+-- King
|
+-- Helper.h
|   +-- Common definitions
|   +-- Position structure
|   +-- Piece colors
|   +-- Raylib textures
|
+-- Chess piece PNG files
```

---

# Files

```text
BSAI25066-Main.cpp
Piece.h
Piece.cpp
Pawn.h
Pawn.cpp
Rook.h
Rook.cpp
Knight.h
Knight.cpp
Bishop.h
Bishop.cpp
Queen.h
Queen.cpp
King.h
King.cpp
Player.h
Player.cpp
Board.h
Board.cpp
Helper.h

w_pawn.png
w_rook.png
w_knight.png
w_bishop.png
w_queen.png
w_king.png

b_pawn.png
b_rook.png
b_knight.png
b_bishop.png
b_queen.png
b_king.png

savegame.txt
```

---

# Basic Design

The project is centered around the `Piece` base class.

All six chess pieces inherit from it:

```text
                    Piece
                      |
       +--------------+--------------+
       |      |       |      |       |
     Pawn   Rook   Knight  Bishop  Queen  King
```

Each piece knows:

- Its current position
- Its color
- The board it belongs to

Each derived piece implements its own `isLegal()` function.

This is one of the main OOP ideas used in the project: the board can work with a `Piece*` without needing to know whether the object is a pawn, rook, bishop, or another piece.

---

# Helper.h

`Helper.h` contains common definitions used throughout the project.

## Player Colors

```cpp
enum COLOR { CBLACK, CWHITE, NONE };
```

This identifies whether a piece or player belongs to the black or white side.

## Position

The board uses a simple structure to represent coordinates:

```cpp
struct Position {
    int row;
    int col;
};
```

The board uses rows and columns from `0` to `7`.

For example:

```text
{0, 0} -> top-left
{7, 7} -> bottom-right
```

The position is used everywhere instead of passing row and column separately.

---

# Player Class

The `Player` class is intentionally simple.

It stores:

```cpp
string name;
COLOR color;
```

A player is created with a name and color:

```cpp
Player p1("Harris", CWHITE);
Player p2("Ali", CBLACK);
```

The class provides:

```cpp
getName()
getColor()
```

The main program uses these functions to display whose turn it is.

---

# Piece Class

`Piece` is the base class for all chess pieces.

Important members are:

```cpp
Position pos;
COLOR color;
Board* board;
```

This means every piece knows:

1. Where it is
2. Which side it belongs to
3. Which board it is currently on

The constructor initializes these values.

---

# Polymorphism

The most important part of the `Piece` class is its virtual functions:

```cpp
virtual bool isLegal(Position dest) = 0;
virtual void draw(int x) = 0;
virtual char getSymbol() const = 0;
```

These are pure virtual functions, making `Piece` an abstract base class.

Every child class must provide its own implementation.

For example:

```cpp
Pawn::isLegal()
Rook::isLegal()
Knight::isLegal()
Bishop::isLegal()
Queen::isLegal()
King::isLegal()
```

This allows the board to store every type of piece using:

```cpp
Piece*
```

while still calling the correct derived-class function.

---

# Common Piece Functions

`Piece.cpp` contains helper functions used by multiple pieces.

## Horizontal Movement

```cpp
isHorizontal(src, dest)
```

checks whether two positions are on the same row.

## Vertical Movement

```cpp
isVertical(src, dest)
```

checks whether two positions are on the same column.

## Diagonal Movement

```cpp
isDiagonal(src, dest)
```

checks whether the row and column differences are equal.

## Path Checking

Sliding pieces cannot jump over other pieces.

The function:

```cpp
isPathClear(src, dest, board)
```

moves square-by-square from the source toward the destination.

If it finds another piece before reaching the destination, the path is considered blocked.

This function is used by:

- Rook
- Bishop
- Queen

---

# Pawn

The pawn has directional movement depending on its color.

For white:

```text
Direction = -1
```

For black:

```text
Direction = +1
```

A pawn can:

- Move one square forward
- Move two squares from its starting position
- Capture diagonally

The two-square move also checks that the square between the pawn and its destination is empty.

The pawn's symbol is:

```cpp
'p'
```

---

# Rook

The rook moves horizontally or vertically.

Its legality check is essentially:

```text
Horizontal OR Vertical
        |
        v
   Path is clear
```

The rook cannot jump over pieces.

Its symbol is:

```cpp
'r'
```

---

# Knight

The knight uses its unique L-shaped movement.

The difference must be either:

```text
2 rows + 1 column
```

or:

```text
1 row + 2 columns
```

Because knights jump over pieces, they do not need a path-clear check.

Its symbol is:

```cpp
'n'
```

---

# Bishop

The bishop can only move diagonally.

The code first checks:

```cpp
isDiagonal(pos, dest)
```

and then checks whether the path is clear.

Its symbol is:

```cpp
'b'
```

---

# Queen

The queen combines rook and bishop movement.

It can move:

- Horizontally
- Vertically
- Diagonally

The path must be clear.

Its symbol is:

```cpp
'q'
```

---

# King

The king can move one square in any direction.

The code calculates the row and column differences and ensures both are at most 1.

It also prevents the king from staying on the same square.

Its symbol is:

```cpp
'k'
```

The board later uses the king's position to determine whether the player is in check.

---

# Board Class

`Board` is the main class responsible for the chess board and its pieces.

The board is represented as:

```cpp
Piece* grid[8][8];
```

Each cell can either contain:

- A pointer to a piece
- `nullptr` if the square is empty

This is useful because all piece types can be stored in the same array through the base-class pointer.

---

# Board Initialization

`Board::init()` creates the starting chess position.

Black pieces are placed on rows:

```text
0 and 1
```

White pieces are placed on:

```text
6 and 7
```

The back rows are arranged as:

```text
Rook
Knight
Bishop
Queen
King
Bishop
Knight
Rook
```

The second row contains eight pawns.

The same arrangement is mirrored for the white side.

---

# Dynamic Memory

Pieces are created dynamically:

```cpp
new Rook(...)
new Knight(...)
new Bishop(...)
new Queen(...)
new King(...)
new Pawn(...)
```

The board owns these pieces.

When the board is destroyed, `clearBoard()` goes through all 64 squares and deletes any piece that exists.

This prevents the dynamically allocated pieces from remaining in memory.

---

# Finding a Piece

The function:

```cpp
Board::pieceAt(Position pos)
```

returns the piece located at a particular square.

If the square is empty, it returns:

```cpp
nullptr
```

It also checks that the requested position is inside the 8x8 board.

---

# Moving Pieces

The function:

```cpp
Board::update(src, dest)
```

performs the actual board update.

The process is:

```text
Get source piece
      |
      v
Check destination
      |
      +---- Occupied ----> Delete captured piece
      |
      v
Move piece pointer
      |
      v
Clear source square
      |
      v
Update piece position
```

This is separate from `isLegal()`. The piece first decides whether the movement pattern is legal, and the board then performs the move.

---

# Capturing

If the destination square already contains a piece, `Board::update()` deletes that piece before placing the moving piece there.

For example:

```text
White Rook -> Black Pawn
                  |
                  v
             Pawn deleted
                  |
                  v
             Rook occupies square
```

---

# Turn Management

The main program stores the current turn using:

```cpp
COLOR currentTurn = CWHITE;
```

After a successful move:

```text
White -> Black
Black -> White
```

Only a piece belonging to the current player can be selected.

---

# Graphical Interface

The game uses Raylib to display the board.

The board size is:

```cpp
const int SQUARE_SIZE = 80;
```

Therefore:

```text
8 x 80 = 640 pixels
```

The game window is wider than the board because an additional area is used for game information.

```cpp
const int WINDOW_WIDTH = BOARD_SIZE + 300;
const int WINDOW_HEIGHT = BOARD_SIZE;
```

---

# Piece Textures

Each piece uses a PNG texture.

There are separate textures for white and black pieces:

```text
White:
w_pawn.png
w_rook.png
w_knight.png
w_bishop.png
w_queen.png
w_king.png

Black:
b_pawn.png
b_rook.png
b_knight.png
b_bishop.png
b_queen.png
b_king.png
```

The textures are loaded once when the game starts.

They are released using `UnloadTexture()` when the program closes.

---

# Drawing Pieces

Each piece implements its own `draw()` function.

The piece's logical board position is converted into screen coordinates:

```cpp
pos.col * squareSize
pos.row * squareSize
```

Raylib's `DrawTexturePro()` then draws the correct texture inside the corresponding square.

---

# Selecting a Piece

The player uses the left mouse button.

The mouse coordinates are converted into board coordinates:

```cpp
clickedCol = mouseX / SQUARE_SIZE;
clickedRow = mouseY / SQUARE_SIZE;
```

The program then calls:

```cpp
gameBoard.pieceAt(...)
```

to find the piece on that square.

A piece can only be selected if its color matches `currentTurn`.

---

# Legal Move Highlighting

Once a piece is selected, the game checks every square on the board:

```cpp
selectedPiece->isLegal({r, c})
```

If the piece can legally move there, a green circle is drawn on that square.

The selected square itself is highlighted in yellow.

This makes it easier for the player to understand where the selected piece can move.

---

# Preventing Moves That Leave the King in Check

A movement pattern being legal does not automatically mean the move is legal in chess.

For example, a player cannot move a piece if doing so leaves their own king in check.

The project handles this through:

```cpp
Board::simulateAndCheck()
```

The board temporarily performs the move, checks whether the player's king is attacked, and then restores the original board state.

The actual move is only performed if the simulation does not leave the king in check.

---

# Check Detection

`Board::isCheck(COLOR c)` searches the board for the king belonging to the specified color.

After finding the king, it checks all opponent pieces.

If any opponent piece can legally attack the king's square, the player is considered to be in check.

The UI displays:

```text
CHECK!
```

when this happens.

---

# Checkmate Detection

`Board::isCheckmate(COLOR c)` first checks whether the player is currently in check.

If they are, the board examines every piece belonging to that player and every possible destination.

For each possible move, the program calls:

```cpp
simulateAndCheck()
```

If no move can get the king out of check, the player is in checkmate.

The game then displays the winning side.

---

# Stalemate Detection

`Board::isStalemate(COLOR c)` works similarly to checkmate, but with one important difference.

A stalemate occurs when:

```text
Player is NOT in check
        +
Player has NO legal moves
        =
STALEMATE
```

The game displays:

```text
STALEMATE
```

when this situation is detected.

---

# Save and Load

The project supports saving the current game using:

```text
S
```

and loading it using:

```text
L
```

The save file is:

```text
savegame.txt
```

The board handles this through:

```cpp
save()
load()
```

---

# Serialization

Instead of writing every C++ object directly to the file, the board converts the current position into a simple text representation.

The first line stores the current turn:

```text
W
```

or:

```text
B
```

The next eight lines represent the board.

Example symbols include:

```text
P = White Pawn
R = White Rook
N = White Knight
B = White Bishop
Q = White Queen
K = White King

p = Black Pawn
r = Black Rook
n = Black Knight
b = Black Bishop
q = Black Queen
k = Black King
```

An empty square is represented by:

```text
-
```

This makes the save file easy to read and reconstruct.

---

# Deserialization

When a saved game is loaded, `deserialize()` first clears the existing board.

It then reads the saved characters and recreates the correct piece objects.

For example:

```text
'p' -> Pawn
'r' -> Rook
'n' -> Knight
'b' -> Bishop
'q' -> Queen
'k' -> King
```

Uppercase letters are interpreted as white pieces, while lowercase letters represent black pieces.

This is a good example of reconstructing an object-oriented game state from a simple text format.

---

# Undo and Redo

The project implements undo and redo using:

```cpp
vector<string> history;
int historyIndex;
```

After every successful move, the board is serialized and added to the history.

The history therefore stores complete board states rather than individual piece changes.

---

## Undo

Press:

```text
U
```

to move backward through the history.

The previous serialized state is loaded using:

```cpp
deserialize()
```

---

## Redo

Press:

```text
R
```

to move forward through the history.

This makes undo and redo relatively simple because the program does not need to manually reverse every individual piece movement.

When a new move is made after an undo, the future history is removed:

```cpp
history.resize(historyIndex + 1);
```

This follows the usual behavior of an undo/redo system.

---

# Game Status

The main program uses:

```cpp
int gameStatus = 0;
```

The statuses represent:

```text
0 -> Game running
1 -> White wins by checkmate
2 -> Black wins by checkmate
3 -> Stalemate
```

The status is updated after moves and redo operations.

---

# Main Game Loop

The overall program works like this:

```text
Start Program
      |
      v
Initialize Raylib
      |
      v
Load Piece Textures
      |
      v
Create Players
      |
      v
Create and Initialize Board
      |
      v
Start Game Loop
      |
      +--------------------------+
      |                          |
      v                          v
Keyboard Input              Mouse Input
      |                          |
 Save / Load                 Select Piece
 Undo / Redo                      |
      |                       Select Destination
      |                          |
      |                       Validate Move
      |                          |
      |                    Check Own King
      |                          |
      |                    Execute Move
      |                          |
      +------------+-------------+
                   |
                   v
             Check Status
                   |
                   v
              Draw Board
                   |
                   v
              Draw Pieces
                   |
                   v
             Draw UI
                   |
                   v
             Next Frame
```

---

# Controls

| Input | Action |
|---|---|
| Left Mouse Button | Select and move pieces |
| `S` | Save game |
| `L` | Load game |
| `U` | Undo |
| `R` | Redo |
| `ESC` | Close the game |

---

# OOP Concepts Used

This project demonstrates several important OOP concepts.

## Inheritance

All chess pieces inherit from:

```cpp
Piece
```

For example:

```cpp
class Rook : public Piece
```

and:

```cpp
class Queen : public Piece
```

This avoids duplicating common piece functionality.

## Polymorphism

The board stores all pieces as:

```cpp
Piece*
```

but calls the appropriate derived implementation of:

```cpp
isLegal()
draw()
getSymbol()
```

depending on the actual object.

## Encapsulation

Classes keep their data and provide functions to interact with it.

For example, the `Player` class keeps the name and color private and exposes:

```cpp
getName()
getColor()
```

## Abstraction

The `Piece` class defines what every chess piece must provide without specifying exactly how each piece moves.

Each derived class handles its own movement rules.

## Composition

The `Board` contains the pieces through its:

```cpp
Piece* grid[8][8]
```

and each piece maintains a pointer back to the board so it can inspect other pieces when validating moves.

---

# Dynamic Memory Management

The board dynamically creates pieces using `new`.

For example:

```cpp
grid[0][0] = new Rook(...);
```

When a piece is captured, the board deletes the old object.

When the board is destroyed, `clearBoard()` deletes all remaining pieces.

This demonstrates manual memory management in C++.

---

# A Note About the Original Source

The `Source.cpp` file also contains an older console-based version of the program, but that code is commented out.

The active version is the Raylib implementation.

The commented version shows an earlier approach where the user entered source and destination coordinates through the console. The current version replaces that interaction with mouse-based graphical selection.

---

# Current Implementation Limitations

The project implements the core chess movement and king-safety logic, but it does not implement every official chess rule.

Based on the current code:

- Pawn promotion is not implemented.
- Castling is not implemented.
- En passant is not implemented.
- The pawn capture implementation checks the right diagonal but does not include the left diagonal.
- Piece-specific `isLegal()` functions primarily validate movement patterns; some additional destination-color validation is handled elsewhere or is not explicitly enforced by every piece.
- The king's `isLegal()` function checks its movement pattern, while `simulateAndCheck()` is responsible for preventing a move that leaves the king in check.
- There is no move clock, draw-by-repetition detection, or fifty-move rule.

These are natural areas for future improvements rather than problems with the overall OOP structure.

---

# Possible Improvements

The game could be expanded with:

- Pawn promotion
- Castling
- En passant
- Complete pawn capture handling
- More complete destination validation
- Draw by repetition
- Fifty-move rule
- Move notation such as algebraic chess notation
- A move list/history panel
- Piece movement animations
- Sound effects
- Main menu
- Player name input
- Restart game option
- Better visual board design

---

# What This Project Demonstrates

This project brings together several C++ concepts in one practical application:

### C++

- Classes and objects
- Inheritance
- Polymorphism
- Abstraction
- Encapsulation
- Pointers
- Dynamic memory
- Virtual functions
- File handling
- STL `vector`

### Game Development

- Game loop
- Input handling
- Board representation
- Piece movement
- Collision/capture
- Turn management
- Game-state management
- Check and checkmate detection
- Save/load
- Undo/redo

### Raylib

- Window creation
- Texture loading
- Texture rendering
- Mouse input
- Keyboard input
- Drawing shapes and text
- Frame-based rendering

---

# Conclusion

This project is a practical implementation of a chess game using C++ and Object-Oriented Programming.

The main strength of the project is its class structure. Instead of treating every piece as the same object, the program uses a common `Piece` base class and lets `Pawn`, `Rook`, `Knight`, `Bishop`, `Queen`, and `King` define their own movement behavior.

The `Board` class manages the complete chess position, while the `Player` class handles player information. Raylib provides the graphical interface, and the serialization system allows the board to be saved, loaded, and stored in the undo/redo history.

Overall, the project demonstrates how OOP can be used to organize a fairly complex game into smaller, understandable components while combining game logic with graphical programming.

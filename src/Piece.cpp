#include "dependencies.h"
#include "Piece.h"

Move::Move(int dirX, int  dirY, int sizeX, int sizeY) : dirX(dirX),
    dirY(dirY), sizeX(sizeX), sizeY(sizeY) {}

Piece::Piece() {}

Pawn::Pawn() : Piece() {
    moves.push_back(new Move(0, -1, 0, 1));
    moves.push_back(new Move(0, -1, 0, 2));
}
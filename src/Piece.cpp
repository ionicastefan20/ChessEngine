#include "dependencies.h"
#include "Piece.h"

Move::Move(int dirX, int dirY, int sizeX, int sizeY) : dirX(dirX),
                                                       dirY(dirY), sizeX(sizeX), sizeY(sizeY) {}

const int Piece::NONE = 0;
const int Piece::PAWN = 1;
const int Piece::ROOK = 2;
const int Piece::KNIGHT = 3;
const int Piece::BISHOP = 4;
const int Piece::QUEEN = 5;
const int Piece::KING = 6;

const int Piece::WHITE = 8;
const int Piece::BLACK = 16;

Piece::Piece() {}

Piece::~Piece() {
    for (auto it = begin(moves); it != end(moves); ++it) {
        delete *it;
    }
}

Pawn::Pawn() : Piece() {
    moves.push_back(new Move(0, -1, 0, 1));
    moves.push_back(new Move(0, -1, 0, 2));
}
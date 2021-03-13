//
// Created by stefan.ionica on 3/13/2021.
//

#include "Board.h"
#include "Piece.h"

int* Board::squares = new int[64];

void Board::initBoard() {
    squares[0] = squares[7] = Piece::WHITE | Piece::ROOK;
    squares[1] = squares[6] = Piece::WHITE | Piece::KNIGHT;
    squares[2] = squares[5] = Piece::WHITE | Piece::BISHOP;
    squares[3] = Piece::WHITE | Piece::QUEEN;
    squares[4] = Piece::WHITE | Piece::KING;
    for (int i = 8; i < 16; i++)
        squares[i] = Piece::WHITE | Piece::PAWN;

    for (int i = 16; i < 48; i++) squares[i] = 0;

    squares[56] = squares[63] = Piece::BLACK | Piece::ROOK;
    squares[57] = squares[62] = Piece::BLACK | Piece::KNIGHT;
    squares[58] = squares[61] = Piece::BLACK | Piece::BISHOP;
    squares[59] = Piece::BLACK | Piece::QUEEN;
    squares[60] = Piece::BLACK | Piece::KING;
    for (int i = 48; i < 56; i++)
        squares[i] = Piece::BLACK | Piece::PAWN;
}
#ifndef EVALUATE_H
#define EVALUATE_H

#include "Piece.h"
#include <string>
#include <unordered_map>

// weight of every piece
#define KingWt 1300
#define QueenWt 900
#define RookWt 500
#define BishopWt 330
#define KnightWt 320
#define PawnWt 100

namespace evaluate {

    // for white
    extern const int wKingTableMid[64];

    extern const int wQueenTable[64];

    extern const int wRookTable[64];

    extern const int wBishopTable[64];

    extern const int wKnightTable[64];

    extern const int wPawnTable[64];

    // for black
    extern const int bKingTableMid[64];

    extern const int bQueenTable[64];

    extern const int bRookTable[64];

    extern const int bKnightTable[64];

    extern const int bBishopTable[64];

    extern const int bPawnTable[64];

    int static_eval(Node root);
};

#endif

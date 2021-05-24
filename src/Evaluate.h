#ifndef CHESSENGINE_EVALUATE_H
#define CHESSENGINE_EVALUATE_H

#include <string>
#include <unordered_map>
#include <float.h>

#include "Move.h"
// #include "MoveGenerator.h"

// weight of every piece
#define KingWt 200
#define QueenWt 30
#define RookWt 17
#define BishopWt 15
#define KnightWt 10
#define PawnWt 8

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

    double static_eval(int botColor);

};

#endif

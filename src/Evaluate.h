#ifndef CHESSENGINE_EVALUATE_H
#define CHESSENGINE_EVALUATE_H

#include <string>
#include <unordered_map>
#include <float.h>

#include "Move.h"
// #include "MoveGenerator.h"

// weight of every piece
#define KingWt 20000
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

    double static_eval(int botColor);

};

#endif

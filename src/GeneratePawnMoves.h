#ifndef CHESSENGINE_GENERATEPAWNMOVES_H
#define CHESSENGINE_GENERATEPAWNMOVES_H

#include <string>
#include "Board.h"
#include "Move.h"
using std::pair;

class GeneratePawnMoves {

public:

    // first 3 bits (less signifiant) -> the black pawns
    // next 3 bits (most signifiant) -> white pawns
    static int currPawn; // 6 bit value
    
    static int lastPos;

    static pair<int, int> generatePawnMove();
};

#endif
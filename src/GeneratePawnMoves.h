#ifndef CHESSENGINE_GENERATEPAWNMOVES_H
#define CHESSENGINE_GENERATEPAWNMOVES_H

#include <string>
#include "Board.h"
#include "Move.h"
using std::pair;

class GeneratePawnMoves {

public:

    static int currPawn;

    static int lastPos;

    static pair<int, int> generatePawnMove();
};

#endif
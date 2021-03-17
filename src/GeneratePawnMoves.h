#ifndef CHESSENGINE_GENERATEPAWNMOVES_H
#define CHESSENGINE_GENERATEPAWNMOVES_H

#include <string>
using std::pair;

class GeneratePawnMoves {

public:

    static int currPawn;

    static int lastPos;

    pair<int, int> generatePawnMove();
};

#endif
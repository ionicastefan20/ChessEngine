#ifndef CHESSENGINE_MOVE_GENERATOR_H
#define CHESSENGINE_MOVE_GENERATOR_H

#include <string>
#include <vector>
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include <time.h>
using std::pair;

class MoveGenerator {

public:

    static pair<int, int> generateMove();
};

#endif

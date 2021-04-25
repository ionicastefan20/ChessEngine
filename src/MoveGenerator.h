#ifndef CHESSENGINE_MOVE_GENERATOR_H
#define CHESSENGINE_MOVE_GENERATOR_H

#include <string>
#include <vector>
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include <time.h>

namespace moveGenerator {

    std::pair<std::string, std::pair<int, int>> generateMove();

};

#endif

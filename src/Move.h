#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H

#include <unordered_map>
#include <string>
#include <vector>
#include "Board.h"

using std::vector;
using std::string;
using std::unordered_map;

#define __min(a,b) (((a) < (b)) ? (a) : (b))

class Move {

public:
    static unordered_map<string, int> DIRECTIONS;

    static vector<unordered_map<string, int>> numUntilEdge;

    static void initDistancesAndDirections();
};

#endif

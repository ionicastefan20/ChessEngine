#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H

#include <unordered_map>
#include <string>
#include <vector>
#include "Board.h"
#include "Piece.h"

using std::vector;
using std::string;
using std::unordered_map;

#define __min(a,b) (((a) < (b)) ? (a) : (b))

class Move {

private:
    static void generatePawnMoves();
    static void generateKnightMoves();
    static void generateKingMoves();
    static void generateLongMoves();

public:
    static unordered_map<string, int> DIRECTIONS;

    static vector<unordered_map<string, int>> numUntilEdge;

    static vector<bool> squaresAttacked;

    static std::unordered_map<int, std::vector<int>> moves;

    static void generate();

    // analyze the board state and generate for the piece to move all attacked
    // spots on the board (true for attacked, false for not attacked)
    static void calculateSquaresAttacked();

    static void initDistancesAndDirections();
};

#endif

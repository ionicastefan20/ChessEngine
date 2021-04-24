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

    static void generatePawnMoves(int pos);

    static void generateKnightMoves(int pos);

    static void generateKingMoves(int pos);

    static void generateBishopMoves(int pos);

    static void generateRookMoves(int pos);

public:

    static unordered_map<string, int> DIRECTIONS;

    static vector<unordered_map<string, int>> numUntilEdge;

    static std::unordered_map<int, std::vector<int>> moves;

    static void generate();

    static void initDistancesAndDirections();
};

#endif

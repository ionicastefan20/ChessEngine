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

    static std::vector<int> generatePawnMoves(int pos);

    static std::vector<int> generateKnightMoves(int pos);

    static std::vector<int> generateKingMoves(int pos);

    static std::vector<int> generateBishopMoves(int pos);

    static std::vector<int> generateRookMoves(int pos);

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

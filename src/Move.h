#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H

#include <unordered_map>
#include <string>
#include <vector>
#include "Board.h"
#include "Piece.h"

#define __min(a,b) (((a) < (b)) ? (a) : (b))

namespace move {

    extern std::unordered_map<std::string, int> directions;

    extern std::vector<std::unordered_map<std::string, int>> numUntilEdge;

    extern std::vector<bool> squaresAttacked;

    extern std::unordered_map<int, std::vector<int>> moves;

    std::vector<int> generatePawnMoves(int pos);

    std::vector<int> generateKnightMoves(int pos);

    std::vector<int> generateKingMoves(int pos);

    std::vector<int> generateBishopMoves(int pos);

    std::vector<int> generateRookMoves(int pos);

    void generate();

    // analyze the board state and generate for the piece to move all attacked
    // spots on the board (true for attacked, false for not attacked)
    void calculateSquaresAttacked();

    void initDistancesAndDirections();
};

#endif

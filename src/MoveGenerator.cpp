#include "MoveGenerator.h"

pair<int, int> MoveGenerator::generateMove() {
    Move::calculateSquaresAttacked();
    Move::generate();
    srand(time(NULL));

    // iterate through pieces and for the first piece that has valid move,
    // for the first one pick a random future position and make the move.
    vector<int> nonZeroMoves; // keeps starting position

    for (auto entry : Move::moves) {
        if (entry.second.size() != 0)
            nonZeroMoves.push_back(entry.first);
    }

    int randomPiece = rand() % nonZeroMoves.size();
    int randomMove = rand() % Move::moves[nonZeroMoves[randomPiece]].size();

    return std::make_pair(nonZeroMoves[randomPiece],
                          Move::moves[nonZeroMoves[randomPiece]][randomMove]);
}
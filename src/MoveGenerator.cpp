#include "MoveGenerator.h"
#include <fstream>

pair<int, int> MoveGenerator::generateMove() {
    std::ofstream fout2("out2", std::ofstream::app);

    fout2 << "da1" << std::endl;
    Move::calculateSquaresAttacked();
    fout2 << "da2" << std::endl;
    Move::generate();
    fout2 << "da3" << std::endl;
    srand(time(NULL));

    // iterate through pieces and for the first piece that has valid move,
    // for the first one pick a random future position and make the move.
    vector<int> nonZeroMoves; // keeps starting position

    for (auto entry : Move::moves) {
        if (entry.second.size() != 0)
            nonZeroMoves.push_back(entry.first);
    }

    fout2 << "da4: " << nonZeroMoves.size() << std::endl;

    int randomPiece = std::rand() % nonZeroMoves.size();
    fout2 << "randomPiece: " << randomPiece << std::endl;
    int randomMove = std::rand() % Move::moves[nonZeroMoves[randomPiece]].size();
    fout2 << "randomMove: " << randomMove << std::endl;

    fout2 << "da5" << std::endl;
    
    return std::make_pair(nonZeroMoves[randomPiece],
                          Move::moves[nonZeroMoves[randomPiece]][randomMove]);
}
#include "MoveGenerator.h"
#include <fstream>

extern int board::colorOnMove;
extern int board::botColor;
extern bool board::isPlaying;
extern int board::kingPos;

extern std::unordered_map<std::string, int> move::directions;
extern std::vector<std::unordered_map<std::string, int>> move::numUntilEdge;
extern std::vector<bool> move::squaresAttacked;
extern std::unordered_map<int, std::vector<int>> move::moves;

std::pair<int, int> moveGenerator::generateMove() {
    // std::ofstream fout2("out2", std::ofstream::app);

    // fout2 << "da1" << std::endl;
    // move::calculateSquaresAttacked();
    // fout2 << "da2" << std::endl;
    move::generate();
    // fout2 << "da3" << std::endl;
    srand(time(NULL));

    // iterate through pieces and for the first piece that has valid move,
    // for the first one pick a random future position and make the move.
    std::vector<int> nonZeroMoves; // keeps starting position

    for (auto entry : move::moves) {
        if (entry.second.size() != 0)
            nonZeroMoves.push_back(entry.first);
    }

    // fout2 << "da4: " << nonZeroMoves.size() << std::endl;

    int randomPiece = std::rand() % nonZeroMoves.size();
    // fout2 << "randomPiece: " << randomPiece << std::endl;
    int randomMove = std::rand() % move::moves[nonZeroMoves[randomPiece]].size();
    // fout2 << "randomMove: " << randomMove << std::endl;

    // fout2 << "da5" << std::endl;

    return std::make_pair(nonZeroMoves[randomPiece],
                          move::moves[nonZeroMoves[randomPiece]][randomMove]);
}
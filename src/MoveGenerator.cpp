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

static int contor = 0;
static std::vector<std::pair<int, int>> mymoves{
    {49, 33},
    {33, 25},
    {25, 18}
};

// returns padding for promotion or empty string for a non-promotion
std::string checkForPromotionAndRandom(std::pair<int, int> move) {
    srand(time(NULL));
    std::string all_promotions[4] = {"q", "r", "n", "b"};
    int all_promotions_values[4] = {piece::QUEEN, piece::ROOK, piece::KNIGHT, piece::BISHOP};

    int random_promotion_index = rand() % 4;
    std::string random_promotion = all_promotions[random_promotion_index];

    if (board::squares[move.first] == (piece::PAWN | piece::BLACK)) {
        // for black pawn check if its final move it's on the first row
        if (move.second <= 7 && move.second >= 0) {
            board::squares[move.first] =  all_promotions_values[random_promotion_index] | piece::BLACK;
            return random_promotion;
        }
    } else if (board::squares[move.first] == (piece::PAWN | piece::WHITE)) {
        // for white pawn check if its final move it's on the top (last) row
        if (move.second <= 63 && move.second >= 56) {
            board::squares[move.first] =  all_promotions_values[random_promotion_index] | piece::WHITE;
            return random_promotion;
        }
    }

    return "";
}

// std::pair<std::string, std::pair<int, int>> moveGenerator::generateMove() {
//     std::ofstream fout2("out2", std::ofstream::app);

//     fout2 << "genMove: in" << std::endl;
//     fout2 << "kingpos: " << board::kingPos << std::endl;
//     // fout2 << "da1" << std::endl;
//     move::calculateSquaresAttacked();
//     // fout2 << "da2" << std::endl;
//     move::generate();

//     std::string padding = checkForPromotionAndRandom(mymoves[contor]);
//     // fout2 << "genMove: out" << std::endl;

//     std::pair<std::string, std::pair<int, int>> aux(padding, mymoves[contor++]);
//     return aux;

//     // return std::make_pair(padding, move);
// }

std::pair<std::string, std::pair<int, int>> moveGenerator::generateMove() {
    std::ofstream fout2("out2", std::ofstream::app);

    fout2 << "genMove: in" << std::endl;
    fout2 << "kingpos: " << board::kingPos << std::endl;
    // fout2 << "da1" << std::endl;
    move::calculateSquaresAttacked();
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
    std::pair<int, int> move = std::make_pair(nonZeroMoves[randomPiece],
                          move::moves[nonZeroMoves[randomPiece]][randomMove]);
    std::string padding = checkForPromotionAndRandom(move);
    // fout2 << "genMove: out" << std::endl;

    std::pair<std::string, std::pair<int, int>> aux(padding, move);
    return aux;

    // return std::make_pair(padding, move);
}
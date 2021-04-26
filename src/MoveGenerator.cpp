#include "MoveGenerator.h"
#include "Logger.h"

extern int board::colorOnMove;
extern int board::botColor;
extern bool board::isPlaying;
extern int board::kingPos;

extern std::unordered_map<std::string, int> move::directions;
extern std::vector<std::unordered_map<std::string, int>> move::numUntilEdge;
extern std::vector<bool> move::squaresAttacked;
extern std::unordered_map<int, std::vector<int>> move::moves;

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

static int contor = 0;
static std::vector<std::pair<int, int>> first_moves = {
    {49, 33},
    {33, 25}
};

// std::pair<std::string, std::pair<int, int>> moveGenerator::generateMove() {

//     move::calculateSquaresAttacked();
//     move::generate();
//     srand(time(NULL));

//     // iterate through pieces and for the first piece that has valid move,
//     // for the first one pick a random future position and make the move.
//     std::vector<int> nonZeroMoves; // keeps starting position


//     std::pair<int, int> move;
//     if (contor < 2) {
//         move = first_moves[contor++];
//     } else {
//         for (auto entry : move::moves) {
//             if (entry.first == 25)
//                 nonZeroMoves.push_back(entry.first);
//         }

//         int randomPiece = std::rand() % nonZeroMoves.size();
//         int randomMove = std::rand() % move::moves[nonZeroMoves[randomPiece]].size();
//         logger::log("generate -> moves no", std::to_string(move::moves[nonZeroMoves[randomPiece]].size()), 1);
//         logger::log("generate -> enPassant", std::to_string(move::enPassantMove), 1);
//         move = std::make_pair(nonZeroMoves[randomPiece],
//                             move::moves[nonZeroMoves[randomPiece]][randomMove]);
//     }
//     std::string padding = checkForPromotionAndRandom(move);

//     std::pair<std::string, std::pair<int, int>> aux(padding, move);
//     return aux;
// }

std::pair<std::string, std::pair<int, int>> moveGenerator::generateMove() {

    move::calculateSquaresAttacked();
    move::generate();
    srand(time(NULL));

    // iterate through pieces and for the first piece that has valid move,
    // for the first one pick a random future position and make the move.
    std::vector<int> nonZeroMoves; // keeps starting position

    for (auto entry : move::moves) {
        if (entry.second.size() != 0)
            nonZeroMoves.push_back(entry.first);
    }

    if (nonZeroMoves.size() == 0) {  // checkmate or stalemate
        std::pair<int, int> resignMove(-1, -1);
        std::pair<std::string, std::pair<int, int>> aux("", resignMove);
        return aux;
    }

    int randomPiece = std::rand() % nonZeroMoves.size();
    int randomMove = std::rand() % move::moves[nonZeroMoves[randomPiece]].size();
    std::pair<int, int> move = std::make_pair(nonZeroMoves[randomPiece],
                          move::moves[nonZeroMoves[randomPiece]][randomMove]);
    std::string padding = checkForPromotionAndRandom(move);

    std::pair<std::string, std::pair<int, int>> aux(padding, move);
    return aux;
}
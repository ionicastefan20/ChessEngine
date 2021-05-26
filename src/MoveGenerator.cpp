#include "MoveGenerator.h"

extern int board::colorOnMove;
extern int board::botColor;
extern bool board::isPlaying;
extern int board::kingPos, whiteKingPos, blackKingPos;
extern int board::squares[64];
extern std::unordered_map<char, int> board::materials;
extern std::vector<bool> board::botSquaresAttacked;

extern std::unordered_map<std::string, int> move::directions;
extern std::vector<std::unordered_map<std::string, int>> move::numUntilEdge;
extern std::vector<bool> move::squaresAttacked;
extern std::unordered_map<int, std::vector<int>> move::moves;

namespace moveGenerator {
    Node curr_node;
}

void moveGenerator::init_materials() {
    // Black's Pieces
    board::materials['p'] = 8;
    board::materials['r'] = 2;
    board::materials['n'] = 2;
    board::materials['b'] = 2;
    board::materials['q'] = 1;
    board::materials['k'] = 1;

    // White's Pieces
    board::materials['P'] = 8;
    board::materials['R'] = 2;
    board::materials['N'] = 2;
    board::materials['B'] = 2;
    board::materials['Q'] = 1;
    board::materials['K'] = 1;
}

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


BState moveGenerator::make_copy(int botColor) {
    BState copy = new board_state;

    copy->enPassantMove = move::enPassantMove;
    copy->leftBlackRook = move::leftBlackRook;
    copy->leftWhiteRook = move::leftWhiteRook;
    copy->rightBlackRook = move::rightBlackRook;
    copy->rightWhiteRook = move::rightWhiteRook;
    copy->whiteKing = move::whiteKing;
    copy->blackKing = move::blackKing;

    copy->colorOnMove = board::colorOnMove;
    copy->botColor = board::botColor;
    copy->kingPos = board::kingPos;
    copy->whiteKingPos = board::whiteKingPos;
    copy->blackKingPos = board::blackKingPos;

    memcpy(copy->squares, board::squares, 64 * sizeof(int));
    copy->squaresAttacked = move::squaresAttacked;
    copy->botSquaresAttacked = board::botSquaresAttacked;
    copy->materials = board::materials;

    return copy;
}

void moveGenerator::restore_copy(BState copy) {
    move::enPassantMove = copy->enPassantMove;
    move::leftBlackRook = copy->leftBlackRook;
    move::leftWhiteRook = copy->leftWhiteRook;
    move::rightBlackRook = copy->rightBlackRook;
    move::rightWhiteRook = copy->rightWhiteRook;
    move::whiteKing = copy->whiteKing;
    move::blackKing = copy->blackKing;

    board::colorOnMove = copy->colorOnMove;
    board::botColor = copy->botColor;
    board::kingPos = copy->kingPos;
    board::whiteKingPos = copy->whiteKingPos;
    board::blackKingPos = copy->blackKingPos;

    memcpy(board::squares, copy->squares, 64 * sizeof(int));
    move::squaresAttacked = copy->squaresAttacked;
    board::botSquaresAttacked = copy->botSquaresAttacked;
    board::materials = copy->materials;
}


std::pair<std::string, std::pair<int, int>> moveGenerator::generateMove() {
    int start = - 1, end = -1;

    double best_score = negamax_alpha_beta(0, 0, start, end, 0, -DBL_MAX, DBL_MAX, board::botColor);

    std::pair<int, int> move(start, end);
    std::string padding = checkForPromotionAndRandom(move);

    std::pair<std::string, std::pair<int, int>> aux(padding, move);
    return aux;
}
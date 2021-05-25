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


// void populate_arb_recursively(Node& root, int level) {
//     // logger::log("SIZE", std::to_string(root->next.size()), 1);
//     // logger::log("MDAAAP", "DA", 0);
//     if (level == MAX_DEPTH)
//         return;

//     // make copy of moves
//     std::unordered_map<int, std::vector<int>> moves_copy;
//     for (auto move : move::moves) {
//         std::vector<int> next_moves_copy(move.second);
//         moves_copy[move.first] = next_moves_copy;
//     }

//     int i = 0;
//     for (auto move : moves_copy) {  // for every legal pair of moves (start -> end)
//         int start = move.first;
//         for (auto legal_move : move.second) {
//             int end = legal_move;

//             // logger::log("i", std::to_string(i++), 4);
//             BState copy = moveGenerator::make_copy();
//             board::makeMove(board::encodeMove(std::pair<int, int>(start, end)));
//             board::botColor = board::getOppositeBotColor(board::botColor);
//             move::calculateSquaresAttacked();
//             move::generate();

//             // logger::log("size pre", std::to_string(move::squaresAttacked.size()), 1);
//             Node child = node::tree_insert(root, start, end);
//             // logger::log("size post", std::to_string(child->squaresAttacked.size()), 1);
//             if (child != NULL)
//                 populate_arb_recursively(child, level + 1);

//             moveGenerator::restore_copy(copy);
//         }
//     }

//     // restore copy
//     move::moves.clear();
//     for (auto move_cpy : moves_copy) {
//         move::moves[move_cpy.first] = move_cpy.second;
//     }
// }

// void populate_arb(Node& root) {
//     root->next.clear();  // eliminate previous children
//     BState copy;

//     copy = moveGenerator::make_copy();
//     move::calculateSquaresAttacked();
//     move::generate();

//     populate_arb_recursively(root, 0);
//     moveGenerator::restore_copy(copy);
// }

std::pair<std::string, std::pair<int, int>> moveGenerator::generateMove() {
    int start = - 1, end = -1;

    // std::pair<int, int> best_move;
    // double best_score = -DBL_MAX;
    // move::calculateSquaresAttacked();
    // move::generate();
    // std::unordered_map<int, std::vector<int>> moves_copy;
    // for (auto move : move::moves) {
    //     std::vector<int> next_moves_copy(move.second);
    //     moves_copy[move.first] = next_moves_copy;
    // }
    // for (auto move : moves_copy) {  // for every legal pair of moves (start -> end)
    //     int start_init = move.first;
    //     for (auto end_init : move.second) {
    double best_score = negamax_alpha_beta(0, 0, start, end, 0, -DBL_MAX, DBL_MAX, board::botColor);
    logger::log("ScoreFinal", std::to_string(best_score), 0);
    logger::log("Start", std::to_string(start), 0);
    logger::log("End", std::to_string(end), 0);
    //         if (score > best_score) {
    //             best_score = score;
    //             best_move = {start, end};
    //         }
    //     }
    // }


    std::pair<int, int> move(start, end);
    std::string padding = checkForPromotionAndRandom(move);

    std::pair<std::string, std::pair<int, int>> aux(padding, move);
    return aux;
}
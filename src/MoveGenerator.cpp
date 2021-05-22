#include "MoveGenerator.h"
#include "Logger.h"

#include <iostream>

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

void init_materials(std::unordered_map<char, int>& m){
    // Black's Pieces
    m.insert(std::pair<char, int>('p', 8));
    m.insert(std::pair<char, int>('r', 2));
    m.insert(std::pair<char, int>('n', 2));
    m.insert(std::pair<char, int>('b', 2));
    m.insert(std::pair<char, int>('q', 1));
    m.insert(std::pair<char, int>('k', 1));

    // White's Pieces
    m.insert(std::pair<char, int>('P', 8));
    m.insert(std::pair<char, int>('R', 2));
    m.insert(std::pair<char, int>('N', 2));
    m.insert(std::pair<char, int>('B', 2));
    m.insert(std::pair<char, int>('Q', 1));
    m.insert(std::pair<char, int>('K', 1));
}

BState make_copy() {
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

    memcpy(copy->squares, board::squares, 64);
    
    return copy;
}

void restore_copy(BState copy) {
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

    memcpy( board::squares, copy->squares, 64);
}

Node populate_arb_one_level(Node& root) {

    for (auto move : move::moves) {  // for every legal pair of moves (start -> end)
        int start = move.first;
        for (auto legal_move : move.second) {
            int end = legal_move;
            tree_insert(root, start, end);
        }
    }
}

Node populate_arb() { 
    Node root = new tNode;
    Node root_to_return = root;
    BState copy;

    init_materials(root->materials);
    root->colorOnMove = board::colorOnMove;
    root->blackKingPos = board::blackKingPos;
    root->whiteKingPos = board::whiteKingPos;

    copy = make_copy();
    move::calculateSquaresAttacked();
    move::generate();
    populate_arb_one_level(root);

    for (int i = 1; i < MAX_DEPTH; i++) {
        BState temp_copy = make_copy();
        for (auto child : root->next)
            

    }
}

std::pair<std::string, std::pair<int, int>> moveGenerator::generateMove() {

    // move::calculateSquaresAttacked();
    // move::generate();
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
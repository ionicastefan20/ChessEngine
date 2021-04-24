#include "Move.h"
#include <fstream>

unordered_map<string, int> Move::DIRECTIONS;

vector<unordered_map<string, int>> Move::numUntilEdge;

void Move::initDistancesAndDirections() {
    Move::DIRECTIONS = {
        {"left", -1},
        {"left_up", 7},
        {"up", 8},
        {"up_right", 9},
        {"right", 1},
        {"right_down", -7},
        {"down", -8},
        {"down_left", -9}
    };

    for (int i = 0; i < 8; i++) // i = 6, j = 1
        for (int j = 0; j < 8; j++) {
            int numUp = 7 - i; // 6
            int numDown = i; // 1
            int numLeft = j; //
            int numRight = 7 - j;

            unordered_map<string, int> distances = {
                {"left", numLeft},
                {"left_up", __min(numLeft, numUp)},
                {"up", numUp},
                {"up_right", __min(numUp, numRight)},
                {"right", numRight},
                {"right_down", __min(numRight, numDown)},
                {"down", numDown},
                {"down_left", __min(numDown, numLeft)}
            };

            Move::numUntilEdge.push_back(distances);
        }
}

void Move::generate() {
    moves.clear();

    for (int i = 0; i < 64; ++i) {
        if (Board::botColor && Board::squares[i]) {
            switch (Board::squares[i] && (~(1 << 3))) {
                case Piece::PAWN:
                    generatePawnMoves();
                    break;
                case Piece::ROOK:
                    generateRookMoves();
                    break;
                case Piece::KNIGHT:
                    generateKnightMoves();
                    break;
                case Piece::BISHOP:
                    generateBishopMoves();
                    break;
                case Piece::QUEEN:
                    generateRookMoves();
                    generateBishopMoves();
                    break;
                case Piece::KING:
                    generateKingMoves();
                    break;
                default:
                    break;
            }
        }
    }
}

void Move::calculateSquaresAttacked() {
    squaresAttacked.clear();

    // iterate over the squares, over the current state of the board
    for (int i = 0; i < 64; i++) {
        if ()

}

void Move::generateRookMoves() {

}

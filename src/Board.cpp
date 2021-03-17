#include "Board.h"
#include <cstring>

int* Board::squares = new int[64];

void Board::initBoard() {
    squares[0] = squares[7] = Piece::WHITE | Piece::ROOK;
    squares[1] = squares[6] = Piece::WHITE | Piece::KNIGHT;
    squares[2] = squares[5] = Piece::WHITE | Piece::BISHOP;
    squares[3] = Piece::WHITE | Piece::QUEEN;
    squares[4] = Piece::WHITE | Piece::KING;
    for (int i = 8; i < 16; i++)
        squares[i] = Piece::WHITE | Piece::PAWN;

    for (int i = 16; i < 48; i++) squares[i] = 0;

    squares[56] = squares[63] = Piece::BLACK | Piece::ROOK;
    squares[57] = squares[62] = Piece::BLACK | Piece::KNIGHT;
    squares[58] = squares[61] = Piece::BLACK | Piece::BISHOP;
    squares[59] = Piece::BLACK | Piece::QUEEN;
    squares[60] = Piece::BLACK | Piece::KING;
    for (int i = 48; i < 56; i++)
        squares[i] = Piece::BLACK | Piece::PAWN;
}

string Board::convertToCode(int square) {
    string s(1, 'a' + (square % 8));
    s += std::to_string(square / 8 + 1);

    return s;
}

int Board::convertToInt(string code) {
    char *c = new char[code.length()];
    std::strcpy(c, code.c_str());

    int result = (c[0] - 'a') + (atoi(&c[1]) - 1) * 8;
    delete c;
    return result;
}

/**
 * Receives a pair of indexes from the Board::squares and returns a string
 * representing the move : "a3a4"
 */
static string encodeMove(pair<int, int> move) {
    return "" + (move.first / 8 + 'a') + (move.first % 10 + '0') +
            (move.second / 8 + 'a') + (move.second % 10 + '0');
}

/**
 * Receives a move in a string format "a3a4" and converts it into an index
 * for the Board::squares array, reffering to the spot on the board
 * that it represents
 */
static pair<int, int> decodeMove(string move) {
    return std::make_pair((move[0] - 'a') * 8 + (move[1] - '0'),
                          (move[2] - 'a') * 8 + (move[3] - '0'));
}

void Board::makeMove(string move) {
    pair<int, int> result = decodeMove(move);
    squares[result.second] = squares[result.first];
    squares[result.first] = 0;
}
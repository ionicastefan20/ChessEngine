#include "Board.h"
#include <cstring>
#include <fstream>

namespace board {
    int colorOnMove = piece::WHITE;
    int botColor = piece::BLACK;
    bool isPlaying = true;
    int kingPos = 60;
    int blackKingPos = 60;
    int whiteKingPos = 4;
    int squares[64];
}

int board::getOppositeBotColor(int color) {
    return color ^ (8 + 16); // bitwise xor with a mask of 11000
    // which will make the color 01000 ^ 11000 = 10000 the other color
}

void board::initBoard() {
    // remove in future updates
    // GeneratePawnMoves::currPawn = 1;
    // GeneratePawnMoves::setBlackLastPos(48);
    // GeneratePawnMoves::setWhiteLastPos(15);

    squares[0] = squares[7] = piece::WHITE | piece::ROOK;
    squares[1] = squares[6] = piece::WHITE | piece::KNIGHT;
    squares[2] = squares[5] = piece::WHITE | piece::BISHOP;
    squares[3] = piece::WHITE | piece::QUEEN;
    squares[4] = piece::WHITE | piece::KING;
    for (int i = 8; i < 16; i++)
        squares[i] = piece::WHITE | piece::PAWN;

    for (int i = 16; i < 48; i++) squares[i] = 0;

    squares[56] = squares[63] = piece::BLACK | piece::ROOK;
    squares[57] = squares[62] = piece::BLACK | piece::KNIGHT;
    squares[58] = squares[61] = piece::BLACK | piece::BISHOP;
    squares[59] = piece::BLACK | piece::QUEEN;
    squares[60] = piece::BLACK | piece::KING;
    for (int i = 48; i < 56; i++)
        squares[i] = piece::BLACK | piece::PAWN;
}

/**
 * Receives a pair of indexes from the board::squares and returns a string
 * representing the move : "a3a4"
 */
std::string board::encodeMove(std::pair<int, int> move) {
    std::string retMove = "";
    retMove.push_back( (char) (move.first % 8 + 'a'));
    retMove.push_back( (char) (move.first / 8  + 1 + '0'));
    retMove.push_back( (char) (move.second % 8 + 'a'));
    retMove.push_back( (char) (move.second / 8 + 1 + '0'));
    return retMove;
}

/**
 * Receives a move in a string format "a3a4" and converts it into an index
 * for the Board::squares array, reffering to the spot on the board
 * that it represents
 */
std::pair<int, int> board::decodeMove(std::string move) {
    return std::make_pair((move[0] - 'a') + (move[1] - '0' - 1) * 8,
                          (move[2] - 'a') + (move[3] - '0' - 1) * 8);
}

void board::makeMove(std::string move) {
    colorOnMove = getOppositeBotColor(colorOnMove); // set the oposite color;
    std::pair<int, int> result = decodeMove(move); //b2b4
    squares[result.second] = squares[result.first];
    squares[result.first] = 0;
}
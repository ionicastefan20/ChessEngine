#include "Board.h"
#include <cstring>
#include <fstream>

int* Board::squares = new int[64];

int Board::botColor = Piece::BLACK;

bool Board::isPlaying = true;

int Board::colorOnMove = Piece::WHITE;

int Board::getOpositeBotColor(int color) {
    return color ^ (8 + 16); // bitwise xor with a mask of 11000
    // which will make the color 01000 ^ 11000 = 10000 the other color
}

void Board::initBoard() {
    // remove in future updates
    GeneratePawnMoves::currPawn = 1;
    GeneratePawnMoves::setBlackLastPos(48);
    GeneratePawnMoves::setWhiteLastPos(15);
    colorOnMove = Piece::WHITE;

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

    Board::botColor = Piece::BLACK;
    Board::isPlaying = true;
}

/**
 * Receives a pair of indexes from the Board::squares and returns a string
 * representing the move : "a3a4"
 */
string Board::encodeMove(pair<int, int> move) {
    string retMove = "";
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
pair<int, int> Board::decodeMove(string move) {
    return std::make_pair((move[0] - 'a') + (move[1] - '0' - 1) * 8,
                          (move[2] - 'a') + (move[3] - '0' - 1) * 8);
}

void Board::makeMove(string move) {
    colorOnMove = getOpositeBotColor(colorOnMove); // set the oposite color;
    pair<int, int> result = decodeMove(move); //b2b4
    squares[result.second] = squares[result.first];
    squares[result.first] = 0;
}
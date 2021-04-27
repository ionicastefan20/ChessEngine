#include "Board.h"
#include <cstring>
#include <fstream>
#include "Move.h"
#include "Logger.h"

extern int move::enPassantMove;
extern int move::leftWhiteRook;
extern int move::rightWhiteRook;
extern int move::leftBlackRook;
extern int move::rightBlackRook;
extern int move::whiteKing;
extern int move::blackKing;

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

    colorOnMove = piece::WHITE;
    botColor = piece::BLACK;
    isPlaying = true;
    kingPos = 60;
    blackKingPos = 60;
    whiteKingPos = 4;
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
    logger::log("board makeMove", move, 0);

    std::pair<int, int> result = decodeMove(move); //b2b4

    // en passant update
    move::enPassantMove = -1;
    logger::log("makeMove first", std::to_string(board::squares[result.first]), 1);
    logger::log("makeMove second", std::to_string(board::squares[result.second]), 1);
    // logger::log("makeMove ce pzm", std::to_string((board::squares[result.first] & 7) == piece::PAWN), 1);
    if ((colorOnMove == botColor) && ((board::squares[result.first] & 7) == piece::PAWN)) { // colorOnMove keeps the future color, so the "future" color of the enemy is now the bot color
        logger::log("makeMove", "yes i am pawn", 1);
        if (botColor & piece::WHITE) {
            if ((result.first >= 48 && result.first <= 55) &&
                    (result.second - result.first == -16))
                move::enPassantMove = result.second;
        } else {
            if ((result.first >= 8 && result.first <= 15) &&
                    (result.second - result.first == 16))
                move::enPassantMove = result.second;
        }
    }

    // castle update
    if (board::squares[result.first] & 7 == piece::KING) {
        if (board::squares[result.first] & piece::WHITE)
            move::whiteKing = 0;
        else
            move::blackKing = 0;
    }
    if (board::squares[result.first] & 7 == piece::ROOK) {
        if (board::squares[result.first] & piece::WHITE) {
            if (result.first == 0)
                move::leftWhiteRook = 0;
            else if (result.first == 7)
                move::rightWhiteRook = 0;
        }
        else {
            if (result.first == 56)
                move::leftBlackRook = 0;
            else if (result.first == 63)
                move::rightBlackRook = 0;
        }
    }

    // apply en passant
    logger::log("makeMove res first", std::to_string(result.first), 1);
    logger::log("makeMove res second", std::to_string(result.second), 1);
    if (((board::squares[result.first] & 7) == piece::PAWN) &&
            ((result.second - result.first) % 2 != 0) && (board::squares[result.second] == 0)) {
        if (board::squares[result.first] & piece::WHITE)
            board::squares[result.second - 8] = 0;
        else
            board::squares[result.second + 8] = 0;
    }

    squares[result.second] = squares[result.first];
    squares[result.first] = 0;



    if (move.size() == 5) {
        if (move[4] == 'q')
            squares[result.second] = (piece::QUEEN | getOppositeBotColor(colorOnMove));
        else if (move[4] == 'b')
            squares[result.second] = (piece::BISHOP | getOppositeBotColor(colorOnMove));
        else if (move[4] == 'r')
            squares[result.second] = (piece::ROOK | getOppositeBotColor(colorOnMove));
        else
            squares[result.second] = (piece::KNIGHT | getOppositeBotColor(colorOnMove));
    }

}
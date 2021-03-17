#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

#include "Piece.h"
#include <string>
using std::string;
using std::pair;

class Board {

public:
    static int* squares;

    static void initBoard();

    static string convertToCode(int square);

    static int convertToInt(string code);

    pair<int, int> decodeMove(string move);

    void makeMove(string move);
};

#endif

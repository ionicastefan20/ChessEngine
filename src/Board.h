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

    static pair<int, int> decodeMove(string move);

    static void makeMove(string move);
};

#endif

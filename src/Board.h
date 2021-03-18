#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

#include "Piece.h"
#include "GeneratePawnMoves.h"
#include <string>

using std::string;
using std::pair;

class Board {

public:
    static int colorOnMove; // which color needs to move next

    static int botColor;

    static bool isPlaying;

    static int* squares;

    static void initBoard();

    static string encodeMove(pair<int, int> move);

    static pair<int, int> decodeMove(string move);

    static void makeMove(string move);
};

#endif

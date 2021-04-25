#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

#include "Piece.h"
#include <string>

namespace board {

    extern int colorOnMove; // which color needs to move next

    extern int botColor;

    extern bool isPlaying;

    extern int kingPos;

    extern int squares[64]; // main board table

    int getOppositeBotColor(int color);

    void initBoard();

    std::string encodeMove(std::pair<int, int> move);

    std::pair<int, int> decodeMove(std::string move);

    void makeMove(std::string move);
};

#endif

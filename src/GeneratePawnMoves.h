#ifndef CHESSENGINE_GENERATEPAWNMOVES_H
#define CHESSENGINE_GENERATEPAWNMOVES_H

#include <string>
#include "Board.h"
#include "Move.h"
using std::pair;

class GeneratePawnMoves {

public:

    // first 3 bits (less signifiant) -> the black pawns
    // next 3 bits (most signifiant) -> white pawns
    static int currPawn; // 6 bit value
    
    // first 6 bits (less signifiant) -> the black pawns
    // next 6 bits (most signifiant) -> white pawns
    static int lastPos; // 12 bit value

    static int getWhiteLastPos();

    static int getBlackLastPos();

    static int getLastPosForCurrentColor();

    static void setWhiteLastPos(int value);

    static void setBlackLastPos(int value);

    static void setLastPosForCurrentColor(int value);

    static int getWhiteCurrPawn();

    static int getBlackCurrPawn();

    static void setWhiteCurrPawn(int value);

    static void setBlackCurrPawn(int value);

    static pair<int, int> generatePawnMove();
};

#endif
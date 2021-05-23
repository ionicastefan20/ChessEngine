#ifndef CHESSENGINE_MOVE_GENERATOR_H
#define CHESSENGINE_MOVE_GENERATOR_H

#include <string>
#include <vector>
#include <time.h>
#include <iostream>
#include <float.h>
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "Minimax.h"
#include "Logger.h"
#include "Node.h"

struct board_state {
    int enPassantMove;
    int leftWhiteRook;
    int rightWhiteRook;
    int leftBlackRook;
    int rightBlackRook;
    int whiteKing;
    int blackKing;

    int colorOnMove;
    int botColor;
    int kingPos, whiteKingPos, blackKingPos;
    int squares[64];
};
typedef struct board_state* BState;

typedef struct tNode* Node;

namespace moveGenerator {

    extern Node curr_node;

    std::pair<std::string, std::pair<int, int>> generateMove();

    Node init_node();

    BState make_copy();

    void restore_copy(BState copy);
};

#endif

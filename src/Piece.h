#ifndef CHESSENGINE_PIECE_H
#define CHESSENGINE_PIECE_H

#pragma once

#include <unordered_map>

namespace piece {

    enum Constants {
        NONE = 0,
        PAWN = 1,
        ROOK = 2,
        KNIGHT = 3,
        BISHOP = 4,
        QUEEN = 5,
        KING = 6,

        WHITE = 8,
        BLACK = 16
    };

    extern std::unordered_map<int, char> map;

};

#endif
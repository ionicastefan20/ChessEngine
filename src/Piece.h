#ifndef CHESSENGINE_PIECE_H
#define CHESSENGINE_PIECE_H

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

    std::unordered_map<char, int> map({
        {QUEEN  | WHITE, 'Q'},
        {QUEEN  | BLACK, 'q'},
        {KING   | WHITE, 'K'},
        {KING   | BLACK, 'k'},
        {ROOK   | WHITE, 'R'},
        {ROOK   | BLACK, 'r'},
        {PAWN   | WHITE, 'P'},
        {PAWN   | BLACK, 'p'},
        {KNIGHT | WHITE, 'N'},
        {KNIGHT | BLACK, 'n'},
        {BISHOP | WHITE, 'B'},
        {BISHOP | BLACK, 'b'},
        {PAWN   | WHITE, 'P'},
        {PAWN   | BLACK, 'p'}
    });

};

#endif
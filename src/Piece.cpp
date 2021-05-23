#include "Piece.h"

namespace piece {
    std::unordered_map<int, char> map({
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
}
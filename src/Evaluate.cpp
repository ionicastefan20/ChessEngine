#include "Evaluate.h"

extern int board::botColor;
extern std::unordered_map<char, int> board::materials;
extern std::vector<bool> board::botSquaresAttacked;

namespace evaluate {

    const int wKingTableMid[64] =
{-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-20,-30,-30,-40,-40,-30,-30,-20,
-100, -100,-100,-100,-100,-100,-100,-100,
 20, 100,  -100,  -100,  -100,  -100, 100, 20,
 20, 20, 10,  0,  0, 10, 20, 20};

    const int wQueenTable[64] =
{-20,-10,-10, -5, -5,-10,-10,-20,
-10,  0,  0,  0,  0,  0,  0,-10,
-10,  0,  5,  5,  5,  5,  0,-10,
 -5,  0,  5,  5,  5,  5,  0, -5,
  0,  0,  5,  5,  5,  5,  0, -5,
-10,  5,  5,  5,  5,  5,  0,-10,
-10,  0,  5,  0,  0,  0,  0,-10,
-20,-10,-10, -5, -5,-10,-10,-20};

    const int wRookTable[64] =
{0,  10,  10,  10,  10,  10,  0,  0,
 5, 0, 0, 0, 0, 0, 0,  5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
 0,  0,  0,  5,  5,  0,  0,  0};

    const int wBishopTable[64] =
{-20,-10,-10,-10,-10,-10,-10,-20,
-10,  0,  0,  0,  0,  0,  0,-10,
-10,  0,  5, 10, 10,  5,  0,-10,
-10,  100,  5, 10, 10,  5,  5,-10,
-10,  10, 10, 10, 10, 10,  0,-10,
-10, 10, 10, 10, 10, 10, 10,-10,
-10,  5,  0,  0,  0,  0,  5,-10,
-20,-10,-10,-10,-10,-10,-10,-20};

    const int wKnightTable[64] =
{-50,-40,-30,-30,-30,-30,-40,-50,
-40,-20,  0,  0,  0,  0,-20,-40,
-30,  0, 10, 15, 15, 10,  0,-30,
-30,  5, 15, 20, 20, 15,  5,-30,
-30,  0, 15, 20, 20, 15,  0,-30,
-30,  5, 10, 15, 15, 100,  5,-30,
-40,-20,  0,  5,  5,  0,-20,-40,
-50,-40,-30,-30,-30,-30,-40,-50};

    const int wPawnTable[64] =
{60,  80,  80,  80,  80,  80,  80,  60,
50, 50, 50, 50, 50, 50, 50, 50,
10, 10, 2000, 30, 30, 20, 10, 10,
 5,  5, 10, 10, 10, 10,  5,  5,
 0,  0,  0, 10, 10,  0,  0,  0,
 5, -5,-10,  0,  0,-10, -5,  5,
 5, 10, 10,-20,-20, 10, 10,  5,
 0,  0,  0,  0,  0,  0,  0,  0};

    // Black's Piece-Square Tables
    const int bKingTableMid[64] =
{20, 20, 10,  0,  0, 10, 20, 20,
 20, 20,  0,  0,  0,  0, 20, 20,
-10,-20,-20,-20,-20,-20,-20,-10,
-20,-30,-30,-40,-40,-30,-30,-20,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30};

    const int bQueenTable[64] =
{-20,-10,-10, -5, -5,-10,-10,-20,
-10,  0,  5,  0,  0,  0,  0,-10,
-10,  5,  5,  5,  5,  5,  0,-10,
  0,  0,  5,  5,  5,  5,  0, 0,
 10000,  0,  5,  5,  5,  5,  0, 10000,
-10,  0,  5,  5,  5,  5,  0,-10,
-10,  0,  0,  0,  0,  0,  0,-10,
-20,-10,-10, -5, -5,-10,-10,-20};

    const int bRookTable[64] =
{0,  0,  0,  5,  5,  0,  0,  0,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
-5,  0,  0,  0,  0,  0,  0, -5,
5, 10, 10, 10, 10, 10, 10,  5,
0,  0,  0,  0,  0,  0,  0,  0};

    const int bBishopTable[64] =
{-20,-10,-10,-10,-10,-10,-10,-20,
-10,  5,  0,  0,  0,  0,  5,-10,
-10, 10, 10, 10, 10, 10, 10,-10,
-10,  0, 10, 10, 10, 10,  0,-10,
-10,  15,  5, 10, 10,  5,  15,-10,
-10,  0,  5, 10, 10,  5,  0,-10,
-10,  0,  0,  0,  0,  0,  0,-10,
-20,-10,-10,-10,-10,-10,-10,-20};

    const int bKnightTable[64] =
{-50,-40,-30,-30,-30,-30,-40,-50,
-40,-20,  0,  5,  5,  0,-20,-40,
-30,  5, 10, 15, 15, 15,  5,-30,
-30,  0, 15, 20, 20, 15,  0,-30,
-30,  5, 15, 20, 20, 15,  5,-30,
-30,  0, 10, 15, 15, 15,  0,-30,
-40,-20,  0,  0,  0,  0,-20,-40,
-50,-40,-30,-30,-30,-30,-40,-50};

    const int bPawnTable[64] =
{0,  0,  0,  0,  0,  0,  0,  0,
5, 10, 10,-20,-20, 10, 10,  5,
5, -5, 0,  0,  1000,  0, -5,  5,
0,  0,  0, 30, 30,  0,  0,  0,
5,  5, 10, 25, 25, 10,  5,  5,
10, 10, 20, 30, 30, 20, 10, 10,
50, 50, 50, 50, 50, 50, 50, 50,
60,  80,  80,  80,  80, 80,  80,  60};

};

static double material_score() {
    double black_material = PawnWt * board::materials['p'] + KnightWt * board::materials['n'] +
                         BishopWt * board::materials['b'] + RookWt * board::materials['r'] +
                         QueenWt * board::materials['q'] + KingWt * board::materials['k'];
    double white_material = PawnWt * board::materials['P'] + KnightWt * board::materials['N'] +
                         BishopWt * board::materials['B'] + RookWt * board::materials['R'] +
                         QueenWt * board::materials['Q'] + KingWt * board::materials['K'];

    if (board::botColor == piece::BLACK)
        return (black_material - white_material);
    else
        return (white_material - black_material);
}

static double mobility_score() {
    double score = 0;
    for (int i = 0; i < 64; i++) {

        char c = piece::map[board::squares[i]];

        // White's pieces, add score
        double w_score = 0;
        if('K' == c)
            w_score += evaluate::bKingTableMid[i];
        else if('Q' == c)
            w_score += evaluate::bQueenTable[i];
        else if('R' == c)
            w_score += evaluate::bRookTable[i];
        else if('B' == c)
            w_score += evaluate::bBishopTable[i];
        else if('N' == c)
            w_score += evaluate::bKnightTable[i];
        else if('P' == c) {
            w_score += evaluate::bPawnTable[i];
        }

        // Black's pieces, substract score
        double b_score = 0;
        if('k' == c)
            b_score += evaluate::wKingTableMid[i];
        else if('q' == c)
            b_score += evaluate::wQueenTable[i];
        else if('r' == c)
            b_score += evaluate::wRookTable[i];
        else if('b' == c)
            b_score += evaluate::wBishopTable[i];
        else if('n' == c)
            b_score += evaluate::wKnightTable[i];
        else if('p' == c)
            b_score += evaluate::wPawnTable[i];

        if (board::botColor == piece::BLACK)
            score += (b_score - w_score);
        else
            score += (w_score - b_score);
    }

    return score;
}

static double check_eval() {

    if (board::colorOnMove == piece::WHITE) {
        if (move::squaresAttacked[board::whiteKingPos]) {
            return 10000;
        }
        int botColorCopy = board::botColor;
        board::botColor = board::getOppositeBotColor(board::botColor);
        move::calculateSquaresAttacked();
        if (move::squaresAttacked[board::whiteKingPos])
            return -10000;
        board::botColor = botColorCopy;
    } else {
        if (move::squaresAttacked[board::blackKingPos]) {
            return -10000;
        }
        int botColorCopy = board::botColor;
        board::botColor = board::getOppositeBotColor(board::botColor);
        move::calculateSquaresAttacked();
        if (move::squaresAttacked[board::blackKingPos])
            return 10000;
        board::botColor = botColorCopy;
    }

    return 0;
}

double evaluate::static_eval() {
    double check_score = check_eval();
    double mob = mobility_score() + check_score;
    double score = material_score() + mob;
    return score;
}

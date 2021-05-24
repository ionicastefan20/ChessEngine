#include "Evaluate.h"

extern int board::botColor;
extern std::unordered_map<char, int> board::materials;
extern std::vector<bool> board::botSquaresAttacked;

// for white
// extern const int evaluate::wKingTableMid[64];
// extern const int evaluate::wQueenTable[64];
// extern const int evaluate::wRookTable[64];
// extern const int evaluate::wBishopTable[64];
// extern const int evaluate::wKnightTable[64];
// extern const int evaluate::wPawnTable[64];
// // for black
// extern const int evaluate::bKingTableMid[64];
// extern const int evaluate::bQueenTable[64];
// extern const int evaluate::bRookTable[64];
// extern const int evaluate::bKnightTable[64];
// extern const int evaluate::bBishopTable[64];
// extern const int evaluate::bPawnTable[64];

namespace evaluate {

    const int wKingTableMid[64] = {
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -10,-20,-20,-20,-20,-20,-20,-10,
         20, 20,  0,  0,  0,  0, 20, 20,
         20, 30, 10,  0,  0, 10, 30, 20
    };

    const int wQueenTable[64] = {
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
         -5,  0,  5,  5,  5,  5,  0, -5,
          0,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
    };

    const int wRookTable[64] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        5, 10, 10, 10, 10, 10, 10,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        0,  0,  0,  5,  5,  0,  0,  0
    };

    const int wBishopTable[64] = {
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -20,-10,-10,-10,-10,-10,-10,-20
    };

    const int wKnightTable[64] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50
    };

    const int wPawnTable[64] =
{60,  80,  80,  80,  80,  80,  80,  60,
50, 50, 50, 50, 50, 50, 50, 50,
10, 10, 20, 30, 30, 20, 10, 10,
 5,  5, 10, 25, 25, 10,  5,  5,
 0,  0,  0, 20, 20,  0,  0,  0,
 5, -5,-10,  0,  0,-10, -5,  5,
 5, 10, 10,-20,-20, 10, 10,  5,
 0,  0,  0,  0,  0,  0,  0,  0};

    // Black's Piece-Square Tables
    const int bKingTableMid[64] = {
        20, 30, 10,  0,  0, 10, 30, 20,
        20, 20,  0,  0,  0,  0, 20, 20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30
    };

    const int bQueenTable[64] = {
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
        0,  0,  5,  5,  5,  5,  0, -5,
        -5,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
    };

    const int bRookTable[64] = {
        0,  0,  0,  5,  5,  0,  0,  0,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        5, 10, 10, 10, 10, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0
    };

    const int bBishopTable[64] = {
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -20,-10,-10,-10,-10,-10,-10,-20
    };

    const int bKnightTable[64] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50
    };

    const int bPawnTable[64] =
{0,  0,  0,  0,  0,  0,  0,  0,
5, 10, 10,-20,-20, 10, 10,  5,
5, -5,-10,  0,  0,-10, -5,  5,
0,  0,  0, 20, 20,  0,  0,  0,
5,  5, 10, 25, 25, 10,  5,  5,
10, 10, 20, 30, 30, 20, 10, 10,
50, 50, 50, 50, 50, 50, 50, 50,
60,  80,  80,  80,  80, 80,  80,  60};
}

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
            w_score += evaluate::wKingTableMid[i];
        else if('Q' == c)
            w_score += evaluate::wQueenTable[i];
        else if('R' == c)
            w_score += evaluate::wRookTable[i];
        else if('B' == c)
            w_score += evaluate::wBishopTable[i];
        else if('N' == c)
            w_score += evaluate::wKnightTable[i];
        else if('P' == c)
            w_score += evaluate::wPawnTable[i];

        // Black's pieces, substract score
        double b_score = 0;
        if('k' == c)
            b_score -= evaluate::bKingTableMid[i];
        else if('q' == c)
            b_score -= evaluate::bQueenTable[i];
        else if('r' == c)
            b_score -= evaluate::bRookTable[i];
        else if('b' == c)
            b_score -= evaluate::bBishopTable[i];
        else if('n' == c)
            b_score -= evaluate::bKnightTable[i];
        else if('p' == c)
            b_score -= evaluate::bPawnTable[i];

        if (board::botColor == piece::BLACK)
            score += (b_score - w_score);
        else
            score += (w_score - b_score);
    }

    return score;
}

static double check_eval(int botColor) {
    logger::logBoard2(board::botSquaresAttacked);
    if (botColor == piece::WHITE) {
        if (board::botSquaresAttacked[board::blackKingPos]) {
            return DBL_MAX;
        }

        // check for bad check
        if (board::botColor == botColor) { // check if current bot is the "main" bot
            if (move::squaresAttacked[board::whiteKingPos]) {
                return -DBL_MAX;
            }
        }
        //  else {
        //     // generate squares attacked for bot
        //     // board::botColor = board::getOppositeBotColor(board::botColor);
        //     move::calculateSquaresAttacked();
        //     board::botSquaresAttacked = move::squaresAttacked;
        //     // restore bot color
        //     board::botColor = board::getOppositeBotColor(board::botColor);
        // }
    }
    if (botColor == piece::BLACK) {
        if (board::botSquaresAttacked[board::whiteKingPos]) {
            return DBL_MAX;
        }

        // check for bad check
        if (board::botColor == botColor) { // check if current bot is the "main" bot
            if (move::squaresAttacked[board::blackKingPos]) {
                return -DBL_MAX;
            }
        }
    }


    // if (board::colorOnMove == piece::WHITE) {
    //     // logger::logBoard(root->board);
    //     // logger::logBoard2(root->squaresAttacked);
    //     // logger::log("size I I I I N N N N", std::to_string(root->squaresAttacked.size()), 3);
    //     // logger::log("black king", std::to_string(root->blackKingPos), 2);
    //     if (move::squaresAttacked[board::blackKingPos]) {
    //         return -DBL_MAX;
    //     }
    // } else {
    //     // logger::logBoard(root->board);
    //     // logger::logBoard2(root->squaresAttacked);
    //     // logger::log("size I I I I N N N N", std::to_string(root->squaresAttacked.size()), 3);
    //     // logger::log("white king", std::to_string(root->whiteKingPos), 2);
    //     // logger::log("dereferentiere", std::to_string(root->squaresAttacked[root->whiteKingPos]), 5);
    //     if (move::squaresAttacked[board::whiteKingPos]) {
    //         return DBL_MAX;
    //     }
    // }
    return 0;
}

double evaluate::static_eval(int botColor) {
    logger::logBoard(board::squares);
    logger::logBoard2(move::squaresAttacked);
    double check_score = check_eval(botColor);
    if (check_score == DBL_MAX || check_score == -DBL_MAX)
        return check_score;
    double score = material_score() + mobility_score();
    // logger::log("Score", std::to_string(score), 0);
    return score / 100;
}



#include "Move.h"
#include <fstream>

extern int board::colorOnMove;
extern int board::botColor;
extern bool board::isPlaying;
extern int board::kingPos;

namespace move {
    std::unordered_map<std::string, int> directions;
    std::vector<std::unordered_map<std::string, int>> numUntilEdge;
    std::vector<bool> squaresAttacked;
    std::unordered_map<int, std::vector<int>> moves;
}

void move::initDistancesAndDirections() {
    move::directions = {
        {"left", -1},
        {"left_up", 7},
        {"up", 8},
        {"up_right", 9},
        {"right", 1},
        {"right_down", -7},
        {"down", -8},
        {"down_left", -9}
    };

    for (int i = 0; i < 8; i++) // i = 6, j = 1
        for (int j = 0; j < 8; j++) {
            int numUp = 7 - i; // 6
            int numDown = i; // 1
            int numLeft = j; //
            int numRight = 7 - j;

            std::unordered_map<std::string, int> distances = {
                {"left", numLeft},
                {"left_up", __min(numLeft, numUp)},
                {"up", numUp},
                {"up_right", __min(numUp, numRight)},
                {"right", numRight},
                {"right_down", __min(numRight, numDown)},
                {"down", numDown},
                {"down_left", __min(numDown, numLeft)}
            };

            move::numUntilEdge.push_back(distances);
        }
}

void addMove(std::vector<int>& result, int pos, int shift) {
    int new_pos = pos + shift;
    if (!(board::squares[new_pos] & board::botColor))
        result.push_back(new_pos);
}

bool isOnLeftColumn(int pos) {
    return pos % 8 == 0;
}

bool isOnRightColumn(int pos) {
    return (pos + 1) % 8 == 0;
}

std::vector<int> generatePawnCheckMoves(int pos, int botColor) {
    std::vector<int> result;

    if (board::squares[pos] & piece::WHITE) {
        if (isOnLeftColumn(pos))
            addMove(result, pos, 9);
        else if (isOnRightColumn(pos))
            addMove(result, pos, 7);
        else {
            addMove(result, pos, 7);
            addMove(result, pos, 9);
        }
    } else {
        if (isOnLeftColumn(pos))
            addMove(result, pos, -7);
        else if (isOnRightColumn(pos))
            addMove(result, pos, -9);
        else {
            addMove(result, pos, -7);
            addMove(result, pos, -9);
        }
    }

    return result;
}

std::vector<int> generatePawnMoves(int pos, int botColor) {
    std::vector<int> result;

    if (board::squares[pos] & piece::WHITE) {
        if (board::squares[pos + 8] == 0)
            addMove(result, pos, 8);
        if (pos >= 8 && pos <= 15) {
            if (board::squares[pos + 8] == 0 && board::squares[pos + 16] == 0)
                addMove(result, pos, 16);
        }
        if (board::squares[pos + 9] & piece::BLACK &&
                move::numUntilEdge[pos]["up_right"] > 0)
            addMove(result, pos, 9);
        if (board::squares[pos + 7] & piece::BLACK &&
                move::numUntilEdge[pos]["left_up"] > 0)
            addMove(result, pos, 7);
    } else {
        if (board::squares[pos - 8] == 0)
            addMove(result, pos, -8);
        if (pos >= 48 && pos <= 55) {
            if (board::squares[pos - 8] == 0 && board::squares[pos - 16] == 0)
                addMove(result, pos, -16);
        }
        if (board::squares[pos - 9] & piece::WHITE &&
                move::numUntilEdge[pos]["down_left"] > 0)
            addMove(result, pos, -9);
        if (board::squares[pos - 7] & piece::WHITE &&
                move::numUntilEdge[pos]["right_down"] > 0)
            addMove(result, pos, -7);
    }

    return result;
}

std::vector<int> generateKnightMoves(int pos, int botColor) {
    std::vector<int> result;

    // up left
    if (move::numUntilEdge[pos]["up"] >= 2 && move::numUntilEdge[pos]["left"] >= 1)
        addMove(result, pos, 15);
    // left up
    if (move::numUntilEdge[pos]["left"] >= 2 && move::numUntilEdge[pos]["up"] >= 1)
        addMove(result, pos, 6);
    // up right
    if (move::numUntilEdge[pos]["up"] >= 2 && move::numUntilEdge[pos]["right"] >= 1)
        addMove(result, pos, 17);
    // right up
    if (move::numUntilEdge[pos]["right"] >= 2 && move::numUntilEdge[pos]["up"] >= 1)
        addMove(result, pos, 10);
    // down left
    if (move::numUntilEdge[pos]["down"] >= 2 && move::numUntilEdge[pos]["left"] >= 1)
        addMove(result, pos, -17);
    // left down
    if (move::numUntilEdge[pos]["left"] >= 2 && move::numUntilEdge[pos]["down"] >= 1)
        addMove(result, pos, -10);
    // down right
    if (move::numUntilEdge[pos]["down"] >= 2 && move::numUntilEdge[pos]["right"] >= 1)
        addMove(result, pos, -15);
    // right down
    if (move::numUntilEdge[pos]["right"] >= 2 && move::numUntilEdge[pos]["down"] >= 1)
        addMove(result, pos, -6);

    return result;
}

std::vector<int> generateKingMoves(int pos, int botColor) {
    std::vector<int> result;

    for (auto kv : move::directions) {
        int new_pos = pos + kv.second;

        if ((board::squares[new_pos] & board::botColor) ||
                (move::numUntilEdge[pos][kv.first] <= 0) ||
                (move::squaresAttacked[new_pos]))
            continue;

        result.push_back(new_pos);
    }

    return result;
}

std::vector<int> generateBishopMoves(int pos, int botColor) {
    std::vector<int> result;

    for (std::string dir : {"left_up", "up_right", "right_down", "down_left"}) {
        for (int i = 1; i <= move::numUntilEdge[pos][dir]; ++i) {
            int new_pos = pos + i * move::directions[dir];
            if (board::squares[new_pos] & board::botColor)
                break;

            result.push_back(new_pos);

            if (board::squares[new_pos] &
                    board::getOppositeBotColor(board::botColor))
                break;
        }
    }

    return result;
}

std::vector<int> generateRookMoves(int pos, int botColor) {
    std::vector<int> result;

    for (std::string dir : {"left", "up", "right", "down"}) {
        for (int i = 1; i <= move::numUntilEdge[pos][dir]; ++i) {
            int new_pos = pos + i * move::directions[dir];
            if (board::squares[new_pos] & board::botColor)
                break;

            result.push_back(new_pos);

            if (board::squares[new_pos] &
                    board::getOppositeBotColor(board::botColor))
                break;
        }
    }

    return result;
}

void removePositionWithCheck(int i) {
    std::vector<int> nonCheckMoves; // only the positions that do not
                                    // generate a check are kept here

    // artificially make the move on the board, check if it generates a
    // situation where the king is in chess, if so remove the move from the
    // list of possible moves
    std::vector<int> copyBoardState(board::squares, board::squares + 64); //copy
        // iterate through moves
    for (int k = 0; k < move::moves[i].size(); k++) {
        // artifically make the move
        int kingPosCopy = board::kingPos; // make copy of the king pos
        if (board::squares[i] == (piece::KING | board::botColor))
            board::kingPos = move::moves[i][k];

        board::squares[move::moves[i][k]] = board::squares[i];
        board::squares[i] = 0;

        // make copy of the squaresAttacked vector
        std::vector<bool> squaresAttackedCopy(move::squaresAttacked); // copy
        move::calculateSquaresAttacked();

        if (!move::squaresAttacked[board::kingPos]) // a valid move
            nonCheckMoves.push_back(move::moves[i][k]);

        // restore copies
        board::kingPos = kingPosCopy;
        move::squaresAttacked = squaresAttackedCopy;
        for (int j = 0; j < 64; j++)
            board::squares[j] = copyBoardState[j];
    }

    move::moves[i] = nonCheckMoves;
}

void move::generate() {
    std::vector<int> aux;

    moves.clear();
    std::ofstream fout5("out5", std::ofstream::app);

    fout5 << board::botColor << " " << board::kingPos << " " << move::squaresAttacked[board::kingPos] << std::endl;
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            fout5 << move::squaresAttacked[i*8+j] << " ";
        }
        fout5 << std::endl;
    }


    if (move::squaresAttacked[board::kingPos]) {
        move::moves[board::kingPos] = generateKingMoves(board::kingPos, board::botColor);
        return;
    }

    for (int i = 0; i < 64; ++i) {
        if (board::botColor & board::squares[i]) {
            switch (board::squares[i] & 0x7) {
                case piece::PAWN:
                    move::moves[i] = generatePawnMoves(i, board::botColor);
                    break;
                case piece::ROOK:
                    move::moves[i] = generateRookMoves(i, board::botColor);
                    break;
                case piece::KNIGHT:
                    move::moves[i] = generateKnightMoves(i, board::botColor);
                    break;
                case piece::BISHOP:
                    move::moves[i] = generateBishopMoves(i, board::botColor);
                    break;
                case piece::QUEEN:
                    move::moves[i] = generateRookMoves(i, board::botColor);
                    aux = generateBishopMoves(i, board::botColor);
                    move::moves[i].insert(move::moves[i].end(),
                        aux.begin(), aux.end()); // append instead of replace TODO
                    break;
                case piece::KING:
                    move::moves[i] = generateKingMoves(i, board::botColor);
                    break;
                default:
                    break;
            }

            removePositionWithCheck(i);
        }
    }
}

void move::calculateSquaresAttacked() {
    squaresAttacked.clear();
    for (int i = 0; i < 64; i++)
        squaresAttacked.push_back(false); // initialize the map with all false

    // iterate over the squares, over the current state of the board
    for (int i = 0; i < 64; i++) {
        if (board::botColor & board::squares[i]) {
            std::vector<int> attackedSquares;
            std::vector<int> auxAttackedSquares;
            int oppositeColor = board::getOppositeBotColor(board::botColor);

            switch (board::squares[i] & 0x7) {
                case piece::PAWN:
                    attackedSquares = generatePawnCheckMoves(i, oppositeColor);
                    break;
                case piece::ROOK:
                    attackedSquares = generateRookMoves(i, oppositeColor);
                    break;
                case piece::KNIGHT:
                    attackedSquares = generateKnightMoves(i, oppositeColor);
                    break;
                case piece::BISHOP:
                    attackedSquares = generateBishopMoves(i, oppositeColor);
                    break;
                case piece::QUEEN:
                    attackedSquares = generateRookMoves(i, oppositeColor);
                    auxAttackedSquares = generateBishopMoves(i, oppositeColor);
                    // append the second list fo positions to the first one
                    // basically centralize the it
                    attackedSquares.insert(attackedSquares.end(),
                        auxAttackedSquares.begin(), auxAttackedSquares.end());
                    break;
                case piece::KING:
                    attackedSquares = generateKingMoves(i, oppositeColor);
                    // fout3 << "\t\t " << attackedSquares[j] << std::endl;
                    break;
                default:
                    break;
            }

            for (int j = 0; j < attackedSquares.size(); j++)
                squaresAttacked[attackedSquares[j]] = true;
        }
    }
}

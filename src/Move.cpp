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

void move::generate() {
    std::vector<int> aux;

    moves.clear();
    std::ofstream fout5("out5", std::ofstream::app);

    if (move::squaresAttacked[board::kingPos]) {
        move::moves[board::kingPos] = generateKingMoves(board::kingPos);
        return;
    }

    for (int i = 0; i < 64; ++i) {
        if (board::botColor & board::squares[i]) {
            fout5 << "va: " << (board::squares[i] & 0x7) << std::endl;
            switch (board::squares[i] & 0x7) {
                case piece::PAWN:
                    move::moves[i] = generatePawnMoves(i);
                    break;
                case piece::ROOK:
                    move::moves[i] = generateRookMoves(i);
                    break;
                case piece::KNIGHT:
                    move::moves[i] = generateKnightMoves(i);
                    break;
                case piece::BISHOP:
                    move::moves[i] = generateBishopMoves(i);
                    break;
                case piece::QUEEN:
                    move::moves[i] = generateRookMoves(i);
                    aux = generateBishopMoves(i);
                    move::moves[i].insert(move::moves[i].end(),
                        aux.begin(), aux.end()); // append instead of replace TODO
                    break;
                case piece::KING:
                    move::moves[i] = generateKingMoves(i);
                    break;
                default:
                    break;
            }
        }
    }
}

void addMove(std::vector<int>& result, int pos, int shift) {
    int new_pos = pos + shift;
    if (!(board::squares[new_pos] & board::botColor))
        result.push_back(new_pos);
}

std::vector<int> move::generatePawnMoves(int pos) {
    std::vector<int> result;

    if (board::squares[pos] & piece::WHITE) {
        if (board::squares[pos + 8] == 0)
            addMove(result, pos, 8);
        if (pos >= 8 && pos <= 15) {
            if (board::squares[pos + 8] == 0 && board::squares[pos + 16] == 0)
                addMove(result, pos, 16);
        }
    } else {
        if (board::squares[pos - 8] == 0)
            addMove(result, pos, -8);
        if (pos >= 48 && pos <= 55) {
            if (board::squares[pos - 8] == 0 && board::squares[pos - 16] == 0)
                addMove(result, pos, -16);
        }
    }

    return result;
}

std::vector<int> move::generateKnightMoves(int pos) {
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

std::vector<int> move::generateKingMoves(int pos) {
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

std::vector<int> move::generateBishopMoves(int pos) {
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

std::vector<int> move::generateRookMoves(int pos) {
    std::vector<int> result;
    std::ofstream fout4("out4", std::ofstream::app);

    for (std::string dir : {"left", "up", "right", "down"}) {
        fout4 << "directia: " << dir << " ";
        for (int i = 1; i <= move::numUntilEdge[pos][dir]; ++i) {
            int new_pos = pos + i * move::directions[dir];
            fout4 << "am dadaugat: " << new_pos << std::endl;

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

void move::calculateSquaresAttacked() {
    std::ofstream fout3("out3", std::ofstream::app);
    squaresAttacked.clear();
    for (int i = 0; i < 64; i++)
        squaresAttacked.push_back(false); // initialize the map with all false

    fout3 << "yessir1" << std::endl;
    // iterate over the squares, over the current state of the board
    for (int i = 0; i < 64; i++) {
        if (board::botColor & board::squares[i]) {
            std::vector<int> attackedSquares;
            std::vector<int> auxAttackedSquares;

            switch (board::squares[i] & 0x7) {
                case piece::PAWN:
                    attackedSquares = generatePawnMoves(i);
                    break;
                case piece::ROOK:
                    attackedSquares = generateRookMoves(i);
                    break;
                case piece::KNIGHT:
                    attackedSquares = generateKnightMoves(i);
                    break;
                case piece::BISHOP:
                    attackedSquares = generateBishopMoves(i);
                    break;
                case piece::QUEEN:
                    attackedSquares = generateRookMoves(i);
                    auxAttackedSquares = generateBishopMoves(i);
                    // append the second list fo positions to the first one
                    // basically centralize the it
                    attackedSquares.insert(attackedSquares.end(),
                        auxAttackedSquares.begin(), auxAttackedSquares.end());
                    break;
                case piece::KING:
                    attackedSquares = generateKingMoves(i);
                    // fout3 << "\t\t " << attackedSquares[j] << std::endl;
                    break;
                default:
                    break;
            }

            fout3 << "yessir: " << i << std::endl;
            for (int j = 0; j < attackedSquares.size(); j++) {
                fout3 << "\tyessir mid before sugio: " << attackedSquares[j] << std::endl;
                squaresAttacked[attackedSquares[j]] = true;
            }
            fout3 << "yessir milsugio: " << i << std::endl;
        }
    }
}

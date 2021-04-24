#include "Move.h"
#include <fstream>

unordered_map<string, int> Move::DIRECTIONS;

vector<unordered_map<string, int>> Move::numUntilEdge;

std::unordered_map<int, std::vector<int>> Move::moves;

vector<bool> Move::squaresAttacked;

void Move::initDistancesAndDirections() {
    Move::DIRECTIONS = {
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

            unordered_map<string, int> distances = {
                {"left", numLeft},
                {"left_up", __min(numLeft, numUp)},
                {"up", numUp},
                {"up_right", __min(numUp, numRight)},
                {"right", numRight},
                {"right_down", __min(numRight, numDown)},
                {"down", numDown},
                {"down_left", __min(numDown, numLeft)}
            };

            Move::numUntilEdge.push_back(distances);
        }
}

void Move::generate() {
    moves.clear();
    std::ofstream fout5("out5", std::ofstream::app);
    for (int i = 0; i < 64; ++i) {
        if (Board::botColor & Board::squares[i]) {
            fout5 << "va: " << (Board::squares[i] & 0x7) << std::endl;
            switch (Board::squares[i] & 0x7) {
                case Piece::PAWN:
                    Move::moves[i] = generatePawnMoves(i);
                    break;
                case Piece::ROOK:
                    Move::moves[i] = generateRookMoves(i);
                    break;
                case Piece::KNIGHT:
                    Move::moves[i] = generateKnightMoves(i);
                    break;
                case Piece::BISHOP:
                    Move::moves[i] = generateBishopMoves(i);
                    break;
                case Piece::QUEEN:
                    Move::moves[i] = generateRookMoves(i);
                    Move::moves[i] = generateBishopMoves(i); // append instead of replace TODO
                    break;
                case Piece::KING:
                    Move::moves[i] = generateKingMoves(i);
                    break;
                default:
                    break;
            }
        }
    }
}

void addMove(std::vector<int>& result, int pos, int shift) {
    int new_pos = pos + shift;
    if (!(Board::squares[new_pos] & Board::botColor))
        result.push_back(new_pos);
}

std::vector<int> Move::generatePawnMoves(int pos) {
    std::vector<int> result;

    if (Board::squares[pos] & Piece::WHITE) {
        addMove(result, pos, 8);
        if (pos >= 8 && pos <= 15)
            addMove(result, pos, 16);
    } else {
        addMove(result, pos, -8);
        if (pos >= 48 && pos <= 55)
            addMove(result, pos, -16);
    }

    return result;
}

std::vector<int> Move::generateKnightMoves(int pos) {
    std::vector<int> result;

    // up left
    addMove(result, pos, 15);
    // left up
    addMove(result, pos, 6);
    // up right
    addMove(result, pos, 17);
    // right up
    addMove(result, pos, 10);
    // down left
    addMove(result, pos, -17);
    // left down
    addMove(result, pos, -10);
    // down right
    addMove(result, pos, -15);
    // right down
    addMove(result, pos, -6);

    return result;
}

std::vector<int> Move::generateKingMoves(int pos) {
    std::vector<int> result;

    for (auto kv : Move::DIRECTIONS) {
        int new_pos = pos + kv.second;

        if ((Board::squares[new_pos] & Board::botColor) ||
                (Move::numUntilEdge[pos][kv.first] > 0))
            break;

        result.push_back(new_pos);
    }

    return result;
}

std::vector<int> Move::generateBishopMoves(int pos) {
    std::vector<int> result;

    for (std::string dir : {"left_up", "up_right", "right_down", "down_left"}) {
        for (int i = 1; i <= Move::numUntilEdge[pos][dir]; ++i) {
            int new_pos = pos + i * Move::DIRECTIONS[dir];

            if (Board::squares[new_pos] & Board::botColor)
                break;

            result.push_back(new_pos);

            if (Board::squares[new_pos] &
                Board::getOppositeBotColor(Board::botColor))
                break;
        }
    }

    return result;
}

std::vector<int> Move::generateRookMoves(int pos) {
    std::vector<int> result;
    std::ofstream fout4("out4", std::ofstream::app);

    for (std::string dir : {"left", "up", "right", "down"}) {
        fout4 << "directia: " << dir << " ";
        for (int i = 1; i <= Move::numUntilEdge[pos][dir]; ++i) {
            int new_pos = pos + i * Move::DIRECTIONS[dir];
            fout4 << "am dadaugat: " << new_pos << std::endl;
            result.push_back(new_pos);

            if (Board::squares[new_pos] &
                Board::getOppositeBotColor(Board::botColor))
                break;
        }
    }

    return result;
}

void Move::calculateSquaresAttacked() {
    std::ofstream fout3("out3", std::ofstream::app);
    squaresAttacked.clear();
    for (int i = 0; i < 64; i++)
        squaresAttacked.push_back(false); // initialize the map with all false

    fout3 << "yessir1" << std::endl;
    // iterate over the squares, over the current state of the board
    for (int i = 0; i < 64; i++) {
        if (Board::botColor & Board::squares[i]) {
            vector<int> attackedSquares;
            vector<int> auxAttackedSquares;

            switch (Board::squares[i] & 0x7) {
                case Piece::PAWN:
                    attackedSquares = generatePawnMoves(i);
                    break;
                case Piece::ROOK:
                    attackedSquares = generateRookMoves(i);
                    break;
                case Piece::KNIGHT:
                    attackedSquares = generateKnightMoves(i);
                    break;
                case Piece::BISHOP:
                    attackedSquares = generateBishopMoves(i);
                    break;
                case Piece::QUEEN:
                    attackedSquares = generateRookMoves(i);
                    auxAttackedSquares = generateBishopMoves(i);
                    // append the second list fo positions to the first one
                    // basically centralize the it
                    attackedSquares.insert(attackedSquares.end(),
                        auxAttackedSquares.begin(), auxAttackedSquares.end());
                    break;
                case Piece::KING:
                    attackedSquares = generateKingMoves(i);
                    break;
                default:
                    break;
            }

            fout3 << "yessir: " << i << std::endl;
            for (int j = 0; j < attackedSquares.size(); j++) {
                squaresAttacked[attackedSquares[j]] = true;
            }
        }
    }
}

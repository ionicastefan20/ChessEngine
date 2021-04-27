#include "Move.h"
#include "Logger.h"

extern int board::colorOnMove;
extern int board::botColor;
extern bool board::isPlaying;
extern int board::kingPos;

namespace move {
    int leftWhiteRook = 1;
    int rightWhiteRook = 1;
    int leftBlackRook = 1;
    int rightBlackRook = 1;
    int whiteKing = 1;
    int blackKing = 1;
    int enPassantMove = 1;
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

// START < END !!!!
bool emptyPath(int start, int end) {
    for (int i = start; i <= end; ++i)
        if (board::squares[i] != 0)
            return false;
    return true;
}

void addMove(std::vector<int>& result, int pos, int shift, int botColor) {
    int new_pos = pos + shift;
    if (!(board::squares[new_pos] & botColor))
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
            addMove(result, pos, 9, botColor);
        else if (isOnRightColumn(pos))
            addMove(result, pos, 7, botColor);
        else {
            addMove(result, pos, 7, botColor);
            addMove(result, pos, 9, botColor);
        }
    } else {
        if (isOnLeftColumn(pos))
            addMove(result, pos, -7, botColor);
        else if (isOnRightColumn(pos))
            addMove(result, pos, -9, botColor);
        else {
            addMove(result, pos, -7, botColor);
            addMove(result, pos, -9, botColor);
        }
    }

    return result;
}

std::vector<int> generatePawnMoves(int pos, int botColor) {
    std::vector<int> result;

    if (board::squares[pos] & piece::WHITE) {
        if (board::squares[pos + 8] == 0)
            addMove(result, pos, 8, botColor);
        if (pos >= 8 && pos <= 15) {
            if (board::squares[pos + 8] == 0 && board::squares[pos + 16] == 0)
                addMove(result, pos, 16, botColor);
        }
        if (board::squares[pos + 9] & piece::BLACK &&
                move::numUntilEdge[pos]["up_right"] > 0)
            addMove(result, pos, 9, botColor);
        if (board::squares[pos + 7] & piece::BLACK &&
                move::numUntilEdge[pos]["left_up"] > 0)
            addMove(result, pos, 7, botColor);

        // en passant
        if ((pos % 8 != 7) && (board::squares[pos + 1] & piece::BLACK) && (move::enPassantMove == pos + 1)) {
            //if ((pos + 1) % 8 != 0) // is not on the right most column
                addMove(result, pos, 9, botColor);
        }
        if ((pos % 8 != 0) && (board::squares[pos - 1] & piece::BLACK) && (move::enPassantMove == pos - 1))
            //if (pos % 8 != 0) // is not on the left most column
                addMove(result, pos, 7, botColor);
    } else {
        if (board::squares[pos - 8] == 0)
            addMove(result, pos, -8, botColor);
        if (pos >= 48 && pos <= 55) {
            if (board::squares[pos - 8] == 0 && board::squares[pos - 16] == 0)
                addMove(result, pos, -16, botColor);
        }
        if (board::squares[pos - 9] & piece::WHITE &&
                move::numUntilEdge[pos]["down_left"] > 0)
            addMove(result, pos, -9, botColor);
        if (board::squares[pos - 7] & piece::WHITE &&
                move::numUntilEdge[pos]["right_down"] > 0)
            addMove(result, pos, -7, botColor);

        // en passant
        if ((pos % 8 != 7) && (board::squares[pos + 1] & piece::WHITE) && (move::enPassantMove == pos + 1))
            //if ((pos + 1) % 8 != 0) // is not on the right most column
                addMove(result, pos, -7, botColor);
        if ((pos % 8 != 0) && (board::squares[pos - 1] & piece::WHITE) && (move::enPassantMove == pos - 1))
            //if (pos % 8 != 0) // is not on the left most column
                addMove(result, pos, -9, botColor);
    }

    return result;
}

std::vector<int> generateKnightMoves(int pos, int botColor) {
    std::vector<int> result;

    // up left
    if (move::numUntilEdge[pos]["up"] >= 2 && move::numUntilEdge[pos]["left"] >= 1)
        addMove(result, pos, 15, botColor);
    // left up
    if (move::numUntilEdge[pos]["left"] >= 2 && move::numUntilEdge[pos]["up"] >= 1)
        addMove(result, pos, 6, botColor);
    // up right
    if (move::numUntilEdge[pos]["up"] >= 2 && move::numUntilEdge[pos]["right"] >= 1)
        addMove(result, pos, 17, botColor);
    // right up
    if (move::numUntilEdge[pos]["right"] >= 2 && move::numUntilEdge[pos]["up"] >= 1)
        addMove(result, pos, 10, botColor);
    // down left
    if (move::numUntilEdge[pos]["down"] >= 2 && move::numUntilEdge[pos]["left"] >= 1)
        addMove(result, pos, -17, botColor);
    // left down
    if (move::numUntilEdge[pos]["left"] >= 2 && move::numUntilEdge[pos]["down"] >= 1)
        addMove(result, pos, -10, botColor);
    // down right
    if (move::numUntilEdge[pos]["down"] >= 2 && move::numUntilEdge[pos]["right"] >= 1)
        addMove(result, pos, -15, botColor);
    // right down
    if (move::numUntilEdge[pos]["right"] >= 2 && move::numUntilEdge[pos]["down"] >= 1)
        addMove(result, pos, -6, botColor);

    return result;
}


std::vector<int> generateKingMoves(int pos, int botColor) {
    std::vector<int> result;

    for (auto kv : move::directions) {
        int new_pos = pos + kv.second;

        if ((board::squares[new_pos] & botColor) ||
                (move::numUntilEdge[pos][kv.first] <= 0) ||
                (move::squaresAttacked[new_pos]))
            continue;

        result.push_back(new_pos);
    }

    // castle
    if (botColor == piece::WHITE) { // white
        if (move::whiteKing && move::leftWhiteRook && emptyPath(1, 3)) // left
            result.push_back(pos - 2);
        if (move::whiteKing && move::rightWhiteRook && emptyPath(5, 6)) // right
            result.push_back(pos + 2);
    } else { // black
        if (move::blackKing && move::leftBlackRook && emptyPath(57, 59)) // left
            result.push_back(pos - 2);
        if (move::blackKing && move::rightBlackRook && emptyPath(61, 62)) // right
            result.push_back(pos + 2);
    }

    return result;
}

std::vector<int> generateBishopMoves(int pos, int botColor) {
    std::vector<int> result;

    for (std::string dir : {"left_up", "up_right", "right_down", "down_left"}) {
        for (int i = 1; i <= move::numUntilEdge[pos][dir]; ++i) {
            int new_pos = pos + i * move::directions[dir];
            if (board::squares[new_pos] & botColor)
                break;

            result.push_back(new_pos);

            if (board::squares[new_pos] &
                    board::getOppositeBotColor(botColor))
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
            if (board::squares[new_pos] & botColor)
                break;

            result.push_back(new_pos);

            if (board::squares[new_pos] &
                    board::getOppositeBotColor(botColor))
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
        // check for enpassant
        if (((board::squares[i] & 7) == piece::PAWN) && ((move::moves[i][k] - i) % 8 != 0) && (move::moves[i][k] == 0)) {
            if (board::squares[i] & piece::WHITE)
                board::squares[move::moves[i][k] - 8] = 0;
            else
                board::squares[move::moves[i][k] + 8] = 0;
        }


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
                        aux.begin(), aux.end());
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

    int oppositeColor = board::getOppositeBotColor(board::botColor);
    // iterate over the squares, over the current state of the board
    for (int i = 0; i < 64; i++) {
        if (oppositeColor & board::squares[i]) {
            std::vector<int> attackedSquares;
            std::vector<int> auxAttackedSquares;


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
                    break;
                default:
                    break;
            }

            for (int j = 0; j < attackedSquares.size(); j++)
                squaresAttacked[attackedSquares[j]] = true;
        }
    }
}

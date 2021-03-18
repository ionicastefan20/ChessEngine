#include "Move.h"
#include <fstream>

unordered_map<string, int> Move::DIRECTIONS;

vector<unordered_map<string, int>> Move::numUntilEdge;

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

/**
 * Returns the future position according to the givven parameters,
 * or -1 if the move is invalid (out of the board move, or an ally piece
 * is already there)
 * This method applies to every piece except the knight, for which there will
 * be a method dedicated to moving it.
 * TODO: need to check for chess if move is done
 */
int Move::getFuturePosForMove(int initialPos, string direction,
                                    int numberOfBlocks) {
    int retValue;
    if (numberOfBlocks <= Move::numUntilEdge[initialPos][direction])
        retValue = initialPos + numberOfBlocks * (DIRECTIONS[direction]);
    else
        return -1;

    // check if the path of the piece encounters any obstacles in it's path
    for (int i = 1; i < numberOfBlocks; i++) {
        int tempFutureValue = initialPos + i * (DIRECTIONS[direction]);
        if (Board::squares[tempFutureValue] != 0)
            return -1;
    }

    if (Board::squares[retValue] & Board::botColor)
        return -1;
    
    // Next rules only for pawns
    if (Board::botColor & Piece::BLACK) {
        if ((direction == "right_down" || direction == "down_left") &&
            !(Board::squares[retValue]))
            return -1;
    
        if (numberOfBlocks == 2 && (initialPos < 48 || initialPos > 56))
            return -1;

        if (direction == "down" && numberOfBlocks == 1 &&
            Board::squares[retValue] & Piece::WHITE)
            return -1;
    }
    else {
        if ((direction == "up_right" || direction == "left_up") &&
            !(Board::squares[retValue]))
            return -1;
    
        if (numberOfBlocks == 2 && (initialPos < 8 || initialPos > 15))
            return -1;

        if (direction == "up" && numberOfBlocks == 1 &&
            Board::squares[retValue] & Piece::BLACK)
            return -1;
    }
    return retValue;
}
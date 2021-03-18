#include "GeneratePawnMoves.h"
#include <fstream>

int GeneratePawnMoves::currPawn = 1; // first pawn in black,
                                          // first pawn in white
int GeneratePawnMoves::lastPos = 48; // 47 + currPawn

int GeneratePawnMoves::getBlackLastPos() {
    return (lastPos & 63); // 64 = 111111 in binary (a mask)
}

int GeneratePawnMoves::getWhiteLastPos() {
    return (lastPos >> 6); // shift 6 bits, get only the next 6
}

void GeneratePawnMoves::setBlackLastPos(int value) {
    lastPos = (lastPos & 4032); // 4032 = 111111000000 in binary (a mask)
    lastPos += value;
}

void GeneratePawnMoves::setWhiteLastPos(int value) {
    lastPos = getBlackLastPos() + (value << 6); // shift the new value with 6
    // bits and add the remaining black
}

int GeneratePawnMoves::getLastPosForCurrentColor() {
    if (Board::botColor & Piece::BLACK)
        return getBlackLastPos();
    else
        return getWhiteLastPos();
}

void GeneratePawnMoves::setLastPosForCurrentColor(int value) {
    if (Board::botColor & Piece::BLACK)
        setBlackLastPos(value);
    else
        setWhiteLastPos(value);
}

/**
 * Returns the move it makes
 */
static pair<int, int> makeMoveUpdatePos(int move) {
    Board::makeMove(Board::encodeMove(std::make_pair(
        GeneratePawnMoves::getLastPosForCurrentColor(), move)));
    // if we move to the last row, turn into queen
    if ((move >= 0 && move < 8 && (Board::botColor & Piece::BLACK)) ||
        (move >= 56 && move < 64 && (Board::botColor & Piece::WHITE)))
        Board::squares[move] == Piece::QUEEN | Board::botColor;
    int tempLastPos = GeneratePawnMoves::getLastPosForCurrentColor();
    GeneratePawnMoves::setLastPosForCurrentColor(move);
    return std::make_pair(tempLastPos, move);
}

static pair<int, int> moveForNextPawn() {
    if (Board::botColor == Piece::WHITE) { 
        // keep only last 3 bits
        int whiteCurrPawn = GeneratePawnMoves::currPawn >> 3; 
        whiteCurrPawn++;
        if (whiteCurrPawn > 8) {
            return std::make_pair(-1, -1); // resign
        }
        GeneratePawnMoves::setLastPosForCurrentColor(16 - whiteCurrPawn);
        GeneratePawnMoves::currPawn = (whiteCurrPawn << 3) +
                                      (GeneratePawnMoves::currPawn & 7);        
    }
    else if (Board::botColor == Piece::BLACK) {
        // keep only first 3 bits (7=111b)
        int blackCurrPawn = GeneratePawnMoves::currPawn & 7; 
        blackCurrPawn++;
        if (blackCurrPawn > 8)
            return std::make_pair(-1, -1); // resign
        GeneratePawnMoves::setLastPosForCurrentColor(47 + blackCurrPawn);
        GeneratePawnMoves::currPawn++;
    }
    // if on the pawn slot we dont have a pawn, call this methot again and get
    // the next desired pawn
    if (Board::squares[GeneratePawnMoves::getLastPosForCurrentColor()] !=
                                        (Piece::PAWN | Board::botColor)) {
        return moveForNextPawn();
    }

    // we have set the parameters for the next pawn, now make a move for it
    return GeneratePawnMoves::generatePawnMove();
}

static void getNextPositions(int& moveOne, int& moveTwo, int& moveDiagRight,
                             int& moveDiagLeft) {
    if (Board::botColor & Piece::BLACK) {
        moveDiagRight = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "right_down", 1);
        moveDiagLeft = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "down_left", 1);
        moveTwo = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "down", 2);
        moveOne = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "down", 1);
    }
    else {
        moveDiagRight = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "left_up", 1);
        moveDiagLeft = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "up_right", 1);
        moveTwo = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "up", 2);
        moveOne = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "up", 1);
    }
}

/**
 * Returns a pair of <-1, -1> when there is no other move the bot can do and
 * it resigns.
 */
pair<int, int> GeneratePawnMoves::generatePawnMove() {

    // if the piece has been taken, go to the next pawn
    if (Board::squares[getLastPosForCurrentColor()] &
        (Board::botColor ^ (8 + 16))) {
        // xor between botcolor and bitmask 11000 gets us the other color
        return moveForNextPawn();
    }

    int moveDiagRight, moveDiagLeft, moveTwo, moveOne;
    // getNextPositions(moveOne, moveTwo, moveDiagRight, moveDiagLeft);
    if (Board::botColor & Piece::BLACK) {
        moveDiagRight = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "right_down", 1);
        moveDiagLeft = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "down_left", 1);
        moveTwo = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "down", 2);
        moveOne = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "down", 1);
    }
    else {
        moveDiagRight = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "left_up", 1);
        moveDiagLeft = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "up_right", 1);
        moveTwo = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "up", 2);
        moveOne = Move::getFuturePosForMove(
            GeneratePawnMoves::getLastPosForCurrentColor(), "up", 1);
    }

    // fout2 << currPawn << " " << lastPos << " " << moveDownRight << " " << moveLeftDown << " " << moveDownTwoBlocks << " " << moveDownOneBlock << std::endl;
    // try advance the pawn 2 blocks
    if (moveTwo >= 0) // prioritize moving pawns 2 pieces forward
        return makeMoveUpdatePos(moveTwo);
    // if we can capture, then capture
    else if (moveDiagRight >= 0) // prioritize capturing to the right
        return makeMoveUpdatePos(moveDiagRight);
    // capture to the left now
    else if (moveDiagLeft >= 0) // prioritize capturing to the left
        return makeMoveUpdatePos(moveDiagLeft);
    // lastly move it one block down
    else if (moveOne >= 0) // prioritize moving pawns one piece down
        return makeMoveUpdatePos(moveOne);
    // piece cannot move anymore, go to the next pawn
    else // go to the next pawn and move it
        return moveForNextPawn();
}
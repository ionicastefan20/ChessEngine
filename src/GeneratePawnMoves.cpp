#include "GeneratePawnMoves.h"
#include <fstream>

int GeneratePawnMoves::currPawn = 1; // first pawn in black,
                                          // first pawn in white
int GeneratePawnMoves::lastPos = 48; // 47 + currPawn

/**
 * Returns the move it makes
 */
static pair<int, int> makeMoveUpdatePos(int move) {
    Board::makeMove(Board::encodeMove(
            std::make_pair(GeneratePawnMoves::lastPos, move)));
    // if we move to the last row, turn into queen
    if ((move >= 0 && move < 8 && (Board::botColor & Piece::BLACK)) ||
        (move >= 56 && move < 64 && (Board::botColor & Piece::WHITE)))
        Board::squares[move] == Piece::QUEEN | Board::botColor;
    int tempLastPos = GeneratePawnMoves::lastPos;
    GeneratePawnMoves::lastPos = move;
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
        GeneratePawnMoves::lastPos = 16 - whiteCurrPawn;
        GeneratePawnMoves::currPawn = whiteCurrPawn << 3 +
                                      (GeneratePawnMoves::currPawn & 7);
    }
    else if (Board::botColor == Piece::BLACK) {
        // keep only first 3 bits (7=111b)
        int blackCurrPawn = GeneratePawnMoves::currPawn & 7; 
        blackCurrPawn++;
        if (blackCurrPawn > 8)
            return std::make_pair(-1, -1); // resign
        GeneratePawnMoves::lastPos = 47 + blackCurrPawn;
        GeneratePawnMoves::currPawn++;
    }
    // if on the pawn slot we dont have a pawn, call this methot again and get
    // the next desired pawn
    if (Board::squares[GeneratePawnMoves::lastPos] !=
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
            GeneratePawnMoves::lastPos, "right_down", 1);
        moveDiagLeft = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "down_left", 1);
        moveTwo = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "down", 2);
        moveOne = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "down", 1);
    }
    else {
        moveDiagRight = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "left_up", 1);
        moveDiagLeft = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "up_right", 1);
        moveTwo = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "up", 2);
        moveOne = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "up", 1);
    }
}

/**
 * Returns a pair of <-1, -1> when there is no other move the bot can do and
 * it resigns.
 */
pair<int, int> GeneratePawnMoves::generatePawnMove() {

    // if the piece has been taken, go to the next pawn
    if (Board::squares[lastPos] & (Board::botColor ^ (8 + 16))) {
        // xor between botcolor and bitmask 11000 gets us the other color
        return moveForNextPawn();
    }

    int moveDiagRight, moveDiagLeft, moveTwo, moveOne;
    // getNextPositions(moveOne, moveTwo, moveDiagRight, moveDiagLeft);
    if (Board::botColor & Piece::BLACK) {
        moveDiagRight = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "right_down", 1);
        moveDiagLeft = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "down_left", 1);
        moveTwo = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "down", 2);
        moveOne = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "down", 1);
    }
    else {
        moveDiagRight = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "left_up", 1);
        moveDiagLeft = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "up_right", 1);
        moveTwo = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "up", 2);
        moveOne = Move::getFuturePosForMove(
            GeneratePawnMoves::lastPos, "up", 1);
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
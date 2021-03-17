#include "GeneratePawnMoves.h"
#include <fstream>

int GeneratePawnMoves::currPawn = 1;
int GeneratePawnMoves::lastPos = 48; // 47 + currPawn

/**
 * Returns the move it makes
 */
static pair<int, int> makeMoveUpdatePos(int move) {
    Board::makeMove(Board::encodeMove(
            std::make_pair(GeneratePawnMoves::lastPos, move)));
    // if we move to the last row, turn into queen
    if (move >= 0 && move < 8)
        Board::squares[move] == Piece::QUEEN | Board::botColor;
    int tempLastPos = GeneratePawnMoves::lastPos;
    GeneratePawnMoves::lastPos = move;
    return std::make_pair(tempLastPos, move);
}

/**
 * Returns a pair of <-1, -1> when there is no other move the bot can do and
 * it resigns.
 */
pair<int, int> GeneratePawnMoves::generatePawnMove() {
    std::ofstream fout2("output2.txt");
    fout2 << GeneratePawnMoves::lastPos << std::endl;

    // if the piece has been taken, go to the next pawn
    if (Board::squares[lastPos] & Piece::WHITE) { // TODO: instead of 
    // Piece::White replace with a more generic formula : negate Board::botColor
        currPawn++;
        if (currPawn > 8) {
            return std::make_pair(-1, -1);
        }
        lastPos = 47 + currPawn;
    }

    int moveDownRight = Move::getFuturePosForMove(lastPos, "right_down", 1);
    int moveLeftDown = Move::getFuturePosForMove(lastPos, "down_left", 1);
    int moveDownTwoBlocks = Move::getFuturePosForMove(lastPos, "down", 2);
    int moveDownOneBlock = Move::getFuturePosForMove(lastPos, "down", 1);

    fout2 << currPawn << " " << lastPos << " " << moveDownRight << " " << moveLeftDown << " " << moveDownTwoBlocks << " " << moveDownOneBlock << std::endl;
    // try advance the pawn 2 blocks
    if (moveDownTwoBlocks >= 0) // prioritize moving pawns 2 pieces forward
        return makeMoveUpdatePos(moveDownTwoBlocks);
    // if we can capture, then capture
    else if (moveDownRight >= 0) // prioritize capturing to the right
        return makeMoveUpdatePos(moveDownRight);
    // capture to the left now
    else if (moveLeftDown >= 0) // prioritize capturing to the left
        return makeMoveUpdatePos(moveLeftDown);
    // lastly move it one block down
    else if (moveDownOneBlock >= 0) // prioritize moving pawns one piece down
        return makeMoveUpdatePos(moveDownOneBlock);
    // piece cannot move anymore, go to the next pawn
    else { // go to the next pawn and move it
        fout2 << "Am intrat aici sa ma sugeti de buci " << currPawn << std::endl;
        currPawn++;
        if (currPawn > 8) {
            return std::make_pair(-1, -1);
        }
        lastPos = 47 + currPawn;
        // we set the parameters for the next pawn, now make a move for it
        return generatePawnMove();
    }
    fout2.close();
}
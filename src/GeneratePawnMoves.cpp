#include "GeneratePawnMoves.h";

int GeneratePawnMoves::currPawn = 1;
int GeneratePawnMoves::lastPos = 48;


pair<int, int> GeneratePawnMoves::generatePawnMove() {
    int futurePos;

    // try advance the pawn 2 blocks
    if (lastPos == currPawn + 47)
        futurePos = 48 - 2 * 8;
    // if we can capture, then capture
    else if (lastPos == )
}
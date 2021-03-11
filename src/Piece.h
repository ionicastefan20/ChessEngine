#ifndef CHESSENGINE_PIECE_H
#define CHESSENGINE_PIECE_H

#include "dependencies.h"

class Move {
    int dirX, dirY;
    int sizeX, sizeY;

public:
    Move(int dirX, int dirY, int sizeX, int sizeY);
};

class Piece {

protected:
    vector<Move *> moves;
    Piece();

    ~Piece();
};

class Pawn : Piece {

public:
    Pawn();
};

#endif //CHESSENGINE_PIECE_H

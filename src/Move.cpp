#include "Move.h"

const int Move::DIRECTIONS = new int[] {8, -8, -1, 1, 7, -7, 9, -9};

Move::Move(int dirX, int dirY, int sizeX, int sizeY) : dirX(dirX),
                                                       dirY(dirY), sizeX(sizeX), sizeY(sizeY) {}
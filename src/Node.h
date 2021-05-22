#ifndef CHESSENGINE_NODE_H
#define CHESSENGINE_NODE_H

#include <string.h>

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "Piece.h"

struct tNode{
    int board[64];

    std::unordered_map<char, int> materials;

    int colorOnMove;
    int blackKingPos;
    int whiteKingPos;

    std::vector<tNode*> next;
};
typedef struct tNode* Node;

std::vector<std::string> prev_moves;

bool is_repeat(Node& test);
void tree_insert(Node& root, int src, int dest);
void tree_delete(Node& root);

#endif
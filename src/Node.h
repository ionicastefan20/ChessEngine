#ifndef CHESSENGINE_NODE_H
#define CHESSENGINE_NODE_H

#include <string.h>

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

struct tNode{
    int board[64];

    std::unordered_map<char, int> materials;

    int colorOnMove;
    int blackKingPos;
    int whiteKingPos;
    std::string mv; // kill it later

    std::vector<tNode*> next;
};
typedef struct tNode* Node;

bool same_side(bool side, char target);

bool is_repeat(Node& test);

void tree_insert(Node& root, int src, int dest);

void tree_delete(Node& root);

#endif
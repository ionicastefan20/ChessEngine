#ifndef CHESSENGINE_NODE_H
#define CHESSENGINE_NODE_H

#include <string.h>
#include <string>
#include <vector>
#include <algorithm>

#include "Piece.h"
#include "Logger.h"

namespace node {
    struct tNode{
        int board[64];

        std::unordered_map<char, int> materials;

        int colorOnMove;
        int blackKingPos;
        int whiteKingPos;

        // move for which we have rechead this specific board state
        int start; // start pos of move
        int end; // end pos of move

        int evaluation_result;

        std::vector<tNode*> next;
    };
    typedef struct tNode* Node;

    extern std::vector<std::string> prev_moves;

    bool is_repeat(node::Node& test);
    node::Node tree_insert(node::Node& root, int src, int dest);
    void tree_delete(node::Node& root);
}
#endif
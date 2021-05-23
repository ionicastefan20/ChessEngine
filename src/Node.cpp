#include "Node.h"

// extern std::vector<std::string> prev_moves;

namespace node {
    std::vector<std::string> prev_moves;
}

bool node::is_repeat(Node& test) {
    std::string board_hash = "";

    for(int i = 0; i < 64; ++i){
        char c = piece::map[test->board[i]];
        if(c != 0) {
            board_hash += c;
        } else {
            board_hash += '0';
        }
    }

    if(board_hash.size() == 0 || std::find(node::prev_moves.begin(), node::prev_moves.end(), board_hash) == node::prev_moves.end()){
        node::prev_moves.push_back(board_hash);
        return false;
    }
    return true;
}

Node node::tree_insert(Node& root, int src, int dest) {

    Node next = new struct tNode;

    // Copying the current board state to the new board state
    memcpy(next->board, root->board, 64*sizeof(int));
    copy(move::squaresAttacked.begin(), move::squaresAttacked.end(), back_inserter(next->squaresAttacked));
    // Moving the piece from (x,y) to (p,q), replacing if needed
    int target = next->board[dest];
    next->board[dest] = next->board[src];
    next->board[src] = 0;

    // Checks if this board state has already been examined; skips it if it has been examined
    // if(!node::is_repeat(next)){

        next->materials = root->materials;
        if(target != 0) {
            next->materials[piece::map[target]] -= 1;
        }

        
        // Copying attributes from old node to new node
        if (root->board[src] == (piece::WHITE | piece::KING))
            next->whiteKingPos = dest;
        else
            next->whiteKingPos = root->whiteKingPos;
        if (root->board[src] == (piece::BLACK | piece::KING))
            next->blackKingPos = dest;
        else
            next->blackKingPos = root->blackKingPos;
        next->colorOnMove = !(root->colorOnMove);
        next->start = src;
        next->end = dest;

        root->next.push_back(next);
        return next;
    // }
    // else{
    //     delete next;
    //     return NULL;
    // }
}

void node::tree_delete(Node& root) {
    if(NULL == root)
        return;
    if(true == root->next.empty())
        return;

    std::vector<Node>::reverse_iterator r_iter;
    for(r_iter = root->next.rbegin(); r_iter != root->next.rend(); r_iter++){
        node::tree_delete(*r_iter);
        Node old = root->next.back();
        root->next.pop_back();
        delete old;
    }
}
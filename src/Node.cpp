#include "Node.h"

bool same_side(bool side, char target){

    if(0 == side && ('Q'==target || 'R'==target || 'B'==target || 'N'==target || 'P'==target || 'K'==target))
        return true;
    if(1 == side && ('q'==target || 'r'==target || 'b'==target || 'n'==target || 'p'==target || 'k'==target))
        return true;
    return false;
}

bool is_repeat(Node& test){
    std::string board_hash = "";

    for(int i = 0; i < 64; ++i){
        char c = test->board[i];
        if(c != 0) {
            board_hash += c;
        } else {
            board_hash += '0';
        }
    }

    if(0 == board_hash.size() || std::find(prev_moves.begin(), prev_moves.end(), board_hash) == prev_moves.end()){
        prev_moves.push_back(board_hash);
        // cout << "NEW HASH :: " << board_hash << endl;
        return false;
    }
    // cout << "OLD HASH :: " << board_hash << endl;
    return true;
}

void tree_insert(Node& root, int src, int dest){

    Node next = new struct tNode;

    // Copying the current board state to the new board state
    memcpy(next->board, root->board, 64*sizeof(int));
    // for(int a = 0; a < 12; ++a) {
    //     for(int b = 0; b < 12; ++b) {
    //         next->board[a][b] = root->board[a][b];
    //     }
    // }

    // Moving the piece from (x,y) to (p,q), replacing if needed
    next->board[dest] = next->board[src];
    next->board[src] = 0;
    // char source = next->board[x][y];
    // char target = next->board[p][q];
    // next->board[p][q] = source;
    // next->board[x][y] = ' ';

    // Checks if this board state has already been examined; skips it if it has been examined
    if(!is_repeat(next)){

        next->materials = root->materials;
        if(' ' != target)
            next->materials[target] -= 1;

        // Copying attributes from old node to new node
        next->w_king_pos = root->w_king_pos;
        next->b_king_pos = root->b_king_pos;
        next->cur_side = !(root->cur_side);

        string conv_array[12] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
        next->mv = "(" + conv_array[x] +  "," + conv_array[y] + ")" + "->" + "(" + conv_array[p] +  "," + conv_array[q] + ")";

        root->next.push_back(next);
    }
    else{
        delete next;
    }
}

void tree_delete(Node& root){
    if(NULL == root)
        return;
    if(true == root->next.empty())
        return;

    std::vector<Node>::reverse_iterator r_iter;
    for(r_iter = root->next.rbegin(); r_iter != root->next.rend(); r_iter++){
        tree_delete(*r_iter);
        Node old = root->next.back();
        root->next.pop_back();
        delete old;
    }
}
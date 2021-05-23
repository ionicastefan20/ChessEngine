#include "Minimax.h"

double minimax_alpha_beta(Node& root, Node& node, int depth, int state, double alpha, double beta) {
    if(depth >= MAX_DEPTH || root->next.size() == 0) {
        return evaluate::static_eval(root);
    }

    // CHOOSE MAXIMUM VALUE
    else if(state) {
        std::vector<Node>::iterator iter;
        for(iter = root->next.begin(); iter != root->next.end(); iter++) {
            if (*iter == NULL)
                continue;
            double val = minimax_alpha_beta(*iter, node, depth + 1, 0, alpha, beta);
            if(val > alpha) {
                if(depth == 0)
                    node = *iter;
                alpha = val;
            }
            if(alpha >= beta)
                break;
        }
        return alpha;
    }

    // CHOOSE MINIMUM VALUE
    else {
        std::vector<Node>::iterator iter;
        for(iter = root->next.begin(); iter != root->next.end(); iter++) {
            if (*iter == NULL)
                continue;
            double val = minimax_alpha_beta(*iter, node, depth + 1, 1, alpha, beta);
            if(val < beta) {
                if(depth == 0)
                    node = *iter;
                beta = val;
            }
            if (alpha >= beta)
                break;
        }
        return beta;
    }
}
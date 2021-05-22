#include "Minimax.h"

double minimax_alpha_beta(node::Node& root, node::Node& node, int depth, bool state, double alpha, double beta) {
    // logger::log("DEPTH", std::to_string(depth), 2);
    if(depth >= MAX_DEPTH || root->next.size() == 0) {
        // logger::log("VERIFICARE", "DA", 5);
        return evaluate::static_eval(root);
    }

    // CHOOSE MAXIMUM VALUE
    else if(state) {
        std::vector<node::Node>::iterator iter;
        for(iter = root->next.begin(); iter != root->next.end(); iter++) {
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
        std::vector<node::Node>::iterator iter;
        for(iter = root->next.begin(); iter != root->next.end(); iter++) {
            double val = minimax_alpha_beta(*iter, node, depth + 1, 1, alpha, beta);
            if(val < beta) {
                if(depth == 0)
                    node = *iter;
                beta = val;
            }
            return beta;
        }
    }
}
#include "Minimax.h"

double negamax_alpha_beta(Node& root, Node& node, int depth, int state, double alpha, double beta) {
    if(depth >= MAX_DEPTH || root->next.size() == 0) {
        double result = evaluate::static_eval(root);
        // logger::log("Score", std::to_string(depth) + "->" + std::to_string(result)
        //     + " " + std::to_string(alpha) + " " + std::to_string(beta) + " ", 0);
        return result;
    }

    double best_score = -100000;
    std::vector<Node>::iterator iter;
    for(iter = root->next.begin(); iter != root->next.end(); iter++) {
        if (*iter == NULL)
            continue;
        double val = -negamax_alpha_beta(*iter, node, depth + 1, 0, -beta, -alpha);
        if (val > best_score) {
            best_score = val;
            if(depth == 0)
                node = *iter;
        }

        if(val > alpha) {
            alpha = best_score;
        }

        // logger::log("Score", std::to_string(depth) + "->" + std::to_string(val)
        //     + " " + std::to_string(alpha) + " " + std::to_string(beta) + " ", 0);
        if(alpha >= beta)
            break;
    }

    return best_score;
}

double minimax_alpha_beta(Node& root, Node& node, int depth, int state, double alpha, double beta) {
    if(depth >= MAX_DEPTH || root->next.size() == 0) {
        double result = evaluate::static_eval(root);
        logger::log("Score", std::to_string(depth) + "->" + std::to_string(result)
            + " " + std::to_string(alpha) + " " + std::to_string(beta) + " ", 0);
        return result;
    }

    // CHOOSE MAXIMUM VALUE
    else if(state) {
        double best_score = -100000;
        std::vector<Node>::iterator iter;
        for(iter = root->next.begin(); iter != root->next.end(); iter++) {
            if (*iter == NULL)
                continue;
            double val = minimax_alpha_beta(*iter, node, depth + 1, 0, alpha, beta);
            if (val > best_score) {
                best_score = val;
                if(depth == 0)
                    node = *iter;
            }
            if(val > alpha) {
                alpha = val;
            }
            logger::log("Score", std::to_string(depth) + "->" + std::to_string(val)
                + " " + std::to_string(alpha) + " " + std::to_string(beta) + " ", 0);
            if(alpha >= beta)
                break;
        }
        return best_score;
    }

    // CHOOSE MINIMUM VALUE
    else {
        double best_score = 100000;
        std::vector<Node>::iterator iter;
        for(iter = root->next.begin(); iter != root->next.end(); iter++) {
            if (*iter == NULL)
                continue;
            double val = minimax_alpha_beta(*iter, node, depth + 1, 1, alpha, beta);
            if (val < best_score) {
                best_score = val;
                if(depth == 0)
                    node = *iter;
            }
            if(val < beta) {
                beta = val;
            }
            logger::log("Score", std::to_string(depth) + "->" + std::to_string(val)
                + " " + std::to_string(alpha) + " " + std::to_string(beta) + " ", 0);
            if (alpha >= beta)
                break;
        }
        return best_score;
    }
}
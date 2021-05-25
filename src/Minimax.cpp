#include "Minimax.h"

double negamax_alpha_beta(int start_init, int end_init, int& start_res, int& end_res, int depth, double alpha, double beta, int botColor) {
    move::calculateSquaresAttacked();
    move::generate();

    int moves_count = 0;
    for (auto& p : move::moves) {
        moves_count += p.second.size();
    }

    if (depth != 0) {
        if (board::colorOnMove == piece::WHITE) {
            // logger::logBoard(root->board);
            // logger::logBoard2(root->squaresAttacked);
            // logger::log("size I I I I N N N N", std::to_string(root->squaresAttacked.size()), 3);
            // logger::log("black king", std::to_string(root->blackKingPos), 2);
            logger::logBoard(board::squares);
            logger::logBoard2(move::squaresAttacked);
            logger::log("eval check", std::to_string(move::squaresAttacked[board::whiteKingPos]), 2);
            if (move::squaresAttacked[board::whiteKingPos]) {
                return -100000;
            }
            int botColorCopy = board::botColor;
            board::botColor = board::getOppositeBotColor(board::botColor);
            move::calculateSquaresAttacked();
            if (move::squaresAttacked[board::blackKingPos])
                return 100000;
            board::botColor = botColorCopy;
        } else {
            // logger::logBoard(root->board);
            // logger::logBoard2(root->squaresAttacked);
            // logger::log("size I I I I N N N N", std::to_string(root->squaresAttacked.size()), 3);
            // logger::log("white king", std::to_string(root->whiteKingPos), 2);
            // logger::log("dereferentiere", std::to_string(root->squaresAttacked[root->whiteKingPos]), 5);
            logger::logBoard(board::squares);
            logger::logBoard2(move::squaresAttacked);
            if (move::squaresAttacked[board::blackKingPos]) {
                return 100000;
            }
            int botColorCopy = board::botColor;
            board::botColor = board::getOppositeBotColor(board::botColor);
            move::calculateSquaresAttacked();
            if (move::squaresAttacked[board::whiteKingPos])
                return -100000;
            board::botColor = botColorCopy;
        }
    }
    // move::calculateSquaresAttacked();

    if(depth >= MAX_DEPTH || moves_count == 0) {
        double result = evaluate::static_eval();
        // logger::log("Score", std::to_string(depth) + "->" + std::to_string(result)
        //     + " " + std::to_string(alpha) + " " + std::to_string(beta) + " ", 0);
        return result;
    }

    std::unordered_map<int, std::vector<int>> moves_copy;
    for (auto move : move::moves) {
        std::vector<int> next_moves_copy(move.second);
        moves_copy[move.first] = next_moves_copy;
    }

    double best_score = -DBL_MAX;
    for (auto move : moves_copy) {  // for every legal pair of moves (start -> end)
        int start = move.first;
        for (auto legal_move : move.second) {
            int end = legal_move;

            // Create a copy of the board state
            BState copy = moveGenerator::make_copy(botColor);

            // Update the materials
            if(board::squares[end] != 0) {
                // logger::log("MatUpdate=" + piece::map[board::squares[end]], std::to_string(board::materials[piece::map[board::squares[end]]]), 0);
                board::materials[piece::map[board::squares[end]]] -= 1;
                // logger::log("MatUpdate=" + std::to_string(piece::map[board::squares[end]]), std::to_string(board::materials[piece::map[board::squares[end]]]), 0);
            }

            // make the move
            board::makeMove(board::encodeMove({start, end}));
            if (botColor == board::botColor) {
                // generate squares attacked for bot
                board::botColor = board::getOppositeBotColor(board::botColor);
                move::calculateSquaresAttacked();
                board::botSquaresAttacked = move::squaresAttacked;
                // restore bot color
                board::botColor = board::getOppositeBotColor(board::botColor);
            }
            // logger::logBoard2(board::botSquaresAttacked);
            // logger::log("Depth", std::to_string(depth), 0);

            board::botColor = board::getOppositeBotColor(board::botColor);

            double score = -negamax_alpha_beta(start, end, start_res, end_res, depth + 1, -beta, -alpha, botColor);
            // logger::logBoard(board::squares);
            // logger::log("Depth", std::to_string(depth), 0);
            if (score > best_score) {
                best_score = score;
                if(depth == 0) {
                    start_res = start;
                    end_res = end;
                    // logger::log("start_res", std::to_string(start_res), 1);
                    // logger::log("end_res", std::to_string(end_res), 1);
                }
            }
            // logger::log("Best", std::to_string(best_score), 0);
            // logger::log("Move", std::to_string(start_res) + " " + std::to_string(end_res), 0);

            if (best_score > alpha)
                alpha = best_score;

            // Restore the board state
            moveGenerator::restore_copy(copy);

            if (alpha >= beta)
                // break;
                return alpha;
        }
    }

        // restore copy
    // move::moves.clear();
    // for (auto move_cpy : moves_copy) {
    //     move::moves[move_cpy.first] = move_cpy.second;
    // }

    return best_score;
}

// double minimax_alpha_beta(Node& root, Node& node, int depth, int state, double alpha, double beta) {
//     if(depth >= MAX_DEPTH || root->next.size() == 0) {
//         double result = evaluate::static_eval(root);
//         // logger::log("Score", std::to_string(depth) + "->" + std::to_string(result)
//         //     + " " + std::to_string(alpha) + " " + std::to_string(beta) + " ", 0);
//         return result;
//     }

//     // CHOOSE MAXIMUM VALUE
//     else if(state) {
//         double best_score = -DBL_MAX;
//         std::vector<Node>::iterator iter;
//         for(iter = root->next.begin(); iter != root->next.end(); iter++) {
//             if (*iter == NULL)
//                 continue;
//             double val = minimax_alpha_beta(*iter, node, depth + 1, 0, alpha, beta);
//             if (val > best_score) {
//                 best_score = val;
//                 if(depth == 0)
//                     node = *iter;
//             }
//             if(val > alpha) {
//                 alpha = val;
//             }
//             // logger::log("Score", std::to_string(depth) + "->" + std::to_string(val)
//             //     + " " + std::to_string(alpha) + " " + std::to_string(beta) + " ", 0);
//             if(alpha >= beta)
//                 break;
//         }
//         return best_score;
//     }

//     // CHOOSE MINIMUM VALUE
//     else {
//         double best_score = DBL_MAX;
//         std::vector<Node>::iterator iter;
//         for(iter = root->next.begin(); iter != root->next.end(); iter++) {
//             if (*iter == NULL)
//                 continue;
//             double val = minimax_alpha_beta(*iter, node, depth + 1, 1, alpha, beta);
//             if (val < best_score) {
//                 best_score = val;
//                 if(depth == 0)
//                     node = *iter;
//             }
//             if(val < beta) {
//                 beta = val;
//             }
//             // logger::log("Score", std::to_string(depth) + "->" + std::to_string(val)
//             //     + " " + std::to_string(alpha) + " " + std::to_string(beta) + " ", 0);
//             if (alpha >= beta)
//                 break;
//         }
//         return best_score;
//     }
// }
#include "Minimax.h"

double negamax_alpha_beta(int start_init, int end_init, int& start_res, int& end_res, int depth, double alpha, double beta, int botColor) {
    move::calculateSquaresAttacked();
    move::generate();

    int moves_count = 0;
    for (auto& p : move::moves) {
        moves_count += p.second.size();
    }

    double check_bonus = 0;
    if (depth != 0) {
        if (board::colorOnMove == piece::WHITE) {
            if (move::squaresAttacked[board::whiteKingPos]) {
                check_bonus = 10000;
            }
        } else {
            if (move::squaresAttacked[board::blackKingPos]) {
                // logger::log("DAAAA", "DAAAA", 3);
                check_bonus = -10000;
            }
        }
    }

    if(depth >= MAX_DEPTH || moves_count == 0) {
        double result = evaluate::static_eval();
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
                board::materials[piece::map[board::squares[end]]] -= 1;
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

            board::botColor = board::getOppositeBotColor(board::botColor);

            double score = check_bonus - negamax_alpha_beta(start, end, start_res, end_res, depth + 1, -beta, -alpha, botColor);
            if (score > best_score) {
                best_score = score;
                if(depth == 0) {
                    start_res = start;
                    end_res = end;
                }
            }

            if (best_score > alpha)
                alpha = best_score;

            // Restore the board state
            moveGenerator::restore_copy(copy);

            if (alpha >= beta)
                return alpha;
        }
    }

    return best_score;
}
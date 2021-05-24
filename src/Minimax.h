#ifndef MINIMAX_H
#define MINIMAX_H

#include "Evaluate.h"
#include "MoveGenerator.h"
#include "Logger.h"

#define MAX_DEPTH 1

typedef struct tNode* Node;

// double minimax_alpha_beta(Node& root, Node& node, int depth, int state, double alpha, double beta);
double negamax_alpha_beta(int start_init, int end_init, int& start_res, int& end_res, int depth, double alpha, double beta);

#endif
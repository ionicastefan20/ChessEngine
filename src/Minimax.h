#ifndef MINIMAX_H
#define MINIMAX_H

#include "Evaluate.h"
#include "Logger.h"
#include "Node.h"

#define MAX_DEPTH 3

double minimax_alpha_beta(node::Node& root, node::Node& node, int depth, int state, double alpha, double beta);

#endif
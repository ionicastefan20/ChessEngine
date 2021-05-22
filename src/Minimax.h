#ifndef MINIMAX_H
#define MINIMAX_H

#include "Evaluate.h"
#include "Logger.h"

#define MAX_DEPTH 4

double minimax_alpha_beta(node::Node& root, node::Node& node, int depth, bool state, double alpha, double beta);

#endif
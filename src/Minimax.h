#ifndef MINIMAX_H
#define MINIMAX_H

#include "Evaluate.h"
#include "Logger.h"
#include "Node.h"

#define MAX_DEPTH 2

typedef struct tNode* Node;

double minimax_alpha_beta(Node& root, Node& node, int depth, int state, double alpha, double beta);
double negamax_alpha_beta(Node& root, Node& node, int depth, int state, double alpha, double beta);

#endif
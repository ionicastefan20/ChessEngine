#ifndef MINIMAX_H
#define MINIMAX_H

#include "Evaluate.h"
#include "MoveGenerator.h"
#include "Logger.h"

#define MAX_DEPTH 3

typedef struct tNode* Node;

double negamax_alpha_beta(int start_init, int end_init, int& start_res, int& end_res, int depth, double alpha, double beta, int botColor);

#endif
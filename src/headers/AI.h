/*
 * AI.h
 */

#ifndef AI_H
#define AI_H

#define NODE pair<int,int>

#include "State.h"
#include <utility>
#include <algorithm>
#include <climits>
#include <iostream>

class AI
{
public:
    AI(bool useMinmax, int depthBound);

    int play(State *state);

private:
    bool useMinmax;
    int depthBound;
    int visitedNodes;
    
    int minmax(State *state);
    int alfaBeta(State *state);

    NODE maxValue(State *state, int depth, int alfa=0, int beta=0);
    NODE minValue(State *state, int depth, int alfa=0, int beta=0);
};

#endif

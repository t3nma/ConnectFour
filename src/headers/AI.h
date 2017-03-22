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

    int play(State *state) const;  

private:
    bool useMinmax;
    int depthBound;
    
    int minmax(State *state) const;
    int alfaBeta(State *state) const;

    NODE maxValue(State *state, int depth, int alfa=0, int beta=0) const;
    NODE minValue(State *state, int depth, int alfa=0, int beta=0) const;
};

#endif

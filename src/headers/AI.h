/*
 * AI.h
 */

#ifndef AI_H
#define AI_H

#define NODE pair<int,int>

#include "State.h"
#include "Globals.h"
#include <utility>
#include <algorithm>
#include <climits>
#include <iostream>
#include <iomanip>
#include <ctime>

struct Performance
{
public:

    int expandedNodes;
    double elapsedTime;

    void init()
    {
	expandedNodes = 0;
	clock_gettime(CLOCK_MONOTONIC,&start);
    }
    
    void time()
    {
	struct timespec end;
	clock_gettime(CLOCK_MONOTONIC,&end);
	elapsedTime = (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec)/1000000000.0);
    }
    
private:
    struct timespec start;
};

class AI
{
public:
    AI(bool useMinmax, int depthBound);

    int play(State *state);

private:
    bool useMinmax;
    int depthBound;
    Performance performance;
    
    int minmax(State *state);
    int alfaBeta(State *state);

    NODE maxValue(State *state, int depth, int alfa=0, int beta=0);
    NODE minValue(State *state, int depth, int alfa=0, int beta=0);
};

#endif

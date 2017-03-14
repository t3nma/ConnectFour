/*
 * AI.h
 */

#ifndef AI_H
#define AI_H

#include "State.h"

class AI
{
public:
    AI(int depthBound);

    void play(State *state, bool minmax) const;  

private:
    int depthBound;
    
    int minmax() const;
    State* alphaBeta() const;

    int maxValue(State *state) const;
    int minValue(State *state) const;
};

#endif

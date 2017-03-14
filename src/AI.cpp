#include "headers/AI.h"
#include <iostream>

AI::AI(int depthBound)
    : depthBound(depthBound)
{
}

void AI::play(State *state, bool minmax) const
{
    return;
}

int AI::minmax() const
{
    return 0;
}

State* AI::alphaBeta() const
{
    return NULL;
}

int AI::maxValue(State *state) const
{
    return 0;
}

int AI::minValue(State *state) const
{
    return 0;
}

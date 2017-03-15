#include "headers/AI.h"

AI::AI(bool useMinmax, int depthBound)
    : useMinmax(useMinmax),
      depthBound(depthBound)
{
}

int AI::play(State *state) const
{
    return useMinmax ? minmax(state) : alphaBeta(state);
}

int AI::minmax(State *state) const
{
    return maxValue(state,1).second;
}

int AI::alphaBeta(State *state) const
{
    return 0;
}

NODE AI::maxValue(State *state, int depth) const
{
    NODE result(-1,-1); // (utility,move)

    if( (result.first = state->isTerminal()) != -1)
	return result;
    else if(depth == depthBound)
    {
	result.first = state->eval();
	return result;
    }
    else
	result.first = INT_MIN;
    
    vector<State*> childs = state->makeDescendants(1);
    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	NODE tmp = minValue(*it,depth+1);
	if(tmp.first > result.first)
	{
	    result.first = tmp.first;
	    //result.second = (*it)->getParentMove();
	}
    }

    return result;
}

NODE AI::minValue(State *state, int depth) const
{
    NODE result(-1,-1); // (utility,move)

    if( (result.first = state->isTerminal()) != 0 )
	return result;
    else if(depth == depthBound)
    {
	result.first = state->eval();
	return result;
    }
    else
	result.first = INT_MAX;
    
    vector<State*> childs = state->makeDescendants(2);
    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	NODE tmp = maxValue(*it,depth+1);
	if(tmp.first < result.first)
	{
	    result.first = tmp.first;
	    //result.second = (*it)->getParentMove();
	}
    }

    return result;
}
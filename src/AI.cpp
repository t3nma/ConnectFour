#include "headers/AI.h"

AI::AI(bool useMinmax, int depthBound)
    : useMinmax(useMinmax),
      depthBound(depthBound)
{
    if(!useMinmax)
	cout << "USING ALFA BETA!\n";
}

int AI::play(State *state)
{
    visitedNodes = 0;
    int r = useMinmax ? minmax(state) : alfaBeta(state);
    cout << "Visited Nodes: " << visitedNodes << endl;
    
    return r;
}

int AI::minmax(State *state)
{
    return maxValue(state,0).second;
}

int AI::alfaBeta(State *state)
{
    return maxValue(state,0,INT_MIN,INT_MAX).second;
}

NODE AI::maxValue(State *state, int depth, int alfa, int beta)
{
    NODE result(-1,state->getMove()); // (utility,move)
    
    if( (result.first = state->isTerminal()) != 0)
	return result;
    else if(depth == depthBound)
    {
	result.first = state->eval();
	return result;
    }
    else
	result.first = INT_MIN;

    vector<State*> childs = state->makeDescendants(2);
    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	NODE tmp = minValue(*it,depth+1,alfa,beta);
	visitedNodes++;
	
	if(tmp.first > result.first)
	{
	    result.first = tmp.first;
	    result.second = (*it)->getMove();
	}

	delete (*it); // free state*
	
	if(!useMinmax)
	{
	    if(tmp.first >= beta)
		return result;
	    alfa = max(alfa,tmp.first);
	}
    }
    
    return result;
}

NODE AI::minValue(State *state, int depth, int alfa, int beta)
{
    NODE result(-1,state->getMove()); // (utility,move)

    if( (result.first = state->isTerminal()) != 0 )
	return result;
    else if(depth == depthBound)
    {
	result.first = state->eval();
	return result;
    }
    else
	result.first = INT_MAX;

    vector<State*> childs = state->makeDescendants(1);
    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	NODE tmp = maxValue(*it,depth+1,alfa,beta);
	visitedNodes++;
	
	if(tmp.first < result.first)
	{
	    result.first = tmp.first;
	    result.second = (*it)->getMove();
	}

	delete (*it); // free state*
	
	if(!useMinmax)
	{
	    if(tmp.first <= alfa)
		return result;
	    beta = min(beta,tmp.first);
	}
    }

    return result;
}

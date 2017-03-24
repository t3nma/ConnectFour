#include "headers/AI.h"

AI::AI(bool useMinmax, int depthBound)
    : useMinmax(useMinmax),
      depthBound(depthBound)
{
}

int AI::play(State *state)
{
    performance.init();
    int action = useMinmax ? minmax(state) : alfaBeta(state);
    performance.time();

    cout << "Action: " << action << endl;
    cout << setprecision(2) << "Time spent: " << performance.elapsedTime << "s" << endl;
    cout << "Nodes visited: " << performance.expandedNodes << endl;
    
    return action;
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
    
    if(depth == depthBound)
    {
	result.first = state->eval();
	return result;
    }

    vector<State*> childs = state->makeDescendants(2);
    bool foundTerminal = false;

    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	if(!foundTerminal && (result.first = (*it)->isTerminal()) != 0 )
	{
	    result.second = (*it)->getMove();
	    foundTerminal = true;
	}

	delete (*it);
    }

    if(foundTerminal)
	return result;
    
    childs.clear();
    childs = state->makeDescendants(2);
    result.first = INT_MIN;
    
    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	NODE tmp = minValue(*it,depth+1,alfa,beta);
	performance.expandedNodes++;
	
	if(tmp.first > result.first)
	{
	    result.first = tmp.first;
	    result.second = (*it)->getMove();
	}
	
	if(!useMinmax)
	{
	    if(tmp.first >= beta)
		return result;
	    alfa = max(alfa,tmp.first);
	}

	delete (*it); // free state*
    }
    
    return result;
}

NODE AI::minValue(State *state, int depth, int alfa, int beta)
{
    NODE result(-1,state->getMove()); // (utility,move)

    if(depth == depthBound)
    {
	result.first = state->eval();
	return result;
    }

    vector<State*> childs = state->makeDescendants(1);
    bool foundTerminal = false;

    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	if(!foundTerminal && (result.first = (*it)->isTerminal()) != 0 )
	{
	    result.second = (*it)->getMove();
	    foundTerminal = true;
	}

	delete (*it);
    }

    if(foundTerminal)
	return result;
    

    childs.clear();
    childs = state->makeDescendants(1);
    result.first = INT_MAX;
    
    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	NODE tmp = maxValue(*it,depth+1,alfa,beta);
	performance.expandedNodes++; 
	
	if(tmp.first < result.first)
	{
	    result.first = tmp.first;
	    result.second = (*it)->getMove();
	}
	
	if(!useMinmax)
	{
	    if(tmp.first <= alfa)
		return result;
	    beta = min(beta,tmp.first);
	}

	delete (*it); // free state*
    }

    return result;
}

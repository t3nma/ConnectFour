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
    cout << "Expanded nodes: " << performance.expandedNodes << endl;
    
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
    NODE result(state->eval(depth),state->getMove());
    if(result.first <= -512 || state->isFull() || depth == depthBound)
	return result;

    result.first = INT_MIN;
    vector<State*> childs = state->makeDescendants(2);
    performance.expandedNodes += (int)childs.size();    
    
    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	NODE tmp = minValue(*it,depth+1,alfa,beta);

	if(tmp.first >= 512 && result.first >= 512)
	{
	    if(tmp.first < result.first)
	    {
		result.first = tmp.first;
		result.second = (*it)->getMove();
	    }
	}
	else if(tmp.first > result.first)
	{
	    result.first = tmp.first;
	    result.second = (*it)->getMove();
	}
	
	if(!useMinmax)
	{
	    if(tmp.first >= beta)
	    {
		for(; it!=childs.end(); ++it) delete (*it);
		return result;
	    }
	    alfa = max(alfa, min(tmp.first,512));
	}

	delete (*it); // free state*
    }
    
    return result;
}

NODE AI::minValue(State *state, int depth, int alfa, int beta)
{
    NODE result(state->eval(depth),state->getMove());
    if(result.first >= 512 || state->isFull() || depth == depthBound)
	return result;
   
    result.first = INT_MAX;
    vector<State*> childs = state->makeDescendants(1);
    performance.expandedNodes += (int)childs.size();
    
    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	NODE tmp = maxValue(*it,depth+1,alfa,beta);

	if(tmp.first <= -512 && result.first <= -512)
	{
	    if(tmp.first > result.first)
	    {
		result.first = tmp.first;
		result.second = (*it)->getMove();
	    }
	}
	else if(tmp.first < result.first)
	{
	    result.first = tmp.first;
	    result.second = (*it)->getMove();
	}
	
	if(!useMinmax)
	{
	    if(tmp.first <= alfa)
	    {
		for(; it!=childs.end(); ++it) delete (*it);
		return result;
	    }
	    beta = min(beta, max(tmp.first,-512));
	}

	delete (*it); // free state*
    }

    return result;
}

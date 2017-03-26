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
    cout << setprecision(3) << "Time spent: " << performance.elapsedTime << "s" << endl;
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
    NODE result(state->eval(),state->getMove());
    if(state->isFull() || depth == depthBound)
	return result;

    result = checkForOptimalTerm(state,BOT);
    if(result.first != -1)
    	return result;
    
    result.first = INT_MIN;
    vector<State*> childs = state->makeDescendants(BOT);
    performance.expandedNodes += (int)childs.size();    
    
    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	NODE tmp = minValue(*it,depth+1,alfa,beta);

	if(tmp.first > result.first)
	{
	    result.first = tmp.first;
	    result.second = (*it)->getMove();
	}

	// alfa-beta 
	if(!useMinmax)
	{
	    if(tmp.first >= beta)
	    {
		for(; it!=childs.end(); ++it) delete (*it);
		return result;
	    }
	    alfa = max(alfa, tmp.first);
	}

	delete (*it); // free state*
    }
    
    return result;
}

NODE AI::minValue(State *state, int depth, int alfa, int beta)
{
    NODE result(state->eval(),state->getMove());
    if(state->isFull() || depth == depthBound)
	return result;

    result = checkForOptimalTerm(state,HUMAN);
    if(result.first != -1)
    	return result;
    
    result.first = INT_MAX;
    vector<State*> childs = state->makeDescendants(HUMAN);
    performance.expandedNodes += (int)childs.size();
    
    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	NODE tmp = maxValue(*it,depth+1,alfa,beta);

	if(tmp.first < result.first)
	{
	    result.first = tmp.first;
	    result.second = (*it)->getMove();
	}

	// alfa-beta
	if(!useMinmax)
	{
	    if(tmp.first <= alfa)
	    {
		for(; it!=childs.end(); ++it) delete (*it);
		return result;
	    }
	    beta = min(beta, tmp.first);
	}

	delete (*it); // free state*
    }

    return result;
}

NODE AI::checkForOptimalTerm(State *state, int player)
{
    NODE result(-1,-1);
    bool foundTerm = false;

    vector<State*> childs = state->makeDescendants(player);
    performance.expandedNodes += (int)childs.size();

    for(auto it=childs.begin(); it!=childs.end(); ++it)
    {
	if(!foundTerm)
	{
	    int points = (*it)->eval();
	    if( (player == HUMAN && points == -512) || (player == BOT && points == 512) )
	    {
		result.first = points;
		result.second = (*it)->getMove();
		foundTerm = true;
	    }
	}
	    
	delete (*it);
    }

    return result;
}

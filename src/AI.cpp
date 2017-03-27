#include "headers/AI.h"

// default constructor
AI::AI(bool useMinimax, int depthBound)
    : useMinimax(useMinimax),
      depthBound(depthBound)
{
}

// initialize performance checker and
// start minimax or alpha-Beta to get and return the AI play
int AI::play(State *state)
{
    performance.init();
    int action = useMinimax ? minimax(state) : alphaBeta(state);
    performance.time();

    cout << "Action: " << action << endl;
    cout << setprecision(3) << "Time spent: " << performance.elapsedTime << "s" << endl;
    cout << "Expanded nodes: " << performance.expandedNodes << endl;
    
    return action;
}

int AI::minimax(State *state)
{
    return maxValue(state,0).second;
}

int AI::alphaBeta(State *state)
{
    return maxValue(state,0,INT_MIN,INT_MAX).second;
}

NODE AI::maxValue(State *state, int depth, int alfa, int beta)
{
    NODE result(state->getUtility(),state->getMove());
    if(state->getUtility() == MIN_UTILITY || state->isFull() || depth == depthBound)
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
	if(!useMinimax)
	{
	    if(tmp.first >= beta)
	    {
		for(; it!=childs.end(); ++it) delete (*it);
		return result;
	    }

	    alfa = max(alfa, tmp.first);
	}

	delete (*it);
    }
    
    return result;
}

NODE AI::minValue(State *state, int depth, int alfa, int beta)
{
    NODE result(state->getUtility(),state->getMove());
    if(state->getUtility() == MAX_UTILITY || state->isFull() || depth == depthBound)
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
	if(!useMinimax)
	{
	    if(tmp.first <= alfa)
	    {
		for(; it!=childs.end(); ++it) delete (*it);
		return result;
	    }

	    beta = min(beta, tmp.first);
	}

	delete (*it);
    }

    return result;
}

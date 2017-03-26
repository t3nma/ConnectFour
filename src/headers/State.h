#ifndef STATE_H
#define STATE_H

#include <vector>
#include "Column.h"
using namespace std;

class State
{
public:
    State(int nRows, int nCols, int move=-1);
    State(const State& s);
    State& operator=(const State& s);
    ~State();

    int getMove() const;
    void setMove(int move);
    
    bool play(int player, int column);
    vector<State*> makeDescendants(int player) const;
    int isTerminal() const;
    bool isFull() const;
    void print() const;

    int getUtility() const;
    // TODO << SUPPORT
    
private:
    int r;
    int c;
    Column *board;
    int move;
    int utility;

    void eval();
    int evalRows() const;
    int evalColumns() const;
    int evalDiagonals() const;
    int runEvalDiagonal(int x, int y, int dirX, int dirY) const;
    int segmentPoints(int humanCount, int pcCount) const;
};

class CompareUtility
{   
public:

    CompareUtility(const bool& reverse=false)
	: reverse(reverse)
    {
    }

    bool operator()(const State* lhs, const State* rhs) const
    {
	if(reverse)
	    return(lhs->getUtility() > rhs->getUtility());
	else
	    return(lhs->getUtility() < rhs->getUtility());
	  
    }
    
private:
    bool reverse;
};

#endif

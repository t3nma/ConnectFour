#include <iostream>
#include "headers/State.h"

State::State(int nRows, int nCols)
    : r(nRows),
      c(nCols),
      board(new Column[c])
{
    for(int i=0; i<c; ++i)
	board[i].set(r);
}

State::State(int **state, int nRows, int nCols)
    : r(nRows),
      c(nCols),
      board(new Column[c])
{
    for(int i=0; i<c; ++i)
	board[i].set(r);

    for(int i=0; i<r; ++i)
	for(int j=0; j<c; ++j)
	    board[j].placeCell( state[r-1-i][j] );
}

State::State(const State& s)
    : r(s.r),
      c(s.c)
{
    board = new Column[c];
    for(int i=0; i<c; ++i)
	board[i] = s.board[i];
}

State& State::operator=(const State& s)
{
    r = s.r;
    c = s.c;
    
    if(board != NULL)
	delete [] board;

    board = new Column[c];
    for(int i=0; i<c; ++i)
	board[i] = s.board[i];

    return *this;
}

State::~State()
{
    if(board != NULL)
	delete [] board;
}


vector<State*> State::makeDescendants(int player) const
{
    vector<State*> descendants;

    for(int i=0; i<c; ++i)
    {
	State* s = new State(*this);
	bool changed = false;

	if(!s->board[i].isFull())
	{
	    s->board[i].placeCell(player);
	    changed = true;
	}

	if(changed)
	    descendants.push_back(s);
    }

    return descendants;
}


bool State::isFinal() const
{
    for(int i=0; i<c; ++i)
	if(!board[i].isFull())
	    return false;

    return true;
}

void State::print() const
{
    for(int i=r-1; i>=0; --i)
    {
	for(int j=0; j<c; ++j)
	    cout << board[j].getCell(i) << " ";
	cout << endl;
    }
}

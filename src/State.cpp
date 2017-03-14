#include <iostream>
#include "headers/State.h"

State::State(int nRows, int nCols)
    : r(nRows),
      c(nCols),
      board(new Column[c])
{
    for(int i=0; i<c; ++i)
	board[i].init(r);
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

bool State::play(int player, int column)
{
    if(column < 0 || column >= c || board[column].isFull())
	return false;

    board[column].placeCell(player);
    return true;
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

bool State::isTerminal() const
{
    return ( hasWinner() || isFull() );
}

void State::print() const
{
    char sym[] = {'.', 'X', 'O'};
    for(int i=r-1; i>=0; --i)
    {
	for(int j=0; j<c; ++j)
	    cout << sym[ board[j].getCell(i) ] << " ";
	cout << endl;
    }
}

bool State::hasWinner() const
{
    return ( checkRows() || checkColumns() || checkDiagonals() );
}

bool State::isFull() const
{
    for(int i=0; i<c; ++i)
	if(!board[i].isFull())
	    return false;

    return true;
}

bool State::checkRows() const
{
    for(int i=0; i<r; ++i)
    {
	int human=0, pc=0;
	for(int j=0; j<c; ++j)
	{
	    switch(board[j].getCell(i))
	    {
	        case 1:
		    human++; pc=0; break;
	        case 2:
		    human=0; pc++; break;
	        default:
		    human=0; pc=0;
	    }

	    if(human == 4 || pc == 4)
		return true;
	}
    }
    
    return false;
}

bool State::checkColumns() const
{
    for(int j=0; j<c; ++j)
    {
	int human=0, pc=0;
	for(int i=0; i<r; ++i)
	{
	    switch(board[j].getCell(i))
	    {
	        case 1:  human++; pc=0; break;
	        case 2:  human=0; pc++; break;
	        default: human=0; pc=0;
	    }

	    if(human == 4 || pc == 4)
		return true;
	}
    }

    return false;
}

bool State::checkDiagonals() const
{
    // top-left to top-right
    for(int j=0; j<c && (c-j >= 4); ++j)
	if( runDiagonal(0,j,1,1) )
	    return true;
    
    // top-left to bottom-left
    for(int i=1; i<r && (r-i >= 4); ++i)
	if( runDiagonal(i,0,1,1) )
	    return true;

    // bottom-left to top-left
    for(int i=r-1; i>=0 && (i+1 >= 4); --i)
	if( runDiagonal(i,0,-1,1) )
	    return true;
    
    // bottom-left to bottom-right
    for(int j=1; j<c && (c-j >= 4); ++j)
	if( runDiagonal(r-1,j,-1,1) )
	    return true;
    
    return false;
}

bool State::runDiagonal(int x, int y, int dirX, int dirY) const
{
    int human=0, pc=0;
    while(x>=0 && x<r && y>=0 && y<c)
    {
	switch(board[y].getCell(x))
	{
	    case 1:  human++; pc=0; break;
	    case 2:  human=0; pc++; break;
	    default: human=0; pc=0;
	}

	if(human == 4 || pc == 4)
	    return true;
	
	x+=dirX;
	y+=dirY;
    }

    return false;
}

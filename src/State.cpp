#include <iostream>
#include "headers/State.h"

State::State(int nRows, int nCols, int move)
    : r(nRows),
      c(nCols),
      board(new Column[c]),
      move(move)
{
    for(int i=0; i<c; ++i)
	board[i].init(r);
}

State::State(const State& s)
    : r(s.r),
      c(s.c),
      board(new Column[c]),
      move(s.move)
{
    for(int i=0; i<c; ++i)
	board[i] = s.board[i];
}

State& State::operator=(const State& s)
{
    r = s.r;
    c = s.c;
    move = s.move;
    
    delete [] board;

    board = new Column[c];
    for(int i=0; i<c; ++i)
	board[i] = s.board[i];

    return *this;
}

State::~State()
{
    if(board != nullptr)
	delete [] board;
}

int State::getMove() const
{
    return move;
}

void State::setMove(int move)
{
    this->move = move;
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
	State *s = new State(*this);
	bool changed = false;
	
	if(!s->board[i].isFull())
	{
	    s->board[i].placeCell(player);
	    s->setMove(i);
	    changed = true;
	}

	if(changed)
	    descendants.push_back(s);
    }

    return descendants;
}

int State::isTerminal() const
{
    int winner;
    if((winner = hasWinner()) != 0)
	return winner;
    
    return isFull();
}
  
int State::eval() const
{
    int bonus = 16;
    return evalRows() + evalColumns() + evalDiagonals() + bonus;
}

void State::print() const
{
    cout << endl;
    
    char sym[] = {'.', 'X', 'O'};
    
    for(int i=r-1; i>=0; --i)
    {
	for(int j=0; j<c; ++j)
	    cout << sym[ board[j].getCell(i) ] << " ";
	cout << endl;
    }

    for(int j=0; j<c; ++j)
	cout << j << " ";
    cout << endl << endl;
}

int State::hasWinner() const
{
    int value;
    
    if( (value = checkRows()) != 0)
	return value;

    if( (value = checkColumns()) != 0)
	return value;

    if( (value = checkDiagonals()) != 0)
	return value;
    
    return 0;
}

int State::isFull() const
{
    for(int i=0; i<c; ++i)
	if(!board[i].isFull())
	    return 0;

    return 1;
}

int State::evalRows() const
{
    int total = 0;

    for(int i=0; i<r; ++i)
    {
        for (int j=0; j<=(c-4); ++j)
	{
	    int human=0, pc=0;
	    for(int k=j; k<(j+4); ++k) 
	    {
		switch(board[k].getCell(i))
		{
		    case 1:
			human++; break;
		    case 2:
			pc++; break;
		    default:
		        break;
		}
	    }

	    total += segmentPoints(human,pc);
	}
    }
    
    return total;
}

int State::evalColumns() const
{
    int total = 0;

    for(int j=0; j<c; ++j)
    {
	for (int i=0; i<=(r-4); ++i)
	{
	    int human=0, pc=0;
	    for(int k=i; k<(i+4); ++k) 
	    {
		switch(board[j].getCell(k))
		{
		    case 1:
			human++; break;
		    case 2:
			pc++; break;
		    default:
		        break;
		}
	    }

	    total += segmentPoints(human,pc);
	}
    }
    
    return total;
}

int State::evalDiagonals() const
{
    int total = 0;
    
    // top-left to top-right
    for(int j=0; j<=(c-4); ++j)
	total += runEvalDiagonal(0,j,1,1);

    // top-left to bottom-left
    for(int i=1; i<=(r-4); ++i)
	total += runEvalDiagonal(i,0,1,1);

    // bottom-left to top-left
    for(int i=r-1; i>=3; --i)
	total += runEvalDiagonal(i,0,-1,1);
    
    // bottom-left to bottom-right
    for(int j=1; j<=(c-4); ++j)
	total += runEvalDiagonal(r-1,j,-1,1);
    
    return total;
}

int State::runEvalDiagonal(int x, int y, int dirX, int dirY) const
{
    int total = 0;
    int startx = x;
    int starty = y;

    while( ((dirX==1 && x<=(r-4)) || (dirX==-1 && x>=3)) && y<=(c-4) )
    {	
	int human=0, pc=0;
	for (int i=0; i<4; i++)
       	{
	    int normX = (r-1)-x;
	    switch(board[y].getCell(normX))
	    {
	        case 1:  human++; break;
	        case 2:  pc++; break;
	        default: break;
	    }
	    
	    x+=dirX;
	    y+=dirY;
	}
	
	total += segmentPoints(human,pc);
	      
	startx += dirX; x = startx;
	starty += dirY; y = starty;
    }

    return total;
}

int State::checkRows() const
{
    for(int i=0; i<r; ++i)
    {
	int human=0, pc=0;
	for(int j=0; j<c; ++j)
	{
	    switch(board[j].getCell(i))
	    {
	        case 1:  human++; pc=0; break;
	        case 2:  human=0; pc++; break;
	        default: human=0; pc=0;
	    }

	    if (human == 4) return -512;
	    if (pc == 4)    return 512;
	}
    }
    
    return 0;
}

int State::checkColumns() const
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

	    if (human == 4) return -512;
	    if (pc == 4)    return  512;
	}
    }

    return 0;
}

int State::checkDiagonals() const
{
    int value;
    
    // top-left to top-right
    for(int j=0; j<=(c-4); ++j)
	if( (value = runDiagonal(0,j,1,1)) != 0 )
	    return value;
    
    // top-left to bottom-left
    for(int i=1; i<r && i<=(r-4); ++i)
	if( (value = runDiagonal(i,0,1,1)) != 0 )
	    return value;

    // bottom-left to top-left
    for(int i=r-1; i>=3; --i)
	if( (value = runDiagonal(i,0,-1,1)) != 0 )
	    return value;
    
    // bottom-left to bottom-right
    for(int j=1; j<=(c-4); ++j)
	if( (value = runDiagonal(r-1,j,-1,1)) != 0 )
	    return value;
    
    return 0;
}

int State::runDiagonal(int x, int y, int dirX, int dirY) const
{
    int human=0, pc=0;
    while(x>=0 && x<r && y>=0 && y<c)
    {
	int normX = (r-1)-x;
	switch(board[y].getCell(normX))
	{
	    case 1:  human++; pc=0; break;
	    case 2:  human=0; pc++; break;
	    default: human=0; pc=0;
	}

	if (human == 4) return -512;
	if (pc == 4)    return 512;

	x+=dirX;
	y+=dirY;
    }

    return 0;
}

int State::segmentPoints(int humanCount, int pcCount) const
{
    if ( (humanCount == 0 && pcCount != 0) || (humanCount != 0 && pcCount == 0) ) {
	int sign = (humanCount == 0) ? 1 : -1;

	if (humanCount == 3 || pcCount == 3)
	    return 50*sign;
	else if (humanCount == 2 || pcCount == 2)
	    return 10*sign;
	else if (humanCount == 1 || pcCount == 1)
	    return  1*sign;
    }

    return 0;
}

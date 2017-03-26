#include <iostream>
#include <algorithm>
#include "headers/State.h"

State::State(int nRows, int nCols, int move)
    : r(nRows),
      c(nCols),
      board(new Column[c]),
      move(move),
      utility(0)
{
    for(int i=0; i<c; ++i)
	board[i].init(r);
}

State::State(const State& s)
    : r(s.r),
      c(s.c),
      board(new Column[c]),
      move(s.move),
      utility(0)
{
    for(int i=0; i<c; ++i)
	board[i] = s.board[i];
}

State& State::operator=(const State& s)
{
    r = s.r;
    c = s.c;
    move = s.move;
    utility = s.utility;
    
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
    eval();
    return true;
}

vector<State*> State::makeDescendants(int player) const
{
    vector<State*> descendants;

    for(int i=0; i<c; ++i)
    {
	State *s = new State(*this);
	bool changed = false;
	
	if(s->play(player,i))
	{
	    s->setMove(i);
	    changed = true;
	}

	if(changed)
	    descendants.push_back(s);
    }

    sort(descendants.begin(), descendants.end(), CompareUtility(player==2));
    return descendants;
}
  
void State::eval()
{
    int rows = evalRows();
    if(rows == -512 || rows == 512)
    {
	utility = rows;
	return;
    }
    
    int cols = evalColumns();
    if(cols == -512 || cols == 512)
    {
	utility = cols;
	return;
    }
    
    int diagonals = evalDiagonals();
    if(diagonals == -512 || diagonals == 512)
    {
	utility = diagonals;
	return;
    }
    
    int bonus = 16;
    utility = rows + cols + diagonals + bonus;
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

bool State::isFull() const
{
    for(int i=0; i<c; ++i)
	if(!board[i].isFull())
	    return false;

    return true;
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
	    
	    int points = segmentPoints(human,pc);
	    if(points == -512 || points == 512)
		return points;
	    
	    total += points;
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

	    int points = segmentPoints(human,pc);
	    if(points == -512 || points == 512)
		return points;

	    total += points;
	}
    }
    
    return total;
}

int State::evalDiagonals() const
{
    int total = 0;
    
    // top-left to top-right
    for(int j=0; j<=(c-4); ++j)
    {
	int points = runEvalDiagonal(0,j,1,1);
	if(points == -512 || points == 512)
	    return points;

	total += points;
    }
    
    // top-left to bottom-left
    for(int i=1; i<=(r-4); ++i)
    {
	int points = runEvalDiagonal(i,0,1,1);
	if(points == -512 || points == 512)
	    return points;

	total += points;
    }
    
    // bottom-left to top-left
    for(int i=r-1; i>=3; --i)
    {
	int points = runEvalDiagonal(i,0,-1,1);
	if(points == -512 || points == 512)
	    return points;
	
	total += points;
    }
    
    // bottom-left to bottom-right
    for(int j=1; j<=(c-4); ++j)
    {
	int points = runEvalDiagonal(r-1,j,-1,1);
	if(points == -512 || points == 512)
	    return points;
	
	total += points;
    }
    
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

	int points = segmentPoints(human,pc);
	if(points == -512 || points == 512)
	    return points;

	total += points;
	      
	startx += dirX; x = startx;
	starty += dirY; y = starty;
    }

    return total;
}

int State::segmentPoints(int humanCount, int pcCount) const
{
    if(humanCount != 0 && pcCount != 0)
	return 0;
    
    int sign = (humanCount == 0) ? 1 : -1;

    if(humanCount == 4 || pcCount == 4)
	return 512*sign;
    else if (humanCount == 3 || pcCount == 3)
	return  50*sign;
    else if (humanCount == 2 || pcCount == 2)
	return  10*sign;
    else if (humanCount == 1 || pcCount == 1)
	return   1*sign;
    else
	return 0;
}

int State::getUtility() const
{
    return utility;
}

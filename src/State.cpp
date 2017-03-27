#include "headers/State.h"

// default constructor
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

// copy constructor
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

// equality support
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

// destructor
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
    eval(); // assign new evaluation
    return true;
}

// sucessor function.
// the sucessor list is sorted for MAX and MIN
// in order to provide the best check order for
// the alpha-beta algorithm
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

    sort(descendants.begin(), descendants.end(), CompareUtility(player==BOT));
    return descendants;
}

// utility + evaluation combined function
void State::eval()
{
    utility = 0;

    for(int i=r-1; i>=0; --i)
	for(int j=0; j<c; ++j)
	{
	    // row
	    if( j<=(c-4) && testPoints(runEval(i,j,0,1)) )
		return;

	    // column
	    if( i<=(r-4) && testPoints(runEval(i,j,1,0)) )
		return;

	    if(j<=(c-4))
	    {
		// diagonal south-east
		if( i<=(r-4) && testPoints(runEval(i,j,1,1)) )
		    return;
	    
		// diagonal north-east
		if( i>=3 && testPoints(runEval(i,j,-1,1)) )
		    return;
	    }
	}

    utility += BONUS;
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

int State::runEval(int x, int y, int dirX, int dirY) const
{
    int human=0, bot=0;
    for (int i=0; i<4; i++)
    {
	switch(board[y].getCell(x))
	{
	    case HUMAN:
		human++; break;
	    case BOT:
		bot++; break;
	    default:
		break;
	}

	x += dirX;
	y += dirY;
    }

    return segmentPoints(human,bot);
}

int State::segmentPoints(int humanCount, int pcCount) const
{
    if(humanCount != 0 && pcCount != 0)
	return 0;
    
    int sign = (humanCount == 0) ? 1 : -1;

    if(humanCount == 4 || pcCount == 4)
	return MAX_UTILITY*sign;
    else if (humanCount == 3 || pcCount == 3)
	return COUNT_3_POINTS*sign;
    else if (humanCount == 2 || pcCount == 2)
	return COUNT_2_POINTS*sign;
    else if (humanCount == 1 || pcCount == 1)
	return COUNT_1_POINTS*sign;
    else
	return 0;
}

bool State::testPoints(int points)
{
    if(points == MIN_UTILITY || points == MAX_UTILITY)
    {
	utility = points;
	return true;
    }

    utility += points;
    return false;
}

int State::getUtility() const
{
    return utility;
}

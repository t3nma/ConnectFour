#include "headers/ConnectFour.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

ConnectFour::ConnectFour()
    : state(nullptr),
      bot(nullptr)
{
    srand(time(NULL));
}

ConnectFour::~ConnectFour()
{
    if(state != nullptr)
	delete state;
    
    if(bot != nullptr)
	delete bot;
}

void ConnectFour::init()
{
    int nRows;
    cout << "Number of Rows: ";
    cin >> nRows;

    int nCols;
    cout << "Number of Columns: ";
    cin >> nCols;

    int algoOP;
    cout << "Algorithm: (1-Minmax) (2-Alpha Beta) ";
    cin >> algoOP;

    int playerOP;
    cout << "First player: (1-Player) (2-AI) ";
    cin >> playerOP;
    
    state = new State(nRows,nCols);
    bot = new AI(((algoOP == 1) ? true : false), 8);
    curPlayer = playerOP;

    cout << endl;
}

void ConnectFour::start()
{
    cout << "Initial State:";
    state->print();
    
    int points = state->eval(0);
    while( points != 512 && points != -512 && !state->isFull() )
    {
	if(curPlayer == 1)
	    humanTurn();
	else
	    botTurn();

	state->print();
	points = state->eval(0);
    }

    if(points == -512 || points == 512)
	cout << ( (points > 0) ? "AI" : "You" ) << " WON!" << endl;
    else
    	cout << "It's a DRAW!" << endl;
}

void ConnectFour::humanTurn()
{
    cout << "Your turn." << endl;

    cout << "Column: ";
    int col; cin >> col;

    while( !state->play(curPlayer,col) )
    {
	cout << "Invalid play! Column: ";
	cin >> col;
    }

    curPlayer = 2;
}

void ConnectFour::botTurn()
{
    cout << "AI turn..." << endl;
    state->play(curPlayer, bot->play(state));
    curPlayer = 1;
}

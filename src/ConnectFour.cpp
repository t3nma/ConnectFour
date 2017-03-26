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
    cout << "Algorithm: (" << MINIMAX << "-Minimax) (" << ALFA_BETA << "-Alfa-Beta) ";
    cin >> algoOP;

    int playerOP;
    cout << "First player: (" << HUMAN << "-Player) (" << BOT << "-AI) ";
    cin >> playerOP;
    
    state = new State(nRows,nCols);
    bot = new AI((algoOP==MINIMAX), SETTINGS_DEPTH_LIMIT);
    curPlayer = playerOP;

    cout << endl;
}

void ConnectFour::start()
{
    cout << "Initial State:";
    state->print();

    int points = state->getUtility();
    while( points != MIN_UTILITY && points != MAX_UTILITY && !state->isFull() )
    {
	if(curPlayer == HUMAN)
	    humanTurn();
	else
	    botTurn();

	state->print();
	points = state->getUtility();
    }

    if(points == MIN_UTILITY || points == MAX_UTILITY)
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

    curPlayer = BOT;
}

void ConnectFour::botTurn()
{
    cout << "AI turn..." << endl;
    state->play(curPlayer, bot->play(state));
    curPlayer = HUMAN;
}

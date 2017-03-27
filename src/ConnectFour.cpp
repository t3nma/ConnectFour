#include "headers/ConnectFour.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// default constructor
ConnectFour::ConnectFour()
    : state(nullptr),
      bot(nullptr)
{
    srand(time(NULL));
}

// destructor
ConnectFour::~ConnectFour()
{
    if(state != nullptr)
	delete state;
    
    if(bot != nullptr)
	delete bot;
}

// prompt user for the game configuration
// and initialize the required data-members
void ConnectFour::init()
{
    int nRows;
    cout << "Number of Rows: ";
    cin >> nRows;

    while(nRows <= 0)
    {
	cout << "Invalid size!" << endl << "Number of Rows: ";
	cin >> nRows;
    }

    bool anyColSize = (nRows >= 4);

    int nCols;
    cout << "Number of Columns" << (anyColSize ? " : " : " (min 4): ");
    cin >> nCols;

    while( (anyColSize && nCols <= 0) || (!anyColSize && nCols < 4) )
    {
	cout << "Invalid size!" << endl << "Number of Columns" << (anyColSize ? ": " : "(min 4): ");
	cin >> nCols;
    }

    int algoOP;
    cout << "Algorithm: (" << MINIMAX << " - Minimax) (" << ALFA_BETA << " - Alfa-Beta) ";
    cin >> algoOP;

    while(algoOP != MINIMAX && algoOP != ALFA_BETA)
    {
	cout << "Invalid Algorithm!" << endl;

	cout << "Algorithm: (" << MINIMAX << " - Minimax) (" << ALFA_BETA << " - Alfa-Beta) ";
	cin >> algoOP;
    }	

    int playerOP;
    cout << "First player: (" << HUMAN << " - Player) (" << BOT << " - AI) ";
    cin >> playerOP;

    while(playerOP != HUMAN && playerOP != BOT)
    {
	cout << "Invalid First player!" << endl;
	
	cout << "First player: (" << HUMAN << " - Player) (" << BOT << " - AI) ";
	cin >> playerOP;
    }

    // initialize game with user prompt
    state = new State(nRows,nCols);
    bot = new AI((algoOP==MINIMAX), SETTINGS_DEPTH_LIMIT);
    curPlayer = playerOP;

    cout << endl;
}

// game life-cycle
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
    cout << "AI's turn..." << endl;
    state->play(curPlayer, bot->play(state));
    curPlayer = HUMAN;
}

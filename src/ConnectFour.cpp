#include "headers/ConnectFour.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

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
    cout << "Rows: ";
    cin >> nRows;

    int nCols;
    cout << "Columns: ";
    cin >> nCols;

    int depth = 12;
    cout << "Depth Bound: (default = 12)";
    cin >> depth;
    
    state = new State(nRows,nCols);
    bot = new AI(depth);
    curPlayer = 1; // human
}

void ConnectFour::start()
{
    state->print();
    cout << endl;

    while(!state->isTerminal())
    {
	if(curPlayer == 1)
	    humanTurn();
	else
	    AITurn();

	state->print();
	cout << endl;
    }

    cout << "GAME ENDED!" << endl;
}

void ConnectFour::humanTurn()
{
    cout << "Your turn." << endl;

    int col;
    cout << "Column: "; cin >> col;
    while( !state->play(curPlayer, col) )
    {
	cout << "Invalid play...\nColumn: ";
	cin >> col;
    }

    curPlayer = 2;
}

void ConnectFour::AITurn(bool minmax)
{
    cout << "AI turn." << endl;

    int col;
    cout << "Column: "; cin >> col;
    while( !state->play(curPlayer, col) )
    {
	cout << "Invalid play...\nColumn: ";
	cin >> col;
    }
    
    curPlayer = 1;
}

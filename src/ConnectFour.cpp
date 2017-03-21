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

    int op;
    cout << "Algorithm: (1-Minmax) (2-Alpha Beta) ";
    cin >> op;
    
    state = new State(nRows,nCols);
    bot = new AI(op,12);
    curPlayer = 1 + rand()%2; // random start player
}

void ConnectFour::start()
{
    state->print();

    while(state->isTerminal() == 0)
    {
	if(curPlayer == 1)
	    humanTurn();
	else
	    botTurn();

	state->print();
    }

    cout << "GAME ENDED!" << endl;
}

void ConnectFour::humanTurn()
{
    cout << "Your turn." << endl;

    cout << "Column: ";
    int col; cin >> col;

    while( !state->play(curPlayer,col) )
    {
	cout << "Invalid play! Again: ";
	cin >> col;
    }

    curPlayer = 2;
}

void ConnectFour::botTurn()
{
    cout << "AI turn." << endl;
    state->play(curPlayer, bot->play(state));
    curPlayer = 1;
}

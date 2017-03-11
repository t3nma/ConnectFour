#include "headers/State.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    State s(4,5);

    cout << "Initial State:" << endl;
    s.print();

    cout << endl << "Descendants:" << endl;
    vector<State*> descendants = s.makeDescendants(1);
    for(auto it=descendants.begin(); it!=descendants.end(); ++it)
    {
	cout << endl; (*it)->print(); cout << endl;
	delete (*it);
    }

    /*
    int r,c;
    cout << "Rows: "; cin >> r;
    cout << "Cols: "; cin >> c;

    int **board = new int*[r];
    cout << "Board:" << endl;
    for(int i=0; i<r; ++i)
    {
	board[i] = new int[c];
	for(int j=0; j<c; ++j)
	    cin >> board[i][j];
    }
	    
    State s(board,r,c);
    cout << endl << "Initial State:" << endl;
    s.print();

    for(int i=0; i<r; ++i)
	delete [] board[i];
    delete [] board;

    cout << endl << "Descendants:" << endl;
    vector<State*> descendants = s.makeDescendants(1);
    for(auto it=descendants.begin(); it!=descendants.end(); ++it)
    {
	cout << endl; (*it)->print(); cout << endl;
	delete (*it);
    }
    */

    return 0;
}

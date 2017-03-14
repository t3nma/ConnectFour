#ifndef STATE_H
#define STATE_H

#include <vector>
#include "Column.h"

using namespace std;

class State
{
public:
    State(int nRows, int nCols);
    State(const State& s);
    State& operator=(const State& s);
    ~State();

    bool play(int player, int column);
    vector<State*> makeDescendants(int player) const;
    bool isTerminal() const;
    void print() const;
    
private:
    int r;
    int c;
    Column *board;

    bool hasWinner() const;
    bool isFull() const;
    bool checkRows() const;
    bool checkColumns() const;
    bool checkDiagonals() const;
    bool runDiagonal(int x, int y, int dirX, int dirY) const;
};

#endif

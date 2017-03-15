#ifndef STATE_H
#define STATE_H

#include <vector>
#include "Column.h"

using namespace std;

class State
{
public:
    State(int nRows, int nCols, int move=-1);
    State(const State& s);
    State& operator=(const State& s);
    ~State();

    int getMove() const;
    void setMove(int move);
    
    bool play(int player, int column);
    vector<State*> makeDescendants(int player) const;
    int isTerminal() const;
    int eval() const;
    void print() const;
    
    // TODO << SUPPORT
    
private:
    int r;
    int c;
    Column *board;
    int move;
    
    int hasWinner() const;
    int isFull() const;
    int checkRows() const;
    int checkColumns() const;
    int checkDiagonals() const;
    int runDiagonal(int x, int y, int dirX, int dirY) const;
};

#endif

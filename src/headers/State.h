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
    bool isFull() const;
    int eval(int depth) const;
    void print() const;
    
    // TODO << SUPPORT
    
private:
    int r;
    int c;
    Column *board;
    int move;
    
    int evalRows(int depth) const;
    int evalColumns(int depth) const;
    int evalDiagonals(int depth) const;
    int runEvalDiagonal(int x, int y, int dirX, int dirY, int depth) const;
    int segmentPoints(int humanCount, int pcCount, int depth) const;
};

#endif

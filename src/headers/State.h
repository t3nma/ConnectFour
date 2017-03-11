#ifndef STATE_H
#define STATE_H

#include <vector>
#include "Column.h"

using namespace std;

class State
{
public:

    State(int nRows, int nCols);
    State(int **board, int nRows, int nCols);
    State(const State& s);
    State& operator=(const State& s);
    ~State();

    vector<State*> makeDescendants(int player) const;
    bool isFinal() const;
    void print() const;
    
private:
    int r;
    int c;
    Column *board;
};

#endif

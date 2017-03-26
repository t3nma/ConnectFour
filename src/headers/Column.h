#ifndef COLUMN_H
#define COLUMN_H

#include "Globals.h"

class Column
{
public:

    Column();
    void init(int r);
    Column(const Column& c);
    Column& operator=(const Column& c);
    ~Column();

    bool isFull() const;
    void placeCell(int player);
    int getCell(int row) const;
    
private:
    int r;
    int *cells;
    int top;
};

#endif

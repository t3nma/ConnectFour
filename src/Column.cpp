#include "headers/Column.h"
#include <iostream>

Column::Column()
    : cells(nullptr)
{
}

void Column::init(int r)
{
    this->r = r;
    top = 0;
    cells = new int[r];
}

Column::Column(const Column& c)
    : r(c.r),
      top(c.top)
{
    cells = new int[r];
    for(int i=0; i<top; ++i)
	cells[i] = c.cells[i];
}

Column& Column::operator=(const Column& c)
{
    if(cells != nullptr)
	delete [] cells;
    
    init(c.r);
    top = c.top;

    for(int i=0; i<r; ++i)
	cells[i] = c.cells[i];

    return *this;
}

Column::~Column()
{
    delete [] cells;
}

bool Column::isFull() const
{
    return top == r;
}

void Column::placeCell(int player)
{
    cells[top] = player;
    if(player != 0)
	top++;
}

int Column::getCell(int row) const
{
    return cells[row];
}

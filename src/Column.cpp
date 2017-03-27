#include "headers/Column.h"
#include <iostream>

// default constructor
Column::Column()
    : cells(nullptr)
{
}

// initialize column with r cells
void Column::init(int r)
{
    this->r = r;
    top = 0;
    cells = new int[r];
}

// copy constructor
Column::Column(const Column& c)
    : r(c.r),
      top(c.top)
{
    cells = new int[r];
    for(int i=0; i<top; ++i)
	cells[i] = c.cells[i];
}

// equality support
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

// destructor
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
    if(player != BLANK)
	top++;
}

int Column::getCell(int row) const
{
    return cells[row];
}

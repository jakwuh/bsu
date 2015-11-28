#include "map.h"    

Cell::Cell()
{
    up = bottom = left = right = 0;
}

void Cell::setColor(COLORREF _color)
{
    color = _color;
}

COLORREF Cell::getColor()
{
    return color;
}
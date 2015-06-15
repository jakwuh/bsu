/**
* @author James
* @version 0.0.1
* @date 24.03.2015
*/

#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

#include <Windows.h>

#include "..\core\town.h"

class Cell
{
private:
    Town *up, *bottom, *left, *right;
    COLORREF color;
public:
    Cell();
    ~Cell();
    void setColor(COLORREF);
    COLORREF getColor();
};


class Map
{
private:
public:
    Map();
    ~Map();
};



#endif
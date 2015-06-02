#ifndef __GENERATOR_H_INCLUDED__
#define __GENERATOR_H_INCLUDED__

#include "ctime"
#include <stdlib.h>
#include <iostream>
#include <list>
#include "stack.h"

struct Point{
	Point(){};
	Point(int _i, int _j) : i(_i), j(_j){};
	int i, j;
};

bool checkExit(bool **, int, int);
void generateMaze(bool**, int, int);

#endif
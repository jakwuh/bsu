// Шаблонный стек на массиве
// Очередь Records с перегруженными операциями ввода-вывода << >> + += [] и конструктором копирования	
// Сортировка очереди Records слиянием с помощью шаблонного стека
// Генерация лабиринта при помощи шаблонного стека на массивах

#ifndef __CONTROLLER_H_INCLUDED__
#define __CONTROLLER_H_INCLUDED__

#define PWidth 9
#define PHeight 9

#include <Windows.h>
#include <fstream>
#include <ctime>
#include "generator.h"
#include "records.h"

enum Direction {d_up, d_right, d_down, d_left};

class Controller
{
private:
	HWND console;
	HDC dc;
	Records rs;
	time_t start;
	bool ** M;
	int n, m, meX, meY, exitX, exitY;
	char* name;
public:
	static COLORREF cl_black, cl_grey, cl_blue, cl_border, cl_red, cl_white;
	Controller();
	~Controller();
	void setName(char*);
	void initialize();
	void paint();
	void paint(int, int, COLORREF);
	void moveMe(Direction);
	void repaintMe(int, int);
	void paintRecords();
	void reset();
};

#endif
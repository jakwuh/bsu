#include "timer.h"

Timer::Timer(HINSTANCE hI_, UI* ui) : UI(NULL, NULL)
{
	parent = ui;
	id = parent ? parent->getUniqueId() : rand();
	hI = hI_;

	if (!handler) throw WindowCreateException();
	registerWindow();
};

Timer::~Timer()
{
	KillTimer(*parent, id);
}

void Timer::begin(int n)
{
	SetTimer(*parent, id, n, NULL);
}

void Timer::registerWindow()
{
}


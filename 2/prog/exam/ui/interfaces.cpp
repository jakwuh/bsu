#include "interfaces.h"

int DefaultDrawableStrategy::operator () (
	unsigned parent_size, unsigned client_size, int margin)
{
	return int(margin);
}

int CenterDrawableStrategy::operator () (
	unsigned parent_size, unsigned client_size, int margin)
{
	return int(parent_size - client_size) / 2;
}

int LeftDrawableStrategy::operator () (
	unsigned parent_size, unsigned client_size, int margin)
{
	return 0;
}

int RightDrawableStrategy::operator () (
	unsigned parent_size, unsigned client_size, int margin)
{
	return int(parent_size - client_size);
}
#include "circle.h"

using namespace graphics;

Circle::Circle(int _px_x, int _px_y, int _r)
    : px_x(_px_x), px_y(_px_y), r(_r){};

void Circle::draw()
{
    assert(false);
}

void Circle::draw(HDC& hdc, int xd, int yd)
{
	Ellipse(hdc, xd + px_x - r, yd + px_y - r, xd + px_x + r, yd + px_y + r);
}

void Circle::move(int dx, int dy)
{
    px_x += dx;
    px_y += dy;
}
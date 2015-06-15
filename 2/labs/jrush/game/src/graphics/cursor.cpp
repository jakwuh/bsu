#include "cursor.h"

using namespace graphics;

Cursor::Cursor(int _px_x, int _px_y, int _r)
    : Circle(_px_x, _px_y, _r){};

void Cursor::move(int x, int y)
{
    if (px_x != x || px_y != y)
    {
        int rr = std::sqr(px_x - x) + std::sqr(px_y - y);
        if (rr < std::sqr(::config::cursor_speed)) {
            px_x = x;
            px_y = y;
        } else {
            px_x += (int) ( (x - px_x) / std::sqrt(rr) * ::config::cursor_speed );
            px_y += (int) ( (y - px_y) / std::sqrt(rr) * ::config::cursor_speed );
        }
    }
}

void Cursor::draw(HDC& hdc, int xd, int yd, int _r)
{
    r = _r;
    SetBkMode(hdc, TRANSPARENT);
    SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
    Ellipse(hdc, xd + px_x - r, yd + px_y - r, xd + px_x + r, yd + px_y + r);
}

int Cursor::getX()
{
    return px_x;
}

int Cursor::getY()
{
    return px_y;
}
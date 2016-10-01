/**
* @author James
* @version 0.0.1
* @date 24.03.2015
*/

#ifndef __CIRCLE_H_INCLUDED__
#define __CIRCLE_H_INCLUDED__

#include <Windows.h>
#include <cmath>
#include <assert.h>
#include "../config/errors.h"
#include "../core/interfaces.h"

namespace graphics
{

    class Circle : public ::IDrawable, public IMovable
    {
    protected:
        int r, px_x, px_y;
    public:
        Circle(int, int, int);
        void draw();
        void draw(HDC&, int, int);
        void move(int, int);
    };

}

#endif
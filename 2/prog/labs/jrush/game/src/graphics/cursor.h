/**
* @author James
* @version 0.0.1
* @date 25.03.2015
*/

#ifndef __CURSOR_H_INCLUDED__
#define __CURSOR_H_INCLUDED__

#include <algorithm>
#include <cmath>

#include "../graphics/circle.h"
#include "../config/config.h"
#include "../utils/math.h"
#include "../utils/styles.h"

namespace graphics{

	class Cursor : public Circle
	{
	public:
		Cursor(int, int, int);
		void move(int, int);
        void draw(HDC&, int, int, int);
        int getX();
        int getY();
	};

}


#endif
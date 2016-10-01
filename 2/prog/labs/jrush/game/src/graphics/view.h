/**
* @author James
* @version 0.0.1
* @date 24.03.2015
*/

#ifndef __VIEW_H_INCLUDED__
#define __VIEW_H_INCLUDED__

#include <algorithm>
#include <assert.h>
#include <Windows.h>
#include <string>

#include "../core/interfaces.h"
#include "../core/town.h"
#include "../config/config.h"
#include "../controllers/player.h"
#include "../utils/styles.h"

using namespace types;

class View : public IDrawable, public IMovable
{
private:
    friend class Application;

    HWND hwnd;
    HBITMAP bitmap;
    HDC hdc, hdc_mem;
    HRGN region;
    
    int xd, yd, xs, ys, w, h, max_xs, max_ys;
    int width, height, bitmap_width, bitmap_height;
	Position position;

    Player* player;
    Towns towns;

public:
    View(HWND, LPTSTR, Position);
    ~View();
    void setPlayer(Player*);
    void setTowns(Towns);
    void draw();
    void move(int, int);
    void resize();
};


#endif
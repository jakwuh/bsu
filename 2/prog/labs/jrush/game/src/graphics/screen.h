#ifndef __SCREEN_H_INCLUDED__
#define __SCREEN_H_INCLUDED__

#include <map>
#include <string>
#include <Windows.h>
#include <commctrl.h>
#include "../utils/styles.h"
#include "../core/interfaces.h"
#include "../config/config.h"

class Screen : public IDrawable
{
private:
    HWND* hwnd_ptr;
public:
    HWND hwnd1, hwnd2;
    static LPCSTR screen_classname;
    Screen(HWND*, HINSTANCE);
    void draw(){};
    void resize();
    ~Screen();
};


#endif
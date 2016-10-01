#ifndef __SETTINGS_H_INCLUDED__
#define __SETTINGS_H_INCLUDED__

#define BTN_OK 11
#define TRACKBAR_LEVEL 12
#define TRACKBAR_FPS 14

#include <map>
#include <string>
#include <Windows.h>
#include <commctrl.h>
#include "../utils/styles.h"
#include "../core/interfaces.h"
#include "../config/config.h"

class Settings : public IDrawable
{
private:
    HWND* hwnd_ptr;
    UI elements;    
public:
    Settings(HWND*);
    void draw();
    void resize(){};
    ~Settings();
};


#endif
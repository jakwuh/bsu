#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#define BTN_PLAY 1
#define BTN_SETTINGS 2
#define BTN_EXIT 3

#include <map>
#include <string>
#include <Windows.h>
#include "../utils/styles.h"
#include "../core/interfaces.h"

class Menu : public IDrawable
{
private:
    HWND* hwnd_ptr;
    UI elements;
public:
    Menu(HWND*);
    void draw();
    void resize(){};
    ~Menu();
};


#endif
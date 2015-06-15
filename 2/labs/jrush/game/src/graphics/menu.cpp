#include "menu.h"

Menu::Menu(HWND* _hwnd_ptr) : hwnd_ptr(_hwnd_ptr)
{
    elements["BTN_PLAY"] = CreateWindow("BUTTON", "Начать!", 
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        0, 0, 0, 0, *hwnd_ptr, (HMENU)BTN_PLAY, 
        NULL, NULL);

    elements["BTN_SETTINGS"] = CreateWindow("BUTTON", "Настройки", 
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        0, 0, 0, 0, *hwnd_ptr, (HMENU)BTN_SETTINGS, 
        NULL, NULL);

    elements["BTN_EXIT"] = CreateWindow("BUTTON", "Выход", 
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        0, 0, 0, 0, *hwnd_ptr, (HMENU)BTN_EXIT, 
        NULL, NULL);

    SendMessage(elements["BTN_PLAY"], WM_SETFONT, 
        (WPARAM)::fonts::button_text, MAKELPARAM(TRUE, 0));

    SendMessage(elements["BTN_SETTINGS"], WM_SETFONT, 
        (WPARAM)::fonts::button_text, MAKELPARAM(TRUE, 0));

    SendMessage(elements["BTN_EXIT"], WM_SETFONT, 
        (WPARAM)::fonts::button_text, MAKELPARAM(TRUE, 0));
}

void Menu::draw()
{
    RECT rect;
    HDC dc = GetDC(*hwnd_ptr);
    GetClientRect(*hwnd_ptr, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // begin BACKGROUND
    GetClientRect(*hwnd_ptr, &rect);
    FillRect(dc, &rect, ::brushes::map[::colors::menu_background]);
    // end BACKGROUND

    // begin TITLE
    SetBkMode(dc, TRANSPARENT);
    SelectObject(dc, ::fonts::title_text);
    SetRect(&rect, 0, 0, width, height);
    SetTextColor(dc, ::colors::title_color);
    DrawText(dc, TEXT("JRUSH V 1.0"), -1, &rect, DT_CENTER | DT_SINGLELINE);
    // end TITLE
    
    // begin BTN_*
    int btn_count = elements.size();
    int free_height = height - 100;
    int btn_width = width / 2;
    int btn_height = 2 * free_height / (3 * btn_count + 1);

    int d_y = free_height / (3 * btn_count + 1);
    int button_y = 100;
    int button_x = width / 2 - btn_width / 2;

    SetWindowPos(elements["BTN_PLAY"], HWND_BOTTOM, 
        button_x, button_y + d_y * 1 + btn_height * 0, btn_width, btn_height, 
        SWP_NOZORDER | SWP_NOACTIVATE);

    SetWindowPos(elements["BTN_SETTINGS"], HWND_BOTTOM, 
        button_x, button_y + d_y * 2 + btn_height * 1, btn_width, btn_height, 
        SWP_NOZORDER | SWP_NOACTIVATE);

    SetWindowPos(elements["BTN_EXIT"], HWND_BOTTOM, 
        button_x, button_y + d_y * 3 + btn_height * 2, btn_width, btn_height, 
        SWP_NOZORDER | SWP_NOACTIVATE);
    // end BTN_*

    ReleaseDC(*hwnd_ptr, dc);
}

Menu::~Menu()
{
    for (UI::iterator it = elements.begin(); it != elements.end(); ++it) {
        DestroyWindow(it->second);
    }
}
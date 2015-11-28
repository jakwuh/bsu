#include "screen.h"

LPCSTR Screen::screen_classname = "JSCREEN";

Screen::Screen(HWND* _hwnd_ptr, HINSTANCE _h_instance) : hwnd_ptr(_hwnd_ptr)
{
   hwnd1 = CreateWindowEx(WS_EX_NOACTIVATE, screen_classname,
        "SCREEN", WS_BORDER, 0, 0, 0, 0,
        *hwnd_ptr, NULL, _h_instance, NULL);
   hwnd2 = CreateWindowEx(WS_EX_NOACTIVATE, screen_classname,
        "SCREEN", WS_BORDER, 0, 0, 0, 0,
        *hwnd_ptr, NULL, _h_instance, NULL);

   ShowWindow(hwnd1, SW_SHOW);
   ShowWindow(hwnd2, SW_SHOW);

   resize();
}

void Screen::resize()
{
    RECT rect;
    HDC dc = GetDC(*hwnd_ptr);
    GetClientRect(*hwnd_ptr, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    SetWindowPos(hwnd1, HWND_TOP, 0, 0, width / 2, height, SWP_SHOWWINDOW);
    SetWindowPos(hwnd2, HWND_TOP, width / 2, 0, width / 2, height, SWP_SHOWWINDOW);
}

Screen::~Screen()
{
    DestroyWindow(hwnd1);
    DestroyWindow(hwnd2);
}
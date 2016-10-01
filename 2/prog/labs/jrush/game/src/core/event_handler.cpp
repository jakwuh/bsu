#include <Windows.h>
#include "../graphics/menu.h"
#include "../graphics/settings.h"

LRESULT WINAPI wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (!app) return DefWindowProc(hwnd, msg, wparam, lparam);

    int level, fps;
    switch (msg) {
    case WM_SIZE:
        app->resize();
        app->go(1);
        break;
    case WM_TIMER:
        app->go(wparam);
        break;
    case WM_PAINT:
        app->go(1);
        break;
    case WM_COMMAND:
        switch (LOWORD(wparam)) {
        
        case BTN_PLAY:
            app->play();
            break;
        case BTN_OK:
            level = SendMessage(GetDlgItem(hwnd, TRACKBAR_LEVEL), TBM_GETPOS, 0, 0);
            fps = SendMessage(GetDlgItem(hwnd, TRACKBAR_FPS), TBM_GETPOS, 0, 0);
			app->setSettings(level, fps);
            app->menu();
            break;
        case BTN_SETTINGS:
            app->settings();
            break;
        case BTN_EXIT:
            DestroyWindow(hwnd);
            return 0;
            break;
        }
        break;
    case WM_KEYDOWN:
        app->keyPress(wparam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}
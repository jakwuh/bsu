#include "settings.h"

Settings::Settings(HWND* _hwnd_ptr) : hwnd_ptr(_hwnd_ptr)
{
    elements["BTN_OK"] = CreateWindow("BUTTON", "Ñîõðàíèòü", 
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        0, 0, 0, 0, *hwnd_ptr, (HMENU)BTN_OK, 
        NULL, NULL);

    wchar_t str[] = L"sfdfdsfsd";

    elements["TRACKBAR_LEVEL"] =  CreateWindowW(L"msctls_trackbar32", 
        L"0", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
        0, 0, 0, 0, *hwnd_ptr, (HMENU)TRACKBAR_LEVEL, NULL, NULL);

    elements["TRACKBAR_FPS"] =  CreateWindowW(L"msctls_trackbar32", 
        L"0", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
        0, 0, 0, 0, *hwnd_ptr, (HMENU)TRACKBAR_FPS, NULL, NULL);

    SendMessage(elements["BTN_OK"], WM_SETFONT, 
        (WPARAM)::fonts::button_text, MAKELPARAM(TRUE, 0));

    draw();

    SendMessageW(elements["TRACKBAR_LEVEL"], TBM_SETRANGE,  TRUE, MAKELONG(0, ::config::levels_count - 1)); 
    SendMessageW(elements["TRACKBAR_LEVEL"], TBM_SETPAGESIZE, 0,  1); 
    SendMessageW(elements["TRACKBAR_LEVEL"], TBM_SETTICFREQ, 1, 0); 
    SendMessageW(elements["TRACKBAR_LEVEL"], TBM_SETPOS, FALSE, 0); 


    SendMessageW(elements["TRACKBAR_FPS"], TBM_SETRANGE,  TRUE, MAKELONG(1, 100)); 
    SendMessageW(elements["TRACKBAR_FPS"], TBM_SETPAGESIZE, 0,  1); 
    SendMessageW(elements["TRACKBAR_FPS"], TBM_SETTICFREQ, 5, 0); 
    SendMessageW(elements["TRACKBAR_FPS"], TBM_SETPOS, TRUE, 100); 

    draw();
}

void Settings::draw()
{
    RECT rect;
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(*hwnd_ptr, &ps);
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
    DrawText(dc, TEXT("GGGG V 1.0"), -1, &rect, DT_CENTER | DT_SINGLELINE);
    // end TITLE
    
    // begin BTN_*
    int btn_count = elements.size() + 2;
    int free_height = height - 100;
    int btn_width = width / 2;
    int btn_height = 2 * free_height / (3 * btn_count + 1);

    int d_y = free_height / (3 * btn_count + 1);
    int button_y = 100;
    int button_x = width / 2 - btn_width / 2;

    RECT tmp;
    SetBkMode(dc, TRANSPARENT);
    SelectObject(dc, ::fonts::button_text);
    SetTextColor(dc, ::colors::black);

    SetRect(&tmp, 0, button_y + d_y * 2 + btn_height * 0, width, button_y + d_y * 1 + btn_height * 1);
    DrawText(dc, TEXT("ÓÐÎÂÅÍÜ"), -1, &tmp, DT_CENTER | DT_VCENTER| DT_SINGLELINE);

    SetWindowPos(elements["TRACKBAR_LEVEL"], HWND_BOTTOM, 
        button_x, button_y + d_y * 2 + btn_height * 1, btn_width, btn_height, 
        SWP_NOZORDER | SWP_NOACTIVATE);

    SetRect(&tmp, 0, button_y + d_y * 4 + btn_height * 2, width, button_y + d_y * 3 + btn_height * 3);
    DrawText(dc, TEXT("ÑÊÎÐÎÑÒÜ ÏÐÎÐÈÑÎÂÊÈ"), -1, &tmp, DT_CENTER | DT_VCENTER| DT_SINGLELINE);

    SetWindowPos(elements["TRACKBAR_FPS"], HWND_BOTTOM, 
        button_x, button_y + d_y * 4 + btn_height * 3, btn_width, btn_height, 
        SWP_NOZORDER | SWP_NOACTIVATE);

    SetWindowPos(elements["BTN_OK"], HWND_BOTTOM, 
        button_x, button_y + d_y * 5 + btn_height * 4, btn_width, btn_height, 
        SWP_NOZORDER | SWP_NOACTIVATE);

    // end BTN_*
    EndPaint(*hwnd_ptr, &ps);
}

Settings::~Settings()
{
    for (UI::iterator it = elements.begin(); it != elements.end(); ++it) {
        DestroyWindow(it->second);
    }
}
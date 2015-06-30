#include "popup.h"

HWND Popup::handler = 0;
bool Popup::toBottom = true;
int Popup::height = 40;
int Popup::top = 0;
int Popup::wait = 0;

void Popup::show(HINSTANCE hI, HWND parent, std::string const& text)
{
	if (handler) DestroyWindow(handler);
	toBottom = true;
	top = -height;
	wait = 30;

	RECT r;
	GetWindowRect(parent, &r);
	handler = CreateWindow("STATIC", text.c_str(), 
        WS_CHILD | WS_VISIBLE | SS_CENTER | SS_SUNKEN, 
        0, top, r.right - r.left, height, parent, NULL, 
        hI, NULL);

	if (!handler) throw WindowCreateException();

	ShowWindow(handler, SW_SHOW);

	HDC hdc = GetDC(handler);
	SetBkMode(hdc,TRANSPARENT);
	SetBkColor(hdc, RGB(154, 22, 748));
	SetTextColor(hdc, RGB(145, 45, 77));
	SendMessage(handler, WM_SETFONT, (WPARAM)fonts::popup_text, MAKELPARAM(TRUE, 0));
	ReleaseDC(handler, hdc);
	SetTimer(handler, 1, 30, (TIMERPROC)Popup::move);
}

void CALLBACK Popup::move()
{
	RECT r;
	GetWindowRect(handler, &r);
	if (top >= 0) {
		toBottom = false;
	}
	else if (top < -height) {
		DestroyWindow(handler);
		KillTimer(handler, 1);
		return;
	}
	if (toBottom) top += 5;
	else if (wait-- > 0) return;
	else top -=5;
	SetWindowPos(handler, HWND_TOP, 0, top, r.right - r.left, height, SWP_NOZORDER | SWP_NOACTIVATE);
	SetTimer(handler, 1, 30, (TIMERPROC)Popup::move);
}
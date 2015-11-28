#include <Windows.h>
#include "functions.h"
#include <cstring>
#include <cstdio>

#define BUTTON_1 1
#define EDIT_1 2
#define TEXTBOX_1 3

char* str = new char[1000];
char* buffer = new char[1000];
int i;
float x;
static COLORREF black = RGB(0, 0, 0);
HPEN default_pen = CreatePen(PS_SOLID, 1, black);;

LRESULT WINAPI wndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hIPrev, LPSTR lpCmdLine, int nCmdShow)
{
	::x = 0;
	::i = 0;
	::str[0] = 0;
	::buffer[0] = 0;

	MSG msg;
	HWND hwnd;
	WNDCLASS w;
	memset(&w, 0, sizeof(WNDCLASS));
	w.style = CS_VREDRAW | CS_HREDRAW;
	w.lpfnWndProc = wndProc;
	w.cbClsExtra = w.cbWndExtra = 0;
	w.hbrBackground = (HBRUSH)(WHITE_BRUSH);
	w.lpszClassName = L"JMain";
	RegisterClass(&w);
	hwnd = CreateWindow(L"JMain", L"JTest", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 0, 0, 500, 200, NULL, NULL, hI, NULL);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}

	return msg.wParam;
}

LRESULT WINAPI wndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	RECT r;
	static HWND button1, edit1, textbox1;
	wchar_t* buf2 = new wchar_t[500];
	switch (message) {
	case WM_CREATE:
		edit1 = CreateWindow(L"EDIT", L"¬ведите число с нечетным количеством цифр( не 0! )", ES_LEFT | WS_BORDER | WS_VISIBLE | WS_CHILD, 0, 0, 400, 20, hwnd, (HMENU)EDIT_1, NULL, NULL);
		button1 = CreateWindow(L"BUTTON", L"BUTTON", BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD, 0, 20, 400, 50, hwnd, (HMENU)BUTTON_1, NULL, NULL);
		textbox1 = CreateWindow(L"STATIC", L"STATIC", SS_LEFT | SS_SUNKEN | WS_VISIBLE | WS_CHILD, 0, 70, 400, 50, hwnd, (HMENU)TEXTBOX_1, NULL, NULL);
		ShowWindow(button1, SW_SHOW);
		break;
	case WM_COMMAND:
		switch (LOWORD(wparam)) {
		case BUTTON_1:
			GetDlgItemText(hwnd, EDIT_1, (LPWSTR)buf2, 500);
			for (int i = 0; i <= wcslen(buf2); ++i){
				str[i] = (char)buf2[i];
			}

			copy_from_the_middle(::str, ::buffer);
			::i = mystoi(::buffer);
			::x = mysqrt(::i);
			
			GetClientRect(hwnd, &r);
			RedrawWindow(hwnd, &r, NULL, RDW_INTERNALPAINT);
			break;
		case EDIT_1:
			wchar_t* buf = new wchar_t[500];
			GetDlgItemText(hwnd, EDIT_1, (LPWSTR)buf, 500);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		
		sprintf_s(::str, 500, "String: %s\nInt: %d\nSqrt: %.2f\n", buffer, ::i, ::x);

		for (int i = 0; i <= strlen(::str); ++i)
			buf2[i] = (wchar_t)::str[i];

		SetDlgItemText(hwnd, TEXTBOX_1, buf2);

		break;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}
#include <windows.h>

LONG WINAPI wndProc(HWND, UINT, WPARAM, LPARAM);

// hpi - previous instance
// hi - current instance
int WINAPI WinMain(HINSTANCE hi, HINSTANCE hpI, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASS w; // WNDCLASS - структура
	HWND hwnd;
	MSG msg;
	memset(&w, 0, sizeof(WNDCLASS)); // memset(adress, fillChar, bytesCount) -fills block of memory with char
	w.style = CS_HREDRAW | CS_VREDRAW // HREDRAW - horizontal redraw, VREDRAW - vertical redraw
	w.lpfnWndProc = WndProc;// long pointer to window proc function
	w.hInstance = hi;
	w.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH) // HBRUSH - handle brush
	w.lpszClassName = MyClass;
	RegisterClass(&w);
	hwnd = CreateWindow(MyClass, "My window", WS_OVERLAPPEDWINDOW, 500, 300, 300, 400, NULL, NULL, hInstance, NULL); // WS - window style
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LONG WINAPI WndProc(hwnd, message, wparam, lparam) {
	PAINTSTRUCT ps;
	RECT r;
	switch(Message)	{
		case WM_DESTROY:
			PostQuit Message(0);
			break;
		case WM_PAINT:
			hdc = beginPaint(hwnd, &ps);
			GetClientRect(hwnd, &r);
			DrawText(hdc, "Hello", -1, &r, DI_SINGLELINE|DI_CENTER|DI_VCenter);
			EndPaint(hwnd, &ps); 
			break;
		default:
			return DefWindowProc(hwnd, message, wparam, lparam);
	}
	return 0;
}
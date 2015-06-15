#include "window.h"

Window::Window(HINSTANCE hI) : UI(hI)
{
	std::string name = std::string("Window") + std::to_string(rand());
	WNDCLASSEX w;
	memset(&w, 0, sizeof(WNDCLASSEX));
	w.cbSize = sizeof(WNDCLASSEX);
	w.style = CS_VREDRAW | CS_HREDRAW;
	w.cbClsExtra = w.cbWndExtra = 0;
	w.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	w.lpszClassName = name.c_str();
	w.lpszMenuName = NULL;
	w.lpfnWndProc = wndProc;
	w.hInstance = hI;
	w.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassEx(&w)) throw WindowCreateException();

	handler = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, name.c_str(), "Default ñaption", 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1, 1, NULL, NULL, hI, NULL);

	if (!handler) throw WindowCreateException();
	registerWindow();
}

void Window::registerWindow()
{
	windows[handler] = (UI*)this;
}

void Window::setText(std::string const& caption)
{
	SetWindowText(handler, caption.c_str());
}

std::string Window::getText()
{
	LPTSTR tmp = new TCHAR[1000];
	GetClassName(handler, tmp, 1000);
	std::string str(tmp);
	delete tmp;
	return str;
}

void Window::initialize()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT WINAPI Window::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  	UI* ui_ptr = windows[hwnd];
  	switch (msg) {
  	case WM_SIZE:
    	ui_ptr->trigger(Action::redraw);
    	break;
	case WM_TIMER:
    	if (ui_ptr) ui_ptr->trigger(Action::timer);
    	break;	
  	case WM_PAINT:
		ui_ptr->trigger(Action::redraw);
    	break;
	case WM_COMMAND:
		switch (HIWORD(wparam)) {
		case BN_CLICKED:
			if (windows.find((HWND)lparam) != windows.end()) 
				windows[(HWND)lparam]->trigger(Action::click);
			break;
		case EN_CHANGE:
			if (windows.find((HWND)lparam) != windows.end()) 
				windows[(HWND)lparam]->trigger(Action::change);
			break;
		case EN_SETFOCUS:
			if (windows.find((HWND)lparam) != windows.end()) 
			windows[(HWND)lparam]->trigger(Action::focus);
			break;
		case CBN_SELENDOK:
			if (windows.find((HWND)lparam) != windows.end()) 
				windows[(HWND)lparam]->trigger(Action::select);
			break;
		}
    	break;
    case WM_NOTIFY:
		switch (((LPNMHDR)lparam)->code) {
    	case NM_CLICK:
			if (windows.find(((LPNMHDR)lparam)->hwndFrom) != windows.end())
				windows[((LPNMHDR)lparam)->hwndFrom]->trigger(Action::select);
    		break;
    	}
    	break;
  	case WM_DESTROY:
      	PostQuitMessage(0);
      	return 0;
  	}
  	return DefWindowProc(hwnd, msg, wparam, lparam);
}

std::string Window::openFile()
{
	char* filename = new char[1000]{0};
	std::string file("");
	OPENFILENAME of;
	memset(&of, 0, sizeof(of));
	of.lStructSize = sizeof(of);
	of.hwndOwner = NULL;
	of.lpstrFile = filename;
	of.nMaxFile = 1000;
	of.lpstrFilter = "All files (*.*)\0*.*\0";
	of.lpstrFileTitle = NULL;
	of.nFilterIndex = 1;
	of.nMaxFileTitle = 0;
	of.lpstrInitialDir = NULL;
	of.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	if (GetOpenFileName(&of)) {
		file = std::string(of.lpstrFile);
	}
	// delete filename;
	return file;
}

std::string Window::saveFile()
{
	char* filename = new char[1000]{0};
	std::string file("");
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = filename;
    ofn.nMaxFile = 1000;
    ofn.lpstrFilter = "All files (*.*)\0*.*\0";
    ofn.lpstrTitle = NULL;
    ofn.nFilterIndex = 1;
	ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = 0;
    if (GetOpenFileName(&ofn)) {
		file = std::string(ofn.lpstrFile);
	}
	delete filename;
	return file;
}
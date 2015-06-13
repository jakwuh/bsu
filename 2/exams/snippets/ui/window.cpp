#include "window.h"

WindowMap Window::windows = WindowMap();

Window::Window(HINSTANCE hI_) : hI(hI_)
{
	initialize();
	create();
}

Window::~Window()
{
	DestroyWindow(handler);
}

void Window::initialize()
{
	name = std::string("Window") + std::to_string(rand());
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
}

void Window::initializeThread()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::create()
{
	handler = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, name.c_str(), "Default ñaption", 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1, 1, NULL, NULL, 
		hI, NULL);

	if (!handler) throw WindowCreateException();
	windows[handler] = this;
}

void Window::show()
{
	ShowWindow(handler, SW_SHOWMAXIMIZED);
}

void Window::hide()
{
	ShowWindow(handler, SW_HIDE);
}

void Window::close()
{
	delete this;
}

void Window::resize(unsigned width, unsigned height)
{
	RECT r;
	GetWindowRect(handler, &r);
	SetWindowPos(handler, HWND_TOP, r.left, r.top, width, height, 
		SWP_NOZORDER | SWP_NOACTIVATE);
}

void Window::setCaption(std::string const& caption)
{
	SetWindowText(handler, caption.c_str());
}

std::string Window::getCaption()
{
	LPTSTR tmp = new CHAR[100];
	GetClassName(handler, tmp, 100);
	std::string str(tmp);
	delete tmp;
	return str;
}

LRESULT WINAPI Window::wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  Window* window_ptr = windows[hwnd];
  switch (msg) {
  case WM_SIZE:
    window_ptr->trigger(Action::redraw);
    break;
// case WM_TIMER:
//     app->go(wparam);	
//     break;	
  case WM_PAINT:
	window_ptr->trigger(Action::redraw);
    break;
 //  case WM_COMMAND:
 //      switch (LOWORD(wparam)) {
      
 //      case BTN_PLAY:
 //          app->play();
 //          break;
 //      case BTN_OK:
 //          level = SendMessage(GetDlgItem(hwnd, TRACKBAR_LEVEL), TBM_GETPOS, 0, 0);
 //          fps = SendMessage(GetDlgItem(hwnd, TRACKBAR_FPS), TBM_GETPOS, 0, 0);
		// app->setSettings(level, fps);
 //          app->menu();
 //          break;
 //      case BTN_SETTINGS:
 //          app->settings();
 //          break;
 //      case BTN_EXIT:
 //          DestroyWindow(hwnd);
 //          return 0;
 //          break;
 //      }
 //      break;
 //  case WM_KEYDOWN:
 //      app->keyPress(wparam);
 //      break;
  case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  
  }
  return DefWindowProc(hwnd, msg, wparam, lparam);
}


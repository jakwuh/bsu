#include "Windows.h"
#include "ui/window.h"
#include "ui/exception.h"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hPI, LPSTR lpCmdLine, int nCmdShow)
{

	try {

		Window window(hI);
		window.resize(600, 400);
		window.setCaption("Тестовое окно");
		window.show();

		Button buttonExit(window);
		button.setPosition(HPosition::center, 0);
		button.resize(100, 200);
		button.setText("Выход");

		Window::initializeThread();

	}
	catch (Exception& e) {
		MessageBox(NULL, e.what(), "ERROR", MB_OK);
		exit(0);
	}
	catch (...) {
		MessageBox(NULL, "Unknown error", "ERROR", MB_OK);
		exit(0);
	}
	return 0;
}

// #include <iostream>
// #include <fstream>
// #include "binary/binary.h"
// #include "binary/utils.h"

// using namespace std;

// class Test : public Binary::Binary
// {
// public:
// 	Test(){};
// 	int x, y, z;
// 	friend std::ostream& operator << (std::ostream& out, Test const& t)
// 	{
// 		out << t.x << ' ' << t.y << ' ' << t.z;
// 		return out;
// 	}

// };

// int main()
// {
// 	// ifstream in("out.bin", ios::in | ios::binary);
// 	// ofstream out("out.bin", ios::out | ios::binary);
// 	// stringstream ss;
// 	// Test a, b, c, d;
// 	// a.x = a.y = a.z = 1;
// 	// c.x = c.y = c.z = 2;
// 	// out << a << b << c;
// 	// out.close();
// 	// in.close();
// 	system("pause");
// }


// // my dream

// void intro(Window& window)
// {
// 	Button button(0, 0, 100, 200);
// 	button.setText("hello world");
// 	button.setFont(UI::Fonts::bold);
// 	button.on(UI::Actions::click, Delegate(&window, &Window::close);	
// }

// void home(Window& window)
// {

// }

// Window window(500, 600);
// window.setCaption("Hello world");
// window.show();

// Popup popup();
// popup.setFont(UI::Fonts::thick);
// window.on(UI::Actions::popup, Delegate(&popup, &Popup::show);

// Timer timer(500);
// timer.on(UI::Actions::end, Delegate(&popup, &Popup::show));

// window.add(popup);
// window.add(button);
// window.remove(button);

// window.show();
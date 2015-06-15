/**
* @author James
* @version 0.0.1
* @date 24.03.2015
*/

#include "core\application.h"

Application* app;

#include "core\event_handler.cpp"

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hPI, LPSTR lpCmdLine, int nCmdShow)
{
    try {
   
	app = new Application(hI, wndProc);

	MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
    
    } catch(const std::exception& e) {
        MessageBox(NULL, e.what(), "Ошибка!", MB_ICONWARNING | MB_OK);
        return 0;
    } catch (...) {
        MessageBox(NULL, "Аварийное завершение работы. Извините :(", "Ошибка!", MB_ICONWARNING | MB_OK);
        return 0;
    }
	return 0;
}
#include "application.h"

Application::Application(HINSTANCE _hI, WNDPROC _wndProc) : 
h_instance(_hI), window_proc(_wndProc)
{
	window_classname = "JRUSH";
	map_path = "resources\\output0.bmp";
	
	registerWindows();
	count_levels();
	
	main_window = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, window_classname,
		"JRUSH", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, ::config::window_width, ::config::window_height,
		NULL, NULL, h_instance, NULL);
	
	if (!main_window)
		throw ::errors::WindowCreateFail();

	ShowWindow(main_window, SW_SHOWMAXIMIZED);
	
	menu();

	delete (new Settings(&main_window));
};

Application::~Application()
{
	DestroyWindow(main_window);
}

void Application::registerWindows()
{
	WNDCLASSEX w;
	memset(&w, 0, sizeof(WNDCLASSEX));
	w.cbSize = sizeof(WNDCLASSEX);
	w.style = CS_VREDRAW | CS_HREDRAW;
	w.cbClsExtra = w.cbWndExtra = 0;
	w.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	w.lpszClassName = window_classname;
	w.lpszMenuName = NULL;
	w.lpfnWndProc = window_proc;
	w.hInstance = h_instance;
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!RegisterClassEx(&w)) 
		throw ::errors::WindowCreateFail();
}

void Application::reset()
{
	for (Views::iterator it = views.begin(); it != views.end(); ++it) {
		delete (*it);
	}
	players.clear();
	views.clear();
	towns.clear();
	KillTimer(main_window, 1);
	KillTimer(main_window, 2);
}

void Application::menu()
{
	reset();
	views.push_back(new Menu(&main_window));
	go(1);
}

void Application::settings()
{
	reset();
	views.push_back(new Settings(&main_window));
	go(1);
}

void Application::setSettings(int _level, int fps)
{
	::config::level = _level;
	::config::milliseconds_per_tact = 40 + (101 - fps) / 100 * 120;
	std::string tmp = "Настройки сохранены!\nУровень:\t" + 
		std::to_string(::config::level) + "\nСкорость прорисовки:\t" 
		+ std::to_string(fps) + "/100";
	MessageBox(NULL, tmp.c_str(), "Настройки", MB_OK);
}

void Application::play()
{
	reset();

	Player *player1_ptr = new Player(::config::keyset1, ::colors::color1);
	Player *player2_ptr = new Player(::config::keyset2, ::colors::color2);
	players.push_back(player1_ptr);
	players.push_back(player2_ptr);

	TownMap map;
	map_path = level(::config::level, towns, map, players);

	View* view1_ptr = new View(main_window, map_path, Position::left);
	View* view2_ptr = new View(main_window, map_path, Position::right);

	view1_ptr->setTowns(towns);
	view2_ptr->setTowns(towns);
	view1_ptr->setPlayer(player1_ptr);
	view2_ptr->setPlayer(player2_ptr);
	
	player1_ptr->setMap(map);
	player2_ptr->setMap(map);
	
	views.push_back(view1_ptr);
	views.push_back(view2_ptr);

	go(1);
	SetTimer(main_window, 1, ::config::milliseconds_per_tact, NULL);
	SetTimer(main_window, 2, 1000, NULL);
}

void Application::go(int cmd)
{
	if (cmd == 1) {
		for (Views::iterator it = views.begin(); it != views.end(); ++it) {
			(*it)->draw();
		}
		for (Towns::iterator it = towns.begin(); it != towns.end(); ++it) {
			(*it)->comeOut();
		}
	} else if (cmd == 2) {
		int k1 = 0, k2 = 0;
		for (Towns::iterator it = towns.begin(); it != towns.end(); ++it) {
			(*it)->grow();
			if ((*it)->getHoster() == players[0]) ++k1;
			if ((*it)->getHoster() == players[1]) ++k2;
		}
		if (k1 == 0) {
			reset();
			MessageBox(main_window, "Игра окончена! Поздравляем игрока 2 с победой", "Gameover", MB_OK);
			menu();
		} else if (k2 == 0) {
			reset();
			MessageBox(main_window, "Игра окончена! Поздравляем игрока 1 с победой", "Gameover", MB_OK);
			menu();
		}
	}
}

void Application::resize()
{
	for (Views::iterator it = views.begin(); it != views.end(); ++it) {
		(*it)->resize();
	}
}

void Application::keyPress(UINT key)
{	
	if (key == 27 && IDYES == MessageBox(NULL, "Вы уверены что хотите выйти?", "Подтверждение действия", MB_YESNO | MB_ICONWARNING))
		menu();
	for (Players::iterator it = players.begin(); it != players.end(); ++it)
		(*it)->keyPress(key);
}
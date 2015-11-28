// Джеймс Аквух
// Учебная практика, задание 1 "Использование STL. Обработка строк String."
// 24.06.2015

#include <iostream>
#include "clipboard.h"
#define CHARBUF 4096

using namespace std;

enum class Menu {
	enter_string = 1, find_string = 2, copy_string = 3,
	insert_string = 4, compare_string = 5, replace_string = 6,
	insert_string_pos = 7, show_string = 8, exit = 0
};

void showMenu();
void showPause();
void showPause(std::string const& s);
std::ostream& operator << (std::ostream&, std::string const&);

int main()
{
	try{
		setlocale(LC_ALL, ".1251");
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);
		int choice, k;
		size_t index;
		bool exit = false;
		char* tmp = new char[CHARBUF];
		string s, s_tmp;
		do
		{
			showMenu();
			cin >> choice;
			switch (static_cast<Menu>(choice))
			{
				case ::Menu::exit:
					exit = true;
					break;
				case ::Menu::enter_string:
					cout << "\nВведите строку и нажмите Enter:\n";
					cin >> tmp;
					s = string(tmp);
					break;
				case ::Menu::show_string:
					cout << "\nТекущая строка:\n" << s;
					showPause();
					break;
				case ::Menu::copy_string:
					ClipBoard << s;
					showPause("Строка сохранена в буфер Windows!");
					break;
				case ::Menu::insert_string:
					ClipBoard >> s;
					showPause("Строка из буфера обмена теперь является текущей строкой!");
					break;
				case ::Menu::compare_string:
					ClipBoard >> s_tmp;
					if (s == s_tmp) showPause("Текущая строка == строке из буфера обмена");
					else showPause("Текущая строка != строке из буфера обмена");
					break;
				case ::Menu::insert_string_pos:
					cout << "\nВведите строку для вставки и нажмите Enter:\n";
					cin >> tmp;
					cout << "\nВведите позицию для вставки и нажмите Enter:\n";
					cin >> k;
					if (k >= 0 && k <= s.size()) s.insert(k, string(tmp));
					cout << "\nТекущая строка:\n" << s;
					showPause();
					break;
				case ::Menu::find_string:
					cout << "\nВведите строку дл поиска и нажмите Enter:\n";
					cin >> tmp;
					cout << "\nС какой стороны искать? [1 - слева, 0 - справа]:\n";
					cin >> k;
					if (k == 1) {
						index = s.find(tmp);
					}
					else if (k == 0) {
						index = s.rfind(tmp);
					}
					else {
						showPause("Написано ведь - введите 0 или 1");
					}
					if (index == string::npos) {
						showPause("Строка не найдена");
					}
					else {
						cout << "\nСтрока найдена на позиции " << index << "\n";
						showPause();
					}
					break;
				case ::Menu::replace_string:
					cout << "\nВведите подстроку для замены и нажмите Enter:\n";
					cin >> tmp;
					s_tmp = string(tmp);
					cout << "\nВведите новую подстроку и нажмите Enter:\n";
					cin >> tmp;
					index = s.find(s_tmp);
					if (index != string::npos) {
						s.replace(s.begin() + index, s.begin() + index + s_tmp.size(), tmp);
						showPause("Строка успешно заменена!");
					}
					else showPause("Подстрока для замены не найдена");
					break;
			}
			cin.clear();
			cin.ignore(CHARBUF, '\n');
		} while (!exit);
	}
	catch (...) {
		cerr << "\n\nUnknown error!!!";
		system("pause");
	}
	return 0;
}

void showMenu()
{
	cout <<
		"\nПрограмма \"Использование STL. Обработка строк String.\"\n"
		"Выберите один из пунктов ниже:\n"
		"[1] - Ввести новую строку\n"
		"[2] - Найти подстроку\n"
		"[3] - Сохранить строку в буфер обмена\n"
		"[4] - Вставить строку из буфера обмена\n"
		"[5] - Сравнить введенную строку со строкой из буфера обмена\n"
		"[6] - Заменить один фрагмент строки на другой\n"
		"[7] - Вставить в строку другую строку с заданной позиции\n"
		"[8] - Вывести строку на экран\n"
		"[0] - Выход\n";
}

void showPause(){ showPause(""); }

void showPause(std::string const& s)
{
	cout << "\n\n";
	if (s.size() > 0) cout << s << "\n";
	cout << "Нажмите Enter для продолжения";
	cin.ignore();
}

std::ostream& operator << (std::ostream& out, std::string const& s)
{
	out << s.c_str();
	return out;
}
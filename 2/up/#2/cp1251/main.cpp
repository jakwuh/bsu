// Джеймс Аквух
// Учебная практика, задание 2 "Использование STL. Обработка контейнеров.  Использование класса Vector."
// 25.06.2015

#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <sstream>

using namespace std;

enum class Menu {
	enter_vector_first = 1, enter_vector_second = 2, insert_in_vector = 3,
	delete_from_vector = 4, replace_in_vector = 5, sort_vector = 6,
	find_in_vector = 7, compare_vectors = 8, copy_vector = 9,
	merge_vectors = 10, sum_vectors = 11, resize_vector = 12,
	get_vector_capacity = 13, get_vector_count = 14, 
	get_vector_capacity_remained = 15, swap = 16, 
	show_vector_first = 17, show_vector_second = 18, exit = 0
};

void showMenu();
void showPause();
void showPause(std::string const& s);

template <typename T>
std::ostream& operator << (std::ostream&, std::vector<T> const&);
template <typename T>
std::istream& operator >> (std::istream&, std::vector<T>&);

int main()
{
	try{
		setlocale(LC_ALL, ".1251");
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);
		int choice, tmp_int;
		bool exit = false;
		vector<int> v1, v2, tmp;
		vector<int>::iterator from, to, it;
		string tmp_string;
		do
		{
			showMenu();
			cin >> choice;
			std::getline(cin, tmp_string);
			switch (static_cast<Menu>(choice))
			{
			case ::Menu::exit:
				exit = true;
				break;
			case ::Menu::enter_vector_first:
				cout << "\nВведите элементы вектора и нажмите Enter:\n";
				cin >> v1;
				cout << "\nПервый вектор:\n" << v1;
				showPause();
				break;
			case ::Menu::enter_vector_second:
				cout << "\nВведите элементы вектора и нажмите Enter:\n";
				cin >> v2;
				cout << "\nВторой вектор:\n" << v2;
				showPause();
				break;
			case ::Menu::insert_in_vector:
				tmp.clear();
				cout << "\nВведите c какой позиции начинать вставку и нажмите Enter:\n";
				cin >> tmp_int;
				it = v1.begin();
				while (tmp_int-- && tmp_int >= 0 && it != v1.end()) ++it;
				cout << "\nВведите элементы для вставки и нажмите Enter:\n";
				cin >> tmp;
				while (tmp_int-- && tmp_int >= 0 && it != v1.end()) ++it;
				v1.insert(it, tmp.begin(), tmp.end());
				cout << "\nПервый вектор:\n" << v1;
				showPause();
				break;
			case ::Menu::delete_from_vector:
				cout << "\nВведите c какой позиции начинать удаление и нажмите Enter:\n";
				cin >> tmp_int;
				from = v1.begin();
				while (tmp_int-- && tmp_int >= 0 && from != v1.end()) ++from;
				cout << "\nВведите количество элементов для удаления и нажмите Enter:\n";
				cin >> tmp_int;
				to = from;
				while (tmp_int-- && tmp_int >= 0 && to != v1.end()) ++to;
				v1.erase(from, to);
				cout << "\nПервый вектор:\n" << v1;
				showPause();
				break;
			case ::Menu::replace_in_vector:
				tmp.clear();
				cout << "\nВведите c какой позиции начинать замену и нажмите Enter:\n";
				cin >> tmp_int;
				to = v1.begin();
				while (tmp_int-- && tmp_int >= 0 && to != v1.end()) ++to;
				cout << "\nВведите элементы для замены и нажмите Enter:\n";
				cin >> tmp;
				from = tmp.begin();
				while (to != v1.end() && from != tmp.end()) {
					*to = *from;
					++to;
					++from;
				}
				cout << "\nПервый вектор:\n" << v1;
				showPause();
				break;
			case ::Menu::sort_vector:
				cout << "\nВведите c какой позиции начинать сортировку и нажмите Enter:\n";
				cin >> tmp_int;
				from = v1.begin();
				while (tmp_int-- && tmp_int >= 0 && from != v1.end()) ++from;
				cout << "\nВведите количество элементов для сортировки и нажмите Enter:\n";
				cin >> tmp_int;
				to = from;
				while (tmp_int-- && tmp_int >= 0 && to != v1.end()) ++to;
				sort(from, to, std::less<int>());
				cout << "\nПервый вектор:\n" << v1;
				showPause();
				break;
			case ::Menu::find_in_vector:
				cout << "\nВведите элемент для поиска и нажмите Enter:\n";
				cin >> tmp_int;
				it = std::find(v1.begin(), v1.end(), tmp_int);
				if (it == v1.end()) {
					showPause("Элемент не найден");
				}
				else {
					cout << "\nЭлемент найден на позиции " << it - v1.begin() << "\n";
					showPause();
				}
				break;
			case ::Menu::compare_vectors:
				if (std::equal(v1.begin(), v1.end(), v2.begin())) {
					showPause("Векторы совпадают!");
				}
				else showPause("Векторы не совпадают");
				break;
			case ::Menu::copy_vector:
				v2.resize(v1.size());
				std::copy(v1.begin(), v1.end(), v2.begin());
				cout << "\nВторой вектор:\n" << v2;
				showPause();
				break;
			case ::Menu::merge_vectors:
				tmp_int = v2.size();
				v2.resize(v2.size() + v1.size());
				it = v2.begin();
				while (tmp_int-- && tmp_int >= 0) ++it;
				std::copy(v1.begin(), v1.end(), it);
				cout << "\nВторой вектор:\n" << v2;
				showPause();
				break;
			case ::Menu::sum_vectors:
				from = v1.begin();
				to = v2.begin();
				while (to != v2.end() && from != v1.end()) {
					*to += *from;
					++to;
					++from;
				}
				cout << "\nВторой вектор:\n" << v2;
				showPause();
				break;
			case ::Menu::resize_vector:
				cout << "\nВведите новый размер вектора и нажмите Enter:\n";
				cin >> tmp_int;
				v1.resize(tmp_int);
				cout << "\nПервый вектор:\n" << v1;
				showPause();
				break;
			case ::Menu::get_vector_capacity:
				showPause("Вместимость первого вектора - " + std::to_string(v1.capacity()));
				break;
			case ::Menu::get_vector_count:
				showPause("Количество элементов первого вектора - " + std::to_string(v1.size()));
				break;
			case ::Menu::get_vector_capacity_remained:
				showPause("Количество элементов, которые вместит первый вектор - " + std::to_string(v1.capacity() - v1.size()));
				break;
			case ::Menu::swap:
				swap(v1, v2);
				cout << "\nПервый вектор:\n" << v1;
				cout << "\nВторой вектор:\n" << v2;
				showPause();
				break;
			case ::Menu::show_vector_first:
				cout << "\nПервый вектор:\n" << v1;
				showPause();
				break;
			case ::Menu::show_vector_second:
				cout << "\nВторой вектор:\n" << v2;
				showPause();
				break;
			}
			cin.clear();
			cin.ignore(1000, '\n');
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
		"\nПрограмма \"Обработка контейнеров.  Использование класса Vector.\"\n"
		"Выберите один из пунктов ниже:\n"
		"[1] - Ввести первый вектор\n"
		"[2] - Ввести второй вектор\n"
		"[3] - Вставить в первый вектор \n"
		"[4] - Удалить из первого вектора\n"
		"[5] - Заменить в первом векторе\n"
		"[6] - Сортировать первый вектор\n"
		"[7] - Найти в первом векторе\n"
		"[8] - Сравнить векторы\n"
		"[9] - Скопировать первый вектор во второй\n"
		"[10] - Объединить вектора и сохранить во второй вектор\n"
		"[11] - Сложить вектора и сохранить во второй вектор\n"
		"[12] - Изменить размеры первого вектора\n"
		"[13] - Показать емкость первого вектора\n"
		"[14] - Показать количество элементов в первом векторе\n"
		"[15] - Показать остаточную емкость в первом векторе\n"
		"[16] - Обменять значения векторов\n"
		"[17] - Вывести на экран первый вектор\n"
		"[18] - Вывести на экран второй вектор\n"
		"[0] - Выход\n";
}

void showPause(){ showPause(""); }

void showPause(std::string const& s)
{
	cout << "\n\n";
	if (s.size() > 0) cout << s << "\n";
	cout << "Нажмите Enter для продолжения";
}

template <typename T>
std::ostream& operator << (std::ostream& out, std::vector<T> const& v)
{
	out << "array(" << v.size() << ") >> ";
	int i = 0;
	for (auto it : v) {
		cout << "[" << i++ << "] = " << it << " ";
	}
	return out;
}
template <typename T>
std::istream& operator >> (std::istream& in, std::vector<T>& v)
{
	v.clear();
	T k;
	string line;
	std::getline(cin, line);
	std::istringstream stream(line);
	while (stream >> k)
		v.push_back(k);
	return in;
}


// Джеймс Аквух
// 25.02.2015
// Качественный контейнер студентов

#include <iostream>
#include <fstream>
#include <string>
#include "container.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "");
	ifstream in("input.txt");
	int group;
	double gpa;
	Container c;
	if (in.fail()) exit(1);
	while (!in.eof()) {
		char* s = new char[100];
		in >> s >> group >> gpa;
		c.push(Student(s, group, gpa));
	}
	int choice = 1;
	while (choice && cin.good()) {
		cout << "\n[0] - Выход";
		cout << "\n[1] - Вывести на экран список всех студентов";
		cout << "\n[2] - Сортировать студентов по фамилиям";
		cout << "\n[3] - Сортировать студентов по группам и фамилиям";
		cout << "\n[4] - Поиск студента по фамилии";
		cout << "\n[5] - Вывести на экран отчет о группах";
		cout << "\n";
		cin >> choice;
		system("cls");
		Student *tmp;
		char* str;
		switch(choice) {
			case 0:
				break;
			case 1:
				c.print(cout);
				break;
			case 2:
				c.sortByName();
				break;
			case 3: 
				c.sortByGroupAndName();
				break;
			case 4:
				str = new char[100];
				cout << "Введите фамилию для поиска :\n";
				cin >> str;
				tmp = c.findByName(str);
				cout.flags(std::ios::left);
				cout << std::setw(2) << '#' << std::setw(20) << "Фамилия" << std::setw(10) << "Группа" << std::setw(20) << "Средний балл" << "\n";
				if (tmp) 
					cout << std::setw(2) << 1 << std::setw(20) << tmp->name << std::setw(10) <<tmp->group << std::setw(20) <<tmp->gpa << std::endl;
				else cout << "Никого не найдено\n";
				break;
			case 5:
				c.report(cout);
				break;
		}
	}
	return 0;
}
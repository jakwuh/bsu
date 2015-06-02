// ������ �����
// 26.02.2015
// ����� ����� � n-������ ������������

#include <iostream>
#include "point.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	try{
		int k = 0;
		cout << "������� ����������� ������ �����:\n";
		cin >> k;
		Point p1(k);
		cout << "������� ���������� ������ �����:\n";
		cin >> p1;
		cout << "������� ����������� ������ �����:\n";
		cin >> k;
		Point p2(k);
		cout << "������� ���������� ������ �����:\n";
		cin >> p2;
		cout << "������ �����:\t" << p1;
		cout << "\n������ �����:\t" << p2;
		cout << "\n����� �����:\t" << (p1 + p2);
		cout << "\n�������� �����:\t" << (p1 - p2);
		cout << "\n������ ����� ������ �� ������ ���������, ��� ������:\t" << (p1 > p2);
		cout << "\n����� ��������� �� ���������� ���������� �� ������ ���������:\t" << (p1 == p2);
		cout << "\n������������ ��������� ������ ����� ������������ ������ ���������:\t" << (-p1);
	} catch (Error& e) {
		cout << "\n������:\t" << e.what();
	}
	cout << "\n";
	system("pause");
	return 0;
}
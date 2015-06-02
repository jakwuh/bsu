#include <iostream>
#include <fstream>
#include <Windows.h>
#include "generator.h"
#include "bitmap.h"
#include "map.h"
#include "surface.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ".1251");
    int regions_number, streched, n, m, ppc;
    double deviation;
	cout << "Добро пожаловать в Генератор карт 1.0!\t";
	cout << "\nЦвета сгенерированной карты находятся в файле colors.ini (формат RGB). Вы можете поменять их на свои значения.";
    cout << "\nВведите количество областей на карте (1 - 10000):\t";
    cin >> regions_number;
    cout << "Введите коэффициент растяжения областей (1 - области очень вытянутые, 100 - ромбообразные):\t";
    cin >> streched;
    cout << "Введите коэффициент размера областей (0 - все области строго одинакового размера, 0,9 - размеры областей сильно отличаются):\t";
    cin >> deviation;
    cout << "Введите ширину карты в ячейках:\t";
    cin >> n;
    cout << "Введите высоту карты в ячейках:\t";
    cin >> m;
    cout << "Введите длину стороны ячейки в пикселях (1-100):\t";
    cin >> ppc;

    assert(regions_number > 0 && regions_number <= 10000);
    assert(streched > 0 && streched <= 100);
    assert(deviation > 0 && deviation < 1);
    assert(n > 0 && n < 30000);
    assert(m > 0 && m < 30000);
    assert(ppc * n > 0 && ppc * n < 60000);
    assert(ppc * m > 0 && ppc * m < 60000);

    std::vector<Surface> surfaces;
	{
		char* buf = new char[100];
		int r, g, b;
		std::ifstream in("colors.ini");
		while (in) {
			in.getline(buf, 100);
			sscanf(buf, "%d%d%d", &r, &g, &b);
			surfaces.push_back(RGB(r, g, b));
		}
		delete buf;
	}

	cout << "\nГенерация карты...\n";
    Generator g;
    g.setParameters(n, m);
    Map<Surface> map = g.generateSurface(regions_number, streched, deviation, surfaces);
    LPTSTR path = "output.bmp";
    cout << "\nЗапись карты в файл...\n";
    generateBitmap(map, n, m, path, ppc);
	cout << "\nОчистка использованной памяти...\n";
	for (int i = 0; i < map.n; ++i) {
		delete[] map[i];
		cout << "\r" << (int)(100 * i / (n - 1)) << " \\ 100";
	}

	cout << "\nКарта успешно сгенерирована (файл output.bmp)\n";
	system("pause");

    return 0;
}
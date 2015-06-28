// Джеймс Аквух
// Учебная практика, задание 3 "Разработать программу для работы с отображениями (multimap). Информационное поле каждого элемента представляет собой структуру, содержащую имя(строку), возраст (вещественные числа). Использовать собственный критерий сортировки(*).Программа должна выводить на экран компьютера меню вида:
// 1. Добавить элементы из заданного диапазона(из массива или из другого отображения)
// 2. Удалить элемент
// 3. Поиск элементов меньших равных заданному ключу
// 4. Обменивает  значения двух объектов(отображений)
// 5. Замена элемента
// 6. Сравнение  отображений
// 7. Выход из программы"
//
// 27.06.2015

#include "MapForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main(array<String^>^args)
{
	try{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		up::MapForm form;
		Application::Run(%form);
	}
	catch (System::Exception^ e) {
		MessageBox::Show(e->Message);
	}
	return 0;
}
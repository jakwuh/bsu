Потоки шаблонизированы по умолчанию (с помощью typedef)

namespace Классификация {
	По направлению
	По виду внешних устройств (стандартные, файловые)
	Форматированный \ неформатированный
}

	 ___ios_____
	|			|
	istream		ostream________________ofstream
 ___|	  |			|				|__ostringstream
|		  |_________|__iostream
ifstream  |					|___stringstream
		istringstream		|
							fstream

namespace Форматированный ввод - вывод {
	namespace ios{
		existing flags {
			long x_flags
			int x_width (сбрасывается в 0 после каждого вывода)
			int x_precision
			int x_fill
		}
		Функции для установки флагов находятся в <iomanip> {
			Функции выравнивания: left, right, internal
			Функции вывода чисел: dec, oct, hex
			Функции для вывода вещественных чисел: fixed, scientific
			Другие: uppercase
		}
		cout.flags(ios::fixed | ios::left) - устанавливает флаги, сбрасывает все остальные
		cout.setf(iof::uppercase | ios::left) - устанавливает флаги, не сбрасывает остальные
		cout.precision(3)
		Манипуляторы {
			dec
			oct
			hex
			endl - Сразу переводит строку('\n' просто добавляет в буфер вывода символ)
			ends - '\0'
			flush
			setiosflags(long)
			resetiosflags(long)
			setprecision(int)
			setw(int)
			setfill(int)
		}
	}
	ifstream in;
	in.open("filename.ext", ios::text | ios::in);
	possible flags {
		ios::app
		ios::binarg
		ios::out
		ioc::trunc
	}
	possible functions {
		operator!
		bad() // if in.bad() ...
		good()
		eof()
		close() // в редких случаях - деструктор вызывается сам при уничтожении класса
	}
}

namespace бинарный ввод-вывод {
	read(buf, num) // num bytes
	возвращает ссылку на текущий поток
	write(buf, num)
	seekg(pos) // устанавливает текущую позицию в потоке
	seekg(offset, org) // смещение относительно чего-либо - org (ios::cur \ ios::beg \ ios::end)
	tellg()
	Бинарные файлы хранят образ оперативной памяти на внешнем устройстве (текстовые же хранят форматированные данные)

	struct Node 
	{
		int code;
		char name[20];
		double salary;
	};

	int length;
	Node* buf;
	fstream in;
	in.open("input.bin", ios::binary);
	in.seekg(0, ios::end);
	length = in.tellg();
	in.seekg(0, ios::beg);
	buf = new Node[length / sizeof(Node)];
	// buf = (Node*) new char[length];
	in.read((char*) buf, length);
}
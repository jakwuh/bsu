#include <iostream>
#include <fstream>
#include "binary_template.h"

using namespace std;

class Test : public BinaryTemplate
{
public:
	Test(){
		x = 2;
		y = 3;
		z = 4;
	};
	int x, y, z;
};

int main()
{
	ifstream in("out.bin", ios::in | ios::binary);
	ofstream out("out.bin", ios::out | ios::binary);
	stringstream ss;
	Test a, b;
	b.x = b.y = b.z = 0;
	out << a;
	in >> b;
	out.close();
	in.close();
	ss << a;
	system("pause");
}
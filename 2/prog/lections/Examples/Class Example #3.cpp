#include <iostream>

using namespace std;

struct s{
	int a, b;
};

class c{
	int a, b;
};

int main() {
	cout << "size of int:\t" << sizeof(int) << endl;
	cout << "size of struct:\t" << sizeof(s) << endl;
	cout << "size of class:\t" << sizeof(c) << endl;
}
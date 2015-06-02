#include <iostream>

using namespace std;

class Parent
{
protected:
	int a;
public:
	Parent(int _a = 2) : a(_a){};
	// virtual void print() { - virtual says: i do not exist for  my childs
	void print() {
		cout << "Base class say: " << a << endl;
	}
};

class Child : public Parent
{
public:
	Child(){};
	void print() {
		cout << "Child class say: " << a << endl;
	}
};

int main()
{
	Parent p;
	Child  c;
	Parent* M[2];

	p.print();
	c.print();
	// try also c.Parent::print();

	M[0] = &p;
	M[1] = &c;

	for (int i = 0; i < sizeof(M) / sizeof(M[0]); ++i)
		M[i]->print();
	return 0;
}
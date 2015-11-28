#include <iostream>

using namespace std;

class Parent
{
public:
	virtual void print() = 0;
};

class Child1 : public Parent
{
	int x, y;
public:
	Child1(){
		x = y = 2;
	}
	virtual void print() {
		cout << x << ' '  << y << endl;
	}
};

class Child2 : public Parent
{
private:
	double x, y, z;
public:
	Child2(){
		x = y = z = 1;
	}
	void print() {
		cout << x << ' ' << y << ' ' << z << endl;
	}

};

int main()
{
	// Parent p; - error - abstract class
	Parent* p1, *p2; // all is ok
	p1 = new Child1(); // all is ok
	p2 = new Child2(); // all is ok
	p1->print();
	p2->print();

	system("pause");
	return 0;
}
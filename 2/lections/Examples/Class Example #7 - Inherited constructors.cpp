#include <iostream>

using namespace std;

class Base
{
public:
	Base(int _v = 10){
		v = _v;
	};
	int v;
};

class Inherit : public Base
{
public:
	Inherit(){
	};
};

int main()
{
	Inherit in;
	cout << "all is ok";
	cout << "\n" << (in.v);
	return 0;
}


#include <iostream>

using namespace std;

class MyLess
{
public:
	bool operator () (int a, int b)
	{
		return (a < b);
	}
};

class MyGreater
{
public:
	bool operator () (int a, int b)
	{
		return (a > b);
	}
};

int main()
{
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	qsort(a, 10, sizeof(int), MyLess());
	return 0;
}
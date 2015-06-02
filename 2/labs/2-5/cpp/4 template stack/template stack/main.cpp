#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

int main()
{
	try{
		Stack<int> s;
		s.push(2);
		s.push(3);
		int i = 4;
		s.push(i);
		cout << s.top();
		s.pop();
		cout << s.top();
		s.pop();
		cout << s.top();
		s.pop();
		s.pop();
	} catch (std::exception &e) {
		cout << e.what();
	}

	system("pause");
	return 0;
}
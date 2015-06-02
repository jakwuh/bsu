#include <iostream>

using namespace std;

class Example {
public:
	void message();
	void message(int, int);
};

void Example::message() {
	cout << "Message from address " << this;
	cout << endl;
}

void Example::message(int a, int b) {
	cout << "Message from address " << this << " with " << a << ' ' << b;
	cout << endl;
}

int main() {
	Example object;
	Example* objectPtr;
	object.message(); // works fine
	object.message(1,2); // works fine
	// objectPtr->message(); bad attempt
	objectPtr = &object;
	objectPtr->message(); // good attempt
}


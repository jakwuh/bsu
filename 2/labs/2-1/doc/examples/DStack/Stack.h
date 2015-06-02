#include <iostream>
struct Node 
{
	char value;
    Node* prev;
};
class Stack
{
private:
Node* head;
public:
Stack();
~Stack();
void Push(int);
char Pop();
char Peek();
bool isEmpty();
int resh(Node*);
};


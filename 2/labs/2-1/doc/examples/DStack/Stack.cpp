#include <iostream>
#include <stack.h>


Stack::Stack()
{
	head=NULL;
}
void Stack::Push(int a)
{
	Node* temp=new Node;
	temp->prev=head;
	temp->value=a;
	head=temp;
}
char Stack::Pop()
{
    char a;
	Node* temp=head;
	if(isEmpty())
		return NULL;
	else
        a=temp->value;
        head=head->prev;
	    delete temp;
	    return a;
}
char Stack::Peek()
{
	if(!isEmpty())
		return head->value;
	else 
		return NULL;
}
bool Stack::isEmpty()
{
    if(head==NULL)
		return true;
	else 
		return false;
}
Stack::~Stack()
{
    Node*temp;
	while(head)
	{
		temp=head;
		head=head->prev;
		delete temp;
	}



}


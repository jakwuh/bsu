struct stack
{
	int c;
	stack *pred;
};



class Stack
{
private:
	stack *top;
public:
	Stack()
	{
	top = NULL;
	}
	void push( int );
	int pop();
	bool empty();

};

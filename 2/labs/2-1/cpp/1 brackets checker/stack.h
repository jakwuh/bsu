struct Item
{
	char value;
	Item * prev;
};

class Stack
{
	private:
		Item * head;
	public:
		Stack();
		~Stack();
		void push(char);
		char pop();
		char peek();
		bool isEmpty();
};
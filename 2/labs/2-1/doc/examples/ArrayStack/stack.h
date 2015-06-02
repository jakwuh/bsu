
class ArrayStack		/* стек на массиве */
{
private:
	int  size;	/* размерность массива */
	int* p;	/* указатель на массив */
	int  top;	/* верхушка стека */
public:
ArrayStack(const int& _size);  /* конструктор */
ArrayStack(const ArrayStack& s);  // конструктор копирования
~ArrayStack();	        /* деструктор */
void push(const int& n);  /* втолкнуть элемент в стек */
int pop();	              /* вытолкнуть элемент из стека */
bool isEmpty();	        /* пустой стек? */
bool isFull();	        /* полный стек? */
};
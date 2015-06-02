#define MAX 200000

class List
{
private:
	__int64 * items;
	int n;
	int head;
	int multi;
public:
	List(int m = 1) : n(0), head(0), multi(m) {
		items = new __int64 [MAX];
		push(1);
	}
	__int64 peek(){
		return !n ? 0 : items[head]; 
	}
	__int64 pop(){
		if (!n) return 0;
		__int64 item = items[head];
		n--;
		head = !n 
			? 0 
			: head == MAX - 1 
				? 0 
				: head + 1;
		return item;
	}
	void push(__int64 item){
		if (n == MAX) std::cout << std::endl << "list overfill " << multi << std::endl;
		int index = head + n;
		if (index > MAX - 1) index -= MAX;
		items[index] = item * multi;
		n++;
	}
};
Attachment #1 {
	struct Empty{};
	struct Full{};

	struct Queue {
		const int size;
		int n, head; // top == -1 if empty else >=0. конец очереди - индекс первого свободного
		int* a;
		Queue() : size(100), n(0), head(0) { // список инициализации. все константные поля должны быть проинициализированы!
			a = new int[size]; // при динамическом выделении памяти список инициализации имеет смысл
		};
		Queue(int s) : size(s), n(0), head(0) {
			a = new int[size];
		}
		~Queue(){ delete [] a; };
		void push_back(int x);
		int top() const; // const - не меняет состояния объекта
		void pop_front();
	};

	void Queue::push_back(int x) {
		if (n == size) throw Full(); // () must be!
		n++;
		a[head + n > size ? head + n - 1 - size : head + n - 1] = x;
	}

	int Queue::top() const {
		if (n == 0) throw Empty();
		return a[head];
	}

	void Queue::pop_front() {
		if (n == 0) throw Empty();
		head++;
		n--;
		if (head >= size) head -= size;
	}


	int main() {
		try {
			Queue q = Queue; // will throw an error
			q.push_back(1);
			q.push_back(2);
			q.push_back(3);
			cout << q.top() << endl;
			q.pop_front();
			cout << q.top() << endl;
			q.pop_front();
			cout << q.top() << endl;
			q.pop_front();	
			q.pop_front();	
		} catch (Empty &e) {
			cout << "Empty catched";
		}
	}
}
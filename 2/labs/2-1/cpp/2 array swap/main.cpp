#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include <deque>
#include <list>

typedef std::deque<int> Deque;
typedef std::stack<int> Stack;
typedef std::queue<int> Queue;
typedef std::list<int> List;

using namespace std;

Stack& reverseStack(Stack);
Queue& reverseQueue(Queue);
Deque& reverseDeque(Deque);
List& reverseList(List);

int main() {

	setlocale(LC_ALL,".1251");
	Stack s, sr;
	Queue q, qr;
	Deque d, dr;
	List l, lr;

	for (int i = 1; i < 10; ++i) {
		s.push(i);
		q.push(i);
		d.push_back(i);
		l.push_back(i);
	}

	sr = reverseStack(s);
	qr = reverseQueue(q);
	dr = reverseDeque(d);
	lr = reverseList(l);

	cout << "\nСтек:";
	while (!s.empty()) {
		cout << setw(3) << s.top();
		s.pop();
	}
	cout << "\nТрансформированный стек:";
	while (!sr.empty()) {
		cout << setw(3) << sr.top();
		sr.pop();
	}
	cout << "\nОчередь:";
	while (!q.empty()) {
		cout << setw(3) << q.front();
		q.pop();
	}
	cout << "\nТрансформированная очередь:";
	while (!qr.empty()) {
		cout << setw(3) <<qr.front();
		qr.pop();
	}
	cout << "\nДек:";
	while (!d.empty()) {
		cout << setw(3) << d.front();
		d.pop_front();
	}
	cout << "\nТрансформированный дек:";
	while (!dr.empty()) {
		cout << setw(3) <<dr.front();
		dr.pop_front();
	}
	cout << "\nСписок:";
	while (!l.empty()) {
		cout << setw(3) << l.front();
		l.pop_front();
	}
	cout << "\nТрансформированный список:";
	while (!lr.empty()) {
		cout << setw(3) << lr.front();
		lr.pop_front();
	}

	cout << endl << endl;
	system("pause");
	return 0;
}

Stack& reverseStack(Stack s) {
	Stack s1, *s2 = new Stack;
	int a, b;
	while (!s.empty()) {
		a = s.top();
		s.pop();
		if (s.empty()) {
			s1.push(a);
			break;
		}
		b = s.top();
		s.pop();
		s1.push(b);
		s1.push(a);
	}
	while(!s1.empty()) {
		s2->push(s1.top());
		s1.pop();
	}
	return *s2;
}

Queue& reverseQueue(Queue q) {
	Queue* q1 = new Queue;
	int a, b;
	while (!q.empty()) {
		a = q.front();
		q.pop();
		if (q.empty()) {
			q1->push(a);
			break;
		}
		b = q.front();
		q.pop();
		q1->push(b);
		q1->push(a);
	}
	return *q1;
}

Deque& reverseDeque(Deque d) {
	Deque* d1 = new Deque();
	Deque::iterator it = d.begin();
	bool toggle = false;
	while (it != d.end()) {
		d1->insert(d1->end() - toggle, *it);
		toggle = !toggle;
		it++;
	}
	return *d1;
}

List& reverseList(List l) {
	List* l1 = new List();
	bool toggle = false;
	for (List::iterator it =l.begin();  it != l.end(); ++it) {
		l1->insert(toggle ? --l1->end() : l1->end(), *it);
		toggle = !toggle;
	}
	return *l1;
}
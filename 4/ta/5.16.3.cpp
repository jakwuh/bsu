#include <iostream>
#include <fstream>
#include <fstream>

using namespace std;

bool used[100] = {0};
short path[100] = {0};
short path_length = 0;
short length;
long long total_count = 0;
ifstream in("input.txt");
ofstream out("output.txt");

inline short index (short a, short b) {
	return a * 10 + b;
}

inline short first (short index) {
	return index / 10;
}

inline short last (short index) {
	return index % 10;
}

inline void use(short ind) {
	path[path_length++] = ind;
	used[ind] = used[index(last(ind), first(ind))] = 1;
}

inline void unuse(short ind) {
	path_length--;
	used[ind] = used[index(last(ind), first(ind))] = 0;
}

inline bool is_valid() {
	return first(path[0]) == last(path[path_length - 1])
		&& (first(path[0]) != last(path[0]) || last(path[1]) < first(path[path_length - 1]));
}

inline void print() {
	total_count++;
	for (int i = 0; i < path_length; ++i) 
		out << first(path[i]) << '.' << last(path[i]) << ' ';
	out << endl;
}

void find(short current) {
	if (path_length == length) {
		if (is_valid()) print();
		return;
	}
	short current_last = last(current);
	for (int i = 0; i < 7; ++i) {
		short next = index(current_last, i);
		if (!used[next]) {
			use(next);
			find(next);
			unuse(next);
		}

	}
}

int main() {
	in >> length;
	if (length < 4 || length > 28) {
		out << "wrong count";
		return 0;
	}
	for (short i = 0; i < 7; ++i) {
		for (short j = 0; j < 7; ++j) {
			use(index(i, j));
			path_length = 0;
			path[path_length++] = index(i, j);
			find(path[0]);
		}
	}
	out << total_count;
}
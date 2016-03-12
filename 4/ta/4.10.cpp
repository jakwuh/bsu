#include <iostream>
#include <fstream>
#include <deque>
#define MAXCOUNT 1001

using namespace std;

typedef deque<int> Q;

int main() {
	ifstream in("input.in");
	ofstream out("output.out");

	Q q;
	int n, k, v0, a;
	in >> n >> k >> v0;

	int** s = new int*[n];
	for (int i = 0; i < n; ++i) {
		s[i] = new int[n];
		std::fill_n(s[i], n, 0);
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			in >> a;
			s[i][a - 1] = s[a - 1][i] = 1;
		}
		q.push_back(i);
	}

	if (n == 2) {
		cout << (v0 == 1 ? "1 2 1" : "2 1 2");
		return 0;
	}

	int nu = n * (n - 1) + 2;
	while (nu--) {
		if (!s[q[0]][q[1]]) {
			int i = 2;
			while (!s[q[0]][q[i]] || !s[q[1]][q[i + 1]]) ++i;
			for (int l = 1, r = i; l < r; ++l, --r) std::swap(q[l],q[r]);
		}
		q.push_back(q.front());
		q.pop_front();
	}

	int ch = v0 - 1;
	while (q.front() != ch) {
		q.push_back(q.front());
		q.pop_front();
	}
	for (int i = 0; i < n; ++i) {
		out << q[i] + 1 << ' ';
	}
	out << (q[0] + 1);

}
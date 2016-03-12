#include <iostream>
#include <fstream>
#include <map>

#define INF 9999

using namespace std;

typedef map<char, int> Map;

int main () {
	ifstream in("in.txt");
	ofstream out("out.txt");

	int n, a, b, tmp, sum = 0, count = 0, sign;
	Map m, path;

	in >> n;

	for (int i = 0; i < n; ++i) {
		in >> a >> b;
		tmp = a - b;
		sum += tmp;
		m[tmp]++;
	}

	sign = sum > 0 ? 1 : -1;

	// 2*5 + 4*2 + 6*1 + 8*2 + 10*5 = 90 | 5 * 12
	// 2*4 + 4*4 + 6*4 + 8*4 = 80 | 4 * 10
	// 2*3 + 4*1 + 6*3 = 28 | 3 * 8
	// 2*2 + 4*2 = 12 | 2 * 6
	// 2*1 = 2 | 1 * 4
	// 100 = 4*12 + 3*10 + 2*8 + 1*6
	for (int i = 6 * sign; i != 0; i -= sign) {
		while (abs(sum) > 100 && m[i] >= abs(i) - 1) {
			sum -= 2 * i;
			m[i]--;
			++count;
		}
	}

	for (int i = -100; i <= 100; ++i) path[i] = INF;
	path[sum] = count;

	for (int i = 6; i != 0; --i) {
		int k = m[i];
		for (int j = -100; j <= 100; ++j) {
			if (path[j] != INF && path[j - 2 * i] < path[j] + 1)[]
				path[j - 2 * i] = path[j] + 1;
		}
	}

	cout << (count + minCount);
	out << (count + minCount);
}
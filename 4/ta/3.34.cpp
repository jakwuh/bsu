// we need structure, which:
// sort - O(n log n)
// delete - O(1)
// get min - O(1)
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;

typedef std::map<int, int> Map;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");

	int n, a;
	Map m;
	in >> n;
	int* x = new int[n];
	for (int i = 0; i < n * n; ++i) {
		in >> a;
		m[a]++;
	}
	int i = 0;
	for (Map::iterator it = m.begin(); it != m.end(); ++it) {
		while (it->second > 0) {
			x[i] = i == 0 ? it->first / 2 : it->first - x[0];
			m[x[i] + x[i]]--;
			for (int j = 0; j < i; ++j) {
				m[x[j] + x[i]] -= 2;
			}
			++i;
		}
	}
	for (int i = 0; i < n - 1; ++i) out << x[i] << endl;
	out << x[n - 1];
}
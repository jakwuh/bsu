#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main (){
	int	count = 0;
	map<string, int> m;
	for (int sum = 0; sum <= 24; ++sum) {
		cout << sum << endl;
		for (int a = 0; a <= 6; ++a) {
			for (int b = 0; b <= 6; ++b) {
				for (int c = 0; c <= 6; ++c) {
					for (int d = 0; d <=6; ++d) {
						if (a + b + c + d == sum) m[to_string(a) + to_string(b) + to_string(c) + to_string(d)] = 1;
					}
				}
			}
		}
	}
	cout << m.size();
}
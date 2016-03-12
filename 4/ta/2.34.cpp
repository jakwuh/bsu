#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

#define MYINFINITY 2000000000
#define MAXSIZE 250250
#define MAXREASONABLESUM 1500500 // 250000 * 6

int main () {
	ifstream in("in.txt");
	ofstream out("out.txt");

	int n, sum = 0;
	char left[MAXSIZE] = {0};
	char right[MAXSIZE] = {0};

	in >> n;
	for (int i = 0; i < n; ++i) {
		in >> left[i] >> right[i];
		sum += left[i] + right[i];
	}
	
	int* steps = new int[MAXREASONABLESUM];
	std::fill_n(steps, MAXREASONABLESUM, MYINFINITY);
	steps[0] = 0;

	int min = 0, max = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = max; j >= min; --j) {
			if (steps[j] == MYINFINITY) continue;
			int tmp = steps[j];
			steps[j] = MYINFINITY;
			if (tmp < steps[j + left[i]]) steps[j + left[i]] = tmp;
			if (tmp + 1 < steps[j + right[i]]) steps[j + right[i]] = tmp + 1;
		}
		max += std::max(left[i], right[i]);
		min += std::min(left[i], right[i]);
	}

	int k = 0;
	int middleLeft = sum / 2;
	int middleRight = (sum + 1) / 2;
	while (middleLeft - k >= 0 && middleRight + k <= sum && 
		steps[middleLeft - k] == MYINFINITY && steps[middleRight + k] == MYINFINITY) ++k;

	if (middleLeft - k >= 0 && middleRight + k <= sum) {
		out << std::min(steps[middleLeft - k], steps[middleRight + k]);
	} else {
		out << 0;		
	}

}
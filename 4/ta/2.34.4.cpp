#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <math.h>

using namespace std;

#define OFFSET 6
#define DELTA 2000
#define ZERO (2 * DELTA)
#define STEPS_SIZE (4 * DELTA)
#define LEFT_BOUND (DELTA)
#define RIGHT_BOUND (3 * DELTA)
#define MYINFINITY 2000000000

typedef long long ll;

ll index(ll delta) {
	return delta + OFFSET;
}

ll delta(ll index) {
	return - 2 * (index - OFFSET);
}

ll bound_sum(ll index) {
	return 1000;
	switch (abs(index - OFFSET)) {
		case 6: return 1000;
		case 5: return 1000;
		case 4: return 50;
		case 3: return 20;
		default: return 10;
	}
}

ll bound_count(ll index) {
	switch (abs(index - OFFSET)) {
		case 6: return 10;
		case 5: return 12;
		case 4: return 6;
		case 3: return 4;
		case 2: return 2;
		default: return 1;
	}
}

ll max_count(ll index) {
	return (2 * DELTA / abs(index - OFFSET)) + 1;
}

int main () {
	ifstream in("input.txt");
	ofstream out("output.txt");
	ll deltas[13] = {0};
	ll n, a, b, counter, sum = 0, answer = 0;
	ll steps[STEPS_SIZE];
	std::fill_n(steps, STEPS_SIZE, MYINFINITY);

	in >> n;

	for (ll i = 0; i < n; ++i) {
		in >> a >> b;
		sum += a - b;
		deltas[index(a - b)]++;
	}

	if (sum == 0) {
		out << 0;
		return 0;
	}

	ll i = sum < 0 ? 0 : 12;
	ll step = sum < 0 ? 1 : -1;
	
	while (i != 6) {
		if (deltas[i] < bound_count(i) || abs(sum) < bound_sum(i)) {
			i += step;
			continue;
		}
		sum += bound_count(i) * delta(i);
		deltas[i] -= bound_count(i);
		answer += bound_count(i);

	}

	steps[ZERO + sum] = answer;

	for (ll i = 0; i < 6; ++i) {
		counter = min(max_count(i), deltas[i]);
		while (counter--) {
			for (int j = RIGHT_BOUND; j > LEFT_BOUND; --j) {
				steps[j + delta(i)] = min(steps[j + delta(i)], steps[j] + 1);
			}
		}
	}

	for (ll i = 12; i > 6; --i) {
		counter = min(max_count(i), deltas[i]);
		while (counter--) {
			for (int j = LEFT_BOUND; j < RIGHT_BOUND; ++j) {
				steps[j + delta(i)] = min(steps[j + delta(i)], steps[j] + 1);
			}
		}
	}

	int k = 0;
	while (steps[ZERO + k] == MYINFINITY && steps[ZERO - k] == MYINFINITY) ++k;

	out << std::min(steps[ZERO - k], steps[ZERO + k]);

}
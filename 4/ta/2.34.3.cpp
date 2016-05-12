#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <math.h>

using namespace std;

#define OFFSET 6
#define AREA 500
#define STEPS_SIZE 2000
#define LEFT_BOUND 500
#define RIGHT_BOUND 1500
#define ZERO 1000
#define MYINFINITY 2000000000

typedef long long ll;

ll index(ll delta) {
	return delta + OFFSET;
}

ll delta(ll index) {
	return - 2 * (index - OFFSET);
}

ll bound(ll index) {
	switch (abs(index - OFFSET)) {
		case 6: return 10;
		case 5: return 12;
		case 4: return 3;
		case 3: return 2;
		default: return 1;
	}
}

int main () {
	ifstream in("in.txt");
	ofstream out("out.txt");
	ll deltas[13] = {0};
	ll n, a, b, sum = 0, answer = 0;
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
	
	while (abs(sum) > AREA && i != 6) {
		if (deltas[i] < bound(i)) {
			i += step;
			continue;
		}
		sum += bound(i) * delta(i);
		deltas[i] -= bound(i);
		answer += bound(i);
	}

	steps[ZERO + sum] = answer;

	for (ll i = 0; i < 6; ++i) {
		for (ll j = RIGHT_BOUND; j > LEFT_BOUND; --j) {
			if (steps[j] == MYINFINITY) continue;
			ll count = deltas[i];
			ll step = 1;
			ll diff = delta(i);
			while (count && j + step * diff < RIGHT_BOUND) {
				steps[j + step * diff] = min(steps[j + step * diff], steps[j] + step);
				step++;
				count--;
			}
		}
	}

	for (ll i = 12; i > 6; --i) {
		for (ll j = LEFT_BOUND; j < RIGHT_BOUND; ++j) {
			if (steps[j] == MYINFINITY) continue;
			ll count = deltas[i];
			ll step = 1;
			ll diff = delta(i);
			while (count && j + step * diff > LEFT_BOUND) {
				steps[j + step * diff] = min(steps[j + step * diff], steps[j] + step);
				step++;
				count--;
			}
		}
	}

	int k = 0;
	while (steps[ZERO + k] == MYINFINITY && steps[ZERO - k] == MYINFINITY) ++k;

	out << std::min(steps[ZERO - k], steps[ZERO + k]);

}
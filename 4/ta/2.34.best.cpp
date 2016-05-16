#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <math.h>

using namespace std;

#define OFFSET 6
#define DELTA 670
#define ZERO (DELTA + 20)
#define STEPS_SIZE (2 * DELTA + 60)
#define LEFT_BOUND (20)
#define RIGHT_BOUND (2 * DELTA + 40)
#define MYINFINITY 2000000000

typedef long long ll;

inline ll index(ll delta) {
	return delta + OFFSET;
}

inline ll delta(ll index) {
	return - 2 * (index - OFFSET);
}

inline ll max_count(ll index) {
	return (DELTA / abs(delta(index))) + 1;
}

inline ll bound_sum(ll index) {
	ll sum = 0;
	switch (abs(index - OFFSET)) {
		case 1: sum += 0;
		case 2: sum += 4;   // 1*1 + 1 + 2*0
		case 3: sum += 20;  // 2*2 + 1*2 + 1*1 + 6*0 + 3*1
		case 4: sum += 46;  // 3*3 + 2*1 + 1*3 + 1 + 12*0 + 4*2
		case 5: sum += 242; // 4*4 + 3*4 + 2*4 + 1*4 + 1 + 20*0 + 15*3 + 10*2 + 5*3
		case 6: sum += 236; // 5*5 + 4*2 + 3*1 + 2*2 + 1*5 + 1 + 30*0 + 12*4 + 6*4
	}
	return sum;
}

inline ll bound_count(ll index) {
	switch (abs(index - OFFSET)) {
		case 6: return 5;
		case 5: return 4;
		case 4: return 3;
		case 3: return 2;
		case 2: return 1;
		case 1: return 1;
	}
}

ifstream in("input.txt");
ofstream out("output.txt");
ll deltas[13] = {0};
ll a, b, counter, sum = 0, answer = 0;
ll steps[STEPS_SIZE];

int main () {
	std::fill_n(steps, STEPS_SIZE, MYINFINITY);
	in >> counter;

	while (counter--) {
		in >> a >> b;
		sum += a - b;
		deltas[index(a - b)]++;
	}

	ll step = sum < 0 ? 1 : -1;
	for (int i = sum < 0 ? 0 : 12; i != 6; i += step) {
		ll bound = bound_count(i);
		ll max_count_1 = deltas[i] / bound;
		ll max_count_2 = max(0ll, abs(sum) - bound_sum(i)) / (bound * abs(delta(i)));
		ll min_count = min(max_count_1, max_count_2) * bound;

		sum += min_count * delta(i);
		answer += min_count;
		deltas[i] -= min_count;
	}

	steps[ZERO + sum] = answer;

	for (ll i = 0; i < 13; ++i) {
		if (6 == i) continue;
		counter = min(max_count(i), deltas[i]);
		int step = - delta(i) / abs(delta(i));
		int from = step > 0 ? LEFT_BOUND : RIGHT_BOUND;
		int current_delta = delta(i);
		while (counter--) {
			for (int j = from; j >= LEFT_BOUND && j <= RIGHT_BOUND; j += step) {
				steps[j + current_delta] = min(steps[j + current_delta], steps[j] + 1);
			}
		}
	}

	int k = 0;
	while (steps[ZERO + k] == MYINFINITY && steps[ZERO - k] == MYINFINITY) ++k;
	out << min(steps[ZERO - k], steps[ZERO + k]);

}
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <bitset>

using namespace std;

typedef long long ll;

struct Edge {
	ll v, b, m;
};

struct Path {
	ll lowest, lowest_tail, sv, v, b, l;
};

struct Node {
	int v;
	Node* next;
};

Node qq[7];

void print(ll b) {
	ll cv = 0;
}

int main (){
	ll b = 1;
	map<int, map<int, Edge>> m;
	for (int i = 0; i <= 6; ++i) {
		m[i] = map<int, Edge>();
		for (int j = 0; j <= 6; ++j) {
			Edge e;
			e.v = j;
			e.b = b;
			m[i][j] = e;
			m[i][j].m = m[min(i, j)][max(i, j)].b;
			b *= 2;
		}
	}

	queue<Path> q;

	int len = 10;

	for (int i = 0; i <= 6; ++i) {
		for (int j = i + 1; j <= 6; ++j) {
			Path p;
			p.sv = i;
			p.v = j;
			p.b = m[i][i].b | m[i][j].b | m[j][i].b;
			p.l = 2;
			p.lowest = m[i][i].b;
			p.lowest_tail = m[j][i].b;
			q.push(p);
		}
	}

	for (int i = 0; i <= 6; ++i) {
		for (int j = i + 1; j <= 6; ++j) {
			Path p;
			p.sv = i;
			p.v = j;
			p.b = m[i][j].b | m[j][i].b;
			p.l = 1;
			p.lowest = m[min(i, j)][max(i, j)].b;
			p.lowest_tail = p.lowest;
			q.push(p);
		}
	}

	int count = 0;
	while (!q.empty()) {
		Path p = q.front();
		q.pop();
		for (auto pair : m[p.v]) {
			Edge e = pair.second;
			if (p.b & e.b) continue;
			if (e.m < p.lowest) continue;
			Path np = p;
			np.l++;
			np.v = e.v;
			np.b = np.b | m[p.v][e.v].b | m[e.v][p.v].b;
			if (np.l == len) {
				if (np.v == np.sv && e.b > np.lowest_tail) {
					++count;
					// cout << np.lowest << ' ' << np.lowest_tail << ' ' << e.b << endl;
					// cout << bitset<64>(np.b) << endl;
					// se.insert(p.b);
				}
				continue;
			}
			q.push(np);
		}
	}
	cout << count;

}
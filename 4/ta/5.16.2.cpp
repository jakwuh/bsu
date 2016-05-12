#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

typedef short vertex_t;
typedef long long rib_t;

struct Path {
	vertex_t first_vertex;
	vertex_t vertex;
	int length;
	rib_t ribs;
	Path (vertex_t first_vertex_, vertex_t vertex_, int length_, rib_t ribs_) 
		: first_vertex(first_vertex_), vertex(vertex_), length(length_), ribs(ribs_) {};
};

typedef queue<Path> Queue;
typedef unordered_set<rib_t> Vector;

vector<vertex_t> VERTICES = {0, 1, 2, 3, 4, 5, 6};
map<int, rib_t> RIBS;
map<rib_t, int> RIBS_INDEXES;
ifstream in("input.txt");
ofstream out("output.txt");

inline int rib_index(vertex_t, vertex_t);
void print_path(rib_t, int);

int main() {
	int length, index;
	rib_t rib = 1;
	Vector cycles;
	Queue q;

	for (auto i : VERTICES) {
		q.push(Path(i, i, 0, 0));
		for (auto j : VERTICES) {
			index = rib_index(i, j);
			RIBS[index] = rib;
			RIBS_INDEXES[rib] = index;
			rib *= 2;
		}
	}

	in >> length;

	if (length <= 3) {
		out << "wrong count";
		return 0;
	}

	while (!q.empty()) {
		Path p = q.front();
		q.pop();

		if (p.length == length) {
			if (p.vertex == p.first_vertex) cycles.insert(p.ribs);
		} else {
			for (auto i : VERTICES) {
				rib = RIBS[rib_index(p.vertex, i)];
				if (p.ribs & rib) continue;
				q.push(Path(p.first_vertex, i, p.length + 1, p.ribs | rib));
			}
		}
	}

	for (auto path : cycles) {
		print_path(path, length);
		out << endl;
	}
	out << cycles.size();

}

inline int rib_index(vertex_t from, vertex_t to) {
	return 7 * min(from, to) + max(from, to);
}

vertex_t find_next_vertex(rib_t path, rib_t current_path, vertex_t current_vertex) {
	rib_t rib = RIBS[rib_index(current_vertex, current_vertex)];
	if ((path & rib) && !(current_path & rib)) return current_vertex;
	
	for (auto vertex : VERTICES) {
	rib_t rib = RIBS[rib_index(vertex, current_vertex)];
		if ((path & rib) && !(current_path & rib)) {
			return vertex;
		}
	}
	return 0;
}

void print_path(rib_t path, int length) {
	vertex_t vertex, next_vertex;
	rib_t current_path;

	bool found = 0;
	for (auto a : VERTICES) {
		for (auto b : VERTICES) {
			current_path = RIBS[rib_index(a, b)];
			if (path & current_path) {
				vertex = a;
				next_vertex = b;
				found = 1;
			}
			if (found) break;
		}
		if (found) break;
	}

	out << vertex << '.' << next_vertex;

	int current_length = 1;
	while (current_length < length) {
		++current_length;
		vertex = next_vertex;
		next_vertex = find_next_vertex(path, current_path, next_vertex);
		current_path = current_path | RIBS[rib_index(vertex, next_vertex)];
		out << ' ' << vertex << '.' << next_vertex;
	}
}
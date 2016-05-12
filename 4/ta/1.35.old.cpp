#include <iostream>
#include <fstream>
#include <sstream>
#include <cstddef>
#include <unordered_set>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
typedef unordered_set<int> Set;

class Node {
	public:
		Node *l, *r;
		ll v, cl, cr, ct;
		Set cls, crs, cts;
		Node (ll _v, Node *_l = 0, Node *_r = 0) {
			v = _v;
			l = _l;
			r = _r;
			cl = cr = ct = 0;
		}
};

ifstream in("tst.in");
ofstream out("tst.out");
stringstream sout;
Node *root = 0;
Node *answer = 0;
ll k, a;


void insert(Node *n, ll v) {
	if (!root) {
		root = new Node(v);
		return;
	}
	if (v > n->v) {
		if (n->r) insert(n->r, v);
		else n->r = new Node(v);
	}
	if (v < n->v) {
		if (n->l) insert(n->l, v);
		else n->l = new Node(v);
	}
}

void print(Node *n, ofstream& out) {
	if (!n) return;
	sout << n->v << '\n';
	print(n->l, out);
	print(n->r, out);
}

ll fill_rl(Node *n) {
	if (!n) return 0;
	n->cl = fill_rl(n->l);
	n->cr = fill_rl(n->r);
	return max(n->cl, n->cr) + 1;
}

Set fill_rls(Node *n) {
	if (!n) return {};
	Set cts;
	Set cls = n->l ? fill_rls(n->l) : Set();
	Set crs = n->r ? fill_rls(n->r) : Set();
	if (!cls.size() && !crs.size()) {
		n->cls = {0};
		n->crs = {0};
		return {1};
	}
	for (auto it : cls) {
		n->cls.insert(it);
		cts.insert(it + 1);
	}
	for (auto it : crs) {
		n->crs.insert(it);
		cts.insert(it + 1);
	}
	return cts;
}

bool hasHalfPath(Set s1, Set s2) {
	for (auto it1 : s1) {
		for (auto it2 : s2) {
			if (it1 + it2 == k) return true;
		}
	}
	return false;
}

void fill_t(Node *n, ll ct, Set cts) {
	if (!n) return;

	n->ct = ct;
	n->cts = cts;
	ll cl = n->cl, cr = n->cr;
	Set cls = n->cls, crs = n->crs;

	if (ct < k && cr < k && cl < k) {
		if (!hasHalfPath(cls, crs) && !hasHalfPath(cts, cls) && !hasHalfPath(cts, crs)) {
			if (!answer || answer->v < n->v) answer = n;
		}
	}

	Set cts_l, cts_r;
	for (auto it : n->cts) {
		cts_l.insert(it + 1);
		cts_r.insert(it + 1);
	}
	for (auto it : n->crs) cts_l.insert(it + 1);
	for (auto it : n->cls) cts_r.insert(it + 1);

	fill_t(n->l, max(ct, cr) + 1, cts_l);
	fill_t(n->r, max(ct, cl) + 1, cts_r);
}

Node* find_parent(Node *n) {
	Node *parent = root;
	while (parent && parent->l != n && parent->r != n)
		parent = (n->v > parent->v ? parent->r : parent->l);
	return parent;
}

Node* remove_r(Node *n, Node *root) {
	Node *parent = find_parent(n);
	Node *&link = parent ? (parent->l == n ? parent->l : parent->r) : root;
	if (!n) return root;

	if (!n->l && !n->r) {
		if (!parent) return 0;
		link = 0;
	}
	else if (!n->l && n->r) {
		if (!parent) return n->r;
		link = n->r;
	}
	else if (!n->r && n->l) {
		if (!parent) return n->l;
		link = n->l;
	}
	else if (n->l && n->r) {
		Node *tmp = n->r;
		while (tmp->l) tmp = tmp->l;
		ll tmpv = tmp->v;
		root = remove_r(tmp, root);
		n->v = tmpv;
	}
	return root;
}

int main() {
	in >> k;
	while (in >> a) insert(root, a);

	fill_rl(root);
	fill_rls(root);
	fill_t(root, 0, {});
	
	if (answer) root = remove_r(answer, root);
	
	if (!root) {
		out << "Empty";
	} else {
		print(root, out);
		string s = sout.str();
		out << s.substr(0, s.size() - 1);
	}
	return 0;
}
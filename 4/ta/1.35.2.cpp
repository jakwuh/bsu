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

void traverse(Node *n, vector<ll>& v) {
	if (!n) return;
	v.push_back(n->v);
	traverse(n->l, v);
	traverse(n->r, v);
}

ll fill_rl(Node *n) {
	if (!n) return 0;
	n->cl = fill_rl(n->l);
	n->cr = fill_rl(n->r);
	return max(n->cl, n->cr) + 1;
}

void fill_t(Node *n, ll ct) {
	if (!n) return;
	n->ct = ct;
	ll cl = n->cl, cr = n->cr;

	if (ct < k && cr < k && cl < k) {
		if (ct + cl < k && cl + cr < k && ct + cr < k) {
			if (!answer || answer->v < n->v) answer = n;
		}
	}

	fill_t(n->l, max(ct, cr) + 1);
	fill_t(n->r, max(ct, cl) + 1);
}

int main() {
	in >> k;
	while (in >> a) insert(root, a);

	fill_rl(root);
	fill_t(root, 0);
	
	vector<ll> vout;
	traverse(root, vout);
	if (answer) {
		vout.erase(std::remove(vout.begin(), vout.end(), answer->v), vout.end());
	}

	if (!vout.size()) {
		out << "Empty";
	} else {
		for (auto it : vout) sout << it << '\n';
		string s = sout.str();
		out << s.substr(0, s.size() - 1);
	}
	
	return 0;
}
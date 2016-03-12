#include <iostream>
#include <fstream>
#include <cstddef>
#include <algorithm>

typedef long long ll;

using namespace std;

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

void insert(Node *n, ll v) {
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
	// cout << n->v << '(' << n->cl << ',' << n->cr << ',' << n->ct << ')' << ' ';
	out << n->v << '\n';
	print(n->l, out);
	print(n->r, out);
}

ll fill_rl(Node *n) {
	if (!n->l) n->cl = 0;
	else n->cl = fill_rl(n->l) + 1;

	if (!n->r) n->cr = 0;
	else n->cr = fill_rl(n->r) + 1;

	return max(n->cl, n->cr);
}

void fill_t(Node *n, ll ct, Node *&answer, ll k) {
	n->ct = ct + 1;

	bool nice = true;
	if (n->ct >= k || n->cr >= k || n->cl >=k) nice = false;
	if (n->ct + n->cr >= k || n->ct + n->cl >= k|| n->cl + n->cr >= k) nice = false;
	if (nice && (!answer || answer->v < n->v)) answer = n;

	if (n->l) {
		fill_t(n->l, max(n->ct, n->cr), answer, k);
	}
	if (n->r) {
		fill_t(n->r, max(n->ct, n->cl), answer, k);
	}
}

Node* find_parent(Node *n, Node *root) {
	if (root == n) return 0;
	if (root->l == n || root->r == n) return root;
	if (n->v > root->v) return find_parent(n, root->r);
	else return find_parent(n, root->l);
}

Node* remove(Node *n, Node *root) {
	Node *parent = find_parent(n, root);
	Node *&link = parent ? (parent->l == n ? parent->l : parent->r) : root;
	if (!n) return root;

	if (!n->l && !n->r) {
		if (!parent) return 0;
		link = 0;
		return root;
	}
	if (!n->l && n->r) {
		if (!parent) return n->r;
		link = n->r;
		return root;
	}
	if (!n->r && n->l) {
		if (!parent) return n->l;
		link = n->l;
		return root;
	}
	if (n->l && n->r) {
		Node *tmp = n->r;
		while (tmp->l) tmp = tmp->l;
		ll tmpv = tmp->v;
		remove(tmp, root);
		n->v = tmpv;
		return root;
	}
	return root;
}

int main() {
	Node *root = 0, *answer = 0;
	ifstream in("tst.in");
	ofstream out("tst.out");
	int k, a;
	in >> k;
	while (in >> a) {
		if (!root) root = new Node(a);
		else insert(root, a);
	}
	if (!root) {
		out << "Empty";
		return 0;
	}
	fill_rl(root);
	fill_t(root, -1, answer, k);
	
	if (answer) root = remove(answer, root);
	if (!root) {
		out << "Empty";
	} else {
		print(root, out);
	}
	return 0;
}
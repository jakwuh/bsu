#ifndef __BTREE_H_INCLUDED__
#define __BTREE_H_INCLUDED__

#include "error.h"
#include "string.h"
#include "vector.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
//#include "list.h"
#include <list>

#define List list

// Node interface

template <typename K, typename V>
class Node
{
private:
	K key;
	V value;
	Node* left, *right;
	Node(const Node&);
	Node(K, const V&);
	~Node();
	Node* find(K);
	void insert(const Node&);
	void remove(Node* parent);
	static Node* parent(Node*, Node*);
	static int maxDepth(Node*);
	static int visualWidth(const Node*);
	template <typename K, typename V>
	friend class BTree;
	template <typename K, typename V>
	friend void emplaceTree(Node<K, V>*** nodes, Node<K, V>* n, int i, int j);
};

// BTree interface

template <typename K, typename V>
class BTree
{
private:
	Node<K, V>* root;
public:
	BTree() : root(nullptr){};
	BTree(const BTree& bt);
	~BTree(){ delete root; root = nullptr; }
	BTree& insert(K, V);
	BTree& remove(K);
	V* find(K);
	V min();
	V max();
	bool empty() const;
	int maxDepth() const;
	Vector<String> toVectorString();
	template <typename K, typename V>
	// Iterator interface
	friend std::ostream& operator << (std::ostream&, const BTree&);
	class Iterator
	{
	public:
		friend BTree;
		enum traverse_type {infix, prefix, postfix};
	private:
		std::list< Node<K, V>* > stack;
		Node<K, V>* node_ptr;
		traverse_type tt;
		Iterator() : node_ptr(nullptr){};
	public:
		Iterator(const Iterator&);
		~Iterator();
		void setTraverseType(traverse_type);
		Iterator& operator = (const Iterator&);
		Iterator& operator ++ ();
		Iterator operator ++ (int);
		Iterator operator + (int);
		V& operator * ();
		V* operator -> ();
		bool operator == (const Iterator&);	
		bool operator != (const Iterator&);
	};
public:
	typename Iterator begin(typename Iterator::traverse_type /*tt*/ = Iterator::traverse_type::infix) const;
	typename Iterator end(typename Iterator::traverse_type /*tt*/ = Iterator::traverse_type::infix) const;
};

// utils

template <typename K, typename V>
void emplaceTree(Node<K, V>*** nodes, Node<K, V>* n, int i, int j)
{
	nodes[i][j + ::Node<K, V>::visualWidth(n->left)] = n;
	if (n->left)
		emplaceTree(nodes, n->left, i + 2, j);
	if (n->right)
		emplaceTree(nodes, n->right, i + 2, j + 1 + ::Node<K, V>::visualWidth(n->left));
}

// Node implementation

template <typename K, typename V>
Node<K, V>::Node(K _key, const V& _value) : key(_key), value(_value), left(nullptr), right(nullptr)
{
};

template <typename K, typename V>
Node<K, V>::Node(const Node& n) : left(nullptr), right(nullptr)
{
	key = n.key;
	value = n.value;
	if (n->left)
		left = new Node<K, V>(n->left);
	if (n->right)
		right = new Node<K, V>(n->right);
}

template <typename K, typename V>
Node<K, V>::~Node()
{
	left = right = nullptr;
}

template <typename K, typename V>
void Node<K, V>::insert(const Node& n)
{
	if (n.key > key)
		if (!right)
			right = new Node<K, V>(n.key, n.value);
		else
			right->insert(n);
	else if (n.key < key)
		if (!left)
			left = new Node<K, V>(n.key, n.value);
		else
			left->insert(n);
}

template <typename K, typename V>
Node<K, V>* Node<K, V>::parent(Node<K, V>* where, Node<K, V>* what)
{
	if (!where) return nullptr;
	if (where->left == what)
		return where;
	else if (where->right == what)
		return where;
	else if (parent(where->right, what))
		return parent(where->right, what);
	else
		return parent(where->left, what);
}

template <typename K, typename V>
Node<K, V>* Node<K, V>::find(K _key)
{
	if (_key == key)
		return this;
	else if (_key < key && this->left)
		return this->left->find(_key);
	else if (_key > key && this->right)
		return this->right->find(_key);
	else return nullptr;
}

template <typename K, typename V>
void Node<K, V>::remove(Node<K, V>* parent)
{
	if (!left && !right) {
		if (parent)
			if (parent->left == this)
				parent->left = nullptr;
			else 
				parent->right = nullptr;
		delete this;
	}
	else if (!left && right) {
		Node<K, V>* tmp = right;
		key = right->key;
		value = right->value;
		left = right->left;
		right = right->right;
		delete tmp;
	}
	else if (left && !right) {
		Node<K, V>* tmp = left;
		key = left->key;
		value = left->value;
		right = left->right;
		left = left->left;
		delete tmp;
	}
	else {
		if (!right->left) {
			Node<K, V>* tmp = right;
			key = right->key;
			value = right->value;
			right = right->right;
			delete tmp;
		}
		else {
			parent = right;
			Node<K, V>* min = right->left;
			while(min->left) {
				parent = min;
				min = min->left;
			}
			key = min->value;
			value = min->value;
			min->remove(parent);
		}
	}
}

template <typename K, typename V>
int Node<K, V>::maxDepth(Node* n)
{
	return n ? 1 + ::std::max(maxDepth(n->left), maxDepth(n->right)) : 0;
}

template <typename K, typename V>
int Node<K, V>::visualWidth(const Node<K, V>* n)
{
	if (n) 
		if (n->left || n->right)
			return 1 + visualWidth(n->left) + visualWidth(n->right);
		else return 1;
	return 0;
}

// BTree implementation

template <typename K, typename V>
BTree<K, V>::BTree(const BTree& bt)
{ 
	root = bt.root ? new Node<K, V>(bt.root) : 0; 
}

template <typename K, typename V>
int BTree<K, V>::maxDepth() const
{ 
	return ::Node<K, V>::maxDepth(root); 
}

template <typename K, typename V>
bool BTree<K, V>::empty() const
{
	return !root;
}

template <typename K, typename V>
BTree<K, V>& BTree<K, V>::insert(K k, V v)
{
	if (!root)
		root = new Node<K, V>(k, v);
	else root->insert(Node<K, V>(k, v));
	return *this;
}

template <typename K, typename V>
V* BTree<K, V>::find(K k)
{
	if (!root)
		return nullptr;
	else 
		return root->find(k);
}

template <typename K, typename V>
BTree<K, V>& BTree<K, V>::remove(K k)
{
	if (root->find(k))
		root->find(k)->remove(::Node<K, V>::parent(root, root->find(k)));
	return *this;
}

template <typename K, typename V>
V BTree<K, V>::min()
{
	if (!root) throw EmptyTree();
	Node<K, V> *tmp = root;
	while(tmp->left)
		tmp = tmp->left;
	return tmp->value;
}

template <typename K, typename V>
V BTree<K, V>::max()
{
	if (!root) throw EmptyTree();
	Node<K, V> *tmp = root;
	while (tmp->right)
		tmp = tmp->right;
	return tmp->value;
}

template <typename K, typename V>
std::ostream& operator << (std::ostream& out, const BTree<K, V>& bt)
{
	out << (bt.print());
	return out;
}

template <typename K, typename V>
Vector<String> BTree<K, V>::toVectorString()
{
	int m = ::Node<K, V>::visualWidth(root);
	int n = root ? 2 * ::Node<K, V>::maxDepth(root) - 1 : 0;
	
	Vector<String> v (n * (m + 1), "");

	Node<K, V>*** nodes = new Node<K, V>** [n];
	for (int i = 0; i < n; ++i) {
		nodes[i] = new Node<K, V>*[m];
		for (int j = 0; j < m; ++j)
			nodes[i][j] = 0;
	}

	if (root)
		::emplaceTree(nodes, root, 0, 0);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			if (nodes[i][j]) {
				v[(m + 1) * i + j] = nodes[i][j]->value;
				if (i > 1) {
					if (::Node<K, V>::parent(root, nodes[i][j])->left == nodes[i][j]) {
						v[(m + 1) * (i - 1) + j] = "/";
						for (int k = j + 1; nodes[i - 2][k] == 0; ++k)
							v[(m + 1) * (i - 2) + k] = "_";
					}
					else {
						v[(m + 1) * (i - 1) + j] = "\\";
						for (int k = j - 1; nodes[i - 2][k] == 0; --k)
							v[(m + 1) * (i - 2) + k] = "_";
					}
				}
			}
		}

	for (int i = 0; i < n; ++i)
		v[(m + 1) * i + m] = "\n";

	return v;
}

template <typename K, typename V>
typename BTree<K, V>::Iterator BTree<K, V>::begin(typename BTree<K, V>::Iterator::traverse_type _tt) const
{
	typename BTree<K, V>::Iterator tmp_it;
	tmp_it.setTraverseType(_tt);
	if (_tt == Iterator::traverse_type::infix) {
		if (root) {
			Node<K, V>* tmp = root;
			while (tmp) {
				tmp_it.stack.push_back(tmp);
				tmp = tmp->left;
			}
			++tmp_it;
		}
	} else {
		throw std::invalid_argument("BTree<K, V>::begin: traverse_type not realised yet");
	}
	return tmp_it;
}

template <typename K, typename V>
typename BTree<K, V>::Iterator BTree<K, V>::end(typename BTree<K, V>::Iterator::traverse_type _tt) const
{
	typename BTree<K, V>::Iterator tmp_it;
	tmp_it.setTraverseType(_tt);
	if (_tt == Iterator::traverse_type::infix) {

	} else {
		throw std::invalid_argument("BTree<K, V>::end: traverse_type not realised yet");
	}
	return tmp_it;
}

// BTree Iterator implementation

template <typename K, typename V>
BTree<K, V>::Iterator::Iterator(const Iterator& it)
{
	(*this).operator = (it);
}

template <typename K, typename V>
BTree<K, V>::Iterator::~Iterator()
{
}

template <typename K, typename V>
void BTree<K, V>::Iterator::setTraverseType(traverse_type _tt)
{
	tt = _tt;
}

template <typename K, typename V>
typename BTree<K, V>::Iterator& BTree<K, V>::Iterator::operator = (const Iterator& it)
{
	stack = List< Node<K, V>* >(it.stack);
	node_ptr = it.node_ptr;
	tt = it.tt;
	return *this;
}

template <typename K, typename V>
typename BTree<K, V>::Iterator& BTree<K, V>::Iterator::operator ++ ()
{
	if (!stack.empty()) {
		node_ptr = stack.back();
		stack.pop_back();
		if (node_ptr->right) {
			stack.push_back(node_ptr->right);
			Node<K, V>* tmp = node_ptr->right->left;
			while (tmp) {
				stack.push_back(tmp);
				tmp = tmp->left;
			}
		}
	} else {
		node_ptr = nullptr;
	}
	return *this;
}

template <typename K, typename V>
typename BTree<K, V>::Iterator BTree<K, V>::Iterator::operator ++ (int)
{
	Iterator tmp(*this);
	++(*this);
	return tmp;
}

template <typename K, typename V>
typename BTree<K, V>::Iterator BTree<K, V>::Iterator::operator + (int i)
{
	Iterator it(*this);
	while (i--)
		++it;
	return it;
}

template <typename K, typename V>
V& BTree<K, V>::Iterator::operator * ()
{
	if (!node_ptr) 
		throw new ::std::runtime_error("BTree<K, V>::Iterator::operator *: empty iterator");
	return node_ptr->value;
}

template <typename K, typename V>
V* BTree<K, V>::Iterator::operator -> ()
{
	if (!node_ptr) 
		throw new ::std::runtime_error("BTree<K, V>::Iterator::operator *: empty iterator");
	return &(node_ptr->value);
}

template <typename K, typename V>
bool BTree<K, V>::Iterator::operator == (const Iterator& it)
{
	return node_ptr == it.node_ptr;
}

template <typename K, typename V>
bool BTree<K, V>::Iterator::operator != (const Iterator& it)
{
	return !(*this == it);
}

#endif
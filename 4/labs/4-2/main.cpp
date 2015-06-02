	#include <iostream>
	#include <fstream>
	#include <iomanip>
	#include <algorithm>

	using namespace std;

	struct Node {
		Node(int newValue = 0) : left(0), right(0), value(newValue){};
		Node *left, *right;
		int value;
	};

	void paste(Node*& root, int newValue) {
		if (!root)
			root = new Node(newValue);
		else if (newValue > root->value)
			if (!root->right)
				root->right = new Node(newValue);
			else
				paste(root->right, newValue);
		else if (newValue < root->value)
			if (!root->left)
				root->left = new Node(newValue);
			else
				paste(root->left, newValue);
	}

	int maxBranchPath(Node* node) {
		if (node)
			return 	1 + max(maxBranchPath(node->left), maxBranchPath(node->right));
		else
			return 0;
	}

	int maxPath(Node* root) {
		if (!root) return 0;
		else return 1 + maxBranchPath(root->left) + maxBranchPath(root->right);
	}

	int findMaxPath(Node* root, int& value) {
		if (!root)
			return 0;
		else if (findMaxPath(root->left, value) > maxPath(root) 
			&& findMaxPath(root->left, value) > findMaxPath(root->right, value))
			return findMaxPath(root->left, value);
		else if (findMaxPath(root->right, value) > maxPath(root))
			return findMaxPath(root->right, value);
		else {
			value = root->value;
			return maxPath(root);
		}
	}

	void deleteNode(Node*& root, Node* rootParent, int value) {
		if (!root) return;
		else if (value < root->value)
			deleteNode(root->left, root, value);
		else if (value > root->value)
			deleteNode(root->right, root, value);
		else {
			if (!root->left && !root->right) {
				if (rootParent)
					if (rootParent->left == root)
						rootParent->left = 0;
					else 
						rootParent->right = 0;
				delete root;
				root = 0;
			}
			else if (!root->left && root->right) {
				Node* tmp = root->right;
				root->value = root->right->value;
				root->left = root->right->left;
				root->right = root->right->right;
				delete tmp;
			}
			else if (root->left && !root->right) {
				Node* tmp = root->left;
				root->value = root->left->value;
				root->left = root->left->left;
				root->right = root->left->right;
				delete tmp;
			}
			else {
				if (!root->right->left) {
					Node* tmp = root->right;
					root->value = root->right->value;
					root->right = root->right->right;
					delete tmp;
				}
				else {
					Node* min = root->right->left;
					while(min->left)
						min = min->left;
					root->value = min->value;
					deleteNode(root->right, root, min->value);
				}
			}
		}
	}
	// see delete algorithm's explanation on wiki

	void show(Node* root, ofstream& out) {
		if (!root) return;
		out << ' ' << root->value;
		show(root->left, out);
		show(root->right, out);
	}


	int main() {
		freopen("input.txt", "r", stdin);
		ofstream out("output.txt");
		Node* root = 0;
		int a;
		while (scanf("%d", &a) == 1)
			paste(root, a);

		int value;
		int pathLength = findMaxPath(root, value);

		if (pathLength)
			deleteNode(root, 0, value);
		
		show(root, out);

		return 0;
	}
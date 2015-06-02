#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "btree.h"
#include "error.h"

#include <fstream>

using namespace std;

int main()
{
	srand((int)time(0));
	ifstream in("input.txt");
	ofstream out("output.txt");
	try{
		BTree<int, int> bt; // why??
		
		for (int i = 0; i < 5000; ++i) {
			int k = rand() % 1000;
			bt.insert(k, k);
		}
		
		Vector<String> v  = bt.toVectorString();
		
		for (Vector<String>::Iterator it = v.begin(); it != v.end(); ++it)
			out << setw(2) << *it;
		out << "\n\n";

		for (BTree<int, int>::Iterator it = bt.begin(); it != bt.end(); ++it)
		{
		//	cout << setw(3) << *it;
		}

		/*for (int i = 0; i < 50; ++i) {
			bt.remove(bt.min());
		}
		
		v  = bt.toVectorString();
		
		for (Vector<String>::Iterator it = v.begin(); it != v.end(); ++it)
			out << setw(2) << *it;*/

	} catch (Error &e) {
		cout << "Error:\t" << e.what();
	}
	cout << '\n';
	system("pause");
	return 0;
}
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

#define MAXSIZE 250100
#define MAXREASONABLESUM 1500012 // 250000 * 6

int main () {
	ios_base::sync_with_stdio(false);
	ofstream in("in.txt");
 	
 	srand (time(NULL));

	int n = 100;
	in << n << endl;
	for (int i = 0; i < n; ++i) {
		in << rand() % 7 << " " << rand() % 7 << endl;
	}
}
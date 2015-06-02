#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath> 
#include <vector>
#include <map>

using namespace std;

int main()
{
    vector<int> v;
    stack<double> s1;
    stack<double, vector<double>> s2;

    list<int> l;
    list<int>::iterator it; // we can change list to vector, or deque

    for (it = l.begin(); it != l.end(); ++it) {
    	cout << *it << " ";
    }

	return 0;
}
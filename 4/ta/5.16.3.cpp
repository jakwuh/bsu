#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector< vector< vector< vector< ll > > > > Container;

int main() {
	int length = 4;

	Container container;
	container.resize(length);
	
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			for (int k = 0; k < 7; ++k)
			{
				container[i][j][k] = vector<ll>();
			}
		}
	}
}
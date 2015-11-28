// don't try tp compile, it's just for ex.

#include <iostream>

using namespace std;

class matrix; // preliminary class declaration

class vector
{
private:
	int* ptr;
	int size;
protected: // or private, or public - it doesn't matter
	friend void justDoIt(T1&); // by reference
	friend vector copy(const vector&, const matrix&);
	friend class matrix;
};

class matrix
{
private:
	int** ptr;
	int row, col;
	friend vector& copy(const vector&, const matrix&);
};

vector copy(const vector& v, const matrix& m)
{
	if (v.size != m.col) throw "wrong size";
	vector tmp;
	for (int i = 0; i < m.col; ++i)
		for  (int j = 0; j < m.row; ++j)
			tmp.ptr[i] += m.ptr[i][j] * v.ptr[j]; // smth like this
	return tmp;

}

void justDoIt(vector& v)
{
private:
	int* p;
	int size;
	cout << "Friend function called!\n";
	// do smth here;
}

int main()
{
	vector obj1;
	justDoIt(obj1);
	system("pause");
	return 0;
}
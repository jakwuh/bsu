#include <iostream>
using namespace std;
struct Bad_index {};
struct Bad_dimensions {};

class matrix
{	
public:
	int** p;
	matrix();
	long	m, n;                    
	matrix(long _m, long _n);
	matrix(const matrix& ma);
	~matrix();	
	matrix& operator = (const matrix& ma);
	int* operator [] (int i);			
	const int* operator [] (int i) const;
	matrix& operator +=(const matrix& ma);
	matrix& operator -=(const matrix& ma);
	matrix& operator *=(const matrix& ma);
	int fullsum();            
	int colsum( long o );            
	matrix& delrow( int o);          
	friend matrix operator *(const int, const matrix& ma);
	friend matrix operator *(const matrix& m, const int d);
	friend matrix operator +(const matrix& m1, const matrix& m2);	 
	friend matrix operator -(const matrix& m1, const matrix& m2);
	friend matrix operator *(const matrix& m1, const matrix& m2);
	friend ostream& operator << (ostream &out,const matrix &ma);
	friend istream& operator >> (istream &in, matrix &ma);
};

matrix::matrix()
{
	m = 10;
	n = 10;
	p = new int* [m];
	for (int i = 0; i < m; i++)
		p[i] = new int [n];
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			p[i][j] = 0;
}
                   
matrix::matrix(long _m, long _n)
{
	m = _m;
	n = _n;
	p = new int* [m];
	for (int i = 0; i < m; i++)
		p[i] = new int [n];
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			p[i][j] = i+j;
}
matrix::matrix(const matrix& ma)
{
	m = ma.m;
	n = ma.n;
	p = new int* [m];
	for (int i = 0; i < m; i++)
		p[i] = new int [n];
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			p[i][j] = ma.p[i][j];
}
	matrix::~matrix();		
{
	for (int i = 0; i < m; i ++)
		delete [] ma[i];
	delete [] ma;
	m = 0;
	n = 0;
}
matrix& matrix::operator = (const matrix& ma)
{
	m = ma.m;
	n = ma.n;
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			p[i][j] = ma.p[i][j];
	return *this;
}

int* matrix::operator [] (int i)
{   if(i>=n||i<0)throw Bad_index();	
		return p[i];
}
const int* matrix::operator [] (int i) const
{   if(i>=n||i<0)throw Bad_index();	
	return p[i];
}
matrix& matrix::operator +=(const matrix& ma)
{
	if(( m == ma.m ) && ( n == ma.n ))
	{
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				p[i][j] += ma.p[i][j];
	}
	else cout << "Invalid Matrix Parameters" << endl;
	return *this;
}
matrix& matrix::operator -=(const matrix& ma)
{
	if(( m == ma.m ) && ( n == ma.n ))
	{
		for(int i = 0; i < m; i++)
			for(int j = 0; j < n; j++)
				p[i][j] -= ma.p[i][j];
	}
	else cout << "Invalid Matrix Parameters" << endl;
	return *this;
}
matrix& matrix::operator *=(const matrix& ma)
{
	if(n == ma.m )            
	{											   				   
			for(int j = 0; j < n; j++)	
				for(int k = 0; k < m; k++)
				{
					p[k][j] = 0;
					for(int t = 0; t < n; t++)
						p[k][j]+= p[k][t] * ma.p[t][k];
				}
	}
	else cout << "Invalid Matrix Parameters" << endl;
	return *this;
}
int matrix::fullsum()
{
	int S = 0;
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			S+= p[i][j];
	return S;
}
int matrix::colsum( long o )
{
	int S = 0;
	for(int i = 0; i < m; i++)
		S+=p[i][o];
	return S;
}

matrix& matrix::delrow( int o )
{
	for(int i = o; i < m; i++)
		for(int j = 0; j < n; j++)
			p[i][j] = p[i+1][j];
	delete[] p[m];
	return *this;
}
 matrix operator *(const int d, const matrix& ma)
 {
	matrix M(ma);
	for(int i = 0; i < ma.m; i++)
		for(int j = 0; j < ma.n; j++)
			M.p[i][j]*= d;
	return M;
}
 matrix operator *(const matrix& ma, const int d)
 {
	matrix M(ma);
	for(int i = 0; i < ma.m; i++)
		for(int j = 0; j < ma.n; j++)
			M.p[i][j]*= d;
	return M;
 }
 matrix operator +(const matrix& m1, const matrix& m2)
 {
	matrix M(m1);
	for(int i = 0; i < m1.m; i++)
		for(int j = 0; j < m1.n; j++)
			M.p[i][j] = m1.p[i][j] + m2.p[i][j];
	return M;
 }
 matrix operator -(const matrix& m1, const matrix& m2)
 {
	matrix M(m1);
	for(int i = 0; i < m1.m; i++)
		for(int j = 0; j < m1.n; j++)
			M.p[i][j] = m1.p[i][j] - m2.p[i][j];
	return M;
 }
 matrix operator *(const matrix& m1, const matrix& m2)
 {
	 matrix M(m1.m, m1.n);
	 for(int j = 0; j < m1.n; j++)
		 for(int k = 0; k < m1.m; k++)
		 {
			 for(int t = 0; t < m1.n; t++)
				 M.p[k][j]+= m1.p[k][t] * m2.p[t][k];
		 }
	return M;
 }
 ostream& operator << (ostream &out,const matrix &ma)
 {
	for(int i = 0; i < ma.m; i++)
	{
		out <<"\n";
		for(int j = 0; j < ma.n; j++)
			out << ma.p[i][j] << "  ";
	}
	return out;
 }
istream& operator >> (istream &in, matrix &ma)
{  in >> ma.m;
   in >> ma.n;
	for(int i = 0; i < ma.m; i++)
	{
		for(int j = 0; j < ma.n; j++)
			in >> ma.p[i][j];
	}
	return in;
 }
void main()
{try
{
	matrix a(3,3), b(3,3);
	//cin>>a;
	matrix c=a;
	cout << c  << endl;
	b = c + a;
	cout << b << endl;
	int r=a[111][0];
	cout<<r<<endl;
}
catch(Bad_index )
{cout<<"error";
}
}
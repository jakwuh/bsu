#include <iostream>
using namespace std;
struct zero_divide{};
struct bad_index{};
class Complex
{
	double im,re;
public:
	Complex();
	Complex(double a,double b);
	friend istream & operator >> (istream &in,Complex &z);
	friend ostream & operator << (ostream &out,Complex &z);
	friend bool operator ==(const Complex &z1,const Complex &z2);
	friend bool operator >(const Complex &z1,const Complex &z2);
	friend Complex operator +(const Complex &z1,const Complex &z2);
	friend Complex operator *(const Complex &z1,const Complex &z2);
	friend Complex operator /(const Complex &z1,const Complex &z2);
	friend Complex operator -(const Complex &z1,const Complex &z2);
	Complex & operator =(const Complex &z1);
	Complex & operator +=(const Complex &z1);
	Complex & operator -();
	Complex & operator ++();
	Complex & operator ++(int);
	double operator [](const int &i);
	double mod();
	double arg();
	void show();
};
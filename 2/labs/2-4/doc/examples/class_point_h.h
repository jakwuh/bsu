#include <fstream>
using namespace std;
//Класс точка
#include <conio.h>
#include <iostream>
using namespace std;
class point
{  //protected:                 //Защищенные данные класса
	int x,y;                  //Координаты точки
 public:
	char *str;
	point();
	point(int p1 , int p2 );
	~point();
	point(const point&p);
	/*point & operator + (point &p);
	point & operator - (point &p);
	point & operator / (point &p);
	point & operator * (point &p);*/
	point & operator =(const point &p);
	point & operator =( int p);
	
	friend point operator + (point &p1, point &p2);
	friend point operator - (point &p1, point &p2);
	friend point operator * (point &p1, point &p2);
	friend point operator / (point &p1, point &p2);

	friend point operator + (int z, point &p2);
	friend point operator + (point &p1, int z);
	friend point operator - (int z, point &p2);
	friend point operator - (point &p1, int z);
	friend point operator * (int z, point &p2);
	friend point operator * (point &p1, int z);
	friend point operator / (int z, point &p2);
	friend point operator / (point &p1, int z);

	point& operator += (const point &p);
	point& operator -= (const point& r);
	point& operator *= (const point& r);
	point& operator /= (const point& r);

	point& operator += (int p);
	point& operator -= (int p);
	point& operator *= (int p);
	point& operator /= (int p);

	friend bool operator < (const point& p1, const point& p2);
	friend bool operator > (const point& p1, const point& p2);
	friend bool operator == (const point& p1, const point& p2);
	friend bool operator != (const point& p1, const point& p2);
	friend bool operator <= (const point& p1, const point& p2);
	friend bool operator >= (const point& p1, const point& p2);

	friend bool operator < (const point& p1, int p);
	friend bool operator > (const point& p1, int p);
	friend bool operator == (const point& p1, int p);
	friend bool operator != (const point& p1, int p);
	friend bool operator <= (const point& p1, int p);
	friend bool operator >= (const point& p1, int p);

	friend bool operator < (int p, const point& p2);
	friend bool operator > (int p, const point& p2);
	friend bool operator == (int p, const point& p2);
	friend bool operator != (int p, const point& p2);
	friend bool operator <= (int p, const point& p2);
	friend bool operator >= (int p, const point& p2);


	friend istream& operator>>(istream& in, point& p);
	friend ostream& operator<<(ostream& out, const point& p);

	friend point operator - (point &p);
	friend point operator + (point &p);
	//friend int operator - (int &p);
	//friend int operator + (int &p);
	//
	point operator ++(int k);
	point &operator ++();

	void print(point &p);
};

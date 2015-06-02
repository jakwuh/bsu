// интерфейс класса Fractionnal
#include <iostream.h>

struct Zero_divide {};

class Fraction
{
	long n, d;		// числитель и знаменатель
	void Reduce();	// сокращает дробь
public:
		// конструкторы
	Fraction();
	Fraction(long n, long d);
	Fraction(const Fraction& r);
		// оператор присваивания
	Fraction& operator = (const Fraction& r);
		// унарные операторы
	Fraction& operator += (const Fraction& r);
	Fraction& operator -= (const Fraction& r);
	Fraction& operator *= (const Fraction& r);
	Fraction& operator /= (const Fraction& r);
		// оператор преобразования типа
	operator double(void) const; 
		// унарный минус и плюс
	friend Fraction operator -(const Fraction& r);
	friend Fraction operator +(const Fraction& r);
		// операторы сравнения
	friend bool operator < (const Fraction& r1, const Fraction& r2);
	friend bool operator > (const Fraction& r1, const Fraction& r2);
	friend bool operator == (const Fraction& r1, const Fraction& r2);
	friend bool operator != (const Fraction& r1, const Fraction& r2);
	friend bool operator <= (const Fraction& r1, const Fraction& r2);
	friend bool operator >= (const Fraction& r1, const Fraction& r2);
		// бинарные операторы
	friend Fraction operator + (const Fraction& r1, const Fraction& r2);
	friend Fraction operator - (const Fraction& r1, const Fraction& r2);
	friend Fraction operator * (const Fraction& r1, const Fraction& r2);
	friend Fraction operator / (const Fraction& r1, const Fraction& r2);
		// операторы ввода-вывода
	friend istream& operator>>(istream& in, Fraction& r);
	friend ostream& operator<<(ostream& out, const Fraction& r);

};
	
		



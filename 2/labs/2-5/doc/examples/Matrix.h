// интерфейс класса matrix

struct Bad_dimensions {};

class matrix
{
	long	n, m;	// размерности матрицы
	double*	p;		// указатель на матрицу
	matrix();		// по умолчанию матрицу создавать нельзя
public:
		// конструкторы
	matrix(long _n, long _m);
	matrix(const matrix& m);
		// деструктор
	~matrix();
		// оператор присваивания
	matrix& operator = (const matrix& m);	// throw Bad_dimensions
		// оператор индексирования
	double* operator [] (long i);
	const double* operator [] (long i) const;
		// унарные операторы
	matrix& operator += (const matrix& m);	// throw Bad_dimensions
	matrix& operator -= (const matrix& m);	// throw Bad_dimensions
	matrix& operator *= (const matrix& m);	// throw Bad_dimensions
	matrix& operator *= (const double& d);
		// унарные операторы
	friend matrix operator -(const matrix& m);
	friend matrix operator +(const matrix& m);
		// бинарные операторы
	friend matrix operator * (const double& d, const matrix& m);
	friend matrix operator * (const matrix& m, const double& d);
		// следующие бинарные операторы 
		// могут выбросить исключение Bad_dimensions
	friend matrix operator + (const matrix& m1, const matrix& m2);	 
	friend matrix operator - (const matrix& m1, const matrix& m2);
	friend matrix operator * (const matrix& m1, const matrix& m2);
};

// исключения
struct BadDimensions {};
struct BadFirstIndex {};
struct BadSecondIndex {};

// интерфейс класса matrix
class matrix
{
	long	n, m;	// размерности матрицы
	double*	p;		// указатель на матрицу
	matrix();
	class row
	{
		long	m;	// размерность строки
		double* p;	// указатель на строку
	public:
		row(long _m, double* _p);
			// оператор индексирования
		double& operator [] (long j);				// throw BadFirstIndex
		const double& operator [] (long j) const;	// throw BadSecondIndex
	};
public:
		// конструкторы
	matrix(long _n, long _m);
	matrix(const matrix& m);
		// деструктор
	~matrix();
		// оператор присваивания
	matrix& operator = (const matrix& m);	// throw BadDimensions
		// оператор индексирования
	row operator [] (long i);				// throw BadFirstIndex
	const row operator [] (long i) const;	// throw BadFirstIndex
		// унарные операторы
	matrix& operator += (const matrix& m);	// throw BadDimensions
	matrix& operator -= (const matrix& m);	// throw BadDimensions
	matrix& operator *= (const matrix& m);	// throw BadDimensions
	matrix& operator *= (const double& d);
		// унарные операторы
	friend matrix operator -(const matrix& m);
	friend matrix operator +(const matrix& m);
		// бинарные операторы
	friend matrix operator * (const double& d, const matrix& m);
	friend matrix operator * (const matrix& m, const double& d);
		// следующие бинарные операторы 
		// могут выбросить исключение BadDimensions
	friend matrix operator + (const matrix& m1, const matrix& m2);	 
	friend matrix operator - (const matrix& m1, const matrix& m2);
	friend matrix operator * (const matrix& m1, const matrix& m2);
};
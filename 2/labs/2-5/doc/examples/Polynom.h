// интерфейс класса Polynom

struct Polynom_exceptions {};
struct Zero_divide: Polynom_exceptions {};
struct Negative_degree: Polynom_exceptions {};
struct Wrong_index: Polynom_exceptions {};

class Polynom
{
	int		n;		// степень полинома
	double*	coeff;	// коэффициенты полинома
		// конструктор по умолчанию
	Polynom();
public:
		// конструкторы
	Polynom(int _n, ...);		// throw(Negative_degree)
	Polynom(const Polynom& p);
		// деструктор
	~Polynom();
		// вычисление значения полинома
	double Value(double x);
		// оператор присваивания
	Polynom& operator = (const Polynom& p);
		// операторы индексировнаия
	double& operator [](int i) const;		// throw(Wrong_index)
		// унарные операторы
	Polynom& operator += (const Polynom& p);
	Polynom& operator -= (const Polynom& p);
	Polynom& operator *= (const Polynom& p);
	Polynom& operator /= (const Polynom& p);	// throw(Zero_divide)
		// унарный минус и плюс
	Polynom& operator -(void);
	Polynom& operator +(void);
		// бинарные операторы
	friend Polynom operator + (const Polynom& p1, const Polynom& p2);
	friend Polynom operator - (const Polynom& p1, const Polynom& p2);
	friend Polynom operator * (const Polynom& p1, const Polynom& p2);
	friend Polynom operator / (const Polynom& p1, const Polynom& p2);// throw(Zero_divide)
};
	
		



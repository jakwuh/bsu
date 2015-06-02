#include "iostream"

using namespace std;

class Derived : public Base
{
private:
	cls obj;
public:
	Derived();
	Derived(Derived const&); // object not constructed yet
	virtual ~Derived(); // must be virtual for proper destruction
	Derived& operator = (Derived const&); // object was constructed
};

inline Derived::Derived() : Base(), obj() // Base class construction only in initializer list
{
}

inline Derived::Derived(Derived const& d) : Base(d) // we can use Derived to initialize Base (by copy constructor)
{
}

Derived& Derived::operator = (Derived const& d)
{
	if (this != &d)
	{
		*((Base*)this) = d;
		obj = d.obj;
	}
	return *this;
}

// My [isocpp] implementation
// Derived& Derived::operator = (Derived const& d)
// {
// 		Base::operator = (d);
// 		d.obj = obj;
// 			return *this;
// }

int main()
{

	system("pause");
}
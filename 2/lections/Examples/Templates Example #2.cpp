#include <iostream>

static const M_PI = 3.141592653589

using namespace std;

template <typename K, typename V>
double square(K x, K y, V r)
{
    return M_PI * r * r;
}

void f(int n, ...); // it's impossible to generate functions with different signatures
// then we need to add additional parameter like
// void f(int n, T t, ...);

template <typename T, int size>
class MyArr
{
    T M[size];
public:
    static int i;
};
// template <typename T> int MyArr<T>::i = 0;
// MyArr<double, 20> myarr;

int main()
{

    system("pause");
    return 0;
}
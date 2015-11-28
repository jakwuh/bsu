#include <iostream>

using namespace std;

template <typename T>
class Sum
{
private:
    T x;
    Sum(){}
public:
    Sum(T x1) : x(x1){};
    Sum (Sum const& s) : x(s.x){};
    Sum& operator = (Sum const& s)
    {
        if (this != &s) {
            x = s.x;
        }
        return *this;
    }
    friend Sum operator + (Sum const& s1, Sum const& s2)
    {
        Sum s(s1.x);
        s.x = s.x + s2.x;
        return s;
    }
    template <typename K>
    friend ostream& operator << (ostream&, Sum<K>);
};

template <typename K>
ostream& operator << (ostream& out, Sum<K> s)
{
    out << (s.x) << endl;
    return out;
}


int main()
{
    Sum<int> a(1), b(2), c(3);
    cout << (a + b);

    system("pause");
    return 0;
}
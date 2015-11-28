#include <iostream>
#include <string>

using namespace std;

template <typename T> // template <class T>
void inc(T& t1)
{
    ++t1;
}

void inc(std::string& s)
{
    s += "a";
}

int main()
{   
    int a = 5;
    double b = 6;
    string s = "";
    inc(a);
    inc(b);
    inc(s);
    cout << a << ' ' << b << ' ' << s << endl;

    system("pause");
    return 0;
}
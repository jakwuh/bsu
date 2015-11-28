#include "iostream"

using namespace std;

class Abstract // complete Interface
{
private:
public:
    virtual void sum1(Abstract*, Abstract*) = 0;
    virtual void sum2(Abstract&, Abstract&) = 0;
    virtual void print() = 0;
};

class Integer : public Abstract
{
private:
    int x;
public:
    Integer(int _x = 0) : Abstract(), x(_x){};
    virtual void sum1(Abstract* a, Abstract* b) // virtual is redundant
    {
        Integer* ai = static_cast<Integer*>(a);
        Integer* bi = static_cast<Integer*>(b);
        x = ai->x + bi->x;
    }
    void sum2(Abstract& a, Abstract& b)
    {
        // Integer* ai = static_cast<Integer*>(&a);
        // Integer* bi = static_cast<Integer*>(&b);
        // x = ai->x + bi->x;
        Integer& ai = *(static_cast<Integer*>(&a));
        Integer& bi = *(static_cast<Integer*>(&b));
        x = ai.x + bi.x;
    }
    void print()
    {
        cout << "\nInteger: " << x;
    }
};

class Double : public Abstract
{
private:
    double x;
public:
    Double(double _x = 0) : Abstract(), x(_x){};
    void sum1(Abstract* a, Abstract* b)
    {
        Double* ad = static_cast<Double*>(a);
        Double* bd = static_cast<Double*>(b);
        // x = (*ad).x + (*bd).x;
        x = ad->x + bd->x;
    }
    void sum2(Abstract& a, Abstract& b)
    {
        Double* ad = static_cast<Double*>(&a);
        Double* bd = static_cast<Double*>(&b);
        x = ad->x + bd->x;
    }
    void print()
    {
        cout << "\nDouble: " << x;
    }
};


int main()
{
    Integer a(5), b(6), c;
    c.sum1(&a, &b);
    c.sum2(a, b);
    c.print();

    Abstract *a_ptr = &a, *b_ptr = &b, *c_ptr = &c; // we can do this way
    c_ptr->sum1(a_ptr, b_ptr);
    c_ptr->sum2(*a_ptr, *b_ptr); // because a_ptr is adress of Integer
    c_ptr->print();
    
    Double ad(5.5), bd(7.2), cd;
    a_ptr = &ad;
    b_ptr = &bd;
    c_ptr = &cd;

    c_ptr->sum1(a_ptr, b_ptr);
    c_ptr->sum2(*a_ptr, *b_ptr); // because a_ptr is adress of Integer
    c_ptr->print();
    
    cout << endl;
    system("pause");
    return 0;
}

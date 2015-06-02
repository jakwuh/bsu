#include <iostream>
#include <stdexcept>

template <typename T>
class Iterator;

template <typename T>
class Stack
{
    friend Iterator<T>;
private:
    struct Node
    {
        Node(T _data, Node* _next) : data(_data), next(_next){};
        T data;
        Node* next;
    };
    Node* head;
public:
    Stack();
    Stack(Stack const&);
    ~Stack();
    void pop();
    void push(T const&);
    T& top() const;
    Iterator<T> begin();
    Iterator<T> end();
};

template <typename T>
Stack<T>::Stack()
{
    head = 0;
}

template <typename T>
Stack<T>::Stack(Stack<T> const& st)
{
    Node *tmp = st.head;
    while (tmp) {
        push(tmp->data);
        tmp = tmp->next;
    }
}


template <typename T>
Stack<T>::~Stack()
{
    while (head)
        pop();
}

template <typename T>
void Stack<T>::push(T const& t)
{
    head = new Node(t, head);
}

template <typename T>
void Stack<T>::pop()
{
    if (!head) throw std::runtime_error("Stack<T>::pop: empty stack");
    Node* tmp = head;
    head = head->next;
    delete tmp;
}

template <typename T>
T& Stack<T>::top() const
{
    if (!head) throw std::runtime_error("Stack<T>::pop: empty stack");
    return head->data;
}

template <typename T>
Iterator<T> Stack<T>::begin()
{
    return head;
}

template <typename T>
Iterator<T> Stack<T>::end()
{
    return 0;
}

template <typename T>
class Iterator
{
    friend Iterator Stack<T>::begin();
    friend Iterator Stack<T>::end();
private:
    Iterator(){};
    Iterator(typename Stack<T>::Node*);
    typename Stack<T>::Node* c;
    // Stack<T>::Node c;
public:
    Iterator& operator ++();
    Iterator operator ++( int );
    Iterator& operator = (Iterator const&);
    // bool operator bool();
    T& operator * () const;
    bool operator == (Iterator const&);
    bool operator != (Iterator const&);
};

template <typename T>
Iterator<T>::Iterator(typename Stack<T>::Node *_c)
{
    c = _c;
}

template <typename T>
Iterator<T>& Iterator<T>::operator ++ ()
{
    if (!c) throw std::runtime_error("Stack::Iterator: empty Node");
    c = c->next;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator ++ (int)
{
    Iterator it(*this);
    operator ++ ();
    return it;
}

template <typename T>
T& Iterator<T>::operator * () const
{
    if (!c) throw std::runtime_error("Stack::Iterator: empty Node");
    return c->data;
}

template <typename T>
bool Iterator<T>::operator == (Iterator<T> const& it)
{
    return (it.c == c);
}

template <typename T>
bool Iterator<T>::operator != (Iterator<T> const& it)
{
    return !(operator == (it));
}

template <typename T>
Iterator<T>& Iterator<T>::operator = (Iterator<T> const& it)
{
    c = it.c;
    return *this;
}

template class Stack<int>;

using namespace std;

int main()
{
    try
    {
        Stack<int> fr;
        Stack<int> st();
        // Stack<int> st;

        for (int i = 0; i < 10; ++i)
            st.push(i);

        for (int i = 0; i < 10; ++i) {
            cout << st.top();
            st.pop();
        }

        for (int i = 0; i < 10; ++i)
            st.push(i);

        cout << endl;
        for (Iterator<int> it = st.begin(); it != st.end(); ++it) {
            cout << *it << ' ';     
        }
        cout << endl;
    } catch (...) {
        cout << "\nError";
    }
    
    return 0;

}
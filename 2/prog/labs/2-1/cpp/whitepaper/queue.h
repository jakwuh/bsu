struct Item {
    int x, y;
    struct Item* next;
};

class Queue {
private:
    struct Item* head, *tail;

public:
    Queue();
    ~Queue();
    void push(int x, int y);
    void peek(int& x, int& y);
    void pop(int& x, int& y);
    bool isEmpty();
};
#ifndef __CHAINEDQUEUE_H_INCLUDED__
#define __CHAINEDQUEUE_H_INCLUDED__

struct Empty{};
struct Full{};

class ChainedQueue
{
private:
	int	size, head, n;
	int *p;
public:
	ChainedQueue(int);
	ChainedQueue(const ChainedQueue&);
	~ChainedQueue();
	const int& peek();
	void push(int);
	void pop();
	bool isEmpty();
	bool isFull();
};

#endif
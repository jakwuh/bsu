#include "generator.h"

bool checkExit(bool ** M, int n, int m)
{
	bool ** a = new bool* [n];
	for (int i = 0; i < n; ++i) 
	{
		a[i] = new bool [m];
		for (int j = 0; j < m; ++j)
			a[i][j] = M[i][j];
	}

	ArrayStack<Point> s(n * m);
	Point p(0, 0);
	if (a[0][0])
		s.push(p);


	while (!s.isEmpty())
	{
		p = s.peek();
		s.pop();
		if (p.i == n - 1 && p.j == m - 1)
			return true;
		if (p.i > 0 && a[p.i - 1][p.j]){
			s.push(Point(p.i - 1, p.j));
			a[p.i - 1][p.j] = 0;
		} if (p.i < n - 1 && a[p.i + 1][p.j]){
			s.push(Point(p.i + 1, p.j));
			a[p.i + 1][p.j] = 0;
		} if (p.j > 0 && a[p.i][p.j - 1]){
			s.push(Point(p.i, p.j - 1));
			a[p.i][p.j - 1] = 0;
		} if (p.j < m - 1 && a[p.i][p.j + 1]){
			s.push(Point(p.i, p.j + 1));
			a[p.i][p.j + 1] = 0;
		}
	}
	return false;
}

void generateMaze(bool ** M, int n, int m)
{
	srand(time(0));
	int i, j, r;
	int cellsCount = n * m - 2;
	int blockCount = 0;
	int cellsRate = 250;
	bool ** changes = new bool* [n * m / cellsRate + 1];
	int t;
	while (blockCount < 5)
	{
		t = 0;
		for (int k = 0; k < cellsCount / cellsRate + 1; ++k)
		{
			r = rand() % cellsCount + 1;
			i = 0;
			j = 0;
			while (r--)
			{
				do {
					j++;
					if (j == m) 
					{
						j = 0;
						i++;
					}
					if (i == n) i = 0;
				} while (!M[i][j]);
			}
			changes[t++] = &M[i][j];
			M[i][j] = 0;
			cellsCount--;
		}
	
		if (!checkExit(M, n, m)){
			for (int i = 0; i < t; ++i)
			{
				*changes[i] = 1;
				cellsCount++;
			}
			blockCount++;
		}
	}
}

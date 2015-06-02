// Аквух Джеймс
// 11.02.2015
// Лист бумаги

#include <iostream>
#include <iomanip>
#include "queue.h"

using namespace std;

int main()
{	
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n, m, x, y;
	Queue * q = new Queue;
	scanf("%d %d", &n, &m);
	
	int ** cells;
	cells = new int * [n];
	
	for (int i = 0; i < n; ++i)
	{
		cells[i] = new int [m];
		for (int j = 0; j < m; ++j)
			scanf("%d", &cells[i][j]);
	}

	int k = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (cells[i][j] == 0) {
				k++;
				q->push(i, j);
				cells[i][j] = k;
			}
			while (!q->isEmpty())
			{
				q->pop(x, y);
				if (x > 0 && cells[x - 1][y] == 0){
					q->push(x - 1, y);
					cells[x - 1][y] = k;
				}
				if (y < m - 1 && cells[x][y + 1] == 0){
					q->push(x, y + 1);
					cells[x][y + 1] = k;
				}
				if (x < n - 1 && cells[x + 1][y] == 0){
					q->push(x + 1, y);
					cells[x + 1][y] = k;
				} 
				if (y > 0 && cells[x][y - 1] == 0){
					q->push(x, y - 1);
					cells[x][y - 1] = k;
				}
			}
			cout << setw(4) << cells[i][j] << ' ';
		}
		cout << endl; 
	}

	cout << endl << "k = " << k << endl;

    return 0;
}
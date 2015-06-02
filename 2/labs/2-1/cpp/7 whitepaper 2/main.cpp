// Аквух Джеймс
// 18.02.2015
// Лист бумаги рекурсивно

#include <iostream>
#include <vector>

using namespace std;

void rD(std::vector<std::vector<int>>& v, int i, int j, int k) {
	if (j < 0 || j >= v[0].size() || i >= v.size() || v[i][j]) return;
	v[i][j] = k;
	rD(v, i + 1, j, k);
	rD(v, i, j + 1, k);
	rD(v, i, j - 1, k);
}

int main() {
	// чтение
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m, k = 0;
	cin >> n >> m;
	std::vector<std::vector<int>> v(n, std::vector<int>(m));

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			scanf("%d", &v[i][j]);
	// конец чтения

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (!v[i][j]) rD(v, i, j, ++k);

	cout << "k = " << k << endl;
	
	system("pause");
    return 0;
}
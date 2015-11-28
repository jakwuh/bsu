#include "generator.h"
Generator::Generator(int _n, int _m)
{
	setParameters(_n, _m);
}

inline void Generator::setParameters(int _n, int _m)
{
	assert(_n >= 0);
	n = _n;
	m = _m > 0 ? _m : n;
}

/**
 * @brief fills the region with the number
 * @details tries to fill a random region with the number k.
 * starts filling from the cell[i][j] and randomly selects
 * new cells. Fills the region up to the count cells and ends up.
 * 
 * @param i defines starting cell coordinate
 * @param j defines starting cell coordinate
 * @param k defines the number the given region will be filled with
 * @param count
 * @param density 
 * @return number of filled cells
 */
int Generator::randomFill(int** a, Cell& first, int k, int count, int density)
{
	int real_count = count, tmp_i, tmp_j;
	::List<Cell> list, tmp_list;
	Cell* current_cell = 0;
	
	list.push_back(first);
	while (real_count > 0 && !list.empty()) {
		delete current_cell;
		if (rand() % 100 < density) {
			current_cell = new Cell(list.front());
			list.pop_front();
		} else {
			current_cell = new Cell(list.back());
			list.pop_back();
		}
		
		tmp_i = current_cell->i;
		tmp_j = current_cell->j;
		if (tmp_i > 0 && !a[tmp_i - 1][tmp_j])
			tmp_list.push_back(Cell(tmp_i - 1, tmp_j));
		if (tmp_i < n - 1 && !a[tmp_i + 1][tmp_j])
			tmp_list.push_back(Cell(tmp_i + 1, tmp_j));
		if (tmp_j > 0 && !a[tmp_i][tmp_j - 1])
			tmp_list.push_back(Cell(tmp_i, tmp_j - 1));
		if (tmp_j < m - 1 && !a[tmp_i][tmp_j + 1])
			tmp_list.push_back(Cell(tmp_i, tmp_j + 1));
		
		while (real_count > 0 && !tmp_list.empty()) {
			for (int i = 0; i < rand() % 8; ++i) {
				tmp_list.push_back(tmp_list.front());
				tmp_list.pop_front();
			}
			list.push_back(tmp_list.back());
			a[tmp_list.back().i][tmp_list.back().j] = k;
			real_count--;
			tmp_list.pop_back();
		}
	}
	return count - real_count;
}

/**
 * @brief generates map filled with numbers 1..k
 * @details uses deque(list) to separate
 * matrix on k distinct regions. The higher density param is the
 * less streched out will be regions. The lower deviation param
 * is the more different in sizes will be regions
 * 
 * @param k defines the number of regions the given matrix to be divided
 * @param density 0..100
 * @param deviation 0..1
 * @return
 */
int** Generator::generateMap(int k, int density, double deviation)
{
	assert(n > 0 && m > 0);

	int** a = new int* [n];

	for (int i = 0; i < n; ++i) {
		a[i] = new int[m];
		for (int j = 0; j < m; ++j)
			a[i][j] = 0;
	}

	std::srand((int)time(0));
	int average_count, current_count = 0, cells_count = n * m;
	int total_count = cells_count;
	int i = 0, j = 0;
	
	while (k) {
		average_count = cells_count / k;
		if (k == 1) 
			current_count = cells_count;
		else 
			current_count = average_count + (int) (deviation * (rand() % (2 * average_count) - average_count));
		if (current_count < 0) current_count = 0;
		cells_count -= current_count;
		
		assert(current_count > 0);
		while (current_count != 0) {
			while (a[i][j]) {
				assert(i < n);
				j++;
				if (j == m) {
					i++;
					j = 0;
				}
			}

			a[i][j] = k;
			current_count--;
			assert(current_count > -1);
			Cell tmp_cell = Cell(i, j);
			current_count -= randomFill(a, tmp_cell, k, current_count, density);
		}
		--k;
		std::cout << "\r" << (int)( 1000 * ( (total_count - cells_count) * 1. / total_count )) << " \\ 1000";
		// std::cout << "\r" << (total_count - cells_count) << " \\ " << total_count;
	}
	return a;
}

Map<Surface> Generator::generateSurface(int k, int density, double deviation, std::vector<Surface>& surfaces)
{
	int** tmp_map = generateMap(k, density, deviation);
	Surface** map = new Surface*[n];
	Surface* conformity = new Surface[k];

	for (int i = 0; i < k; ++i) 
		conformity[i] = surfaces[rand() % surfaces.size()];

	for (int i = 0; i < n; ++i) {
		map[i] = new Surface[m];
		for (int j = 0; j < m; ++j)
				map[i][j] = conformity[tmp_map[i][j] - 1];
	}

	for (int i = 0; i < n; ++i)
		delete[] tmp_map[i];	
	delete[] conformity;

	return Map<Surface>(n, m, map);
}
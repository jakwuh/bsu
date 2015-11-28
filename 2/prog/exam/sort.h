#ifndef __SORT_H_INCLUDED__
#define __SORT_H_INCLUDED__

template <typename T>
void shell_sort(T* &a, int n)
{
	T tmp;
	int k;
	for (int d = n / 2; d > 0; d /= 2) {
		for (int i = d; i < n; i += d) {
			k = i;
			tmp = a[i];
			while (k > 0 && a[k - d] > tmp) {
				a[k] = a[k - d];
				k -= d;
			}
			a[k] = tmp;
		}
	}
}

#endif
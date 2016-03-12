#include <stdio.h>
#include <stdlib.h>

#define MYINFINITY 2000000000
#define MAXREASONABLESUM 3000300 // 250000 * 12
#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

int main () {
	FILE *f = fopen("in.txt","r");
	int n, a, b, i, j, sum = 0;
	int* steps = (int*) malloc(sizeof(int) * MAXREASONABLESUM);
	for (i = 1; i < MAXREASONABLESUM; ++i) steps[i] = MYINFINITY;
	steps[0] = 0;
	fscanf(f,"%d", &n);

	int min = 0, max = 0;
	for (i = 0; i < n; ++i) {
		fscanf(f, "%i%i", &a, &b);
		for (j = max; j >= min; --j) {
			if (steps[j] != MYINFINITY) {
				int tmp = steps[j];
				steps[j] = MYINFINITY;
				if (tmp < steps[j + a]) steps[j + a] = tmp;
				if (tmp + 1 < steps[j + b]) steps[j + b] = tmp + 1;
			}
		}
		max += MAX(a, b);
		min += MIN(a, b);
	}
	fclose(f);
	sum = min + max;
	i = sum / 2;
	j = (sum + 1) / 2;
	while (steps[i] == MYINFINITY && steps[j] == MYINFINITY) {i--;j++;}
	f = fopen("out.txt","w");
	fprintf(f,"%i", MIN(steps[i], steps[j]));
	fclose(f);
}
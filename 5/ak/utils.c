#include <time.h>
#include <stdlib.h>

struct Profiler {
	double start;
	double end;
};

void printVector(long *v, long n) {
	for (long i = 0; i < n; ++i) {
		printf("%ld\t", v[i]);
	}
}

void printVector(double *v, long n) {
	for (long i = 0; i < n; ++i) {
		printf("%lf\t", v[i]);
	}
}

void printVectorAsMatrix(long* v, long n, long m) {
	for (long i = 0; i < n; ++i) {
		printVector(v + i * m, m);
		printf("\n");
	}
	printf("\n");
}

void printVectorAsMatrix(double* v, long n, long m) {
	for (long i = 0; i < n; ++i) {
		printVector(v + i * m, m);
		printf("\n");
	}
	printf("\n");
}

long* transposeVectorAsMatrix(long* v, long n, long m) {
	long *tv = (long*)malloc(sizeof(long) * n * m);
	for (long i = 0; i < n; ++i) {
		for (long j = 0; j < m; ++j) {
			tv[j * n + i] = v[i * m + j];
		}
	}
	return tv;
}

long* generateRandomVector(long n) {
	srand(time(NULL));
	long *v = (long*)malloc(sizeof(long) * n);
	for (long i = 0; i < n; ++i) {
		v[i] = rand() % 10;
	}
	return v;
}

double* generateDoubleRandomVector(long n) {
	srand(time(NULL));
	double *v = (double*)malloc(sizeof(double) * n);
	for (long i = 0; i < n; ++i) {
		v[i] = rand() % 100;
	}
	return v;
}

double realtime() {
	return clock() * 1. / CLOCKS_PER_SEC;
}
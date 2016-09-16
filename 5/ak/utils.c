struct Profiler {
	double start;
	double end;
};

void printVector(long *v, long n) {
	for (long i = 0; i < n; ++i) {
		printf("%ld\t", v[i]);
	}
}

void printVectorAsMatrix(long* v, long n, long m) {
	for (long i = 0; i < n; ++i) {
		printVector(v + i * m, m);
		printf("\n");
	}
	printf("\n");
}

long* transposeVectorAsMatrix(long* v, long n, long m) {
	long *tv = malloc(sizeof(long) * n * m);
	for (long i = 0; i < n; ++i) {
		for (long j = 0; j < m; ++j) {
			tv[j * n + i] = v[i * m + j];
		}
	}
	return tv;
}

long* generateRandomVector(n) {
	long *v = malloc(sizeof(long) * n);
	for (long i = 0; i < n; ++i) {
		v[i] = rand() % 10;
	}
	return v;
}

double realtime() {
	return clock() * 1. / CLOCKS_PER_SEC;
}
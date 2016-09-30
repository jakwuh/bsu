#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define ROOT 0

struct Profiler {
	double start;
	double end;
};

void printVector(long *v, long n);

void printVectorAsMatrix(long* v, long n, long m);

long* transposeVectorAsMatrix(long* v, long n, long m);

long* generateRandomVector(long n);

double realtime();

int main(int argc, char ** argv) {
	int rank, processesCount;
	long n, m, k, *A, *B, *AB = NULL;
	struct Profiler profiler;
	MPI_Status status;

	srand(time(0));

	profiler.start = realtime();

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &processesCount);

	if (rank == ROOT) {
		printf("Multiplying 2 random matrices...\n");
		printf("Enter dimensions (n, m, k): \n");	
		scanf("%ld %ld %ld", &n, &m, &k);
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&n, 1, MPI_LONG, ROOT, MPI_COMM_WORLD);
	MPI_Bcast(&m, 1, MPI_LONG, ROOT, MPI_COMM_WORLD);
	MPI_Bcast(&k, 1, MPI_LONG, ROOT, MPI_COMM_WORLD);

	bool shouldPrintMatrix = n < 10 && m < 10 && k < 10;
	long childRowsCount = n / processesCount;
	long rootRowsCount = childRowsCount + n % processesCount;

	if (rank == ROOT) {
		A = generateRandomVector(n * m);
		B = generateRandomVector(m * k); // transposed matrix for simplier multiplication
		AB = malloc(sizeof(long) * n * k);

		if (shouldPrintMatrix) {
			printf("Matrix A:\n");
			printVectorAsMatrix(A, n, m);
			printf("Matrix B:\n");
			printVectorAsMatrix(transposeVectorAsMatrix(B, k, m), m, k);
		}
	} else {
		A = malloc(sizeof(long) * childRowsCount * m);
		B = malloc(sizeof(long) * m * k);
	}

	MPI_Bcast(B, m * k, MPI_LONG, ROOT, MPI_COMM_WORLD);

	if (rank == ROOT) {
		long *buffer = A + rootRowsCount * m;
		for (long i = 1; i < processesCount; ++i) {
			MPI_Send(buffer, childRowsCount * m, MPI_LONG, i, 0, MPI_COMM_WORLD);
			buffer += childRowsCount * m;
		}
	} else {
		MPI_Recv(A, childRowsCount * m, MPI_LONG, ROOT, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	}

	long rowsCount, *C;
	if (rank == ROOT) {
		rowsCount = rootRowsCount;
		C = AB;
	} else {
		rowsCount = childRowsCount;
		C = malloc(sizeof(long) * rowsCount * k);
	}

	for (long i = 0; i < rowsCount; ++i) {
		long *row = A + i * m;
		for (long j = 0; j < k; ++j) {
			long *column = B + j * m;
			long s = 0;
			for (long l = 0; l < m; ++l) {
				s += row[l] * column[l];
			}
			C[i * k + j] = s;
		}
	}

	MPI_Barrier (MPI_COMM_WORLD);

	if (rank == ROOT) {
		long *C = malloc(sizeof(long) * childRowsCount * k);
		for (long i = 1; i < processesCount; ++i) {
			MPI_Recv(C, childRowsCount * k, MPI_LONG, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			long offset = rootRowsCount * k + (i - 1) * childRowsCount * k;
			long count = childRowsCount * k;
			memcpy(AB + offset, C, childRowsCount * k * sizeof(long));
		}
		profiler.end = realtime();
		if (shouldPrintMatrix) {
			printf("Matrix A * B:\n");
			printVectorAsMatrix(AB, n, k);
		}
		printf("Execution time: %.3lfs\n", profiler.end - profiler.start);
	} else {
		MPI_Send(C, childRowsCount * k, MPI_LONG, ROOT, 0, MPI_COMM_WORLD);
	}


	MPI_Finalize();
}

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

double realtime() {
	return clock() * 1. / CLOCKS_PER_SEC;
}

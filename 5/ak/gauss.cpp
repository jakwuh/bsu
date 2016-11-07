#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <cmath>

#define ROOT 0
#define DEBUG 1

struct Profiler {
    double start;
    double end;
};

void printVector(double *v, long n);

void printVectorAsMatrix(double* v, long n, long m);

double* generateDoubleRandomVector(long n);

double realtime();

void printResidual(double* A, double* AD, long n);

int main(int argc, char ** argv) {
	int rank, processesCount;
	long n;
	double *A, *copyA;
	struct Profiler profiler;
	MPI_Status status;

	profiler.start = realtime();

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &processesCount);

	if (rank == ROOT) {
		std::cout << "Gaussian elimination." << std::endl;
		std::cout << "Enter number of rows in matrix (n): " << std::endl;
		std::cin >> n;
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&n, 1, MPI_LONG, ROOT, MPI_COMM_WORLD);

	bool shouldPrintMatrix = n < 10;
	long childRowsCount = n / processesCount;
	long rootRowsCount = childRowsCount + n % processesCount;
	long m = n + 1;

	if (rank == ROOT) {
		A = generateDoubleRandomVector(n * m);
		if (DEBUG) {
			// this should run only in debug since it affects profiling
			copyA = new double[n * m];
			memcpy(copyA, A, n * m * sizeof(double));
		}

		if (shouldPrintMatrix) {
			std::cout << "Initial matrix: " << std::endl;
			printVectorAsMatrix(A, n, m);
		}

		double *buffer = A + rootRowsCount * m;
		for (long i = 1; i < processesCount; ++i) {
			MPI_Send(buffer, childRowsCount * m, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
			buffer += childRowsCount * m;
		}
	} else {
		A = new double[childRowsCount * m];
		MPI_Recv(A, childRowsCount * m, MPI_DOUBLE, ROOT, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	}

	double *v = new double[m];
	
	long row = 0;
	for (int i = 0; i < processesCount; ++i) {
		long rowsCount = (i == 0 ? rootRowsCount : childRowsCount);
		for (long j = 0; j < rowsCount; ++j) {
			if (rank == i) {
				memcpy(v, A + j * m, sizeof(double) * m);
			}
			
			MPI_Bcast(v, m, MPI_DOUBLE, i, MPI_COMM_WORLD);

			long selfRowsCount = (rank == 0 ? rootRowsCount : childRowsCount);
			for (long k = 0; k < selfRowsCount; ++k) {
				double coef;
				if (rank == i && k == j) {
					coef = (1 - A[k * m + row]) * 1. / v[row];
				} else {
					coef = - A[k * m + row] * 1. / v[row];
				}
				for (long l = 0; l < m; ++l) {
					A[k * m + l] += coef * v[l];
				}
			}
			++row;
		}		
	}

	MPI_Barrier (MPI_COMM_WORLD);

	if (rank == ROOT) {
		double *dA = new double[childRowsCount * m];
		for (long i = 1; i < processesCount; ++i) {
			MPI_Recv(dA, childRowsCount * m, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			long offset = (rootRowsCount + (i - 1) * childRowsCount) * m;
			memcpy(A + offset, dA, childRowsCount * m * sizeof(double));
		}

		profiler.end = realtime();
		if (shouldPrintMatrix) {
			printf("Canonical matrix:\n");
			printVectorAsMatrix(A, n, m);
		}
		if (DEBUG) {
			printResidual(copyA, A, n);
		}
		printf("Execution time: %.3lfs\n", profiler.end - profiler.start);
	} else {
		MPI_Send(A, childRowsCount * m, MPI_DOUBLE, ROOT, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}

void printVector(double *v, long n) {
    for (long i = 0; i < n; ++i) {
        printf("%lf\t", v[i]);
    }
}

void printVectorAsMatrix(double* v, long n, long m) {
    for (long i = 0; i < n; ++i) {
        printVector(v + i * m, m);
        printf("\n");
    }
    printf("\n");
}

double* generateDoubleRandomVector(long n) {
    srand(time(NULL));
    double *v = new double[n];
    for (long i = 0; i < n; ++i) {
        v[i] = rand() % 100;
    }
    return v;
}

void printResidual(double* A, double* AD, long n) {
	for (long i = 0; i < n; ++i) {
		double sum = 0;
		for (long j = 0; j < n; ++j) {
			sum += A[i * (n + 1) + j] * AD[n + (n + 1) * j];
		}
		sum = std::abs((double)(sum - A[i * (n + 1) + n]));
		std::cout << sum << ' ';
	}
}

double realtime() {
    return clock() * 1. / CLOCKS_PER_SEC;
}
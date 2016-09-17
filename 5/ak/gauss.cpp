#include <mpi.h>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include "./utils.c"

#define ROOT 0

int main(int argc, char ** argv) {
	int rank, processesCount;
	long n, m;
	double *A;
	struct Profiler profiler;
	MPI_Status status;

	profiler.start = realtime();

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &processesCount);

	if (rank == ROOT) {
		std::cout << "Gaussian elimination." << std::endl;
		std::cout << "Enter dimensions of an extended matrix (n, m): " << std::endl;
		std::cin >> n >> m;
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(&m, 1, MPI_LONG, ROOT, MPI_COMM_WORLD);
	MPI_Bcast(&n, 1, MPI_LONG, ROOT, MPI_COMM_WORLD);

	bool shouldPrintMatrix = n < 10 && m < 10;
	long childRowsCount = n / processesCount;
	long rootRowsCount = childRowsCount + n % processesCount;

	if (rank == ROOT) {
		A = generateDoubleRandomVector(n * m);

		if (shouldPrintMatrix) {
			std::cout << "Initial matrix: " << std::endl;
			printVectorAsMatrix(A, n, m);
		}

		double *buffer = A + rootRowsCount * m;
		for (long i = 1; i < processesCount; ++i) {
			MPI_Send(buffer, childRowsCount * m, MPI_LONG, i, 0, MPI_COMM_WORLD);
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
		printf("Execution time: %.3lfs\n", profiler.end - profiler.start);
	} else {
		MPI_Send(A, childRowsCount * m, MPI_DOUBLE, ROOT, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
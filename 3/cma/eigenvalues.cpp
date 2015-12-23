/**
 * @author James Akwuh <@jakwuh>
 * @description The purpose of the code is only to get calculation results.
 * Optimization, memory handling, etc. are ignored for simplicity.
 * (However there should be no memory leaks because of using vectors)
 */
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <math.h>

#define DEBUG false
#define EPS 1E-6
#undef minor

using namespace std;

typedef vector<double> Vector;
typedef vector<vector<double>> Matrix;

namespace operators {
	Vector operator+ (Vector a, Vector b) {
		for (int i = 0; i < a.size(); ++i) a[i] += b[i];
		return a;
	}
	Vector operator- (Vector a, Vector b) {
		for (int i = 0; i < a.size(); ++i) a[i] -= b[i];
		return a;
	}
	double operator* (Vector a, Vector b) {
		double x = 0;
		for (int i = 0; i < a.size(); ++i) x += a[i] * b[i];
		return x;
	}

	Matrix operator+ (Matrix a, Matrix b) {
		for (int i = 0; i < a.size(); ++i) a[i] = a[i] + b[i];
		return a;
	}
	Matrix operator- (Matrix a, Matrix b) {
		for (int i = 0; i < a.size(); ++i) a[i] = a[i] - b[i];
		return a;
	}
	Matrix operator*(Matrix a, Matrix b) {
		int n = a.size(), m = b.size(), k = b[0].size();
		if (m != a[0].size()) {throw "Matrix:operator*:dimensions differ";}
		Matrix c(n, Vector(k, 0));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < k; ++j) {
				for (int l = 0; l < m; ++l) c[i][j] += a[i][l] * b[l][j];
			}
		}
		return c;
	}
	Matrix operator*(Matrix a, double c) {
		for (int i = 0; i < a.size(); ++i) {
			for (int j = 0; j < a[0].size(); ++j) {
				a[i][j] *= c;
			}
		}
		return a;
	}
}

using namespace operators;
namespace generators {
	Matrix identity_matrix(int n) {
		Matrix a(n, Vector(n, 0));
		for (int i = 0; i < n; ++i) a[i][i] = 1;
		return a;
	}

	Matrix transpose(Matrix a) {
		Matrix b(a[0].size(), Vector(a.size(), 0));
		for (int i = 0; i < a.size(); ++i) {
			for (int j = 0; j < a[0].size(); ++j) b[j][i] = a[i][j];
		}
		return b;
	}

	Matrix transpose(Vector v) {
		Matrix a(1, v);
		return transpose(a);
	}

	Matrix inverse(Matrix a) {
		Matrix b = a;
		for (int i = 0; i < a.size(); ++i) {
			b[i].resize(a.size() * 2);
			b[i][i + a.size()] = 1;
		}
		for (int i = 0; i < b.size(); ++i) {
			for (int k = (i == 0 ? 1 : 0); k < b.size(); k += (k == i - 1 ? 2 : 1)) {
				double c = - b[k][i] / b[i][i];
				for (int j = 0; j < b[0].size(); ++j) b[k][j] += c * b[i][j];
			}
			for (int j = 0; j < b[0].size(); ++j) if (j != i) b[i][j] /= b[i][i];
			b[i][i] = 1;
		}
		for (auto it = b.begin(); it != b.end(); ++it) it->erase(it->begin(), it->begin() + a.size());
		return b;
	}

	Matrix minor(Matrix a, int i, int j) {
		a.erase(a.begin() + i);
		for (auto it = a.begin(); it != a.end(); ++it) it->erase(it->begin() + j);
		return a;
	}

	Matrix quad(Matrix a) {
		int n = min(a.size(), a[0].size());
		for(int i = n; i < a.size(); ++i) a.erase(a.begin() + i);
		a = transpose(a);
		for(int i = n; i < a.size(); ++i) a.erase(a.begin() + i);
		return transpose(a);
	}
}

using namespace generators;
namespace helpers {
	double sqr(double a){ return a*a;}

	double norm(Matrix a) {
		double x = 0;
		for (int i = 0; i < a.size(); ++i) {
			double tmp = 0;
			for (int j = 0; j < a[0].size(); ++j) {
				tmp += fabs(a[i][j]);
			}
			x = max(tmp, x);
		}
		return x;
	}

	double norm(Vector x) {
		double tmp = fabs(x[0]);
		for (int i = 0; i < x.size(); ++i) tmp = max(tmp, fabs(x[i]));
		return tmp;
	}

	double det(Matrix a) {
		if (a.size() == 1) return a[0][0];
		double x = 0;
		for (int j = 0, k = 1; j < a.size(); ++j, k *= -1) {
			Matrix m = minor(a, 0, j);
			x += k * a[0][j] * det(m);
		}
		return x;
	}

	bool silvester(Matrix a) {
		if (a.size() != a[0].size()) return false;
		for (int i = 0; i < a.size(); ++i) {
			for (int j = i + 1; j < a.size(); ++j) {
				if (a[i][j] != a[j][i]) return false;
			}
		}
		while (a.size() > 0) {
			if (det(a) < 0) return false;
			a.erase(a.begin() + a.size() - 1);
			for (auto it = a.begin(); it != a.end(); ++it) {it->erase(it->begin() + it->size() - 1);}
		}
		return true;
	}

	Matrix column(Matrix a, int j) {
		return transpose(transpose(a)[j]);
	}

	Matrix swap_rows(Matrix a, int i, int j) {
		swap(a[i], a[j]);
		return a;
	}

	Matrix swap_cols(Matrix a, int i, int j) {
		return transpose(swap_rows(transpose(a), i, j));
	}
}

using namespace helpers;
namespace io {

	void print(Vector v) {
		if (DEBUG)cout << "{";
		bool first = true;
		for (auto it : v) {
			if (DEBUG)if (!first) cout << ",";
			cout << (DEBUG ? std::fixed : std::scientific) << setprecision(4) << setw(DEBUG && first ? 13 : 14) << it;
			first = false;
		}
		cout << (DEBUG ? "}" : "") << endl;
	}

	void print(Matrix a) {
		int c = a.size();
		if (DEBUG) cout << "{";
		for (auto it : a) {
			print(it);
			if (DEBUG) cout << (--c > 0 ? "," : "}");
		}
		if (DEBUG) cout << endl;
	}

	void check(Matrix a, Vector x, Vector p, double lambda) {
		p.insert(p.begin(), -1);
		Matrix R1 = a * transpose(x) - transpose(x) * lambda;
		double R2 = 0, cc = 1;
		for (int i = 0; i < p.size(); ++i) {
			R2 += p[p.size() - i - 1] * cc;
			cc *= lambda;
		}

		cout << "Polynom coeffs:" << endl;
		print(p);
		cout << "lambda_max:" << endl;
		cout << lambda << endl;
		cout << "Eigenvector:" << endl;
		print(x);
		cout << "Matrix residual norm:" << endl;
		print(R1);
		cout << "Polynom residual:" << endl;
		cout << R2 << endl;
		cout << "Matrix residual norm:" << endl;
		cout << norm(R1) << endl << endl;
	}

	void check(Matrix a, Vector x, double lambda) {
		Matrix R1 = a * transpose(x) - transpose(x) * lambda;

		cout << "lambda_max:" << endl;
		cout << lambda << endl;
		cout << "Eigenvector:" << endl;
		print(x);
		cout << "Matrix residual:" << endl;
		print(R1);
		cout << "Matrix residual norm:" << endl;
		cout << norm(R1) << endl << endl;
	}
}

using namespace io;
namespace methods {
	Vector gauss(Matrix a) {
		Matrix ac(a);
		Vector xs(a.size());
		for (int i = 0; i < xs.size(); ++i) xs[i] = i;
		for (int i = 0; i < ac.size(); ++i) {
			double max = fabs(a[i][i]), maxI = i, maxJ = i;
			for (int l = i; l < ac.size(); ++l) {
				for (int m = i; m < ac.size(); ++m) {
					if (fabs(ac[l][m]) > max) {
						max = fabs(ac[l][m]);
						maxI = l;
						maxJ = m;
					}
				}
			}
			if (maxI != i) ac = swap_rows(ac, i, maxI);
			if (maxJ != i) ac = swap_cols(ac, i, maxJ);
			swap(xs[i], xs[maxJ]);

			for (int k = i + 1; k < ac.size(); ++k) {
				double c = - ac[k][i] / ac[i][i];
				for (int j = i; j < ac[0].size(); ++j) {
					ac[k][j] += c * ac[i][j];
				}
			}
			for (int j = ac[0].size() - 1; j >= i; --j) {
				ac[i][j] /= ac[i][i];
			}
		}
		Vector v(ac.size());
		for (int i = ac.size() - 1; i >= 0; --i) {
			v[xs[i]] = ac[i][ac[0].size()-1];
			for (int j = i + 1; j < ac.size(); ++j) {
				v[xs[i]] -= v[xs[j]] * ac[i][j];
			}
		}
		return v;
	}

	double power_iteration(Matrix a, double precision, bool doPrint = false) {
		int n = a.size();
		Matrix x, xk = transpose(Vector(n, 1));
		double eps = precision + 1, lambda, lambdak;
		bool first = true;
		while (eps > precision) {
			x = xk;
			xk = a * x;
			if (first) {
				first = false;
				continue;
			}
			lambda = lambdak;
			lambdak = 0;
			for (int i = 0; i < n; ++i) {
				lambdak += xk[i][0] / x[i][0] / n;
			}
			eps = abs(lambdak - lambda);
		}
		if (doPrint) {
			xk = xk * (1 / sqrt(norm(transpose(xk) * xk)));
			cout << "Power iteration method for max eigenvalue & eigenvector:" << endl;
			cout << "Given matrix:" << endl;
			print(a);
			cout << "Initial vector:" << endl;
			print(Vector(n, 1));
			cout << "Precision:" << endl;
			cout << eps << endl;
			check(a, transpose(xk)[0], lambda);
		}
		return lambdak;
	}

	void krilov(Matrix a) {
		int n = a.size();
		Matrix Y(n, Vector(n + 1, 0));
		for (int i = 0; i < n; ++i) Y[i][0] = 1;
		for (int i = 1; i <= n; ++i) {
			Matrix T = a * column(Y, i - 1);
			for (int j = 0; j < n; ++j) {
				Y[j][i] = T[j][0];
			}
		}
		Vector x = gauss(Y);
		double lambda = power_iteration(a, EPS);
		Vector q(n, 1);
		for (int i = 1; i < n; ++i) {
			q[i] = lambda * q[i - 1] - x[n - i];
		}
		Matrix X(n, Vector(1, 0));
		for (int i = 0; i < n; ++i) {
			X = X + column(Y, i) * q[n - i - 1];
		}
		X = X * (1 / sqrt(norm(transpose(X) * X)));
		cout << "Krilov method for eigenvalues:" << endl;
		cout << "Given matrix:" << endl;
		print(a);
		std::reverse(x.begin(), x.end());
		check(a, transpose(X)[0], x, lambda);
	}

	void danilevski(Matrix a) {
		int n = a.size();
		Matrix B, A(a), C = identity_matrix(n);
		for (int i = n - 2; i >= 0; --i) {
			B = identity_matrix(n);
			for (int j = 0; j < n; ++j) {
				if (j != i) {
					B[i][j] = -1 * A[i + 1][j] / A[i + 1][i];
				} else {
					B[i][j] = 1 / A[i + 1][i];
				}
			}
			C = C * B;
			A = inverse(B) * A * B;
		}
		double lambda = power_iteration(a, EPS);
		Matrix Y(n, Vector(1, 1));
		double vl = lambda;
		for (int i = 1; i < n; ++i) {
			Y[n - i - 1][0] = vl;
			vl *= lambda;
		}
		Matrix X = C * Y;
		X = X * (1. / sqrt(norm(transpose(X) * X)));
		cout << "Danilevski method for eigenvalues:" << endl;
		cout << "Given matrix:" << endl;
		print(a);
		cout << "Frobenius matrix:" << endl;
		print(A);
		check(a, transpose(X)[0], A[0], lambda);
	}

	double jacobi_eigenvalue(Matrix a, double precision) {
		double max = precision + 1;
		int imax, jmax, n = a.size(), k = 0;
		Matrix A(a);
		while (true) {
			k++;
			max = 0;
			imax = jmax = 0;
			for (int i = 0; i < n; ++i) {
				for (int j = i; j < n; ++j) {
					if (i != j && abs(A[i][j]) > max) {
						max = abs(A[i][j]);
						imax = i; jmax = j;
					}
				}
			}
			if (max < precision) break;
			double phi = 1. / 2 * atan(2 * A[imax][jmax] / (A[imax][imax] - A[jmax][jmax]));
			Matrix U = identity_matrix(n);
			U[imax][imax] = cos(phi);
			U[jmax][jmax] = cos(phi);
			U[imax][jmax] = -1 * sin(phi);
			U[jmax][imax] = sin(phi);
			A = transpose(U) * A * U;
		}
		Vector X(n);
		for (int i = 0; i < n; ++i) {
			X[i] = A[i][i];
		}
		cout << "Jacobi method for eigenvalues:" << endl;
		cout << "Given matrix:" << endl;
		print(a);
		cout << "Transformed matrix (" << k << " iterations):" << endl;
		print(A);
		cout << "Precision:" << endl;
		cout << max << endl;
		cout << "Eigenvalues:" << endl;
		print(X);
		cout << endl;
	}
}

using namespace methods;
int main(int argc, char *argv[]) {
	try	{
		if (argc == 2) {freopen (argv[1], "w", stdout);}
		Matrix a = {
			{0.4997, -0.0658, 0.0132, 0.0263, 0.0921},
			{0.0684, 0.7824, 0.0000, -0.0526, 0.0526},
			{0.0395, 0.0000, 0.6286, -0.1841, 0.1052},
			{-0.0789, 0.1657, 0.0000, 0.6181, -0.0263},
			{0.3288, 0.0000, 0.1184, 0.0132, 0.7364}
		};
		Matrix aq = a * transpose(a);
		krilov(aq);
		danilevski(aq);
		power_iteration(aq, EPS, true);
		jacobi_eigenvalue(aq, EPS);
		if (argc == 2) {fclose(stdout);}
	} catch (const char* error) {
		cout << error;
	}
}
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

#define DEBUG false
#define EPS 0.00001
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

	void check(Matrix a, Vector x) {
		Matrix aq = quad(a);
		Vector r = transpose(aq * transpose(x) - column(a, a.size()))[0];
		Matrix E = identity_matrix(a.size());
		Matrix R = aq * inverse(aq) - E;
		
		cout << "Matrix residual:" << endl;
		print(R);
		cout << "Solution residual:" << endl;
		print(r);
		cout << "Matrix residual norm:" << endl;
		cout << norm(R) << endl;
		cout << "Solution residual norm:" << endl;
		cout << norm(r) << endl;
		cout << "Condition number:" << endl;
		cout << norm(aq) * norm(inverse(aq)) << endl;
	}
}

using namespace io;
namespace methods {
	/**
	 * Gauss elimination method with complete pivoting.
	 * Solves & prints: given extended matrix, solution, vector residual,
	 * vector residual norm, matrix residual, matrix residual norm,
	 * inverse matrix, condition number
	 * @param a extended matrix
	 */
	void gauss_with_pivoting(Matrix a) {
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
		// solution residual
		Matrix aq = quad(a);
		Matrix r = transpose(aq * transpose(Matrix(1, v)) - transpose(Matrix(1, transpose(a)[a.size()])));
		// matrix residual
		Matrix E = Matrix(a.size(), Vector(a.size(), 0));
		for (int i = 0; i < a.size(); ++i){ E[i][i] =1; }
		Matrix R = aq * inverse(aq) - E;
		cout << "Gauss elimination method with complete pivoting:" << endl;
		cout << "Given matrix:" << endl;
		print(a);
		cout << "Triangulized matrix:" << endl;
		print(ac);
		cout << "Inverse matrix:" << endl;
		print(inverse(aq));
		cout << "Solution:" << endl;
		print(v);
		check(a, v);
		cout << endl;
	}

	/**
	 * Sweeping method for tridiagonal matrix.
	 * Solves & prints: given extended matrix, solution, vector residual,
	 * vector residual norm, matrix residual, matrix residual norm,
	 * condition number.
	 * Checks method sufficient conditions.
	 * @param a [description]
	 */
	void tridiagonal(Matrix matrix) {
		int n = matrix.size();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (abs(i - j) > 1) matrix[i][j] = 0;
			}
		}
		bool sufficient = true;
		bool sufficient_counter = 0;
		Vector f = transpose(matrix)[matrix.size()];
		Vector l(n), m(n), x(n), a(n), b(n), c(n);
		double sum;
		for (int i = 0; i < n; ++i) {
			sum = 0;
			if (i > 0) {a[i] = -matrix[i][i - 1]; sum += fabs(a[i]);}
			if (i < n - 1) {b[i] = -matrix[i][i + 1]; sum += fabs(a[i]);}
			c[i] = matrix[i][i];
			if (fabs(c[i]) > sum) ++sufficient_counter;
			if (fabs(c[i]) < sum) sufficient = false;
		}
		if (!sufficient_counter) sufficient = false;
		l[n - 1] = a[n - 1] / c[n - 1];
		m[n - 1] = f[n - 1] / c[n - 1];
		for (int i = n - 2; i >= 0; --i) {
			l[i] = a[i] / (c[i] - l[i + 1] * b[i]);
			m[i] = (f[i]+m[i + 1] * b[i]) / (c[i] - l[i + 1] * b[i]);
		}
		x[0] = m[0];
		for (int i = 1; i < n; ++i) {x[i] = l[i] * x[i - 1] + m[i];}
		// solution residual
		Matrix aq = matrix;
		for (auto it = aq.begin(); it != aq.end(); ++it){it->erase(it->begin() + it->size() -1);}
		Matrix r = transpose(aq * transpose(Matrix(1, x)) - transpose(Matrix(1, transpose(matrix)[matrix.size()])));
		// matrix residual
		Matrix E = Matrix(a.size(), Vector(a.size(), 0));
		for (int i = 0; i < a.size(); ++i){ E[i][i] =1; }
		Matrix R = aq * inverse(aq) - E;
		cout << "Sweeping method for tridiagonal matrix:" << endl;
		cout << "Given matrix:" << endl;
		print(matrix);
		cout << "Sufficient condition test:" << (sufficient ? " Passed" : " Failed") << endl;
		cout << "Solution:" << endl;
		print(x);
		check(matrix, x);
		cout << endl;
	}

	void square_root(Matrix a) {
		Matrix aq = quad(a);
		Matrix bq = transpose(aq) * aq;
		Matrix f = transpose(aq) * column(a, a.size());
		for (int i = 0; i < a.size(); ++i) {
			for (int j = 0; j <= a.size(); ++j) {
				a[i][j] = (j == a.size() ? f[i][0] : bq[i][j]);
			}
		}
		aq = quad(a);
		f = column(a, a.size());
		int n = a.size();

		Matrix s(n, Vector(n, 0));
		s[0][0] = sqrt(a[0][0]);
		for (int j = 1; j < n; ++j) {s[0][j] = a[0][j] / s[0][0];}
		for (int i = 1; i < n; ++i) {
			s[i][i] = a[i][i];
			for (int k = 0; k < i; ++k) {
				s[i][i] -= sqr(s[k][i]);
			}
			s[i][i] = sqrt(s[i][i]);

			for (int j = i + 1; j < n; ++j) {
				s[i][j] = a[i][j];
				for (int k = 0; k < i; ++k) {
					s[i][j] -= s[k][i] * s[k][j];
				}
				s[i][j] /= s[i][i];
			}
		}
		Vector y(n, 0);
		Vector x(n, 0);
		y[0] = f[0][0] / s[0][0];
		for (int i = 1; i < n; ++i) {
			y[i] = f[i][0];
			for (int j = 0; j < i; ++j) {
				y[i] -= s[j][i] * y[j];
			}
			y[i] /= s[i][i];
		}
		x[n - 1] = y[n - 1] / s[n - 1][n - 1];
		for (int i = n - 2; i >= 0; --i) {
			x[i] = y[i];
			for (int j = i + 1; j < n; ++j) {
				x[i] -= s[i][j] * x[j];
			}
			x[i] /= s[i][i];
		}

		Matrix E = Matrix(a.size(), Vector(n, 0));
		for (int i = 0; i < n; ++i){ E[i][i] =1; }
		Matrix R = aq * inverse(aq) - E;
		cout << "Square root method for symmetrical matrix:" << endl;
		cout << "Given matrix:" << endl;
		print(a);
		cout << "Sufficient condition test:" << (silvester(aq) ? " Passed" : " Failed") << endl;
		cout << "Solution:" << endl;
		print(x);
		check(a, x);
		cout << endl;
	}

	void jacobi(Matrix a, double precision) {
		int n = a.size();
		bool criteria = true;
		for (int i = 0; i < n; ++i) {
			double sum = -fabs(a[i][i]);
			for (int j = 0; j < n; ++j) {
				sum += fabs(a[i][j]);
			}
			if (a[i][i] <= sum) criteria = false;
		}
		Matrix X(1, Vector(n, 0));
		double eps = precision + 1;
		int k = 0;
		while (eps > precision) {
			X.resize(k + 2, Vector(n, 0));
			for (int i = 0; i < n; ++i) {
				X[k + 1][i] = a[i][n] / a[i][i];
				for (int j = 0; j < n; ++j) {
					if (j == i) continue;
					X[k + 1][i] -= a[i][j] / a[i][i] * X[k][j];
				}
			}
			eps = norm(X[k + 1] - X[k]);
			++k;
		}
		Vector x = X[k];
		Matrix aq = a;
		for (auto it = aq.begin(); it != aq.end(); ++it){it->erase(it->begin() + it->size() -1);}
		Matrix r = transpose(aq * transpose(Matrix(1, x)) - transpose(Matrix(1, transpose(a)[a.size()])));
		// matrix residual
		Matrix E = Matrix(a.size(), Vector(a.size(), 0));
		for (int i = 0; i < a.size(); ++i){ E[i][i] =1; }
		Matrix R = aq * inverse(aq) - E;
		cout << "Jacobi method:" << endl;
		cout << "Given matrix:" << endl;
		print(a);
		cout << "Sufficient condition test:" << (criteria ? " Passed" : " Failed") << endl;
		cout << "Solution:" << endl;
		print(x);
		cout << "Precision:" << endl;
		cout << eps << " (" << k << " iterations)" << endl;
		check(a, x);
		cout << endl;
	}

	void gauss_seidel(Matrix a, double precision) {
		int n = a.size();
		Matrix X(1, Vector(n, 0));
		double eps = precision + 1;
		int k = 0;
		bool criteria = true;
		for (int i = 0; i < n; ++i) {
			double sum = -fabs(a[i][i]);
			for (int j = 0; j < n; ++j) {
				sum += fabs(a[i][j]);
			}
			if (a[i][i] <= sum) criteria = false;
		}
		while (eps > precision) {
			X.resize(k + 2, Vector(n, 0));
			for (int i = 0; i < n; ++i) {
				X[k + 1][i] = a[i][n] / a[i][i];
				for (int j = 0; j < n; ++j) {
					if (j == i) continue;
					if (j < i) {
						X[k + 1][i] -= a[i][j] / a[i][i] * X[k + 1][j];
					} else {
						X[k + 1][i] -= a[i][j] / a[i][i] * X[k][j];
					}
				}
			}
			eps = norm(X[k + 1] - X[k]);
			++k;
		}
		Vector x = X[k];
		Matrix aq = a;
		for (auto it = aq.begin(); it != aq.end(); ++it){it->erase(it->begin() + it->size() -1);}
		Matrix r = transpose(aq * transpose(Matrix(1, x)) - transpose(Matrix(1, transpose(a)[a.size()])));
		// matrix residual
		Matrix E = Matrix(a.size(), Vector(a.size(), 0));
		for (int i = 0; i < a.size(); ++i){ E[i][i] =1; }
		Matrix R = aq * inverse(aq) - E;
		cout << "Gauss-seidel method:" << endl;
		cout << "Given matrix:" << endl;
		print(a);
		cout << "Sufficient condition test:" << (criteria ? " Passed" : " Failed") << endl;
		cout << "Solution:" << endl;
		print(x);
		cout << "Precision:" << endl;
		cout << eps << " (" << k << " iterations)" << endl;
		check(a, x);
		cout << endl;
	}

	void minimal_residual_method(Matrix a, double precision) {
		Matrix aq = quad(a);
		Matrix bq = transpose(aq) * aq;
		Matrix f = transpose(aq) * column(a, a.size());
		for (int i = 0; i < a.size(); ++i) {
			for (int j = 0; j <= a.size(); ++j) {
				a[i][j] = (j == a.size() ? f[i][0] : bq[i][j]);
			}
		}
		aq = quad(a);
		f = column(a, a.size());

		Matrix x = f;
		Matrix r = aq * x - f;

		int k = 0;
		while (norm(transpose(r)[0]) > precision) {
			++k;
			x = x - r * ((transpose(r) * (aq * r))[0][0] / (transpose(aq * r) * (aq * r))[0][0]);
			r = aq * x - f;
		}
		Vector xs = transpose(x)[0];
		cout << "Minimal residual method:" << endl;
		cout << "Given matrix:" << endl;
		print(a);
		cout << "Sufficient condition test:" << (silvester(bq) ? " Passed" : " Failed") << endl;
		cout << "Solution:" << endl;
		print(xs);
		cout << "Precision:" << endl;
		cout << norm(transpose(r)[0]) << " (" << k << " iterations)" << endl;
		check(a, xs);
		cout << endl;
	}
}

using namespace methods;
int main(int argc, char *argv[]) {
	try	{
		if (argc == 2) {freopen (argv[1], "w", stdout);}
		Matrix a = {
			{0.4997, -0.0658, 0.0132, 0.0263, 0.0921, -2.8141},
			{0.0684, 0.7824, 0.0000, -0.0526, 0.0526, 2.4104},
			{0.0395, 0.0000, 0.6286, -0.1841, 0.1052, 2.2828},
			{-0.0789, 0.1657, 0.0000, 0.6181, -0.0263, -1.6332},
			{0.3288, 0.0000, 0.1184, 0.0132, 0.7364, 1.8936}
		};
		gauss_with_pivoting(a);
		tridiagonal(a);
		square_root(a);
		jacobi(a, EPS);
		gauss_seidel(a, EPS);
		minimal_residual_method(a, EPS);
		if (argc == 2) {fclose(stdout);}
	} catch (const char* error) {
		cout << error;
	}
}
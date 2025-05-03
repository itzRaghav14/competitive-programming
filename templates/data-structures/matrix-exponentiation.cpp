const int MOD = 1e9 + 7;
int add(int a, int b) { return (a + b) % MOD; }
int mul(int a, int b) { return 1LL * a * b % MOD; }

template <const int R, const int C>
struct matrix {
  using Type = int;
  using matrix_type = array<array<Type, C>, R>;
  matrix_type a;
  matrix() {
    for (int i = 0; i < R; i++)
      for (int j = 0; j < C; j++) a[i][j] = 0;
  }
  matrix(matrix_type _a) : a(_a) {}
  friend matrix<R, C> operator*(matrix<R, C> &x, matrix<C, C> &y) {
    matrix<R, C> res;
    for (int i = 0; i < R; i++)
      for (int k = 0; k < C; k++)
        for (int j = 0; j < C; j++)
          res[i][k] = add(res[i][k], mul(x[i][j], y[j][k]));
    return res;
  }
  friend matrix<R, C> power(matrix<R, C> init, matrix<C, C> x, long long b) {
    matrix<R, C> res = init;
    while (b) {
      if (b & 1) res = res * x;
      b >>= 1, x = x * x;
    }
    return res;
  }
  static matrix identity() {
    assert(R == C);
    matrix res;
    for (int i = 0; i < R; i++) res[i][i] = 1;
    return res;
  }
  array<Type, C> &operator[](int i) { return a[i]; }
  size_t size() { return a.size(); }
};
const int MATRIX_SIZE = 1;
using Matrix = matrix<MATRIX_SIZE, MATRIX_SIZE>;
using matrix_type = Matrix::matrix_type;
using Matrixx = matrix<1, MATRIX_SIZE>;
using matrixx_type = Matrixx::matrix_type;
const Matrix identity_matrix = Matrix::identity();
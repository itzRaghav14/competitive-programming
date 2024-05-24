const int MOD = 1e9 + 7;
int add(int a, int b) { return (a + b) % MOD; }
int mul(int a, int b) { return 1LL * a * b % MOD; }

template<const int SZ>
struct matrix {
    array<array<int, SZ>, SZ> a;
    matrix() {
        for (int i = 0; i < SZ; i++)
            for (int j = 0; j < SZ; j++)
                a[i][j] = 0;
    }
    matrix(array<array<int, SZ>, SZ> _a): a(_a) {}
    friend matrix operator*(const matrix &x, const matrix &y) {
        matrix res;
        for (int i = 0; i < SZ; i++)
            for (int j = 0; j < SZ; j++)
                for (int k = 0; k < SZ; k++)
                    res.a[i][j] = add(res.a[i][j], mul(x.a[i][k], y.a[k][j]));
        return res;
    }
    friend matrix power(matrix init, matrix x, long long b) {
        matrix res = init;
        while (b) {
            if (b & 1) res = res * x;
            b >>= 1, x = x * x;
        }
        return res;
    }
    static matrix identity() {
        matrix res;
        for (int i = 0; i < SZ; i++) res.a[i][i] = 1;
        return res;
    }
};
using Matrix = matrix<2>;
const Matrix identity_matrix = Matrix::identity();
using matrix_type = decltype(identity_matrix.a);
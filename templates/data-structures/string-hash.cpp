template<int K = 2>
struct StringHash {
    using ll = long long;
    static inline array<ll, 2> Q = {271, 277};
    static inline array<ll, 2> M = {1000000007, 998244353};

    vector<array<ll, K>> ps;
    vector<array<ll, K>> pw;

    StringHash(string s) {
        int n = s.length();
        ps.resize(n + 1);
        pw.resize(n + 1);
        pw[0].fill(1);

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < K; j++) {
                ps[i][j] = (Q[j] * ps[i - 1][j] + s[i - 1] + 1) % M[j];
                pw[i][j] = (pw[i - 1][j] * Q[j]) % M[j];
            }
        }
    }

    static array<ll, K> getHash(string s) {
        int n = s.length();
        array<ll, K> ps;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < K; j++) {
                ps[j] = (Q[j] * ps[j] + s[i - 1] + 1) % M[j];
            }
        }
    }

    array<ll, K> substrHash(int start, int end)  {
        array<ll, K> res;
        for (int j = 0; j < K; j++) {
            ll rem = (pw[end - start + 1][j] * ps[start][j]) % M[j];
            res[j] = (ps[end + 1][j] - rem + M[j]) % M[j];
        }
        return res;
    }
};
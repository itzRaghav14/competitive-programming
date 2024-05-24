// const int MOD = 1e9 + 7;
// const int MOD = 998244353;
// const long long MOD = 1375927501846395853LL;
template<const int mod>
struct mint {
    int val;
    constexpr mint(long long x = 0) : val((x % mod + mod) % mod) {}
    explicit operator int() const { return val; }
    mint& operator+=(const mint &b) { val += b.val; val -= mod * (val >= mod); return *this; }
    mint& operator-=(const mint &b) { val -= b.val; val += mod * (val < 0); return *this; }
    mint& operator*=(const mint &b) { val = 1ll * val * b.val % mod; return *this; }
    mint& operator/=(const mint &b) { return *this *= b.inv(); }
    mint inv() const { int x = 1, y = 0, t; for(int a=val, b=mod; b; swap(a, b), swap(x, y)) t = a/b, a -= t * b, x -= t * y; return mint(x); }
    mint power(int b) const { mint a = *this, res(1); for(; b; a *= a, b /= 2)  if(b & 1) res *= a; return res; }
    mint operator-() const { return val == 0 ? 0 : mod - val; }
    mint& operator++() { val = val == mod - 1 ? 0 : val + 1; return *this; }
    mint& operator--() { val = val == 0 ? mod - 1 : val - 1; return *this; }
    mint operator++(int32_t) { mint before = *this; ++*this; return before; }
    mint operator--(int32_t) { mint before = *this; --*this; return before; }
    friend mint operator+(const mint &a, const mint &b) {return mint(a) += b;}
    friend mint operator-(const mint &a, const mint &b) {return mint(a) -= b;}
    friend mint operator*(const mint &a, const mint &b) {return mint(a) *= b;}
    friend mint operator/(const mint &a, const mint &b) {return mint(a) /= b;}
    friend bool operator==(const mint &a, const mint &b) {return a.val == b.val;}
    friend bool operator!=(const mint &a, const mint &b) {return a.val != b.val;}
    friend bool operator<(const mint &a, const mint &b) {return a.val < b.val;}
    friend istream& operator>>(istream &in, mint &a) {return in >> a.val;}
    friend ostream& operator<<(ostream &os, const mint &a) {return os << a.val;}
};
using Mint = mint<MOD>;
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

template<typename... Ts, size_t... Is, typename F>
void __op(index_sequence<Is...>, tuple<Ts...>& a, const tuple<Ts...>& b, F op) { ((get<Is>(a) = op(get<Is>(a), get<Is>(b))), ...); }
#define OVERLOAD(OP, F) \
template<typename... Ts> auto& operator OP##=(tuple<Ts...> &a, const tuple<Ts...> &b) { __op(index_sequence_for<Ts...>(), a, b, F<>{}); return a; } \
template<typename... Ts> auto operator OP(const tuple<Ts...> &a, const tuple<Ts...> &b) { auto c = a; c OP##= b; return c; }
OVERLOAD(+, plus) OVERLOAD(-, minus) OVERLOAD(*, multiplies) OVERLOAD(/, divides)

constexpr int NUM_HASHES = 2; // *
constexpr array<int, NUM_HASHES> mods = {127657753, 987654319}; // *
template <size_t N = NUM_HASHES> constexpr auto mint_ntuple(const int &v) { return [&]<size_t... Is>(index_sequence<Is...>) { return make_tuple(mint<mods[Is]>(v)...); }(make_index_sequence<N>{}); }

using HT = decltype(mint_ntuple(0)); 
HT hash0 = mint_ntuple(0);
ostream& operator<<(ostream &os, const HT &ht) { os << "( "; apply([&os](auto&&... args) { ((os << args << ' '), ...); }, ht); return os << ")"; }

struct Node {
    HT val;
    Node(): val(hash0) {}
    Node(HT v): val(v) {}
    friend Node merge(Node l, Node r) { return Node(l.val + r.val); }
    void update(HT v) { val = v; }
};

struct SegmentTree {
    int n;
    vector<Node> seg;
    SegmentTree() {}
    SegmentTree(int _n): n(_n), seg(2 * n) {}
    template <typename Type>
    SegmentTree(vector<Type> a) {
        n = a.size();
        seg.resize(2 * n);
        for (int i = 0; i < n; i++) seg[i + n] = Node(a[i]);
        for (int i = n - 1; i > 0; i--) seg[i] = merge(seg[i << 1], seg[i << 1 | 1]);
    }
    void update(int i, HT v) {
        for (seg[i += n].update(v); i >>= 1; ) seg[i] = merge(seg[i << 1], seg[i << 1 | 1]);
    }
    Node query(int l, int r) {
        Node resl, resr;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = merge(resl, seg[l++]);
            if (r & 1) resr = merge(seg[--r], resr);
        }
        return merge(resl, resr);
    }
};

struct StringHash {
    static inline HT Q = {271, 277};
    int n;
    vector<HT> pw, ps1, ps2;
    SegmentTree sg1, sg2;

    StringHash(string s) {
        n = s.length();
        pw.resize(n + 1); ps1.resize(n), ps2.resize(n);
        pw[0] = mint_ntuple(1);
        for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * Q;
        for (int i = 0; i < n; i++) {
            ps1[i] = mint_ntuple(s[i]) * pw[i + 1];
            ps2[i] = mint_ntuple(s[i]) * pw[n - i];
        }
        sg1 = SegmentTree(ps1), sg2 = SegmentTree(ps2);
    }

    void update(int i, char c) {
        sg1.update(i, mint_ntuple(c) * pw[i + 1]);
        sg2.update(i, mint_ntuple(c) * pw[n - i]);
    }

    HT substrHash(int l, int r)  {
        if (l <= r) return sg1.query(l, r).val / pw[l];
        else return sg2.query(r, l).val / pw[n - l - 1];
    }

    bool isPalindrome(int l, int r) {
        return substrHash(l, r) == substrHash(r, l);
    }
};
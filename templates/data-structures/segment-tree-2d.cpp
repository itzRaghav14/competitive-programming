struct Node {
    long long val;
    Node(): val(0) {}
    Node(long long v): val(v) {}
    friend Node merge(Node l, Node r) { return Node(l.val + r.val); }
    void update(long long v) { val = v; }
};
 
struct SegmentTree2D {
    int n, m;
    vector<vector<Node>> seg;
    SegmentTree2D(int _n, int _m): n(_n), m(_m), seg(2 * n, vector<Node>(2 * m)) {}
    template<typename Type> SegmentTree2D(vector<vector<Type>> a): n(a.size()), m(a[0].size()) {
        seg.assign(2 * n, vector<Node>(2 * m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) seg[i + n][j + m] = Node(a[i][j]);
            for (int j = m - 1; j > 0; j--) seg[i + n][j] = merge(seg[i + n][j << 1], seg[i + n][j << 1 | 1]);
        }
        for (int i = n - 1; i > 0; i--) {
            for (int j = 0; j < 2 * m; j++) seg[i][j] = merge(seg[i << 1][j], seg[i << 1 | 1][j]);
        }
    }
    void update(int r, int c, long long v) {
        seg[r += n][c += m].update(v);
        for (int j = c; j >>= 1;) seg[r][j] = merge(seg[r][j << 1], seg[r][j << 1 | 1]);
        for (; r >>= 1;) for (int j = c; j >= 1; j >>= 1) {
            seg[r][j] = merge(seg[r << 1][j], seg[r << 1 | 1][j]);
        }
    }
    Node query(int li, int lj, int ri, int rj) {
        if (li > ri || lj > rj) return Node();
        Node res;
        for (li += n, ri += n + 1; li < ri; li >>= 1, ri >>= 1) {
            int l =  lj, r = rj;
            for (l += m, r += m + 1; l < r; l >>= 1, r >>= 1) {
                if (l & 1) {
                    if (li & 1) res = merge(res, seg[li][l]);
                    if (ri & 1) res = merge(res, seg[ri - 1][l]);
                    l++;
                }
                if (r & 1) {
                    r--;
                    if (li & 1) res = merge(res, seg[li][r]);
                    if (ri & 1) res = merge(res, seg[ri - 1][r]);
                }
            }
            li += li & 1, ri -= ri & 1;
        }
        return res;
    }
};
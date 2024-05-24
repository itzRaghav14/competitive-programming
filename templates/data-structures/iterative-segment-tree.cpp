struct Node {
    long long val;
    Node(): val(0) {}
    Node(long long v): val(v) {}
    friend Node merge(Node l, Node r) { return Node(l.val + r.val); }
    void update(long long v) { val = v; }
};

struct SegmentTree {
    int n;
    vector<Node> seg;
    SegmentTree(int n): n(n), seg(2 * n) {}
    template <typename Type>
    SegmentTree(vector<Type> a) {
        n = a.size();
        seg.resize(2 * n);
        for (int i = 0; i < n; i++) seg[i + n] = Node(a[i]);
        for (int i = n - 1; i > 0; i--) seg[i] = merge(seg[i << 1], seg[i << 1 | 1]);
    }
    void update(int i, long long v) {
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
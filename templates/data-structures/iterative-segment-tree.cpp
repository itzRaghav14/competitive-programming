struct Node {
    long long val;
    Node(): val(0) {}
    Node(int v): val(v) {}
    friend Node merge(Node a, Node b) {
        return Node(a.val + b.val);
    }
    void update(long long v) {
        val = v;
    }
};

struct SegmentTree {
    int n;
    vector<Node> seg;

    SegmentTree(int n): n(n) {
        seg.resize(2 * n);
    }

    void update(int i, long long v) {
        for (seg[i += n].update(v); i > 1; i >>= 1) seg[i >> 1] = merge(seg[i], seg[i ^ 1]);
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
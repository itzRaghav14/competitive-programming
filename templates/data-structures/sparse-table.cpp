// const int LOG = 20;

struct Node {
    long long val;
    Node(): val(0) {}
    Node(long long v): val(v) {}
    friend Node merge(Node l, Node r) {
        return Node(l.val + r.val);
    }
};

struct SparseTable {
    vector<vector<Node>> jmp;

    SparseTable(vector<int> &a) {
        int n = a.size();
        jmp.assign(n, vector<Node>(LOG));
        for (int i = 0; i < n; i++) jmp[i][0] = Node(a[i]);
        for (int j = 1, len = 1; j < LOG; j++, len *= 2) {
            for (int i = 0; i + 2 * len <= n; i++) {
                jmp[i][j] = merge(jmp[i][j - 1], jmp[i + len][j - 1]);
            }
        }
    }

    Node query(int l, int r) {
        if (l > r) return Node();
        int j = 63 - __builtin_clzll(r - l + 1), len = 1 << j;
        return merge(jmp[l][j], jmp[r - len + 1][j]);
    }
};
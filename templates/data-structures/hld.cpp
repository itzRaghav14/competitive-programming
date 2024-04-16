struct Node {
    long long val;
    Node(): val(0) {}
    Node(long long v): val(v) {}
    friend Node operator+(Node l, Node r) {
        return Node(l.val + r.val);
    }
    friend Node operator-(Node u) { return u; }
    void update(long long v) {
        val = v;
    }
};

struct SegmentTree {
    int n;
    vector<Node> seg;

    template <typename Type>
    void init(vector<Type> a) {
        n = a.size();
        seg.resize(2 * n);
        for (int i = 0; i < n; i++) seg[i + n] = Node(a[i]);
        for (int i = n - 1; i > 0; i--) seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }

    void update(int i, long long v) {
        for (seg[i += n].update(v); i >>= 1; ) seg[i] = seg[i << 1] + seg[i << 1 | 1];
    }

    Node query(int l, int r) {
        Node resl, resr;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = resl + seg[l++];
            if (r & 1) resr = seg[--r] + resr;
        }
        return resl + resr;
    }
};

struct BinaryLifting {
    int n;
    vector<int> lvl;
    vector<vector<int>> par;

    void init(vector<vector<int>> &g) { // 1-indexed
        n = g.size() - 1;
        lvl.assign(n + 1, 0);
        par.assign(n + 1, vector<int>(LOG, 0));

        function<void(int,int)> dfs = [&] (int u, int p) {
            par[u][0] = p;
            lvl[u] = lvl[p] + 1;
            for (int v : g[u]) if (v != p) {
                dfs(v, u);
            }
        };
        dfs(1, 0);

        for (int j = 1; j < LOG; j++) {
            for (int i = 1; i <= n; i++) {
                par[i][j] = par[par[i][j - 1]][j - 1];
            }
        }
    }

    int lift(int u, int k) {
        for (int j = 0; j < LOG; j++) if (k >> j & 1) {
            u = par[u][j];
        }
        return u;
    }

    int lca(int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        if (lvl[u] > lvl[v]) u = lift(u, lvl[u] - lvl[v]);
        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (par[u][j] != par[v][j]) {
                u = par[u][j];
                v = par[v][j];
            }
        }

        return par[u][0];
    }
};

template<typename Type>
struct HLD {
    int n;
    vector<vector<int>> adj, adj_hld;
    vector<int> sz, pos, rpos, chain;
    vector<Type> tree;
    SegmentTree sg;
    BinaryLifting bl;

    HLD(vector<Type> a, vector<vector<int>> &g) { // 1-indexed
        n = a.size() - 1;
        adj = g;
        adj_hld.resize(n + 1);
        sz.assign(n + 1, 0);
        pos.resize(n + 1);
        rpos.resize(n + 1);
        tree.resize(n + 1);
        chain.resize(n + 1);

        function<void(int,int)> dfs = [&] (int u, int p) {
            sz[u] = 1;
            int mx = 0;
            for (int &v : adj[u]) if (v != p) {
                dfs(v, u);
                sz[u] += sz[v];
                if (sz[v] > mx) {
                    mx = sz[v];
                    swap(v, adj[u][0]);
                }
            }
        };
        dfs(1, 0);

        int t = 1;
        function<void(int,int)> makeHld = [&] (int u, int p) {
            pos[u] = t++;
            rpos[pos[u]] = u;
            tree[pos[u]] = a[u];
            chain[pos[u]] = p && adj[p][0] == u ? chain[pos[p]] : pos[u];

            for (int v : adj[u]) if(v != p) {
                makeHld(v, u);
                adj_hld[pos[u]].push_back(pos[v]);
            }
        };
        makeHld(1, 0);

        sg.init(tree);
        bl.init(adj_hld);
    }

    Node up(int u, int l) {
        Node res;
        while (u > l) {
            int anc = max(l + 1, chain[u]);
            res = res + sg.query(anc, u);
            u = bl.par[anc][0];
        }
        return res;
    }

    void update(int u, long long val) {
        sg.update(pos[u], val);
    }

    Node query(int u, int v) {
        u = pos[u], v = pos[v];
        int l = bl.lca(u, v);
        return up(u, l) + sg.query(l, l) + -up(v, l);
    }
};
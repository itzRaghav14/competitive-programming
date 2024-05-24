// const int LOG = 20;

struct BinaryLifting {
    int n;
    vector<int> lvl;
    vector<vector<int>> par;

    BinaryLifting(vector<vector<int>> &g) { // 1-indexed
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
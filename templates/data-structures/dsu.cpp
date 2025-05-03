struct Dsu {
  int n;
  vector<int> par, sz;
  Dsu(int n) : n(n) {
    par.resize(n + 1);
    sz.assign(n + 1, 1);
    for (int i = 0; i <= n; i++) par[i] = i;
  }
  int find(int u) { return par[u] = par[u] == u ? u : find(par[u]); }
  int size(int u) { return sz[find(u)]; }
  bool same(int u, int v) { return find(u) == find(v); }
  bool unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (sz[u] < sz[v]) swap(u, v);
    par[v] = u, sz[u] += sz[v];
    return true;
  }
};
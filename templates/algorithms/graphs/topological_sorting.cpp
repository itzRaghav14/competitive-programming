// Note: 1-based indexing is used in this snippet.
vector<int> getTopoSort(vector<vector<int>> &adj) {
  int n = adj.size() - 1;
  vector<int> vis(n + 1, 0), topo;
  auto dfs = [&](auto &&dfs, int u) -> void {
    vis[u] = 1;
    for (int v : adj[u]) {
      if (!vis[v]) {
        dfs(dfs, v);
      }
    }
    topo.push_back(u);
  };
  for (int u = 1; u <= n; u++) {
    if (!vis[u]) {
      dfs(dfs, u);
    }
  }
  reverse(topo.begin(), topo.end());
  return topo;
}
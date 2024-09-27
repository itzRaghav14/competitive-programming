// Note: 1-based indexing is used in this snippet.
vector<int> getPath(int src, int dest, vector<vector<int>> &adj) {
  int n = adj.size() - 1;
  auto bfs = [&](int src) {
    vector<int> dist(n + 1, -1), from(n + 1, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : adj[u]) {
        if (dist[v] == -1) {
          dist[v] = dist[u] + 1;
          from[v] = u;
          q.push(v);
        }
      }
    }
    return from;
  };
  vector<int> from = bfs(src), path;
  for (int node = dest; node != -1; node = from[node]) path.push_back(node);
  reverse(path.begin(), path.end());
  return path;
}
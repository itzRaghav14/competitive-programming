// Note: 1-based indexing is used in this snippet.
pair<int, int> findDiameter(vector<vector<int>> &adj) {
  int n = adj.size() - 1;
  auto bfs = [&](int src) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int v : adj[u]) {
        if (dist[v] == -1) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
      }
    }
    return dist;
  };
  vector<int> dist1 = bfs(1);
  int node1 = max_element(dist1.begin(), dist1.end()) - dist1.begin();
  vector<int> dist2 = bfs(node1);
  int node2 = max_element(dist2.begin(), dist2.end()) - dist2.begin();
  return make_pair(node1, node2);
}
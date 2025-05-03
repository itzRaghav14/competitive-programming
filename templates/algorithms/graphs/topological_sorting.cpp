vector<int> getTopoSort(vector<vector<int>> &adj) {
  constexpr int obi = 1;  // one based indexing
  int n = adj.size() - obi;
  vector<int> indegree(n + obi), topo;
  queue<int> q;
  for (int u = obi; u < n + obi; u++)
    for (int v : adj[u]) indegree[v]++;
  for (int u = obi; u < n + obi; u++)
    if (!indegree[u]) q.push(u);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    topo.push_back(u);
    for (int v : adj[u])
      if (--indegree[v] == 0) q.push(v);
  }
  return topo.size() == n ? topo : vector<int>();
}
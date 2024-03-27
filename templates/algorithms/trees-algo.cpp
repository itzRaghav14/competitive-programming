array<vector<int>, 2> bfs(int src, int n, vector<int> adj[]) {
    vector<int> dist(n + 1, -1);
    vector<int> from(n + 1, -1);
    queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int child : adj[node]) if (dist[child] == -1) {
            dist[child] = dist[node] + 1;
            from[child] = node;
            q.push(child);
        }
    }
    
    return {dist, from};
}

pair<int,int> findDiameter(int n, vector<int> adj[]) {
    vector<int> dist1 = bfs(1, n, adj)[0];
    int node1 = max_element(dist1.begin(), dist1.end()) - dist1.begin();
    vector<int> dist2 = bfs(node1, n, adj)[0];
    int node2 = max_element(dist2.begin(), dist2.end()) - dist2.begin();
    return {node1, node2};
}

vector<int> getPath(int src, int dest, int n, vector<int> adj[]) {
    auto [dist, from] = bfs(src, n, adj);
    vector<int> path;
    for (int node = dest; node != -1; node = from[node]) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());
    return path;
}
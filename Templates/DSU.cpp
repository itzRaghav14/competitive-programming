// === Disjoint Set Union ===
class DSU{
public:
    vector<int> parent;
    vector<int> sizes;
    vector<int> rank;
    int N;
    
    DSU(int n){
        N = n;
        parent.resize(N + 1);
        sizes.resize(N + 1);
        rank.resize(N + 1);
    }
    
    void merge(int child, int par){
        
        return;
    }
    
    void makeSet(){
        for(int i = 1; i <= N; i++){
            parent[i] = i;
            sizes[i] = 1;
            rank[i] = 0;
        }
    }
    
    int findParent(int node){
        if(parent[node] == node){
            return node;
        }
        return parent[node] = findParent(parent[node]);
    }
    
    void unionFunc(int u, int v){
        u = findParent(u);
        v = findParent(v);
        if(rank[u] < rank[v]){
            merge(u, v);
            parent[u] = v;
            sizes[v] += sizes[u];
        }
        else if(rank[v] < rank[u]){
            merge(v, u);
            parent[v] = u;
            sizes[u] += sizes[v];
        }
        else{
            merge(v, u);
            parent[v] = u;
            sizes[u] += sizes[v];
            rank[u]++;
        }
    }
    
};
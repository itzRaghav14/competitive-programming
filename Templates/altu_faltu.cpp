// Prime or Not
bool isPrime(int n){
    if (n == 2 || n == 3) return true;
    if (n <= 1 || n % 2 == 0 || n % 3 == 0) return false; 
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int loPrime(int n){
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0) return i;
        if (n % (i+2) == 0) return i+2;
    }
    return n;
}

// === Binary Exponentiation ===
int powermod(int a, int b, int Mod = MOD){
    int res = 1;
    a %= Mod;
    while (b > 0){
        if (b & 1) res = (res * a) % Mod;
        a = (a * a) % Mod;
        b = b >> 1;
    }
    return res;
}


// === Binary Multiplication ===
int binMul(int a, int b, int Mod = MOD){
    int res = 0;
    a %= Mod;
    b %= Mod;
    if(a==0) return 0;
    while(b){
        if(b & 1) res = (res + a) % Mod;
        b >>= 1;
        a = (a + a) % Mod;
    }
    return res;
}

// === Modulo Multiplicative Inverse ===
int mul_inv(int a, int Mod = MOD){
    return powermod(a, Mod-2, Mod);
}

// === GCD ===
int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a % b);
}

// === LCM ===
int lcm(int a, int b){
    return (a / gcd(a, b) * b);
}

// === nCr ===
int ncr(int n, int r){
    int p = 1, k = 1;
    if(n - r < r) r = n - r;
    while(r){
        p *= n;
        k *= r;
        int m = gcd(p, k);
        p /= m;
        k /= m;
        n--;
        r--;
    }
    return p;
}

// === Lease Significant Bit ===
int lsb(int n){
    if(n==0) return -1;
    int res = 0;
    while(n){
        if(n & 1) return res;
        n /= 2;
        res++;
    }
    return -1;
}

// === Most Significant Bit ===
int msb(int n){
    if (n == 0) return -1;
    int res = 0;
    n = n / 2;
    while (n != 0) {
        n = n / 2;
        res++;
    }
 
    return res;
}

// === Sum of digits of a number ===
int digitSum(int n){
    int ans = 0;
    while (n > 0){
        ans += n % 10;
        n /= 10;
    }
    return ans;
}

// === Modular Multiplication ===
int modM(int n, int m, int M = MOD){
    return ((n % M * m % M) + M) % M;
}

// === Modular Addition ===
int modA(int n, int m, int M = MOD){
    return ((n % M + m % M) + M) % M;
}

// === Decimal to Binary ===
string decToBinary(int n){
    if(n == 0) return "0";
    string binaryNum;
    while (n > 0) {
        binaryNum.pb('0' + n%2);
        n /= 2;
    }
    reverse(all(binaryNum));
    return binaryNum;
}

// === Decimal to Binary 2.0 ===
string decToBinarylen(int n, int len = -1){
    string bin = decToBinary(n);
    string ret = "";
    for(int i=0; i<len - bin.length(); i++) ret += '0';
    for(int i=0; i<bin.length(); i++) ret += bin[i];
    return ret;
}

// === Countbits ===
int bitSet(int n){
    return __builtin_popcountll(n);
}

// === Seive Algorithm ===
const int N = 1e5 + 5;
vi isPrime(N, 1);
vi lp(N, 0);
vi hp(N, 0);
// vvi divisors(N);
void seive(){
    isPrime[0] = isPrime[1] = 0;
    for(int i=1; i<N; i++){
        if(isPrime[i] == 0) continue;
        lp[i] = hp[i] = i;
        for(int j = 2*i; j<N; j+=i){
            isPrime[j] = 0;
            // divisors[j].pb(i);
            hp[j] = i;
            if(lp[j] == 0) lp[j] = i;
        }
    }
}

// === Segment Tree ===

struct item{
    int sum, mx, pre, suf;
};

class segtree{
public:
    
    vector<item> seg;
    int n;
    
    item NEUTRAL_ELEMENT = {0, -INF, -INF, -INF};
    
    item single(int val){
        int mxVal = max(0ll, val);
        return {val, mxVal, mxVal, mxVal};
    }
    
    item merge(item left, item right, int type = 1){
        
        item node = NEUTRAL_ELEMENT;
        
        
        
        return node;
        
    }
    
    
    segtree(vector<int> &arr, int size = -1){
        if(size == -1) size = arr.size();
        n = size;
        seg.resize(4 * n + 1);
        build(arr);
    }
    
    void build(vector<int> &arr, int ind = 0, int low = 0, int high = -1){
        if(high == -1) high = n -  1;
        if(low == high){
            seg[ind] = single(arr[low]);
            return;
        }
        int mid = (low + high) / 2;
        build(arr, 2 * ind + 1, low, mid);
        build(arr, 2 * ind + 2, mid + 1, high);
        seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
    
    item query(int l, int r, int type = 1, int ind = 0, int low = 0, int high = -1){
        if(high == -1) high = n - 1;
        if(low > r || high < l){
            return NEUTRAL_ELEMENT;
        }
        if(low >= l && high <= r) return seg[ind];
        int mid = (low + high) / 2;
        item left = query(l, r, 1, 2 * ind + 1, low, mid);
        item right = query(l, r, 1, 2 * ind + 2, mid + 1, high);
        return merge(left, right);        
    }
    
    void update(int i, int v, int ind = 0, int low = 0, int high = -1){
        if(high == -1) high = n - 1;
        if(low == high){
            seg[ind] = single(v);
            return;
        }
        int mid = (low + high) / 2;
        if(i <= mid) update(i, v, 2 * ind + 1, low, mid);
        else update(i, v, 2 * ind + 2, mid + 1, high);
        seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
    
};

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

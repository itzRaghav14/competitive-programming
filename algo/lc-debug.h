#define dbg(x...) cout << "[" << __LINE__ - 9 << "]\t[ " << #x << " ]\t\t"; debug_struct::_print(x); cout << endl;
#define debug(x,y...) cout << "[" << __LINE__ - 9 << "]\t[ " << #x << " ]\t\t"; debug_struct::_print(y); cout << endl;
#define crndl cout << endl;

// #define dbg(...) ;
// #define debug(...) ;
// #define crndl ;

struct debug_struct {
    template <typename T> static void _print(T t) { cout << t; }
    static void _print() { return; }
    template <class T> static void _print(vector <T> v) {cout << "[ "; for (T i : v) {_print(i); cout << " ";} cout << "]";}
    template <class T> static void _print(deque <T> d) {cout << "[ "; for (T i : d) {_print(i); cout << " ";} cout << "]";}
    template <class T> static void _print(queue <T> q) {cout << "[ "; while (!q.empty()) {_print(q.front()); cout << " "; q.pop();} cout << "]";}
    template <class T> static void _print(stack<T> s) { cout << "[ "; while (!s.empty()) { _print(s.top()); cout << " "; s.pop(); } cout << "]"; }
    template <class T, size_t S> static void _print(array<T, S> a) {cout << "[ "; for (T i : a) {_print(i); cout << " ";} cout << "]";}
    template <class T, class V> static void _print(set <T, V> st) {cout << "[ "; for (T i : st) {_print(i); cout << " ";} cout << "]";}
    template <class T, class V> static void _print(multiset <T, V> st) {cout << "[ "; for (T i : st) {_print(i); cout << " ";} cout << "]";}
    template <class T, class V> static void _print(priority_queue<T, vector<T>, V> pq) {cout << "[ "; while (!pq.empty()) {_print(pq.top()); cout << " "; pq.pop();} cout << "]";}
    template <class T, class V> static void _print(pair <T, V> p) {cout << "{"; _print(p.first); cout << ","; _print(p.second); cout << "}";}
    template <class T, class V> static void _print(T a[], V n) { cout << "[ "; for(int i = 0; i < n; i++) { _print(a[i]); cout << " "; } cout << "]"; }
    template <class T, class V> static void _print (T* a, V n, V m) { cout << "[ "; for(int i = 0; i < n; i++) { _print(a + i * m, m); cout << " "; } cout << "]"; }
    template <class T, class V, class Compare> static void _print(unordered_map <T, V, Compare> mp) {cout << "[ "; for (auto &i : mp) {_print(i); cout << " ";} cout << "]";}
    template <class T, class V, class Compare> static void _print(map <T, V, Compare> mp) {cout << "[ "; for (auto &i : mp) {_print(i); cout << " ";} cout << "]";}
    template <class T, class... V> static void _print(T t, V... v) { _print(t); if (sizeof...(v)) { cout << ", "; _print(v...); } }
    // template<typename T, typename ComparatorFn> static void _print(oset<T, ComparatorFn> st) {cout << "[ "; for (auto i : st) {_print(i); cout << " ";} cout << "]";}
};
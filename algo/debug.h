#define dbg(x...) cerr << "[" << __LINE__ << "] [ " << #x << " ]\t\t"; debug_struct::_print(x); cerr << endl;
#define debug(x,y...) cerr << "[" << __LINE__ << "] [ " << #x << " ]\t\t"; debug_struct::_print(y); cerr << endl;
#define crndl cerr << endl;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename Type, typename ComparatorFn>
using ordered_set = tree<Type, null_type, ComparatorFn, rb_tree_tag, tree_order_statistics_node_update>;

struct debug_struct {
    template <typename T> static void _print(T t) { cerr << t; }
    static void _print() { return; }
    template <class T> static void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
    template <class T> static void _print(deque <T> d) {cerr << "[ "; for (T i : d) {_print(i); cerr << " ";} cerr << "]";}
    template <class T> static void _print(queue <T> q) {cerr << "[ "; while (!q.empty()) {_print(q.front()); cerr << " "; q.pop();} cerr << "]";}
    template <class T> static void _print(stack<T> s) { cerr << "[ "; while (!s.empty()) { _print(s.top()); cerr << " "; s.pop(); } cerr << "]"; }
    template <class T, size_t S> static void _print(array<T, S> a) {cerr << "[ "; for (T i : a) {_print(i); cerr << " ";} cerr << "]";}
    template <class T, class V> static void _print(set <T, V> st) {cerr << "[ "; for (T i : st) {_print(i); cerr << " ";} cerr << "]";}
    template <class T, class V> static void _print(multiset <T, V> st) {cerr << "[ "; for (T i : st) {_print(i); cerr << " ";} cerr << "]";}
    template <class T, class V> static void _print(priority_queue<T, vector<T>, V> pq) {cerr << "[ "; while (!pq.empty()) {_print(pq.top()); cerr << " "; pq.pop();} cerr << "]";}
    template <class T, class V> static void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
    template <class T, class V> static void _print(T a[], V n) { cerr << "[ "; for(int i = 0; i < n; i++) { _print(a[i]); cerr << " "; } cerr << "]"; }
    template <class T, class V> static void _print (T* a, V n, V m) { cerr << "[ "; for(int i = 0; i < n; i++) { _print(a + i * m, m); cerr << " "; } cerr << "]"; }
    template <class T, class V, class Compare> static void _print(unordered_map <T, V, Compare> mp) {cerr << "[ "; for (auto &i : mp) {_print(i); cerr << " ";} cerr << "]";}
    template <class T, class V, class Compare> static void _print(map <T, V, Compare> mp) {cerr << "[ "; for (auto &i : mp) {_print(i); cerr << " ";} cerr << "]";}
    template <class T, class... V> static void _print(T t, V... v) { _print(t); if (sizeof...(v)) { cerr << ", "; _print(v...); } }
    template<typename T, typename ComparatorFn> static void _print(ordered_set<T, ComparatorFn> st) {cerr << "[ "; for (auto i : st) {_print(i); cerr << " ";} cerr << "]";}
};
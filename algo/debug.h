#include <bits/stdc++.h>
using namespace std;

#define dbg(x...) cerr << #x << "\t\t"; _print(x); cerr << endl;
#define debug(x,y...) cerr << #x << "\t\t"; _print(y); cerr << endl;

// printing anything
template <typename T> void _print (T t) { cerr << t; }
void _print() {return;}

void _print(array<int, 3> v) {cerr << "[ "; for (int i : v) {_print(i); cerr << " ";} cerr << "]";}

// declarations
template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(unordered_map <T, V> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T> void _print(queue <T> q);
template <class T> void _print(stack <T> s);
template <class T> void _print(priority_queue <T> pq);
template <class T> void _print(priority_queue<T, vector<T>, greater<T>> pq);
template <class T> void _print(deque <T> v);
template <class T, class V> void _print(T a[], V n);
template <class T, class V> void _print (T* a, V n, V m);

// definitions
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(unordered_map <T, V> v) {cerr << "[ "; for (auto &i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto &i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(deque <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(queue <T> q) {cerr << "[ "; while (!q.empty()) {_print(q.front()); cerr << " "; q.pop();} cerr << "]";}
template <class T> void _print(stack <T> s) {cerr << "[ "; stack<T> t; while (!s.empty()) {t.push(s.top()); s.pop();} while (!t.empty()) {_print(t.top()); cerr << " "; t.pop();} cerr << "]";}
template <class T> void _print(priority_queue <T> pq) {cerr << "[ "; while (!pq.empty()) {_print(pq.top()); cerr << " "; pq.pop();} cerr << "]";}
template <class T> void _print(priority_queue<T, vector<T>, greater<T>> pq) {cerr << "[ "; while (!pq.empty()) {_print(pq.top()); cerr << " "; pq.pop();} cerr << "]";}
template <class T, class V> void _print(T a[], V n) { cerr << "[ "; for(int i = 0; i < n; i++) { _print(a[i]); cerr << " "; } cerr << "]"; }
template <class T, class V> void _print (T* a,V n, V m) { cerr << "[ "; for(int i = 0; i < n; i++) { _print(a + i * m, m); cerr << " "; } cerr << "]"; }
template<typename T, typename ComparatorFn> void _print(oset<T, ComparatorFn> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

// multiple printing
template <class T, class... V> void _print(T t, V... v) {_print(t); if(sizeof...(v)) {cerr<<", "; _print(v...);}}
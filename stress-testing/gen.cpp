#include <bits/stdc++.h>
using namespace std;

#define int long long

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b) { return a + ((rng()) % (b - a + 1)); }
int rand(pair<int, int> p) { return rand(p.first, p.second); }
char rand_char(char a, char b) { return char(rand(a, b)); }
string rand_string(int n, char a = 'a', char b = 'z') {
  string s = "";
  while (n--) s += rand_char(a, b);
  return s;
}
vector<int> rand_vector(int n, int a, int b) {
  vector<int> v(n);
  for (int i = 0; i < n; i++) v[i] = rand(a, b);
  return v;
}
vector<int> rand_vector(int n, pair<int, int> p) {
  return rand_vector(n, p.first, p.second);
}
pair<int, int> mp(int a, int b) { return {a, b}; }

int32_t main(int32_t argc, char* argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  const int arg = argc >= 2 ? stoi(argv[1]) : 1;

  pair<int, int> N = {4, 8}, A = {1, 20};
  if (arg > 3) N = mp(6, 10), A = mp(1, 31);
  if (arg > 9) N = mp(10, 15), A = mp(1, 255);
  if (arg > 15) N = mp(15, 20), A = mp(1, 255);
  // if (arg > 17) N = mp(3000, 3000), A = mp(1, 255);


  return 0;
}
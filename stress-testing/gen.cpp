#include <bits/stdc++.h>
using namespace std;

#define int long long

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b) { return a + ((rng()) % (b - a + 1)); }
char rand_char(char a, char b) { return char(rand(a, b)); }
string rand_string(int n) { string s = ""; while (n--) s += rand_char('a', 'z'); return s; }

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    return 0;
}
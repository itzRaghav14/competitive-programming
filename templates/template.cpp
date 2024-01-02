#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include "algo/debug.h"
#else
#define dbg(...) ;
#define debug(...) ;
#endif

void solve() {
	
	
	
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	#ifndef ONLINE_JUDGE
  freopen("io/input.txt", "r", stdin);
  freopen("io/output.txt", "w", stdout);
  freopen("io/error.txt", "w", stderr);
  #endif
	
	int t = 1;
	cin >> t;
	
	for (int tc = 1; tc <= t; tc++) {
		debug(Testcase, tc);
		solve();
		dbg();
	}
	
	return 0;
}
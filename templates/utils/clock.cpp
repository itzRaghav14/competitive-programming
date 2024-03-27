#include <bits/stdc++.h>
using namespace std;

int main() {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	auto start1 = chrono::high_resolution_clock::now();

	// do something here

	auto stop1 = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop1 - start1);
	debug(Time, duration.count() / 1000);

	return 0;
}
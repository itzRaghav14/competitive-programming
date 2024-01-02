#include <bits/stdc++.h>
using namespace std;

using namespace chrono;
mt19937 rng(steady_clock::now().time_since_epoch().count());

int main() {
  
	auto start1 = high_resolution_clock::now();

	// do something here

    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
    debug(Time, duration.count() / 1000);

	return 0;
}
#ifdef itzzRaghav
int LOCAL = 1;
#else
int LOCAL = 0;
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b) { return a + ((rng()) % (b - a + 1)); }

struct Tester {
    void init() { }
    void solve() { }
    void check() { }
} tester;
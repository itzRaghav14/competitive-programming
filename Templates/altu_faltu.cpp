// Prime or Not
bool isPrime(int n){
    if (n == 2 || n == 3) return true;
    if (n <= 1 || n % 2 == 0 || n % 3 == 0) return false; 
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// === Binary Exponentiation ===
int powermod(int a, int b, int m = MOD){
    int res = 1;
    a %= m;
    while (b > 0){
        if (b & 1) res = (1LL * res * a) % m;
        a = (1LL * a * a) % m;
        b = b >> 1;
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

// === Decimal to Binary ===
string decToBinary(int n, int len = 0){
    if(n == 0) return "0";
    string binaryNum;
    while (n > 0) {
        binaryNum.pb('0' + n%2);
        n /= 2;
    }
    reverse(all(binaryNum));
    string res = "";
    for (int i = 0; i < len - binaryNum.length(); i++) res += '0';
    res += binaryNum;
    return res;
}

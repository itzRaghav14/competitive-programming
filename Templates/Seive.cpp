// === SEIVE ===

class Seive{
public:
    int N;
    vector<bool> isPrime;
    vector<int> primes;
    vector<int> loPrime;
    vector<int> hiPrime;
    vector<vector<int>> divisors;
    
    Seive(){
        
    }
    
    Seive(int n){
        this->N = n;
        isPrime = vector<bool>(N + 1, 1);
        loPrime = vector<int>(N + 1);
        hiPrime = vector<int>(N + 1);
        divisors = vector<vector<int>>(N + 1);
    }
    
    void build(int n = 0){
        if(n == 0) n = N;
        isPrime[0] = isPrime[1] = 0;
        for(int prime = 2; prime <= n; prime++){
            if(isPrime[prime] == 0) continue;
            primes.push_back(prime);
            loPrime[prime] = hiPrime[prime] = prime;
            for(int multiple = prime * prime; multiple <= n; multiple += prime){
                isPrime[multiple] = 0;
                if(loPrime[multiple] == 0) loPrime[multiple] = prime;
                hiPrime[multiple] = prime;
            }
        }
    }
    
    void generateDivisors(int n = 0){
        if(n == 0) n = N;
        for(int divisor = 1; divisor <= n; divisor++){
            for(int multiple = divisor; multiple <= n; multiple += divisor){
                divisors[multiple].push_back(divisor);
            }
        }
    }
    
    vector<int> findPrimeFactors(int num){
        vector<int> primeFactors;
        for(int i = 2; i * i <= num; i++){
            while(num % i == 0){
                primeFactors.push_back(i);
                num /= i;
            }
        }
        if(num != 1){
            primeFactors.push_back(num);
        }
        return primeFactors;
    }
    
    vector<int> findDistinctPrimeFactors(int num){
        vector<int> primeFactors;
        for(int i = 2; i * i <= num; i++){
            if(num % i == 0) primeFactors.push_back(i);
            while(num % i == 0){
                num /= i;
            }
        }
        if(num != 1){
            primeFactors.push_back(num);
        }
        return primeFactors;
    }
    
    bool findPrime(int num){
        if(num == 0 || num == 1) return false;
        if(num == 2 || num == 3) return true;
        if(num % 2 == 0 || num % 3 == 0) return false;
        for(int i = 5; i * i <= num; i += 6){
            if(num % i == 0) return false;
            if(num % (i + 2) == 0) return false;
        }
        return true;
    }
    
};
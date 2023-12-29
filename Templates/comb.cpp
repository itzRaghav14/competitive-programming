struct Comb {
    int n;
    vector<Mint> _fac, _invfac, _inv;
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
    
    void init (int m) {
        m = min (m, MOD - 1);
        if (m <= n) return;
        
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    
    Mint fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    
    Mint invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    
    Mint inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    
    Mint ncr(int n, int r) {
        if (n < r || r < 0) return 0;
        return fac(n) * invfac(r) * invfac(n - r);
    }
} comb;

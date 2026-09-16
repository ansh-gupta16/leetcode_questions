class Solution {
public:
    int numberOfSets(int n, int k) {
        const int MOD = 1e9 + 7;
        int m = n + k - 1;      // total "slots" for the combination
        int r = 2 * k;          // choose 2k of them
        
        // Precompute factorials up to m
        vector<long long> fact(m + 1), invFact(m + 1);
        fact[0] = 1;
        for (int i = 1; i <= m; i++) {
            fact[i] = fact[i-1] * i % MOD;
        }
        invFact[m] = modpow(fact[m], MOD - 2, MOD);
        for (int i = m; i > 0; i--) {
            invFact[i-1] = invFact[i] * i % MOD;
        }
        
        // C(m, r) = fact[m] * invFact[r] * invFact[m-r] mod MOD
        if (r < 0 || r > m) return 0;
        long long result = fact[m] * invFact[r] % MOD * invFact[m - r] % MOD;
        return (int)result;
    }
    
private:
    long long modpow(long long base, long long exp, long long mod) {
        long long result = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) result = result * base % mod;
            base = base * base % mod;
            exp >>= 1;
        }
        return result;
    }
};
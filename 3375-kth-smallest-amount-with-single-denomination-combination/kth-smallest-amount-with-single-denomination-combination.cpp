class Solution {
public:
    long long lcm(long long a, long long b) {
        return a / std::__gcd(a, b) * b;
    }
    
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();
        int total = 1 << n;
        
        // Precompute LCM and sign for each non-empty subset
        vector<long long> subsetLcm(total, 0);
        vector<int> subsetSign(total, 0);
        vector<bool> valid(total, false);
        
        for (int mask = 1; mask < total; mask++) {
            long long curLcm = 1;
            int bits = __builtin_popcount(mask);
            bool overflow = false;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    // Check for overflow before computing lcm
                    long long g = std::__gcd(curLcm, (long long)coins[i]);
                    long long newLcm = curLcm / g * coins[i];
                    // amounts up to ~ k * min(coins) which fits in long long comfortably
                    // but guard against absurd overflow anyway
                    if (newLcm > (long long)4e18) {
                        overflow = true;
                        break;
                    }
                    curLcm = newLcm;
                }
            }
            if (overflow) {
                valid[mask] = false;
                continue;
            }
            subsetLcm[mask] = curLcm;
            subsetSign[mask] = (bits % 2 == 1) ? 1 : -1;
            valid[mask] = true;
        }
        
        auto countUpTo = [&](long long x) -> long long {
            long long count = 0;
            for (int mask = 1; mask < total; mask++) {
                if (!valid[mask]) continue;
                long long l = subsetLcm[mask];
                if (l > x) continue;
                count += subsetSign[mask] * (x / l);
            }
            return count;
        };
        
        int minCoin = *min_element(coins.begin(), coins.end());
        long long lo = 1, hi = (long long)k * minCoin;
        
        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (countUpTo(mid) >= k) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        
        return lo;
    }
};
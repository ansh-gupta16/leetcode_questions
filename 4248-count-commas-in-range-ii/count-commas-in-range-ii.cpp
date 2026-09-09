class Solution {
public:
    long long countCommas(long long n) {
        long long total = 0;
        long long lo = 1, hi = 9;
        
        for (int d = 1; d <= 18 && lo <= n; d++) {
            long long curHi = min(hi, n);
            long long cnt = curHi - lo + 1;
            long long commasPerNumber = (d - 1) / 3;
            total += cnt * commasPerNumber;
            
            lo = hi + 1;
            hi = hi * 10 + 9;
        }
        
        return total;
    }
};
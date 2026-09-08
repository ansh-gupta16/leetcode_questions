class Solution {
public:
    int countCommas(int n) {
        long long total = 0;
        long long lower = 1, upper = 9;
        long long N = n;  // promote to long long
        int digits = 1;
        
        while (lower <= N) {
            long long hi = min(upper, N);
            long long count = hi - lower + 1;
            long long commasPerNumber = (digits - 1) / 3;
            total += count * commasPerNumber;
            
            lower = upper + 1;
            upper = upper * 10 + 9;
            digits++;
        }
        
        return (int)total;
    }
};
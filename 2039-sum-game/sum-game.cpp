class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int half = n / 2;
        long long sum1 = 0, sum2 = 0;
        int cnt1 = 0, cnt2 = 0;
        
        for (int i = 0; i < half; i++) {
            if (num[i] == '?') cnt1++;
            else sum1 += num[i] - '0';
        }
        
        for (int i = half; i < n; i++) {
            if (num[i] == '?') cnt2++;
            else sum2 += num[i] - '0';
        }
        
        int totalQ = cnt1 + cnt2;
        if (totalQ % 2 == 1) return true; // Alice wins by parity
        
        long long diff = (sum1 - sum2) + 9LL * (cnt1 - cnt2) / 2;
        return diff != 0;
    }
};
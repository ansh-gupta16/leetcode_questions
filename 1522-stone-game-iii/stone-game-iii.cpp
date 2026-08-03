class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();

        // dp[i] = best score difference (current player - opponent) 
        // achievable by the player to move, considering stones[i..n-1]
        
        vector<long long> dp(n + 1, 0);
        
        for (int i = n - 1; i >= 0; i--) {
            long long best = LLONG_MIN;
            long long takeSum = 0;
            for (int k = 1; k <= 3; k++) {
                if (i + k - 1 < n) {
                    takeSum += stoneValue[i + k - 1];
                    best = max(best, takeSum - dp[i + k]);
                } else {
                    break;
                }
            }
            dp[i] = best;
        }
        
        if (dp[0] > 0) return "Alice";
        else if (dp[0] < 0) return "Bob";
        else return "Tie";
    }
};
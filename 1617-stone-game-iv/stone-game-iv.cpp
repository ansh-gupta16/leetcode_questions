class Solution {
public:
    bool winnerSquareGame(int n) {
        // dp[i] represents if the current player can win starting with i stones
        vector<bool> dp(n + 1, false);
        
        for (int i = 1; i <= n; ++i) {
            // Check all possible square numbers we can subtract
            for (int k = 1; k * k <= i; ++k) {
                // If making this move leaves the opponent in a losing state, we win
                if (!dp[i - k * k]) {
                    dp[i] = true;
                    break; // No need to check further, we found a winning strategy
                }
            }
        }
        
        return dp[n];
    }
};
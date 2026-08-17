class Solution {
    int memo[505][505];
    int prefix[505];

    int solve(int left, int right) {
        // Base case: only one stone left, game ends.
        if (left >= right) return 0;
        
        // Return already computed result
        if (memo[left][right] != -1) return memo[left][right];

        int max_score = 0;
        
        // Try all possible split points k
        for (int k = left; k < right; ++k) {
            int left_sum = prefix[k] - prefix[left - 1];
            int right_sum = prefix[right] - prefix[k];

            if (left_sum < right_sum) {
                // Bob throws away the right row
                max_score = max(max_score, left_sum + solve(left, k));
            } 
            else if (left_sum > right_sum) {
                // Bob throws away the left row
                max_score = max(max_score, right_sum + solve(k + 1, right));
            } 
            else {
                // Alice decides which row to throw away
                max_score = max(max_score, left_sum + max(solve(left, k), solve(k + 1, right)));
            }
        }
        
        return memo[left][right] = max_score;
    }

public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        
        // Initialize prefix sums (1-indexed for easier math)
        prefix[0] = 0;
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }
        
        // Initialize memoization table with -1
        memset(memo, -1, sizeof(memo));
        
        // Start the game with the full range of stones (1 to n)
        return solve(1, n);
    }
};
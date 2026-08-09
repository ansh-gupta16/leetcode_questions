class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        
        // memo[i][m] stores the max stones the current player can get 
        // starting from index i with the given M.
        vector<vector<int>> memo(n, vector<int>(n + 1, -1));
        
        // suffixSum[i] stores the sum of piles[i] to piles[n-1]
        vector<int> suffixSum(n, 0);
        suffixSum[n - 1] = piles[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }
        
        return dfs(piles, 0, 1, memo, suffixSum);
    }
    
private:
    int dfs(const vector<int>& piles, int i, int m, vector<vector<int>>& memo, const vector<int>& suffixSum) {
        int n = piles.size();
        
        // If we've processed all piles, there are no stones left.
        if (i >= n) return 0;
        
        // If the current player can take all the remaining piles, they should do it.
        if (i + 2 * m >= n) {
            return suffixSum[i];
        }
        
        // Return precalculated result if it exists.
        if (memo[i][m] != -1) {
            return memo[i][m];
        }
        
        int maxStones = 0;
        
        // The current player can take X piles, where 1 <= X <= 2 * m
        for (int x = 1; x <= 2 * m; ++x) {
            // Stones current player gets = Total remaining stones - Max stones the other player gets
            int currentStones = suffixSum[i] - dfs(piles, i + x, max(m, x), memo, suffixSum);
            maxStones = max(maxStones, currentStones);
        }
        
        return memo[i][m] = maxStones;
    }
};
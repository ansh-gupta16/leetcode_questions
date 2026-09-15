class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        if (k > n) return 0;
        
        // isPalin[i][j] = true if s[i..j] is a palindrome
        vector<vector<bool>> isPalin(n, vector<bool>(n, false));
        
        // base cases: single characters
        for (int i = 0; i < n; i++) isPalin[i][i] = true;
        
        // length 2
        for (int i = 0; i + 1 < n; i++) {
            isPalin[i][i+1] = (s[i] == s[i+1]);
        }
        
        // length >= 3, build from smaller intervals
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                isPalin[i][j] = (s[i] == s[j]) && isPalin[i+1][j-1];
            }
        }
        
        // dp[i] = max number of non-overlapping valid substrings using s[0..i-1]
        vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i-1]; // don't use position i-1 as end of a chosen substring
            
            // try palindrome of length k ending at i-1, i.e., s[i-k .. i-1]
            if (i - k >= 0 && isPalin[i-k][i-1]) {
                dp[i] = max(dp[i], dp[i-k] + 1);
            }
            
            // try palindrome of length k+1 ending at i-1, i.e., s[i-k-1 .. i-1]
            if (i - k - 1 >= 0 && isPalin[i-k-1][i-1]) {
                dp[i] = max(dp[i], dp[i-k-1] + 1);
            }
        }
        
        return dp[n];
    }
};
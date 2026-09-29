class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        // Quick check: total path length must be even, and start must be '(' and end must be ')'
        if ((m + n - 1) % 2 != 0) return false;
        if (grid[0][0] == ')' || grid[m-1][n-1] == '(') return false;

        // dp[i][j] = set of possible balance values (number of unmatched '(') reachable at (i,j)
        vector<vector<vector<bool>>> dp(m, vector<vector<bool>>(n));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int maxBalance = i + j + 2; // upper bound for balance array size
                dp[i][j] = vector<bool>(maxBalance, false);

                int delta = (grid[i][j] == '(') ? 1 : -1;

                if (i == 0 && j == 0) {
                    if (delta == 1) dp[i][j][1] = true;
                    continue;
                }

                // From top (i-1, j)
                if (i > 0) {
                    for (int b = 0; b < (int)dp[i-1][j].size(); b++) {
                        if (dp[i-1][j][b]) {
                            int nb = b + delta;
                            if (nb >= 0 && nb < (int)dp[i][j].size()) {
                                dp[i][j][nb] = true;
                            }
                        }
                    }
                }
                // From left (i, j-1)
                if (j > 0) {
                    for (int b = 0; b < (int)dp[i][j-1].size(); b++) {
                        if (dp[i][j-1][b]) {
                            int nb = b + delta;
                            if (nb >= 0 && nb < (int)dp[i][j].size()) {
                                dp[i][j][nb] = true;
                            }
                        }
                    }
                }
            }
        }

        return dp[m-1][n-1][0];
    }
};
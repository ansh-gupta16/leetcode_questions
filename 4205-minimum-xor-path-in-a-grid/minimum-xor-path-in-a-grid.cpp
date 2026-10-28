class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        const int SIZE = 1024; // grid values up to 1023, XOR results bounded by 1024

        vector<vector<bitset<SIZE>>> dp(m, vector<bitset<SIZE>>(n));

        dp[0][0][grid[0][0]] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;

                bitset<SIZE> combined;

                if (i > 0) {
                    for (int v = 0; v < SIZE; v++) {
                        if (dp[i-1][j][v]) {
                            combined[v ^ grid[i][j]] = true;
                        }
                    }
                }
                if (j > 0) {
                    for (int v = 0; v < SIZE; v++) {
                        if (dp[i][j-1][v]) {
                            combined[v ^ grid[i][j]] = true;
                        }
                    }
                }

                dp[i][j] = combined;
            }
        }

        for (int v = 0; v < SIZE; v++) {
            if (dp[m-1][n-1][v]) {
                return v;
            }
        }

        return -1; // unreachable in practice
    }
};
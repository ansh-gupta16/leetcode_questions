class Solution {
public:
    int distinctSubseqII(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;
        vector<long long> last(26, -1); // stores dp[j-1] for last occurrence of each char, -1 means not seen

        for (int i = 1; i <= n; i++) {
            int c = s[i - 1] - 'a';
            dp[i] = (2 * dp[i - 1]) % MOD;
            if (last[c] != -1) {
                dp[i] = (dp[i] - last[c] + MOD) % MOD;
            }
            last[c] = dp[i - 1];
        }

        return (int)((dp[n] - 1 + MOD) % MOD);
    }
};
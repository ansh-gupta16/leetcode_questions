class Solution {
public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        const long long MOD = 1e9 + 7;

        // Precompute Pascal's triangle for combinations
        vector<vector<long long>> C(n + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                C[i][j] = (C[i-1][j-1] + (j <= i-1 ? C[i-1][j] : 0)) % MOD;
            }
        }

        long long totalWays = countWays(nums, C);
        long long result = (totalWays - 1 + MOD) % MOD;
        return (int)result;
    }

private:
    long long countWays(vector<int>& arr, vector<vector<long long>>& C) {
        int n = arr.size();
        if (n <= 2) return 1;

        int root = arr[0];
        vector<int> left, right;
        for (int i = 1; i < n; i++) {
            if (arr[i] < root) left.push_back(arr[i]);
            else right.push_back(arr[i]);
        }

        long long leftWays = countWays(left, C);
        long long rightWays = countWays(right, C);

        long long ways = (C[n - 1][left.size()] * leftWays) % 1000000007;
        ways = (ways * rightWays) % 1000000007;

        return ways;
    }
};
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        const int BITS = 30;
        vector<int> bitCount(BITS, 0);

        for (int num : nums) {
            for (int b = 0; b < BITS; b++) {
                if (num & (1 << b)) {
                    bitCount[b]++;
                }
            }
        }

        vector<long long> result(k, 0);

        for (int b = 0; b < BITS; b++) {
            int c = bitCount[b];
            for (int i = 0; i < k && c > 0; i++) {
                result[i] |= (1LL << b);
                c--;
            }
        }

        long long sum = 0;
        for (int i = 0; i < k; i++) {
            sum = (sum + (result[i] % MOD) * (result[i] % MOD)) % MOD;
        }

        return (int)sum;
    }
};
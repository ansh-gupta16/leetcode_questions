class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0);
        vector<long long> cnt(k, 0);

        for (int a : nums) {
            vector<long long> next(k, 0);
            int m = a % k;

            // extend all subarrays ending at previous index
            for (int r = 0; r < k; r++) {
                if (cnt[r]) {
                    next[(r * m) % k] += cnt[r];
                }
            }
            // new subarray consisting of only nums[i]
            next[m] += 1;

            cnt = next;
            for (int r = 0; r < k; r++) {
                result[r] += cnt[r];
            }
        }
        return result;
    }
};
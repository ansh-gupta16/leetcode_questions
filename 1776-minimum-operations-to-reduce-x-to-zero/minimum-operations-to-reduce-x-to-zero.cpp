class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        long long total = 0;
        for (int v : nums) total += v;

        long long target = total - x;
        if (target < 0) return -1;
        if (target == 0) return n; // remove everything

        int left = 0;
        long long sum = 0;
        int best = -1;

        for (int right = 0; right < n; right++) {
            sum += nums[right];
            while (sum > target && left <= right) {
                sum -= nums[left];
                left++;
            }
            if (sum == target) {
                best = max(best, right - left + 1);
            }
        }

        return best == -1 ? -1 : n - best;
    }
};
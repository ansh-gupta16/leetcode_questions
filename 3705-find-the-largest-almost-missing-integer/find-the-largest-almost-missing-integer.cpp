class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_set<int> distinctVals(nums.begin(), nums.end());
        int best = -1;

        for (int x : distinctVals) {
            int count = 0;
            for (int start = 0; start <= n - k; start++) {
                bool found = false;
                for (int i = start; i < start + k; i++) {
                    if (nums[i] == x) {
                        found = true;
                        break;
                    }
                }
                if (found) count++;
                if (count > 1) break; // early exit, no need to keep counting
            }
            if (count == 1) {
                best = max(best, x);
            }
        }

        return best;
    }
};
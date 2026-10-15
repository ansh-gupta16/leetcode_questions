class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        long long result = 0;

        for (int i = 0; i < n; i++) {
            unordered_set<int> distinct;
            for (int j = i; j < n; j++) {
                distinct.insert(nums[j]);
                long long cnt = distinct.size();
                result += cnt * cnt;
            }
        }

        return (int)result;
    }
};
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> ans;
        int s = 0;
        int e = nums.size() - 1;
        while (s <= e) {
            if (s == e) {
                ans.push_back(nums[s] * nums[s]);
            } else {
                ans.push_back(nums[s] * nums[s]);
                ans.push_back(nums[e] * nums[e]);
            }
            s++;
            e--;
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};
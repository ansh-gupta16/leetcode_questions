class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<int> ans;

        for (int i = 0; i < nums.size() - 1; i++) {
            int curr = nums[i] + 1;

            while (curr < nums[i + 1]) {
                ans.push_back(curr);
                curr++;
            }
        }

        return ans;

    }
};
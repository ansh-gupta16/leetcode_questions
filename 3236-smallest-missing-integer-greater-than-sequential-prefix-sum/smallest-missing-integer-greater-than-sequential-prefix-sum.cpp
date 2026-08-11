class Solution {
public:
    int missingInteger(vector<int>& nums) {
        // Step 1: Find the sum of the longest sequential prefix
        int prefixSum = nums[0];
        
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                prefixSum += nums[i];
            } else {
                break; // Sequence broken
            }
        }
        
        // Step 2: Store all numbers in a set for O(1) lookups
        unordered_set<int> presentNums(nums.begin(), nums.end());
        
        // Step 3: Find the smallest missing integer >= prefixSum
        while (presentNums.count(prefixSum)) {
            prefixSum++;
        }
        
        return prefixSum;
    }
};
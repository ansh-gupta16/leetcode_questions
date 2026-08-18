class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        unordered_map<int, int> subarray_count;
        int n = nums.size();
        
        // Loop through all possible starting indices for a subarray of size k
        for (int i = 0; i <= n - k; ++i) {
            unordered_set<int> unique_in_subarray;
            
            // Collect unique elements in the current subarray
            for (int j = i; j < i + k; ++j) {
                unique_in_subarray.insert(nums[j]);
            }
            
            // Increment the subarray presence count for each unique element
            for (int num : unique_in_subarray) {
                subarray_count[num]++;
            }
        }
        
        int max_val = -1;
        
        // Find the largest integer that appears in exactly one subarray
        for (auto const& [num, count] : subarray_count) {
            if (count == 1) {
                max_val = max(max_val, num);
            }
        }
        
        return max_val;
    }
};
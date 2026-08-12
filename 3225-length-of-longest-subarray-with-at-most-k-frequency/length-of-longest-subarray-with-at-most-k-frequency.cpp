class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int left = 0;
        int max_len = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            // Expand the window by including nums[right]
            freq[nums[right]]++;
            
            // If the frequency of the newly added element exceeds k,
            // shrink the window from the left until it's valid again.
            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }
            
            // Update the maximum length found so far
            max_len = max(max_len, right - left + 1);
        }
        
        return max_len;
    }
};
class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int totalXor = 0;
        bool hasNonZero = false;
        
        for (int num : nums) {
            totalXor ^= num;
            if (num != 0) {
                hasNonZero = true;
            }
        }
        
        // If the XOR of all elements is non-zero, the whole array is the answer.
        if (totalXor != 0) {
            return nums.size();
        }
        
        // If the total XOR is 0 but there is at least one non-zero element,
        // we can remove exactly one non-zero element to make the remaining XOR non-zero.
        if (hasNonZero) {
            return nums.size() - 1;
        }
        
        // If all elements are 0, it's impossible to get a non-zero XOR.
        return 0;
    }
};
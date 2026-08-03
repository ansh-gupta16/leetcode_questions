class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
         int n = nums.size();
        if (n <= 2) return n; // arrays of size 0, 1, or 2 are always valid as-is
        
        int k = 2; // first two elements are always kept
        
        for (int i = 2; i < n; i++) {
            if (nums[i] != nums[k - 2]) {
                nums[k] = nums[i];
                k++;
            }
        }
        
        return k;
        
    }
};
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        int write = 1;   // next write position
        int count = 1;   // count of current run
        
        for (int i = 1; i < n; i++) {
            if (nums[i] == nums[i - 1]) {
                count++;
            } else {
                count = 1;
            }
            
            if (count <= 2) {           // allow at most 2 duplicates
                nums[write] = nums[i];
                write++;
            }
        }
        
        return write;

        
    }
};
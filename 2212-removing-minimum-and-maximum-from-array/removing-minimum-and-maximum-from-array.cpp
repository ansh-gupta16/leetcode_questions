class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        int minIdx = 0, maxIdx = 0;
        
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[minIdx]) minIdx = i;
            if (nums[i] > nums[maxIdx]) maxIdx = i;
        }
        
        int i = min(minIdx, maxIdx);
        int j = max(minIdx, maxIdx);
        
        // Option 1: remove both from front (up to j+1 elements)
        int fromFront = j + 1;
        
        // Option 2: remove both from back
        int fromBack = n - i;
        
        // Option 3: remove one from front, one from back
        int mixed = (i + 1) + (n - j);
        
        return min({fromFront, fromBack, mixed});
    }
};
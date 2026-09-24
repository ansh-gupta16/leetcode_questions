class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        for (int i = 0; i < (int)nums.size(); i++) {
            int val = nums[i];
            int digitSum = 0;
            while (val > 0) {
                digitSum += val % 10;
                val /= 10;
            }
            if (digitSum == i) return i;
        }
        return -1;
    }
};
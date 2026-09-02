class Solution {
public:
    bool check(vector<int>& nums1, int t) {
        int n = nums1.size();
        int cntOdd = 0;
        for (int x : nums1) if (x % 2 != 0) cntOdd++;
        
        for (int i = 0; i < n; i++) {
            if (nums1[i] % 2 == t) continue; // already satisfies target directly
            // need some j != i with nums1[j] odd
            int availableOdd = cntOdd - (nums1[i] % 2 != 0 ? 1 : 0);
            if (availableOdd < 1) return false;
        }
        return true;
    }
     
    bool uniformArray(vector<int>& nums1) {
        return check(nums1, 0) || check(nums1, 1);
    }
};
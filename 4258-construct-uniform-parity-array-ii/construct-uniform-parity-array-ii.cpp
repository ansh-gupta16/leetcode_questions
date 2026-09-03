class Solution {
public:
    bool check(vector<pair<long long,int>>& arr, int p) {
        bool seenOdd = false;
        for (auto& [val, par] : arr) {
            if (par != p) {
                if (!seenOdd) return false;
            }
            if (par == 1) seenOdd = true;
        }
        return true;
    }
    bool uniformArray(vector<int>& nums1) {
        int n = nums1.size();
        vector<pair<long long,int>> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = {(long long)nums1[i], nums1[i] & 1};
        }
        sort(arr.begin(), arr.end());
        
        return check(arr, 0) || check(arr, 1);
    }
};
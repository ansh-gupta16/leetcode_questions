class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> best(n, INT_MAX); // best[i] = min length of a valid subarray ending at or before index i
        int left = 0, sum = 0;
        int ans = INT_MAX;
        
        for (int right = 0; right < n; right++) {
            sum += arr[right];
            
            while (sum > target) {
                sum -= arr[left];
                left++;
            }
            
            if (sum == target) {
                int currLen = right - left + 1;
                
                // Check if there's a valid non-overlapping subarray ending before 'left'
                if (left > 0 && best[left - 1] != INT_MAX) {
                    ans = min(ans, best[left - 1] + currLen);
                }
                
                // Update best[right]
                best[right] = currLen;
            }
            
            // Propagate the best value so far (carry forward minimum length seen up to this index)
            if (right > 0) {
                best[right] = min(best[right], best[right - 1]);
            }
        }
        
        return ans == INT_MAX ? -1 : ans;
    }
};
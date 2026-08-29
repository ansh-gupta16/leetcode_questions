class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        
        // Create array of indices, sort by value
        vector<int> indexed(n);
        for (int i = 0; i < n; i++) indexed[i] = i;
        
        sort(indexed.begin(), indexed.end(), [&](int a, int b) {
            return nums[a] < nums[b];
        });
        
        vector<int> result(n);
        
        int i = 0;
        while (i < n) {
            int j = i;
            // Extend group while consecutive sorted values differ by <= limit
            while (j + 1 < n && nums[indexed[j + 1]] - nums[indexed[j]] <= limit) {
                j++;
            }
            
            // Collect original indices for this group and sort them
            vector<int> groupIndices(indexed.begin() + i, indexed.begin() + j + 1);
            sort(groupIndices.begin(), groupIndices.end());
            
            // Values are already sorted (since indexed is sorted by value)
            // Assign smallest value to smallest index
            for (int k = 0; k < (int)groupIndices.size(); k++) {
                result[groupIndices[k]] = nums[indexed[i + k]];
            }
            
            i = j + 1;
        }
        
        return result;
    }
};
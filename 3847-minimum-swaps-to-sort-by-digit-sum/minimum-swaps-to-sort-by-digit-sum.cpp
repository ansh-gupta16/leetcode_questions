class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int> idx(n);
        for (int i = 0; i < n; i++) idx[i] = i;

        auto digitSum = [](int x) {
            int s = 0;
            while (x > 0) {
                s += x % 10;
                x /= 10;
            }
            return s;
        };

        vector<int> ds(n);
        for (int i = 0; i < n; i++) ds[i] = digitSum(nums[i]);

        sort(idx.begin(), idx.end(), [&](int a, int b) {
            if (ds[a] != ds[b]) return ds[a] < ds[b];
            return nums[a] < nums[b];
        });

        // idx[pos] = original index that should go to position 'pos' in sorted order
        // find min swaps via cycle decomposition
        vector<int> targetPos(n); // targetPos[originalIndex] = where it should go
        for (int pos = 0; pos < n; pos++) {
            targetPos[idx[pos]] = pos;
        }

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || targetPos[i] == i) continue;
            int cycleLen = 0;
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = targetPos[j];
                cycleLen++;
            }
            swaps += cycleLen - 1;
        }

        return swaps;
    }
};
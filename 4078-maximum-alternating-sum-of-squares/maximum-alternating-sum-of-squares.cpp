class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> squares(n);
        for (int i = 0; i < n; i++) {
            squares[i] = (long long)nums[i] * nums[i];
        }

        sort(squares.rbegin(), squares.rend()); // descending order

        int posCount = (n + 1) / 2; // ceil(n/2) positions get '+'
        long long result = 0;

        for (int i = 0; i < n; i++) {
            if (i < posCount) {
                result += squares[i];
            } else {
                result -= squares[i];
            }
        }

        return result;
    }
};
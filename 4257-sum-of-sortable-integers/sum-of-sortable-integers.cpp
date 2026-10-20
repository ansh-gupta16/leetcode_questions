class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());

        int maxVal = *max_element(nums.begin(), nums.end());
        vector<int> diff(maxVal + 1, 0);

        // collect divisors of n
        vector<int> divisors;
        for (int d = 1; (long long)d * d <= n; d++) {
            if (n % d == 0) {
                divisors.push_back(d);
                if (d != n / d) divisors.push_back(n / d);
            }
        }

        long long result = 0;

        for (int k : divisors) {
            int m = n / k;
            bool valid = true;

            for (int i = 0; i < m && valid; i++) {
                int start = i * k;
                vector<int> touched;
                touched.reserve(2 * k);

                for (int j = 0; j < k; j++) {
                    int a = nums[start + j];
                    int b = sortedNums[start + j];
                    diff[a]++;
                    diff[b]--;
                    touched.push_back(a);
                    touched.push_back(b);
                }

                bool multisetOk = true;
                for (int idx : touched) {
                    if (diff[idx] != 0) {
                        multisetOk = false;
                    }
                }

                // reset diff array
                for (int idx : touched) {
                    diff[idx] = 0;
                }

                if (!multisetOk) {
                    valid = false;
                    continue;
                }

                // circular descent check
                int descents = 0;
                for (int j = 0; j < k; j++) {
                    int next = (j + 1) % k;
                    if (nums[start + j] > nums[start + next]) {
                        descents++;
                        if (descents > 1) break;
                    }
                }

                if (descents > 1) {
                    valid = false;
                }
            }

            if (valid) {
                result += k;
            }
        }

        return (int)result;
    }
};
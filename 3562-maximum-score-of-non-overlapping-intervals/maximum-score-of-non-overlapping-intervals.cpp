class Solution {
public:
    struct Result {
        long long score;
        vector<int> idx;   // chosen original indices, kept sorted ascending
    };

    // true if a is strictly better than b:
    // higher score wins; on tie, lexicographically smaller index list wins.
    static bool isBetter(const Result &a, const Result &b) {
        if (a.score != b.score) return a.score > b.score;
        return a.idx < b.idx;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // (l, r, w, originalIndex), sorted by r ascending
        vector<array<long long,4>> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = { (long long)intervals[i][0],
                       (long long)intervals[i][1],
                       (long long)intervals[i][2],
                       (long long)i };
        }
        sort(arr.begin(), arr.end(),
             [](const array<long long,4>& a, const array<long long,4>& b) {
                 return a[1] < b[1];
             });

        vector<long long> rArr(n);
        for (int i = 0; i < n; i++) rArr[i] = arr[i][1];

        // dp[i][j]: considering first i sorted intervals, choose at most j of them
        vector<vector<Result>> dp(n + 1, vector<Result>(5, Result{0, {}}));

        for (int i = 1; i <= n; i++) {
            long long l = arr[i - 1][0];
            long long w = arr[i - 1][2];
            int origIdx = (int)arr[i - 1][3];

            // p = number of (sorted) intervals with r < l  (strict, since sharing an
            // endpoint counts as overlapping)
            int p = (int)(lower_bound(rArr.begin(), rArr.end(), l) - rArr.begin());

            // skip interval i-1
            for (int j = 0; j <= 4; j++) {
                dp[i][j] = dp[i - 1][j];
            }

            // take interval i-1
            for (int j = 1; j <= 4; j++) {
                Result cand = dp[p][j - 1];
                cand.score += w;
                auto pos = upper_bound(cand.idx.begin(), cand.idx.end(), origIdx);
                cand.idx.insert(pos, origIdx);

                if (isBetter(cand, dp[i][j])) {
                    dp[i][j] = cand;
                }
            }
        }

        return dp[n][4].idx;
    }
};
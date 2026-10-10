class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        vector<long long> diff(n);
        long long k = (long long)k1 + k2;
        long long maxDiff = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs((long long)nums1[i] - nums2[i]);
            maxDiff = max(maxDiff, diff[i]);
        }

        if (maxDiff == 0) {
            return 0; // all diffs already zero
        }

        // cost(L) = sum over d>L of (d - L): operations needed to bring all values down to L
        auto cost = [&](long long L) -> long long {
            long long total = 0;
            for (long long d : diff) {
                if (d > L) total += (d - L);
            }
            return total;
        };

        // find minimal L in [0, maxDiff] such that cost(L) <= k
        long long lo = 0, hi = maxDiff;
        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (cost(mid) <= k) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        long long L = lo;

        long long cnt = 0;      // count of diff[i] >= L (eligible for further reduction to L-1)
        long long opsUsed = 0;  // cost(L)
        for (long long d : diff) {
            if (d >= L) cnt++;
            if (d > L) opsUsed += (d - L);
        }

        long long remaining = k - opsUsed;
        if (L == 0) {
            remaining = 0; // can't reduce below 0 usefully
        }
        // remaining should be < cnt by binary search minimality when L > 0

        long long reduceToLminus1 = remaining; // this many elements go from L to L-1
        long long stayAtL = cnt - reduceToLminus1;

        long long result = 0;
        for (long long d : diff) {
            if (d < L) {
                result += d * d;
            }
        }
        result += stayAtL * (L * L);
        if (reduceToLminus1 > 0) {
            result += reduceToLminus1 * ((L - 1) * (L - 1));
        }

        return result;
    }
};
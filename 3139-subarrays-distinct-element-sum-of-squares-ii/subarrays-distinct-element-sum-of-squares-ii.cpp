class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        const long long MOD = 1e9 + 7;

        // Fenwick tree supporting range update + range sum query
        vector<long long> bit1(n + 2, 0), bit2(n + 2, 0);

        auto updateBIT = [&](vector<long long>& bit, int i, long long val) {
            for (++i; i <= n; i += i & (-i)) bit[i] += val;
        };
        auto queryBIT = [&](vector<long long>& bit, int i) -> long long {
            long long s = 0;
            for (++i; i > 0; i -= i & (-i)) s += bit[i];
            return s;
        };
        auto rangeAdd = [&](int l, int r, long long val) {
            if (l > r) return;
            updateBIT(bit1, l, val);
            updateBIT(bit1, r + 1, -val);
            updateBIT(bit2, l, val * l);
            updateBIT(bit2, r + 1, -val * (r + 1));
        };
        auto prefixSum = [&](int i) -> long long {
            if (i < 0) return 0;
            return queryBIT(bit1, i) * (i + 1) - queryBIT(bit2, i);
        };
        auto rangeSum = [&](int l, int r) -> long long {
            if (l > r) return 0;
            return prefixSum(r) - prefixSum(l - 1);
        };

        vector<int> last(100001, -1);
        long long f = 0;
        long long result = 0;

        for (int r = 0; r < n; r++) {
            int v = nums[r];
            int p = last[v];
            last[v] = r;

            long long S = rangeSum(p + 1, r - 1);
            long long add = (2 * S % MOD + (r - p)) % MOD;
            f = (f + add) % MOD;
            result = (result + f) % MOD;

            // update distinct counts: range (p+1, r-1) gets +1, position r becomes +1
            rangeAdd(p + 1, r - 1, 1);
            rangeAdd(r, r, 1);
        }

        return (int)((result % MOD + MOD) % MOD);
    }
};
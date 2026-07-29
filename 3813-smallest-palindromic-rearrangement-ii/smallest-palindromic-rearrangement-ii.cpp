class Solution {
public:
    static const long long LIMIT = 1000001;

    long long comb(int n, int r) {
        if (r > n) return 0;
        r = min(r, n - r);

        long long ans = 1;

        for (int i = 1; i <= r; i++) {
            long long num = n - r + i;
            long long den = i;

            long long g = std::gcd(num, den);
            num /= g;
            den /= g;

            g = std::gcd(ans, den);
            ans /= g;
            den /= g;

            if (ans > LIMIT / num)
                return LIMIT;

            ans *= num;
            ans /= den;

            if (ans > LIMIT)
                return LIMIT;
        }

        return ans;
    }

    long long countWays(vector<int>& cnt) {
        int total = 0;
        for (int x : cnt) total += x;

        long long ans = 1;
        int remain = total;

        for (int x : cnt) {
            if (x == 0) continue;

            long long c = comb(remain, x);

            if (c == 0) return 0;

            if (ans > LIMIT / c)
                ans = LIMIT;
            else
                ans *= c;

            if (ans > LIMIT)
                ans = LIMIT;

            remain -= x;
        }

        return ans;
    }
    string smallestPalindrome(string s, int k) {
         vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        vector<int> half(26, 0);
        string mid = "";

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] % 2)
                mid.push_back(char('a' + i));
        }

        if (countWays(half) < k)
            return "";

        string left = "";
        int len = s.size() / 2;

        for (int pos = 0; pos < len; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0)
                    continue;

                half[c]--;

                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                }

                k -= ways;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};
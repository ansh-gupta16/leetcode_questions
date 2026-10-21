class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        string t = s;
        sort(t.begin(), t.end());

        if (s == t) return 0;

        int l = 0, r = n - 1;
        while (l < n && s[l] == t[l]) l++;
        while (r >= 0 && s[r] == t[r]) r--;

        if (l > 0 || r < n - 1) return 1;

        if (n == 2) return -1;

        char maxRest = *max_element(s.begin() + 1, s.end());
        char minRest = *min_element(s.begin(), s.end() - 1);

        if (s[0] > maxRest && s[n - 1] < minRest) return 3;

        return 2;
    }
};
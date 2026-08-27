class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> sCount(26, 0);
        for (char ch : s) sCount[ch - 'a']++;

        // Find max prefix length L such that target[0..L-1] is feasible from s's multiset
        vector<int> running(26, 0);
        int L = 0;
        for (int idx = 0; idx < n; idx++) {
            int c = target[idx] - 'a';
            running[c]++;
            if (running[c] > sCount[c]) break;
            L = idx + 1;
        }

        // prefixCount = counts of target[0..L-1]
        vector<int> prefixCount(26, 0);
        for (int idx = 0; idx < L; idx++) prefixCount[target[idx] - 'a']++;

        for (int i = L; i >= 0; i--) {
            if (i < n) {
                vector<int> remaining(26, 0);
                for (int k = 0; k < 26; k++) remaining[k] = sCount[k] - prefixCount[k];

                int tc = target[i] - 'a';
                for (int c = tc + 1; c < 26; c++) {
                    if (remaining[c] > 0) {
                        remaining[c]--;
                        string result = target.substr(0, i);
                        result += char('a' + c);
                        for (int k = 0; k < 26; k++) {
                            result += string(remaining[k], char('a' + k));
                        }
                        return result;
                    }
                }
            }
            if (i == 0) break;
            prefixCount[target[i - 1] - 'a']--;
        }

        return "";
    }
};
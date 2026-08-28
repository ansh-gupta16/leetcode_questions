class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26, 0);
        for (char ch : s) cnt[ch - 'a']++;

        vector<int> oddChars;
        for (int i = 0; i < 26; i++)
            if (cnt[i] % 2 == 1) oddChars.push_back(i);

        if (oddChars.size() > 1) return "";  // no palindromic permutation exists

        int h = n / 2;
        vector<int> pairCount(26, 0);
        for (int i = 0; i < 26; i++) pairCount[i] = cnt[i] / 2;
        string oddChar = oddChars.empty() ? "" : string(1, char('a' + oddChars[0]));

        string T = target;

        auto buildFromH = [&](const string& H) -> string {
            string revH(H.rbegin(), H.rend());
            return H + oddChar + revH;
        };

        // ---------- Case 1: try H = T[0:h] exactly ----------
        vector<int> prefCnt(26, 0);
        for (int i = 0; i < h; i++) prefCnt[T[i] - 'a']++;

        if (prefCnt == pairCount) {
            string P = buildFromH(T.substr(0, h));
            if (P > T) return P;
            // else fall through to case 2
        }

        // ---------- Case 2: find smallest H strictly greater than T[0:h] ----------
        // prefixCounts[i] = char counts of T[0:i] (only valid up to maxI)
        vector<vector<int>> prefixCounts(h + 1, vector<int>(26, 0));
        vector<int> cur(26, 0);
        int maxI = 0;
        bool feasible = true;
        for (int i = 0; i < h; i++) {
            int c = T[i] - 'a';
            if (feasible && cur[c] + 1 <= pairCount[c]) {
                cur[c]++;
                maxI = i + 1;
            } else {
                feasible = false;
            }
            prefixCounts[i + 1] = cur;
        }

        int startI = min(maxI, h - 1);
        for (int i = startI; i >= 0; i--) {
            vector<int>& pc = prefixCounts[i];
            vector<int> avail(26);
            for (int k = 0; k < 26; k++) avail[k] = pairCount[k] - pc[k];
            int tChar = T[i] - 'a';

            int chosen = -1;
            for (int c = tChar + 1; c < 26; c++) {
                if (avail[c] > 0) {
                    chosen = c;
                    break;
                }
            }

            if (chosen != -1) {
                avail[chosen]--;
                string rest;
                for (int c = 0; c < 26; c++) {
                    if (avail[c] > 0) {
                        rest += string(avail[c], char('a' + c));
                    }
                }
                string H = T.substr(0, i) + string(1, char('a' + chosen)) + rest;
                return buildFromH(H);
            }
        }

        return "";
    }
};
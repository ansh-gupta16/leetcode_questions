class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        vector<int> first(26, -1), last(26, -1);
        
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (first[c] == -1) first[c] = i;
            last[c] = i;
        }
        
        // Generate candidate intervals only from positions that are
        // the first occurrence of some character (at most 26 of them).
        vector<pair<int,int>> candidates;
        for (int c = 0; c < 26; c++) {
            if (first[c] == -1) continue;
            int i = first[c];
            int end = last[c];
            int minFirst = first[c];
            int j = i;
            while (j <= end) {
                int cc = s[j] - 'a';
                end = max(end, last[cc]);
                minFirst = min(minFirst, first[cc]);
                j++;
            }
            // Valid only if no character inside started before i
            if (minFirst >= i) {
                candidates.push_back({i, end});
            }
        }
        
        // Sort by length ascending -> prefer smaller/nested intervals first
        sort(candidates.begin(), candidates.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
            return (a.second - a.first) < (b.second - b.first);
        });
        
        vector<bool> used(n, false);
        vector<pair<int,int>> chosen;
        
        for (auto& cand : candidates) {
            int i = cand.first, end = cand.second;
            bool ok = true;
            for (int k = i; k <= end; k++) {
                if (used[k]) { ok = false; break; }
            }
            if (ok) {
                chosen.push_back(cand);
                for (int k = i; k <= end; k++) used[k] = true;
            }
        }
        
        vector<string> result;
        for (auto& p : chosen) {
            result.push_back(s.substr(p.first, p.second - p.first + 1));
        }
        return result;
    }
};
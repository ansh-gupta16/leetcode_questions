class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        string ans = "";
        int bestLen = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = i; j < n; j++) {
                if (s[j] == '1') count++;
                if (count == k) {
                    int len = j - i + 1;
                    string cand = s.substr(i, len);
                    if (len < bestLen) {
                        bestLen = len;
                        ans = cand;
                    } else if (len == bestLen && cand < ans) {
                        ans = cand;
                    }
                    break; // no need to extend further from this i since count exceeds k after
                }
            }
        }
        
        return ans;
    }
};
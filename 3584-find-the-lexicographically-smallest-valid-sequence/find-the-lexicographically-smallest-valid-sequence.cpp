class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        // last_pos[j] stores the largest index in word1 from which 
        // the suffix word2[j...m-1] can be matched exactly.
        vector<int> last_pos(m, -1);
        
        int p = n - 1;
        for (int j = m - 1; j >= 0; --j) {
            while (p >= 0 && word1[p] != word2[j]) {
                p--;
            }
            last_pos[j] = p;
            if (p >= 0) p--; // move left for the next character
        }

        vector<int> result;
        bool used_change = false;
        p = 0; // forward pointer in word1

        for (int i = 0; i < m; ++i) {
            bool matched = false;

            while (p < n) {
                if (word1[p] == word2[i]) {
                    // Exact match
                    result.push_back(p);
                    p++;
                    matched = true;
                    break;
                } else if (!used_change) {
                    // Check if taking a mismatch at 'p' allows the remaining suffix to match
                    bool can_finish_suffix = (i == m - 1) || (last_pos[i + 1] > p);
                    if (can_finish_suffix) {
                        result.push_back(p);
                        used_change = true;
                        p++;
                        matched = true;
                        break;
                    }
                }
                p++; // Move forward if no match or invalid mismatch position
            }

            // If we couldn't match the current character of word2, no valid sequence exists
            if (!matched) return {};
        }

        return result;
    }
};
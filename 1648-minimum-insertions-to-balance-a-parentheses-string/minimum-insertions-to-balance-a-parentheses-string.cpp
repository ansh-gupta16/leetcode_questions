class Solution {
public:
    int minInsertions(string s) {
        int n = s.size();
        int open = 0;   // count of unmatched '('
        int res = 0;    // insertions needed
        int i = 0;

        while (i < n) {
            if (s[i] == '(') {
                open++;
                i++;
            } else { // s[i] == ')'
                int count = 0;
                while (i < n && s[i] == ')' && count < 2) {
                    count++;
                    i++;
                }
                if (count == 1) {
                    // only found one ')', need to insert another to complete the pair
                    res++;
                }
                if (open > 0) {
                    open--; // matched with an existing '('
                } else {
                    res++; // no '(' available, need to insert one
                }
            }
        }

        // each remaining unmatched '(' needs two ')' inserted
        res += open * 2;

        return res;
    }
};
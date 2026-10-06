class Solution {
public:
    int minAddToMakeValid(string s) {
        int openNeeded = 0;  // unmatched '(' waiting for ')'
        int insertions = 0;  // count of ')' we had to "insert" to match

        for (char c : s) {
            if (c == '(') {
                openNeeded++;
            } else { // c == ')'
                if (openNeeded > 0) {
                    openNeeded--;
                } else {
                    insertions++; // no open to match, need to insert a '('
                }
            }
        }

        return insertions + openNeeded;
    }
};
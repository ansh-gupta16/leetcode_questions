class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int c0 = 0, c1 = 0, c2 = 0;
        
        // Count stones based on their modulo 3 value
        for (int stone : stones) {
            int mod = stone % 3;
            if (mod == 0) c0++;
            else if (mod == 1) c1++;
            else c2++;
        }
        
        // If the number of 0s is even, Alice wins if she has at least one 1 and one 2.
        if (c0 % 2 == 0) {
            return c1 > 0 && c2 > 0;
        } 
        // If the number of 0s is odd, Alice wins if the difference between 1s and 2s is greater than 2.
        else {
            return abs(c1 - c2) > 2;
        }
    }
};
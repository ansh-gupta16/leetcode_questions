class Solution {
public:
    int maximumLengthSubstring(string s) {
        int left = 0, maxLength = 0;
        int count[26] = {0}; // To store frequency of lowercase English letters

        for (int right = 0; right < s.length(); ++right) {
            count[s[right] - 'a']++;

            // If the character count exceeds 2, shrink the window from the left
            while (count[s[right] - 'a'] > 2) {
                count[s[left] - 'a']--;
                left++;
            }

            // Update the maximum length of a valid substring
            maxLength = max(maxLength, right - left + 1);
        }

        return maxLength;
    }
};
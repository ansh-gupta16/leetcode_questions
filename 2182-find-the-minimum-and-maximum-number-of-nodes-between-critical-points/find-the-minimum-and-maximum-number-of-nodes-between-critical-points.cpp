/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int minDistance = INT_MAX;
        int firstIdx = -1, prevIdx = -1, lastIdx = -1;
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        int idx = 1;
        
        while (curr->next != nullptr) {
            bool isMax = curr->val > prev->val && curr->val > curr->next->val;
            bool isMin = curr->val < prev->val && curr->val < curr->next->val;
            
            if (isMax || isMin) {
                if (firstIdx == -1) {
                    firstIdx = idx;
                } else {
                    minDistance = min(minDistance, idx - prevIdx);
                }
                prevIdx = idx;
                lastIdx = idx;
            }
            
            prev = curr;
            curr = curr->next;
            idx++;
        }
        
        if (firstIdx == -1 || firstIdx == lastIdx) {
            return {-1, -1};
        }
        
        int maxDistance = lastIdx - firstIdx;
        return {minDistance, maxDistance};
    }
};
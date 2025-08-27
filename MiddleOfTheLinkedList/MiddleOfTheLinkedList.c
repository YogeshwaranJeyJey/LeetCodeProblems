/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

 int lengthOfLinkedList(struct ListNode* head){
    struct ListNode* temp = head;
    int count = 0;
    while(temp){
        count++;
        temp = temp->next;
    }
    return count;
 }
struct ListNode* middleNode(struct ListNode* head) {
    int middleNodeIndex = lengthOfLinkedList(head) / 2, count = 0;
    struct ListNode* temp = head;
    while(temp){
        if(middleNodeIndex == count)
            return temp;
        count++;
        temp = temp->next;
    }
    return NULL;
}
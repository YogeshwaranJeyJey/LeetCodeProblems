struct TreeNode* createNewNode(struct ListNode* midNode){
    struct TreeNode* newNode = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    if(!newNode) return NULL;
    newNode->val = midNode->val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct TreeNode* sortedListToBST(struct ListNode* head) {
    if (head == NULL) 
        return NULL;
    if (head->next == NULL) {
        return createNewNode(head);
    }
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    struct ListNode* prev = NULL;

    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    struct TreeNode* root = createNewNode(slow);
    if (prev != NULL) {
        prev->next = NULL;
        root->left = sortedListToBST(head);
    }
    root->right = sortedListToBST(slow->next);

    return root;
}
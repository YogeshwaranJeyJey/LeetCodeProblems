/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int countNodes(struct TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void inorderHelper(struct TreeNode* root, int* resultArray, int* index) {
    if (!root) return;
    inorderHelper(root->left, resultArray, index);
    resultArray[(*index)++] = root->val;
    inorderHelper(root->right, resultArray, index);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    *returnSize = countNodes(root);
    int* resultArray = malloc((*returnSize) * sizeof(int));
    if (!resultArray) return NULL;

    int index = 0;
    inorderHelper(root, resultArray, &index);
    return resultArray;
}
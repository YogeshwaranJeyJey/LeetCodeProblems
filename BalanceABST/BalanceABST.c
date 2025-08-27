/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isValidBST(struct TreeNode* root, long min, long max){
    if(root == NULL)
        return true;
    if(root->val <= min || root->val >= max)
        return false;
    return isValidBST(root->left, min, root->val) && 
            isValidBST(root->right, root->val, max);
}

int countNodes(struct TreeNode* root) {
    if (root == NULL) return 0;
    return countNodes(root->left) + countNodes(root->right) + 1;
}

void inOrderTraversal(struct TreeNode* root, int* resArr, int* index){
    if(root == NULL) return;
    inOrderTraversal(root->left, resArr, index);
    resArr[(*index)++] = root->val;
    inOrderTraversal(root->right, resArr, index);
}
struct TreeNode* createNewNode(int newVal){
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if(!newNode) return NULL;
    newNode->val = newVal;
    newNode->left = newNode->right = NULL;
    return newNode;
}
struct TreeNode* constructBST(int* arr, int start, int end){
    if(start > end) return NULL;
    int mid = (start + end) / 2;
    struct TreeNode* newNode = createNewNode(arr[mid]);
    newNode->left = constructBST(arr, start, mid - 1);
    newNode->right = constructBST(arr, mid + 1, end);
    return newNode;
}

struct TreeNode* balanceBST(struct TreeNode* root) {
    int nodeCount = countNodes(root);
    int inOrderArr[nodeCount];
    if(!isValidBST(root, LONG_MIN, LONG_MAX))
        return NULL;
    int index = 0;
    inOrderTraversal(root, inOrderArr, &index);
    int start = 0, end = nodeCount - 1;
    return constructBST(inOrderArr, start, end);
}
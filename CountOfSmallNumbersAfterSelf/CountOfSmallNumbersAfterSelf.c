/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct AVLNode {
    int val;
    int height;
    int leftCount;
    int subtreeSize;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

int max(int a, int b) { return (a > b) ? a : b; }

int getSubtreeSize(AVLNode* node) { return node ? node->subtreeSize : 0; }
int getLeftCount(AVLNode* node) { return node ? node->leftCount : 0; }
int getHeight(AVLNode* node) { return node ? node->height : 0; }

AVLNode* createNode(int val) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->val = val;
    node->height = 1;
    node->leftCount = 0;
    node->subtreeSize = 1;
    node->left = node->right = NULL;
    return node;
}

void updateNode(AVLNode* node) {
    if (!node) return;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    node->leftCount = getSubtreeSize(node->left);
    node->subtreeSize = 1 + getSubtreeSize(node->left) + getSubtreeSize(node->right);
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateNode(y);
    updateNode(x);

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateNode(x);
    updateNode(y);

    return y;
}

int getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* insertAVL(AVLNode* node, int val, int* countSmaller) {
    if (!node) return createNode(val);

    if (val <= node->val) {
        node->left = insertAVL(node->left, val, countSmaller);
    } else {
        *countSmaller += node->leftCount + 1;
        node->right = insertAVL(node->right, val, countSmaller);
    }

    updateNode(node);

    int balance = getBalance(node);

    if (balance > 1 && val <= node->left->val)
        return rightRotate(node);

    if (balance > 1 && val > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && val > node->right->val)
        return leftRotate(node);

    if (balance < -1 && val <= node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void freeAVL(AVLNode* root) {
    if (!root) return;
    freeAVL(root->left);
    freeAVL(root->right);
    free(root);
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* result = (int*)malloc(numsSize * sizeof(int));
    if (numsSize == 0) return result;

    AVLNode* root = NULL;

    for (int i = numsSize - 1; i >= 0; i--) {
        int count = 0;
        root = insertAVL(root, nums[i], &count);
        result[i] = count;
    }

    freeAVL(root);
    return result;
}
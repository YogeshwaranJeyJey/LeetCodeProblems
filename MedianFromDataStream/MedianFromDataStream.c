typedef struct Node {
    int val, height, count, size;
    struct Node *left, *right;
} Node;

typedef struct {
    Node* root;
} MedianFinder;

int height(Node* n) { 
    return n ? n->height : 0; 
}
int size(Node* n)   { 
    return n ? n->size : 0; 
}
int max(int a, int b) { 
    return a > b ? a : b; 
}

Node* createNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->count = 1;
    node->height = 1;
    node->size = 1;
    node->left = node->right = NULL;
    return node;
}

void update(Node* n) {
    if (n) {
        n->height = 1 + max(height(n->left), height(n->right));
        n->size = n->count + size(n->left) + size(n->right);
    }
}

int getBalance(Node* n) { 
    return n ? height(n->left) - height(n->right) : 0; 
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    update(y);
    update(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    update(x);
    update(y);
    return y;
}

Node* insert(Node* node, int val) {
    if (!node) return createNode(val);

    if (val == node->val) {
        node->count++;
    } else if (val < node->val) {
        node->left = insert(node->left, val);
    } else {
        node->right = insert(node->right, val);
    }

    update(node);

    int balance = getBalance(node);
    if (balance > 1 && val < node->left->val) return rotateRight(node);
    if (balance < -1 && val > node->right->val) return rotateLeft(node);
    if (balance > 1 && val > node->left->val) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && val < node->right->val) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

int kth(Node* root, int k) {
    if (!root) return -1;
    int leftSize = size(root->left);
    if (k <= leftSize) return kth(root->left, k);
    if (k > leftSize + root->count) return kth(root->right, k - leftSize - root->count);
    return root->val;
}

MedianFinder* medianFinderCreate() {
    MedianFinder* mf = (MedianFinder*)malloc(sizeof(MedianFinder));
    mf->root = NULL;
    return mf;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    obj->root = insert(obj->root, num);
}

double medianFinderFindMedian(MedianFinder* obj) {
    int n = size(obj->root);
    if (n % 2 == 1) {
        return kth(obj->root, n / 2 + 1);
    } else {
        int left = kth(obj->root, n / 2);
        int right = kth(obj->root, n / 2 + 1);
        return (left + right) / 2.0;
    }
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void medianFinderFree(MedianFinder* obj) {
    freeTree(obj->root);
    free(obj);
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 
 * double param_2 = medianFinderFindMedian(obj);
 
 * medianFinderFree(obj);
*/
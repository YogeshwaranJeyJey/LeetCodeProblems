#define MOD 1000000007

typedef struct Node {
    int val;
    int height;
    int size;
    int count;
    struct Node* left;
    struct Node* right;
} Node;

int getHeight(Node* n) { 
    return n ? n->height : 0; 
}
int getSize(Node* n)   { 
    return n ? n->size : 0; 
}
int maxInt(int a, int b){ 
    return a > b ? a : b; 
}

Node* createNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->val = val;
    n->height = 1;
    n->size = 1;
    n->count = 1;
    n->left = n->right = NULL;
    return n;
}

void updateNode(Node* n) {
    if (!n) return;
    n->height = 1 + maxInt(getHeight(n->left), getHeight(n->right));
    n->size = n->count + getSize(n->left) + getSize(n->right);
}

int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateNode(y);
    updateNode(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateNode(x);
    updateNode(y);
    return y;
}

Node* insertNode(Node* root, int val, long long* smaller, int* equalBefore) {
    if (!root) {
        return createNode(val);
    }
    if (val == root->val) {
        *smaller += getSize(root->left);
        *equalBefore = root->count;
        root->count++;              
    } else if (val < root->val) {
        root->left = insertNode(root->left, val, smaller, equalBefore);
    } else {
        *smaller += getSize(root->left) + root->count;
        root->right = insertNode(root->right, val, smaller, equalBefore);
    }

    updateNode(root);

    int balance = getBalance(root);

    if (balance > 1 && val < root->left->val)
        return rotateRight(root);

    if (balance < -1 && val > root->right->val)
        return rotateLeft(root);

    if (balance > 1 && val > root->left->val) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && val < root->right->val) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

int createSortedArray(int* instructions, int instructionsSize) {
    Node* root = NULL;
    long long ans = 0;
    int totalInserted = 0;
    for (int i = 0; i < instructionsSize; i++) {
        long long smaller = 0;
        int equalBefore = 0;
        root = insertNode(root, instructions[i], &smaller, &equalBefore);
        long long greater = (long long)totalInserted - smaller - equalBefore;
        long long cost = smaller < greater ? smaller : greater;
        ans = (ans + cost) % MOD;
        totalInserted++;
    }
    return (int)ans;
}
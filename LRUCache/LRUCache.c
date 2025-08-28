typedef struct Node {
    int key, value;
    struct Node *prev, *next;
} Node;

typedef struct {
    int capacity;
    int count;
    Node *head, *tail;   
    Node **map;          
    int size;        
} LRUCache;

Node* createNode(int key, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->prev = node->next = NULL;
    return node;
}

int hash(LRUCache* obj, int key) {
    return (key % obj->size + obj->size) % obj->size;
}

void mapPut(LRUCache* obj, int key, Node* node) {
    int idx = hash(obj, key);
    while (obj->map[idx] && obj->map[idx]->key != key)
        idx = (idx + 1) % obj->size;
    obj->map[idx] = node;
}

Node* mapGet(LRUCache* obj, int key) {
    int idx = hash(obj, key);
    while (obj->map[idx]) {
        if (obj->map[idx]->key == key)
            return obj->map[idx];
        idx = (idx + 1) % obj->size;
    }
    return NULL;
}

void mapRemove(LRUCache* obj, int key) {
    int idx = hash(obj, key);
    while (obj->map[idx]) {
        if (obj->map[idx]->key == key) {
            obj->map[idx] = NULL;
            return;
        }
        idx = (idx + 1) % obj->size;
    }
}

void addNode(LRUCache* obj, Node* node) {
    node->next = obj->head->next;
    node->prev = obj->head;
    obj->head->next->prev = node;
    obj->head->next = node;
}

void removeNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void moveToHead(LRUCache* obj, Node* node) {
    removeNode(node);
    addNode(obj, node);
}

Node* popTail(LRUCache* obj) {
    Node* res = obj->tail->prev;
    removeNode(res);
    return res;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->count = 0;
    cache->size = 10007;
    cache->map = (Node**)calloc(cache->size, sizeof(Node*));

    cache->head = createNode(0, 0);
    cache->tail = createNode(0, 0);
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;

    return cache;
}

int lRUCacheGet(LRUCache* obj, int key) {
    Node* node = mapGet(obj, key);
    if (!node) return -1;
    moveToHead(obj, node);
    return node->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    Node* node = mapGet(obj, key);

    if (!node) {
        Node* newNode = createNode(key, value);
        mapPut(obj, key, newNode);
        addNode(obj, newNode);
        obj->count++;

        if (obj->count > obj->capacity) {
            Node* tail = popTail(obj);
            mapRemove(obj, tail->key);
            free(tail);
            obj->count--;
        }
    } else {
        node->value = value;
        moveToHead(obj, node);
    }
}

void lRUCacheFree(LRUCache* obj) {
    Node* cur = obj->head;
    while (cur) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }
    free(obj->map);
    free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 typedef struct {
    int *data;
    int front, back, size;
} Deque;

Deque* createDeque(int size) {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->data = (int*)malloc(size * sizeof(int));
    dq->front = 0;
    dq->back = -1;
    dq->size = 0;
    return dq;
}

void pushBack(Deque* dq, int val, int capacity) {
    dq->back = (dq->back + 1) % capacity;
    dq->data[dq->back] = val;
    dq->size++;
}

void popBack(Deque* dq, int capacity) {
    dq->back = (dq->back - 1 + capacity) % capacity;
    dq->size--;
}

void popFront(Deque* dq, int capacity) {
    dq->front = (dq->front + 1) % capacity;
    dq->size--;
}

int front(Deque* dq) {
    return dq->data[dq->front];
}

int back(Deque* dq) {
    return dq->data[dq->back];
}

int empty(Deque* dq) {
    return dq->size == 0;
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
     if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }
    int* result = (int*)malloc((numsSize - k + 1) * sizeof(int));
    *returnSize = 0;
    Deque* dq = createDeque(numsSize);
    for (int i = 0; i < numsSize; i++) {
        if (!empty(dq) && front(dq) <= i - k)
            popFront(dq, numsSize);
        while (!empty(dq) && nums[back(dq)] <= nums[i])
            popBack(dq, numsSize);
        pushBack(dq, i, numsSize);
        if (i >= k - 1)
            result[(*returnSize)++] = nums[front(dq)];
    }
    return result;
}
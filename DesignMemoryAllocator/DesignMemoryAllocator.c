typedef struct {
    int* memory;
    size_t size;
    size_t usedSize;
} Allocator;


Allocator* allocatorCreate(int n) {
    Allocator* pool = malloc(sizeof(Allocator));
    if(!pool) return NULL;
    pool->memory = calloc(n, sizeof(int));
    if(!pool->memory){
        free(pool);
        return NULL;
    }
    pool->size = n;
    pool->usedSize = 0;
    return pool;
}

int allocatorAllocate(Allocator* obj, int size, int mID) {
    int count = 0, start = -1;
    for (int i = 0; i < obj->size; i++) {
        if (obj->memory[i] == 0) {
            if (count == 0) start = i;
            count++;
            if (count == size) {
                for (int j = start; j < start + size; j++) {
                    obj->memory[j] = mID;
                }
                obj->usedSize += size;
                return start;
            }
        } else {
            count = 0;
        }
    }
    return -1;  
}

int allocatorFreeMemory(Allocator* obj, int mID) {
    int mID_Count = 0;
    for(int i = 0; i < obj->size; i++){
        if(obj->memory[i] == mID){
            obj->memory[i] = 0;
            mID_Count++;
            obj->usedSize--;
        }
    }
    return mID_Count;
}

void allocatorFree(Allocator* obj) {
    free(obj->memory);
    free(obj);
}

/**
 * Your Allocator struct will be instantiated and called as such:
 * Allocator* obj = allocatorCreate(n);
 * int param_1 = allocatorAllocate(obj, size, mID);
 
 * int param_2 = allocatorFreeMemory(obj, mID);
 
 * allocatorFree(obj);
*/
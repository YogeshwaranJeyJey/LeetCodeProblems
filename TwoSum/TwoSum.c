#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    int value;
    struct Node *next;
};

unsigned int hash(int key, int numsSize) {
    if (key < 0) key = -key;
    return (unsigned int)(key % numsSize);
}

void insert(int key, int value, int numsSize, struct Node** hashTable) {
    unsigned int index = hash(key, numsSize);

    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        struct Node *temp = hashTable[index];
        while (temp->next != NULL) {
            if (temp->key == key) {
                temp->value = value;
                free(newNode);
                return;
            }
            temp = temp->next;
        }
        if (temp->key == key) {
            temp->value = value;
            free(newNode);
            return;
        }
        temp->next = newNode;
    }
}

int search(int hashSize, struct Node** hashTable, int key) {
    unsigned int index = hash(key, hashSize);
    struct Node *temp = hashTable[index];
    while (temp) {
        if (temp->key == key)
            return temp->value;
        temp = temp->next;
    }
    return -1;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* resultArray = (int*)malloc((*returnSize) * sizeof(int));
    struct Node** hashTable = (struct Node**)calloc(numsSize, sizeof(struct Node*));

    for (int i = 0; i < numsSize; i++) {
        int anotherOperand = target - nums[i];
        int searchResult = search(numsSize, hashTable, anotherOperand);

        if (searchResult != -1) {
            resultArray[0] = searchResult;
            resultArray[1] = i;
            for (int j = 0; j < numsSize; j++) {
                struct Node* temp = hashTable[j];
                while (temp) {
                    struct Node* next = temp->next;
                    free(temp);
                    temp = next;
                }
            }
            free(hashTable);
            return resultArray;
        }
        insert(nums[i], i, numsSize, hashTable);
    }
    free(resultArray);
    for (int j = 0; j < numsSize; j++) {
        struct Node* temp = hashTable[j];
        while (temp) {
            struct Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(hashTable);
    return NULL;
}
#define SIZE    26
int firstUniqChar(char* s) {
    int arr[SIZE] = {0};
    int length = strlen(s);
    for(int i = 0; i < length; i++){
        arr[s[i] - 'a']++;
    }
    for(int i = 0; i < length; i++){
        if(arr[s[i] - 'a'] == 1)
            return i;
    }
    return -1;
}
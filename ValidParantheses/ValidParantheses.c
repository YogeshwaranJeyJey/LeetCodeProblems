typedef struct stack{
    int top;
    char *arr;
    int capacity;
}stack_t;

stack_t* createStack(int length){
    stack_t *newStack = (stack_t *)malloc(sizeof(stack_t));
    if(!newStack) return NULL;
    newStack->arr = (char*) malloc(length * sizeof(char));
    if(!newStack->arr) return NULL;
    newStack->top = -1;
    newStack->capacity = length;
    return newStack;
}

void push(stack_t *stack, char c){
    stack->arr[++stack->top] = c;
}

char pop(stack_t *stack){
    return stack->arr[stack->top--];
}

bool isEmpty(stack_t *stack){
    if(stack->top == -1)
        return true;
    return false;
}

void freeStack(stack_t *stack) {
    free(stack->arr);
    free(stack);
}

bool isValid(char* s) {
    int strLength = strlen(s);
    if(s[0] == '\0')
        return true;
    stack_t *stack =  createStack(strLength);
    for(int i = 0; i < strLength; i++){
        if(s[i] == '(' || s[i] == '{' || s[i] == '['){
            push(stack, s[i]);
        }
        else{
            if(isEmpty(stack)){
                freeStack(stack);
                return false;
            }
            char topChar = pop(stack);
            if(topChar == '(' && s[i] != ')' ||
            topChar == '{' && s[i] != '}' ||
            topChar == '[' && s[i] != ']'){
                freeStack(stack);
                return false;
            }
        }
    }
    bool valid = isEmpty(stack);
    freeStack(stack);
    return valid;
}
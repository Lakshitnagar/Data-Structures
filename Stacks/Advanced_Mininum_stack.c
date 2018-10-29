#include<stdio.h>
#include<stdlib.h>

struct StackNode{
    int data;
    struct StackNode *next;
};

struct StackNode *createNewNode(){
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    if(!newNode) return NULL;
    else return newNode;
}

struct StackNode *createNewStack(){
    return NULL;
}

struct AdvancedMinStack{
    struct StackNode *ElemStack;
    struct StackNode *MinStack;
};

struct AdvancedMinStack *createAdvancedMinStack(){
    struct AdvancedMinStack *AMStack;
    AMStack = (struct AdvancedMinStack *)malloc(sizeof(struct AdvancedMinStack));
    AMStack->ElemStack = createNewStack();
    AMStack->MinStack = createNewStack();

    return AMStack;
}

void iterateStack(struct StackNode *head){
    struct StackNode *currNode, *nextNode;

    if(!head) return;
    
    currNode = head;
    nextNode = currNode->next;

    int i=0;
    while(nextNode){
        printf("Data at %dth location : %d \n", i, currNode->data);
        currNode = nextNode;
        nextNode = nextNode->next;
        i++;
    }
    printf("Data at %dth location : %d \n \n", i, currNode->data);

}

int ListLength(struct StackNode *head){
    if(!head) return 0;

    int count = 0;
    struct StackNode *currNode = head;

    while(currNode!=NULL){
        count++;
        currNode = currNode->next;
    }

    return count;
}

void push(struct StackNode **top, int data){
    struct StackNode *newStackNode = createNewNode();
    if(!newStackNode) return;

    newStackNode->data = data;
    newStackNode->next = *top;
    *top = newStackNode;
}

int isEmptyStack(struct StackNode *top){
    return top == NULL;
}

int pop(struct StackNode **top){
    if(isEmptyStack(*top)) return INT_MIN;

    int data;
    struct StackNode *temp = *top;
    data = temp->data;
    *top = temp->next;
    free(temp);

    return data;
}

int top(struct StackNode *top){
    return top->data;
}

void advancedMinStackpush(struct AdvancedMinStack *AMStack, int data){
    if(AMStack->ElemStack==NULL && AMStack->MinStack==NULL){
        push(&(AMStack->ElemStack), data);
        push(&(AMStack->MinStack), data);
    }
    else{
        push(&(AMStack->ElemStack), data);
        if(data < top(AMStack->MinStack))
            push(&(AMStack->MinStack), data);
        else
            push(&(AMStack->MinStack), top(AMStack->MinStack));
    }
}

void advancedMinStackpop(struct AdvancedMinStack *AMStack){
    if(isEmptyStack(AMStack->ElemStack)) return;

    pop(&(AMStack->ElemStack));
    pop(&(AMStack->MinStack));
}

int main(){
    struct AdvancedMinStack *AMStack = createAdvancedMinStack();
    struct StackNode **elemStakTop = &(AMStack->ElemStack);
    
    advancedMinStackpush(AMStack, 2);
    advancedMinStackpush(AMStack, 3);
    advancedMinStackpush(AMStack, 1);
    advancedMinStackpush(AMStack, -1);

    iterateStack(AMStack->ElemStack);

    iterateStack(AMStack->MinStack);

    printf("Minimum element: %d\n", top(AMStack->MinStack));

    advancedMinStackpop(AMStack);
    advancedMinStackpop(AMStack);

    iterateStack(AMStack->ElemStack);

    iterateStack(AMStack->MinStack);

    printf("Minimum element: %d\n", top(AMStack->MinStack));

    return 0;
}
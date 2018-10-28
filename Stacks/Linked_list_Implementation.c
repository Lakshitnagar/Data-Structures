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

int main(){
    struct StackNode *stack = createNewStack();
    struct StackNode **top = &stack;

    push(top, 2);
    push(top, 3);
    push(top, 4);
    push(top, 5);

    iterateStack(*top);
    printf("\n");
    printf("popped item: %d\n", pop(top));

    iterateStack(*top);

    return 0;
}
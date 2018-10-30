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

int top(struct StackNode *top){
    if(isEmptyStack(top)) return NULL;
    else return top->data;
}

void iterateArray(int a[], int n){
    printf("\n");
    for(int i=0; i<n; i++){
        printf("a[%d] = %d\n", i, a[i]);
    }
    printf("\n");
}

void findSpanOfArray_iterative(int a[], int n, int s[]){
    int j;

    for(int i=0; i<n; i++){
        j = 1;
        s[i] = 1;
        while(j<=i && a[i-j]<a[i]){
            s[i]++;
            j++;
        }
    }
}

void findSpanOfArray_stack(int a[], int n, int s[]){
    struct StackNode *stk = createNewStack();
    push(&stk, 0);
    s[0] = 1;

    for(int i=1; i<n; i++){
        while(!isEmptyStack(stk) && a[i] >= a[top(stk)])
            pop(&stk);
        
        s[i] = (isEmptyStack(stk)) ? i+1 : i-top(stk);

        push(&stk, i);
    }
    iterateStack(stk);
}

int main(){
    // int a[] = {10, 4, 5, 90, 120, 80};
    int a[] = {5, 4, 3, 2, 4, 3};
    int n = sizeof(a)/sizeof(a[0]); 
    int s[n];

    // iterateArray(a, n);
    // findSpanOfArray_iterative(a, n, s);
    // iterateArray(s, n);

    iterateArray(a, n);
    findSpanOfArray_stack(a, n, s);
    iterateArray(s, n);
    

    return 0;
}
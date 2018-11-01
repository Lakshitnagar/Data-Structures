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

// References
// https://stackoverflow.com/questions/4311694/maximize-the-rectangular-area-under-histogram
void largest_histogram(int a[], int n){
    struct StackNode *stk = createNewStack();
    int max_area = 0, height, area, currPos;

    for(int i=0; i<n; i++){
        while(!isEmptyStack(stk) && a[i] < a[top(stk)]){
            currPos = pop(&stk);
            height = a[currPos];

            if(isEmptyStack(stk))
                area = height * (i - currPos);
            else
                area = height * (i - top(stk) - 1);
                
            max_area = (area > max_area) ? area : max_area;
            
        }
        push(&stk, i);
    }
    
    while(!isEmptyStack(stk)){
        currPos = pop(&stk);
        height = a[currPos];
        
        if(isEmptyStack(stk))
            area = height * n;
        else 
            area = height * (currPos - top(stk));

        max_area = (area > max_area) ? area : max_area;
    }
    printf("Max area is : %d\n", max_area);
}

int main(){
    int a[] = {1, 2, 3, 4, 5, 3, 3, 2};
    // int a[] = {5, 4, 3, 2, 4, 3};
    int n = sizeof(a)/sizeof(a[0]); 
    int s[n];

    largest_histogram(a, n);

    return 0;
}
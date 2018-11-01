#include<stdio.h>
#include<stdlib.h>

#define ROW 4
#define COLUMN 4

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
int largest_histogram(int a[], int n){
    struct StackNode *stk = createNewStack();
    int max_area = 0, height, area, currPos;
    int l,r;

    for(int i=0; i<n; i++){
        while(!isEmptyStack(stk) && a[i] < a[top(stk)]){
            currPos = pop(&stk);
            height = a[currPos];

            if(isEmptyStack(stk)){
                area = height * i;
            }
            else
                area = height * (i - top(stk) - 1);
            
            if(area > max_area){
                max_area = area;
                if(isEmptyStack(stk)){
                    l = currPos;
                    r = i - 1;
                }
                else{
                    l = top(stk) + 1;
                    r = i - 1;
                }
            }
            
        }
        push(&stk, i);
    }
    
    while(!isEmptyStack(stk)){
        currPos = pop(&stk);
        height = a[currPos];
        
        if(isEmptyStack(stk))
            area = height * n;
        else 
            area = height * (n - top(stk) - 1);

        if(area > max_area){
            max_area = area;
            if(isEmptyStack(stk)){
                l = 0;
                r = n - 1;
            }
            else{
                l = top(stk) + 1;
                r = currPos;
            }
        }
    }
    return max_area;
}

void largest_area(int a[][COLUMN]){
    int max_area = largest_histogram(a[0], COLUMN);
    int row_area = 0;
    
    for(int i=1; i<ROW; i++){
        for(int j=0; j<COLUMN; j++){
            if(a[i][j]) a[i][j] += a[i-1][j];
        }
        row_area = largest_histogram(a[i], COLUMN);
        if(row_area > max_area){
            max_area = row_area;
        }
    }

    printf("max area: %d\n", max_area);
}

int main(){
    int a[][COLUMN] = {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 0, 0}
    };

    largest_area(a);

    return 0;
}
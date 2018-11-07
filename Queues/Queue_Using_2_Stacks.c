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

struct QueueUsingStack{
    struct StackNode *S1;
    struct StackNode *S2;
};

struct QueueUsingStack *createNewQueueUsingStack(){
    struct QueueUsingStack *QUS;
    QUS = (struct QueueUsingStack *)malloc(sizeof(struct QueueUsingStack));
    if(!QUS) return NULL;

    QUS->S1 = createNewStack();
    QUS->S2 = createNewStack();

    return QUS;
}

void enQueueQUS(struct QueueUsingStack *QUS, int data){
    if(!QUS) return NULL;

    push(&(QUS->S1), data);
}

int deQueueQUS(struct QueueUsingStack *QUS){
    if(!isEmptyStack(QUS->S2)) return pop(&(QUS->S2));

    if(isEmptyStack(QUS->S1)){
        printf("QUS is empty\n");
        return NULL;
    }

    while(!isEmptyStack(QUS->S1)){
        push(&(QUS->S2), pop(&(QUS->S1)));
    }

    return pop(&(QUS->S2));
}

int main(){
    struct QueueUsingStack *QUS = createNewQueueUsingStack();
    enQueueQUS(QUS, 1);
    enQueueQUS(QUS, 2);
    enQueueQUS(QUS, 3);
    enQueueQUS(QUS, 4);
    enQueueQUS(QUS, 5);

    iterateStack(QUS->S1);

    deQueueQUS(QUS);
    iterateStack(QUS->S2);
    enQueueQUS(QUS, 6);
    enQueueQUS(QUS, 7);
    deQueueQUS(QUS);
    iterateStack(QUS->S2);
    deQueueQUS(QUS);
    iterateStack(QUS->S2);
    deQueueQUS(QUS);
    iterateStack(QUS->S2);
    deQueueQUS(QUS);
    iterateStack(QUS->S2);
    deQueueQUS(QUS);
    iterateStack(QUS->S2);

    return 0;
}
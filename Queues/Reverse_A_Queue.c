#include<stdio.h>
#include<stdlib.h>

struct ListNode{
    int data;
    struct ListNode *next;
};

struct Queue {
    struct ListNode *front;
    struct ListNode *rear;
};

struct ListNode *createNewNode(){
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    if(!newNode) return NULL;
    else return newNode;
}

struct Queue *createNewQueue(){
    struct Queue *Q;
    Q = (struct Queue *)malloc(sizeof(struct Queue));
    if(!Q) return NULL;

    Q->front = Q->rear = NULL;
    return Q;
}

int isEmptyQueue(struct Queue *Q){
    return(Q->front == NULL);
}

void enQueue(struct Queue *Q, int data){
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    if(!newNode) return NULL;

    newNode->data = data;
    newNode->next = NULL;
    if(Q->rear)
        Q->rear->next = newNode;
    Q->rear = newNode;

    if(Q->front == NULL)
        Q->front = Q->rear;
}

int deQueue(struct Queue *Q){
    if(isEmptyQueue(Q)){
        printf("Queue is empty\n");
        return NULL;
    }
    int data;
    struct ListNode *temp;
    temp = Q->front;
    data = Q->front->data;
    Q->front = Q->front->next;
    free(temp);

    return data;
}

void deleteQueue(struct Queue *Q){
    struct ListNode *temp;
    while(Q->front){
        temp = Q->front;
        Q->front = Q->front->next;
        free(temp);
    }
    Q->front = NULL;
    Q->rear = NULL;
}

struct ListNode *createNewStack(){
    return NULL;
}

void push(struct ListNode **top, int data){
    struct ListNode *newStackNode = createNewNode();
    if(!newStackNode) return;

    newStackNode->data = data;
    newStackNode->next = *top;
    *top = newStackNode;
}

int isEmptyStack(struct ListNode *top){
    return top == NULL;
}

int pop(struct ListNode **top){
    if(isEmptyStack(*top)) return INT_MIN;

    int data;
    struct ListNode *temp = *top;
    data = temp->data;
    *top = temp->next;
    free(temp);

    return data;
}

void iterateList(struct ListNode *head){
    struct ListNode *currNode, *nextNode;

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

int ListLength(struct ListNode *head){
    if(!head) return 0;

    int count = 0;
    struct ListNode *currNode = head;

    while(currNode!=NULL){
        count++;
        currNode = currNode->next;
    }

    return count;
}

void reverseQueueUsingStack(struct Queue *Q){
    struct ListNode *S = createNewStack();
    while(!isEmptyQueue(Q))
        push(&S, deQueue(Q));
    while(!isEmptyStack(S))
        enQueue(Q, pop(&S));
}

int main(){
    struct Queue *Q = createNewQueue();
    enQueue(Q, 1);
    enQueue(Q, 2);
    enQueue(Q, 3);
    enQueue(Q, 4);

    iterateList(Q->front);
    
    reverseQueueUsingStack(Q);

    iterateList(Q->front);

    return 0;
}
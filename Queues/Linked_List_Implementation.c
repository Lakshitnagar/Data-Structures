#include<stdio.h>
#include<stdlib.h>

struct QueueNode{
    int data;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *front;
    struct QueueNode *rear;
};

struct QueueNode *createNewNode(){
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
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
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
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
    struct QueueNode *temp;
    temp = Q->front;
    data = Q->front->data;
    Q->front = Q->front->next;
    free(temp);

    return data;
}

void deleteQueue(struct Queue *Q){
    struct QueueNode *temp;
    while(Q->front){
        temp = Q->front;
        Q->front = Q->front->next;
        free(temp);
    }
    Q->front = NULL;
    Q->rear = NULL;
}

void iterateQueue(struct QueueNode *head){
    struct QueueNode *currNode, *nextNode;

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

int ListLength(struct QueueNode *head){
    if(!head) return 0;

    int count = 0;
    struct QueueNode *currNode = head;

    while(currNode!=NULL){
        count++;
        currNode = currNode->next;
    }

    return count;
}

int main(){
    struct Queue *Q = createNewQueue();
    enQueue(Q, 1);
    enQueue(Q, 2);
    enQueue(Q, 3);
    enQueue(Q, 4);

    iterateQueue(Q->front);

    deQueue(Q);iterateQueue(Q->front);

    deleteQueue(Q);
    iterateQueue(Q->front);

    return 0;
}
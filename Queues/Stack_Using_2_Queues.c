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

struct StackUsingQueue{
    struct Queue *Q1;
    struct Queue *Q2;
};

struct StackUsingQueue *createNewStackUsingQueue(){
    struct StackUsingQueue *SUQ;
    SUQ = (struct StackUsingQueue *)malloc(sizeof(struct StackUsingQueue));
    if(!SUQ) return NULL;

    SUQ->Q1 = createNewQueue();
    SUQ->Q2 = createNewQueue();

    return SUQ;
}

void pushSUQ(struct StackUsingQueue *SUQ, int data){
    if(!SUQ) return NULL;

    if(!isEmptyQueue(SUQ->Q1))
        enQueue(SUQ->Q1, data);
    else
        enQueue(SUQ->Q2, data);
}

int popSUQ(struct StackUsingQueue *SUQ){
    if(!SUQ) return NULL;

    int length = ListLength(SUQ->Q2->front);
    printf("%d\n", length);

    if(!isEmptyQueue(SUQ->Q1)){
        while(SUQ->Q1->front->next){
            enQueue(SUQ->Q2, deQueue(SUQ->Q1));
        }
        return deQueue(SUQ->Q1);
    }

    if(!isEmptyQueue(SUQ->Q2)){
        while(SUQ->Q2->front->next){
            enQueue(SUQ->Q1, deQueue(SUQ->Q2));
        }
        return deQueue(SUQ->Q2);
    }

    printf("SUQ is Empty\n");
    return NULL;
}

int main(){
    struct StackUsingQueue *SUQ;
    SUQ = createNewStackUsingQueue();
    pushSUQ(SUQ, 1);
    pushSUQ(SUQ, 2);
    pushSUQ(SUQ, 3);
    printf("Popped element is : %d\n", popSUQ(SUQ));
    printf("Popped element is : %d\n", popSUQ(SUQ));
    printf("Popped element is : %d\n", popSUQ(SUQ));

    return 0;
}
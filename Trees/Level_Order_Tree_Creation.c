#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct QueueNode{
    struct BinaryTreeNode *BTNode;
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

void enQueue(struct Queue *Q, struct BinaryTreeNode *BTNode){
    struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    if(!newNode) return NULL;

    newNode->BTNode = BTNode;
    newNode->next = NULL;
    if(Q->rear)
        Q->rear->next = newNode;
    Q->rear = newNode;

    if(Q->front == NULL)
        Q->front = Q->rear;
}

struct BinaryTreeNode *deQueue(struct Queue *Q){
    if(isEmptyQueue(Q)){
        printf("Queue is empty\n");
        return NULL;
    }
    struct BinaryTreeNode *data;
    struct QueueNode *temp;
    temp = Q->front;
    data = Q->front->BTNode;
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
        printf("Data at %dth location : %d \n", i, currNode->BTNode);
        currNode = nextNode;
        nextNode = nextNode->next;
        i++;
    }
    printf("Data at %dth location : %d \n \n", i, currNode->BTNode);

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

struct BinaryTreeNode{
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};

struct BinaryTreeNode *createNewBTNode(){
    struct BinaryTreeNode *BTNode;
    BTNode = (struct BinaryTreeNode *)malloc(sizeof(struct BinaryTreeNode));
    if(!BTNode) return NULL;

    BTNode->left = NULL;
    BTNode->right = NULL;

    return BTNode;
}

struct BinaryTreeNode *createFullBinaryTree_LevelOrder_iterative(int depth){
    struct Queue *Q = createNewQueue();
    struct BinaryTreeNode *BTRoot = createNewBTNode();
    int count = 1;
    BTRoot->data = count++;
    enQueue(Q, BTRoot);

    while(ListLength(Q->front) < pow(2, depth)){
        struct BinaryTreeNode *FrontBTNode = Q->front->BTNode;
        struct BinaryTreeNode *left, *right;

        if(!FrontBTNode->left){
            left = createNewBTNode();
            left->data = count++;
            FrontBTNode->left = left;
            enQueue(Q, left);
        }

        if(!FrontBTNode->right){
            right = createNewBTNode();
            right->data = count++;
            FrontBTNode->right = right;
            enQueue(Q, right);
        }

        deQueue(Q);
    }

    deleteQueue(Q);

    return BTRoot;
}

void preOrderTraversal_Recursive(struct BinaryTreeNode *root){
    if(root){
        printf("node : %d\n", root->data);
        preOrderTraversal_Recursive(root->left);
        preOrderTraversal_Recursive(root->right);
    }
}

int main(){
    struct BinaryTreeNode *BTRoot;
    BTRoot = createFullBinaryTree_LevelOrder_iterative(2);

    preOrderTraversal_Recursive(BTRoot);

    return 0;
}
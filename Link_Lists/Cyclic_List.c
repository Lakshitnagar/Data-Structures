#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Node definition
struct ListNode {
    int data;
    struct ListNode *next;
};

// Function to create a new node and send back the reference
struct ListNode *createNewNode(){
    struct ListNode *newNode;
    newNode = (struct ListNode *)malloc(sizeof(struct ListNode));

    if(!newNode) return NULL;
    else return newNode;
}

struct ListNode *generateCyclicList(int loopStartPoint, int loopSize){
    if(loopStartPoint<1 || loopSize<0) return NULL;
    struct ListNode *head = createNewNode();
    if(!head) return NULL;

    struct ListNode *currNode = head;
    struct ListNode *nextNode, *loopStartNode;

    for(int i=1; i<loopStartPoint; i++){
        nextNode = createNewNode();
        if(!nextNode) return NULL;

        printf("currNode %d\n", currNode);
        currNode->next = nextNode;
        currNode->data = i*i;

        currNode = nextNode;
    }

    loopStartNode = currNode;
    printf("loopStartNode %d\n", loopStartNode);

    for(int i=1; i<loopSize; i++){
        nextNode = createNewNode();
        if(!nextNode) return NULL;
        
        printf("currNode %d\n", currNode);
        currNode->next = nextNode;
        currNode->data = i*i;

        currNode = nextNode;
    }

    currNode->next = loopStartNode;
    printf("currNode %d\n", currNode);
    printf("currNode->next %d\n\n", currNode->next);

    return head;
}

void iterateCyclicList(struct ListNode *head, int loopStartPoint){
    if(!head) return NULL;

    struct ListNode *currNode = head;
    struct ListNode *loopStartNode;
    int count = 1;

    while(count<loopStartPoint){
        printf("Node at %dth location: %d\n", count, currNode);
        currNode = currNode->next;
        count++;
    }

    loopStartNode = currNode;
    if(loopStartNode==currNode)
    printf("Node at %dth location(loop start): %d\n", count, currNode);
    currNode = currNode->next;
    count++;

    while(currNode!=loopStartNode){
        printf("Node at %dth location(inside loop): %d\n", count, currNode);
        currNode = currNode->next;
        count++;
    }
}

int main() {
    int loopStart = 17;
    int loopSize = 10;
    struct ListNode *head = generateCyclicList(loopStart, loopSize);
    iterateCyclicList(head, loopStart);

    return 0;
}
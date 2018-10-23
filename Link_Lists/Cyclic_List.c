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
    if(loopStartPoint<1){
        printf("Loop starting point must be at least from begining\n");
        return NULL;
    }

    struct ListNode *head = createNewNode();
    if(!head) return NULL;

    struct ListNode *currNode = head;
    struct ListNode *nextNode, *loopStartNode;

    for(int i=1; i<loopStartPoint; i++){
        nextNode = createNewNode();
        if(!nextNode) return NULL;

        currNode->next = nextNode;
        currNode->data = i;
        printf("currNode %d\n", currNode->data);

        currNode = nextNode;
    }

    loopStartNode = currNode;
    printf("loopStartNode %d\n", loopStartNode);
    
    for(int i=1; i<loopSize; i++){
        nextNode = createNewNode();
        if(!nextNode) return NULL;
        
        currNode->next = nextNode;
        currNode->data = i;
        printf("currNode %d\n", currNode->data);

        currNode = nextNode;
    }

    if(loopSize<1)
        currNode->next = NULL;
    else
        currNode->next = loopStartNode;
    currNode->data = 9876;
    printf("currNode %d\n", currNode->data);

    return head;
}

void iterateCyclicList(struct ListNode *head, int loopStartPoint){
    if(!head){
        printf("Head value is NULL\n");
        return NULL;
    }

    struct ListNode *currNode = head;
    struct ListNode *loopStartNode;
    int count = 1;

    while(count<loopStartPoint){
        printf("Node at %dth location: %d\n", count, currNode->data);
        currNode = currNode->next;
        count++;
    }

    loopStartNode = currNode;
    if(loopStartNode==currNode)
    printf("Node at %dth location(loop start): %d\n", count, currNode->data);
    currNode = currNode->next;
    count++;

    while(currNode!=loopStartNode && currNode!=NULL){
        printf("Node at %dth location(inside loop): %d\n", count, currNode->data);
        currNode = currNode->next;
        count++;
    }
}

int isCyclicList(struct ListNode *head){
    if(!head) return NULL;

    struct ListNode *slowPtr, *fastPtr;
    slowPtr = fastPtr = head;
    slowPtr = slowPtr->next;
    fastPtr = fastPtr->next->next;

    while(slowPtr!=fastPtr && fastPtr->next!=NULL){
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
    }

    if(slowPtr==fastPtr) return 1;
    else return 0;
}

int main() {
    int loopStart = 15;
    int loopSize = 0;
    struct ListNode *head = generateCyclicList(loopStart, loopSize);
    iterateCyclicList(head, loopStart);

    printf("\nLoop status: %d\n", isCyclicList(head));

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Node definition
struct ListNode {
    int data;
    struct ListNode *next;
};

// Function to create a new node and send bakc a reference
struct ListNode *createNewNode(){
    struct ListNode *newNode;
    newNode = (struct ListNode *)malloc(sizeof(struct ListNode));

    if(!newNode) return NULL;
    else return newNode;
}

// Create random list of Linked Lists
struct ListNode *generateRandomLinkedList(int n){
    struct ListNode *head, *nextNode, *currNode;
    time_t t;
    srand((unsigned) time(&t));

    head = createNewNode();
    if(!head) return NULL;

    head->data = rand();

    currNode = head;

    for(int i=1; i<n; i++){
        nextNode = createNewNode();
        if(!nextNode) return NULL;

        nextNode->data = rand();
        currNode->next = nextNode;

        currNode = nextNode;
    }

    currNode->next = NULL;

    return head;
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
    printf("Data at %dth location : %d \n", i, currNode->data);

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

int main()
{
    struct ListNode *head = NULL;
    head = generateRandomLinkedList(5);
    iterateList(head);

    printf("Length of the Linked List : %d", ListLength(head));

    // free();

    return 0;
}
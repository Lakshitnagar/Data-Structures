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
    printf("Data at %dth location : %d \n \n", i, currNode->data);

}

struct ListNode *NthNodeFromLast(struct ListNode *head, int N){
    if(!head) return NULL;
    struct ListNode *NthNode = NULL,
                    *tempNode = head;
    
    for(int count=1; count<N; count++){
        if(tempNode)
            tempNode = tempNode->next;
        else
            return NULL;
    }

    while(tempNode){
        if(NthNode==NULL)
            NthNode = head;
        else
            NthNode = NthNode->next;
        tempNode = tempNode->next;
    }

    return NthNode;
}

int main() {
    struct ListNode *head;
    head = generateRandomLinkedList(10);
    iterateList(head);

    int N = 11;
    struct ListNode *nthNodeFromLast = NthNodeFromLast(head, N);
    if(nthNodeFromLast)
        printf("%dth node from last is %d", N, nthNodeFromLast->data);
    else
        printf("List length is less than %d", N);

    return 0;
}
#include<stdio.h>
#include<stdlib.h>

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
struct ListNode *generateSortedLinkedList(int n){
    struct ListNode *head, *nextNode, *currNode;

    head = createNewNode();
    if(!head) return NULL;

    head->data = 0;

    currNode = head;

    for(int i=1; i<n; i++){
        nextNode = createNewNode();
        if(!nextNode) return NULL;

        nextNode->data = i;
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

int insertNodeInSortedList(struct ListNode *head, struct ListNode *newNode){
    if(!head) return NULL;
    if(!newNode) return NULL;

    struct ListNode *currNode, *nextNode;
    currNode = head;
    nextNode = head->next;

    while(nextNode){
        if(newNode->data<nextNode->data){
            newNode->next = nextNode;
            currNode->next = newNode;
            break;
            return 1;
        }
        else{
            currNode = nextNode;
            nextNode = nextNode->next;
        }
    }
    // Important point for largest element
    if(!nextNode){
        currNode->next = newNode;
        newNode->next = NULL;
        return 1;
    }
    return 0;
}


struct ListNode *reverseListIterative(struct ListNode *head){
    if(!head) return NULL;

    struct ListNode *prevNode, *nextNode;
    prevNode = NULL;
    nextNode = NULL;

    while(head){
        nextNode = head->next;
        head->next = prevNode;

        prevNode = head;
        head = nextNode;
    }
    return prevNode;
}

struct ListNode *reverseListRecursive(struct ListNode *head){
    if(!head) return NULL;

    if(head->next==NULL) return head;

    struct ListNode *secondNode = head->next;
    head->next = NULL;

    struct ListNode *rest = reverseListRecursive(secondNode);

    secondNode->next = head;
    return rest;
}

int main(){
    struct ListNode *head;
    head = generateSortedLinkedList(10);
    printf("List Length: %d\n", ListLength(head));
    iterateList(head);

    struct ListNode *newNode = createNewNode();
    newNode->data = 90;
    insertNodeInSortedList(head, newNode);
    printf("List Length: %d\n", ListLength(head));
    iterateList(head);

    head = reverseListIterative(head);
    printf("List Length: %d\n", ListLength(head));
    iterateList(head);

    head = reverseListRecursive(head);
    printf("List Length: %d\n", ListLength(head));
    iterateList(head);

    return 0;
}
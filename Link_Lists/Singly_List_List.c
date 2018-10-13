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

void InsertListNode_ptr(struct ListNode *head, int position, int data){
    if(!head) return;
    struct ListNode *newNode, *tempNode, *p;
    int k = 1;

    newNode = createNewNode();
    if(!newNode) return;

    newNode->data = data;

    if(position==1){
        tempNode = createNewNode();
        if(!tempNode) return;

        newNode->next = newNode;
        *tempNode = *head;
        *head = *newNode;
        *newNode = *tempNode;

        free(tempNode);
        return;
    }
    else {
        p = head;
        while((p->next) && k < position-1){
            k++;
            p = p->next;
            printf("k: %d \n", k);
        }

        if(k == position-1){
            printf("position found \n");
            newNode->next = p->next;
            p->next = newNode;
            return;
        }
        else {
            printf("***ListLength: %d , postion: %d ***\n", ListLength(head), position);
            return;
        }
    }
}

void InsertListNode_ptr2ptr(struct ListNode **head, int position, int data){
    if(!*head) return;

    int k = 1;
    struct ListNode *newNode, *p;
    newNode = createNewNode();
    if(!newNode) return;

    newNode->data = data;
    p = *head;

    if(position==1){
        newNode->next = p;
        *head = newNode;
    }
    else{
        while(p->next && k < position-1){
            k++;
            p = p->next;
        }
        if(k == position-1){
            printf("Position found \n");
            newNode->next = p->next;
            p->next = newNode;
        }
        else{
            printf("Position not found: %d \n", k);
        }
    }
}

void DeleteListNode_ptr2ptr(struct ListNode **head, int position){
    if(!head || position<=0) return;

    struct ListNode *p, *q;
    int k = 1;
    p = *head;

    if(position==1){
        *head = (*head)->next;
        free(p);
        return;
    }
    else{
        while(p->next && k < position-1){
            k++;
            p = p->next;
        }

        if(k == position-1 && p->next){
            q = p->next;
            p->next = q->next;
            free(q);
        }
        else{
            printf("position not found \n");
            return;
        }
    }
}

int main()
{
    struct ListNode *head = NULL;
    head = generateRandomLinkedList(5);
    iterateList(head);

    printf("Length of the Linked List : %d \n", ListLength(head));

    // InsertListNode_ptr(head, 1, 10);

    // iterateList(head);

    // printf("Length of the Linked List : %d \n", ListLength(head));

    // InsertListNode_ptr(head, 4, 0);
    // InsertListNode_ptr2ptr(&head, 8, 14581);

    // iterateList(head);

    // printf("Length of the Linked List : %d \n", ListLength(head));

    DeleteListNode_ptr2ptr(&head, 6);
    iterateList(head);
    printf("Length of the Linked List : %d \n", ListLength(head));



    // free();

    return 0;
}
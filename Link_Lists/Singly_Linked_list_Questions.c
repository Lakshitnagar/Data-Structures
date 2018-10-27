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

struct ListNode *join2LinkedList(struct ListNode *first, struct ListNode *second, int linkPoint){
    if(!first && !second) return NULL;
    if(!first) return second;
    if(!second) return first;

    struct ListNode *firstCurr, *secondCurr;
    firstCurr = first;
    secondCurr = second;
    int count = 1;

    while(firstCurr->next && count<linkPoint){
        firstCurr = firstCurr->next;
        count++;
    }
    while(secondCurr->next){
        secondCurr = secondCurr->next;
    }

    if(count<linkPoint){
        printf("first list is shorter\n");
        return NULL;
    }

    secondCurr->next = firstCurr;
}

struct ListNode *findLinkPoint(struct ListNode *first, struct ListNode *second){
    if(!first || !second) return NULL;

    int L1=1, L2=1, diff=0;
    struct ListNode *head1 = first, *head2 = second;

    while(head1->next){ L1++; head1 = head1->next; }
    while(head2->next){ L2++; head2 = head2->next; }

    if(L1>L2){ diff = L1-L2; head1 = first; head2 = second; }
    else{ diff = L2-L1; head1 = second; head2 = first; }

    for(int i=0; i<diff; i++)
        head1 = head1->next;
    
    while(head1 && head2){
        if(head1 == head2) return head1;
        head1 = head1->next;
        head2 = head2->next;
    }

    return NULL;
}

struct ListNode *findMiddleNode(struct ListNode *head){
    if(!head) return NULL;
    if(!head->next || !head->next->next) return head;

    struct ListNode *ptr1x = head, *ptr2x = head;

    while(ptr2x->next && ptr2x->next->next){
        ptr1x = ptr1x->next;
        ptr2x = ptr2x->next->next;
    }

    return ptr1x;

}

void dispayFromEnd(struct ListNode *head){
    if(!head) return NULL;

    dispayFromEnd(head->next);
    printf("head :%d\n", head->data);
}

struct ListNode *pairReverseListRecursive(struct ListNode *head){
    if(!head) return NULL;
    if(!head->next) return head;
    
    struct ListNode *rest = pairReverseListRecursive(head->next->next);

    struct ListNode *temp = NULL;
    temp = head->next;
    head->next = head->next->next;
    temp->next = head;

    head->next = rest;
    return temp;
}

struct ListNode *pairReverseListIterative(struct ListNode *head){
    if(!head) return NULL;
    if(!head->next) return head;

    struct ListNode *curr = head, *temp1 = NULL, *temp2 = NULL;
    while(curr && curr->next){
        temp1 = curr->next;
        curr->next = temp1->next;
        temp1->next = curr;
        
        if(!temp2){
            head = temp1;
            temp2 = curr;
        }
        else{
            temp2->next = temp1;
            temp2 = curr;
        }

        curr = curr->next;
    }
    return head;
}

int main()
{
    struct ListNode *head = NULL;
    head = generateRandomLinkedList(10);
    printf("\n****** LENGTH: %d ****** \n", ListLength(head));
    iterateList(head);

    // struct ListNode *first = generateRandomLinkedList(5);
    // printf("\n****** LENGTH: %d ****** \n", ListLength(first));
    // iterateList(first);
    // struct ListNode *second = generateRandomLinkedList(3);
    // printf("\n****** LENGTH: %d ****** \n", ListLength(second));
    // iterateList(second);

    // join2LinkedList(first, second, 4);
    // printf("\n****** LENGTH: %d ****** \n", ListLength(first));
    // iterateList(first);
    // printf("\n****** LENGTH: %d ****** \n", ListLength(second));
    // iterateList(second);

    // printf("Link point data is : %d\n", findLinkPoint(first, second)->data);
    
    // struct ListNode *midNode = findMiddleNode(head);
    // printf("\nMiddle Node: %d\n", midNode->data);

    // dispayFromEnd(head);

    // struct ListNode *pairRev = pairReverseListRecursive(head);
    // iterateList(pairRev);

    struct ListNode *pairRev = pairReverseListIterative(head);
    iterateList(pairRev);

    return 0;
}
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
    struct ListNode *head = createNewNode();
    if(!head) return NULL;

    struct ListNode *currNode = head;

    for(int i=1; i<=loopStartPoint; i++){
        
    }
}

int main() {


    return 0;
}
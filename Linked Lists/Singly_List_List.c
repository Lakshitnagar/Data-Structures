#include <stdio.h>

struct ListNode {
    int data;
    struct ListNode *next;
};

struct ListNode *createNewNode(){
    struct ListNode *newNode;
    newNode = malloc(sizeof(struct ListNode));

    return newNode;
}

int main()
{
    struct ListNode *head;
    head = createNewNode();
    head->data = 2;
    printf("Hello World %d", head->data);

    return 0;
}
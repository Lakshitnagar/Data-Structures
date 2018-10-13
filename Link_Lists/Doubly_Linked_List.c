#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct DLLNode{
    int data;
    struct DLLNode *next;
    struct DLLNode *prev;
};

struct DLLNode *createNewNode(){
    struct DLLNode *newNode;
    newNode = (struct DLLNode *)malloc(sizeof(struct DLLNode));

    if(!newNode){
        printf("Memory Error !!!");
        return NULL;
    }
    else{
        return newNode;
    }
}

struct DLLNode *gnerateRandomDLL(int n){
    struct DLLNode *head, *newNode, *prev;
    time_t t;
    srand((unsigned) time(&t));

    head = createNewNode();
    if(!head) return NULL;

    head->data = rand();
    head->prev = NULL;
    prev = head;

    for(int i=2; i<=n; i++){
        newNode = createNewNode();
        if(!newNode) return NULL;

        newNode->data = rand();
        newNode->prev = prev;

        prev->next = newNode;
        prev = newNode;
    }

    newNode->next = NULL;

    return head;
}

int LengthOfDLL(struct DLLNode *head){
    if(!head) return 0;

    int count = 0;
    struct DLLNode *p;
    p = head;

    while(p){
        count++;
        p = p->next;
    }

    return count;
}

void iterateDLL(struct DLLNode *head){
    if(!head) return NULL;

    struct DLLNode *p, *q;
    int k = 1;
    p = head;
    q = p->next;

    while(q){
        printf("Data at %dth location (forward -->) : %d \n", k, p->data);
        p = p->next;
        q = q->next;
        k++;
    }
    printf("Data at %dth location (forward -->) : %d \n", k, p->data);

    q = p->prev;

    while(q){
        printf("Data at %dth location (backward <--) : %d \n", k, p->data);
        p = p->prev;
        q = q->prev;
        k--;
    }
    printf("Data at %dth location (backward <--) : %d \n", k, p->data);
    printf("\n");
}

void InsertDLLNode(struct DLLNode **head, int position, int data){
    if(!*head) return NULL;

    int k = 1;
    struct DLLNode *newNode, *p;
    newNode = createNewNode();
    if(!newNode) return NULL;

    newNode->data = data;
    p = *head;

    if(position==1){
        newNode->prev = NULL;
        newNode->next = p;
        p->prev = newNode;

        *head = newNode;
    }
    else{
        while(p->next && k < position-1){
            p = p->next;
            k++;
        }
        if(k == position-1){
            if(p->next){
                newNode->prev = p;
                newNode->next = p->next;
                p->next->prev = newNode;
                p->next = newNode;
            }
            else{
                // Last node
                newNode->next = NULL;
                newNode->prev = p;
                p->next = newNode;
            }
        }
        else{
            printf("Position not found !!! \n \n");
        }
    }
}

void DeleteDLLNode(struct DLLNode **head, int position){
    if(!*head) return NULL;

    struct DLLNode *p, *q;
    p = *head;
    int k = 1;

    if(position == 1){
        *head = (*head)->next;
        if(!*head) return; // this is important
        (*head)->prev = NULL;
        free(p);
    }
    else{
        while(p->next && k < position-1){
            p = p->next;
            k++;
        }
        if(k == position-1){
            q = p->next;
            if(q->next){
                q = p->next;
                p->next = q->next;
                q->next->prev = p;
                free(q);
            }
            else{
                printf("Last node \n");
                p->next = NULL;
                free(q);
            }
        }
        else{
            printf("Position not found !!! \n \n");
        }
    }
}

int main(){
    struct DLLNode *head;

    head = gnerateRandomDLL(3);
    printf("****** LENGTH: %d ****** \n", LengthOfDLL(head));
    iterateDLL(head);

    // InsertDLLNode(&head, 1, 123);
    // InsertDLLNode(&head, 1, 120);
    // printf("****** LENGTH: %d ****** \n", LengthOfDLL(head));
    // iterateDLL(head);

    // InsertDLLNode(&head, 3, 124);
    InsertDLLNode(&head, 1, 0);
    InsertDLLNode(&head, 1, 1);
    printf("****** LENGTH: %d ****** \n", LengthOfDLL(head));
    iterateDLL(head);

    DeleteDLLNode(&head, 5);
    printf("****** LENGTH: %d ****** \n", LengthOfDLL(head));
    iterateDLL(head);

    DeleteDLLNode(&head, 4);
    printf("****** LENGTH: %d ****** \n", LengthOfDLL(head));
    iterateDLL(head);

    DeleteDLLNode(&head, 3);
    printf("****** LENGTH: %d ****** \n", LengthOfDLL(head));
    iterateDLL(head);

    DeleteDLLNode(&head, 2);
    printf("****** LENGTH: %d ****** \n", LengthOfDLL(head));
    iterateDLL(head);

    DeleteDLLNode(&head, 1);
    printf("****** LENGTH: %d ****** \n", LengthOfDLL(head));
    iterateDLL(head);

    return 0;
}
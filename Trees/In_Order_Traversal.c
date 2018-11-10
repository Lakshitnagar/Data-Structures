#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct StackNode{
    struct BinaryTreeNode *BTNode;
    struct StackNode *next;
};

struct StackNode *createNewStackNode(){
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    if(!newNode) return NULL;
    else return newNode;
}

struct StackNode *createNewStack(){
    return NULL;
}

void iterateStack(struct StackNode *head){
    struct StackNode *currNode, *nextNode;

    if(!head) return;
    
    currNode = head;
    nextNode = currNode->next;

    int i=0;
    while(nextNode){
        printf("Data at %dth location : %d \n", i, currNode->BTNode);
        currNode = nextNode;
        nextNode = nextNode->next;
        i++;
    }
    printf("Data at %dth location : %d \n \n", i, currNode->BTNode);

}

int StackLength(struct StackNode *head){
    if(!head) return 0;

    int count = 0;
    struct StackNode *currNode = head;

    while(currNode!=NULL){
        count++;
        currNode = currNode->next;
    }

    return count;
}

void push(struct StackNode **top, struct BinaryTreeNode *BTNode){
    struct StackNode *newStackNode = createNewStackNode();
    if(!newStackNode) return;

    newStackNode->BTNode = BTNode;
    newStackNode->next = *top;
    *top = newStackNode;
}

int isEmptyStack(struct StackNode *top){
    return top == NULL;
}

struct BinaryTreeNode *pop(struct StackNode **top){
    if(isEmptyStack(*top)) return NULL;

    struct BinaryTreeNode *data;
    struct StackNode *temp = *top;
    data = temp->BTNode;
    *top = temp->next;
    free(temp);

    return data;
}

struct BinaryTreeNode{
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};

struct BinaryTreeNode *createNewBTNode(){
    struct BinaryTreeNode *BTNode;
    BTNode = (struct BinaryTreeNode *)malloc(sizeof(struct BinaryTreeNode));
    if(!BTNode) return NULL;

    BTNode->left = NULL;
    BTNode->right = NULL;

    return BTNode;
}

struct BinaryTreeNode *createFullBinaryTree_recursive(int depth){
    static int data = 1;
    struct BinaryTreeNode *BTNode;
    BTNode = createNewBTNode();

    if(depth == 0){
        BTNode->data = data++;
        return BTNode;
    }
    BTNode->left = createFullBinaryTree_recursive(depth-1);
    BTNode->data = data++;
    BTNode->right = createFullBinaryTree_recursive(depth-1);

    return BTNode;
}

void inOrderTraversal_recursive(struct BinaryTreeNode *root){
    if(root){
        inOrderTraversal_recursive(root->left);
        printf("Node : %d\n", root->data);
        inOrderTraversal_recursive(root->right);
    }
}

void inOrderTraversal_iterative(struct BinaryTreeNode *root){
    struct StackNode *S = createNewStack();
    struct StackNode **top = &S;

    while(1){
        while(root){
            push(top, root);
            root = root->left;
        }

        if(isEmptyStack(S))
            break;
        
        root = pop(top);
        printf("Node :%d\n", root->data);
        root = root->right;
    }
}

int main(){
    struct BinaryTreeNode *BTRoot;
    BTRoot = createFullBinaryTree_recursive(3);

    inOrderTraversal_iterative(BTRoot);

    return 0;
}
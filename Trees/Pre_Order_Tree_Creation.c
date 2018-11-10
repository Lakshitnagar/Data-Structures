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

// ToDo : complete it by tracking depth while creating
struct BinaryTreeNode *createFullBinaryTree_iterative(int depth){
    struct StackNode *S = createNewStack();
    struct BinaryTreeNode *BTRoot, *root, *left, *right;
    int count = 1;
    int dp = 0;
    int leaf = 0;
    BTRoot = createNewBTNode();
    root = BTRoot;

    while(1){
        while(root){
            root->data = count++;

            if(dp < depth){
                left = createNewBTNode();
                right = createNewBTNode();
                root->left = left;
                root->right = right;
                push(&S, right);
                dp++;
            }
            else{
                root->left = root->right = NULL;
                leaf = 1;
            }

            root = root->left;
        }

        if(isEmptyStack(S))
            break;
        
        if(leaf){
            root = pop(&S);
            leaf = 0;
        }
        else{
            root = pop(&S);
            dp--;
        }
        
        // root = pop(&S);
        // dp--;
    }

    return BTRoot;
}

struct BinaryTreeNode *createFullBinaryTree_recursive(int depth){
    static int data = 1;
    struct BinaryTreeNode *BTNode;
    BTNode = createNewBTNode();
    BTNode->data = data++;

    if(depth == 0) return BTNode;
    BTNode->left = createFullBinaryTree_recursive(depth - 1);
    BTNode->right = createFullBinaryTree_recursive(depth - 1);

    return BTNode;
}

void preOrderTraversal_Recursive(struct BinaryTreeNode *root){
    if(root){
        printf("node : %d\n", root->data);
        preOrderTraversal_Recursive(root->left);
        preOrderTraversal_Recursive(root->right);
    }
}

int main(){
    struct BinaryTreeNode *BTRoot;
    BTRoot = createFullBinaryTree_iterative(2);

    preOrderTraversal_Recursive(BTRoot);

    return 0;
}
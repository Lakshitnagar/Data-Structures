#include <stdio.h>
#include <stdlib.h>

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

struct BinaryTreeNode *createFullBinaryTree_Preorder(int depth){
    static int data = 1;
    struct BinaryTreeNode *BTNode;
    BTNode = createNewBTNode();
    BTNode->data = data++;

    if(depth == 0) return BTNode;
    BTNode->left = createFullBinaryTree_recursive(depth - 1);
    BTNode->right = createFullBinaryTree_recursive(depth - 1);

    return BTNode;
}

int main(){
    struct BinaryTreeNode *BTRoot, *BTLeft, *BTRight;
    BTRoot = createNewBTNode();
    BTLeft = createNewBTNode();
    BTRight = createNewBTNode();

    BTRoot->data = 1;
    BTLeft->data = 2;
    BTRight->data = 3;

    BTRoot->left = BTLeft;
    BTRoot->right = BTRight;

    printf("Root : %d\n", BTRoot->data);
    printf("Left : %d\n", BTRoot->left->data);
    printf("Right : %d\n", BTRoot->right->data);

    return 0;
}